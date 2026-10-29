/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "main_callbacks.h"
#include "state0_work.h"

extern u16 gSetup6D7A0_saved0300180C[];
extern u16 gUnknown_030017EE[];

s32 sub_0806DE9C(u8 index);

s32 sub_0806DE9C(u8 index) {

    u32 root = (u32)gFrameObjects;
    struct FrameObject *object = (struct FrameObject *)(root + (index << 6));
    u8 *stepp = &object->commandStopped;
    u8 step = *stepp;
    u32 zero;
    u8 size;

    if (*stepp > 30)
        return 0;
    if (*stepp == 0 || *stepp == 30) {
        volatile u32 *dma;
        zero = 0;
        dma = (volatile u32 *)0x040000D4;
        dma[0] = (u32)&zero;
        dma[1] = 0x050002C0;
        dma[2] = 0x85000000 | (0x20 / 4);
        dma[2];
    } else if (*stepp <= 14) {
        size = step * 2;
        {
            volatile u32 *dma;
            zero = 0;
            dma = (volatile u32 *)0x040000D4;
            dma[0] = (u32)&zero;
            dma[1] = 0x050002C0;
            dma[2] = 0x85000000 | ((0x20 - size) / 4);
            dma[2];
        }
        {
            volatile u32 *dma = (volatile u32 *)0x040000D4;
            dma[0] = (u32)gSetup6D7A0_saved0300180C;
            dma[1] = 0x050002E0 - size;
            dma[2] = 0x80000000 | (size / 2);
            dma[2];
        }
    } else if (*stepp == 15) {
        volatile u32 *dma = (volatile u32 *)0x040000D4;
        dma[0] = (u32)gSetup6D7A0_saved0300180C;
        dma[1] = 0x050002C0;
        dma[2] = 0x80000000 | (0x1C / 2);
        dma[2];
    } else {
        size = (30 - step) * 2;
        {
            volatile u32 *dma;
            zero = 0;
            dma = (volatile u32 *)0x040000D4;
            dma[0] = (u32)&zero;
            dma[1] = 0x050002C0 + size;
            dma[2] = 0x85000000 | ((0x20 - size) / 4);
            dma[2];
        }
        {
            volatile u32 *dma = (volatile u32 *)0x040000D4;
            dma[0] = (u32)&gUnknown_030017EE[object->commandStopped];
            dma[1] = 0x050002C0;
            dma[2] = 0x80000000 | (size / 2);
            dma[2];
        }
    }
    gFrameObjects[index].commandStopped++;
    return 1;
}
