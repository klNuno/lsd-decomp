"""Print a vtable of the built executable slot by slot with the symbol names of config/symbol_addrs.txt (include/game/task.h, where the vtable contents come from).
Run after make check: python3 tools/research/vt.py ADDR:SIZE [...], hex, e.g. vt.py 80086668:80 for the Task vtable."""
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
d = open(os.path.join(ROOT, 'build', 'SLPS_015.56'), 'rb').read()
taddr=0x80010000
def w(a): return struct.unpack_from('<I',d,0x800+a-taddr)[0]
sym={}
for line in open(os.path.join(ROOT, 'config', 'symbol_addrs.txt')):
    m=re.match(r'\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)',line)
    if m: sym[int(m.group(2),16)]=m.group(1)
def name(v): return sym.get(v, 'func_%08X'%v if 0x80010000<=v<0x80070000 else hex(v))
for arg in sys.argv[1:]:
    base,n=arg.split(':'); base=int(base,16); n=int(n,16)
    print('== vtable',hex(base))
    for off in range(0,n,4):
        print('  %03X %s'%(off,name(w(base+off))))
