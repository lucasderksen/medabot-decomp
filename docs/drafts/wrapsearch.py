"""Parallel do/while(0) wrap search for sub_0805424C (lean_c helper).

usage (from the worktree root, after one try_draft of the draft):
    python docs/drafts/wrapsearch.py DRAFT.c [MAXSPAN] [JOBS]
Scores each single wrap/unwrap with casediff rows, then combines the best
disjoint ones into DRAFT.c.best.c. Wraps containing break/continue/goto are skipped.
"""
import json, os, re, subprocess, sys, shutil
from concurrent.futures import ThreadPoolExecutor
R=os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
S=os.path.dirname(os.path.abspath(__file__))
name='sub_0805424C'
draft=f'{R}/build/m2c/{name}'
cand=open(f'{draft}/candidate.c',encoding='utf-8').read()
marker=f"#define {name} m2c_{name}\n"
prefix=cand.split(marker,1)[0]+marker+"\n"
spec=json.load(open(f'{draft}/spec.json'))
spec['cflags']=['-w','-fprologue-bugfix']
WD=f'{R}/build/wv'
os.makedirs(WD,exist_ok=True)

def score(code, tag):
    d=f'{WD}/{tag}'
    os.makedirs(d,exist_ok=True)
    src=f'{d}/candidate.c'
    # m2c_macros.h include path: copy header
    open(src,'w',encoding='utf-8').write(prefix+code)
    shutil.copy(f'{draft}/m2c_macros.h', f'{d}/m2c_macros.h')
    sp=dict(spec); sp['source']=os.path.relpath(src,R).replace(os.sep,'/')
    json.dump(sp,open(f'{d}/spec.json','w'))
    r=subprocess.run([sys.executable,'tools/match.py',f'{d}/spec.json','--output-dir',f'{d}/match'],cwd=R,capture_output=True,text=True)
    elf=f'{d}/match/candidate.elf'
    if not os.path.exists(elf): return 99999
    out=subprocess.run([sys.executable,f'{S}/casediff.py',name,'0x0805424C','0x080568F4','0x64','0x8c',elf],cwd=R,capture_output=True,text=True).stdout
    m=re.search(r'total rows (\d+)',out)
    try: os.remove(elf)
    except OSError: pass
    return int(m.group(1)) if m else 99999

if __name__=='__main__':
    path=sys.argv[1]; maxspan=int(sys.argv[2]) if len(sys.argv)>2 else 8
    jobs=int(sys.argv[3]) if len(sys.argv)>3 else 12
    lo=int(sys.argv[4]) if len(sys.argv)>4 else 0
    hi=int(sys.argv[5]) if len(sys.argv)>5 else 10**9
    src=open(path).read()
    i=src.index('u32 sub_0805424C(void)')
    head,fn=src[:i],src[i:]
    lines=fn.split('\n')
    def ind(l): return len(l)-len(l.lstrip())
    def okstart(k):
        l=lines[k].strip()
        if not l or l.startswith(('else','}','{','case','default','#')) or l.endswith(':'): return False
        if re.match(r'(s32|u32|u8|s16|u16|long|struct|volatile)\b[^=(]*;',l): return False
        return True
    cands=[]
    for a in range(1,len(lines)-1):
        if a<lo or a>hi or not okstart(a): continue
        d=0
        for b in range(a,min(len(lines)-1,a+maxspan)):
            d+=lines[b].count('{')-lines[b].count('}')
            if d<0: break
            if 'break' in lines[b] or 'continue' in lines[b] or 'goto' in lines[b] or re.match(r'\s*(case|default)\b',lines[b]) or lines[b].strip().endswith(':'): break
            if re.match(r'\s+(s32|u32|u8|s16|u16|long|struct|volatile)\b[^=(]*;',lines[b]): break
            l=lines[b].strip(); nxt=lines[b+1].strip()
            if d==0 and (l.endswith(';') or l=='}') and not nxt.startswith(('else','while')):
                if l=='}' and ind(lines[b])!=ind(lines[a]): continue
                cands.append((a,b))
    unw=[]
    for k,l in enumerate(lines):
        if l.strip()=='do {':
            for m in range(k+1,len(lines)):
                if lines[m].strip()=='} while (0);' and ind(lines[m])==ind(l):
                    unw.append((k,m)); break
    print('candidates',len(cands),'unwraps',len(unw),flush=True)
    base=score(head+fn,'base'); print('base',base,flush=True)
    def run(ab):
        a,b=ab
        if a<0:
            k,m=-a-1,b
            nl=lines[:k]+lines[k+1:m]+lines[m+1:]
            sc=score(head+chr(10).join(nl), f'u{k}')
            shutil.rmtree(f'{WD}/u{k}', ignore_errors=True)
            return ab, sc
        sp=' '*ind(lines[a])
        nl=lines[:a]+[sp+'do {']+lines[a:b+1]+[sp+'} while (0);']+lines[b+1:]
        sc = score(head+'\n'.join(nl), f'v{a}_{b}')
        shutil.rmtree(f'{WD}/v{a}_{b}', ignore_errors=True)
        return ab, sc
    res=[]
    allc=[(-k-1,m) for k,m in unw]+cands
    with ThreadPoolExecutor(jobs) as ex:
        for n,(ab,sc) in enumerate(ex.map(run,allc)):
            res.append((sc,ab))
            if n%100==0: print('progress',n,flush=True)
            if sc<base: print('better',sc,ab,lines[ab[0]].strip()[:60],flush=True)
    res.sort()
    print('top',res[:15],flush=True)
    def build(ws):
        nl=list(lines)
        for a,b in sorted(ws,key=lambda x:-x[0]):
            sp=' '*ind(lines[a])
            nl=nl[:a]+[sp+'do {']+nl[a:b+1]+[sp+'} while (0);']+nl[b+1:]
        return head+chr(10).join(nl)
    chosen=[]; best=base
    for sc,ab in res[:40]:
        if sc>=base: break
        if ab[0]<0:
            if not chosen:
                print('unwrap best',ab,sc,flush=True)
            continue
        if any(not (ab[1]<c[0] or ab[0]>c[1]) for c in chosen): continue
        t=score(build(chosen+[ab]),'comb')
        print('try',ab,t,flush=True)
        if t<best:
            best=t; chosen.append(ab)
            open(path+'.best.c','w').write(build(chosen))
    print('combined',best,chosen,flush=True)
