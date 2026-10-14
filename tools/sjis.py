"""Re-encode splat asm to Shift-JIS on stdout: splat decodes the game's strings to UTF-8
with Python's codec, so the same codec gives the original bytes back.

  sjis.py FILE.s    the file, re-encoded
  sjis.py -         filter for compiled C (after maspsx): every `.include "asm/....s"` line
                    (INCLUDE_ASM, INCLUDE_RODATA) is replaced by that file, re-encoded, because
                    `as` would read it as UTF-8 and lengthen every non-ASCII string. Other
                    lines pass through byte for byte.
"""
import re
import sys

INCLUDE = re.compile(rb'^\s*\.include\s+"(asm/[^"]+\.s)"\s*(#.*)?$')


def inline(data, depth=0):
    out = []
    for line in data.split(b"\n"):
        m = INCLUDE.match(line)
        if m and depth < 8:
            text = open(m.group(1).decode(), encoding="utf-8").read().encode("shift_jis")
            out.append(inline(text, depth + 1))
        else:
            out.append(line)
    return b"\n".join(out)


if sys.argv[1] == "-":
    sys.stdout.buffer.write(inline(sys.stdin.buffer.read()))
else:
    sys.stdout.buffer.write(open(sys.argv[1], encoding="utf-8").read().encode("shift_jis"))
