"""Value census of the model grid of every STGxx\\Mxxx.LBD, the records MapModels_NextModel reads (docs/discoveries.md, map files).
Run after make check-disk: python3 tools/research/lbd_models.py [CDI folder, default extract/CDI]."""
import collections
import glob
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
root = sys.argv[1] if len(sys.argv) > 1 else os.path.join(ROOT, 'extract', 'CDI')
C = collections.defaultdict(collections.Counter)
heads = collections.Counter()
for path in sorted(glob.glob(os.path.join(root, 'STG*', 'M*.LBD'))):
    d = open(path, 'rb').read()
    h = struct.unpack_from('<HHiiiii', d, 0)
    C['hdr0'][h[0]] += 1
    C['hdr0C_minus'][(h[4] - h[2] - h[3]) if h[4] else None] += 1
    mo, ms = h[2], h[3]
    base = mo
    lh = struct.unpack_from('<HHHH', d, base)
    heads[lh] += 1
    chains = 0
    for cell in range(400):
        off = base + 8 + cell * 12
        while True:
            b0, b1, w2, b4, b5, s6, nxt = struct.unpack_from('<BBHBBhi', d, off)
            C['b0'][b0] += 1
            if b0:
                C['b1'][b1] += 1; C['b4'][b4] += 1; C['b5'][b5] += 1; C['s6'][s6] += 1
            C['chained'][nxt != 0] += 1
            if not nxt: break
            chains += 1
            off = base + nxt
    C['chains_per_file'][chains] += 1
print('list heads', heads.most_common(8))
for k, v in C.items():
    print(k, sorted(v.items(), key=lambda x: (x[0] is None, x[0]))[:40])
