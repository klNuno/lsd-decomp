#!/usr/bin/env python3
"""List the raw addresses of the build: words the linker cannot move.

    python3 tools/rawscan.py [--max N]

Run from the repo root after `make check`. It links the objects of build/ twice in a temp dir,
once at the retail base and once with .main 0x10000 higher (and `_gp` moved the same way), then
compares the two images word by word. A word the linker relocated changes by 0x10000 (data), by
0x4000 in a jal/j field or by 1 in a lui. A word that stays equal although it is a pointer into the
executable, a jal/j into it or a lui of its upper half is a raw address: a shifted build (code or
data added before it) would still use the old value. It also flags what this method cannot see:
a numeric `_gp` in linker/lsd.ld and a numeric .text size in asm/header.s.

Columns: address, section, object, symbol + offset, kind. Last line: `# N raw words`.
Exit code 0 (it is a report); with --max N, 1 when more than N are found.
"""
import argparse
import bisect
import os
import re
import struct
import subprocess
import sys
import tempfile

CROSS = "mipsel-linux-gnu-"
DELTA = 0x10000
LD_SCRIPT = "linker/lsd.ld"
EXTRA_SCRIPTS = ["linker/undefined_syms_auto.txt", "linker/undefined_funcs_auto.txt"]
SKIP_SUFFIX = ("_START", "_END", "_SIZE", "_VRAM", ".NON_MATCHING")
# lw/lb/lh/lbu/lhu/sw/sb/sh/addiu/ori/lwl/lwr/swl/swr, the instructions that take a %lo after a lui
LO_OPS = {0x09, 0x0D, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x28, 0x29, 0x2A, 0x2B, 0x2E}


def run(cmd):
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit("rawscan: %s failed:\n%s" % (" ".join(cmd), r.stderr[-2000:]))
    return r.stdout


def link(tmp, name, script):
    ld = os.path.join(tmp, name + ".ld")
    open(ld, "w").write(script)
    elf, mapf, binf = (os.path.join(tmp, name + ext) for ext in (".elf", ".map", ".bin"))
    args = [CROSS + "ld", "-nostdlib", "--no-check-sections", "-T", ld]
    for s in EXTRA_SCRIPTS:
        args += ["-T", s]
    run(args + ["-Map", mapf, "-o", elf])
    run([CROSS + "objcopy", "-O", "binary", elf, binf])
    return elf, mapf, open(binf, "rb").read()


def symbols(elf):
    syms = {}
    for line in run([CROSS + "nm", "-n", elf]).splitlines():
        p = line.split()
        if len(p) == 3 and p[1] not in "aA" and not p[2].startswith((".L", "$", "gcc2_compiled", "__gnu_compiled")) and not p[2].endswith(SKIP_SUFFIX):
            syms.setdefault(int(p[0], 16), p[2])
    return syms


def objects(mapf, vram):
    objs = []
    for line in open(mapf):
        m = re.match(r"^ (\.\w+)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+\.o)", line)
        if m and int(m.group(2), 16) >= vram and int(m.group(3), 16):
            objs.append((int(m.group(2), 16), int(m.group(3), 16), m.group(1), m.group(4).replace("build/", "")))
    return sorted(objs)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--max", type=int, help="exit 1 when more raw words than this are found")
    args = ap.parse_args()
    if not os.path.exists(LD_SCRIPT) or not os.path.exists("build/SLPS_015.56"):
        sys.exit("rawscan: run from the repo root after make check")

    script = open(LD_SCRIPT).read()
    m = re.search(r"\.main 0x([0-9A-Fa-f]+) :", script)
    if not m:
        sys.exit("rawscan: no `.main 0x... :` in " + LD_SCRIPT)
    vram = int(m.group(1), 16)
    gp = re.search(r"^(\s*)_gp = (0x[0-9A-Fa-f]+);", script, re.M)
    hi_script = script.replace(m.group(0), ".main 0x%X :" % (vram + DELTA))
    if gp:
        hi_script = hi_script.replace(gp.group(0), "%s_gp = 0x%X;" % (gp.group(1), int(gp.group(2), 16) + DELTA))

    with tempfile.TemporaryDirectory(prefix="rawscan.") as tmp:
        elf, mapf, A = link(tmp, "base", script)
        _, _, B = link(tmp, "hi", hi_script)
        syms = symbols(elf)
        objs = objects(mapf, vram)

    built = open("build/SLPS_015.56", "rb").read()
    if built[:len(A)] != A:
        print("# warning: build/SLPS_015.56 differs from a fresh link of build/: run make check first", file=sys.stderr)

    # the executable runs from .main to the end of .bss
    end = max(o[0] + o[1] for o in objs)

    def inexe(v):
        return vram <= v < end

    sk = sorted(syms)

    def sym(a):
        i = bisect.bisect_right(sk, a) - 1
        return "%s+0x%X" % (syms[sk[i]], a - sk[i]) if i >= 0 else "?"

    ok = [o[0] for o in objs]

    def obj(a):
        i = bisect.bisect_right(ok, a) - 1
        if i >= 0 and a < objs[i][0] + objs[i][1]:
            return objs[i][2], objs[i][3]
        return "?", "?"

    out = []
    # the PS-X EXE header (0x800 bytes before .main)
    pc0, = struct.unpack_from("<I", A, 0x10)
    pc1, = struct.unpack_from("<I", B, 0x10)
    if pc0 == pc1 and inexe(pc0):
        out.append("0x%08X\theader\tasm/header.s.o\tinitial pc\tword 0x%08X (%s)" % (0x10, pc0, sym(pc0)))
    if os.path.exists("asm/header.s"):
        for line in open("asm/header.s"):
            if re.match(r"\s*\.word 0x[0-9A-Fa-f]+\s*/\* \.text size \*/", line):
                size, = struct.unpack_from("<I", A, 0x1C)
                out.append("0x%08X\theader\tasm/header.s.o\ttext size\tword 0x%08X (a number, not main_ROM_END - main_ROM_START)" % (0x1C, size))
    if gp:
        out.append("-\tlinker\t%s\t_gp\t_gp = %s (a number, not main_SDATA_START)" % (LD_SCRIPT, gp.group(2)))

    n = (min(len(A), len(B)) - 0x800) // 4
    for i in range(n):
        a, = struct.unpack_from("<I", A, 0x800 + i * 4)
        b, = struct.unpack_from("<I", B, 0x800 + i * 4)
        pc = vram + i * 4
        sect, o = obj(pc)
        kind = None
        if sect == ".text":
            if a != b:
                continue
            op = a >> 26
            if op in (2, 3):
                t = (pc & 0xF0000000) | ((a & 0x3FFFFFF) << 2)
                if inexe(t):
                    kind = "%s 0x%08X (%s)" % ("jal" if op == 3 else "j", t, sym(t))
            elif op == 0x0F and (vram >> 16) <= (a & 0xFFFF) <= ((end - 1) >> 16) + 1:
                rt = (a >> 16) & 31
                full = None
                for k in range(1, 12):
                    if i + k >= n:
                        break
                    c, = struct.unpack_from("<I", A, 0x800 + (i + k) * 4)
                    if (c >> 21) & 31 == rt and (c >> 26) in LO_OPS:
                        lo = c & 0xFFFF
                        if (c >> 26) != 0x0D and lo & 0x8000:
                            lo -= 0x10000
                        full = (((a & 0xFFFF) << 16) + lo) & 0xFFFFFFFF
                        break
                kind = "lui 0x%04X" % (a & 0xFFFF) + (" -> 0x%08X (%s)" % (full, sym(full)) if full is not None else "")
        else:
            if a == b and inexe(a):
                kind = "word 0x%08X (%s)" % (a, sym(a))
            elif a != b and b - a != DELTA:
                kind = "odd delta 0x%08X -> 0x%08X" % (a, b)
        if kind:
            out.append("0x%08X\t%s\t%s\t%s\t%s" % (pc, sect, o, sym(pc), kind))

    for line in out:
        print(line)
    print("# %d raw words" % len(out))
    if args.max is not None and len(out) > args.max:
        sys.exit(1)


if __name__ == "__main__":
    main()
