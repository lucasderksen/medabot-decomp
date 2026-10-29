/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern u32 sub_08033184(u32);
extern u8 *gUnknown_083B6280;
extern u8 gUnknown_030018D2[];
extern void sub_0803836C(void);

void sub_08029984(void);
void sub_08029B04(void);

void sub_08029984(void) {
    s32 found = 0;
    u8 *work;
    u8 *setup;
    u8 *flags;
    u32 i;
    do {
    sub_0803836C();
    work = gState0TransferWork.bytes;
    work[0x60] = sub_08032FC4(work[0x87]);
    } while (0);
    i = 0;
    setup = gSetupBuffer_03000590;
    flags = work + 0xD2;
    do {
        u32 slot = work[0x60] + i;
        u32 address = (slot << 8) + (u32) setup;
        if (*(u8 *) (address + 0x40) != 0 && *(u8 *) (address + 0x59) != 0 && sub_08033184(slot) != 0) {
            found = 1;
            *(u8 *) (i + (u32) flags) = found;
        }
        i++;
    } while (i <= 2);
    if (found == 0)
        gState0TransferWork.bytes[0xAA]++;
    else
        gState0TransferWork.bytes[0xAA] += 2;
}

void sub_08029B04(void) {
    s32 found = 0;
    u32 i = 0;
    u8 *flags = gUnknown_030018D2;
    u8 **commands = &gUnknown_083B6280;
    struct FrameObject *objects = gFrameObjects;
    u8 *stopped = &objects[0x21].commandStopped;
    u32 slot = 0x21000000;
    do {
        if (*(u8 *) (i + (u32) flags) != 0) {
            sub_08040BD8(*commands, slot >> 24);
            if (*stopped == 0xFF)
                found = 1;
        }
        stopped += 0x40;
        slot += 0x01000000;
        i++;
    } while (i <= 2);
    if (found != 0) {
        sub_08040CD0(0x21, 3);
        gState0TransferWork.bytes[0xAA]++;
    }
}
