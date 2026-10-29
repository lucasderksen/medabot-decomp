"""Native action table consumers with only random source and sprite clearing stubbed."""
import sys,json,struct
from pathlib import Path
from common import find_rom
from cpu import RoutineCpu,arm_const,unicorn
r=find_rom().read_bytes();cpu=RoutineCpu(r);state={};coverage=set();cases=0
ranges=[(0x83ad380,216),(0x83ad470,128),(0x83ad502,24),(0x83ad51a,6),(0x83ad533,32),(0x83ad553,32),(0x83ad573,6),(0x83ad579,7),(0x83ad580,76)]
def code(m,a,n,u):
    if a==0x807ccf0:return
    if state['start']<=a<state['end'] or 0x8041d04<=a<0x8041d28:return
    assert a in (0x80424b8,0x8040cd0) or a==state.get('callback'),hex(a)
    if a==0x8040cd0:
        assert m.reg_read(arm_const.UC_ARM_REG_R0)==60 and m.reg_read(arm_const.UC_ARM_REG_R1)==10
    state['calls'].append(a)
    m.reg_write(arm_const.UC_ARM_REG_R0,state.get('random',0) if a==0x80424b8 else 0)
    m.reg_write(arm_const.UC_ARM_REG_PC,m.reg_read(arm_const.UC_ARM_REG_LR))
def read(m,access,a,n,v,u):coverage.update(range(a,a+n))
cpu.engine.hook_add(unicorn.UC_HOOK_CODE,code)
for a,n in ranges:cpu.engine.hook_add(unicorn.UC_HOOK_MEM_READ,read,begin=a,end=a+n-1)
def run(a,b,ram,expected,args=(),calls=()):
    global cases
    state.update(start=a,end=b,calls=[])
    cpu.write(0x3000000,bytes(ram));regs=cpu.call(a,args,timeout_us=0)
    actual=cpu.read(0x3000000,len(expected))
    assert actual==expected,(hex(a),args,[(hex(i),x,y) for i,(x,y) in enumerate(zip(actual,expected)) if x!=y][:12])
    assert state['calls']==list(calls)
    assert regs[4:12]==tuple(0xab000000|i for i in range(4,12)) and cpu.engine.reg_read(arm_const.UC_ARM_REG_SP)==0x3007f00
    cases+=1
    return regs[0]
def ram():return bytearray([0xa5]*0x7000)
for selected in range(3):
    for kind in range(30):
        for level in (0,1,2,3,19,199,200,255):
            x=ram();b=0x1800+selected*12;x[b+4]=0;x[b+8]=kind;x[b+9]=level
            e=bytearray(x);meta=r[0x3b62d8+kind*16:0x3b62e8+kind*16];e[0x52e:0x53e]=meta
            out=0x590+(selected+3)*256
            for off,v in {0:128,1:meta[0],4:meta[1],5:level,6:meta[2],7:meta[7],9:x[b+14]}.items():e[out+off]=v
            name=struct.unpack_from('<I',r,0x3ba658)[0]-0x8000000;e[out+10:out+24]=r[name:name+14]
            for j in range(4):e[out+24+j*2]=x[b+10+j]>>4;e[out+25+j*2]=x[b+10+j]&15
            e[out+32:out+40]=bytes(max(1,min(100,v*max(1,level>>1))) for v in r[0x3ad380+meta[1]*8:0x3ad388+meta[1]*8])
            run(0x80150fc,0x801520c,x,e,(selected,))
for index in range(32):
    for mode,flag in ((0,0),(1,0),(1,1)):
        for mask in (0,1,21,42,63):
            for excluded in range(-1,6):
                state['random']=index;x=ram();x[0x4c9]=mode;x[0xb90]=flag
                for j in range(6):x[0x590+j*256+0x40]=(mask>>j)&1
                expected=0
                for attempt in range(6):
                    selected=r[0x3ad553+((index+attempt)&31)]
                    if mode==1 and flag:selected=r[0x3ad573+selected]
                    if (mask>>selected)&1 and selected!=excluded:expected=selected;break
                assert run(0x801b700,0x801b76c,x,x,(excluded&0xffffffff,),calls=(0x80424b8,))==expected
for a,b,table,count,phase in ((0x801c0bc,0x801c0f8,0x3ad580,4,0xa1),(0x801c154,0x801c188,0x3ad590,5,0x9c),(0x801c2f0,0x801c32c,0x3ad5a4,10,0x9c)):
    for index in range(count):
        for kind in (0,255,256):
            for done in (0,1):
                x=ram();x[0x1800+phase]=index;x[0x189e]=done;e=bytearray(x)
                state['callback']=struct.unpack_from('<I',r,table+4*index)[0]&~1
                if count==4:e[0x18a2]=kind&255
                if count==10:e[0x189d]=kind&255;expected=done
                else:
                    expected=int(index==count-1)
                    if expected:e[0x1800+phase]=0
                assert run(a,b,x,e,(kind,),calls=(state['callback'],))==expected
state.pop('callback',None)
for random in list(range(32))+[0xffffffe0+i for i in range(32)]:
    state['random']=random;x=ram();e=bytearray(x);i=random&31;e[0x1864:0x1868]=r[0x3ad470+i*4:0x3ad474+i*4]
    run(0x80156d0,0x80156f8,x,e,calls=(0x80424b8,))
for i in range(6):
    x=ram();x[0x1881]=i;e=bytearray(x);struct.pack_into('<I',e,0x137c,r[0x3ad51a+i]);run(0x80165b0,0x80165d0,x,e)
    x=ram();e=bytearray(x);count,kind,px,py=r[0x3ad502+i*4:0x3ad506+i*4]
    for j in range(count):
        b=0x2c30+(60+j)*64;phase=j&3
        struct.pack_into('<HHHH',e,b,0xc404|(0x1000 if i>2 else 0),px,py,0x616+phase)
        for off,value in {10:8,11:128,28:0,0x25:kind,0x26:count-1-j,0x24:0,0x27:j*2,0x28:0,0x21:0,0x22:phase}.items():e[b+off]=value
    run(0x8016370,0x8016438,x,e,(i,),calls=(0x8040cd0,))
for bank in range(6):
    for index in range(7):
        x=ram();b=0x590+bank*256+0xe0;x[b]=index;e=bytearray(x);e[b]=r[0x3ad579+index];run(0x801c0a0,0x801c0bc,x,e,(bank,))
for selected in range(6):
    for offset in list(range(33))+[255]:
        for delay in (0,1,255):
            for y in (0,32767,32768):
                x=ram()
                for j in range(3):
                    b=0x2c30+(selected*4+10+j)*64;struct.pack_into('<H',x,b+4,y);x[b+0x20]=delay;x[b+0x21]=offset
                e=bytearray(x)
                for j in range(3):
                    if offset==255:break
                    if offset<=31:
                        b=0x2c30+(selected*4+10+j)*64
                        if delay:e[b+0x20]=delay-1
                        else:
                            step=struct.unpack_from('<b',r,0x3ad533+offset)[0];struct.pack_into('<H',e,b+4,(y+step)&65535);e[b+9]=(e[b+9]+2)&255;e[b+0x21]=offset+1
                run(0x801a228,0x801a28c,x,e,(selected,))
assert coverage==set().union(*(set(range(a,a+n)) for a,n in ranges))
result=dict(cases=cases,covered_bytes=len(coverage),scope='Original consumers150FC,156D0,16370,165B0,1A228,1B700,1C0A0,1C0BC,1C154,1C2F0. Byte-copy helper and call trampoline native; random source, sprite clear and dispatched callbacks stubbed with exact calls. Full guarded IWRAM and ABI. All table entries; selection32 starts/7 exclusions/5 active masks/3 modes; dispatch19 entries/3 kinds/2 completion flags; action stats30 kinds/3 slots/8 levels; motion offset0..32/255,delay0/1/255,signed-y boundaries,6 groups. Stubbed helper effects outside scope.')
Path('build/more/action_aux_cpu.json').write_text(json.dumps(result,indent=2)+'\n');print(result)
