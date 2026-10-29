/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct BackgroundDma90 {
    u32 source;
    u32 destination;
    u32 control;
};

extern const u16 gUnknown_087F312C[16];
extern const u16 gUnknown_087F39CC[16];
extern const u8 gUnknown_087F2D40[];
extern const u8 gUnknown_087F3040[];
extern const u8 gUnknown_087F314C[];
extern const u8 gUnknown_087F384C[];

void sub_0806E5E0(void);
void sub_0806E6E4(void);

void sub_0806E5E0(void) {

    u16 packed[0x258];
    u16 expanded[0x280];
    volatile struct BackgroundDma90 *dma;
    u32 paletteAddress;
    union State0TransferWork *modeWork;
    s32 *stateWork;
    u32 zero;
    u16 *zeroDestination;
    s32 nextRow;
    s32 packedOffset;
    u8 *rowBase;
    u16 *zeroBase;
    s32 rowOffset;
    s32 row;
    s32 remaining;
    u16 *destination;
    u16 *source;

    LZ77UnCompVram(&gUnknown_087F2D40, (void *)0x06000000);
    LZ77UnCompVram(&gUnknown_087F3040, &packed[0]);
    row = 0;
    paletteAddress=(u32)&gUnknown_087F312C;
    modeWork=&gState0TransferWork;
    stateWork=&gUnknown_0300137C;
    /* Keep separate whole-array views; this order preserves register roles. */
    zeroBase = expanded;
    zero = 0;
    rowBase = (u8 *)&expanded;
    do {
        rowOffset = row << 5;
        packedOffset = row << 4;
        nextRow = row + 1;
        packedOffset -= row;
        packedOffset <<= 2;
        source = (u16 *)((u32)packedOffset+(u32)packed);
        destination = (u16 *)((u32)(row<<6)+(u32)rowBase);
        remaining = 0x1D;
loop_2:
        *destination = *source;
        source += 1;
        destination += 1;
        remaining -= 1;
        if (remaining >= 0) {
            goto loop_2;
        }
        zeroDestination=(u16 *)((u32)zeroBase+((rowOffset+0x1E)<<1));
        *zeroDestination = zero;
        zeroDestination=(u16 *)((u32)zeroBase+((rowOffset+0x1F)<<1));
        *zeroDestination = zero;
        row = nextRow;
    } while (row <= 0x13);
    dma=(volatile struct BackgroundDma90 *)0x040000D4;
    dma->source=(u32)(&expanded[0]);
    dma->destination=0x06007800;
    dma->control=0x84000140;
    (void)dma->control;
    dma=(volatile struct BackgroundDma90 *)0x040000D4;
    dma->source=paletteAddress;
    dma->destination=0x05000000;
    dma->control=0x80000010;
    (void)dma->control;
    *(volatile u16 *)0x04000008 = 0xF01;
    *(volatile u16 *)0x04000000 |= 0x100;
    modeWork->backgroundSetup.word04 = 5;
    *stateWork = 1;
}

void sub_0806E6E4(void) {

    u16 packed[0x258];
    u16 expanded[0x280];
    volatile struct BackgroundDma90 *dma;
    u32 paletteAddress;
    union State0TransferWork *modeWork;
    s32 *stateWork;
    u32 zero;
    u16 *zeroDestination;
    s32 nextRow;
    s32 packedOffset;
    u8 *rowBase;
    u16 *zeroBase;
    s32 rowOffset;
    s32 row;
    s32 remaining;
    u16 *destination;
    u16 *source;

    LZ77UnCompVram(&gUnknown_087F314C, (void *)0x06000000);
    LZ77UnCompVram(&gUnknown_087F384C, &packed[0]);
    row = 0;
    paletteAddress=(u32)&gUnknown_087F39CC;
    modeWork=&gState0TransferWork;
    stateWork=&gUnknown_0300137C;
    /* Keep separate whole-array views; this order preserves register roles. */
    zeroBase = expanded;
    zero = 0;
    rowBase = (u8 *)&expanded;
    do {
        rowOffset = row << 5;
        packedOffset = row << 4;
        nextRow = row + 1;
        packedOffset -= row;
        packedOffset <<= 2;
        source = (u16 *)((u32)packedOffset+(u32)packed);
        destination = (u16 *)((u32)(row<<6)+(u32)rowBase);
        remaining = 0x1D;
loop_2:
        *destination = *source;
        source += 1;
        destination += 1;
        remaining -= 1;
        if (remaining >= 0) {
            goto loop_2;
        }
        zeroDestination=(u16 *)((u32)zeroBase+((rowOffset+0x1E)<<1));
        *zeroDestination = zero;
        zeroDestination=(u16 *)((u32)zeroBase+((rowOffset+0x1F)<<1));
        *zeroDestination = zero;
        row = nextRow;
    } while (row <= 0x13);
    dma=(volatile struct BackgroundDma90 *)0x040000D4;
    dma->source=(u32)(&expanded[0]);
    dma->destination=0x06007800;
    dma->control=0x84000140;
    (void)dma->control;
    dma=(volatile struct BackgroundDma90 *)0x040000D4;
    dma->source=paletteAddress;
    dma->destination=0x05000000;
    dma->control=0x80000010;
    (void)dma->control;
    modeWork->backgroundSetup.word10 = 0x34;
    *(volatile u16 *)0x04000008 = 0xF02;
    *(volatile u16 *)0x04000000 |= 0x100;
    modeWork->backgroundSetup.word04 = 7;
    *stateWork = 1;
}
