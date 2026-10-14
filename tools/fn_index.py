#!/usr/bin/env python3
"""Inventory of the functions still in asm: size, calls, gp, rodata and jump-table use.

  tools/fn_index.py [--json build/fn_index.json] [--leaf] [--max-size 0x40] [--no-gp] [--no-rodata]
Prints one line per function: name, size, calls, flags (L leaf, G gp_rel, R rodata/jtbl, S strings).
"""
import argparse
import glob
import json
import os
import re

RODATA = (0x80010000, 0x800118DC)  # main .rodata, before the first function
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def scan(path):
    body = open(path, encoding="utf-8").read()
    m = re.search(r"nonmatching\s+(\w+),\s*(0x[0-9A-Fa-f]+)", body)
    name, size = (m.group(1), int(m.group(2), 16)) if m else (os.path.basename(path)[:-2], 0)
    calls = sorted(set(re.findall(r"\bjal\s+(\w+)", body)))
    return {
        "name": name,
        "file": os.path.relpath(path, ROOT),
        "size": size,
        "calls": calls,
        "leaf": not calls and "jalr" not in body,
        "gp": "%gp_rel" in body,
        "rodata": "jtbl_" in body or bool(re.search(r"\bjr\s+\$(?!ra\b)", body))
        or any(RODATA[0] <= int(x, 16) < RODATA[1] for x in re.findall(r"\b[DL]_(8001[0-9A-F]{4})\b", body)),
        "unaligned": bool(re.search(r"\b(lwl|lwr|swl|swr)\b", body)),
        "gte": bool(re.search(r"\b(mtc2|mfc2|ctc2|cfc2|lwc2|swc2|cop2)\b", body)),
    }


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--json")
    p.add_argument("--leaf", action="store_true")
    p.add_argument("--no-gp", action="store_true")
    p.add_argument("--no-rodata", action="store_true")
    p.add_argument("--max-size", type=lambda s: int(s, 0), default=None)
    a = p.parse_args()
    fns = [scan(f) for f in sorted(glob.glob(f"{ROOT}/asm/nonmatchings/**/*.s", recursive=True))]
    if a.json:
        json.dump(fns, open(a.json, "w"), indent=1)
    for f in fns:
        if a.leaf and not f["leaf"] or a.no_gp and f["gp"] or a.no_rodata and f["rodata"]:
            continue
        if a.max_size is not None and f["size"] > a.max_size:
            continue
        flags = "".join(c for c, k in (("L", "leaf"), ("G", "gp"), ("R", "rodata"), ("U", "unaligned"), ("T", "gte")) if f[k])
        print(f"{f['name']} 0x{f['size']:x} {flags} {','.join(f['calls'][:4])}")


if __name__ == "__main__":
    main()
