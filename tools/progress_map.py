#!/usr/bin/env python3
"""Progress map: one rectangle per function of the executable, sized by its bytes.

  tools/progress_map.py [--output docs/progress]

Writes treemap.svg and progress.json. Run it after a green `make check`: it reads
build/lsd.map and build/lsd.elf, and refuses a build whose sha1 is not the original.

Every game function is matching C, so the map measures what is left to understand:
- address name: the function is still called func_8XXXXXXX;
- named: it has a name of ours, but its body still reads a field called unk_XX, a local or
  parameter named by m2c (arg0, temp_s0, var_v0, sp10), an Unk_ type or a D_ global;
- read: every name in its body is ours.
The 70 game files are labelled by name; the 40 Sony library units (PSY-Q, linked as asm, never
decompiled) are drawn apart.
"""
import argparse
import hashlib
import html
import json
import pathlib
import re
import subprocess

ROOT = pathlib.Path(__file__).resolve().parent.parent
LEVELS = [  # key, label, fill (one-hue ordinal ramp, validated on the dark surface)
    ("address", "Address name", "#2f6f43"),
    ("named", "Named, unknowns inside", "#3fa35a"),
    ("read", "Read: every name ours", "#8fe0a0"),
]
SONY = ("sony", "Sony library, linked as is", "#5c5b57")
SURFACE, INK, INK2, INK3 = "#1a1a19", "#f0efec", "#c3c2b7", "#8f8d84"
UNKNOWN = {
    "unk_fields": re.compile(r"(?:->|\.)\s*unk_?[0-9A-Fa-f]+\b"),
    "m2c_names": re.compile(r"\b(?:arg[0-9]+|temp_[a-z0-9_]+|var_[a-z0-9_]+|sp[0-9A-F]+)\b"),
    "unk_types": re.compile(r"\bUnk_[0-9A-F]{8}\w*"),
    "d_globals": re.compile(r"\bD_[0-9A-F]{8}\b"),
}


def sh(*cmd):
    return subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, check=True).stdout


def strip_comments(src):
    """Blank out comments and string literals, keeping offsets and newlines."""
    out = list(src)
    for m in re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', src, re.S):
        for i in range(m.start(), m.end()):
            if out[i] != "\n":
                out[i] = " "
    return "".join(out)


def c_functions(path):
    """Map function name -> body text (comments blanked) for every definition of a C unit.

    The declarator is the last line of the text before a top-level brace that starts in column 0,
    holds a parenthesis and does not end with a semicolon: K&R definitions (`f(a, b)` followed by
    `int a;` lines) are covered, prototypes, struct bodies and initializers are not taken."""
    code = strip_comments(path.read_text(encoding="utf-8", errors="surrogateescape"))
    funcs, depth, start, last, head = {}, 0, 0, 0, ""
    for i, ch in enumerate(code):
        if ch == "{":
            if depth == 0:
                head, start = code[last:i], i
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                tail = head.rstrip().split("\n")[-1]
                cands = [l for l in head.split("\n") if l[:1].strip() and "(" in l
                         and not l.rstrip().endswith(";") and "=" not in l.split("(")[0]]
                if cands and not re.search(r"\b(struct|union|enum)\b|=", tail):
                    m = re.search(r"(\w+)\s*\(", cands[-1])
                    if m:
                        funcs[m.group(1)] = code[start:i + 1]
                last = i + 1
    return funcs


def text_sections():
    """(address, size, object path) of every .text input section of the link."""
    secs = []
    for line in (ROOT / "build/lsd.map").read_text().splitlines():
        m = re.match(r"^ \.text\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+build/(\S+)\.o$", line)
        if m and int(m.group(2), 16) and m.group(1).startswith("80"):
            secs.append((int(m.group(1), 16), int(m.group(2), 16), m.group(3)))
    return secs


def symbols():
    syms = {}
    for line in sh("mipsel-linux-gnu-nm", "-n", "--defined-only", "build/lsd.elf").splitlines():
        a, t, name = line.split()[:3]
        # gcc2_compiled. and __gnu_compiled_c mark the start of each C object; .NON_MATCHING markers
        # come from splat's asm; neither is a function
        if t in "Tt" and "." not in name and not name.startswith("__gnu_compiled"):
            syms.setdefault(int(a, 16), name)
    return syms


def sony_libraries():
    """psyq/<addr> -> its libraries, from the comments of config/splat.yaml."""
    libs = {}
    for line in (ROOT / "config/splat.yaml").read_text().splitlines():
        m = re.search(r"asm, (psyq/[0-9A-F]{8})\]\s*#\s*([A-Z0-9 ,]+?)(?:\s+[A-Z][a-z]|\s*\(|,\s*near|$)", line)
        if m:
            libs[m.group(1)] = m.group(2).strip().split()[0].replace(",", ", ")
    return libs


def squarify(items, x, y, w, h):
    """Squarified treemap (Bruls, Huizing, van Wijk). items: [(weight, payload)], weights > 0."""
    items = sorted(items, key=lambda it: -it[0])
    total = sum(it[0] for it in items)
    out = []
    if not items or w <= 0 or h <= 0:
        return out
    scale = w * h / total
    rest = [(wt * scale, p) for wt, p in items]

    def worst(row, side):
        s = sum(r[0] for r in row)
        return max(max(side * side * r[0] / (s * s), s * s / (side * side * r[0])) for r in row)

    while rest:
        side = min(w, h)
        row = [rest.pop(0)]
        while rest and worst(row + [rest[0]], side) <= worst(row, side):
            row.append(rest.pop(0))
        s = sum(r[0] for r in row)
        if w >= h:  # lay the row as a column on the left
            cw = s / h
            cy = y
            for a, p in row:
                ch = a / cw
                out.append((x, cy, cw, ch, p))
                cy += ch
            x, w = x + cw, w - cw
        else:
            rh = s / w
            cx = x
            for a, p in row:
                cw2 = a / rh
                out.append((cx, y, cw2, rh, p))
                cx += cw2
            y, h = y + rh, h - rh
    return out


def subsystem(funcs):
    """Most common name prefix in a unit, weighted by bytes."""
    weight = {}
    for f in funcs:
        if f["level"] != "address" and "_" in f["name"]:
            p = f["name"].split("_")[0]
            if p and p[0].isupper():
                weight[p] = weight.get(p, 0) + f["bytes"]
    return max(weight, key=weight.get) if weight else ""


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--output", default="docs/progress")
    args = ap.parse_args()

    want = (ROOT / "config/SLPS_015.56.sha1").read_text().split()[0]
    got = hashlib.sha1((ROOT / "build/SLPS_015.56").read_bytes()).hexdigest()
    if got != want:
        raise SystemExit(f"build/SLPS_015.56 is not the original ({got}): run make check first")
    commit = sh("git", "rev-parse", "--short", "HEAD").strip()
    dirty = bool(sh("git", "status", "--porcelain", "--untracked-files=no", "src", "include", "config").strip())

    syms = symbols()
    addrs = sorted(syms)
    bodies = {}
    for p in sorted((ROOT / "src").rglob("*.c")):
        for name, body in c_functions(p).items():
            bodies[name] = (str(p.relative_to(ROOT)), body)
    cited = set(re.findall(r"\b[A-Za-z_]\w+\b", (ROOT / "docs/discoveries.md").read_text()))

    libs = sony_libraries()
    units = []
    for start, size, obj in text_sections():
        game = obj.startswith("src/")
        inside = [a for a in addrs if start <= a < start + size]
        funcs = []
        for k, a in enumerate(inside):
            end = inside[k + 1] if k + 1 < len(inside) else start + size
            name = syms[a]
            f = {"name": name, "address": f"0x{a:08X}", "bytes": end - a}
            if game:
                if name not in bodies:
                    raise SystemExit(f"{obj}: no C definition found for {name}")
                body = bodies[name][1]
                for key, rx in UNKNOWN.items():
                    f[key] = len(set(rx.findall(body)))
                unknowns = sum(f[key] for key in UNKNOWN)
                f["level"] = "address" if name.startswith("func_") else ("named" if unknowns else "read")
                f["in_findings"] = name in cited
            else:
                f["level"] = "sony"
            funcs.append(f)
        unit = {"unit": obj if game else obj.replace("asm/", "") + ".s", "game": game, "bytes": size,
                "functions": funcs}
        if game:
            unit["subsystem"] = subsystem(funcs)
        else:
            unit["libraries"] = libs.get(obj.replace("asm/", "").removesuffix(".s"), "")
        units.append(unit)

    game_units = [u for u in units if u["game"]]
    gfuncs = [f for u in game_units for f in u["functions"]]
    gbytes = sum(f["bytes"] for f in gfuncs)
    sony_bytes = sum(u["bytes"] for u in units if not u["game"])
    sony_funcs = sum(len(u["functions"]) for u in units if not u["game"])
    by_level = {k: {"functions": sum(1 for f in gfuncs if f["level"] == k),
                    "bytes": sum(f["bytes"] for f in gfuncs if f["level"] == k)} for k, _, _ in LEVELS}
    totals = {
        "game_functions": len(gfuncs), "game_bytes": gbytes, "game_bytes_in_c": gbytes,
        "levels": by_level,
        "unknowns": {k: sum(f[k] for f in gfuncs) for k in UNKNOWN},
        "functions_in_findings": sum(1 for f in gfuncs if f["in_findings"]),
        "sony_symbols": sony_funcs, "sony_bytes": sony_bytes,
    }
    report = {
        "schema_version": 1, "commit": commit, "tracked_tree_dirty": dirty, "exe_sha1": got,
        "metric": "Code bytes of each function (.text of the link map). Every game function is matching C; "
                  "the level says how much of its body still carries names we did not choose.",
        "totals": totals, "units": units,
    }
    out = ROOT / args.output
    out.mkdir(parents=True, exist_ok=True)
    (out / "progress.json").write_text(json.dumps(report, indent=1) + "\n")
    (out / "treemap.svg").write_text(svg(report))
    pct = 100 * by_level["read"]["bytes"] / gbytes
    print(f"{len(gfuncs)} game functions, {gbytes} bytes: read {by_level['read']['functions']} "
          f"({pct:.1f} % of bytes), named {by_level['named']['functions']}, address {by_level['address']['functions']}; "
          f"{sony_funcs} Sony symbols, {sony_bytes} bytes; written to {args.output}/")


def svg(r):
    W, H, top, pad = 1200, 800, 132, 28
    t = r["totals"]
    lv = t["levels"]
    g = t["game_bytes"]
    pct = lambda k: 100 * lv[k]["bytes"] / g
    fill = {k: c for k, _, c in LEVELS}
    fill["sony"] = SONY[2]
    e = html.escape
    parts = [
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H}" viewBox="0 0 {W} {H}" role="img">',
        "<title>LSD: Dream Emulator decompilation progress map</title>",
        "<desc>Rectangle area is code bytes. Every game function is matching C. Dark green: still named by "
        "address. Mid green: named, with unknown fields or locals inside. Light green: every name in its body "
        "is ours. Grey hatched: Sony library linked as is. Hover for details.</desc>",
        "<defs><pattern id=\"hatch\" width=\"6\" height=\"6\" patternUnits=\"userSpaceOnUse\" "
        f"patternTransform=\"rotate(45)\"><rect width=\"6\" height=\"6\" fill=\"{SONY[2]}\"/>"
        "<line x1=\"0\" y1=\"0\" x2=\"0\" y2=\"6\" stroke=\"#4a4946\" stroke-width=\"2\"/></pattern></defs>",
        f'<rect width="{W}" height="{H}" rx="16" fill="{SURFACE}"/>',
        '<g font-family="system-ui, -apple-system, Segoe UI, sans-serif">',
        f'<text x="{pad}" y="44" font-size="25" font-weight="700" fill="{INK}">LSD: Dream Emulator · decompilation</text>',
        f'<text x="{pad}" y="72" font-size="14" fill="{INK2}">Matching SLPS_015.56 verified · {e(r["commit"])}'
        f'{" + edits" if r["tracked_tree_dirty"] else ""} · {t["game_functions"]:,} game functions, '
        f'{g:,} code bytes, all in C</text>',
        f'<text x="{W - pad}" y="44" text-anchor="end" font-size="30" font-weight="700" fill="{INK}">'
        f'{pct("read"):.1f}% read</text>',
        f'<text x="{W - pad}" y="72" text-anchor="end" font-size="14" fill="{INK2}">100% of game code in matching C · '
        f'{lv["read"]["functions"]:,} of {t["game_functions"]:,} functions use only our names</text>',
    ]
    lx = pad
    legend = [(k, f"{lab} {pct(k):.1f}%", fill[k]) for k, lab, _ in LEVELS] + \
             [("sony", f"Sony library ({100 * t['sony_bytes'] / (g + t['sony_bytes']):.0f}% of the exe code), linked as is", "url(#hatch)")]
    for k, lab, c in legend:
        parts.append(f'<rect x="{lx}" y="92" width="12" height="12" rx="2" fill="{c}"/>')
        parts.append(f'<text x="{lx + 19}" y="103" font-size="14" fill="{INK}">{e(lab)}</text>')
        lx += 19 + 7.6 * len(lab) + 26
    bx, by, bw, bh = pad, top, W - 2 * pad, H - top - 60
    gw = bw * g / (g + t["sony_bytes"])
    placed = squarify([(u["bytes"], u) for u in r["units"] if u["game"]], bx, by, gw - 3, bh) + \
        squarify([(u["bytes"], u) for u in r["units"] if not u["game"]], bx + gw + 3, by, bw - gw - 3, bh)
    labels = []
    for ux, uy, uw, uh, u in placed:
        inner = [(f["bytes"], f) for f in u["functions"] if f["bytes"] > 0]
        if u["game"]:
            ulab = pathlib.Path(u["unit"]).name  # the source file, named by what it holds
        else:
            ulab = u["libraries"] or "Sony " + pathlib.Path(u["unit"]).stem
        for fx, fy, fw, fh, f in squarify(inner, ux, uy, uw, uh):
            c = "url(#hatch)" if f["level"] == "sony" else fill[f["level"]]
            tip = f'{f["name"]} · {f["address"]} · {f["bytes"]} bytes · {ulab}'
            if f["level"] != "sony":
                tip += (f' · {dict((k, l) for k, l, _ in LEVELS)[f["level"]]}'
                        f' · unknown fields {f["unk_fields"]}, m2c names {f["m2c_names"]},'
                        f' Unk_ types {f["unk_types"]}, D_ globals {f["d_globals"]}'
                        + (" · cited in docs/discoveries.md" if f["in_findings"] else ""))
            parts.append(f'<rect x="{fx:.2f}" y="{fy:.2f}" width="{fw:.2f}" height="{fh:.2f}" fill="{c}" '
                         f'stroke="{SURFACE}" stroke-width="0.6"><title>{e(tip)}</title></rect>')
        parts.append(f'<rect x="{ux:.2f}" y="{uy:.2f}" width="{uw:.2f}" height="{uh:.2f}" fill="none" '
                     f'stroke="{SURFACE}" stroke-width="2.5"><title>{e(u["unit"])}</title></rect>')
        # the longest label that fits: "file.c", then the file name without its suffix
        for lab in (ulab, pathlib.Path(ulab).stem if u["game"] else ""):
            if lab and uw > 7.2 * len(lab) + 18 and uh > 30:
                labels.append((ux, uy, lab))
                break
    for ux, uy, ulab in labels:
        tw = 7.2 * len(ulab) + 14
        parts.append(f'<rect x="{ux + 5:.2f}" y="{uy + 5:.2f}" width="{tw:.0f}" height="21" rx="4" '
                     f'fill="{SURFACE}" fill-opacity="0.82"/>')
        parts.append(f'<text x="{ux + 12:.2f}" y="{uy + 20:.2f}" font-size="12.5" fill="{INK}">{e(ulab)}</text>')
    u = t["unknowns"]
    parts.append(f'<text x="{pad}" y="{H - 34}" font-size="13" fill="{INK2}">Area = code bytes · hover for each '
                 f'function · left to name inside game code: {u["unk_fields"]} unknown fields, {u["m2c_names"]} '
                 f'm2c locals, {u["unk_types"]} Unk_ types, {u["d_globals"]} D_ globals (per function)</text>')
    parts.append(f'<text x="{pad}" y="{H - 15}" font-size="12" fill="{INK3}">Understanding, not matching: every '
                 f'game byte already rebuilds from C. A name of ours is backed by evidence in '
                 f'config/symbol_addrs.txt. Generated by tools/progress_map.py.</text>')
    parts.append("</g></svg>")
    return "\n".join(parts) + "\n"


if __name__ == "__main__":
    main()
