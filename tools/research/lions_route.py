"""Shortest walks (on the model) from a stage 3 dream start square to a first square next to (10, 13) that makes the day point cyan, no character touched (docs/discoveries.md, the cyan route to the Natural World lions).
Run after make check: python3 tools/research/lions_route.py (prints the stage 3 mood grid first; takes a few minutes)."""
# Square changes are logged again on every revisit, so revisits are allowed. For a target square N with mood (nx, ny),
# cyan needs trunc(SX/n) + trunc(nx/3) in 4..9 and trunc(SY/n) + trunc(ny/3) in -9..-4.
import os
import struct

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
exe = open(os.path.join(ROOT, 'build', 'SLPS_015.56'), 'rb').read()
def off(a): return a - 0x80010000 + 0x800
def u32(a): return struct.unpack_from('<I', exe, off(a))[0]
def s8(v): return v - 256 if v >= 128 else v
st = 3
cols, rows = struct.unpack_from('<hh', exe, off(0x800861D4) + st*8)
g = u32(0x80086590 + st*4)
print("cols", cols, "rows", rows)
for r in range(rows):
    line = []
    for c in range(cols):
        v = struct.unpack_from('<H', exe, off(g) + 2*(r*cols + c))[0]
        line.append("%3d,%3d" % (s8(v & 0xff), s8(v >> 8)))
    print("row %2d: " % r + " | ".join(line))

# Route search (model): hex neighbours, odd rows shifted half a square left (StageMap_ChunkColRow).
grid = {}
first = {}
for s in range(14):
    cc, rr = struct.unpack_from('<hh', exe, off(0x800861D4) + s*8)
    gg = u32(0x80086590 + s*4)
    for r in range(rr):
        for c in range(cc):
            v = struct.unpack_from('<H', exe, off(gg) + 2*(r*cc + c))[0]
            m = (s8(v & 0xff), s8(v >> 8))
            first.setdefault(m, (s, c, r))
            if s == st: grid[(c, r)] = m
def nb(sq):
    c, r = sq
    if r & 1: cand = [(c-1, r), (c+1, r), (c-1, r-1), (c, r-1), (c-1, r+1), (c, r+1)]
    else: cand = [(c-1, r), (c+1, r), (c, r-1), (c+1, r-1), (c, r+1), (c+1, r+1)]
    return [q for q in cand if q in grid and grid[q] != (9, 0)]
def axis(last, s, n):
    r = int(s / n) + int(last / 3)
    return -9 if r > 9 else (9 if r < -9 else r)
def band(v): return 2 if v >= 4 else (0 if v < -3 else 1)
table = [[6, 7, 2], [4, 7, 1], [3, 0, 5]]
def colour(log):
    n = len(log); x = axis(log[-1][0], sum(p[0] for p in log), n); y = axis(log[-1][1], sum(p[1] for p in log), n)
    return (x, y), table[band(x)][band(y)]
T = (10, 13)
print("neighbours of", T, [(q, grid[q]) for q in nb(T)])
starts = [sq for sq in grid if grid[sq] != (9, 0) and first[grid[sq]] == (st, sq[0], sq[1])]
print("start squares:", len(starts))
ban = set(nb(T)) | {T}
def need(N):
    nx, ny = grid[N]; ax, ay = int(nx / 3), int(ny / 3)
    return 4 - ax, -4 - ay   # mean x >= mx, mean y <= my (positive and negative means)
results = []
for N in nb(T):
    mx, my = need(N)
    # state: (sq, ex, ey) with ex = SX - mx*n, ey = SY - my*n
    C = 80
    start = {}
    for s in starts:
        if s in ban: continue
        start[(s, grid[s][0] - mx, grid[s][1] - my)] = None
    prev = dict(start); layer = list(start); n = 1; hit = None
    while layer and n < 60 and not hit:
        new = []
        for st_ in layer:
            sq, ex, ey = st_
            for q in nb(sq):
                if q == N:
                    fx, fy = ex + grid[N][0] - mx, ey + grid[N][1] - my
                    if fx >= 0 and fy <= 0: hit = (st_, n + 1); break
                    continue
                if q in ban: continue
                k = (q, min(C, ex + grid[q][0] - mx), max(-C, ey + grid[q][1] - my))
                if k[1] < -C or k[2] > C or k in prev: continue
                prev[k] = st_; new.append(k)
            if hit: break
        layer = new; n += 1
    if hit:
        st_, steps = hit; path = [N]
        while st_ is not None: path.append(st_[0]); st_ = prev[st_]
        path.reverse()
        log = [grid[q] for q in path]
        results.append((steps, N, path, colour(log)))
for steps, N, path, (pt, col) in sorted(results):
    print("via", N, grid[N], "squares", steps, "point", pt, "colour", col)
    print("  ", " ".join("(%d,%d)%s" % (q[0], q[1], grid[q]) for q in path))
