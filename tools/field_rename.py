#!/usr/bin/env python3
"""Rename struct fields with evidence, everywhere the compiler says they are used.

    tools/field_rename.py FIELDS.tsv [--dry-run]

FIELDS.tsv: one rename per line, tab separated: FILE, STRUCT, OLD, NEW, evidence.
FILE is the header or unit that defines `typedef struct STRUCT { ... } STRUCT;` (or `struct STRUCT {`).
Blank lines and lines starting with # are skipped.

How it works: it renames the member in the struct's definition, then compiles every C unit of
src/ with the game's own toolchain (make print-* gives the exact commands) and reads cc1's
"structure has no member named `OLD'" errors: each one names a file and a line that accesses the
renamed member, and only that line's `->OLD` / `.OLD` is rewritten. It repeats until no such
error is left. A line where OLD appears more than once, or an error it cannot place, stops it
with a report, leaving the tree as it was. Field names never change the code, so after it:
tools/unit_check.sh on every unit, then make check.
"""
import argparse
import pathlib
import re
import shutil
import subprocess
import sys
import tempfile

ROOT = pathlib.Path(__file__).resolve().parent.parent
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
ERR = re.compile(r"^(?P<file>[^:]+):(?P<line>\d+): (?:structure|union) has no member named `(?P<name>\w+)'")


def make_var(name):
    return subprocess.run(["make", "-s", f"print-{name}"], cwd=ROOT, capture_output=True, text=True, check=True).stdout.strip()


def struct_block(text, struct):
    """Return (start, end) of the braces body of struct STRUCT in text."""
    m = re.search(r"(?:typedef\s+)?struct\s+" + re.escape(struct) + r"\s*\{", text)
    if not m:
        return None
    depth, i = 0, m.end() - 1
    while i < len(text):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return m.end(), i
        i += 1
    return None


def compile_errors(units, cmds):
    cpp, cppflags, cc1, cflags = cmds
    errs = []
    for u in units:
        p = subprocess.run(f"{cpp} {cppflags} {u} | {cc1} {cflags} -quiet -o /dev/null", shell=True, cwd=ROOT,
                           capture_output=True, text=True)
        for line in p.stderr.splitlines():
            m = ERR.match(line)
            if m:
                errs.append((m.group("file"), int(m.group("line")), m.group("name")))
            elif ": " in line and ("error" in line.lower() or "parse" in line.lower() or "undeclared" in line):
                errs.append((u, 0, "OTHER " + line))
    return errs


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("fields")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    rows = []
    for n, line in enumerate(pathlib.Path(args.fields).read_text().splitlines(), 1):
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        cols = [c.strip() for c in line.split("\t")]
        if len(cols) < 5 or not cols[4]:
            sys.exit(f"{args.fields}:{n}: need FILE STRUCT OLD NEW evidence (tabs)")
        f, st, old, new, ev = cols[:5]
        if not all(IDENT.match(x) for x in (st, old, new)):
            sys.exit(f"{args.fields}:{n}: not an identifier")
        rows.append((f, st, old, new, ev))

    units = sorted(str(p.relative_to(ROOT)) for p in (ROOT / "src").rglob("*.c"))
    cmds = (make_var("CPP"), make_var("CPPFLAGS"), make_var("CC1"), make_var("CFLAGS"))
    before = compile_errors(units, cmds)
    if before:
        sys.exit("the tree does not compile cleanly before the renames:\n" + "\n".join(map(str, before[:10])))

    backup = pathlib.Path(tempfile.mkdtemp(prefix="field_rename."))
    touched = set()

    def save(path):
        if path not in touched:
            dst = backup / path
            dst.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(ROOT / path, dst)
            touched.add(path)

    def restore():
        for path in touched:
            shutil.copy2(backup / path, ROOT / path)

    # 1. definitions
    renamed = {}  # old name -> set of new names (to map errors back)
    for f, st, old, new, ev in rows:
        path = ROOT / f
        text = path.read_text(errors="surrogateescape")
        blk = struct_block(text, st)
        if blk is None:
            restore()
            sys.exit(f"{f}: struct {st} not found")
        body = text[blk[0]:blk[1]]
        code = re.sub(r"/\*.*?\*/|//[^\n]*", " ", body, flags=re.S)  # a comment may say the new name
        if re.search(r"\b" + re.escape(new) + r"\b", code):
            restore()
            sys.exit(f"{f}: struct {st} already has a member {new}")
        # rename the member in code only: comments of the struct may mention the old name
        parts = re.split(r"(/\*.*?\*/|//[^\n]*)", body, flags=re.S)
        k = 0
        for i in range(0, len(parts), 2):
            parts[i], n = re.subn(r"\b" + re.escape(old) + r"\b", new, parts[i])
            k += n
        nb = "".join(parts)
        if k != 1:
            restore()
            sys.exit(f"{f}: struct {st}: member {old} found {k} times")
        save(f)
        path.write_text(text[:blk[0]] + nb + text[blk[1]:], errors="surrogateescape")
        renamed.setdefault(old, []).append(new)
    print(f"{len(rows)} member definitions renamed")

    # 2. accesses, driven by the compiler
    fixed = 0
    multi = set()
    for rnd in range(40):
        errs = compile_errors(units, cmds)
        for file, ln, name in errs:
            rel = str(pathlib.Path(file).resolve().relative_to(ROOT)) if file.startswith("/") else file
            if any(m[0] == rel and m[1] == ln and m[2] == name for m in multi):
                restore()
                sys.exit(f"{rel}:{ln}: several accesses on this line, not all of the renamed struct: fix it by hand")
        other = [e for e in errs if e[2].startswith("OTHER")]
        miss = [e for e in errs if not e[2].startswith("OTHER")]
        if other and not miss:
            restore()
            sys.exit("compile errors that are not renamed members:\n" + "\n".join(e[2] for e in other[:10]))
        if not miss:
            break
        for file, ln, name in sorted(set(miss)):
            if name not in renamed or len(renamed[name]) != 1:
                restore()
                sys.exit(f"{file}:{ln}: `{name}' is renamed in several structs of this batch, or not in it: split the batch")
            new = renamed[name][0]
            rel = str(pathlib.Path(file).resolve().relative_to(ROOT)) if file.startswith("/") else file
            path = ROOT / rel
            lines = path.read_text(errors="surrogateescape").split("\n")
            src = lines[ln - 1]
            hits = re.findall(r"(?:->|\.)\s*" + re.escape(name) + r"\b", src)
            if not hits:
                restore()
                sys.exit(f"{rel}:{ln}: no access of {name} found on the line cc1 names:\n  {src.strip()}")
            if len(hits) > 1:
                # all of them are rewritten; if one belonged to another struct, the next round
                # reports "no member named NEW" on this line and the batch is refused
                multi.add((rel, ln, new))
            save(rel)
            lines[ln - 1] = re.sub(r"((?:->|\.)\s*)" + re.escape(name) + r"\b", r"\g<1>" + new, src)
            path.write_text("\n".join(lines), errors="surrogateescape")
            fixed += 1
    else:
        restore()
        sys.exit("still failing after 40 rounds")
    print(f"{fixed} accesses rewritten in {len(touched)} files")
    if args.dry_run:
        restore()
        print("dry run: tree restored")
    else:
        levels = ROOT / "config" / "name_levels.tsv"  # the audit levels follow the rename
        if levels.exists():
            moved = {(st, old): new for _, st, old, new in ((r[0], r[1], r[2], r[3]) for r in rows)}
            out = []
            for line in levels.read_text(encoding="utf-8").split("\n"):
                c = line.split("\t")
                if len(c) > 2 and c[1] == "field" and (c[2].rsplit(":", 1)[-1], c[0]) in moved:
                    c[0] = moved[(c[2].rsplit(":", 1)[-1], c[0])]
                out.append("\t".join(c))
            levels.write_text("\n".join(out), encoding="utf-8")
        print("now run tools/unit_check.sh on every unit, then make check")
    shutil.rmtree(backup, ignore_errors=True)


if __name__ == "__main__":
    main()
