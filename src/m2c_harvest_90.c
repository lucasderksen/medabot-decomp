/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"


void sub_080145BC(void);
void sub_080146DC(void);

void sub_080145BC(void) {
 struct FrameObject *frame;
 u32 i,frames,setup,scale;
 u8 *kind,*active;
 sub_080195C0();sub_0801A0D0();
 i=0;setup=(u32)gSetupBuffer_03000590;frames=(u32)gFrameObjects;scale=0x40;
 frame=(struct FrameObject *)(frames+0x1180);
 kind=(u8 *)(setup+0xCE);active=(u8 *)(setup+0x40);
 do {
  if(*active!=0 && (*kind&1)!=0) {
   frame->flags|=0x8220;frame->scaleY=scale;frame->scaleX=scale;
  }
  frame+=3;kind+=0x100;active+=0x100;i++;
 }while(i<=5);
 sub_08074DE0(0x37);gUnknown_0300137C++;
}

void sub_080146DC(void) {
 struct FrameObject *frame;
 u32 i,frames,setup,scale;
 u8 *kind,*active;
 sub_080195C0();sub_0801A0D0();
 i=0;setup=(u32)gSetupBuffer_03000590;frames=(u32)gFrameObjects;scale=0x40;
 frame=(struct FrameObject *)(frames+0x11C0);
 kind=(u8 *)(setup+0xCE);active=(u8 *)(setup+0x40);
 do {
  if(*active!=0 && (*kind&2)!=0) {
   frame->flags|=0x8220;frame->scaleY=scale;frame->scaleX=scale;
  }
  frame+=3;kind+=0x100;active+=0x100;i++;
 }while(i<=5);
 sub_08074DE0(0x37);gUnknown_0300137C++;
}
