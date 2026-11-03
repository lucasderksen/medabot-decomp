/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "continued_blend_work.h"
#include "gba.h"
#include "main.h"
#include "record_helpers.h"
#include "scene_graphics_loads.h"
#include "sound_voice.h"
#include "state0_callbacks.h"
#include "state0_display.h"

struct DmaRegs72080 { u32 source, destination, control; };

extern u16 *gPalettePointer71FF80300700C;
extern u16 gUnknown_0202FE00[];
extern void sub_0806B718(u8);

s32 sub_08072080(void);

s32 sub_08072080(void) {

    u8 k;
    u8 inv;
    s32 i;
    if (gCounter6ED08_03001800.pad00[0x11] > 0x40) {
        sub_08074DE0(0xA);
        gCounter6ED08_03001800.pad00[0x10]++;
    } else {
        if (gCounter6ED08_03001800.pad00[0x11] <= 0x1F)
            k = 0x20 - gCounter6ED08_03001800.pad00[0x11];
        else
            k = gCounter6ED08_03001800.pad00[0x11] - 0x20;
        if (gCounter6ED08_03001800.pad00[0x11] == 0x20)
            sub_0806B718(0);
        if (gCounter6ED08_03001800.pad00[0x11] == 0x14)
            sub_08074DE0(0x51);
        inv = 0x20 - k;
        for (i = 0; i <= 0xFF; ) {
            gUnknown_0202FE00[i] = (((0x1F & gPalettePointer71FF80300700C[i]) * k + 0x1F * inv) >> 5)
                + ((((0x3E0 & gPalettePointer71FF80300700C[i]) * k + 0x3E0 * inv) >> 5) & 0x3E0)
                + ((((0x7C00 & gPalettePointer71FF80300700C[i]) * k + 0x7C00 * inv) >> 5) & 0x7C00);
            do { i++; } while (0); /* FAKE MATCH: loop-depth weight on the dest giv increment so dest outranks inv * 31 (r5/r7) */
        }
        {
            volatile struct DmaRegs72080 *dma = (void *)0x040000D4;
            dma->source = (u32)gUnknown_0202FE00;
            dma->destination = 0x05000200;
            dma->control = 0x84000080;
            (void)dma->control;
        }
    }
    if (gFrameCounter & 1)
        gCounter6ED08_03001800.pad00[0x11]++;
    return 0;
}
