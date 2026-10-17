#!/usr/bin/env python3
"""Confidence levels of our names, from the name audit.

    tools/name_levels.py merge OUT.tsv IN.tsv [IN.tsv ...]
    tools/name_levels.py comments LEVELS.tsv [--dry-run]
    tools/name_levels.py check LEVELS.tsv

An audit TSV has a header line and the columns NAME KIND FILE LEVEL NEW EVIDENCE (tab separated).
KIND is func, global, lsd, type or field (FILE is then include/game/x.h:Type); LEVEL is game (seen in
the emulator), code (the code proves it), guess (plausible, unproven) or wrong (contradicted, NEW
holds the fix).

merge: one row per name; when two inputs rate the same name, the lower level wins (wrong, guess,
code, game) and the disagreement is printed. lsd rows (a cross-check of FirecatFG's names) are left
out. Writes OUT with the columns NAME KIND FILE LEVEL EVIDENCE and prints the counts.

comments: rewrites the evidence comment of each func and global row in config/symbol_addrs.txt with
its EVIDENCE, keeping splat's attributes and the notes other tools rely on ("string reached from
data", "object start of") and the docs/ and work/ paths it cited. Colons and semicolons would be read by splat, so they become commas.
After it: make split && make check (comments never change the build).

check: every func and global row names a symbol of config/symbol_addrs.txt, every type row a type
defined in include/ or src/, every field row a member of its struct; every name of ours in
config/symbol_addrs.txt has a row. Exits 1 and lists what is off.
"""
import argparse
import collections
import pathlib
import re
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
SYMS = ROOT / "config" / "symbol_addrs.txt"
ORDER = {"wrong": 0, "guess": 1, "code": 2, "game": 3}
KINDS = ("func", "global", "lsd", "type", "field")
KEEP = re.compile(r"^(string reached from data|object start of)")
REF = re.compile(r"(?:docs|work|\.agents)/[\w./#-]*[\w#-]")  # finding and report paths, kept when the evidence drops them


def read_rows(path):
    lines = pathlib.Path(path).read_text(encoding="utf-8").splitlines()
    if not lines or lines[0].split("\t")[:4] != ["NAME", "KIND", "FILE", "LEVEL"]:
        sys.exit(f"{path}: the first line must be the header NAME KIND FILE LEVEL ...")
    cols = lines[0].split("\t")
    for n, line in enumerate(lines[1:], 2):
        if not line.strip():
            continue
        row = dict(zip(cols, (c.strip() for c in line.split("\t"))))
        if row.get("KIND") not in KINDS or row.get("LEVEL") not in ORDER or not row.get("NAME"):
            sys.exit(f"{path}:{n}: bad KIND or LEVEL: {line[:120]}")
        yield row


def merge(out, inputs):
    best, clashes = {}, 0
    for path in inputs:
        for row in read_rows(path):
            if row["KIND"] == "lsd":
                continue
            key = (row["KIND"], row["NAME"], row["FILE"] if row["KIND"] in ("type", "field") else "")
            old = best.get(key)
            if old and old["LEVEL"] != row["LEVEL"]:
                clashes += 1
                print(f"clash {key[0]} {key[1]}: {old['LEVEL']} ({old['src']}) vs {row['LEVEL']} ({path})")
            if not old or ORDER[row["LEVEL"]] < ORDER[old["LEVEL"]]:
                best[key] = dict(row, src=path)
    rows = sorted(best.values(), key=lambda r: (KINDS.index(r["KIND"]), r["FILE"], r["NAME"]))
    with open(out, "w", encoding="utf-8") as f:
        f.write("NAME\tKIND\tFILE\tLEVEL\tEVIDENCE\n")
        for r in rows:
            f.write("\t".join((r["NAME"], r["KIND"], r["FILE"], r["LEVEL"], r.get("EVIDENCE", ""))) + "\n")
    count = collections.Counter((r["KIND"], r["LEVEL"]) for r in rows)
    for kind in KINDS:
        if any(k == kind for k, _ in count):
            print(kind, " ".join(f"{lv} {count[(kind, lv)]}" for lv in ORDER), sep="\t")
    print(f"{len(rows)} names, {clashes} clashes -> {out}")


def clean(text):
    text = re.sub(r'"([^"]*):"', r'"\1" plus a colon', text)  # "bu00:" keeps its meaning without the colon
    return re.sub(r"\s+", " ", text.replace("//", "/").replace(";", ",").replace(":", ",")).strip()


def comments(levels, dry_run):
    evidence = {r["NAME"]: clean(r.get("EVIDENCE", "")) for r in read_rows(levels)
                if r["KIND"] in ("func", "global") and r["LEVEL"] != "wrong" and r.get("EVIDENCE")}
    out, done = [], set()
    for line in SYMS.read_text(encoding="utf-8").splitlines():
        m = re.match(r"^(\w+)\s*=\s*(0x[0-9A-Fa-f]+);(.*)$", line)
        if not m or m.group(1) not in evidence:
            out.append(line)
            continue
        segs = [s.strip() for s in m.group(3).split("//")[1:]]
        attrs = segs[0] if segs and segs[0] and all(":" in t for t in segs[0].split()) else ""
        notes = [s for s in segs[1 if attrs else 0:] if KEEP.match(s)]
        new = evidence[m.group(1)]
        refs = [r for r in dict.fromkeys(REF.findall(m.group(3))) if r not in new]
        tail = " // ".join(([attrs] if attrs else []) + notes + [new + (f" (see {', '.join(refs)})" if refs else "")])
        out.append(f"{m.group(1)} = {m.group(2)}; // {tail}")
        done.add(m.group(1))
    missing = sorted(set(evidence) - done)
    if not dry_run:
        SYMS.write_text("\n".join(out) + "\n", encoding="utf-8")
    print(f"{len(done)} comments rewritten" + (" (dry run)" if dry_run else ""))
    if missing:
        print(f"{len(missing)} rated names have no line in {SYMS.relative_to(ROOT)}: {' '.join(missing[:20])}")


def struct_bodies():
    """Type name -> list of bodies (comments stripped) of the struct, union or enum it names."""
    out = collections.defaultdict(list)
    for path in list((ROOT / "include").rglob("*.h")) + list((ROOT / "src").rglob("*.c")):
        text = re.sub(r"/\*.*?\*/|//[^\n]*", " ", path.read_text(encoding="utf-8", errors="replace"), flags=re.S)
        for m in re.finditer(r"\b(?:struct|union|enum)\s*(\w*)\s*\{", text):
            depth, i = 0, m.end() - 1
            while i < len(text):
                depth += {"{": 1, "}": -1}.get(text[i], 0)
                if depth == 0:
                    break
                i += 1
            body = text[m.end():i]
            tail = re.match(r"\s*(\w+)\s*;", text[i + 1:])
            for name in {m.group(1), tail.group(1) if tail and text[m.start():m.start() + 7] != "" and
                         re.search(r"typedef\s+$", text[max(0, m.start() - 40):m.start()]) else ""} - {""}:
                out[name].append(body)
        for m in re.finditer(r"typedef\s+[^;{}()]*?\b(\w+)\s*(?:\[[^\]]*\])?\s*;", text):
            out.setdefault(m.group(1), [])
        for m in re.finditer(r"typedef\s+[^;{}]*\(\s*\*\s*(\w+)\s*\)", text):
            out.setdefault(m.group(1), [])
    return out


def check(levels):
    ours = {m.group(1) for m in re.finditer(r"^(\w+) = 0x", SYMS.read_text(encoding="utf-8"), re.M)
            if not re.match(r"^(func|D|jtbl)_[0-9A-F]{8}$", m.group(1))}
    bodies, bad, seen = struct_bodies(), [], set()
    for r in read_rows(levels):
        kind, name = r["KIND"], r["NAME"]
        if kind in ("func", "global"):
            seen.add(name)
            if name not in ours:
                bad.append(f"{kind} {name}: not in config/symbol_addrs.txt")
        elif kind == "type" and name not in bodies:
            bad.append(f"type {name}: no definition in include/ or src/")
        elif kind == "field":
            st = r["FILE"].rsplit(":", 1)[-1]
            if not any(re.search(r"\b" + re.escape(name) + r"\b", b) for b in bodies.get(st, [])):
                bad.append(f"field {st}.{name}: not a member of {st}")
    bad += [f"no row for {n}" for n in sorted(ours - seen)]
    print("\n".join(bad) if bad else "every row matches the code")
    sys.exit(1 if bad else 0)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    m = sub.add_parser("merge")
    m.add_argument("out")
    m.add_argument("inputs", nargs="+")
    c = sub.add_parser("comments")
    c.add_argument("levels")
    c.add_argument("--dry-run", action="store_true")
    k = sub.add_parser("check")
    k.add_argument("levels")
    args = ap.parse_args()
    if args.cmd == "merge":
        merge(args.out, args.inputs)
    elif args.cmd == "check":
        check(args.levels)
    else:
        comments(args.levels, args.dry_run)


if __name__ == "__main__":
    main()
