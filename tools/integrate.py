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
        depth += line.count("{") - line.count("}")
        if depth == 0 and line.rstrip().endswith((";", "*/")) or line.lstrip().startswith("#"):
            items.append("\n".join(buf))
            buf = []
    if buf:
        items.append("\n".join(buf))
    return items


def is_function_start(item):
    head = item.split("{", 1)[0]
    return "(" in head and ";" not in head and "{" in item and not head.lstrip().startswith(("typedef", "struct", "union", "enum", "extern"))


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
        if not buf and line.startswith("INCLUDE_ASM"):
            bodies.append(line)
            continue
        buf.append(line)
        depth += line.count("{") - line.count("}")
        if depth == 0 and (line.rstrip().endswith((";", "}")) or line.lstrip().startswith("//")):
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
    block = ("\n".join(new) + "\n\n" if new else "") + body + "\n"
    patched = normalize(unit[:m.start()] + block + unit[m.end():])
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
