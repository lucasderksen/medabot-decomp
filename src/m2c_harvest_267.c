/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"

struct ScriptDispatchRecord {u8 before61[0x61];u8 kind,active;};

extern void sub_0807244C(void *);
extern void sub_080725B0(void *);
extern void sub_080725D0(void *);
extern void sub_08072618(void *);
extern void sub_08072660(void *);

void sub_08060400(void);
void sub_0807266C(void *record);

void sub_08060400(void) {

 *(volatile u16 *)0x04000000|=0x100;
 *(volatile u16 *)0x04000000|=0x200;
 *(volatile u16 *)0x04000000|=0x800;
 *(volatile u16 *)0x04000000|=0x1000;
 *(u8 *)gMainContextPointer_03006F74=0x20;
 *(volatile u16 *)0x04000054=*(u8 *)gMainContextPointer_03006F74>>1;
 gUnknown_0300137C++;
}

void sub_0807266C(void *record) {

 struct ScriptDispatchRecord *work=record;
 if(work->active){
  switch(work->kind){
  case 1:sub_080725B0(record);break;
  case 2:sub_080725D0(record);break;
  case 3:sub_08072618(record);break;
  case 4:sub_08072660(record);break;
  case 5:sub_0807244C(record);break;
  }
 }
}
