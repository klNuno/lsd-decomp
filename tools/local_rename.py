#!/usr/bin/env python3
"""Rename parameters and locals of one function, with evidence.

    tools/local_rename.py LOCALS.tsv [--dry-run]

LOCALS.tsv: one rename per line, tab separated: FILE, FUNCTION, OLD, NEW, evidence (more columns are
ignored). Blank lines and lines starting with # are skipped. FILE may be a bare name (pad.c); it is
looked up under src/.

Each rename rewrites OLD as a whole word inside the definition of FUNCTION only: its parameter list,
its K&R declarations and its body, comments included, but never a member access (`->OLD`, `.OLD`):
a field may share the name. It refuses a rename when FUNCTION is not defined once in FILE, when OLD
does not appear in it, or when NEW is already a word of it outside member accesses (a local, a
global, a call). Local names never change the code, so after it: tools/unit_check.sh on every file
touched, then make check.
"""
import argparse
import pathlib
import re
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")


def function_span(text, func):
    """(start, end) of FUNCTION's definition: from its declarator line to its closing brace."""
    spans = []
    for m in re.finditer(r"^[A-Za-z_][^;{}\n]*\b" + re.escape(func) + r"\s*\(", text, re.M):
        i = text.find("{", m.end())
        head = text[m.end():i]
        if i < 0 or re.search(r";\s*$", head.split("\n")[0]) or ";" in head.split(")")[0]:
            continue  # a prototype, not a definition
        depth, j = 0, i
        while j < len(text):
            if text[j] == "{":
                depth += 1
            elif text[j] == "}":
                depth -= 1
                if depth == 0:
                    spans.append((m.start(), j + 1))
                    break
            j += 1
    return spans


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("tsv")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()
    rows = []
    for n, line in enumerate(pathlib.Path(args.tsv).read_text().splitlines(), 1):
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        cols = [c.strip() for c in line.split("\t")]
        if len(cols) < 5 or not cols[4]:
            sys.exit(f"{args.tsv}:{n}: need FILE FUNCTION OLD NEW evidence (tabs)")
        f, func, old, new = cols[:4]
        if not all(IDENT.match(x) for x in (func, old, new)):
            sys.exit(f"{args.tsv}:{n}: not an identifier")
        path = ROOT / f if "/" in f else next(iter(sorted((ROOT / "src").rglob(f))), None)
        if path is None or not path.exists():
            sys.exit(f"{args.tsv}:{n}: no file {f}")
        rows.append((n, path, func, old, new))

    texts, touched, done = {}, set(), 0
    for n, path, func, old, new in rows:
        text = texts.setdefault(path, path.read_text(encoding="utf-8", errors="surrogateescape"))
        spans = function_span(text, func)
        if len(spans) != 1:
            sys.exit(f"{args.tsv}:{n}: {func} defined {len(spans)} times in {path.relative_to(ROOT)}")
        a, b = spans[0]
        body = text[a:b]
        word = lambda w: re.compile(r"(?<!->)(?<!\.)(?<![\w])" + re.escape(w) + r"\b")  # not a member access
        if not word(old).search(body):
            sys.exit(f"{args.tsv}:{n}: {old} does not appear in {func}")
        if word(new).search(body):
            sys.exit(f"{args.tsv}:{n}: {new} is already used in {func}")
        texts[path] = text[:a] + word(old).sub(new, body) + text[b:]
        touched.add(path)
        done += 1
    if not args.dry_run:
        for path in touched:
            path.write_text(texts[path], encoding="utf-8", errors="surrogateescape")
    print(f"{done} renames in {len(touched)} files" + (" (dry run, nothing written)" if args.dry_run else
          "; now tools/unit_check.sh on: " + " ".join(str(p.relative_to(ROOT)) for p in sorted(touched))))


if __name__ == "__main__":
    main()
