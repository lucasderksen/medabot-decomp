/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "effect_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern const void *const gState0NextCommands_083B6100[];
extern s32 gUnknown_03000648;
extern s32 sub_08035740(void *, s16, s32);

void sub_080236E0(void);
void sub_080239C0(void);
void sub_08023F48(void);
void sub_08026378(void);
void sub_0802A7E0(void);
s32 sub_08032FD0(s32 slot, s32 kind);
s32 sub_08035880(s32 slot, s32 row, s32 other);
void sub_0805F9C8(void);

void sub_080236E0(void) {
    u8 *work = gState0TransferWork.bytes;
    u32 index = work[0x87] << 8;
    u8 *base = (u8 *) &gUnknown_03000648;
    u8 *record = (u8 *) (index + (u32) base);
    record++;
    sub_08035740(record, *(s16 *) (work + 0xEC), 0x78);
    work[0xAA]++;
}

void sub_080239C0(void) {
    const void *const *commands = gState0NextCommands_083B6100;
    sub_08040BD8(commands[gState0TypedWork.bytes[0x84]], 0x21);
    if (gFrameObjects[0x21].commandStopped == 0xFF)
        gState0TransferWork.bytes[0xAA]++;
}

void sub_08023F48(void) {
    if (gFrameObjects[0x21].scaleX == 0x40) {
        gState0TransferWork.bytes[0xAA]++;
    } else {
        gFrameObjects[0x21].scaleX += 8;
        gFrameObjects[0x21].scaleY += 8;
    }
}

void sub_08026378(void) {
    if (gFrameObjects[0x21].scaleX == 0x40) {
        gState0TypedWork.widths.word86 = 0x3C;
        gState0TransferWork.bytes[0xAA]++;
    } else {
        gFrameObjects[0x21].scaleX -= 4;
        gFrameObjects[0x21].scaleY -= 4;
    }
}

void sub_0802A7E0(void) {
    if (gFrameObjects[0x21].scaleX == 0x40) {
        gState0TypedWork.widths.word86 = 0x3C;
        gState0TransferWork.bytes[0xAA]++;
    } else {
        gFrameObjects[0x21].scaleX += 4;
        gFrameObjects[0x21].scaleY += 4;
    }
}

s32 sub_08032FD0(s32 slot, s32 kind) {
    u32 i = 0;
    u8 *setup = gSetupBuffer_03000590;
    u8 *record;
    slot <<= 8;
    setup += 0x4A;
    record = slot + setup;
    do {
        if (record[0xF] != 0 && record[0] == kind)
            return 1;
        record += 0x18;
        i++;
    } while (i <= 2);
    return 0;
}

s32 sub_08035880(s32 slot, s32 row, s32 other) {
    u8 *setup = gSetupBuffer_03000590;
    u32 address = row * 0x18;
    u32 offset = slot << 8;
    address += offset;
    address += (u32) setup;
    if (*(u8 *) (address + 0x49) == 0x22 && setup[(other << 8) + 0x91] == 0x64)
        return 1;
    return 0;
}

void sub_0805F9C8(void) {
    if (sub_0803FB3C(gMain2ScriptSlots_0848521C[16]) != 0) {
        u16 *context = gMainContextPointer_03006F74;
        u16 count = context[1]++;
        if (count > 0x3C)
            gUnknown_0300137C = 0xD;
    }
}
