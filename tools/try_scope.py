"""tools/try_scope.py NAME FILE CFLAGS: greedily move each single-variable declaration into any other block
that encloses all of its uses (inner or outer). Winners must be checked for semantics by hand
(a variable moved into a loop body must not carry a value between iterations)."""
import sys,subprocess,re
import os
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/"build"/"sweeps"; OUT.mkdir(parents=True,exist_ok=True)
name,path,cflags=sys.argv[1],sys.argv[2],sys.argv[3]
DECL=re.compile(r'^\s+(?:const\s+|volatile\s+)*(?:u8|u16|u32|s8|s16|s32|vu16|struct \w+|union \w+)(?:\s+const)?\s*\**\s*(\w+)(\s*\[[^\]]*\])*\s*(=\s*[^;]+)?;\s*$')
tmp=str(OUT/('sc_tmp_%s.c'%name))
def score(lines):
    open(tmp,'w').write('\n'.join(lines))
    o=subprocess.run(['python','tools/try_draft.py',name,tmp,'--cflags='+cflags],cwd=ROOT,capture_output=True,text=True).stdout
    if re.search(r'^MATCH',o,re.M): return 0
    m=re.search(r'(\d+) reference bytes, (\d+) candidate bytes, (\d+) differing',o)
    if not m: return 9999
    return int(m.group(3))+(0 if m.group(1)==m.group(2) else 500)
def analyse(lines):
    start=next(i for i,l in enumerate(lines) if re.match(r'^\w.*\b%s\s*\('%name,l) and not l.rstrip().endswith(';'))
    blocks=[];stack=[];end=None
    for i in range(start,len(lines)):
        code=re.sub(r'//.*','',lines[i])
        for ch in code:
            if ch=='{': stack.append(i)
            elif ch=='}':
                o=stack.pop(); blocks.append((o,i))
                if not stack: end=i; break
        if end is not None: break
    return start,end,blocks
def candidates(lines):
    start,end,blocks=analyse(lines)
    out=[]
    for i in range(start,end):
        m=DECL.match(lines[i])
        if not m: continue
        v=m.group(1)
        if sum(1 for j in range(start,end) if DECL.match(lines[j]) and DECL.match(lines[j]).group(1)==v)>1: continue
        uses=[j for j in range(start,end+1) if j!=i and re.search(r'\b%s\b'%v,lines[j])]
        if not uses: continue
        cur=max((b for b in blocks if b[0]<i<b[1]),key=lambda b:b[0])
        for b in blocks:
            if b==cur or not all(b[0]<u<b[1] for u in uses): continue
            if not (b[0]<i<b[1]) and not (cur[0]>b[0] and cur[1]<b[1]) and not (b[0]>cur[0] and b[1]<cur[1]): continue
            t=list(lines); line=t.pop(i); ins=b[0]+1 if b[0]<i else b[0]
            t.insert(ins,line); out.append(((v,b[0]+1),t))
    return out
lines=open(path).read().split('\n')
best=score(lines); print('base',best,flush=True)
while best:
    improved=None
    for desc,t in candidates(lines):
        s=score(t); print(s,desc,flush=True)
        if s<best: best,improved=s,(desc,t)
        if s==0: break
    if not improved: break
    lines=improved[1]; open(OUT/('sc_best_%s.c'%name),'w').write('\n'.join(lines)); print('take',best,improved[0],flush=True)
print('final',best)
