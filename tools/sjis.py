"""Re-encode a splat .s file to Shift-JIS on stdout: splat decodes the game's strings to UTF-8
with Python's codec, so the same codec gives the original bytes back."""
import sys

sys.stdout.buffer.write(open(sys.argv[1], encoding="utf-8").read().encode("shift_jis"))
