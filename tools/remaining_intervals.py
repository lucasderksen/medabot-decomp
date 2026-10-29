"""List unmatched code-region intervals (copied gaps and NONMATCH functions) and push-starts in a ROM range.

    python tools/remaining_intervals.py 0x5C000 0x69000
"""
import json,struct,sys
lo,hi=(int(x,0)&0xFFFFFF for x in sys.argv[1:3])
c=[s for s in json.load(open('config/segments.json')) if not s.get('nonmatching')]; rom=open('baserom.gba','rb').read()
iv=sorted((int(s['start'],16),int(s['end'],16)) for s in c); p=0; gaps=[]
for a,b in iv:
    if a>p: gaps.append((p,a))
    p=max(p,b)
tot=0
for a,b in gaps:
    a,b=max(a,lo),min(b,hi,0x7E858)
    if a>=b: continue
    starts=[x for x in range(a,b,2) if (struct.unpack_from('<H',rom,x)[0]&0xFF00)==0xB500]
    tot+=b-a
    print(f"{0x08000000+a:08X}-{0x08000000+b:08X} {b-a:6d} bytes  push-starts: "+" ".join(f"{0x08000000+x:08X}" for x in starts[:8]))
print("total",tot)
