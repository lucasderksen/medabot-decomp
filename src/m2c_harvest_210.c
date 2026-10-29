/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "interrupts.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Dma68EA8 {u32 source,destination,control;};

extern u32 gUnknown_03006F80;
extern u32 sub_080688E0(void);

void sub_0801B3AC(void);
void sub_08068EA8(void);

void sub_0801B3AC(void) {
 u32 fill;
 u8 *work=gState0TransferWork.bytes,*saved=work+0x118;
 if(*saved) {
  u8 *setup=gSetupBuffer_03000590,*part=work+0xA7,*bank;
  {u32 partOffset=*part*24,bankOffset;u8 *record;u32 value;bank=work+0x87;bankOffset=*bank<<8;record=(u8 *)(partOffset+bankOffset+(u32)setup);value=work[0x11C];record[0x48]=value;}
  {u32 partOffset=*part*24,bankOffset=*bank<<8;u8 *record=(u8 *)(partOffset+bankOffset+(u32)setup);u32 value=work[0x11D];record[0x49]=value;}
  {u32 partOffset=*part*24,bankOffset=*bank<<8;u8 *record=(u8 *)(partOffset+bankOffset+(u32)setup);u32 value=work[0x121];record[0x4D]=value;}
  {u32 partOffset=*part*24,bankOffset=*bank<<8;u8 *record=(u8 *)(partOffset+bankOffset+(u32)setup);u32 value=work[0x122];record[0x4E]=value;}
  {u32 partOffset=*part*24,bankOffset=*bank<<8;u8 *record=(u8 *)(partOffset+bankOffset+(u32)setup);u32 value=work[0x123];record[0x4F]=value;}
  {u32 partOffset=*part*24,bankOffset=*bank<<8;u8 *record=(u8 *)(partOffset+bankOffset+(u32)setup);u32 value=work[0x128];record[0x54]=value;}
  {u32 partOffset=*part*24,bankOffset=*bank<<8;u8 *record=(u8 *)(partOffset+bankOffset+(u32)setup);u32 value=work[0x133];record[0x5F]=value;}
  sub_080158F8();sub_0801A0D0();
 }
 fill=0;CpuSet(&fill,saved,0x05000009);
}

void sub_08068EA8(void) {
    u32 sp0;
    volatile struct Dma68EA8 *dma;

    if (sub_080688E0() != 0) {
        sp0 = 0;
        dma=(volatile struct Dma68EA8 *)0x040000D4;
        dma->source=(u32)&sp0;
        dma->destination=(u32)gFrameObjects;
        dma->control=0x85000800;
        (void)dma->control;
        gUnknownCallback_030017F0 = DummyInterruptHandler;
        *(volatile u16 *)0x04000000 &= 0x80FF;
        gUnknown_0300137C = gUnknown_03006F80;
    }
}
