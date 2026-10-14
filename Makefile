# lsd-decomp: matching decompilation of LSD: Dream Emulator (SLPS-01556).
#   make             build build/SLPS_015.56 from src/ and asm/
#   make check       build, then compare its sha1 with the retail executable
#   make split       regenerate asm/ and linker/ (and missing src/ stubs) with splat
#   make check-disk  extract the disc and check the retail executable
#   make clean       remove build/; make distclean also removes extract/, asm/, linker/

SHELL       := /bin/bash
.SHELLFLAGS := -eo pipefail -c

EXE     := SLPS_015.56
DISK    ?= disks/SLPS-01556.cue
EXTRACT := extract
BUILD   := build
TOOLS   := tools/bin
PYTHON  := .venv/bin/python
SPLAT   := config/splat.yaml

# Compiler pair, fixed by the calibration batch (see .agents/ARCHITECTURE.md).
GCC_VER   ?= 2.6.3-psx
ASPSX_VER ?= 2.34
CPP       := tools/gcc/$(GCC_VER)/cpp
CC1       := tools/gcc/$(GCC_VER)/cc1
MASPSX    := $(PYTHON) tools/src/maspsx/maspsx.py
CROSS     := mipsel-linux-gnu-
AS        := $(CROSS)as
LD        := $(CROSS)ld
OBJCOPY   := $(CROSS)objcopy

CPPFLAGS    := -Iinclude -undef -lang-c -nostdinc -Dmips -D__mips__ -D__mips -D__GNUC__=2 -D__OPTIMIZE__ \
               -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C
CFLAGS      := -quiet -O2 -G0 -funsigned-char -w $(CFLAGS_EXTRA)
MASPSXFLAGS := --aspsx-version=$(ASPSX_VER) --expand-div $(MASPSX_EXTRA)
ASFLAGS     := -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0
LDFLAGS     := -nostdlib --no-check-sections -T linker/lsd.ld -T linker/undefined_syms_auto.txt \
               -T linker/undefined_funcs_auto.txt -Map $(BUILD)/lsd.map

C_SRCS  := $(shell find src -name '*.c' 2>/dev/null)
S_SRCS  := $(shell find asm -name '*.s' -not -path 'asm/nonmatchings/*' -not -path 'asm/matchings/*' 2>/dev/null)
OBJS    := $(C_SRCS:%=$(BUILD)/%.o) $(S_SRCS:%=$(BUILD)/%.o)
ELF     := $(BUILD)/lsd.elf
TARGET  := $(BUILD)/$(EXE)

.PHONY: all check split extract check-disk clean distclean
.DELETE_ON_ERROR:

all: $(TARGET)

check: $(TARGET)
	@echo "$$(cat config/$(EXE).sha1)  $(TARGET)" | sha1sum -c -

$(TARGET): $(ELF)
	$(OBJCOPY) -O binary $< $@
	truncate -s %2048 $@

$(OBJS): Makefile

$(ELF): $(OBJS) linker/lsd.ld
	$(LD) $(LDFLAGS) -o $@

$(BUILD)/%.c.o: %.c
	@mkdir -p $(@D)
	$(CPP) $(CPPFLAGS) $< | $(CC1) $(CFLAGS) | $(MASPSX) $(MASPSXFLAGS) | $(AS) $(ASFLAGS) -o $@

# splat writes the game's Shift-JIS strings as UTF-8: encode them back before assembling.
$(BUILD)/asm/%.s.o: asm/%.s
	@mkdir -p $(@D)
	$(PYTHON) -I tools/sjis.py $< | $(AS) $(ASFLAGS) -o $@

split linker/lsd.ld: $(SPLAT) $(wildcard config/symbol_addrs*.txt) | $(EXTRACT)/$(EXE)
	rm -rf asm linker
	$(PYTHON) -m splat split $(SPLAT)

extract: $(EXTRACT)/$(EXE)

$(EXTRACT)/$(EXE):
	@test -f "$(DISK)" || { echo "no disc: put your own dump in disks/ (see disks/README.md)"; exit 1; }
	$(TOOLS)/dumpsxiso -x $(EXTRACT) -s $(EXTRACT)/layout.xml "$(DISK)"

# The executable must be the retail one, whatever patch touched the data files.
check-disk: extract
	@echo "$$(cat config/$(EXE).sha1)  $(EXTRACT)/$(EXE)" | sha1sum -c -

clean:
	rm -rf $(BUILD)

# Used by tools/fmatch.py so that one function is built exactly like the game.
print-%:
	@echo '$($*)'

distclean: clean
	rm -rf $(EXTRACT) asm linker
