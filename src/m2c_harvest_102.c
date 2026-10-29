/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern const u8 *gState0NextCommands_083B6100[];
extern s32 gUnknown_0850F8F8;
extern s32 sub_0803725C(void);
extern u8 gUnknown_084CE3E8;
extern void sub_0803579C(u8,u8);
extern void sub_08035814(u8);

void sub_08021E2C(void);
void sub_08029004(void);
s32 sub_0806B1A8(u32 inputIndex);
s32 sub_0806B1D0(u32 inputIndex);
s32 sub_08070734(s32 slot);

void sub_08021E2C(void) {
    __typeof__(&gState0TransferWork.bytes[0]) member0;
    u8 *setup;
    u8 *record;
    u8 *var_r1;
    u32 var_r0;

    member0 = gState0TransferWork.bytes;
    sub_0803579C(member0[0x87], member0[0xA7]);
    sub_08035814(member0[0x87]);
    if (sub_0803725C() != 0) {
        member0[0xA6] = 0x1A;
        *(&member0[0xA6] + 4) = member0[0xAA] + 1;
    } else {
        setup = gSetupBuffer_03000590;
        record = setup + (member0[0x88] << 8);
        if (record[0xC9] == 0) {
        member0[0xA6] = 0x70;
        *(&member0[0xA6] + 4) = member0[0xAA] + 1;
    } else {
        sub_08036270();
        member0[0xAA] = 4;
        }
    }
}

void sub_08029004(void) {
    const u8 **commands;
    LeDecompress(&gUnknown_084CE3E8, (void *)0x06014800);
    CpuFastSet(&gUnknown_0850F8F8, (void *)0x050002E0, 8U);
    gFrameObjects[0x21].scaleX = 0x40;
    gFrameObjects[0x21].scaleY = 0x40;
    gFrameObjects[0x21].angle = 0;
    gFrameObjects[0x21].priority = 0xF0;
    commands = gState0NextCommands_083B6100;
    sub_08040B90(commands[35],0x21);
    CpuSet(&gFrameObjects[0x21], &gFrameObjects[0x22], 0x20U);
    CpuSet(&gFrameObjects[0x21], &gFrameObjects[0x23], 0x20U);
    CpuSet(&gFrameObjects[0x21], (u8*)gFrameObjects + 0x900, 0x20U);
    CpuSet(&gFrameObjects[0x21], &gFrameObjects[0x25], 0x20U);
    gFrameObjects[0x21].unknown23[1] = 0;
    gFrameObjects[0x22].unknown23[1] = 2;
    gFrameObjects[0x22].unknown23[2] = 0x1C;
    gFrameObjects[0x22].screenX = (u16) gFrameObjects[0x22].screenX - 0x10;
    gFrameObjects[0x22].screenY = (u16) gFrameObjects[0x22].screenY - 0x10;
    gFrameObjects[0x23].unknown23[1] = 2;
    gFrameObjects[0x23].unknown23[2] = 4;
    gFrameObjects[0x23].screenX = (u16) gFrameObjects[0x23].screenX + 0x10;
    gFrameObjects[0x23].screenY = (u16) gFrameObjects[0x23].screenY - 0x10;
    gFrameObjects[0x24].unknown23[1] = 2;
    gFrameObjects[0x24].unknown23[2] = 0x14;
    gFrameObjects[0x24].screenX = (u16) gFrameObjects[0x24].screenX - 0x10;
    gFrameObjects[0x24].screenY = (u16) gFrameObjects[0x24].screenY + 0x10;
    gFrameObjects[0x25].unknown23[1] = 2;
    gFrameObjects[0x25].unknown23[2] = 0xC;
    gFrameObjects[0x25].screenX = (u16) gFrameObjects[0x25].screenX + 0x10;
    gFrameObjects[0x25].screenY = (u16) gFrameObjects[0x25].screenY + 0x10;
    gState0TransferWork.bytes[0xAA] += 1;
}

s32 sub_0806B1A8(u32 inputIndex) {
    s32 slot = (s32)inputIndex;
    u32 shifted;
    struct FrameObject *objects;
    struct FrameObject *frame;
    shifted = slot << 24;
    objects = gFrameObjects;
    shifted >>= 18;
    frame = (void *)((u32)objects + shifted);
    frame->screenX += 2;
    if ((u32)frame->commandStopped < (u32)frame->unknown1A) return 0;
    return 1;
}

s32 sub_0806B1D0(u32 inputIndex) {
    s32 slot = (s32)inputIndex;
    u32 shifted;
    struct FrameObject *objects;
    struct FrameObject *frame;
    shifted = slot << 24;
    objects = gFrameObjects;
    shifted >>= 18;
    frame = (void *)((u32)objects + shifted);
    frame->screenX += -2;
    if ((u32)frame->commandStopped < (u32)frame->unknown1A) return 0;
    return 1;
}

s32 sub_08070734(s32 slot) {
    u32 shifted;
    struct FrameObject *objects;
    struct FrameObject *frame;
    shifted = slot << 24;
    objects = gFrameObjects;
    shifted >>= 18;
    frame = (void *)((u32)objects + shifted);
    if (frame->commandOffset <= 0x47) frame->commandOffset++;
    else if (frame->screenY < -0x50) {
        frame->screenY = 0xA0;
        frame->commandOffset = 0;
    } else frame->screenY -= 4;
    return 1;
}
