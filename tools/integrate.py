#!/usr/bin/env python3
"""Move a matched function from work/ into its unit in src/, then prove the whole build.

  tools/integrate.py FUNC FILE.c [--no-check]

FILE.c holds `#include "common.h"`, then top-level declarations (externs, prototypes,
typedefs, structs), then the definition of FUNC. The declarations missing from the unit
go to the declaration block at the top of the unit, and the function replaces
`INCLUDE_ASM(..., FUNC);`. `tools/integrate.py --normalize` only rewrites every unit that way. Then `make check`
runs; on any failure the unit is restored and the exit code is 1. One integration at a time.
"""
import glob
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def find_unit(func):
    pat = re.compile(r'^INCLUDE_ASM\("[^"]+",\s*' + re.escape(func) + r'\);\s*$', re.M)
    for path in sorted(glob.glob(f"{ROOT}/src/**/*.c", recursive=True)):
        text = open(path, encoding="utf-8").read()
        m = pat.search(text)
        if m:
            return path, text, m
    sys.exit(f"{func}: no INCLUDE_ASM line in src/ (already integrated?)")


def rodata_syms(func):
    """D_ symbols that FUNC's original asm references and that have an INCLUDE_RODATA file."""
    hits = glob.glob(f"{ROOT}/asm/nonmatchings/**/{func}.s", recursive=True)
    if not hits:
        return []
    names = set(re.findall(r"%(?:hi|lo)\((D_[0-9A-F]{8})\)", open(hits[0], encoding="utf-8").read()))
    return sorted(n for n in names if glob.glob(f"{ROOT}/asm/nonmatchings/**/{n}.s", recursive=True))


def split_candidate(func, text):
    """(declarations, definition) of FILE.c, without the common.h include."""
    text = re.sub(r'^\s*#include\s+"common\.h"\s*\n', "", text, flags=re.M)
    m = re.search(r"^[^\n;{}]*\b" + re.escape(func) + r"\s*\([^;{]*\)\s*\{", text, re.M)
    if not m:
        sys.exit(f"{func}: no definition found in the candidate")
    return text[:m.start()].strip(), text[m.start():].strip()


def top_level_items(decls):
    """Split declarations into items (a line, or a braced block ending with ';')."""
    items, buf, depth = [], [], 0
    for line in decls.splitlines():
        if not line.strip() or line.strip().startswith("//"):
            continue
        buf.append(line.rstrip())
        code = code_of(line)
        depth += code.count("{") - code.count("}")
        if depth == 0 and (code.endswith(";") or not code.strip()) or line.lstrip().startswith("#"):
            items.append("\n".join(buf))
            buf = []
    if buf:
        items.append("\n".join(buf))
    return items


def code_of(line):
    """The line without /* */ and // comments, for deciding where an item ends."""
    return re.sub(r"//.*", "", re.sub(r"/\*.*?\*/", "", line)).rstrip()


def is_function_start(item):
    """A function definition: the code before its first '{' ends with ')'.
    A struct, union or enum body has no parenthesis right before its brace."""
    if "{" not in item:
        return False
    head = " ".join(code_of(l) for l in item.split("{", 1)[0].splitlines()).strip()
    return head.endswith(")") and not head.startswith(("typedef", "extern"))


def normalize(unit):
    """Rewrite a unit as: includes, every top-level declaration, then functions and
    INCLUDE_ASM lines in their original order. A declaration never sits below a user."""
    includes, decls, bodies, buf, depth = [], [], [], [], 0
    for line in unit.splitlines():
        if not buf and not line.strip():
            continue
        if not buf and line.startswith("#include"):
            includes.append(line)
            continue
        if not buf and line.startswith(("INCLUDE_ASM", "INCLUDE_RODATA")):
            bodies.append(line)
            continue
        buf.append(line)
        code = code_of(line)
        depth += code.count("{") - code.count("}")
        if depth == 0 and (code.endswith((";", "}")) or not code.strip()):
            item = "\n".join(buf)
            buf = []
            if is_function_start(item) and not item.rstrip().endswith(";"):
                bodies.append(item)
            else:
                decls.append(item)
    if buf:
        bodies.append("\n".join(buf))
    seen, uniq = set(), []
    for d in decls:
        key = re.sub(r"\s+", " ", d).strip()
        if key not in seen:
            seen.add(key)
            uniq.append(d)
    out = "\n".join(includes) + "\n\n"
    if uniq:
        out += "\n".join(uniq) + "\n\n"
    return out + "\n\n".join(bodies) + "\n"


def type_name(item):
    """The struct/union tag or typedef name an item defines, else None."""
    code = " ".join(code_of(l) for l in item.splitlines())
    if "{" not in code:
        return None
    m = re.search(r"\}\s*(\w+)\s*;\s*$", code) if code.lstrip().startswith("typedef") else None
    if m:
        return m.group(1)
    m = re.match(r"\s*(?:typedef\s+)?(?:struct|union|enum)\s+(\w+)\s*\{", code)
    return m.group(1) if m else None


def replace_types(unit, items):
    """Items that redefine a type the unit already defines replace that definition in place
    (a matcher extended a sibling's struct); make check then judges every user of it.
    Returns the patched unit and the items still to insert."""
    rest = []
    for item in items:
        name = type_name(item)
        old = None
        if name:
            for cand in top_level_items(unit):
                if type_name(cand) == name:
                    old = cand
                    break
        if old and old in unit:
            unit = unit.replace(old, item, 1)
        else:
            rest.append(item)
    return unit, rest


def main():
    if sys.argv[1:2] == ["--normalize"]:
        for path in sorted(glob.glob(f"{ROOT}/src/**/*.c", recursive=True)):
            text = open(path, encoding="utf-8").read()
            new = normalize(text)
            if new != text:
                open(path, "w", encoding="utf-8").write(new)
                print("normalized", os.path.relpath(path, ROOT))
        return
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    func, cfile = sys.argv[1], sys.argv[2]
    path, unit, m = find_unit(func)
    decls, body = split_candidate(func, open(cfile, encoding="utf-8").read())
    norm = lambda s: re.sub(r"\s+", " ", s).strip()
    have = norm(unit)
    new = [d for d in top_level_items(decls) if norm(d) not in have]
    head, new = replace_types(unit[:m.start()], new)
    # Earlier one-line declarations of FUNC in the unit (often `extern void FUNC();` written by a
    # caller) must agree with its definition: replace them with the definition's own prototype.
    proto = re.sub(r"\s+", " ", body.split("{", 1)[0]).strip() + ";"
    head = re.sub(r"^(?:extern\s+)?[^\n;{}()]*\b" + re.escape(func) + r"\s*\([^;{}]*\)\s*;[ \t]*$",
                  lambda _: proto, head, flags=re.M)
    block = ("\n".join(new) + "\n\n" if new else "") + body + "\n"
    patched = head + block + unit[m.end():]
    # The function's own strings and constants now come from its C literals, emitted at its
    # position: drop the INCLUDE_RODATA lines of every D_ symbol its asm references and the
    # candidate does not name (an `extern` use keeps the line).
    for sym in rodata_syms(func):
        if not re.search(r"\b" + sym + r"\b", decls + body):
            patched = re.sub(r'^INCLUDE_RODATA\("[^"]+",\s*' + sym + r'\);\n\n?', "", patched, flags=re.M)
    patched = normalize(patched)
    with open(path, "w", encoding="utf-8") as f:
        f.write(patched)
    if "--no-check" in sys.argv:
        print(f"{func}: written to {os.path.relpath(path, ROOT)} (not checked)")
        return
    r = subprocess.run(["make", "-s", "check"], cwd=ROOT, capture_output=True, text=True)
    if r.returncode or ": OK" not in r.stdout:
        with open(path, "w", encoding="utf-8") as f:
            f.write(unit)
        subprocess.run(["make", "-s"], cwd=ROOT, capture_output=True)
        tail = (r.stdout + r.stderr).strip().splitlines()[-12:]
        print(f"{func}: make check FAILED, {os.path.relpath(path, ROOT)} restored\n" + "\n".join(tail))
        sys.exit(1)
    print(f"{func}: integrated into {os.path.relpath(path, ROOT)}, make check OK")


if __name__ == "__main__":
    main()
