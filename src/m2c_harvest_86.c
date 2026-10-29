/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "eeprom.h"
#include "frame.h"
#include "frame_objects.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_work.h"
#include "tile_text.h"

struct CallbackBacking {
    u8 prefix[0x18];
    s32 first;
    s32 second;
    s32 gap;
    s32 third;
    s32 fourth;
    s32 fifth;
    u8 sixth;
    u8 seventh;
    u8 padding[0xC];
    u8 active;
};

extern const u8 *gState0NextCommands_083B6100[];

void sub_08015BF4(u32 value);
void sub_0803CDCC(void);

void sub_08015BF4(u32 value) {
    if (value <= 2) {
        sub_08042698(3, 1, 1, 0x12, *(u16 *) 0x0400000A, 0xD20D);
        return;
    }
    sub_08042698(3, 1, 0x15, 0x12, *(u16 *) 0x0400000A, 0xD20D);
}

void sub_0803CDCC(void) {
    const u8 **commands = gState0NextCommands_083B6100;
    struct FrameObject *objects = gFrameObjects;
    u8 *work = gState0TypedWork.bytes;
    sub_08040BD8(commands[objects[work[0x12F]].unknown2C[1]], work[0x12F]);
    if (objects[work[0x12F]].commandStopped == 0xFF)
        sub_08040CD0(work[0x12F], 1);
}
