# disks

Put your own dump of the game disc here. Git ignores everything in this folder except this file.

Expected names:

- `SLPS-01556.bin`: the raw MODE2/2352 image, or a link to it.
- `SLPS-01556.cue`: `FILE "SLPS-01556.bin" BINARY`, `TRACK 01 MODE2/2352`, `INDEX 01 00:00:00`.

Then `make check-disk` extracts the disc into `extract/` and checks that `SLPS_015.56` has the sha1 in `config/SLPS_015.56.sha1`.
