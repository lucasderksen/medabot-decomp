/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "frame.h"
#include "frame_objects.h"
#include "state0_work.h"

s32 sub_08037424(s32);

void sub_08025570(void);
void sub_08027D98(void);
void sub_0802A274(void);

void sub_08025570(void) {
    u8 *var_r1;
    u8 var_r0;

    sub_08037424(0x21);
    gFrameObjects[0x22].screenX = (s16) (u16) gFrameObjects[0x21].screenX;
    gFrameObjects[0x22].screenY = (s16) (u16) gFrameObjects[0x21].screenY;
    if (gFrameObjects[0x21].scaleX == 1) {
        sub_08040CD0(0x21U, 2U);
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gFrameObjects[0x21].scaleX -= 1;
        gFrameObjects[0x21].scaleY -= 1;
        gFrameObjects[0x22].scaleX -= 1;
        gFrameObjects[0x22].scaleY = gFrameObjects[0x22].scaleY - 1;
    }
}

void sub_08027D98(void) {
    u8 *var_r1;
    u8 var_r0;

    gState0TypedWork.widths.word86 += 1;
    gFrameObjects[0x21].angle = (gFrameObjects[0x21].angle + 0x40) & 0x3FF;
    if (gFrameObjects[0x21].scaleX == 4) {
        sub_08040CD0(0x21U, 2U);
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gFrameObjects[0x21].scaleX -= 4;
        gFrameObjects[0x21].scaleY -= 4;
        gFrameObjects[0x22].scaleX -= 4;
        gFrameObjects[0x22].scaleY = gFrameObjects[0x22].scaleY - 4;
    }
}

void sub_0802A274(void) {
    u8 *var_r1;
    u8 var_r0;

    if (gFrameObjects[0x21].scaleX == 0x40) {
        gState0TypedWork.widths.word86 = 0x3C;
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gFrameObjects[0x21].scaleX += 4;
        gFrameObjects[0x21].scaleY += 4;
        gFrameObjects[0x22].scaleX += 4;
        gFrameObjects[0x22].scaleY = gFrameObjects[0x22].scaleY + 4;
    }
}
