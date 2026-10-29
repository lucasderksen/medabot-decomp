/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "main.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"

struct Graphics6EBA4 {u16 savedState;u16 savedSubstate;u16 savedStep;u8 pad06[0xEA];u16 timer;u16 angle;};
struct Dma6EBA4 {const void *volatile source;void *volatile destination;volatile u32 control;};

extern s32 sub_080688E0(void);
extern struct Graphics6EBA4 gGraphicsWork6EBA403001800;
extern void sub_0806FE44(void);
extern void sub_08070550(void);

void sub_0806EBA4(void);

void sub_0806EBA4(void) {
 u32 fill;
 u32 zero;
 u32 next;
 struct Dma6EBA4 *dma;
 next=gGraphicsWork6EBA403001800.timer+1;
 zero=0;
 gGraphicsWork6EBA403001800.timer=next;
 gGraphicsWork6EBA403001800.angle+=0x6F;
 sub_0806FE44();
 sub_08070550();
 if(sub_080688E0()!=0){
  fill=zero;
  dma=(struct Dma6EBA4 *)0x040000D4;
  dma->source=&fill;
  dma->destination=gFrameObjects;
  dma->control=0x85000800;
  (void)dma->control;
  gRenderMode=zero;
  *(volatile u16 *)0x04000000&=0x80FF;
  gMainState=gGraphicsWork6EBA403001800.savedState;
  gMainSubstate=gGraphicsWork6EBA403001800.savedSubstate;
  gUnknown_0300137C=gGraphicsWork6EBA403001800.savedStep;
 }
}
