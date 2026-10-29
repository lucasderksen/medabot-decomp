"""Generate banked-event source/spec in build/more for isolated comparison.

Requires the verified native ROM. Does not edit production source/manifest.
Dispatch extents are checked against all roots, allowing the verified overlap.
"""
import sys,json,struct,hashlib,collections,re
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parent))
from common import find_rom,load_segments
from banked_scripts import decode,OPERANDS,script_address
rom=find_rom().read_bytes(); existing=[entry for entry in load_segments() if entry['source'] != 'src/banked_script_data.c'];base=0x8000000
offsets=struct.unpack_from('<2288H',rom,0x769ec0);banks=rom[0x76b0a0:0x76b990]
roots=[script_address(a,b)-base for a,b in zip(offsets,banks)]
indices=collections.defaultdict(list)
for i,a in enumerate(roots):indices[a].append(i)
unique=sorted(set(roots));commands={}
for a,b in zip(unique,unique[1:]+[0x785ec0]):
 for command in decode(rom,a,b):
  assert command.offset not in commands
  commands[command.offset]=command
assert b''.join(x.encode() for x in commands.values())==rom[0x76b990:0x785ec0]
assert len(rom[0x765ec4:0x769ec0].strip(b'\0'))==0
assert len(rom[0x76b990:0x76dec0].strip(b'\0'))==0
table=re.findall(r'(sub_\w+|0), /\* opcode ([0-9A-F]+) \*/',Path('src/continued_command_tables.c').read_text())[:256]
names={i:f'BANKED_OP_{i:02X}' for i in range(len(OPERANDS))}
names.update({0:'BANKED_NOP',1:'BANKED_DIALOGUE',2:'BANKED_DIALOGUE_02',4:'BANKED_WAIT_TICKS',5:'BANKED_WAIT_KEY',6:'BANKED_END',0x30:'BANKED_JUMP16',0x80:'BANKED_RESET_AND_DISPATCH',0x81:'BANKED_ADD_ROW_AND_DISPATCH',0x86:'BANKED_ADD_ROW'})
header=['#ifndef GUARD_BANKED_SCRIPT_COMMANDS_H','#define GUARD_BANKED_SCRIPT_COMMANDS_H','#include "global.h"','',
'/* Native event command bytes. Unknown semantics retain the opcode name. */',
'#define BANKED_HEADER_U16(value) ((value) & 0xFF), (((value) >> 8) & 0xFF)']
for op,count in enumerate(OPERANDS):
 if op==0x2f:continue
 args=[f'a{i}' for i in range(count)]
 form=names[op]+('('+', '.join(args)+')' if args else '')
 header.append(f'#define {form} 0x{op:02X}'+''.join(', ('+a+')' for a in args)+f' /* {table[op][0]} */')
for n in range(1,9):
 args=[f'a{i}' for i in range(n)]
 header.append(f'#define BANKED_SWITCH_{n}('+', '.join(args)+') 0x2F'+''.join(', ('+a+')' for a in args))
header+=['','#endif','']
Path('build/more/banked_script_commands.h').write_text('\n'.join(header))
source=['#include "banked_script_commands.h"','#include "banked_commands.h"','',
'/* The first four bytes locate the existing offset/bank directories. */',
'const u8 gSetupData_08765EC0[BANKED_COMMAND_WINDOW] __attribute__((aligned(1))) = {',
'    BANKED_HEADER_U16(0x4000), BANKED_HEADER_U16(0x51E0)',
'    /* Remaining header window is native reserved zero storage. */','};','',
'/* The shared empty root for 99 directory entries occupies the bank-one tail. */',
'const u8 gBankedEmptyScriptSpace_0876B990[9520] __attribute__((aligned(1))) = {0};','']
segs=[];audits=[]
def segment(a,b,name):
 assert not any(s['start']<b and a<s['end'] for s in existing)
 segs.append({'name':name,'start':hex(a),'end':hex(b),'input_section':'.rodata.'+name,'category':'data'})
 audits.append({'name':name,'start':hex(a+base),'end':hex(b+base),'bytes':b-a,'sha256':hashlib.sha256(rom[a:b]).hexdigest()})
segment(0x765ec0,0x769ec0,'gSetupData_08765EC0')
segment(0x76b990,0x76dec0,'gBankedEmptyScriptSpace_0876B990')
trailing=0;emitted=0
for bank in range(2,8):
 a=0x765ec0+bank*0x4000;b=a+0x4000
 assert a in commands
 last=max(x.end for x in commands.values() if a<=x.offset<b and any(x.encode()))
 assert last<=b and not any(rom[last:b])
 trailing+=b-last
 name=f'gBankedScriptBank{bank}_0{a+base:07X}'
 segment(a,b,name)
 source += [f'/* Native bank {bank}; directory offsets use the 4000..7FFF window. */',f'const u8 {name}[BANKED_COMMAND_WINDOW] __attribute__((aligned(1))) = {{']
 for pos,command in commands.items():
  if not a<=pos<last:continue
  emitted+=1
  if pos in indices:source.append(f'    /* Script indices '+', '.join(str(i) for i in indices[pos])+f'; ROM {pos+base:08X}. */')
  if pos==0x77a023:source.append('    /* Selector 3 enters the last two table bytes as facing command 0D 02. */')
  macro=f'BANKED_SWITCH_{len(command.operands)}' if command.opcode==0x2f else names[command.opcode]
  if command.operands:macro+='('+', '.join(f'0x{x:02X}' for x in command.operands)+')'
  source.append('    '+macro+',')
 source += [f'    /* {b-last} trailing native zero bytes are implicit. */','};','']
switches=[x for x in commands.values() if x.opcode==0x2f]
bad=[(x.offset,x.offset+1+v) for x in switches for v in x.operands if x.offset+1+v not in commands]
assert bad==[(0x77a023,0x77a026)]
assert decode(rom,0x77a026,0x77a028)[0].encode()==bytes([0xD,2])
assert all(a in commands for a in roots)
Path('build/more/banked_script_data.c').write_text('\n'.join(source))
Path('build/more/banked_script_spec.json').write_text(json.dumps({'source':'build/more/banked_script_data.c','compiler':'gcc','cflags':['-Ibuild/more'],'segments':segs},indent=2)+'\n')
Path('build/more/banked_script_audit.json').write_text(json.dumps({'objects':audits,'indices':len(roots),'roots':len(unique),'storage_commands':len(commands),'emitted_commands':emitted,'switches':len(switches),'switch_table_bytes':sum(len(x.operands) for x in switches),'overlapping_switch_target':{'table':'0x0877A023','target':'0x0877A026','command':'0D 02'},'header_reserved_bytes':0x4000-4,'empty_root_bytes':9520,'trailing_bank_zero_bytes':trailing,'source_bytes':sum(int(s['end'],0)-int(s['start'],0) for s in segs)},indent=2)+'\n')
print('Reconstructed',sum(int(s['end'],0)-int(s['start'],0) for s in segs),'bytes;',len(unique),'roots;',emitted,'commands;',len(switches),'dispatch tables;',trailing,'trailing zero bytes.')
