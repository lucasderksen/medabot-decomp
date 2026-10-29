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

struct FadeWork6F9D8 { u8 pad00[6]; u16 count6; s32 step8; u8 pad0C[2]; u16 paletteE[16]; };
struct DmaRegs6F9D8 { u32 source, destination, control; };

extern struct FadeWork6F9D8 gFadeWork6F9D8 asm("gCounter6ED08_03001800");

s32 sub_0806F9D8(void);

s32 sub_0806F9D8(void) {

    u16 buf[16];
    s32 i;
    u16 red;
    u16 green;
    u16 blue;
    u16 *src;
    u16 *dst;
    s32 w;
    volatile s32 inv;
    s32 zero = 0;

    if (gFadeWork6F9D8.step8 == 0) {
        do {
        volatile struct DmaRegs6F9D8 *dma = (void *)0x040000D4;
        dma->source = 0x05000280;
        dma->destination = (u32)gFadeWork6F9D8.paletteE;
        dma->control = 0x80000010;
        (void)dma->control;
        for (i = 0; i < 16; i++)
            buf[i] = zero;
        } while (0);
        {
            volatile struct DmaRegs6F9D8 *dma = (void *)0x040000D4;
        dma->source = (u32)buf;
        dma->destination = 0x05000280;
        dma->control = 0x84000008;
        (void)dma->control;
        }
        { s32 v = *(volatile u16 *)0x04000050; s32 m = 0xFFEF; m &= v; *(volatile u16 *)0x04000050 = m; }
        *(volatile u16 *)0x04000000 |= 0x1B00;
        if (gFadeWork6F9D8.count6 == 0)
            gFadeWork6F9D8.count6 = 1;
    } else {
        if (gFadeWork6F9D8.step8 == gFadeWork6F9D8.count6 << 5) {
            volatile struct DmaRegs6F9D8 *dma;
            gFadeWork6F9D8.step8 = zero;
            dma = (void *)0x040000D4;
            dma->source = (u32)gFadeWork6F9D8.paletteE;
            dma->destination = 0x05000280;
            dma->control = 0x80000010;
            (void)dma->control;
            return 1;
        }
        if (gFadeWork6F9D8.step8 % gFadeWork6F9D8.count6 == 0) {
            w = gFadeWork6F9D8.step8 / gFadeWork6F9D8.count6;
            inv = 0x20 - w;
            for (i = 0, red = 0x1F, green = 0x3E0, src = gFadeWork6F9D8.paletteE, dst = buf, blue = 0x7C00; i < 16; i++) {
                *dst = (((red & *src) * w) >> 5)
                    + ((((green & *src) * w) >> 5) & green)
                    + ((((blue & *src) * w) >> 5) & blue);
                src++; dst++;
            }
            {
                volatile struct DmaRegs6F9D8 *dma = (void *)0x040000D4;
                dma->source = (u32)buf;
                dma->destination = 0x05000280;
                dma->control = 0x84000008;
                (void)dma->control;
            }
            if (gFadeWork6F9D8.step8 % (gFadeWork6F9D8.count6 * 2) == 0)
                *(volatile u16 *)0x04000054 = 0x10 - gFadeWork6F9D8.step8 / (gFadeWork6F9D8.count6 * 4);
        }
    }
    gFadeWork6F9D8.step8++;
    return zero & 1;
}
