/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "graphics.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "utility_helpers.h"

struct ContinuedPhaseWork27 { u8 before[0xAA]; u8 phase; };
struct Dma696A8 {u32 source,destination,control;};

extern const u32 gPalette696A8087C67C4[8],gPalette696A8087C67E4[8];
extern const u8 *const gUnknownPointers_083B7048[];
extern const u8 *const gUnknown_083BE868[];
extern const u8 *gUnknown_083B618C;
extern const u8 gTiles696A8087C64BC[],gTiles696A8087C670C[];
extern u32 sub_08033184(u32);
extern u8 gUnknown_030018D2[3];
extern void sub_08036CCC(u32,u32,s32);
extern void sub_080697B4(u8,u8,u8);

void sub_0801DE44(void);
void sub_08020928(void);
void sub_08026D44(void);
void sub_08029178(void);
void sub_0802DA0C(void);
u32 sub_080330F4(s32 arg0);
void sub_080696A8(void);

void sub_0801DE44(void) {
 const u8 *const *labels=gUnknownPointers_083B7048;
 u8 *setup=gSetupBuffer_03000590;
 u8 *work=gState0TransferWork.bytes;
 u8 *part=work+0xA7;
 u32 selected=*part*24;
 u8 *bank=work+0x87;
 u32 bankOffset=*bank<<8;
 const u8 *record=setup+(selected+bankOffset);
 u8 *destination;
 const u8 *label=labels[record[0x4A]];
 destination=gDebugMenuTextBuffer;
 sub_0803F63C(label,destination,14);
 labels=gUnknown_083BE868;
 selected=*part*24;
 bankOffset=*bank<<8;
 record=setup+(selected+bankOffset);
 label=labels[record[0x49]];
 destination+=20;
 sub_0803F63C(label,destination,14);
 work[0xA6]=0x17;
 work[0xAA]++;
}

void sub_08020928(void) {
 u8 *setup=gSetupBuffer_03000590;
 u8 *work=gState0TransferWork.bytes;
 u8 *phase;
 s32 next;
 u16 *amount;
 u8 *bank;
 u32 chosen;
 u32 part=work[0xA7]*24;
 u32 bankOffset=work[0x87]<<8;
 if(setup[part+bankOffset+0x4F] &&
    (amount=(u16 *)(work+0xCA),*amount)!=0 &&
    (bank=work+0x88,chosen=sub_08033184(*bank))!=0) {
  u8 *saved;
  chosen-=1;
  saved=work+0xD0;
  *saved=chosen;work[0x8B]=chosen;
  sub_08036CCC(*bank,*saved,*amount);
  phase=work+0xAA;next=0xE;
 } else {phase=work+0xAA;next=*phase+1;}
 *phase=next;
}

void sub_08026D44(void) {
 u8 *work=gState0TransferWork.bytes;
 u16 *amount=(u16 *)(work+0xCA);
 u8 *phase;
 s32 next;
 if(*amount) {
  u8 *bank=work+0x87;
  u8 *part;
  u8 *saved;
  u32 value;
  sub_08035528(*bank);sub_080355C4(*bank);
  part=work+0x8B;value=*part;saved=work+0xD0;
  *saved=value;
  sub_08034F68(*(u8 *)((u32)saved-0x48),*part,*amount);
  phase=work+0xAA;next=*phase+3;
 } else {phase=work+0xAA;next=*phase+1;}
 *phase=next;
}

void sub_08029178(void) {
    u32 var_r5;
    u32 var_r6;
    const u8 **script;

    var_r5 = 0;
    script=&gUnknown_083B618C;
    var_r6 = 0x21000000;
    do {
        const u8 *commands=*script;
        u32 current=var_r5+0x21;
        sub_08040BD8(commands, (u8) (var_r6 >> 0x18));
        sub_0804422C(current);
        var_r6 += 0x01000000;
        var_r5 += 1;
    } while (var_r5 <= 4U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        sub_08040CD0(0x21U, 5U);
        gState0TypedWork.widths.word86 = 0x3C;
        ((struct ContinuedPhaseWork27 *)&gState0TransferWork)->phase = (u8) (((struct ContinuedPhaseWork27 *)&gState0TransferWork)->phase + 1);
    }
}

void sub_0802DA0C(void) {
    s32 var_r5;
    s32 var_r6;
    u32 var_r4;
    u8 *selected;

    var_r6 = 0;
    var_r5 = 0;
    var_r4 = 0;
    selected=gUnknown_030018D2;
    do {
        if (*(u8 *)(var_r4+(u32)selected) != 0) {
            var_r5 += 1;
            if (sub_08036AC4(var_r4 + 0x24, 0U) != 0) {
                var_r6 += 1;
            }
        }
        var_r4 += 1;
    } while (var_r4 <= 2U);
    if (var_r6 == var_r5) {
        gState0TypedWork.widths.word86 = 0x3C;
        ((struct ContinuedPhaseWork27 *)&gState0TransferWork)->phase = (u8) (((struct ContinuedPhaseWork27 *)&gState0TransferWork)->phase + 1);
    }
}

u32 sub_080330F4(s32 arg0) {
    u8 *base;
    u32 bank;
    s32 temp_r2;
    s32 var_r1;
    u32 var_r3;
    u32 var_r4;

    var_r4 = sub_08033074();
    temp_r2 = sub_080424B8() & 1;
    var_r3=0;
    base=gSetupBuffer_03000590;

    var_r1 = var_r4 * 0x18;
loop_1:
    if ((*(u8 *)((u8 *)((u8 *)((u32)var_r1+((u32)arg0<<8)+(u32)base)) + 0x59)) == 0) {
        if (temp_r2 != 0) {
            var_r1 += 0x18;
            var_r4 += 1;
            if (var_r4 > 2U) {
                var_r1 = 0;
                var_r4 = 0;
            }
        } else if (var_r4 == 0) {
            var_r1 = 0x30;
            var_r4 = 2;
        } else {
            var_r1 -= 0x18;
            var_r4 -= 1;
        }
        var_r3 += 1;
        if (var_r3 <= 2U) {
            goto loop_1;
        }
    }
    return var_r4;
}

void sub_080696A8(void) {
    u16 sp4;
    u16 *fill;
    volatile struct Dma696A8 *dma;

    fill=&sp4;
    *fill = 0;
    dma=(volatile struct Dma696A8 *)0x040000D4;
    dma->source = (u32)fill;
    dma->destination = 0x0600E800;
    dma->control = 0x81000400;
    (void)dma->control;
    LZ77UnCompVram(gTiles696A8087C64BC, (void *)0x0600CD00);
    LZ77UnCompVram(gTiles696A8087C670C, (void *)0x0600D0A0);
    dma->source = (u32)gPalette696A8087C67C4;
    dma->destination = 0x05000180;
    dma->control = 0x84000008;
    (void)dma->control;
    dma->source = (u32)gPalette696A8087C67E4;
    dma->destination = 0x050001A0;
    dma->control = 0x84000008;
    (void)dma->control;
    sub_080697B4(4, 1, 0xE);
    sub_080697B4(4, 0xB, 0xE);
    sub_080697B4(4, 0x15, 0xE);
    *(volatile u16 *)0x0400000A = 0x1D0D;
    sub_08048864(1U, 0xC400U, 0x6FU, 8U, 1U);
    gFrameObjects[1].screenX = 0xF;
    gFrameObjects[1].screenY = 0x7F;
    sub_08048864(2U, 0xC400U, 0x7BU, 9U, 1U);
    gFrameObjects[2].screenX = 0x5F;
    gFrameObjects[2].screenY = 0x7F;
    sub_08048864(3U, 0xC400U, 0x87U, 0xAU, 1U);
    gFrameObjects[3].screenX = 0xAF;
    gFrameObjects[3].screenY = 0x7F;
}
