"""Convert a PCSX-Redux screenshot dump (frameNNNNN-WxH-BPP.raw) to PNG next to it."""
import re
import sys

import png

src = sys.argv[1]
m = re.search(r"-(\d+)x(\d+)-(16|24)\.raw$", src)
if not m:
    sys.exit(f"unexpected name: {src}")
w, h, bpp = (int(g) for g in m.groups())
data = open(src, "rb").read()
rows = []
for y in range(h):
    if bpp == 24:
        rows.append(data[y * w * 3:(y + 1) * w * 3])
        continue
    row = []
    for x in range(w):
        v = data[2 * (y * w + x)] | data[2 * (y * w + x) + 1] << 8
        row += [(v & 31) * 255 // 31, (v >> 5 & 31) * 255 // 31, (v >> 10 & 31) * 255 // 31]
    rows.append(row)
with open(src[:-4] + ".png", "wb") as f:
    png.Writer(w, h, greyscale=False).write(f, rows)
print(src[:-4] + ".png")
