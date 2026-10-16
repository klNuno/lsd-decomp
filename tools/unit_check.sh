#!/usr/bin/env bash
# Check one game unit on its own: it must assemble to the same bytes as the reference build.
#   tools/unit_check.sh --save              after a green `make check`: keep build/src/**/*.o as the reference
#   tools/unit_check.sh src/game/dream_sys.c build that unit alone (in a temp dir) and compare it
# Compares every section's bytes and the relocation list (offset, type and symbol) with the reference
# object, so renames and struct rewrites can be tested while other units are being edited.
# The final judge stays `make check` (sha1 of the linked executable).
set -euo pipefail
cd "$(dirname "$0")/.."
ref=build/ref
if [ "${1:-}" = "--save" ]; then
  rm -rf "$ref"; mkdir -p "$ref"
  (cd build && find src -name '*.c.o' -exec cp --parents {} ref/ \;)
  echo "reference saved: $(find "$ref" -name '*.c.o' | wc -l) objects"
  exit 0
fi
unit=${1:?usage: tools/unit_check.sh src/game/UNIT.c | --save}
[ -f "$unit" ] || { echo "no such unit: $unit"; exit 2; }
want="$ref/$unit.o"
[ -f "$want" ] || { echo "no reference for $unit: run tools/unit_check.sh --save after a green make check"; exit 2; }
tmp=$(mktemp -d /tmp/unitcheck.XXXXXX)
trap 'rm -rf "$tmp"' EXIT
make -s BUILD="$tmp" "$tmp/$unit.o" >"$tmp/build.log" 2>&1 || { cat "$tmp/build.log"; echo "UNIT BUILD FAILED: $unit"; exit 1; }
got="$tmp/$unit.o"
bad=0
secs=$(mipsel-linux-gnu-objdump -h "$want" | awk '$2 ~ /^\./ {print $2}')
for s in $secs; do
  mipsel-linux-gnu-objcopy -O binary -j "$s" "$want" "$tmp/want$s" 2>/dev/null || true
  mipsel-linux-gnu-objcopy -O binary -j "$s" "$got" "$tmp/got$s" 2>/dev/null || true
  if ! cmp -s "$tmp/want$s" "$tmp/got$s"; then echo "DIFF in section $s"; bad=1; fi
done
mipsel-linux-gnu-objdump -h "$want" | awk '$2 ~ /^\./ {print $2, $3}' > "$tmp/hw"
mipsel-linux-gnu-objdump -h "$got" | awk '$2 ~ /^\./ {print $2, $3}' > "$tmp/hg"
cmp -s "$tmp/hw" "$tmp/hg" || { echo "DIFF in section sizes:"; diff "$tmp/hw" "$tmp/hg" | head; bad=1; }
# offset, type and symbol: a unit worker may rename locals only, so a symbol name that differs
# from the reference means a function or global was renamed outside tools/rename.py.
rel() { mipsel-linux-gnu-objdump -r "$1" | awk '/^RELOCATION RECORDS/ {sec=$4} /^[0-9a-f]{8} / {print sec, $1, $2, $3}'; }
rel "$want" > "$tmp/rw"; rel "$got" > "$tmp/rg"
cmp -s "$tmp/rw" "$tmp/rg" || { echo "DIFF in relocations:"; diff "$tmp/rw" "$tmp/rg" | head; bad=1; }
if [ $bad = 0 ]; then echo "UNIT OK: $unit"; else echo "UNIT MISMATCH: $unit"; exit 1; fi
