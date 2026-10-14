# lsd-decomp: matching decompilation of LSD: Dream Emulator (SLPS-01556).
# Phase 0: toolchain and disc. The split, the build and `make check` arrive in phase 1.

EXE     := SLPS_015.56
DISK    ?= disks/SLPS-01556.cue
EXTRACT := extract
TOOLS   := tools/bin

.PHONY: setup extract check-disk distclean

setup:
	tools/setup.sh

extract: $(EXTRACT)/$(EXE)

$(EXTRACT)/$(EXE):
	@test -f "$(DISK)" || { echo "no disc: put your own dump in disks/ (see disks/README.md)"; exit 1; }
	$(TOOLS)/dumpsxiso -x $(EXTRACT) -s $(EXTRACT)/layout.xml "$(DISK)"

# The executable must be the retail one, whatever patch touched the data files.
check-disk: extract
	@echo "$$(cat config/$(EXE).sha1)  $(EXTRACT)/$(EXE)" | sha1sum -c -

distclean:
	rm -rf $(EXTRACT) build
