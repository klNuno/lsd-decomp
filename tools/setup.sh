#!/usr/bin/env bash
# Install the pinned decomp toolchain into tools/ and .venv/. Safe to re-run.
#   tools/setup.sh          install, verified against tools/toolchain.sha256 and tools/requirements.lock
#   tools/setup.sh --lock   rewrite both lock files first (only when bumping tools/versions.env)
set -euo pipefail
cd "$(dirname "$0")/.."
T=tools
LOCK=0
if [ "${1:-}" = "--lock" ]; then LOCK=1; fi
# shellcheck source=versions.env
. "$T/versions.env"
mkdir -p "$T/dl" "$T/bin" "$T/src" "$T/gcc"

gh_asset() { # owner/repo tag asset
  local f="$T/dl/$3"
  if [ ! -f "$f" ]; then
    curl -fsSL --retry 3 -o "$f.part" "https://github.com/$1/releases/download/$2/$3"
    mv "$f.part" "$f"
  fi
}

git_pin() { # url rev name
  local d="$T/src/$3"
  if [ ! -d "$d/.git" ]; then git clone -q "$1" "$d"; fi
  if ! git -C "$d" cat-file -e "$2^{commit}" 2>/dev/null; then git -C "$d" fetch -q origin; fi
  git -C "$d" -c advice.detachedHead=false checkout -q "$2"
}

command -v mipsel-linux-gnu-as >/dev/null || { echo "missing binutils: apt install binutils-mipsel-linux-gnu"; exit 1; }

# Release binaries, checked by sha256
MKPSXISO_ZIP="mkpsxiso-${MKPSXISO_TAG#v}-Linux.zip"
for v in $OLD_GCC_VERSIONS; do gh_asset decompals/old-gcc "$OLD_GCC_TAG" "gcc-$v.tar.gz"; done
gh_asset Lameguy64/mkpsxiso "$MKPSXISO_TAG" "$MKPSXISO_ZIP"
gh_asset encounter/objdiff "$OBJDIFF_TAG" objdiff-cli-linux-x86_64
# PCSX-Redux only ships rolling dev builds; an old one can vanish from distrib.app.
PCSX_ZIP="PCSX-Redux-$PCSX_REDUX_REV-linux-x86_64.zip"
if [ ! -f "$T/dl/$PCSX_ZIP" ]; then
  curl -fsSL --retry 3 -o "$T/dl/$PCSX_ZIP.part" "https://distrib.app$PCSX_REDUX_ASSET" \
    || { rm -f "$T/dl/$PCSX_ZIP.part"; echo "$PCSX_ZIP is gone from distrib.app: put a saved copy in $T/dl/"; exit 1; }
  mv "$T/dl/$PCSX_ZIP.part" "$T/dl/$PCSX_ZIP"
fi
if [ $LOCK = 1 ]; then sha256sum "$T"/dl/* > "$T/toolchain.sha256"; fi
sha256sum -c --quiet "$T/toolchain.sha256"

for v in $OLD_GCC_VERSIONS; do
  d="$T/gcc/$v"
  if [ ! -x "$d/cc1" ]; then mkdir -p "$d"; tar -xzf "$T/dl/gcc-$v.tar.gz" -C "$d"; fi
done
if [ ! -x "$T/bin/dumpsxiso" ]; then
  python3 -c 'import sys, zipfile; zipfile.ZipFile(sys.argv[1]).extractall(sys.argv[2])' "$T/dl/$MKPSXISO_ZIP" "$T/src"
  mk="$T/src/${MKPSXISO_ZIP%.zip}/bin"
  install -m 755 "$mk/dumpsxiso" "$mk/mkpsxiso" "$T/bin/"
fi
install -m 755 "$T/dl/objdiff-cli-linux-x86_64" "$T/bin/objdiff-cli"
if [ ! -x "$T/src/pcsx-redux/AppRun" ]; then
  # No FUSE in containers: unpack the AppImage instead of mounting it.
  tmp=$(mktemp -d)
  python3 -c 'import sys, zipfile; zipfile.ZipFile(sys.argv[1]).extractall(sys.argv[2])' "$T/dl/$PCSX_ZIP" "$tmp"
  chmod +x "$tmp"/*.AppImage
  (cd "$tmp" && ./*.AppImage --appimage-extract >/dev/null)
  rm -rf "$T/src/pcsx-redux"
  mv "$tmp/squashfs-root" "$T/src/pcsx-redux"
  rm -rf "$tmp"
fi

# Source tools, pinned by commit
git_pin https://github.com/mkst/maspsx "$MASPSX_REV" maspsx
git_pin https://github.com/matt-kempster/m2c "$M2C_REV" m2c
git_pin https://github.com/simonlindholm/decomp-permuter "$PERMUTER_REV" decomp-permuter
git_pin https://github.com/simonlindholm/asm-differ "$ASM_DIFFER_REV" asm-differ
git_pin https://github.com/lab313ru/psx_psyq_signatures "$PSYQ_SIGNATURES_REV" psx_psyq_signatures

if [ ! -x "$T/bin/mipsmatch" ]; then
  cargo install -q --locked --git https://github.com/ttkb-oss/mipsmatch --rev "$MIPSMATCH_REV" --root "$T/mipsmatch" --jobs 3
  ln -sf ../mipsmatch/bin/mipsmatch "$T/bin/mipsmatch"
fi

# Python: splat and the helpers of m2c, permuter and asm-differ
if [ ! -x .venv/bin/python ]; then python3 -m venv .venv; fi
if [ $LOCK = 1 ]; then
  .venv/bin/pip install -q -r "$T/requirements.in"
  .venv/bin/pip freeze > "$T/requirements.lock"
fi
.venv/bin/pip install -q -r "$T/requirements.lock"

echo "== toolchain"
mipsel-linux-gnu-as --version | head -1
for v in $OLD_GCC_VERSIONS; do printf '%s: ' "$v"; echo 'int f(void){return 0;}' | "$T/gcc/$v/cc1" -quiet -version -o /dev/null 2>&1 | head -1; done
"$T/bin/objdiff-cli" --version
"$T/bin/mipsmatch" --version 2>/dev/null || echo "mipsmatch $MIPSMATCH_REV"
printf 'pcsx-redux: '; "$T/src/pcsx-redux/AppRun" -cli -version | grep -m1 '"version"'
.venv/bin/python -c 'import importlib.metadata as m; print("splat64", m.version("splat64"), "spimdisasm", m.version("spimdisasm"))'
echo "setup ok"
