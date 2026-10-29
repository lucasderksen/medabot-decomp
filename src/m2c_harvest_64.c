/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "frame.h"
#include "state0_callbacks.h"
#include "state0_work.h"


void sub_08024C44(void);
void sub_08026340(void);
void sub_08027CB0(void);
void sub_0802C714(void);
void sub_0802C758(void);
void sub_0802FD4C(void);
void sub_0802FD84(void);

void sub_08024C44(void) {
    u8 *var_r1;
    u8 var_r0;

    if (gFrameObjects[0x21].scaleX == 0x40) {
        sub_08074DE0(0x3CU);
        gState0TypedWork.widths.word86 = 0;
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gFrameObjects[0x21].scaleX -= 8;
        gFrameObjects[0x21].scaleY = gFrameObjects[0x21].scaleY - 8;
    }
}

void sub_08026340(void) {
    u8 *var_r1;
    u8 var_r0;

    if (gFrameObjects[0x21].scaleX == 0x50) {
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gFrameObjects[0x21].scaleX += 4;
        gFrameObjects[0x21].scaleY = gFrameObjects[0x21].scaleY + 4;
    }
}

void sub_08027CB0(void) {
    u8 *var_r1;
    u8 var_r0;

    gState0TypedWork.widths.word86 += 1;
    gFrameObjects[0x21].angle = (gFrameObjects[0x21].angle + 0x40) & 0x3FF;
    if (gFrameObjects[0x22].scaleX == 0x40) {
        sub_08074DE0(0x30U);
        gState0TypedWork.bytes[0x84] = 0x3C;
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gFrameObjects[0x22].scaleX -= 8;
        gFrameObjects[0x22].scaleY = gFrameObjects[0x22].scaleY - 8;
    }
}

void sub_0802C714(void) {
    u8 *var_r1;
    u8 var_r0;

    if (gFrameObjects[0x21].scaleX == 0x40) {
        gState0TypedWork.widths.word86 = 0x3C;
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gFrameObjects[0x21].scaleX += 4;
        gFrameObjects[0x21].scaleY = gFrameObjects[0x21].scaleY + 4;
    }
}

void sub_0802C758(void) {
    u8 *var_r1;
    u8 var_r0;

    if (gFrameObjects[0x21].scaleX == 0x20) {
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gFrameObjects[0x21].scaleX -= 4;
        gFrameObjects[0x21].scaleY = gFrameObjects[0x21].scaleY - 4;
    }
}

void sub_0802FD4C(void) {
    u8 *var_r1;
    u8 var_r0;

    if (gFrameObjects[0x21].scaleX == 0x60) {
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gFrameObjects[0x21].scaleX += 4;
        gFrameObjects[0x21].scaleY = gFrameObjects[0x21].scaleY + 4;
    }
}

void sub_0802FD84(void) {
    u8 *var_r1;
    u8 var_r0;

    if (gFrameObjects[0x21].scaleX == 0x40) {
        gState0TypedWork.widths.word86 = 0x3C;
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gFrameObjects[0x21].scaleX -= 4;
        gFrameObjects[0x21].scaleY = gFrameObjects[0x21].scaleY - 4;
    }
}
