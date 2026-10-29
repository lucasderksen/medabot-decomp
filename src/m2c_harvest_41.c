/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "sound_tables.h"
#include "background_state.h"
#include "frame.h"
#include "frame_objects.h"
#include "state0_work.h"


void sub_0802186C(void);
void sub_08023A04(void);
void sub_08023E50(void);
void sub_0802C820(void);
void sub_0802F48C(void);
void sub_0802FDC8(void);

void sub_0802186C(void) {
    u8 *var_r1;
    u8 var_r0;

    if (gFrameObjects[0x21].scaleX == 8) {
        sub_08040CD0(0x21U, 3U);
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gFrameObjects[0x21].scaleX -= 8;
        gFrameObjects[0x22].scaleX -= 8;
        gFrameObjects[0x23].scaleX = gFrameObjects[0x23].scaleX - 8;
    }
}

void sub_08023A04(void) {
    if (gFrameObjects[0x21].scaleX == 8) {
        sub_08040CD0(0x21U, 1U);
        gState0TransferWork.bytes[0xAA] += 1;
    } else {
        gFrameObjects[0x21].scaleX -= 8;
        gFrameObjects[0x21].scaleY += 8;
    }
}

void sub_08023E50(void) {
    u8 *var_r1;
    u8 var_r0;

    if (gFrameObjects[0x21].scaleX == 8) {
        sub_08040D0C(0x21U, 1U);
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gFrameObjects[0x21].scaleX -= 8;
        gFrameObjects[0x21].scaleY = gFrameObjects[0x21].scaleY - 8;
    }
}

void sub_0802C820(void) {
    u8 *var_r1;
    u8 var_r0;

    if (gFrameObjects[0x21].scaleX == 4) {
        sub_08040CD0(0x21U, 1U);
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gFrameObjects[0x21].scaleX -= 4;
        gFrameObjects[0x21].scaleY = gFrameObjects[0x21].scaleY - 4;
    }
}

void sub_0802F48C(void) {
    u8 *var_r1;
    u8 var_r0;

    if (gFrameObjects[0x21].scaleX == 4) {
        sub_08040CD0(0x21U, 1U);
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gFrameObjects[0x21].scaleX -= 4;
        gFrameObjects[0x21].scaleY = gFrameObjects[0x21].scaleY - 4;
    }
}

void sub_0802FDC8(void) {
    u8 *var_r1;
    u8 var_r0;

    if (gFrameObjects[0x21].scaleX == 4) {
        sub_08040CD0(0x21U, 1U);
        gState0TransferWork.bytes[0xAA] = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        gFrameObjects[0x21].scaleX -= 4;
        gFrameObjects[0x21].scaleY = gFrameObjects[0x21].scaleY - 4;
    }
}

u32 sub_080732B8(u32 index) {
    u32 root = (u32)gUnknown_083ABB50;
    return *(const u16 *)(root + (index << 1));
}
