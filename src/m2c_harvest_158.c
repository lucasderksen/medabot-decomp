/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_display.h"

struct LocalTextTransferWork { u8 pad00[8]; s32 counter8; u8 pad0C[0xC4]; u8 cursorD0; u8 padD1; u16 tilesD2[13]; u8 padEC[12]; };
struct LocalTextDmaRegisters { const void *volatile source; void *volatile destination; volatile u32 control; };

extern const u8 *const gUnknown_08485ACC[8];
extern struct LocalTextTransferWork gGraphicsTransferCounter;
extern u8 gUnknown_030018D2[26];

s32 sub_0806FCCC(u8 arg0);

s32 sub_0806FCCC(u8 arg0) {
    s32 temp_r5;
    s32 phase;
    u32 cursor;
    struct LocalTextDmaRegisters *dma;
    const u8 *temp_r1;
    u8 temp_r3;

    temp_r1 = gUnknown_08485ACC[arg0];
    cursor = gGraphicsTransferCounter.cursorD0;
    temp_r1 += cursor;
    phase = gGraphicsTransferCounter.counter8;
    temp_r5 = 1 & phase;
    if (temp_r5 != 0) {
        if (*temp_r1 == 0x14) {
            return 1;
        }
        goto block_12;
    }
    if (*temp_r1 == 0x14) {
        if (phase & 8) {
            gGraphicsTransferCounter.tilesD2[cursor] = temp_r5;
        } else {
            gGraphicsTransferCounter.tilesD2[cursor] = 0x9078;
        }
        dma = (struct LocalTextDmaRegisters *)0x040000D4;
        dma->source = gUnknown_030018D2;
        dma->destination = (void *)0x0600FC44;
        dma->control = 0x8000000D;
        (void)dma->control;
        return 1;
    }
    temp_r3 = *temp_r1;
    if (temp_r3 == 0x15) {
        gGraphicsTransferCounter.tilesD2[cursor] = temp_r5;
    } else {
        gGraphicsTransferCounter.tilesD2[cursor] = temp_r3 + 0x9064;
    }
    gGraphicsTransferCounter.cursorD0 += 1;
    dma = (struct LocalTextDmaRegisters *)0x040000D4;
    dma->source = gGraphicsTransferCounter.tilesD2;
    dma->destination = (void *)0x0600FC44;
    dma->control = 0x8000000D;
        (void)dma->control;
block_12:
    return 0;
}
