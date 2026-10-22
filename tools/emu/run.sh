#!/usr/bin/env bash
# Run the game headless in PCSX-Redux (no window, no sound) and drive it with Lua.
#   tools/emu/run.sh [extra.lua ...]
# tools/emu/probe.lua always runs first; it reads these variables:
#   LSD_EMU_FRAMES  quit after this many vsyncs (default 1800, about 30 s)
#   LSD_EMU_SHOTS   comma-separated vsync numbers to capture, e.g. 2700,3600
#   LSD_EMU_REGS    print pc, gp, sp, ra every N vsyncs (default 0, off)
#   LSD_EMU_OUT     capture folder (default captures, ignored by git)
# Also: LSD_BIOS (default disks/bios.bin), LSD_DISC (default disks/SLPS-01556.cue), LSD_EMU_TIMEOUT (seconds, default 300).
set -euo pipefail
cd "$(dirname "$0")/../.."
emu=tools/src/pcsx-redux/AppRun
bios=${LSD_BIOS:-disks/bios.bin}
disc=${LSD_DISC:-disks/SLPS-01556.cue}
[ -x "$emu" ] || { echo "no emulator: run tools/setup.sh"; exit 1; }
[ -f "$bios" ] || { echo "no BIOS: link your own dump of a Japanese BIOS as $bios (see disks/README.md)"; exit 1; }
[ -f "$disc" ] || { echo "no disc: see disks/README.md"; exit 1; }
export LSD_EMU_OUT=${LSD_EMU_OUT:-captures}
mkdir -p "$LSD_EMU_OUT"
args=(-dofile tools/emu/probe.lua)
for s in "$@"; do args+=(-dofile "$s"); done
timeout "${LSD_EMU_TIMEOUT:-300}" nice -n 10 "$emu" -cli -stdout -lua_stdout -no-gui-logs \
  -bios "$bios" -iso "$disc" -run "${args[@]}"
for raw in "$LSD_EMU_OUT"/*.raw; do
  [ -e "$raw" ] || continue
  .venv/bin/python -I tools/emu/raw2png.py "$raw" && rm "$raw"
done
