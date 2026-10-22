"""Stage 5 (Violence District) square moods, and which walks inside stage 5 load square (4, 3) on a cyan colour, on the model (docs/discoveries.md, the cyan colour on foot).
Run after make check: python3 tools/research/cyanroute.py."""
# Model (read in the code): the chunk accumulator logs each square entered (DreamSys_LogChunkMood), the day point
# per axis is sum/count + last/3 with a wrap past +-9 (Mood_CalcAxis), no touch means entity point = chunk point,
# colour bands < -3, -3..3, >= 4 into g_moodColors. A square's characters are made when it enters the 3x3 window.
import itertools
import os
import struct

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
exe = open(os.path.join(ROOT, 'build', 'SLPS_015.56'), 'rb').read()
def off(a): return a - 0x80010000 + 0x800
def u32(a): return struct.unpack_from('<I', exe, off(a))[0]
def s8(v): return v - 256 if v >= 128 else v
grid = {}; first = {}
for st in range(14):
    cols, rows = struct.unpack_from('<hh', exe, off(0x800861D4) + st*8)
    g = u32(0x80086590 + st*4)
    for r in range(rows):
        for c in range(cols):
            v = struct.unpack_from('<H', exe, off(g) + 2*(r*cols + c))[0]
            m = (s8(v & 0xff), s8(v >> 8))
            first.setdefault(m, (st, c, r))
            if st == 5: grid[(c, r)] = m
COLS, ROWS = 5, 6
names = {0: 'black', 1: 'blue', 2: 'green', 3: 'cyan', 4: 'red', 5: 'pink', 6: 'yellow', 7: 'white'}
table = [[6, 7, 2], [4, 7, 1], [3, 0, 5]]
def axis(last, s, n):
    r = int(s / n) + int(last / 3)
    return -9 if r > 9 else (9 if r < -9 else r)
def band(v): return 2 if v >= 4 else (0 if v < -3 else 1)
def colour(log):
    n = len(log); x = axis(log[-1][0], sum(p[0] for p in log), n); y = axis(log[-1][1], sum(p[1] for p in log), n)
    return (x, y), table[band(x)][band(y)]
print("stage 5 moods (col, row):")
for r in range(ROWS): print(" ", [grid[(c, r)] for c in range(COLS)])
T = (4, 3)
def near(a, b): return abs(a[0]-b[0]) <= 1 and abs(a[1]-b[1]) <= 1
starts = [sq for sq in grid if first[grid[sq]] == (5, sq[0], sq[1])]
print("possible start squares:", starts)
for s in starts:
    pt, col = colour([grid[s]])
    print(f"start {s} mood {grid[s]} -> point {pt} {names[col]}{'  (4,3) in window' if near(s, T) else ''}")
def nb(sq): return [(sq[0]+dc, sq[1]+dr) for dc in (-1, 0, 1) for dr in (-1, 0, 1) if (dc or dr) and (sq[0]+dc, sq[1]+dr) in grid]
print("walks from a start square (orthogonal or diagonal steps) whose first square next to (4,3) gives cyan:")
for s in starts:
    if near(s, T): continue
    paths = [[s]]
    for depth in range(4):
        new = []
        for p in paths:
            for q in nb(p[-1]):
                if q in p: continue
                pp = p + [q]
                if near(q, T):
                    for incl, log in (("after logging it", pp), ("before logging it", p)):
                        pt, col = colour([grid[x] for x in log])
                        if col == 3: print(f"  {pp} cyan {pt} ({incl})")
                else: new.append(pp)
        paths = new
print("longer walks (up to 8 squares), first square next to (4,3) logged before the spawn: cyan ones")
found = 0
for s in starts:
    if near(s, T): continue
    paths = [[s]]
    for depth in range(7):
        new = []
        for p in paths:
            for q in nb(p[-1]):
                if q in p: continue
                pp = p + [q]
                if near(q, T):
                    pt, col = colour([grid[x] for x in pp])
                    if col == 3: found += 1; print(f"  {pp} cyan {pt}") if found <= 10 else None
                else: new.append(pp)
        paths = new
print("count", found)
