#!/usr/bin/env bash
# Count the casts and the compiler warnings of the game C (with warnings on), per file and in total.
#   tools/castcount.sh [FILE.c ...]     default: every src/game/*.c
set -uo pipefail
cd "$(dirname "$0")/.."
files=("$@"); [ ${#files[@]} -gt 0 ] || files=(src/game/*.c)
CPPFLAGS="-Iinclude -undef -lang-c -nostdinc -Dmips -D__mips__ -D__mips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C"
tc=0; tw=0
for f in "${files[@]}"; do
  c=$(grep -oE '\((const )?(un)?signed( char| short| int| long)?\)|\((s|u)(8|16|32)\)|\((const )?[A-Za-z_][A-Za-z0-9_]*( [A-Za-z_][A-Za-z0-9_]*)? ?\*+\)' "$f" | wc -l || true)
  w=$(tools/gcc/2.6.3-psx/cpp $CPPFLAGS "$f" 2>/dev/null | tools/gcc/2.6.3-psx/cc1 -quiet -O2 -G8 -funsigned-char -o /dev/null 2>&1 | grep -c 'warning' || true)
  printf '%-28s casts %4d  warnings %4d\n' "$(basename "$f")" "$c" "$w"; tc=$((tc+c)); tw=$((tw+w))
done
echo "total casts $tc warnings $tw"
