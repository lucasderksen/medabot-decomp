/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_work.h"

extern s8 sub_08036E54(s16);
extern u8 *gUnknown_083B6298;
extern u8 gUnknown_030018D2[];

void sub_08022C28(void);
void sub_0802B460(void);

void sub_08022C28(void) {
    u8 *setup = gSetupBuffer_03000590;
    u8 *work = gState0TransferWork.bytes;
    u8 *slot = &work[0x88];
    s32 zero;
    setup[(*slot << 8) + 0xC4] = (zero = 0, 0x1F);
    setup[(*slot << 8) + 0xC5] = zero;
    setup[(*slot << 8) + 0xC6] = sub_08036E54(*(s16 *) &work[0xE8]);
    setup[(*slot << 8) + 0xC7] = sub_08036E54(*(s16 *) &work[0xEC]);
    work[0xAA]++;
}

void sub_0802B460(void) {
    s32 found = 0;
    u32 i = 0;
    u8 *flags = gUnknown_030018D2;
    u8 **script = &gUnknown_083B6298;
    u8 *objects = (u8 *) gFrameObjects;
    u8 *stopped = objects + 0x862;
    do {
        if (*(u8 *) (i + (u32) flags) != 0) {
            sub_08040BD8(*script, i + 0x21);
            if (*stopped == 0xFF)
                found = 1;
        }
        stopped += 0x40;
        i++;
    } while (i <= 2);
    if (found)
        gState0TransferWork.bytes[0xAA]++;
}
