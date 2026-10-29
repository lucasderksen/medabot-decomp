"""tools/try_reuse.py NAME FILE LO HI CFLAGS: (1) replace each integer constant on lines LO..HI by (v = K) for each scalar local v;
(2) rename each scalar local to another of the same function (merge). Check semantics of winners by hand."""
import sys,subprocess,re
import os
from pathlib import Path
from c_source import function_body_lines
ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/"build"/"sweeps"; OUT.mkdir(parents=True,exist_ok=True)
name,path,lo,hi,cflags=sys.argv[1],sys.argv[2],int(sys.argv[3]),int(sys.argv[4]),sys.argv[5]
tmp=str(OUT/('ru_tmp_%s.c'%name))
def score(lines):
    open(tmp,'w').write('\n'.join(lines))
    o=subprocess.run(['python','tools/try_draft.py',name,tmp,'--cflags='+cflags],cwd=ROOT,capture_output=True,text=True).stdout
    if re.search(r'^MATCH',o,re.M): return 0
    m=re.search(r'(\d+) reference bytes, (\d+) candidate bytes, (\d+) differing',o)
    if not m: return 9999
    return int(m.group(3))+(0 if m.group(1)==m.group(2) else 500)
src=open(path).read().split('\n')
start,end=function_body_lines('\n'.join(src),name)
DECL=re.compile(r'^\s+(?:volatile\s+)?(u8|u16|u32|s8|s16|s32)\s+(\w+)\s*(=\s*[^;]+)?;\s*$')
vars_=[(i,m.group(2)) for i,l in enumerate(src) if start < i < end for m in [DECL.match(l)] if m]
base=score(src); print('base',base,flush=True); best=base
def report(s,desc,t):
    global best
    print(s,desc,flush=True)
    if s<best:
        best=s; open(OUT/('ru_best_%s.c'%name),'w').write('\n'.join(t)); print('improved',s,desc,flush=True)
    if s==0: sys.exit()
for li in range(max(start+1,lo-1),min(end,hi)):
    l=src[li]
    if DECL.match(l): continue
    for m in re.finditer(r'(?<![\w.])(0x[0-9A-Fa-f]+|\d+)(?![\w.])',l):
        if l[:m.start()].rstrip().endswith('[') : pass
        for _,v in vars_:
            t=list(src); t[li]=l[:m.start()]+'(%s = %s)'%(v,m.group(1))+l[m.end():]
            report(score(t),(li+1,m.group(1),v),t)
for i,a in vars_:
    for j,b in vars_:
        if a==b: continue
        t=[x for k,x in enumerate(src) if k!=j]
        t=[re.sub(r'(?<![\w.>])%s\b'%b,a,x) for x in t]
        report(score(t),('merge',b,'->',a),t)
print('final',best)
