#!/usr/bin/env python3
"""Split the address-named game units into the original source files of config/layout.tsv.

  tools/split_units.py apply [--rev REV]   split src/game/<addr>.c into the files of the plan
  tools/split_units.py docs                write docs/layout.md from config/layout.tsv

apply reads each old unit from src/game/<addr>.c, or from git REV when the file is gone (default
6c028b9, the last commit with address units), so the split can be replayed. Function addresses
come from build/lsd.elf: run it after a green `make check` of the address-unit tree. It writes
the new C files, rewrites the game entries of config/splat.yaml and removes the old units. Then
run `make split` twice (INCLUDE_RODATA paths name the new units) and `make check`.

Each new file gets, in the order of the old unit: its functions (address range of the plan), its
INCLUDE_RODATA lines (rodata range of its splat entry), its initialized records, and every other
declaration whose name its code uses, directly or through another kept declaration. Declarations
keep their exact text: unprototyped forms and tentative gp definitions matter to the bytes.
"""
import argparse, os, re, subprocess, sys
from collections import OrderedDict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PLAN = os.path.join(ROOT, 'config/layout.tsv')
SPLAT = os.path.join(ROOT, 'config/splat.yaml')
ELF = os.path.join(ROOT, 'build/lsd.elf')
SRC = os.path.join(ROOT, 'src/game')
ROM_BASE = 0x8000F800  # vram - rom offset of the main segment
DEFAULT_REV = '6c028b9'

# .rodata entries after the split: rom offset -> file. The old 0x1F78 entry is gone (graph.c holds both
# Graph strings); 0x1D0C, 0x1F4C and 0x1F88 are new cuts (docs/layout.md, "Rodata").
RODATA = OrderedDict([
    (0xA8C, 'heap'), (0xB54, 'model_object'), (0xF64, 'pad'), (0xFA4, 'scene'), (0xFD8, 'file_cd'),
    (0x14D8, 'seq_timer'), (0x17EC, 'bgm'), (0x1890, 'menu_screen'), (0x1A90, 'screen_sprite'),
    (0x1B84, 'path_table'), (0x1BEC, 'dream_runner'), (0x1C34, 'menu'), (0x1D0C, 'card'),
    (0x1DD0, 'comment_object'), (0x1EA4, 'string_list'), (0x1F4C, 'place'), (0x1F6C, 'graph'),
    (0x1F88, 'dream_sys'), (0x206C, 'sym'),
])
RODATA_END = 0x20DC
# Comments of the .rodata entries the split cut or merged (the others keep their old comment).
RODATA_COMMENTS = {
    0x1C34: 'object B: FLASHBACK block (data 0x80086CFC), Menu_Init..Menu_GetVtbl',
    0x1D0C: 'object B, card part: the strings of g_cardMessageNames',
    0x1EA4: 'object D: alphabet copy, StringList_Open, jtbl StringList_OnKey',
    0x1F4C: 'object D, place part: jtbl Place_OnDreamSysNotify',
    0x1F6C: 'objects D2 and E start: ETC\\ETCSE of Graph_Init, ETC\\HGRAPH.TIM',
    0x1F88: 'object E: jtbls DreamSys_OnPad, DreamSys_OnEntityEvent',
}
# Initialized gp records: .sdata subsegment rom offset -> file that defines them.
SDATA = {0x7B0FC: 'view', 0x7B368: 'scenery'}

KEYWORDS = set('''auto break case char const continue default do double else enum extern float for goto if
int long register return short signed sizeof static struct switch typedef union unsigned void volatile
while asm'''.split())


def read_plan():
    rows = []
    with open(PLAN) as f:
        head = f.readline().rstrip('\n').split('\t')
        for line in f:
            if line.strip():
                rows.append(dict(zip(head, line.rstrip('\n').split('\t'))))
    return rows


# ---------------------------------------------------------------- C items

class Item:
    def __init__(self, kind, text, lead):
        self.kind = kind      # include, define, func, decl, rodata, comment
        self.text = text      # code text without leading comments
        self.lead = lead      # comments and blank lines before it (kept with it)
        self.names = set()    # names it declares
        self.uses = set()     # identifiers in its code
        self.func = None      # function name
        self.init = False     # initialized definition


# K&R definition head: name(a, b) followed by the parameter declarations
KR = re.compile(r'\w+\s*(\(\s*[A-Za-z_]\w*(?:\s*,\s*[A-Za-z_]\w*)*\s*\))\s*[A-Za-z_]')


def strip_code(text):
    """Remove comments, strings and char literals."""
    out, i, n = [], 0, len(text)
    while i < n:
        c = text[i]
        if text.startswith('/*', i):
            j = text.index('*/', i + 2) + 2
            out.append(' '); i = j
        elif text.startswith('//', i):
            j = text.find('\n', i); j = n if j < 0 else j
            i = j
        elif c in '"\'':
            j = i + 1
            while text[j] != c:
                j += 2 if text[j] == '\\' else 1
            out.append(' 0 '); i = j + 1
        else:
            out.append(c); i += 1
    return ''.join(out)


def idents(code):
    return set(re.findall(r'[A-Za-z_]\w*', code)) - KEYWORDS


def drop_braces(code):
    out, depth = [], 0
    for c in code:
        if c == '{':
            depth += 1
            continue
        if c == '}':
            depth -= 1
            continue
        if depth == 0:
            out.append(c)
    return ''.join(out)


def top_split(code, sep):
    parts, depth, cur = [], 0, []
    for c in code:
        if c in '([{':
            depth += 1
        elif c in ')]}':
            depth -= 1
        if c == sep and depth == 0:
            parts.append(''.join(cur)); cur = []
        else:
            cur.append(c)
    parts.append(''.join(cur))
    return parts


def declared_names(code):
    """Names declared by one top-level declaration (code without comments)."""
    names = set()
    body = code.strip().rstrip(';')
    m = re.match(r'(typedef\s+)?(struct|union|enum)\s+(\w+)\s*\{', body)
    if m:
        names.add(m.group(3))
    if re.match(r'(typedef\s+)?enum\b', body):
        inner = body[body.index('{') + 1:body.rindex('}')] if '{' in body else ''
        for part in top_split(inner, ','):
            m = re.match(r'\s*(\w+)', part)
            if m:
                names.add(m.group(1))
    flat = drop_braces(body)
    # an initializer is not part of the declarator
    flat = top_split(flat, '=')[0] if '=' in flat else flat
    m = re.match(r'\s*(typedef\s+)?(extern\s+)?((const|volatile|unsigned|signed|struct|union|enum)\s+)*\w+', flat)
    rest = flat[m.end():] if m else flat
    for decl in top_split(rest, ','):
        m = re.search(r'(\w*)\s*\(\s*(\*+\s*(\w+))?', decl)
        if m and m.group(1) and m.group(1) not in KEYWORDS:  # a function: its name before the first '('
            names.add(m.group(1)); continue
        if m and m.group(3):  # a pointer to function: (*name)
            names.add(m.group(3)); continue
        decl = re.sub(r'\[[^\]]*\]', '', decl)
        ids = re.findall(r'[A-Za-z_]\w*', decl)
        ids = [i for i in ids if i not in KEYWORDS]
        if ids:
            names.add(ids[-1])
    if not names:  # `struct X;` or a bare type
        ids = [i for i in re.findall(r'[A-Za-z_]\w*', flat) if i not in KEYWORDS]
        if ids:
            names.add(ids[-1])
    return names


def parse_c(text):
    """Top-level items of a C unit. Comments and blank lines lead the next item."""
    items, i, n = [], 0, len(text)
    lead_start = 0
    while True:
        # skip whitespace and comments: they lead the next item
        j = i
        while j < n:
            if text[j].isspace():
                j += 1
            elif text.startswith('/*', j):
                j = text.index('*/', j + 2) + 2
            elif text.startswith('//', j):
                k = text.find('\n', j); j = n if k < 0 else k
            else:
                break
        if j >= n:
            if text[lead_start:].strip():
                items.append(Item('comment', '', text[lead_start:]))
            break
        lead = text[lead_start:j]
        start = j
        if text[j] == '#':
            k = j
            while True:
                e = text.find('\n', k)
                e = n if e < 0 else e
                if text[e - 1] == '\\':
                    k = e + 1; continue
                break
            code = text[start:e]
            kind = ('include' if re.match(r'#\s*include', code) else
                    'define' if re.match(r'#\s*define', code) else 'pp')
            it = Item(kind, code, lead)
            if kind == 'define':
                it.names = {re.match(r'#\s*define\s+(\w+)', code).group(1)}
                it.uses = idents(strip_code(code)) - it.names
            items.append(it)
            i = lead_start = e
            continue
        # scan to ';' at depth 0, or to the '}' closing a function body
        depth, k = 0, j
        kind = None
        while k < n:
            c = text[k]
            if text.startswith('/*', k):
                k = text.index('*/', k + 2) + 2; continue
            if text.startswith('//', k):
                e = text.find('\n', k); k = n if e < 0 else e; continue
            if c in '"\'':
                q = k + 1
                while text[q] != c:
                    q += 2 if text[q] == '\\' else 1
                k = q + 1; continue
            if c in '([{':
                if c == '{' and depth == 0:
                    head = strip_code(text[start:k]).strip()
                    if (head.endswith(')') or KR.search(head)) and '=' not in drop_braces(head):
                        kind = 'func'
                depth += 1
            elif c in ')]}':
                depth -= 1
                if c == '}' and depth == 0 and kind == 'func':
                    k += 1; break
            elif c == ';' and depth == 0:
                if not KR.search(strip_code(text[start:k])):
                    k += 1; kind = kind or 'decl'; break
            k += 1
        m = re.match(r'[ \t]*(/\*[^\n]*?\*/|//[^\n]*)[ \t]*(?=\n|$)', text[k:])
        if m:  # a comment on the same line closes the item
            k += m.end()
        code = text[start:k]
        it = Item(kind, code, lead)
        sc = strip_code(code)
        if kind == 'func':
            head = sc[:sc.index('{')]
            # the name is the identifier before the parameter list of the declarator
            h = head.rstrip()
            m = KR.search(h)
            if m:  # K&R definition: the parameter declarations follow the identifier list
                h = h[:m.start(1) + len(m.group(1))]
            depth, q = 0, len(h) - 1
            while True:
                depth += {')': 1, '(': -1}.get(h[q], 0)
                if depth == 0:
                    break
                q -= 1
            it.func = re.search(r'(\w+)\s*$', h[:q]).group(1)
            it.names = {it.func}
            it.uses = idents(sc)
        elif re.match(r'INCLUDE_RODATA\s*\(', code):
            it.kind = 'rodata'
            it.names = {re.search(r',\s*(\w+)\s*\)', code).group(1)}
            it.uses = set()
        else:
            it.names = declared_names(sc)
            it.uses = idents(sc) - it.names
            flat = drop_braces(sc)
            it.init = ('=' in top_split(flat, ';')[0] and not re.match(r'\s*(extern|typedef)\b', sc))
        items.append(it)
        i = lead_start = k
    return items


# ---------------------------------------------------------------- split

def elf_funcs():
    out = subprocess.run(['mipsel-linux-gnu-nm', ELF], capture_output=True, text=True, check=True).stdout
    addr = {}
    for line in out.splitlines():
        p = line.split()
        if len(p) == 3:
            addr.setdefault(p[2], int(p[0], 16))
    return addr


def old_unit_text(unit, rev):
    path = os.path.join(SRC, unit + '.c')
    if os.path.exists(path):
        return open(path, encoding='utf-8').read()
    return subprocess.run(['git', '-C', ROOT, 'show', '%s:src/game/%s.c' % (rev, unit)],
                          capture_output=True, text=True, check=True).stdout


def header_types():
    """Type names each game header declares, with the headers it includes."""
    out = {}
    for name in sorted(os.listdir(os.path.join(ROOT, 'include/game'))):
        text = open(os.path.join(ROOT, 'include/game', name), encoding='utf-8').read()
        names, incs = set(), re.findall(r'#include\s+"([^"]+)"', text)
        for it in parse_c(text):
            if it.kind in ('decl', 'define'):
                names |= it.names
        out['game/' + name] = (names, incs)
    return out


def split_header(lead):
    """(header comment, rest of lead): the unit comment is the first block comment of the unit that
    stands alone (a blank line after it)."""
    m = re.search(r'/\*.*?\*/\n\s*\n', lead, re.S)
    if not m:
        return None, lead
    return m.group(0).rstrip() + '\n', lead[:m.start()] + lead[m.end():]


def rodata_file(addr):
    rom = addr - ROM_BASE
    keys = list(RODATA)
    for i, k in enumerate(keys):
        end = keys[i + 1] if i + 1 < len(keys) else RODATA_END
        if k <= rom < end:
            return RODATA[k]
    raise SystemExit('no rodata file for 0x%X' % addr)


def build_files(rows, rev):
    faddr = elf_funcs()
    htypes = header_types()
    # file ranges
    ranges = []
    for r in rows:
        ranges.append((faddr[r['FIRST_FUNC']], faddr[r['LAST_FUNC']], r['FILE'][:-2], r))
    ranges.sort()

    def file_of(fn):
        a = faddr[fn]
        for lo, hi, name, _ in ranges:
            if lo <= a <= hi:
                return name
        raise SystemExit('function %s at 0x%X is in no file' % (fn, a))

    units = []
    for r in rows:
        for u in r['UNIT'].split('+'):
            if u not in units:
                units.append(u)
    files = OrderedDict((name, {'items': [], 'units': [], 'row': r}) for _, _, name, r in ranges)
    unit_headers = {}
    for unit in units:
        items = parse_c(old_unit_text(unit, rev))
        incs = [it.text for it in items if it.kind == 'include']
        body = [it for it in items if it.kind != 'include']
        # the unit comment block
        hdr = None
        for it in body:
            if it.kind == 'func':
                break
            h, rest = split_header(it.lead)
            if h:
                hdr, it.lead = h, rest
                break
        unit_headers[unit] = hdr
        owners = {}  # item index -> set of files
        for idx, it in enumerate(body):
            if it.kind == 'func':
                owners[idx] = {file_of(it.func)}
            elif it.kind == 'rodata':
                owners[idx] = {rodata_file(faddr[next(iter(it.names))])}
        unit_files = []
        for idx in sorted(owners):
            for f in owners[idx]:
                if f not in unit_files:
                    unit_files.append(f)
        for f in unit_files:
            files[f]['units'].append(unit)
        # initialized records go to the one file that uses them
        uses_by_file = {f: set() for f in unit_files}
        for idx, own in owners.items():
            for f in own:
                uses_by_file[f] |= body[idx].uses
        for idx, it in enumerate(body):
            if it.kind == 'decl' and it.init:
                users = [f for f in unit_files if it.names & uses_by_file[f]]
                if len(users) != 1:
                    raise SystemExit('%s: initialized %s used by %s' % (unit, sorted(it.names), users))
                owners[idx] = {users[0]}
                uses_by_file[users[0]] |= it.uses
        # every other declaration: closure over the names each file uses
        fixed = set(owners)
        for f in unit_files:
            need = set(uses_by_file[f])
            kept = set()
            changed = True
            while changed:
                changed = False
                for idx, it in enumerate(body):
                    if idx in kept or idx in fixed or it.kind not in ('decl', 'define'):
                        continue
                    if it.names & need:
                        kept.add(idx); need |= it.uses; changed = True
            for idx in kept:
                owners.setdefault(idx, set()).add(f)
            # includes: those whose types (or their includes' types) the file uses
            files[f].setdefault('need', set()).update(need)
            for inc in incs:
                if inc not in files[f].setdefault('incs', []):
                    files[f]['incs'].append(inc)
        for idx, it in enumerate(body):
            for f in owners.get(idx, ()):
                files[f]['items'].append((unit, it))
            if idx not in owners and it.kind != 'comment':
                print('dropped from %s: %s' % (unit, it.text.splitlines()[0][:90]), file=sys.stderr)
    return files, unit_headers, htypes


def header_closure(h, htypes, seen=None):
    seen = set() if seen is None else seen
    if h in seen or h not in htypes:
        return set()
    seen.add(h)
    names = set(htypes[h][0])
    for inc in htypes[h][1]:
        names |= header_closure(inc, htypes, seen)
    return names


HEADER_NOTE = ' * File boundaries: %s (docs/layout.md)\n'


def render(name, f, headers, htypes):
    out = []
    need = set(f['need'])
    for _, it in f['items']:
        need |= it.uses
    hname = {inc: re.search(r'"([^"]+)"', inc).group(1) for inc in f['incs']}
    cands = [i for i in f['incs'] if hname[i].startswith('game/')]
    # a header whose own types the file uses, then any other one still needed for a used type
    keep = [i for i in cands if htypes.get(hname[i], ((), ()))[0] & need]
    given = set()
    for i in keep:
        given |= header_closure(hname[i], htypes)
    for i in cands:
        if i not in keep and header_closure(hname[i], htypes) & need - given:
            keep.append(i); given |= header_closure(hname[i], htypes)
    cands = keep
    for inc in f['incs']:
        if not hname[inc].startswith('game/') or inc in cands:
            out.append(inc)
    text = '\n'.join(out) + '\n\n'
    conf = f['row']['CONFIDENCE']
    hdr = headers.get(name)
    if hdr:
        text += hdr.rstrip()[:-2].rstrip() + '\n *\n' + HEADER_NOTE % conf + ' */\n'
    else:
        text += '/*\n' + HEADER_NOTE % conf + ' */\n'
    first = True
    for unit, it in f['items']:
        lead = it.lead
        if first:
            lead = '\n' + lead.lstrip('\n')
            if not lead.strip():
                lead = '\n'
            first = False
        code = it.text
        if it.kind == 'rodata':
            code = re.sub(r'asm/nonmatchings/game/\w+', 'asm/nonmatchings/game/' + name, code)
        text += lead + code
    return text.rstrip() + '\n'


# ---------------------------------------------------------------- splat

def rewrite_splat(rows, faddr, rev):
    lines = open(SPLAT, encoding='utf-8').read().split('\n')
    # comments of the old game entries, from the address-unit tree, with today's names
    names = {a: n for n, a in faddr.items() if not re.match(r'(func|D|jtbl)_', n)}
    old_comments = {}
    entry = re.compile(r'\s*- \[(0x[0-9A-Fa-f]+),\s*(\.?\w+),\s*([\w/]+)\]\s*(#.*)?$')
    old_text = subprocess.run(['git', '-C', ROOT, 'show', '%s:config/splat.yaml' % rev],
                              capture_output=True, text=True, check=True).stdout
    for l in old_text.split('\n'):
        m = entry.match(l)
        if m and m.group(3).startswith('game/') and m.group(4):
            com = re.sub(r'\b(func|D)_([0-9A-F]{8})\b',
                         lambda x: names.get(int(x.group(2), 16), x.group(0)), m.group(4))
            old_comments[(int(m.group(1), 16), m.group(2))] = com
    try:
        s = next(i for i, l in enumerate(lines) if l.strip() == 'subsegments:')
        e = next(i for i, l in enumerate(lines) if i > s and 'type: bss' in l)
    except StopIteration:
        raise SystemExit('splat.yaml: no subsegments block')
    old = lines[s + 1:e]
    keep = []   # (offset, order, [lines])
    pending = []
    for l in old:
        m = entry.match(l)
        if not m:
            pending.append(l); continue
        off, kind, name, com = int(m.group(1), 16), m.group(2), m.group(3), m.group(4)
        if name.startswith('game/'):
            if pending:
                keep.append((off, len(keep), pending)); pending = []
            continue
        keep.append((off, len(keep), pending + [l])); pending = []
    if pending:
        keep.append((1 << 40, len(keep), pending))
    ind = '      '
    for off, name in RODATA.items():
        com = '# ' + RODATA_COMMENTS[off] if off in RODATA_COMMENTS else old_comments.get((off, '.rodata'))
        keep.append((off, len(keep), ['%s- [0x%X, .rodata, game/%s]%s' % (ind, off, name, '  ' + com if com else '')]))
    starts = sorted((faddr[r['FIRST_FUNC']], r) for r in rows)
    for a, r in starts:
        off = a - ROM_BASE
        com = old_comments.get((off, 'c'))
        if com and 'object' in com:
            com = None
        com = '  # %s%s' % (r['CONFIDENCE'], '; ' + com[1:].strip() if com else '')
        keep.append((off, len(keep), ['%s- [0x%X, c, game/%s]%s' % (ind, off, r['FILE'][:-2], com)]))
    for off, name in SDATA.items():
        com = old_comments.get((off, '.sdata'))
        keep.append((off, len(keep), ['%s- [0x%X, .sdata, game/%s]%s' % (ind, off, name, '  ' + com if com else '')]))
    keep.sort()
    body = [l for _, _, ls in keep for l in ls]
    text = '\n'.join(lines[:s + 1] + body + lines[e:])
    text = text.replace(
        "# game/<addr> are the code between them, to be split into real translation units as evidence comes.",
        "# game/<name> are the original source files rebuilt from the evidence in docs/layout.md.")
    open(SPLAT, 'w', encoding='utf-8').write(text)


# ---------------------------------------------------------------- citations

CITE_PATHS = ['docs/naming.md', 'docs/discoveries.md', 'config/symbol_addrs.txt', 'tools/unit_check.sh',
              'tools/psyq/match.py']
CITE = re.compile(r'(src/game/)?\b(800[0-9A-F]{5})\.c\b( line [0-9]+)?|\bgame/(800[0-9A-F]{5})\b')
# Citations the line alone does not settle: (file, old unit, words of the line) -> new file.
from split_units_cites import CITE_OVERRIDES  # noqa: E402


def cite_tables(rows):
    faddr = elf_funcs()
    unit_files = OrderedDict()
    for r in rows:
        for u in r['UNIT'].split('+'):
            unit_files.setdefault(u, []).append(r['FILE'][:-2])
    texts = {}
    for r in rows:
        name = r['FILE'][:-2]
        path = os.path.join(SRC, name + '.c')
        texts[name] = open(path, encoding='utf-8').read() if os.path.exists(path) else ''
    defined = {name: {it.func for it in parse_c(t) if it.kind == 'func'} for name, t in texts.items()}
    used = {name: idents(strip_code(t)) for name, t in texts.items()}
    return unit_files, defined, used


def cite_one(path, line, unit, tables, why):
    unit_files, defined, used = tables
    cands = unit_files[unit]
    if len(cands) == 1:
        return cands[0]
    for (p, u, words), f in CITE_OVERRIDES.items():
        if p == path and u == unit and words in line:
            why.append('override')
            return f
    ids = [i for i in re.findall(r'[A-Za-z_]\w*', line) if '_' in i or i[:1].isupper()]
    if path == 'config/symbol_addrs.txt':
        ids = ids[:1]  # the symbol the line describes
    d = [f for f in cands if any(i in defined[f] for i in ids)]
    if len(d) == 1:
        why.append('defines')
        return d[0]
    score = {f: sum(1 for i in ids if i in used[f]) for f in (d or cands)}
    best = max(score.values())
    top = [f for f in score if score[f] == best]
    if best and len(top) == 1:
        why.append('uses')
        return top[0]
    why.append('UNRESOLVED')
    return unit


def rewrite_cites(text, path, tables, log=None):
    out = []
    for line in text.split('\n'):
        def sub(m):
            unit = m.group(2) or m.group(4)
            if unit not in tables[0]:
                return m.group(0)
            why = []
            f = cite_one(path, line, unit, tables, why)
            if log is not None:
                log.append('%s\t%s\t%s\t%s\t%s' % (path, unit, f, ','.join(why), line.strip()[:140]))
            if m.group(4):
                return 'game/' + f
            return (m.group(1) or '') + f + '.c'
        out.append(CITE.sub(sub, line))
    return '\n'.join(out)


def cmd_cite(args):
    tables = cite_tables(read_plan())
    log = []
    paths = list(CITE_PATHS) + sorted('include/game/' + n for n in os.listdir(os.path.join(ROOT, 'include/game')))
    paths += sorted('src/game/' + n for n in os.listdir(SRC))
    for p in paths:
        full = os.path.join(ROOT, p)
        text = open(full, encoding='utf-8').read()
        new = rewrite_cites(text, p, tables, log)
        if any('UNRESOLVED' in l for l in log):
            args.dry_run = True
        if new != text and not args.dry_run:
            open(full, 'w', encoding='utf-8').write(new)
    print('\n'.join(log))


# ---------------------------------------------------------------- docs

DOC_HEAD = """# Source file layout

The game code is split into the 70 source files the original programmers most likely had. Each file
holds its functions in address order; the files sit in link order between the Sony library objects.
The plan is `config/layout.tsv`; `tools/split_units.py docs` writes this page from it, and
`tools/split_units.py apply` replays the split from the address units of commit %s.

Confidence: **proven** means a Sony object sits on both sides of the file in .text, or the binary
rules out every other cut; **likely** means one end is proven and the other follows a class that ends
with its `X_GetVtbl`, with its vtable and data in class order; **guess** means the binary allows
another cut (each guess says which).

%d files: %d proven, %d likely, %d guess.

## Files in link order

| File | Functions | Confidence | Evidence |
| --- | --- | --- | --- |
"""

DOC_RODATA = """
## Rodata

A C file emits its strings and constants at parse time and its jump tables after the function
bodies; `INCLUDE_RODATA` lines place the symbols that are not migrated. Each `.rodata` entry of
`config/splat.yaml` names the file whose functions use it:

| ROM offset | Address | File |
| --- | --- | --- |
"""

DOC_TAIL = """
## How the boundaries were found

| Source | What it shows | Strength |
| --- | --- | --- |
| Sony objects between game code in .text | A file boundary on each side | Proven |
| Data order | .data, .sdata and the small .sbss statics follow link order, Sony objects included. Two symbols in inverted order bind their users into one file. | Proven, if a symbol is defined in a file that uses it |
| gp access | maspsx only reaches through gp the symbols a file defines or declares `.comm`. No gp symbol is reached through gp from two files, so all its gp users are one file. | Proven for .sdata; for .sbss it assumes no shared `.comm` |
| Rodata (cc1 2.6.3) | A string after a jump table starts a new file; a string used by a function placed before the jump table of an earlier function binds the range. | Proven where it applies |
| Equal literals | cc1 merges identical string literals in one file: two stored copies ("FONTICON") mean two files. | Proven |
| One class per file | FlatLight, Pad, Display, Bgm, App, Tim, Stream, ModelObject and SceneNode each sit alone between Sony objects. Classes end with `X_GetVtbl`, and vtables follow class order. | Convention: likely |
| Text padding | None between game functions | No signal |

`make check` cannot judge a layout: any cut matches as long as each file declares the gp symbols it
uses (rule 1 below). The 46 boundaries between two game functions rest on the evidence above; 23
are proven exactly by a Sony object.

The study corrected one older claim: the cut at 0x80058078 is not forced. `ETC\\ETCSE` and
`ETC\\HGRAPH.TIM` form one rodata object of 0x1C bytes, so DreamSys's first jump table at
0x80011788 is 8-aligned in its own object either way, and Graph_New, Graph_Init and
Graph_LoadImage..Graph_GetVtable read as one class file, `graph.c`.

## Rules for contributors

1. **A small global (8 bytes or less) reached through gp is declared without `extern` in every file
   that uses it**, as a tentative definition (`s32 g_fileBackend;`). cc1 emits `.comm`, maspsx
   reaches it through gp, and the linker merges it with the asm data. An `extern` gives `lui`
   accesses and shifts the whole executable. Never move such a declaration into a header with
   `extern`.
2. **An initialized gp record is defined, with its initializer, at the end of the file that uses
   it**: `g_viewDefaultScreenSize` in `view.c`, `g_bandPos` and `g_bandSize` in `scenery.c`. Their
   `.sdata` entries in `config/splat.yaml` name those files.
3. **No `static` variable while the data lives in asm**: it would allocate bytes in the C object and
   duplicate the data. File statics stay tentative definitions. A function is `static` when no other
   file calls it and no data points to it (275 are); one that a vtable or table in asm names stays
   global, or the link fails. `static` keeps the bytes but changes the relocations, so
   `tools/unit_check.sh --save` must run again after one is added or removed.
4. A file with rodata keeps its `.rodata` entry in `config/splat.yaml` (dot form, same name); an
   `INCLUDE_RODATA` path names `asm/nonmatchings/game/<file>`. After renaming a file, run
   `make split` twice: splat writes the `.s` only once the C file names it.
5. GCC 2.6.3 carries reload choices from one function to the next (`Render_ProjectTri` then
   `Render_ProjectQuad` in `render.c`): keep functions in address order inside a file.
6. **A file's header, `include/game/<file>.h`, declares what other files call or reference**: its
   functions in the form of their definition, parameter names included, and the non-gp globals other
   files read, with `extern`. heap.c, entity.c, menu.c, place.c, scene.c and stage.c add theirs at
   the end of the type header of the same name. A file includes the header of every file it calls
   and keeps no local copy; only Sony functions, gp globals (rule 1), forward declarations of its own
   helpers and the exceptions listed in [naming.md](naming.md#prototypes) stay in the file. The
   Makefile does not track headers: after editing one, `rm -rf build/src && make check` (not
   `make clean`, which also deletes the unit_check references in `build/ref`), then
   `tools/unit_check.sh` on every file that includes it.
7. **The build must stay shiftable: every address in it is a symbol the linker can move.** After
   `make check`, `python3 tools/rawscan.py` links the objects a second time with `.main` 0x10000
   higher and lists every word that did not move although it points into the executable (data
   pointers, `jal`, `lui` of an address). Read a field of the containing table in C
   (`g_entityRecords[i].link`, `g_ruleColors[rule - 10]`) instead of declaring a symbol in the
   middle of it, and give a string or a label that data points at its own entry in
   `config/symbol_addrs.txt` (Sony ones in the hand-kept block of `symbol_addrs.psyq.txt`), so that
   `linker/undefined_syms_auto.txt` keeps only `D_7FFFFF`. A label splat writes at an address that is
   not word aligned needs `defined:True`, or splat also writes it there as a fixed number. `tools/rawscan.py
   --max 0` must exit 0: the count is 0 since 2026-10-16. The last raw words were in files splat
   writes: Sony's startup (`asm/psyq/80011994.s`, written as `.word` because the function ends in a
   table) and the header's initial pc and .text size. `make split` runs `tools/postsplit.py` after
   splat to write them as symbols, and `_gp` comes from `ld_gp_expression` in `config/splat.yaml`.
   A build with 0x100 bytes of code added before `main` plays like the retail game (logos, title, a
   dream, its links and the fall, pixel for pixel).
"""


def write_docs(rows):
    faddr = elf_funcs()
    text_lines = open(SPLAT, encoding='utf-8').read().split('\n')
    entry = re.compile(r'\s*- \[(0x[0-9A-Fa-f]+),\s*(\.?\w+),\s*([\w/]+)\]\s*(#\s*(.*))?$')
    order = []
    for l in text_lines:
        m = entry.match(l)
        if m and m.group(2) in ('c', 'asm'):
            order.append((int(m.group(1), 16), m.group(3), (m.group(5) or '').strip()))
    byfile = {r['FILE'][:-2]: r for r in rows}
    conf = [r['CONFIDENCE'] for r in rows]
    out = DOC_HEAD % (DEFAULT_REV, len(rows), conf.count('proven'), conf.count('likely'), conf.count('guess'))
    for off, name, com in order:
        kind, base = name.split('/')
        if kind == 'psyq':
            out += '| *%s* | Sony: %s | | |\n' % (name, com.split(';')[0] or 'library code')
            continue
        r = byfile[base]
        funcs = r['FIRST_FUNC'] if r['FIRST_FUNC'] == r['LAST_FUNC'] else '%s..%s' % (r['FIRST_FUNC'], r['LAST_FUNC'])
        out += '| [`%s`](../src/game/%s) | `%s` @0x%08X | %s | %s |\n' % (
            r['FILE'], r['FILE'], funcs, faddr[r['FIRST_FUNC']], r['CONFIDENCE'], r['evidence'])
    out += DOC_RODATA
    for off, name in RODATA.items():
        out += '| 0x%X | 0x%08X | `%s.c` |\n' % (off, off + ROM_BASE, name)
    out += DOC_TAIL
    open(os.path.join(ROOT, 'docs/layout.md'), 'w', encoding='utf-8').write(out)
    print('wrote docs/layout.md')


def cmd_apply(args):
    rows = read_plan()
    files, unit_headers, htypes = build_files(rows, args.rev)
    if args.dump_headers:
        for u, h in unit_headers.items():
            print('=== %s -> %s' % (u, [n for n, f in files.items() if u in f['units']]))
            print(h)
        return
    from split_units_headers import HEADERS
    headers = {}
    for name in files:
        if name in HEADERS:
            headers[name] = HEADERS[name]
        elif all(unit_headers[u] is None for u in files[name]['units']):
            headers[name] = None
        elif len(files[name]['units']) == 1 and sum(1 for g in files.values() if g['units'] == files[name]['units']) == 1:
            headers[name] = unit_headers[files[name]['units'][0]]
        else:
            raise SystemExit('no header text for %s.c (tools/split_units_headers.py)' % name)
    faddr = elf_funcs()
    for name, f in files.items():
        open(os.path.join(SRC, name + '.c'), 'w', encoding='utf-8').write(render(name, f, headers, htypes))
    tables = cite_tables(rows)
    for name in files:
        path = os.path.join(SRC, name + '.c')
        text = open(path, encoding='utf-8').read()
        log = []
        open(path, 'w', encoding='utf-8').write(rewrite_cites(text, 'src/game/%s.c' % name, tables, log))
        bad = [l for l in log if 'UNRESOLVED' in l]
        if bad:
            raise SystemExit('unresolved citations (tools/split_units_cites.py):\n' + '\n'.join(bad))
    # menu.c, string_list.c and graph.c join units that described the same class differently: their
    # declarations were reconciled once by hand, kept here as a patch.
    fix = os.path.join(ROOT, 'tools/split_units.fixups.patch')
    if not args.no_fixups:
        subprocess.run(['patch', '-p1', '-s', '--no-backup-if-mismatch', '-d', ROOT, '-i', fix], check=True)
    olds = sorted({u for r in rows for u in r['UNIT'].split('+')})
    for u in olds:
        p = os.path.join(SRC, u + '.c')
        if os.path.exists(p):
            os.remove(p)
    rewrite_splat(rows, faddr, args.rev)
    print('wrote %d files, removed %d units' % (len(files), len(olds)))


def main():
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest='cmd', required=True)
    a = sub.add_parser('apply')
    a.add_argument('--rev', default=DEFAULT_REV)
    a.add_argument('--dump-headers', action='store_true')
    a.add_argument('--no-fixups', action='store_true', help='skip the hand reconciliation patch')
    sub.add_parser('docs')
    c = sub.add_parser('cite')
    c.add_argument('--dry-run', action='store_true')
    args = ap.parse_args()
    if args.cmd == 'apply':
        cmd_apply(args)
    elif args.cmd == 'cite':
        cmd_cite(args)
    else:
        write_docs(read_plan())


if __name__ == '__main__':
    main()
