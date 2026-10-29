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

struct BackgroundDma6E7EC {
    u32 source;
    u32 destination;
    u32 control;
};

extern const u16 gBackgroundPalette_087F4444[16];
extern const u8 gCompressed6E7EC_087F39EC[2168];
extern const u8 gCompressed6E7EC_087F4264[480];

void sub_0806E7EC(void);

void sub_0806E7EC(void) {

    u16 packedTiles[0x258];
    u16 expandedTiles[0x280];
    u16 *outputTile;
    volatile struct BackgroundDma6E7EC *dma;
    u32 paletteAddress;
    union State0TransferWork *workRoot;
    u32 *sceneState;
    u32 zero;
    u16 *zeroDestination;
    s32 nextRow;
    u16 tileBias;
    s32 packedOffset;
    u32 rowBase;
    u16 *zeroBase;
    s32 rowWordOffset;
    s32 row;
    s32 remaining;
    u16 *sourceTile;

    LZ77UnCompVram(gCompressed6E7EC_087F39EC, (void *)0x06008000);
    LZ77UnCompVram(gCompressed6E7EC_087F4264, &packedTiles[0]);
    row = 0;
    sceneState = &gUnknown_0300137C;
    paletteAddress = (u32)&gBackgroundPalette_087F4444;
    workRoot = &gState0TransferWork;
    zeroBase = expandedTiles;
    zero = 0;
    rowBase = (u32)&expandedTiles;
    tileBias = 0x1000;
    /* The structured inner loop is required for the original register allocation. */
    do {
        rowWordOffset = row << 5;
        packedOffset = row << 4;
        nextRow = row + 1;
        packedOffset -= row;
        packedOffset <<= 2;
        sourceTile = (u16 *)((u32)packedOffset+(u32)packedTiles);
        outputTile = (u16 *)((row<<6)+rowBase);
        remaining = 0x1D;
        do {
            *outputTile = *sourceTile + tileBias;
            sourceTile += 1;
            outputTile += 1;
            remaining -= 1;
        } while (remaining >= 0);
        zeroDestination = (u16 *)((u32)zeroBase+((rowWordOffset+0x1E)<<1));
        *zeroDestination = zero;
        zeroDestination = (u16 *)((u32)zeroBase+((rowWordOffset+0x1F)<<1));
        *zeroDestination = zero;
        row = nextRow;
    } while (row <= 0x13);
    dma = (volatile struct BackgroundDma6E7EC *)0x040000D4;
    dma->source = (u32)(&expandedTiles[0]);
    dma->destination = 0x0600F800;
    dma->control = 0x84000140;
    (void)dma->control;
    dma = (volatile struct BackgroundDma6E7EC *)0x040000D4;
    dma->source = paletteAddress;
    dma->destination = 0x05000020;
    dma->control = 0x80000010;
    (void)dma->control;
    *(volatile u16 *)0x0400000A = 0x1F0B;
    *(volatile u16 *)0x04000000 |= 0x200;
    *(volatile u16 *)0x04000050 = 0x241;
    *(volatile u16 *)0x04000052 = 0x10;
    workRoot->backgroundSetup.word04 = 9;
    *sceneState = 3;
}
