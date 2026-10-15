#!/usr/bin/env python3
"""Match one function in isolation, built exactly like the game (flags come from the Makefile).

  tools/fmatch.py diff FUNC FILE.c [--gcc 2.7.2-psx] [--aspsx 2.56] [--cflags "-G8"] [--maspsx "-G8"] [--all]
      Compile FILE.c, compare FUNC with the original asm through objdiff-cli.
      Prints "MATCH func 100%" (exit 0) or the percent and the differing rows (exit 1).
      A compile error prints the compiler output (exit 2).
  tools/fmatch.py m2c FUNC     first-pass C from m2c, with include/ as context
  tools/fmatch.py asm FUNC     path of the original asm
  tools/fmatch.py decls FUNC   the declarations of FUNC's unit that FUNC needs: those naming a symbol
                               its asm uses, prototypes of unit functions it calls, the types they use

Run from anywhere; work files go to build/fmatch/<FUNC>/. A 100 % here is necessary, not
sufficient: only `make check` on the whole executable decides.
"""
import argparse
import glob
import json
import re
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = os.path.join(ROOT, ".venv/bin/python")


def run(cmd, **kw):
    return subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, **kw)


def make_var(name, overrides):
    r = run(["make", "-s", "--no-print-directory", f"print-{name}", *overrides])
    if r.returncode:
        sys.exit(f"make print-{name} failed: {r.stderr}")
    return r.stdout.strip()


def find_asm(func):
    hits = sorted(glob.glob(f"{ROOT}/asm/nonmatchings/**/{func}.s", recursive=True))
    if not hits:
        sys.exit(f"no asm for {func} under asm/nonmatchings/ (run make split?)")
    return os.path.relpath(hits[0], ROOT)


def rodata_includes(asm):
    """The INCLUDE_RODATA files (asm/nonmatchings/**/D_x.s) that the function references, so the
    target object holds the strings and constants and objdiff can compare their bytes."""
    text = open(os.path.join(ROOT, asm), encoding="utf-8").read()
    out = []
    for name in sorted(set(re.findall(r"%(?:hi|lo)\((D_[0-9A-F]{8})\)", text))):
        hits = glob.glob(f"{ROOT}/asm/nonmatchings/**/{name}.s", recursive=True)
        if hits:
            out.append(os.path.relpath(hits[0], ROOT))
    return out


def build_target(func, work, overrides):
    src = os.path.join(work, "target.s")
    asm_path = find_asm(func)
    with open(src, "w", encoding="utf-8") as f:
        f.write('.include "include/macro.inc"\n')
        for r in rodata_includes(asm_path):
            f.write(f'.include "{r}"\n')
        f.write('.section .text\n')
        f.write(f'.include "{asm_path}"\n')
    obj = os.path.join(work, "target.o")
    asm = make_var("AS", overrides) + " " + make_var("ASFLAGS", overrides)
    r = run(["bash", "-o", "pipefail", "-c", f"{PY} -I tools/sjis.py {src} | {PY} -I tools/sjis.py - | {asm} -o {obj}"])
    if r.returncode:
        sys.exit(f"target asm failed:\n{r.stderr}")
    return obj


def build_base(cfile, work, overrides):
    v = {n: make_var(n, overrides) for n in ("CPP", "CPPFLAGS", "CC1", "CFLAGS", "MASPSX", "MASPSXFLAGS", "AS", "ASFLAGS")}
    obj = os.path.join(work, "base.o")
    cfile = os.path.abspath(cfile)
    pipe = (f"{v['CPP']} {v['CPPFLAGS']} {cfile} | {v['CC1']} {v['CFLAGS']} | "
            f"{v['MASPSX']} {v['MASPSXFLAGS']} | {PY} -I tools/sjis.py - | {v['AS']} {v['ASFLAGS']} -o {obj}")
    r = run(["bash", "-o", "pipefail", "-c", pipe])
    if r.returncode:
        print(f"COMPILE ERROR\n{r.stderr.strip()}")
        sys.exit(2)
    return obj


def section_bytes(obj, work, overrides, name):
    out = os.path.join(work, os.path.basename(obj) + ".rodata.bin")
    r = run([make_var("OBJCOPY", overrides), "-O", "binary", "--only-section=.rodata", obj, out])
    if r.returncode:
        sys.exit(f"objcopy failed: {r.stderr}")
    return open(out, "rb").read()


def rodata_diff(t, b, work, overrides):
    """None when both objects carry the same .rodata bytes: the strings and constants the function
    references (INCLUDE_RODATA files of the target) and its jump tables (whose words hold .text
    offsets, so they agree only if the code layout does). Else a short description."""
    tb, bb = section_bytes(t, work, overrides, "target"), section_bytes(b, work, overrides, "base")
    # splat files end with .align 2, cc1 leaves the padding to whatever follows: pad both to 4.
    tb, bb = (x + bytes(-len(x) % 4) for x in (tb, bb))
    if tb == bb:
        return None
    # A splat D_x.s can keep the zero pad word after its enddlabel (func_8004FBE4, func_80049684):
    # a longer side that only adds zero bytes past the shorter one is alignment, not data.
    short, long_ = sorted((tb, bb), key=len)
    if long_.startswith(short) and len(long_) - len(short) <= 12 and not any(long_[len(short):]):
        return None
    if len(tb) != len(bb):
        return f"target {len(tb)} bytes, yours {len(bb)} bytes"
    i = next(i for i in range(len(tb)) if tb[i] != bb[i])
    return f"first difference at .rodata+0x{i:X}: target {tb[i:i + 8].hex()} yours {bb[i:i + 8].hex()}"


def text(row):
    ins = row.get("instruction")
    return ins.get("formatted", "").strip() if ins else ""


def cmd_diff(a):
    overrides = []
    if a.gcc:
        overrides.append(f"GCC_VER={a.gcc}")
    if a.aspsx:
        overrides.append(f"ASPSX_VER={a.aspsx}")
    if a.cflags:
        overrides.append(f"CFLAGS_EXTRA={a.cflags}")
    if a.maspsx:
        overrides.append(f"MASPSX_EXTRA={a.maspsx}")
    work = os.path.join(ROOT, "build/fmatch", a.func)
    os.makedirs(work, exist_ok=True)
    t = build_target(a.func, work, overrides)
    b = build_base(a.cfile, work, overrides)
    out = os.path.join(work, "diff.json")
    # data_value lets D_8001176C in the target and .rodata+off in yours pair up; it does not check
    # the bytes (tested), so rodata_diff() below compares the .rodata sections themselves.
    r = run([f"{ROOT}/tools/bin/objdiff-cli", "diff", "-1", t, "-2", b, a.func, "--format", "json", "-o", out,
             "-c", "functionRelocDiffs=data_value"])
    if r.returncode:
        sys.exit(f"objdiff failed: {r.stderr}")
    d = json.load(open(out))
    left = next((s for s in d["left"]["symbols"] if s["name"] == a.func), None)
    right = next((s for s in d.get("right", {}).get("symbols", []) if s["name"] == a.func), None)
    if right is None:
        print(f"NO FUNCTION {a.func} in {a.cfile}")
        sys.exit(2)
    pct = left.get("match_percent", 0.0)
    lrows, rrows = left.get("instructions", []), right.get("instructions", [])
    if pct >= 100.0 and len(lrows) == len(rrows):
        bad = rodata_diff(t, b, work, overrides)
        if bad:
            print(f"{a.func} code 100%, RODATA MISMATCH: {bad}")
            return 1
        print(f"MATCH {a.func} 100%")
        return 0
    print(f"{a.func} {pct:.2f}%  (target {left.get('size')} bytes, yours {right.get('size')} bytes)")
    marks = {"DIFF_NONE": " ", "DIFF_REPLACE": "|", "DIFF_DELETE": "<", "DIFF_INSERT": ">",
             "DIFF_OP_MISMATCH": "|", "DIFF_ARG_MISMATCH": "~"}
    rows = []
    for i in range(max(len(lrows), len(rrows))):
        lr = lrows[i] if i < len(lrows) else {}
        rr = rrows[i] if i < len(rrows) else {}
        kind = lr.get("diff_kind") or rr.get("diff_kind") or "DIFF_NONE"
        rows.append((marks.get(kind, "?"), text(lr), text(rr)))
    show = set(range(len(rows))) if a.all else {
        j for i, r in enumerate(rows) if r[0] != " " for j in range(i - 2, i + 3) if 0 <= j < len(rows)}
    print(f"{'':1} {'target':<40} {'yours':<40}")
    last = -1
    for i in sorted(show):
        if i != last + 1:
            print("  ...")
        m, lt, rt = rows[i]
        print(f"{m} {lt:<40} {rt:<40}")
        last = i
    return 1


def cmd_m2c(a):
    asm = find_asm(a.func)
    ctx = os.path.join(ROOT, "build/fmatch", a.func, "ctx.c")
    os.makedirs(os.path.dirname(ctx), exist_ok=True)
    r = run(["bash", "-o", "pipefail", "-c",
             f"cpp -P -undef -D__GNUC__=2 -DM2CTX -Iinclude include/common.h > {ctx}"])
    if r.returncode:
        sys.exit(f"context failed: {r.stderr}")
    r = run([PY, "tools/src/m2c/m2c.py", "-t", "mipsel-gcc-c", "--context", ctx, asm])
    print(r.stdout, end="")
    print(r.stderr, end="", file=sys.stderr)
    return r.returncode


def unit_items(text):
    """(declarations, function prototypes) of a unit: top-level items and the head of each definition."""
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    import integrate
    decls, protos, buf, depth = [], {}, [], 0
    for line in text.splitlines():
        if not buf and (not line.strip() or line.startswith(("#include", "INCLUDE_ASM", "INCLUDE_RODATA"))):
            continue
        buf.append(line)
        code = integrate.code_of(line)
        depth += code.count("{") - code.count("}")
        if depth == 0 and (code.endswith((";", "}")) or not code.strip()):
            item = "\n".join(buf)
            buf = []
            if integrate.is_function_start(item) and not item.rstrip().endswith(";"):
                head = re.sub(r"\s+", " ", item.split("{", 1)[0]).strip()
                m = re.search(r"(\w+)\s*\(", head)
                if m:
                    protos[m.group(1)] = head + ";"
            else:
                decls.append(item)
    return decls, protos


def cmd_decls(a):
    asm = find_asm(a.func)
    unit = asm.split("/")[-2]
    path = os.path.join(ROOT, "src/game", unit + ".c")
    names = set(re.findall(r"\b((?:func|D|jtbl)_[0-9A-F]{8})\b", open(os.path.join(ROOT, asm), encoding="utf-8").read()))
    names.add(a.func)
    decls, protos = unit_items(open(path, encoding="utf-8").read())
    words = lambda t: set(re.findall(r"\b\w+\b", t))
    picked = [d for d in decls if words(d) & names]
    picked += [protos[n] for n in sorted(names) if n in protos and n != a.func]
    # Close over the types they use: a struct, union or typedef defined in the unit.
    typedefs = {}
    for d in decls:
        code = " ".join(d.split())
        m = re.search(r"\}\s*(\w+)\s*;$", code) if code.startswith("typedef") and "{" in code else None
        m = m or re.match(r"(?:typedef\s+)?(?:struct|union|enum)\s+(\w+)\s*\{", code)
        m = m or re.match(r"typedef\s+[^;{]*?\b(\w+)\s*;$", code)
        if m:
            typedefs.setdefault(m.group(1), []).append(d)
    seen, todo, types = set(), list(picked), []
    while todo:
        for w in words(todo.pop()):
            if w in typedefs and w not in seen:
                seen.add(w)
                for d in typedefs[w]:
                    types.append(d)
                    todo.append(d)
    out, done = [], set()
    for d in [d for d in decls if d in types] + picked:
        if d not in done:
            done.add(d)
            out.append(d)
    print(f"/* src/game/{unit}.c: {len(out)} of {len(decls)} declarations, in unit order (types first) */")
    print("\n".join(out))


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd", required=True)
    d = sub.add_parser("diff")
    d.add_argument("func")
    d.add_argument("cfile")
    d.add_argument("--gcc")
    d.add_argument("--aspsx")
    d.add_argument("--cflags")
    d.add_argument("--maspsx")
    d.add_argument("--all", action="store_true")
    m = sub.add_parser("m2c")
    m.add_argument("func")
    s = sub.add_parser("asm")
    s.add_argument("func")
    c = sub.add_parser("decls")
    c.add_argument("func")
    a = p.parse_args()
    if a.cmd == "decls":
        sys.exit(cmd_decls(a))
    if a.cmd == "diff":
        sys.exit(cmd_diff(a))
    if a.cmd == "m2c":
        sys.exit(cmd_m2c(a))
    print(find_asm(a.func))


if __name__ == "__main__":
    main()
