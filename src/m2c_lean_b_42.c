/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "main_callbacks.h"
#include "rom_libc.h"
#include "sound_samples.h"
#include "state0_work.h"

extern const u8 gUnknown_080B0108[];
extern s32 sub_0807CDF8(s32, s32);
extern u8 gUnknown_03007010;

void sub_08071804(void);

void sub_08071804(void) {

    u8 frames[4];
    s32 i;
    s32 index;
    u8 bit;

    memcpy(frames, gUnknown_080B0108, 4);
    i = 0;
    bit = 1;
    index = 0x16;
loop:
        if (gUnknown_03007010 & bit) {
            u32 root = (u32)gFrameObjects;
            struct FrameObject *object = (struct FrameObject *)((index << 6) + root);
            s32 r = sub_0807CDF8((u16)object->value32, object->unknown23[0]);
            s32 k = index;
            u32 base = root;
            do {
            if (r == 0) {
                if (++object->commandOffset > 3)
                    object->commandOffset = r;
                object->frameAndGroup = object->value30 + frames[object->commandOffset];
            }
            ((struct FrameObject *)((k << 6) + base))->value32++;
            } while (0);
        }
        index++;
        i++;
        bit <<= 1;
    if (i <= 3)
        goto loop;
}
