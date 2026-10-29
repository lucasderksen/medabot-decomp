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
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "tile_text.h"

struct Graphics6E504 {u16 savedState;u16 savedSubstate;u8 pad04[4];s32 counter;u8 pad0C[8];};
struct Dma6E504 {const void *volatile source;void *volatile destination;volatile u32 control;};

extern struct Graphics6E504 gGraphicsWork6E50403001800;
extern void sub_08068460(u8,u8,u16);

void sub_0806E504(void);

void sub_0806E504(void) {
 u32 fill;
 u32 zero;
 u32 byteZero;
 struct Dma6E504 *dma;
 zero=0;
 fill=zero;
 dma=(struct Dma6E504 *)0x040000D4;
 dma->source=&fill;dma->destination=(void *)0x06000000;dma->control=0x85006000;(void)dma->control;
 fill=zero;
 dma->source=&fill;dma->destination=(void *)0x05000000;dma->control=0x85000100;(void)dma->control;
 fill=zero;
 dma->source=&fill;dma->destination=(void *)0x07000000;dma->control=0x85000100;(void)dma->control;
 fill=zero;
 dma->source=&fill;dma->destination=gFrameObjects;dma->control=0x85000800;(void)dma->control;
 fill=zero;
 dma->source=&fill;dma->destination=&gGraphicsWork6E50403001800;dma->control=0x85000005;(void)dma->control;
 sub_08074B88(0U);
 *(volatile u16 *)0x04000000=0x60;
 byteZero=0;
 gGraphicsWork6E50403001800.savedState=3;
 gGraphicsWork6E50403001800.savedSubstate=zero;
 gGraphicsWork6E50403001800.counter=zero;
 gBgScroll0.x=zero;gBgScroll0.y=zero;
 gBgScroll1.x=zero;gBgScroll1.y=zero;
 gBgScroll2.x=zero;gBgScroll2.y=zero;
 gBgScroll3.x=zero;gBgScroll3.y=zero;
 gMain2Byte_03007008=byteZero;
 sub_08068460(2,4,0);
 gUnknown_0300137C=4;
}
