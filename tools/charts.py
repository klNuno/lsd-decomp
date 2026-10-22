#!/usr/bin/env python3
"""Draw the SVG charts of docs/discoveries.md. Python stdlib only.

Usage: python3 tools/charts.py [--check] [--out DIR]

Every number below comes from a row of docs/discoveries.md or from the
executable tables it cites. With --check (and extract/SLPS_015.56 present) the
script re-reads those tables and stops if a constant here disagrees.

Output: docs/img/chart-*.svg, or DIR/chart-*.svg with --out. Each SVG carries its own card background and a
prefers-color-scheme block, so it reads on GitHub's light and dark themes.
"""
import os
import struct
import sys
from html import escape

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
OUT = os.path.join(ROOT, "docs", "img")
if "--out" in sys.argv:
    OUT = os.path.abspath(sys.argv[sys.argv.index("--out") + 1])
EXE = os.path.join(ROOT, "extract", "SLPS_015.56")

# g_stageTimeLimits: seconds per starting stage, stages 0 to 13 (Spawn_PickFromMood)
STAGE_SECONDS = [240, 180, 480, 420, 120, 600, 60, 300, 240, 300, 240, 180, 120, 480]
# g_specialDays: the 42 special-day entries, in table order (Day_FindSpecial)
SPECIAL_DAYS = [2, 15, 43, 81, 120, 126, 202, 259, 267, 284, 308, 328, 358,
                7, 14, 21, 28, 35, 42, 49, 56, 63, 70, 77, 84, 91, 98, 105, 112,
                119, 126, 134, 141, 148, 155, 162, 169, 176, 183, 190, 197, 204]
N_FIXED = 13
# Mood points (x, y) in -9..9 that no stage chunk carries (tools/research/moodmap.py)
NO_START = [(-9, -9), (-9, -8), (-9, -7), (-9, -6), (-9, 6), (-9, 7), (-9, 8), (-9, 9),
            (-8, -9), (-8, -8), (-8, -7), (-8, 6), (-8, 7), (-8, 8), (-8, 9),
            (-7, -9), (-7, -8), (-7, -7), (-7, 7), (-7, 8), (-7, 9),
            (-6, -9), (-6, -8), (-6, 8), (-6, 9), (0, 3), (5, 7),
            (6, -9), (6, -8), (6, 8), (6, 9), (7, -9), (7, -8), (7, -7), (7, 8), (7, 9),
            (8, -9), (8, -8), (8, -7), (8, 6), (8, 7), (8, 8), (8, 9),
            (9, -9), (9, -8), (9, -7), (9, -6), (9, 6), (9, 7), (9, 8), (9, 9)]


def check():
    """Compare the constants with the executable's tables."""
    if not os.path.exists(EXE):
        sys.exit("no %s: run make check-disk first" % EXE)
    d = open(EXE, "rb").read()
    base = 0x80010000 - 0x800

    def h(a):
        return struct.unpack_from("<h", d, a - base)[0]

    def w(a):
        return struct.unpack_from("<I", d, a - base)[0]

    assert [h(0x80087F14 + 2 * i) for i in range(14)] == STAGE_SECONDS
    assert [h(0x80088CCC + 2 * i) for i in range(42)] == SPECIAL_DAYS

    def sb(v):
        return v - 256 if v > 127 else v

    seen = set()
    for st in range(14):
        cols, rows = h(0x800861D4 + 8 * st), h(0x800861D6 + 8 * st)
        p = w(0x80086590 + 4 * st)
        for i in range(rows * cols):
            v = struct.unpack_from("<H", d, p - base + 2 * i)[0]
            seen.add((sb(v & 0xFF), sb(v >> 8)))
    grid = [(x, y) for x in range(-9, 10) for y in range(-9, 10)]
    assert sorted(p for p in grid if p not in seen) == sorted(NO_START)
    print("tables match the executable")


# Palette: reference dataviz palette, light and dark steps of the same hues.
STYLE = """
<style>
  .card { fill: #fcfcfb; stroke: rgba(11,11,11,0.10); }
  .t1 { fill: #0b0b0b; } .t2 { fill: #52514e; } .t3 { fill: #6d6c67; }
  .grid { stroke: #e1e0d9; } .axis { stroke: #c3c2b7; }
  .s1 { fill: #2a78d6; } .s2 { fill: #eb6834; } .s1s { stroke: #2a78d6; } .s2s { stroke: #eb6834; }
  .s3 { fill: #1baf7a; } .s4 { fill: #eda100; }
  .mute { fill: #e1e0d9; } .hole { fill: #fcfcfb; stroke: #eb6834; }
  .gap { stroke: #fcfcfb; }
  @media (prefers-color-scheme: dark) {
    .card { fill: #1a1a19; stroke: rgba(255,255,255,0.10); }
    .t1 { fill: #f0efec; } .t2 { fill: #c3c2b7; } .t3 { fill: #a3a29b; }
    .grid { stroke: #2c2c2a; } .axis { stroke: #383835; }
    .s1 { fill: #3987e5; } .s2 { fill: #d95926; } .s1s { stroke: #3987e5; } .s2s { stroke: #d95926; }
    .s3 { fill: #199e70; } .s4 { fill: #c98500; }
    .mute { fill: #383835; } .hole { fill: #1a1a19; stroke: #d95926; }
    .gap { stroke: #1a1a19; }
  }
  text { font-family: system-ui, -apple-system, "Segoe UI", sans-serif; }
</style>
"""


class Svg:
    def __init__(self, w, h, title, desc):
        self.w, self.h = w, h
        self.parts = []
        self.title, self.desc = title, desc

    def add(self, s):
        self.parts.append(s)

    def text(self, x, y, s, cls="t2", size=12, anchor="start", weight="normal"):
        self.add('<text x="%g" y="%g" class="%s" font-size="%g" text-anchor="%s" font-weight="%s">%s</text>'
                 % (x, y, cls, size, anchor, weight, escape(s)))

    def rect(self, x, y, w, h, cls, rx=0, tip=None):
        t = "<title>%s</title>" % escape(tip) if tip else ""
        self.add('<rect x="%g" y="%g" width="%g" height="%g" rx="%g" class="%s">%s</rect>'
                 % (x, y, w, h, rx, cls, t))

    def line(self, x1, y1, x2, y2, cls, width=1, dash=None):
        d = ' stroke-dasharray="%s"' % dash if dash else ""
        self.add('<line x1="%g" y1="%g" x2="%g" y2="%g" class="%s" stroke-width="%g"%s/>'
                 % (x1, y1, x2, y2, cls, width, d))

    def header(self, title, subtitle):
        self.text(24, 34, title, "t1", 17, weight="600")
        self.text(24, 56, subtitle, "t2", 13)

    def caption(self, lines):
        y = self.h - 18 - 17 * (len(lines) - 1)
        for s in lines:
            self.text(24, y, s, "t3", 12)
            y += 17

    def save(self, name):
        body = "\n".join(self.parts)
        svg = ('<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 %d %d" width="%d" height="%d" '
               'role="img" aria-labelledby="t d">\n<title id="t">%s</title>\n<desc id="d">%s</desc>\n%s\n'
               '<rect x="0.5" y="0.5" width="%g" height="%g" rx="10" class="card"/>\n%s\n</svg>\n'
               % (self.w, self.h, self.w, self.h, escape(self.title), escape(self.desc), STYLE,
                  self.w - 1, self.h - 1, body))
        path = os.path.join(OUT, name)
        with open(path, "w") as f:
            f.write(svg)
        print("wrote", os.path.relpath(path, ROOT))


def bar_path(x, y0, w, h, r=4):
    """Vertical bar from baseline y0 up by h, top corners rounded."""
    r = min(r, w / 2, h)
    top = y0 - h
    return ("M%g,%g V%g Q%g,%g %g,%g H%g Q%g,%g %g,%g V%g Z"
            % (x, y0, top + r, x, top, x + r, top, x + w - r, x + w, top, x + w, top + r, y0))


def chart_dream_length():
    W, H = 760, 400
    s = Svg(W, H, "How long a dream lasts, by starting stage",
            "Bar chart of the time limit for each of the 14 starting stages, from 1 to 10 minutes.")
    s.header("How long a dream lasts", "Time limit set when the dream starts, by the stage you wake up in")
    left, right, top, base = 70, W - 24, 90, H - 92
    ymax = 10
    step = (right - left) / 14
    bw = step * 0.62
    for m in range(0, ymax + 1, 2):
        y = base - (base - top) * m / ymax
        s.line(left, y, right, y, "grid" if m else "axis")
        s.text(left - 10, y + 4, "%d min" % m if m else "0", "t3", 11, "end")
    for i, sec in enumerate(STAGE_SECONDS):
        mins = sec / 60
        x = left + step * i + (step - bw) / 2
        hgt = (base - top) * mins / ymax
        s.add('<path d="%s" class="s1"><title>Stage %d: %d s (%g min)</title></path>'
              % (bar_path(x, base, bw, hgt), i, sec, mins))
        s.text(x + bw / 2, base - hgt - 6, "%g" % mins, "t2", 11, "middle")
        s.text(x + bw / 2, base + 17, str(i), "t2", 11, "middle")
    s.text((left + right) / 2, base + 36, "Starting stage (index in the game's table)", "t3", 12, "middle")
    s.caption(["Stage 0, where day 1 starts, gives 4 minutes; stage 5 gives the longest dream (10), stage 6 the shortest (1).",
               "Nominal time: the limit is stored as seconds x 15 ticks; in the emulator a tick was one game frame."])
    s.save("chart-dream-length.svg")


def chart_special_days():
    W, H = 760, 290
    s = Svg(W, H, "The 42 special days in a year",
            "Calendar strip of 365 days in columns of 7. 13 fixed special days scattered through the year; "
            "29 weekly entries: every 7th day from 7 to 126, then from 134 to 204 (133 skipped); 126 is listed twice.")
    s.header("Special days in a year", "365 days, one column per week of 7 days, read top to bottom then left to right")
    fixed = set(SPECIAL_DAYS[:N_FIXED])
    weekly = set(SPECIAL_DAYS[N_FIXED:])
    left, top, cell, gap = 46, 104, 11.6, 1.6
    rows = 7
    for d in range(1, 366):
        c, r = (d - 1) // rows, (d - 1) % rows
        x, y = left + c * (cell + gap), top + r * (cell + gap)
        if d in fixed and d in weekly:
            cls, tip = "s2", "Day %d: fixed and weekly (listed twice)" % d
        elif d in fixed:
            cls, tip = "s2", "Day %d: fixed special day" % d
        elif d in weekly:
            cls, tip = "s1", "Day %d: weekly special day" % d
        else:
            cls, tip = "mute", "Day %d" % d
        s.rect(x, y, cell, cell, cls, 2, tip)
        if d in fixed:
            s.text(x + cell / 2, top - 8 if r < 4 else top + rows * (cell + gap) + 13,
                   str(d), "t2", 10, "middle")
    # row labels: day of the week counted from day 1
    for r in (0, 6):
        s.text(left - 8, top + r * (cell + gap) + cell - 2, "%d" % (r + 1), "t3", 10, "end")
    yb = top + rows * (cell + gap)
    # week ruler under the strip
    for c in (0, 13, 26, 39):
        x = left + c * (cell + gap)
        s.text(x, yb + 32, "day %d" % (c * 7 + 1), "t3", 10)
    s.text(left + 53 * (cell + gap) - gap, yb + 32, "day 365", "t3", 10, "end")
    xg = left + 18 * (cell + gap) + cell / 2
    s.line(xg, yb + 2, xg, yb + 18, "axis", 1)
    s.text(xg + 4, yb + 18, "133 skipped", "t3", 10)
    ly = 74
    s.rect(24, ly - 9, 10, 10, "s2", 2)
    s.text(40, ly, "13 fixed days (126 is also a weekly one)", "t2", 12)
    s.rect(300, ly - 9, 10, 10, "s1", 2)
    s.text(316, ly, "29 weekly entries: 7 to 126, then 134 to 204", "t2", 12)
    s.caption(["42 entries, 41 different days. The weekly run skips 133 and goes on one day later, so it jumps rows.",
               "Nothing weekly after day 204: the rest of the year only has the fixed days 259 to 358."])
    s.save("chart-special-days.svg")


def chart_mood_grid():
    W, H = 560, 660
    s = Svg(W, H, "Graph points with no start place",
            "19 by 19 grid of graph points from -9 to 9 on each axis. 310 points lead to a place, 51 do not: "
            "49 in the four corners plus (0, 3) and (5, 7).")
    s.header("Graph points with no start place", "Where yesterday's graph point sends tomorrow's dream")
    holes = set(NO_START)
    cell, gap = 22, 2
    left, top = 78, 112
    for y in range(9, -10, -1):
        for x in range(-9, 10):
            px = left + (x + 9) * (cell + gap)
            py = top + (9 - y) * (cell + gap)
            if (x, y) in holes:
                s.add('<rect x="%g" y="%g" width="%g" height="%g" rx="3" class="hole" stroke-width="2">'
                      '<title>(%d, %d): no place, the dream falls back to stage 1</title></rect>'
                      % (px + 1, py + 1, cell - 2, cell - 2, x, y))
            else:
                s.rect(px, py, cell, cell, "s1", 3, "(%d, %d): a place starts here" % (x, y))
    # day 1 marker on (0, 0)
    cx = left + 9 * (cell + gap) + cell / 2
    cy = top + 9 * (cell + gap) + cell / 2
    s.add('<circle cx="%g" cy="%g" r="5" class="card" stroke-width="0"/>' % (cx, cy))
    for v in (-9, 0, 9):
        px = left + (v + 9) * (cell + gap) + cell / 2
        s.text(px, top + 19 * (cell + gap) + 14, str(v), "t3", 11, "middle")
        py = top + (9 - v) * (cell + gap) + cell / 2 + 4
        s.text(left - 8, py, str(v), "t3", 11, "end")
    s.text(left + 19 * (cell + gap) / 2, top + 19 * (cell + gap) + 32, "graph x", "t3", 12, "middle")
    s.add('<text transform="translate(%g,%g) rotate(-90)" class="t3" font-size="12" text-anchor="middle">graph y</text>'
          % (left - 34, top + 19 * (cell + gap) / 2))
    ly = 82
    s.rect(24, ly - 10, 12, 12, "s1", 3)
    s.text(42, ly, "310 points lead to a place", "t2", 12)
    s.add('<rect x="225" y="%g" width="10" height="10" rx="2" class="hole" stroke-width="2"/>' % (ly - 9))
    s.text(242, ly, "51 lead nowhere: always stage 1", "t2", 12)
    s.rect(444, ly - 10, 12, 12, "s1", 3)
    s.add('<circle cx="450" cy="%g" r="3" class="card" stroke-width="0"/>' % (ly - 4))
    s.text(466, ly, "day 1 (0, 0)", "t2", 12)
    s.caption(["The 49 corner points plus (0, 3) and (5, 7) have no matching place.",
               "A dream after such a day starts on stage 1, at one of its 3 spawn points."])
    s.save("chart-mood-grid.svg")


def chart_textures():
    W, H = 760, 360
    s = Svg(W, H, "Texture sets possible on each day of the 40-day cycle",
            "Step chart: days 1 to 10 of each 40-day cycle allow only set A, 11 to 20 A or B, "
            "21 to 30 A to C, 31 to 40 A to D.")
    s.header("Texture sets in the 40-day cycle", "How many texture sets a place can load, by day of the cycle")
    left, right, top, base = 70, W - 24, 92, H - 96
    for n in range(0, 5):
        y = base - (base - top) * n / 4
        s.line(left, y, right, y, "grid" if n else "axis")
        s.text(left - 10, y + 4, str(n), "t3", 11, "end")
    s.add('<text transform="translate(%g,%g) rotate(-90)" class="t3" font-size="12" text-anchor="middle">sets possible</text>'
          % (left - 34, (top + base) / 2))
    dw = (right - left) / 40
    letters = "ABCD"
    for d in range(1, 41):
        n = (d - 1) // 10 + 1
        x = left + (d - 1) * dw
        seg = (base - top) / 4
        for k in range(n):
            y = base - (k + 1) * seg
            s.rect(x + 1, y + 1, dw - 2, seg - 2, "s%d" % (k + 1), 2,
                   "Cycle day %d: set %s (1 in %d)" % (d, letters[k], n))
    for b in range(4):
        x = left + (b * 10 + 5) * dw
        s.text(x, base + 18, "days %d to %d" % (b * 10 + 1, b * 10 + 10), "t2", 11, "middle")
        s.text(x, top - 8 + (3 - b) * (base - top) / 4, "%s" % (" ".join(letters[:b + 1])), "t2", 12, "middle", "600")
    s.text((left + right) / 2, base + 38, "Day of the 40-day cycle (day 41 starts the next one)", "t3", 12, "middle")
    s.caption(["Each set allowed on a day is equally likely: 1 in 2 on days 11 to 20, 1 in 4 on days 31 to 40.",
               "The cycle restarts at day 41, 81 and so on; days 361 to 365 count as days 1 to 5 and always load A."])
    s.save("chart-texture-cycle.svg")


def chart_link_odds():
    W, H = 760, 380
    s = Svg(W, H, "Odds of the next place on a random link, example from stage 2",
            "Bar chart: from main stage 2, stage 3 has 2 chances in 6, stages 0, 1, 4 and 5 have 1 in 6 each, "
            "stage 2 itself has none.")
    s.header("Where a random link sends you", "Example: you are on main stage 2 and touch a wall that links at random")
    cur = 2
    odds = [0 if st == cur else 2 if st == (cur + 1) % 6 else 1 for st in range(6)]
    left, right, top, base = 84, W - 24, 96, H - 92
    for n in range(0, 3):
        y = base - (base - top) * n / 2
        s.line(left, y, right, y, "grid" if n else "axis")
        s.text(left - 10, y + 4, "%d in 6" % n if n else "0", "t3", 11, "end")
    step = (right - left) / 6
    bw = step * 0.55
    for st, o in enumerate(odds):
        x = left + step * st + (step - bw) / 2
        cls = "s2" if o == 2 else "s1"
        if o:
            hgt = (base - top) * o / 2
            s.add('<path d="%s" class="%s"><title>Stage %d: %d in 6</title></path>'
                  % (bar_path(x, base, bw, hgt), cls, st, o))
            s.text(x + bw / 2, base - hgt - 6, "%d in 6" % o, "t2", 11, "middle")
        else:
            s.text(x + bw / 2, base - 8, "you are here", "t3", 11, "middle")
        s.text(x + bw / 2, base + 18, "stage %d" % st, "t2", 11, "middle")
    s.text((left + right) / 2, base + 38, "Next stage", "t3", 12, "middle")
    s.caption(["The game rolls a 6-sided die over the main stages 0 to 5. Rolling your own stage moves you one stage up",
               "(5 wraps to 0), so the stage after yours comes up twice as often as each of the other four."])
    s.save("chart-link-odds.svg")


if __name__ == "__main__":
    if "--check" in sys.argv:
        check()
    assert len(SPECIAL_DAYS) == 42 and len(NO_START) == 51 and len(STAGE_SECONDS) == 14
    os.makedirs(OUT, exist_ok=True)
    chart_dream_length()
    chart_special_days()
    chart_mood_grid()
    chart_textures()
    chart_link_odds()
