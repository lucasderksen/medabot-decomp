"""tools/try_merge.py NAME FILE CFLAGS: rename each local B to another local A of the same declared type (drop B's
declaration), one pair at a time; then greedily repeat. Check that A and B have disjoint lifetimes by hand."""
import sys,subprocess,re
import os
from pathlib import Path
from c_source import function_body_lines
ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/"build"/"sweeps"; OUT.mkdir(parents=True,exist_ok=True)
name,path,cflags=sys.argv[1],sys.argv[2],sys.argv[3]
tmp=str(OUT/('mg_tmp_%s.c'%name))
DECL=re.compile(r'^\s+((?:const\s+|volatile\s+)*(?:u8|u16|u32|s8|s16|s32|struct \w+|union \w+)\s*\**)\s*(\w+)\s*;\s*$')
def score(lines):
    open(tmp,'w').write('\n'.join(lines))
    o=subprocess.run(['python','tools/try_draft.py',name,tmp,'--cflags='+cflags],cwd=ROOT,capture_output=True,text=True).stdout
    if re.search(r'^MATCH',o,re.M): return 0
    m=re.search(r'(\d+) reference bytes, (\d+) candidate bytes, (\d+) differing',o)
    if not m: return 9999
    return int(m.group(3))+(0 if m.group(1)==m.group(2) else 500)
lines=open(path).read().split('\n')
best=score(lines); print('base',best,flush=True)
while best:
    start,end=function_body_lines('\n'.join(lines),name)
    vs=[(i,re.sub(r'\s+','',m.group(1)),m.group(2)) for i,l in enumerate(lines) if start < i < end for m in [DECL.match(l)] if m]
    imp=None
    for i,ta,a in vs:
        for j,tb,b in vs:
            if a==b: continue
            t=[x for k,x in enumerate(lines) if k!=j]
            t=[re.sub(r'(?<![\w.>])%s\b'%b,a,x) for x in t]
            s=score(t); print(s,b,'->',a,'same' if ta==tb else 'cross',flush=True)
            if s<best: best,imp=s,(b,a,t)
            if s==0: break
        if best==0: break
    if not imp: break
    lines=imp[2]; open(OUT/('mg_best_%s.c'%name),'w').write('\n'.join(lines)); print('take',best,imp[0],'->',imp[1],flush=True)
print('final',best)
