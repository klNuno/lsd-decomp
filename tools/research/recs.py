"""Dump of the 130 character records of g_entityRecords at 0x80089EA4, 16 bytes each (docs/engine/characters.md, the character record).
Run from anywhere: python3 tools/research/recs.py (reads extract/SLPS_015.56)."""
import os
import struct

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
D = open(os.path.join(ROOT, "extract", "SLPS_015.56"), "rb").read(); B = 0x80010000 - 0x800
def b(a): return D[a-B]
def sb(a): v=D[a-B]; return v-256 if v>127 else v
def w(a): return struct.unpack_from('<I',D,a-B)[0]
print("type addr mood score act deact actR touchR link vid r9 rA rB handler")
for t in range(130):
    a=0x80089EA4+16*t
    print(t, hex(a), (sb(a),sb(a+1)), b(a+2), b(a+3), b(a+4), sb(a+5), sb(a+6), sb(a+7), sb(a+8), sb(a+9), sb(a+10), sb(a+11), hex(w(a+12)))
