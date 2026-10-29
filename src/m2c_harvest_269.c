/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_effects.h"
#include "effect_work.h"
#include "frame.h"
#include "main.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "rom_libc.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct CallbackBlock_080649BC {void (*entries[4])(void);};
struct PurchaseContextView {u8 before2E[0x2E];u8 first,second;u8 before3A[10];u16 timer;u8 before4C[16];u8 active;u8 beforeB0[0x63];u8 values[0];};

extern const struct CallbackBlock_080649BC gUnknown_080AFC48;
extern s32 (*const gUnknown_08485708[])(void);
extern s32 gTransferStep03000000;
extern u32 gPostDispatchWord_03002B70;
extern u8 gUnknown_03000004;
extern void (*const gUnknown_080AFCC0[13])(void);

void sub_08060180(void);
void sub_080649BC(void);
void sub_080655FC(void);
void sub_08066824(void);
s32 sub_08068888(void);

void sub_08060180(void) {

 u8 phase=*(u8 *)gMainContextPointer_03006F74;
 if(phase!=0x20) {
  *(u8 *)gMainContextPointer_03006F74=phase+1;
  *(volatile u16 *)0x04000054=*(u8 *)gMainContextPointer_03006F74>>1;
  return;
 }
 *(volatile u16 *)0x04000000&=0xFDFF;
 gMainState=3;
 gMainSubstate=0;
 gUnknown_0300137C=0;
}

void sub_080649BC(void) {

 struct CallbackBlock_080649BC local;
 local=gUnknown_080AFC48;
 local.entries[gUnknown_0300137C]();
 if(gFrameCounter&1) gBgScroll3.x++;
}

void sub_080655FC(void) {

 s32 busy=1;
 u32 high;
 if(((struct PurchaseContextView *)gMainContextPointer_03006F74)->active){
  if(sub_08041CA4()){
   ((struct PurchaseContextView *)gMainContextPointer_03006F74)->active=0;
   sub_0803FAA0(1,0,0);
  }
 }else if(sub_0803FB3C(gMain2ScriptSlots_0848521C[14]))busy=0;
 if(busy==0&&(busy=sub_08041674())!=0){
  high=busy&0xF0;
  if(high){
   ((struct PurchaseContextView *)gMainContextPointer_03006F74)->active=1;
   gUnknown_0300137C=5;
  }else if(gPostDispatchWord_03002B70<=99U){
   struct PurchaseContextView *work;
   gUnknown_0300137C=8;
   work=gMainContextPointer_03006F74;
   work->timer=0xB4;
   work->active=1;
  }else{
   struct PurchaseContextView *work;
   u8 *quantity;
   u8 *choices;
   u32 selection;
   gPostDispatchWord_03002B70-=100;
   quantity=&gQuantityResult_030017EC;
   work=gMainContextPointer_03006F74;
   choices=&work->first;
   selection=*choices++;
   selection+=*choices;
   *quantity=work->values[selection];
   gState0TypedWork.bytes[0x84]=high;
   gUnknown_0300137C=6;
  }
 }
}

void sub_08066824(void) {

 void (*local[13])(void);
 memcpy(local,gUnknown_080AFCC0,52);
 local[gUnknown_0300137C]();
 if(gFrameCounter&1) {gBgScroll3.x++;gBgScroll3.y++;}
}

s32 sub_08068888(void) {

 if(gUnknown_08485708[gUnknown_03000004]()!=0) {
  gTransferStep03000000=0;
  if(gUnknown_03000004==3) *(volatile u16 *)0x04000000&=0xFEFF;
  return 1;
 }
 gTransferStep03000000++;
 return 0;
}
