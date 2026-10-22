#!/usr/bin/env python3
"""Find PSY-Q library OBJs linked into the game executable.

Scans extract/SLPS_015.56 for every OBJ signature of every SDK version in
tools/src/psx_psyq_signatures (lab313ru/psx_psyq_signatures), resolves
overlaps and versions, and writes:
  tools/psyq/hits.tsv            every raw hit and what happened to it
  tools/psyq/libs.tsv            per-library version vote
  config/symbol_addrs.psyq.txt   splat symbols for the kept functions

Run: .venv/bin/python -I tools/psyq/match.py   (from the repo root)

Rules:
  - A hit must be 4-byte aligned.
  - An OBJ signature that matches at more than one address is ambiguous and
    rejected (mostly short wildcard stubs that match all over the binary).
  - Kept hits are chosen greedily by number of fixed (non-wildcard) bytes;
    a hit overlapping a bigger kept hit is dropped. A hit covering exactly
    the same range as a kept hit is merged into it (same code shipped in two
    libraries or under two OBJ names); see vote() for which one names it.
  - Versions are voted per library on the kept hits only; a hit whose
    version set misses the library's winning set is kept but flagged.
  - Function labels are the OBJ labels that do not start with "loc_" or
    "text_". A name already used by another OBJ (a static helper) gets an
    _ADDRESS suffix.
  - size is emitted only when the function range (label to next function
    label or OBJ end) holds exactly one `jr` and it is the second-to-last
    instruction, so no unnamed static function can hide inside it.
"""
import collections
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SIGDIR = os.path.join(ROOT, "tools/src/psx_psyq_signatures")
EXE = os.path.join(ROOT, "extract/SLPS_015.56")
OUT_SYMS = os.path.join(ROOT, "config/symbol_addrs.psyq.txt")
OUT_HITS = os.path.join(ROOT, "tools/psyq/hits.tsv")
OUT_LIBS = os.path.join(ROOT, "tools/psyq/libs.tsv")

HEADER = 0x800
LOAD = 0x80010000


def vram(off):
    return LOAD + off - HEADER


# Ranges where two OBJs ship the same bytes under different names. The jal
# targets differ only through relocations, so the callee decides. main()
# checks the callee and stops if the evidence no longer holds.
NAME_FIXES = {
    0x800391C8: ("SpuWrite", "_spu_write",
                 "S_R.OBJ SpuRead and S_W.OBJ SpuWrite match; this copy calls _spu_write"),
    0x8003FBF4: ("GsDrawOt", "DrawOTag",
                 "GS_111.OBJ GsDrawOt and GS_112.OBJ GsDrawOtIO match; this copy calls DrawOTag"),
}


# Signature hits that are not Sony code. The address map says what the bytes
# are; main() stops if a listed hit disappears, so a stale entry is noticed.
FALSE_HITS = {
    # LIBSND SsInit (SSINIT_C.OBJ, SSINIT_H.OBJ): 0x30 bytes whose three jal
    # targets are wildcards. This copy calls game functions func_800280D0,
    # func_80028218 (VSyncCallback setup) and func_800280E0, sits in the
    # data function table at 0x8006D4E8 between func_80027C80 and
    # func_80027D70, and the strings of the code from 0x80027D70 come before
    # the jump tables of the code from 0x800271D8 in .rodata: one game TU
    # 0x800271D8..0x80028B78, src/game/file_cd.c.
    0x80027D40: "SsInit pattern inside game TU file_cd.c, calls game code",
}


# Sony functions no exact signature finds: the game links a LIBSND build that
# is not in the database (it matches 3.3 and 3.5 OBJs by pieces), and the two
# SPU stubs are 8 words that match everywhere. Evidence per function (fuzzy
# label-aligned match against every LIBSND/LIBSPU OBJ, callers, callees,
# strings) was gathered by hand for each one. Each address must
# start a function and must not be named by the scan; main() stops otherwise.
NEAR_MATCHES = {
    # LIBGS GS_101, GS_102 and GS_124 share one 16-byte body (store a0 into a common), so the scan
    # rejects them as ambiguous; named by the common they store to (2026-10-17, names audit review)
    0x8003FB0C: "GsSetNearClip",
    0x8003FBE4: "GsSetWorkBase",
    # LIBSND SSINIT.OBJ (3.3), units psyq/8003221C and psyq/80032588 (once game/spu.c and
    # game/seq_timer.c): the 11 functions follow the OBJ's labels one to one, _SsInit at 88 % of its
    # words, the other ten word for word (2026-10-17, names audit)
    0x8003221C: "_SsInit",
    0x80032368: "SsInit",
    0x80032388: "SsInitHot",
    0x80032588: "SsSetTickMode",
    0x80032708: "_SsStart",
    0x80032998: "SsStart",
    0x800329B8: "SsStart2",
    0x800329D8: "SsEnd",
    0x80032A7C: "SsQuit",
    0x80032A9C: "_SsTrapIntrVSync",
    0x80032AD0: "_SsSeqCalledTbyT_1per2",
    # LIBSND VMANAGER.OBJ (3.3), unit psyq/8002CF18: the 31 functions follow the OBJ's 31 named
    # labels one to one (range cover 89 % vs 3.3)
    0x8002CF18: "SpuVmAlloc",
    0x8002D1B4: "SpuVmKeyOnNow",
    0x8002D6A4: "SpuVmDoAllocate",
    0x8002D8E0: "vmNoiseOn",
    0x8002DDBC: "vmNoiseOn2",
    0x8002DF7C: "note2pitch",
    0x8002E038: "note2pitch2",
    0x8002E138: "SePitchBend",
    0x8002E2F8: "SsUtVibrateOn",
    0x8002E300: "SsUtVibrateOff",
    0x8002E308: "SeAutoVol",
    0x8002E4D8: "SetAutoVol",
    0x8002E874: "SeAutoPan",
    0x8002EA44: "SetAutoPan",
    0x8002EDD4: "SpuVmInit",
    0x8002F20C: "SpuVmNoiseOnWithAdsr",
    0x8002F2A4: "SpuVmNoiseOff",
    0x8002F368: "SpuVmNoiseOn",
    0x8002F3E8: "SpuVmPBVoice",
    0x8002F610: "SpuVmPitchBend",
    0x8002F700: "SpuVmFlush",
    0x8002FAC4: "SpuVmKeyOn",
    0x800300D0: "SpuVmKeyOff",
    0x800302DC: "SpuVmSeKeyOn",
    0x800303C8: "SpuVmSeKeyOff",
    0x800303FC: "KeyOnCheck",
    0x80030404: "SpuVmSetSeqVol",
    0x80030584: "SpuVmGetSeqVol",
    0x800305F4: "SpuVmGetSeqLVol",
    0x80030648: "SpuVmGetSeqRVol",
    0x8003069C: "SpuVmSeqKeyOff",
    # LIBSND VMANAGER.OBJ (3.5 closest), unit psyq/80030980
    0x80030980: "SpuVmSetVol",
    0x80030E90: "SsUtKeyOn",
    0x80031280: "SsUtKeyOff",
    0x8003149C: "SsUtKeyOnV",
    0x80031890: "SsUtKeyOffV",
    # LIBSND VMANAGER.OBJ (3.3), unit psyq/80031A44
    0x80031A44: "SsUtChangePitch",
    0x80031BA4: "SsUtChangeADSR",
    0x80031C98: "SsUtGetDetVVol",
    0x80031CF0: "SsUtSetDetVVol",
    0x80031D6C: "SsUtGetVVol",
    0x80031DF8: "SsUtSetVVol",
    0x80031E94: "SsUtAutoVol",
    0x80031EE8: "SsUtAutoPan",
    0x80031F3C: "SsUtAllKeyOff",
    # LIBSND DECRE.OBJ, version not in the database, unit psyq/80033C90
    0x80033C90: "_SsSndDecrescendo",
    # LIBSND PLAY.OBJ + SEQREAD.OBJ (3.3), unit psyq/8003410C
    0x8003410C: "Snd_play",
    0x80034138: "SeqPlay",
    0x8003424C: "GetSeqData",
    0x800344FC: "NoteOn",
    0x80034614: "SetProgramChange",
    0x80034690: "SetControlChange",
    0x800349B0: "ContModulation",
    0x80034AEC: "ContPortaTime",
    0x80034C28: "ContPortamento",
    0x80034D90: "ContResetAll",
    0x80034E5C: "ContNrpn1",
    0x80034F90: "ContNrpn2",
    0x800350D8: "ContRpn1",
    0x80035154: "ContRpn2",
    0x800351D0: "ContDataEntry",
    0x800357B0: "Snd_setVabAttr",
    0x80035A7C: "SetPitchBend",
    0x80035B2C: "GetMetaEvent",
    0x80035E80: "ReadDeltaValue",
    # LIBSND CRES.OBJ, version not in the database, unit psyq/80036528
    0x80036528: "_SsSndCrescendo",
    # LIBSPU S_IH.OBJ and S_I.OBJ: jal _SpuInit with a0 = 1 and a0 = 0
    0x80036AA8: "SpuInitHot",
    0x80038D54: "SpuInit",
    # LIBSND SEQINIT.OBJ (3.3 = 3.5, 253 of 254 words), unit psyq/8003A670
    0x8003A670: "_SsInitSoundSeq",
    0x8003A99C: "SsSeqOpen",
}


def version_key(v):
    # "260" -> 2.6, "3610" -> 3.6.1.0; sort as tuples of digits.
    return tuple(int(c) for c in v)


def fmt_versions(vs):
    return ",".join(sorted(vs, key=version_key))


def load_signatures():
    """(lib, obj, sig) -> {"versions": set, "labels": [...]}"""
    sigs = {}
    for vdir in sorted(os.listdir(SIGDIR), key=lambda s: (not s.isdigit(), s)):
        path = os.path.join(SIGDIR, vdir)
        if not vdir.isdigit() or not os.path.isdir(path):
            continue
        for fn in sorted(os.listdir(path)):
            if not fn.endswith(".json"):
                continue
            lib = fn[:-5]
            with open(os.path.join(path, fn)) as f:
                entries = json.load(f)
            for o in entries:
                sig = o.get("sig", "").strip()
                if not sig:
                    continue
                key = (lib, o["name"], sig)
                if key not in sigs:
                    sigs[key] = {"versions": set(), "labels": o.get("labels", [])}
                sigs[key]["versions"].add(vdir)
    return sigs


def compile_sig(sig):
    toks = sig.split()
    pat = b"".join(b"." if t == "??" else re.escape(bytes([int(t, 16)])) for t in toks)
    fixed = sum(t != "??" for t in toks)
    return re.compile(pat, re.S), len(toks), fixed


def scan(data, sigs):
    hits = []
    for key, info in sigs.items():
        rx, size, fixed = compile_sig(key[2])
        pos = 0
        while True:
            m = rx.search(data, pos)
            if not m:
                break
            if m.start() % 4 == 0:
                hits.append({"lib": key[0], "obj": key[1], "sig": key[2],
                             "versions": set(info["versions"]),
                             "labels": info["labels"], "off": m.start(),
                             "size": size, "fixed": fixed,
                             "status": "", "merged": []})
            pos = m.start() + 1
    return hits


def resolve(hits):
    # Ambiguity: an OBJ (lib, obj) whose signatures land at several offsets.
    positions = collections.defaultdict(set)
    for h in hits:
        positions[(h["lib"], h["obj"], h["sig"])].add(h["off"])
    for h in hits:
        n = len(positions[(h["lib"], h["obj"], h["sig"])])
        if n > 1:
            h["status"] = "ambiguous x%d" % n

    for h in hits:
        if vram(h["off"]) in FALSE_HITS and not h["status"]:
            h["status"] = "false hit"
    kept = []
    order = sorted((h for h in hits if not h["status"]),
                   key=lambda h: (-h["fixed"], -h["size"], h["off"], h["lib"], h["obj"]))
    for h in order:
        a, b = h["off"], h["off"] + h["size"]
        clash = None
        for k in kept:
            ka, kb = k["off"], k["off"] + k["size"]
            if a < kb and ka < b:
                clash = k
                break
        if clash is None:
            h["status"] = "kept"
            kept.append(h)
        elif (clash["off"], clash["off"] + clash["size"]) == (a, b):
            h["status"] = "merged into %s/%s" % (clash["lib"], clash["obj"])
            clash["merged"].append(h)
        else:
            h["status"] = "overlaps %s/%s@%08x" % (clash["lib"], clash["obj"], vram(clash["off"]))
    kept.sort(key=lambda h: h["off"])
    return kept


def lib_scores(hs):
    score = collections.Counter()
    for g in hs:
        for v in g["versions"]:
            score[v] += g["size"]
    return score


def vote(kept):
    """Pick one source hit per kept range, then vote versions per library.

    Pass 1 votes on ranges that only one library claims. Pass 2 resolves
    ranges claimed by several libraries (same bytes in LIBC and LIBC2, or a
    standalone MALLOC.OBJ and LIBAPI's MALLOC.OBJ): prefer a candidate whose
    versions meet its library's pass-1 winners, then the library with the
    most pass-1 bytes. Pass 3 is the final vote on the chosen sources.
    """
    single = collections.defaultdict(list)
    for h in kept:
        if not h["merged"]:
            single[h["lib"]].append(h)
    pass1 = {}
    for lib, hs in single.items():
        score = lib_scores(hs)
        best = max(score.values())
        pass1[lib] = ({v for v, s in score.items() if s == best}, sum(g["size"] for g in hs))

    for h in kept:
        cands = [h] + h["merged"]

        def rank(g):
            winners, nbytes = pass1.get(g["lib"], (None, 0))
            consistent = winners is None or bool(winners & g["versions"])
            return (not consistent, -nbytes, g["lib"], g["obj"])
        h["source"] = min(cands, key=rank)
        h["source"]["names"] = True

    libs = collections.defaultdict(list)
    for h in kept:
        libs[h["source"]["lib"]].append(h["source"])
    result = {}
    for lib, hs in libs.items():
        score = lib_scores(hs)
        best = max(score.values())
        winners = {v for v, s in score.items() if s == best}
        result[lib] = {"hits": hs, "score": score, "winners": winners,
                       "total": sum(g["size"] for g in hs)}
    return result


def is_local(name):
    # loc_XXX: branch targets. text_XXX: MipsDis names for unnamed relocation
    # targets inside .text; checked on this binary, none starts a function.
    return name.startswith(("loc_", "text_"))


def ends_function(w2, w1):
    """True when the two words before a label close a function: jr, j or
    b (beq $zero,$zero) followed by its delay slot, or a break."""
    return (w2 & 0xFC1FFFFF == 0x00000008 or w2 >> 26 == 2 or w2 >> 16 == 0x1000
            or w1 & 0xFC00003F == 0x0000000D)


# When an OBJ gives one offset two names, this one wins (2MBYTE.OBJ names the
# PS-X EXE entry point both stup2 and __SN_ENTRY_POINT).
PREFERRED_ALIASES = {"__SN_ENTRY_POINT"}


JAL_TARGETS = set()


def jal_targets(data):
    """Every jal target in the executable's text."""
    out = set()
    for p in range(0x800, len(data) - 3, 4):
        w = int.from_bytes(data[p:p + 4], "little")
        if w >> 26 == 3:
            out.add(0x80000000 | (w & 0x3FFFFFF) << 2)
    return out


def function_ranges(h, data):
    """[(name, vram, size or None, "func" or "label")] for one hit.

    A named label that does not start the OBJ and does not follow a function
    end is a second entry point reached by fallthrough (hand-written GTE asm)
    or an internal label (stup0/stup1 in the startup code): it becomes a
    splat "label" and does not bound the function before it.
    """
    word = lambda p: int.from_bytes(data[h["off"] + p:h["off"] + p + 4], "little")
    labels = {}
    for l in sorted(h["labels"], key=lambda l: l["offset"]):
        if is_local(l["name"]):
            continue
        prev = labels.get(l["offset"])
        if prev is None or l["name"] in PREFERRED_ALIASES:
            labels[l["offset"]] = l["name"]
    kinds = {}
    for off in labels:
        mid = off > 0 and not (off >= 8 and ends_function(word(off - 8), word(off - 4)))
        # A second entry that something calls with jal must be a function, or the
        # caller's jal has no symbol to link against (RCpolyGT4A).
        called = vram(h["off"] + off) in JAL_TARGETS
        kinds[off] = "label" if mid and not called else "func"
    funcs = sorted(o for o, k in kinds.items() if k == "func")
    out = []
    for off in sorted(labels):
        size = None
        if kinds[off] == "func":
            later = [o for o in funcs if o > off]
            end = later[0] if later else h["size"]
            words = [word(p) for p in range(off, end, 4)]
            jrs = [i for i, w in enumerate(words) if w & 0xFC1FFFFF == 0x00000008]
            if jrs == [len(words) - 2]:
                size = end - off
        out.append((labels[off], vram(h["off"] + off), size, kinds[off]))
    return out


def main():
    with open(EXE, "rb") as f:
        data = f.read()
    if data[:8] != b"PS-X EXE":
        sys.exit("not a PS-X EXE: " + EXE)

    JAL_TARGETS.update(jal_targets(data))
    sigs = load_signatures()
    hits = scan(data, sigs)
    kept = resolve(hits)
    for where in FALSE_HITS:
        if not any(vram(h["off"]) == where for h in hits):
            sys.exit("FALSE_HITS entry %08x no longer matches any signature" % where)
    lib_votes = vote(kept)

    entries = []       # [addr, name, size, lib, obj, kind]
    notes = []
    fixes_used = []
    for h in kept:
        src = h["source"]
        own = function_ranges(src, data)
        others = set()
        for g in h["merged"]:
            if g is not src:
                others |= {(n, a) for n, a, _, _ in function_ranges(g, data)}
        if h is not src:
            others |= {(n, a) for n, a, _, _ in function_ranges(h, data)}
        if others and others != {(n, a) for n, a, _, _ in own}:
            where = vram(h["off"])
            names = sorted({n for n, _ in others} | {n for n, _, _, _ in own})
            if where not in NAME_FIXES:
                if len(own) != 1:
                    sys.exit("ambiguous multi-function range at %08x" % where)
                own = [("func_%08X" % where,) + tuple(own[0][1:])]
                notes.append("unnamed: %08x same bytes under %s, kept as %s"
                             % (where, "/".join(names), own[0][0]))
            else:
                name, callee, why = NAME_FIXES[where]
                if name not in names or len(own) != 1:
                    sys.exit("NAME_FIXES entry %08x no longer fits %s" % (where, names))
                own = [(name,) + tuple(own[0][1:])]
                fixes_used.append((where, name, callee))
                notes.append("named %s at %08x (%s)" % (name, where, why))
        for name, addr, size, kind in own:
            entries.append([addr, name, size, src["lib"], src["obj"], kind])

    syms = {}          # addr -> [name, size, lib, obj, kind]
    by_name = collections.defaultdict(list)
    for e in entries:
        if e[0] in syms:
            notes.append("alias %s = %s @%08x dropped" % (e[1], syms[e[0]][0], e[0]))
            continue
        syms[e[0]] = e[1:]
        by_name[e[1]].append(e[0])
    for name, where in by_name.items():
        if len(where) < 2:
            continue
        # A helper compiled into several OBJs (memset in LIBGPU SYS.OBJ and
        # LIBC2 MEMSET.OBJ). The copy in the OBJ named after it keeps the bare
        # name; every other copy is a static and gets an address suffix.
        owner = [a for a in where if syms[a][3] == name.upper() + ".OBJ"]
        for a in where:
            if owner and a == owner[0]:
                continue
            syms[a][0] = "%s_%08X" % (name, a)
            notes.append("static %s @%08x named %s" % (name, a, syms[a][0]))

    addr_of = {v[0]: a for a, v in syms.items()}
    for where, name, callee in fixes_used:
        size = syms[where][1] or 0x40
        targets = set()
        for p in range(where, where + size, 4):
            w = int.from_bytes(data[p - LOAD + HEADER:p - LOAD + HEADER + 4], "little")
            if w >> 26 == 3:  # jal
                targets.add((p & 0xF0000000) | ((w & 0x03FFFFFF) << 2))
        if addr_of.get(callee) not in targets:
            sys.exit("NAME_FIXES %s at %08x does not call %s" % (name, where, callee))

    taken = {v[0] for v in syms.values()}
    word_at = lambda a: int.from_bytes(data[a - LOAD + HEADER:a - LOAD + HEADER + 4], "little")
    for a, name in sorted(NEAR_MATCHES.items()):
        if a in syms or name in taken:
            sys.exit("NEAR_MATCHES %s at %08x clashes with the scan (%s)" % (name, a, syms.get(a, [name])[0]))
        if not ends_function(word_at(a - 8), word_at(a - 4)):
            sys.exit("NEAR_MATCHES %s at %08x does not start a function" % (name, a))
        syms[a] = [name, None, "LIBSND/LIBSPU", "near match", "func"]
        notes.append("near match %s at %08x" % (name, a))

    addrs = sorted(syms)
    if len({syms[a][0] for a in addrs}) != len(addrs):
        sys.exit("duplicate symbol name")
    funcs = [a for a in addrs if syms[a][4] == "func"]
    for a, b in zip(funcs, funcs[1:]):
        size = syms[a][1]
        if size is not None and a + size > b:
            sys.exit("overlap: %s @%08x size %x reaches %s @%08x" % (syms[a][0], a, size, syms[b][0], b))

    # Sony data labels written by hand (shiftability) live after this marker and are kept.
    kept = ""
    if os.path.exists(OUT_SYMS):
        old = open(OUT_SYMS).read()
        cut = old.find("\n// Hand-kept below this line")
        if cut >= 0:
            kept = old[cut:]
    with open(OUT_SYMS, "w") as f:
        f.write("// PSY-Q library functions, generated by tools/psyq/match.py\n")
        f.write("// from lab313ru/psx_psyq_signatures. Do not edit by hand above the hand-kept block; rerun the script.\n")
        for a in addrs:
            name, size, lib, obj, kind = syms[a]
            extra = " size:0x%X" % size if size else ""
            f.write("%s = 0x%08X; // type:%s%s\n" % (name, a, kind, extra))
        f.write(kept)

    with open(OUT_HITS, "w") as f:
        f.write("vram\tfile_off\tsize\tfixed\tlib\tobj\tversions\tstatus\tfunctions\n")
        for h in sorted(hits, key=lambda h: (h["off"], h["lib"], h["obj"])):
            funcs = " ".join("%s@%08x%s%s" % (n, a, ":%x" % s if s else "",
                                             "(label)" if k == "label" else "")
                             for n, a, s, k in function_ranges(h, data))
            f.write("%08x\t%06x\t%x\t%d\t%s\t%s\t%s\t%s\t%s\n"
                    % (vram(h["off"]), h["off"], h["size"], h["fixed"], h["lib"], h["obj"],
                       fmt_versions(h["versions"]),
                       h["status"] + (" (names)" if h.get("names") else ""), funcs))

    with open(OUT_LIBS, "w") as f:
        f.write("lib\tobjs\tbytes\twinning_versions\tlow\thigh\toff_version_objs\n")
        for lib in sorted(lib_votes):
            lv = lib_votes[lib]
            hs = lv["hits"]
            off = sorted({"%s(%s)" % (g["obj"], fmt_versions(g["versions"]))
                          for g in hs if not (g["versions"] & lv["winners"])})
            f.write("%s\t%d\t%d\t%s\t%08x\t%08x\t%s\n"
                    % (lib, len(hs), lv["total"], fmt_versions(lv["winners"]),
                       vram(min(g["off"] for g in hs)),
                       vram(max(g["off"] + g["size"] for g in hs)), " ".join(off)))

    status = collections.Counter(h["status"].split()[0] for h in hits)
    sized = sum(1 for s in syms.values() if s[1])
    nlabels = sum(1 for s in syms.values() if s[4] == "label")
    print("signatures %d, raw hits %d, %s" % (len(sigs), len(hits), dict(status)))
    print("kept OBJ ranges %d, symbols %d: %d func (%d with size), %d label; range %08x-%08x"
          % (len(kept), len(syms), len(syms) - nlabels, sized, nlabels, addrs[0], addrs[-1]))
    for n in notes:
        print("note:", n)


if __name__ == "__main__":
    main()
