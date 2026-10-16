#!/usr/bin/env python3
"""After `make split`: write the last raw addresses of the build as symbols.

    python3 tools/postsplit.py

spimdisasm writes Sony's startup (__SN_ENTRY_POINT, asm/psyq/80011994.s) as `.word` because the
function ends in a RAM size table, and splat writes the PS-X EXE header with numbers. Both keep
retail addresses the linker never moves, so a shifted build crashes on its first instruction.
This rewrites, in place:
  - asm/header.s: initial pc -> __SN_ENTRY_POINT, .text size -> lsd_exe_text_size;
  - linker/lsd.ld: defines lsd_exe_text_size after main_VRAM_END;
  - asm/psyq/80011994.s: every lui/%lo pair and jal of the startup whose target is a known retail
    address, as the instruction with %hi/%lo or a symbol, and a label on the RAM size table.
Only the address-bearing words change: the bytes of the retail build stay the same (make check).
It holds no Sony code, only the retail addresses and the symbols that replace them.
"""
import re
import sys

STARTUP = "asm/psyq/80011994.s"
HEADER = "asm/header.s"
LD = "linker/lsd.ld"
RAMTAB = 0x80011A48
# retail address -> what it is in a relinked build
TARGETS = {
    0x8008AC20: "main_BSS_START",   # bss clear loop start
    0x80090C68: "main_BSS_END",     # bss clear loop end, heap start
    RAMTAB: ".Lstup_ramtab",        # RAM size table at the end of the function
    0x8006B584: "D_8006B3F8 + 0x18C",  # _stacksize
    0x8008AC24: "g_scene + 0x4",    # saved ra
    0x8008A808: "_gp",
    0x80011CF4: "InitHeap",
    0x800118DC: "main",
}
LO_OPS = {0x09: "addiu", 0x23: "lw", 0x2B: "sw"}
WORD = re.compile(r"^(\s*)/\* (\w+) ([0-9A-F]{8}) [0-9A-F]{8} \*/ \.word 0x([0-9A-F]{8})(.*)$")


def reg(n):
    return "$%d" % n


def startup():
    lines = open(STARTUP).read().split("\n")
    start = next(i for i, l in enumerate(lines) if l.startswith("glabel __SN_ENTRY_POINT"))
    end = next(i for i in range(start, len(lines)) if lines[i].startswith("enddlabel __SN_ENTRY_POINT"))
    words = {}
    for i in range(start, end):
        m = WORD.match(lines[i])
        if m:
            words[i] = (int(m.group(3), 16), int(m.group(4), 16), m.group(1), m.group(2))
    done = 0
    pending = {}  # rt -> (line, hi)
    for i in sorted(words):
        vram, w, ind, rom = words[i]
        op = w >> 26
        com = "%s/* %s %08X */ " % (ind, rom, vram)
        if vram == RAMTAB:
            lines[i] = "  .Lstup_ramtab:\n" + lines[i]
            continue
        if op == 0x0F:
            pending[(w >> 16) & 31] = (i, w & 0xFFFF)
        elif op in LO_OPS and (w >> 21) & 31 in pending:
            rs, rt = (w >> 21) & 31, (w >> 16) & 31
            li, hi = pending.pop(rs)
            lo = w & 0xFFFF
            addr = ((hi << 16) + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF
            sym = TARGETS.get(addr)
            if sym is None:
                continue
            lv = words[li][0]
            lines[li] = "%s/* %s %08X */ lui %s, %%hi(%s)" % (words[li][2], words[li][3], lv, reg(rs), sym)
            if op == 0x09:
                lines[i] = com + "addiu %s, %s, %%lo(%s)" % (reg(rt), reg(rs), sym)
            else:
                lines[i] = com + "%s %s, %%lo(%s)(%s)" % (LO_OPS[op], reg(rt), sym, reg(rs))
            done += 2
        elif op == 0x03:
            t = (vram & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
            if t in TARGETS:
                lines[i] = com + "jal %s" % TARGETS[t]
                done += 1
    open(STARTUP, "w").write("\n".join(lines))
    return done


def header():
    s = open(HEADER).read()
    s2 = re.sub(r"\.word 0x[0-9A-F]{8}(\s*)/\* Initial PC \*/", r".word __SN_ENTRY_POINT\1/* Initial PC */", s)
    s2 = re.sub(r"\.word 0x[0-9A-F]{8}(\s*)/\* \.text size \*/", r".word lsd_exe_text_size\1/* .text size */", s2)
    open(HEADER, "w").write(s2)
    ld = open(LD).read()
    if "lsd_exe_text_size" not in ld:
        ld = re.sub(r"^(\s*)main_VRAM_END = \.;$",
                    r"\g<0>\n\1lsd_exe_text_size = ALIGN(main_ROM_END, 0x800) - main_ROM_START;", ld, count=1, flags=re.M)
        open(LD, "w").write(ld)
    return (s != s2) + ("lsd_exe_text_size" in ld)


if __name__ == "__main__":
    n = startup()
    h = header()
    print("postsplit: %d startup words, header and linker script %s" % (n, "done" if h == 2 else "INCOMPLETE"))
    if n != 18 or h != 2:
        sys.exit(1)
