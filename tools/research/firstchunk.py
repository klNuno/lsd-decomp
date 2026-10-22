"""Which stage and square Stage_FindChunkByMood picks for a mood point, and which arrival record (docs/discoveries.md, natural green from Kyoto).
Run after make check: python3 tools/research/firstchunk.py X Y [X Y ...], e.g. firstchunk.py -6 7 -7 6."""
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
exe = open(os.path.join(ROOT, 'build', 'SLPS_015.56'), 'rb').read()
def off(a): return a - 0x80010000 + 0x800
def u32(a): return struct.unpack_from('<I', exe, off(a))[0]
def find(px, py):
    for st in range(14):
        cols, rows = struct.unpack_from('<hh', exe, off(0x800861D4) + st*8)
        g = u32(0x80086590 + st*4)
        for r in range(rows):
            for c in range(cols):
                v = struct.unpack_from('<h', exe, off(g) + 2*(r*cols + c))[0]
                x = struct.unpack('b', bytes([v & 0xff]))[0]; y = struct.unpack('b', bytes([(v >> 8) & 0xff]))[0]
                if (x, y) == (px, py):
                    sp = u32(0x800885B8 + st*4); n = exe[off(0x800885F0) + st]
                    key = r*256 + c; arr = None
                    for i in range(n):
                        rec = exe[off(sp)+6*i: off(sp)+6*i+6]
                        if rec[0] == c and rec[1] == r: arr = i
                    if arr is None: arr = ('fallback', key % n)
                    return st, (c, r), arr
    return None
a = list(map(int, sys.argv[1:]))
for i in range(0, len(a), 2): print((a[i], a[i+1]), find(a[i], a[i+1]))
