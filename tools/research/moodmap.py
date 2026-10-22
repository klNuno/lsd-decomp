"""Which mood points (-9..9 on each axis) some stage square carries, and which stage matches first (docs/discoveries.md, the 51 points no dream can start from).
Run from anywhere: python3 tools/research/moodmap.py (reads extract/SLPS_015.56)."""
import os
import struct
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
D = open(os.path.join(ROOT, 'extract', 'SLPS_015.56'), 'rb').read()
BASE = 0x80010000 - 0x800
def w(a): return struct.unpack_from('<I', D, a - BASE)[0]
def h(a): return struct.unpack_from('<h', D, a - BASE)[0]
def sb(v): return v - 256 if v > 127 else v
first = {}; allv = {}
for st in range(14):
    cols, rows = h(0x800861D4 + 8*st), h(0x800861D6 + 8*st)
    p = w(0x80086590 + 4*st)
    for r in range(rows):
        for c in range(cols):
            v = struct.unpack_from('<H', D, p - BASE + 2*(r*cols + c))[0]
            pt = (sb(v & 0xff), sb(v >> 8))
            allv.setdefault(pt, []).append((st, c, r))
            first.setdefault(pt, (st, c, r))
inrange = [(x, y) for x in range(-9, 10) for y in range(-9, 10)]
unc = [p for p in inrange if p not in first]
out = [p for p in first if p not in set(inrange)]
print('covered', len([p for p in inrange if p in first]), 'uncovered', len(unc), unc[:20])
print('table points outside -9..9:', out)
print('winning stage count', Counter(v[0] for p, v in first.items() if p in set(inrange)))
dups = [(p, v) for p, v in allv.items() if len(v) > 1]
print('points in >1 chunk', len(dups))
print('point (0,0):', allv.get((0, 0)))
print('min |x|,|y| of uncovered', min(abs(x) for x, y in unc), min(abs(y) for x, y in unc))
for y in range(9, -10, -1):
    print('%3d ' % y + ''.join('.' if (x, y) in unc else '%x' % first[(x, y)][0] for x in range(-9, 10)))
