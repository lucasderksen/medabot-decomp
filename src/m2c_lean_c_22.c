/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "gba.h"
#include "record_helpers.h"
#include "sound_voice.h"
#include "state0_display.h"

struct DigitWork6FDA4 { u8 pad00[8]; s32 counter8; u8 pad0C[0x22]; u8 index2E; u8 pad2F; u16 table30[1]; };
struct DmaRegs6FDA4 { u32 source, destination, control; };

extern struct DigitWork6FDA4 gDigitWork6FDA4 asm("gCounter6ED08_03001800");

s32 sub_0806FDA4(u8 column);

s32 sub_0806FDA4(u8 column) {

    struct DigitWork6FDA4 *work = &gDigitWork6FDA4;
    u16 tile[1];
    u32 offset;
    u8 k;

    if (!(work->index2E <= 0x27))
        return 1;
    if (!(work->counter8 & 1)) {
        k = work->index2E;
        offset = (u8)(k / 10u) << 6;
        offset += (u8)(k % 10u) << 1;
        tile[0] = work->table30[k + column] + 0x8001;
        {
            volatile struct DmaRegs6FDA4 *dma = (void *)0x040000D4;
            dma->source = (u32)tile;
            dma->destination = offset + 0x0600FB0A;
            dma->control = 0x80000001;
            (void)dma->control;
        }
        work->index2E++;
    }
    return 0;
}
