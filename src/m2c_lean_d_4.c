/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "frame_command_handlers.h"
#include "graphics.h"
#include "main.h"
#include "main_callbacks.h"
#include "sound_samples.h"
#include "state0_work.h"

extern const u8 gRandomBytes_083F7D80[];

s32 sub_0806B2F4(u32 indexWord);

s32 sub_0806B2F4(u32 indexWord) {

    u8 index = indexWord;
    struct FrameObject *base = gFrameObjects;
    struct FrameObject *obj = &base[index];
    s32 px;
    s32 py;
    s32 hi;

    hi = ((obj->positionX.value >> 8) + gScrollOscillationSines_083D6A2C[(obj->unknown23[0] + 0x40) & 0xFF]) << 8;
    px = (0xFF & obj->positionX.value) | hi;
    obj->positionX.value = px;
    hi = ((obj->positionY >> 8) + gScrollOscillationSines_083D6A2C[obj->unknown23[0]]) << 8;
    py = (0xFF & obj->positionY) | hi;
    obj->positionY = py;
    if (index > 11) {
        obj->screenX = (px >> 8) / 256 + 0x20;
        obj->screenY = 0x10 - (py >> 8) / 256;
    } else {
        obj->screenX = (px >> 8) / 128 + 0x20;
        obj->screenY = 0x10 - (py >> 8) / 128;
    }
    if (gFrameObjects[index].unknown1A > 8) {
        gFrameObjects[index].unknown1A = gRandomBytes_083F7D80[(gFrameCounter + index) & 0xFF] >> 3;
        gFrameObjects[index].commandDelay = 9;
    }
    return 1;
}
