#!/usr/bin/env python3
"""Progress of the decomp: game functions written in C, bytes, names.

  tools/progress.py [--json]
Game code is everything under asm/{non,}matchings/game/; Sony library units (asm/psyq/) are
counted apart and never decompiled. A function counts as done when no INCLUDE_ASM in src/
names it and `make check` passes (run it first).
"""
import glob
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    sizes = {}
    # splat writes matched functions to asm/matchings/ (disassemble_all), the rest to asm/nonmatchings/.
    for path in glob.glob(f"{ROOT}/asm/*matchings/game/**/*.s", recursive=True):
        m = re.search(r"nonmatching\s+(\w+),\s*(0x[0-9A-Fa-f]+)", open(path, encoding="utf-8").read())
        if m:
            sizes[m.group(1)] = int(m.group(2), 16)
    pending = set()
    for path in glob.glob(f"{ROOT}/src/**/*.c", recursive=True):
        pending.update(re.findall(r"INCLUDE_ASM\(\s*\"[^\"]+\",\s*(\w+)\)", open(path, encoding="utf-8").read()))
    done = [f for f in sizes if f not in pending]
    total_b = sum(sizes.values())
    done_b = sum(sizes[f] for f in done)
    sony = sum(1 for l in open(f"{ROOT}/config/symbol_addrs.psyq.txt") if "type:func" in l)
    ours = sum(1 for l in open(f"{ROOT}/config/symbol_addrs.txt") if "=" in l and not l.lstrip().startswith("//"))
    r = {"game_functions": len(sizes), "done_functions": len(done), "game_bytes": total_b, "done_bytes": done_b,
         "done_percent_bytes": round(100 * done_b / total_b, 2) if total_b else 0, "named_symbols": ours,
         "sony_functions": sony}
    if "--json" in sys.argv:
        print(json.dumps(r))
    else:
        print(f"game code: {len(done)}/{len(sizes)} functions, {done_b}/{total_b} bytes ({r['done_percent_bytes']} %) in C; "
              f"{ours} names of our own; {sony} Sony functions linked as is")


if __name__ == "__main__":
    main()
