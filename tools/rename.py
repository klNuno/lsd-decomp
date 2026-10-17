#!/usr/bin/env python3
"""Rename game symbols with evidence, everywhere at once.

    tools/rename.py NAMES.tsv [--dry-run]

NAMES.tsv holds one rename per line, tab separated: OLD, NEW, evidence. Blank lines and lines
starting with # are skipped. OLD is a splat name (func_8005B03C, D_8008AC70) or one of our own
names; NEW follows docs/naming.md (Subsystem_VerbNoun for functions, g_name for globals).

What it does:
- rewrites OLD as a whole word in src/, include/, docs/ (every .md) and config/name_levels.tsv;
- in config/symbol_addrs.txt, replaces OLD's line (keeping its attributes) or adds
  `NEW = 0xADDR; // type:func size:0xNN // evidence` under the names block, with the address and
  size read from build/lsd.elf;
- refuses a NEW already in use, an OLD it cannot place, or a name that is not a C identifier.

Then run `make split && make check`: asm/ and the data tables are regenerated from the symbol files.
"""
import argparse
import pathlib
import re
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
SYMS = ROOT / "config" / "symbol_addrs.txt"
OTHER_SYMS = [ROOT / "config" / "symbol_addrs.psyq.txt"]
ELF = ROOT / "build" / "lsd.elf"
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
SPLAT_NAME = re.compile(r"^(?:func|D)_([0-9A-F]{8})$")
NAMES_HEADER = "// Names with evidence"


def text_files():
    for sub in ("src", "include"):
        for p in (ROOT / sub).rglob("*"):
            if p.suffix in (".c", ".h", ".inc") and p.is_file():
                yield p
    for p in (ROOT / "docs").rglob("*.md"):
        yield p
    if (ROOT / "config" / "name_levels.tsv").exists():
        yield ROOT / "config" / "name_levels.tsv"  # the audit levels follow the rename


def elf_symbols():
    out = subprocess.run(["mipsel-linux-gnu-nm", "-S", str(ELF)], capture_output=True, text=True, check=True).stdout
    syms = {}
    for line in out.splitlines():
        parts = line.split()
        if len(parts) == 4:
            addr, size, kind, name = parts
            syms[name] = (int(addr, 16), int(size, 16), kind)
        elif len(parts) == 3:
            addr, kind, name = parts
            syms[name] = (int(addr, 16), None, kind)
    return syms


def declared_names():
    names = set()
    for f in [SYMS, *OTHER_SYMS]:
        for line in f.read_text().splitlines():
            m = re.match(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=", line)
            if m:
                names.add(m.group(1))
    return names


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("names")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    renames = []
    for n, line in enumerate(pathlib.Path(args.names).read_text().splitlines(), 1):
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        cols = line.split("\t")
        if len(cols) < 3 or not cols[2].strip():
            sys.exit(f"{args.names}:{n}: need OLD<TAB>NEW<TAB>evidence")
        old, new, ev = cols[0].strip(), cols[1].strip(), cols[2].strip()
        # splat reads every "word:value" token of a symbol comment as an attribute
        ev = re.sub(r":\s*", " - ", ev).replace(";", ",")
        if not IDENT.match(old) or not IDENT.match(new):
            sys.exit(f"{args.names}:{n}: not a C identifier: {old!r} or {new!r}")
        renames.append((old, new, ev))

    olds = [r[0] for r in renames]
    news = [r[1] for r in renames]
    for dup in {x for x in news if news.count(x) > 1} | {x for x in olds if olds.count(x) > 1}:
        sys.exit(f"listed twice: {dup}")

    syms = elf_symbols()
    declared = declared_names()
    sym_text = SYMS.read_text()
    sym_lines = sym_text.splitlines()
    errors = []
    for old, new, _ in renames:
        if new in syms or new in declared:
            errors.append(f"{new}: already in use")
        if old not in syms and not SPLAT_NAME.match(old):
            errors.append(f"{old}: not in build/lsd.elf (run make first)")
    if errors:
        sys.exit("\n".join(errors))

    # symbol_addrs.txt
    added = []
    for old, new, ev in renames:
        pat = re.compile(rf"^(\s*){re.escape(old)}(\s*=.*)$")
        hit = [i for i, l in enumerate(sym_lines) if pat.match(l)]
        if hit:
            for i in hit:
                line = pat.sub(rf"\g<1>{new}\g<2>", sym_lines[i])
                if ev not in line:
                    line += f" // {ev}"
                sym_lines[i] = line
            continue
        if old in syms:
            addr, size, kind = syms[old]
        else:
            addr, size, kind = int(SPLAT_NAME.match(old).group(1), 16), None, "?"
        attrs = []
        # nm marks labels inside asm .data as "t" too: only a func_ (or a C function) is code
        if old.startswith("func_") or (kind in ("T", "t") and not old.startswith("D_")):
            attrs.append("type:func")
            if size:
                attrs.append(f"size:0x{size:X}")
        added.append(f"{new} = 0x{addr:08X}; // {' '.join(attrs) + ' // ' if attrs else ''}{ev}")
    if added:
        at = next((i for i, l in enumerate(sym_lines) if l.startswith(NAMES_HEADER)), None)
        if at is None:
            sym_lines += ["", NAMES_HEADER + " (tools/rename.py).", *added]
        else:
            end = at + 1
            while end < len(sym_lines) and sym_lines[end].strip() and not sym_lines[end].startswith("//"):
                end += 1
            sym_lines[end:end] = added

    # source and docs
    word = re.compile(r"\b(" + "|".join(re.escape(o) for o in olds) + r")\b")
    table = dict((o, n) for o, n, _ in renames)
    changed = {}
    for p in text_files():
        s = p.read_text(errors="surrogateescape")
        t = word.sub(lambda m: table[m.group(1)], s)
        if t != s:
            changed[p] = t
    print(f"{len(renames)} renames, {len(changed)} files, {len(added)} new symbol lines")
    if args.dry_run:
        for p in sorted(changed):
            print("  would edit", p.relative_to(ROOT))
        return
    for p, t in changed.items():
        p.write_text(t, errors="surrogateescape")
    SYMS.write_text("\n".join(sym_lines) + "\n")
    print("now run: make split && make check")


if __name__ == "__main__":
    main()
