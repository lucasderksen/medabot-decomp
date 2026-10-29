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
#include "state0_work.h"

extern u8 *gUnknown_083B627C;
extern u8 gUnknown_030018D2[];

void sub_080292D4(void);

void sub_080292D4(void) {
    s32 found = 0;
    u32 i = 0;
    u8 *flags = gUnknown_030018D2;
    u8 **commands = &gUnknown_083B627C;
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
