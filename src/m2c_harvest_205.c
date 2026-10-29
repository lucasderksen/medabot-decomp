/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "effect_work.h"
#include "frame.h"
#include "input.h"
#include "main.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ChoiceWork64524 {u8 pad0[0x7A];s8 mode;};
struct SavedGraphics6E184 {u16 state;u16 substate;u16 step;};
struct DmaRegisters6E184 {u32 source;u32 destination;u32 control;};
struct GraphicsWork701A8 {u8 pad0[0xEC];u8 position;u8 stage;};
struct DmaRegisters701A8 {u32 source;u32 destination;u32 control;};

extern s32 sub_080688E0(void);
extern struct GraphicsWork701A8 gGraphicsWork701A803001800;
extern struct SavedGraphics6E184 gGraphicsWork6E18403001800;

void sub_08064524(void);
void sub_0806E184(void);
void sub_080701A8(void);
s32 sub_08071D88(u32 slot);

void sub_08064524(void) {
 const void *const *scripts=gMain2ScriptSlots_08485678;
 s32 mode=((struct ChoiceWork64524 *)gMainContextPointer_03006F74)->mode;
 u32 offset=0x6C;
 struct SerialView64524 {u8 pad0[0xA];u16 wordA;};
 struct SerialView64524 *serial;
 u32 connected;
 u16 *wordA;
 u32 rowOffset;
 if(mode) offset=0x68;
 if(sub_0803FB3C(*(const void *const *)((u32)scripts+offset))) {
  if(*(u8 *)&gRepeatedKeys &1) {sub_08074DE0(13);gUnknown_0300137C++;}
  else {
   serial=(struct SerialView64524 *)&gMainSerialOutgoingWork;
   connected=*(u8 *)&gUnknown_03000B90;
   rowOffset=0;
   if(connected==0) rowOffset=4;
   wordA=&serial->wordA;
   if(*(u16 *)((u32)wordA+rowOffset)==0xFEFF) gUnknown_0300137C++;
  }
 }
}

void sub_0806E184(void) {
 u32 fill;
 volatile struct DmaRegisters6E184 *dma;
 if(sub_080688E0()) {
  fill=0;
  dma=(volatile struct DmaRegisters6E184 *)0x040000D4;
  dma->source=(u32)&fill;
  dma->destination=(u32)gFrameObjects;
  dma->control=0x85000800;
  (void)dma->control;
  *(volatile u16 *)0x04000000 &=0x80FF;
  gMainState=gGraphicsWork6E18403001800.state;
  gMainSubstate=gGraphicsWork6E18403001800.substate;
  gUnknown_0300137C=gGraphicsWork6E18403001800.step;
 }
}

void sub_080701A8(void) {
 u32 fill;
 volatile struct DmaRegisters701A8 *dma;
 struct FrameObject *frames;
 u32 y;
 s32 count;
 gGraphicsWork701A803001800.position=0;
 gGraphicsWork701A803001800.stage=0;
 fill=0;
 dma=(volatile struct DmaRegisters701A8 *)0x040000D4;
 dma->source=(u32)&fill;
 dma->destination=0x0600F800;
 dma->control=0x850000A0;
 (void)dma->control;
 frames=gFrameObjects;
 y=200;
 count=5;
 do {frames[count+14].screenY=y;count--;} while(count>=0);
}

s32 sub_08071D88(u32 slot) {
 u32 index=(u8)slot;
 u32 root=(u32)gFrameObjects;
 struct FrameObject *first=(struct FrameObject *)(root+(index<<6));
 struct FrameObject *second;
 first->screenY=(u16)first->screenY+1;
 second=(struct FrameObject *)(root+((index+4)<<6));
 second->screenY=(u16)second->screenY+1;
 if(first->unknown1A>7) return 0;
 return 1;
}
