"""Each TIX texture set's part count and largest part, the header words 5 to 8 Tix_GetMaxPartSize reads (docs/discoveries.md, the texture heap margin).
Run after make check-disk: python3 tools/research/tixsizes.py [extract folder, default extract]."""
import glob
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
top = sys.argv[1] if len(sys.argv) > 1 else os.path.join(ROOT, 'extract')
rows = []
for p in sorted(glob.glob(top + "/CDI/STG*/*.TIX")):
    with open(p, "rb") as f:
        h = struct.unpack("<9I", f.read(36))
    n = h[0]
    sizes = h[5:5 + n]
    print(f"{os.path.relpath(p, top)} parts={n} offs={[hex(x) for x in h[1:1+n]]} sizes={list(sizes)} max={max(sizes)} file={os.path.getsize(p)}")
