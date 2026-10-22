"""Dump of the spawn groups and slots of each stage, with their colour and day rules (docs/engine/characters.md, the slot and group tables).
Run from anywhere: python3 tools/research/spawns.py (reads extract/SLPS_015.56)."""
import os
import struct

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
D = open(os.path.join(ROOT, "extract", "SLPS_015.56"), "rb").read(); B = 0x80010000 - 0x800
def u8(a): return D[a-B]
def s8(a): v=D[a-B]; return v-256 if v>127 else v
def s16(a): return struct.unpack_from('<h',D,a-B)[0]
def w(a): return struct.unpack_from('<I',D,a-B)[0]
cnd={1:'always',2:'month%3==1',3:'month%3==2',4:'month%3==0',5:'day%3==0',6:'day%3!=0',7:'AC80even',8:'day%3==1',9:'day%3==2',20:'even day',21:'odd day'}
print('colour cond table D_80088D16[10..40]:',[s8(0x80088D16+i) for i in range(10,40)])
for st in range(14):
    sp=w(0x80089A8C+4*st); n=s8(0x80089AC4+st); gp=w(0x80089A44+4*st); gn=s8(0x80089A7C+st)
    print(f'== stage {st} slots {n} at {sp:#x}, groups {gn} at {gp:#x}')
    for i in range(gn):
        a=gp+8*i
        c=s8(a+1); m=abs(c)
        desc=cnd.get(m, 'n<10:always' if m<10 else f'colour=={s8(0x80088D16+m)}')
        if c<0: desc+=' once'
        print(f'  g{i}: cond {c} ({desc}) model {u8(a+2)} type {u8(a+3)} pos {[s8(a+4+k) for k in range(4)]}')
    for i in range(n):
        a=sp+6*i
        print(f'  slot{i}: key {s16(a)} parity {s8(a+2)} groups {[s8(a+3+k) for k in range(3)]}')
