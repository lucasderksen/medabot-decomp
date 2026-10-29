/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"

extern s32 (*gUnknown_08485994[])(u8);
extern s32 sub_0807CDF8(u16,u8);
extern u8 gUnknown_084859B4[];
extern void sub_0806B718(u8);

void sub_0806DE0C(void);

void sub_0806DE0C(void) {
    u8 i=0;
    struct FrameObject *frame;
    do {
        s32 index;
        s32 result;
        struct FrameObject *objects;
        objects = gFrameObjects;
        frame = &objects[i];
        if (frame->commandDelay != 0) {
            u8 *limits;
            u16 narrow_timer;
            u32 timer = frame->unknown1A + 1;
            frame->unknown1A = timer;
            narrow_timer = timer;
            limits = gUnknown_084859B4;
            index = frame->commandDelay - 1;
            if (sub_0807CDF8(narrow_timer,limits[index]) == 0) {
                result = gUnknown_08485994[index](i);
                if (result != 1) {
                    switch (result) {
                    case 1: break;
                    case 0: frame->commandDelay=0; frame->commandStopped=0; break;
                    case 0xFF: sub_0806B718(i); break;
                    }
                }
            }
        }
        i++;
    } while (i <= 4);
}
