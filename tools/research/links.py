"""Dump of the fixed and facing link lists of each stage and the navigation flag each sets (docs/engine/links.md, 17 fixed links with flags 0 to 12, 32 facing links with flags 14 to 29).
Run from anywhere: python3 tools/research/links.py (reads extract/SLPS_015.56)."""
import os
import struct

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
D = open(os.path.join(ROOT, "extract", "SLPS_015.56"), "rb").read(); B = 0x80010000 - 0x800
def u8(a): return D[a-B]
def s8(a): v=D[a-B]; return v-256 if v>127 else v
def s16(a): return struct.unpack_from('<h',D,a-B)[0]
def w(a): return struct.unpack_from('<I',D,a-B)[0]
flags={}; total=0
for st in range(14):
    n=u8(0x80088748+st); t=w(0x80088710+4*st)
    for i in range(n):
        e=t+6*i
        a,b,c,d=s16(e),s16(e+2),s8(e+4),u8(e+5)
        y=w(0x80088664+4*c)+6*d if 0<=c<14 else 0
        fl=s8(y+5) if y else None
        total+=1
        flags.setdefault(fl,[]).append((st,a,b,c,d))
        print(f'stage {st} link{i}: chunk {a} tile {b} -> stage {c} entry {d} navflag {fl}')
print('links',total,'distinct flags',sorted(k for k in flags if k is not None))
print('--- second table with nav flags (Link_FindFacing, 0x800889F0, 0x80088980, 0x80088820)')
f2=set()
for st in range(14):
    n=u8(0x800889F0+st); t=w(0x80088980+4*st)
    for i in range(n):
        e=t+6*i
        a,b,c,d=s16(e),s16(e+2),s8(e+4),u8(e+5)
        y=w(0x80088820+4*c)+6*d
        fl=s8(y+5); f2.add(fl)
        print(f'stage {st} link{i}: chunk {a} tile {b} -> stage {c} entry {d} navflag {fl}')
print('second table flags', sorted(f2), 'union', sorted(f2|set(k for k in flags if k is not None)))
