# disks

Put your own dump of the game disc here. Git ignores everything in this folder except this file.

Expected names:

- `SLPS-01556.bin`: the raw MODE2/2352 image, or a link to it.
- `SLPS-01556.cue`: `FILE "SLPS-01556.bin" BINARY`, `TRACK 01 MODE2/2352`, `INDEX 01 00:00:00`.

For in-game checks, also link your own dump of a Japanese BIOS (SCPH-7000 or similar) as `bios.bin`; `tools/emu/run.sh` boots the disc with it.

Then `make check-disk` extracts the disc into `extract/` and checks that `SLPS_015.56` has the sha1 in `config/SLPS_015.56.sha1`.
