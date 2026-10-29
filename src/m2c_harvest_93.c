/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "dialogue_messages.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_effects.h"
#include "effect_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern u8 gUnknown_03001855;
extern void sub_0803E894(void);
extern void sub_0803ED6C(void);

void sub_08014634(void);
void sub_08014754(void);
void sub_0803E1A4(void);

void sub_08014634(void) {
 struct FrameObject *frame;
 u32 i,selected,frames;
 u8 *flags;
 sub_080195C0();
 i=0;frames=(u32)gFrameObjects;flags=&gUnknown_03001855;
 selected=0x46000000;
 frame=(struct FrameObject *)(frames+0x1180);
 do {
  u8 *setup=gSetupBuffer_03000590;
  u32 offset=i<<8;
  u32 address=offset+(u32)setup;
  u8 *kind;
  if(*(u8 *)(address+0x40)!=0) {
   kind=(u8 *)(address+0xCE);
   if((*kind&1)!=0) {
    u32 scale;
    frame->flags|=0x8000;
    frame->scaleY+=4;scale=frame->scaleX-4;frame->scaleX=scale;
    if((u8)scale==4) {
     *flags&=0xFD;*kind&=0xFE;
     sub_08040CD0((u8)(selected>>24),1);
    }
   }
  }
  selected+=0x03000000;frame+=3;i++;
 }while(i<=5);
 if(!(gState0TransferWork.bytes[0x55]&2))gUnknown_0300137C=0x44;
}

void sub_08014754(void) {
 struct FrameObject *frame;
 u32 i,selected,frames;
 u8 *flags;
 sub_080195C0();
 i=0;frames=(u32)gFrameObjects;flags=&gUnknown_03001855;
 selected=0x47000000;
 frame=(struct FrameObject *)(frames+0x11C0);
 do {
  u8 *setup=gSetupBuffer_03000590;
  u32 offset=i<<8;
  u32 address=offset+(u32)setup;
  u8 *kind;
  if(*(u8 *)(address+0x40)!=0) {
   kind=(u8 *)(address+0xCE);
   if((*kind&2)!=0) {
    u32 scale;
    frame->flags|=0x8000;
    frame->scaleY+=4;scale=frame->scaleX-4;frame->scaleX=scale;
    if((u8)scale==4) {
     *flags&=0xFB;*kind&=0xFD;
     sub_08040CD0((u8)(selected>>24),1);
    }
   }
  }
  selected+=0x03000000;frame+=3;i++;
 }while(i<=5);
 if(!(gState0TransferWork.bytes[0x55]&4))gUnknown_0300137C=0x44;
}

void sub_0803E1A4(void) {
    const void *commands;
    u8 *work;
    sub_0803E894();
    sub_0803ED6C();
    work = gState0TypedWork.bytes;
    (*(u16 *) (work + 0x86))++;
    if (work[0x9C] == 1)
        commands = gUnknownPointers_083CF530[4];
    else
        commands = gUnknownPointers_083CF530[5];
    if (sub_0803FB3C(commands) != 0) {
        sub_0803FAA0(1, 0, 0);
        gUnknown_0300137C++;
    }
}
