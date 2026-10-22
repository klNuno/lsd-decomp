#!/usr/bin/env python3
"""Check that every in-page or cross-file anchor link in docs/ (every .md, subfolders too) and README.md resolves.

Slugs follow GitHub: lowercase, drop every character that is not a letter, digit,
space, hyphen or underscore (emoji are dropped), spaces become hyphens, a repeated
slug gets -1, -2. Usage: python3 tools/linkcheck.py [repo root]. Exit 1 when a link is broken.
"""
import re
import sys
import unicodedata
from pathlib import Path

ROOT = Path(sys.argv[1] if len(sys.argv) > 1 else Path(__file__).resolve().parents[1])
LINK = re.compile(r"\]\(([^)\s]*#[^)\s]*)\)")
HEADING = re.compile(r"^(#{1,6})\s+(.*?)\s*#*\s*$")


def slug(text):
    text = re.sub(r"`([^`]*)`", r"\1", text)          # inline code keeps its text
    text = re.sub(r"\[([^\]]*)\]\([^)]*\)", r"\1", text)  # link text only
    out = []
    for ch in text.lower():
        cat = unicodedata.category(ch)
        if cat[0] in "LNM" or ch in "-_ ":
            out.append(ch)
    return "".join(out).replace(" ", "-")


def anchors(path):
    seen = {}
    result = set()
    fence = False
    for line in path.read_text(encoding="utf-8").splitlines():
        if line.startswith("```"):
            fence = not fence
            continue
        m = None if fence else HEADING.match(line)
        if not m:
            continue
        base = slug(m.group(2))
        n = seen.get(base, 0)
        result.add(base if n == 0 else f"{base}-{n}")
        seen[base] = n + 1
    return result


def main():
    files = sorted((ROOT / "docs").rglob("*.md")) + [ROOT / "README.md"]
    cache = {}
    total = broken = 0
    for f in files:
        for i, line in enumerate(f.read_text(encoding="utf-8").splitlines(), 1):
            for target in LINK.findall(line):
                if target.startswith(("http://", "https://")):
                    continue
                file_part, _, frag = target.partition("#")
                dest = (f.parent / file_part).resolve() if file_part else f
                total += 1
                if not dest.exists():
                    broken += 1
                    print(f"BROKEN {f.relative_to(ROOT)}:{i}: {target} (no file)")
                    continue
                if dest not in cache:
                    cache[dest] = anchors(dest)
                if frag not in cache[dest]:
                    broken += 1
                    print(f"BROKEN {f.relative_to(ROOT)}:{i}: {target}")
    print(f"{total} anchor links checked, {broken} broken")
    return 1 if broken else 0


if __name__ == "__main__":
    sys.exit(main())
