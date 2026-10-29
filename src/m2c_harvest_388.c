/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_float_progress.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_effects.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_debug_menu.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct BackgroundSelectionDma {
    u32 source;
    u32 destination;
    u32 control;
};

extern const u8 *const gUnknown_08486DC4[12];
extern const u8 *const gUnknown_08486DF4[12];
extern const u8 *const gUnknown_08486E24[12];
extern void sub_08068460(u32,u32,u32);

void sub_0806E2A0(void);

void sub_0806E2A0(void) {

    u16 packed[600];
    u16 expanded[640];
    const u8 *const *initialTable;
    const union State0TransferWork *earlyWork;
    union State0TransferWork *work;
    const u8 *const *paletteTable;
    u32 rowBase;
    u16 *zeroBase;
    u32 zero;
    s32 row,rowOffset,packedOffset,nextRow,remaining;
    u16 *source,*destination,*zeroDestination;
    volatile struct BackgroundSelectionDma *dma;
    /* Capture the table before the work root; retain these two lifetimes. */
    initialTable=gUnknown_08486DC4;
    /* word0C is an initialized index into the twelve-entry asset tables. */
    earlyWork=&gState0TransferWork;
    LZ77UnCompVram(initialTable[earlyWork->backgroundSetup.word0C],(void *)0x06008000);
    LZ77UnCompVram(gUnknown_08486DF4[earlyWork->backgroundSetup.word0C],packed);
    row=0;work=&gState0TransferWork;
    paletteTable=gUnknown_08486E24;
    zeroBase=expanded;
    zero=0;
    rowBase=(u32)&expanded;
    do {
        rowOffset=row<<5;
        packedOffset=row<<4;
        nextRow=row+1;
        packedOffset-=row;
        packedOffset<<=2;
        source=(u16 *)((u32)packedOffset+(u32)packed);
        destination=(u16 *)((u32)(row<<6)+(u32)rowBase);
        remaining=29;
        do {
            *destination=*source;
            ++source;
            ++destination;
            --remaining;
        } while(remaining>=0);
        zeroDestination=(u16 *)((u32)zeroBase+((rowOffset+30)<<1));
        *zeroDestination=zero;
        zeroDestination=(u16 *)((u32)zeroBase+((rowOffset+31)<<1));
        *zeroDestination=zero;
        row=nextRow;
    } while(row<=19);
    dma=(volatile struct BackgroundSelectionDma *)0x040000D4;
    dma->source=(u32)expanded;
    dma->destination=0x06007800;
    dma->control=0x84000140;
    (void)dma->control;
    dma->source=(u32)paletteTable[work->backgroundSetup.word0C];
    dma->destination=0x05000000;
    dma->control=0x800000E0;
    (void)dma->control;
    *(volatile u16 *)0x0400000A=0xF8B;
    sub_08068460(2,1,0);
    sub_0803FAA0(1U,2U,0U);
    *(volatile u16 *)0x04000000 |=0x200;
    work->backgroundSetup.word04=4;
    gUnknown_0300137C=1;
}
