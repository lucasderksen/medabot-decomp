/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "rom_libc.h"

struct AnimContext62DFC {
    u8 pad00[0x3A];
    s16 timer3A;
};

extern const u8 gUnknown_080B00B8[8];
extern const u8 gUnknown_080B00C0[8];
extern struct AnimContext62DFC *gAnimContext62DFC asm("gMainContextPointer_03006F74");
extern void sub_0806D398(void);

void sub_08062DFC(void);
void sub_0806CB28(void);

void sub_08062DFC(void) {

    s32 frame;
    s32 i;
    s32 src;
    s32 dst;
    s32 next;
    s32 tiles;

    switch (gAnimContext62DFC->timer3A / 128) {
    case 0:
    case 1:
        frame = gAnimContext62DFC->timer3A >> 5;
        break;
    case 2:
        frame = gAnimContext62DFC->timer3A >> 4;
        break;
    case 3:
        frame = gAnimContext62DFC->timer3A >> 3;
        break;
    case 4:
        frame = gAnimContext62DFC->timer3A >> 2;
        break;
    default:
        frame = gAnimContext62DFC->timer3A >> 1;
        break;
    }
    frame &= 3;
    if (--gAnimContext62DFC->timer3A < 0)
        gAnimContext62DFC->timer3A = 0x3F;
    do {
    i = 0;
    next = frame + 2;
    tiles = 0x0600D800;
    dst = 0x1C0;
    src = frame << 9;
    } while (0);
loop:
    CpuSet((void *)(src + tiles), (void *)(dst + 0x0600E804), 12);
    CpuSet((void *)((((3 & next) * 8 + i) << 6) + tiles), (void *)(dst + 0x0600E820), 12);
    dst += 0x40;
    src += 0x40;
    i++;
    if (i <= 7)
        goto loop;
}

void sub_0806CB28(void) {

    u8 low[8];
    u8 high[8];

    memcpy(low, gUnknown_080B00B8, 8);
    memcpy(high, gUnknown_080B00C0, 8);
    switch (gFrameObjects[0].commandDelay) {
    case 1:
        if (gFrameObjects[0].unknown1A < 0x18) {
            if (gFrameObjects[0].unknown1A < 0x10) {
                gFrameObjects[0].scaleX += 4;
                if (gFrameObjects[0].scaleX > 0x40)
                    gFrameObjects[0].scaleX = 0x40;
            } else {
                gFrameObjects[0].scaleY += 8;
                if (gFrameObjects[0].scaleY > 0x40)
                    gFrameObjects[0].scaleY = 0x40;
            }
        }
        break;
    case 2:
        if (gFrameObjects[0].unknown1A < 0x18) {
            if (gFrameObjects[0].unknown1A < 8) {
                gFrameObjects[0].scaleY -= 8;
                if (gFrameObjects[0].scaleY < 4)
                    gFrameObjects[0].scaleY = 4;
            } else {
                gFrameObjects[0].scaleX -= 4;
                if (gFrameObjects[0].scaleX < 4)
                    gFrameObjects[0].scaleX = 4;
            }
        }
        break;
    case 3:
        sub_0806D398();
        break;
    case 4:
    case 5:
    case 6:
        if (gFrameObjects[0].unknown1A < 9) {
            if ((u8)(gFrameObjects[0].scaleX += 8) > 0x40)
                gFrameObjects[0].scaleX = 0x40;
            if ((u8)(gFrameObjects[0].scaleY -= 4) < 0x40)
                gFrameObjects[0].scaleY = 0x40;
        } else if (gFrameObjects[0].unknown1A > 0x33) {
            if (gFrameObjects[0].scaleX > 8)
                gFrameObjects[0].scaleX -= 8;
            gFrameObjects[0].scaleY += 4;
            if (gFrameObjects[0].scaleY > 0x60)
                gFrameObjects[0].scaleY = 0x60;
        }
        break;
    case 7:
        if (gFrameObjects[0].unknown1A < 9) {
            if ((u8)(gFrameObjects[0].scaleX += 8) > 0x40)
                gFrameObjects[0].scaleX = 0x40;
            if ((u8)(gFrameObjects[0].scaleY -= 4) < 0x40)
                gFrameObjects[0].scaleY = 0x40;
        } else if (gFrameObjects[0].unknown1A > 0x15) {
            *(volatile u16 *)0x04000052 = (high[gFrameObjects[0].unknown1A - 0x16] << 8) | low[gFrameObjects[0].unknown1A - 0x16];
        }
        break;
    }
}
