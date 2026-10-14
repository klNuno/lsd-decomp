#!/usr/bin/env python3
"""Match one function in isolation, built exactly like the game (flags come from the Makefile).

  tools/fmatch.py diff FUNC FILE.c [--gcc 2.7.2-psx] [--aspsx 2.56] [--cflags "-G8"] [--maspsx "-G8"] [--all]
      Compile FILE.c, compare FUNC with the original asm through objdiff-cli.
      Prints "MATCH func 100%" (exit 0) or the percent and the differing rows (exit 1).
      A compile error prints the compiler output (exit 2).
  tools/fmatch.py m2c FUNC     first-pass C from m2c, with include/ as context
  tools/fmatch.py asm FUNC     path of the original asm

Run from anywhere; work files go to build/fmatch/<FUNC>/. A 100 % here is necessary, not
sufficient: only `make check` on the whole executable decides.
"""
import argparse
import glob
import json
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


def build_target(func, work, overrides):
    src = os.path.join(work, "target.s")
    with open(src, "w", encoding="utf-8") as f:
        f.write('.include "include/macro.inc"\n.section .text\n')
        f.write(f'.include "{find_asm(func)}"\n')
    obj = os.path.join(work, "target.o")
    asm = make_var("AS", overrides) + " " + make_var("ASFLAGS", overrides)
    r = run(["bash", "-o", "pipefail", "-c", f"{PY} -I tools/sjis.py {src} | {asm} -o {obj}"])
    if r.returncode:
        sys.exit(f"target asm failed:\n{r.stderr}")
    return obj


def build_base(cfile, work, overrides):
    v = {n: make_var(n, overrides) for n in ("CPP", "CPPFLAGS", "CC1", "CFLAGS", "MASPSX", "MASPSXFLAGS", "AS", "ASFLAGS")}
    obj = os.path.join(work, "base.o")
    cfile = os.path.abspath(cfile)
    pipe = (f"{v['CPP']} {v['CPPFLAGS']} {cfile} | {v['CC1']} {v['CFLAGS']} | "
            f"{v['MASPSX']} {v['MASPSXFLAGS']} | {v['AS']} {v['ASFLAGS']} -o {obj}")
    r = run(["bash", "-o", "pipefail", "-c", pipe])
    if r.returncode:
        print(f"COMPILE ERROR\n{r.stderr.strip()}")
        sys.exit(2)
    return obj


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
    r = run([f"{ROOT}/tools/bin/objdiff-cli", "diff", "-1", t, "-2", b, a.func, "--format", "json", "-o", out])
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
    a = p.parse_args()
    if a.cmd == "diff":
        sys.exit(cmd_diff(a))
    if a.cmd == "m2c":
        sys.exit(cmd_m2c(a))
    print(find_asm(a.func))


if __name__ == "__main__":
    main()
