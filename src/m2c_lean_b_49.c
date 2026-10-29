/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "graphics.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "render_work.h"
#include "scene_view.h"
#include "serial.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

struct Context614 {
    u8 unknown00[2];
    u16 counter;
    u8 unknown04[0x11];
    u8 scale;
    u8 speed;
};

extern s32 sub_0807CD2C(s32 value, s32 divisor);

s32 sub_0805B614(struct FrameObject *objects);

s32 sub_0805B614(struct FrameObject *objects) {

    s32 done;
    s32 divisor;
    s32 center;
    u8 scale;
    s32 angles[8];
    struct Context614 *context;

    done = 0;
    divisor = 0x400;
    center = 0x50;
    context = gMainContextPointer_03006F74;
    scale = context->scale;
    angles[0] = context->speed * context->counter++;
    angles[1] = angles[0] - 0x80;
    angles[2] = angles[0] - 0x100;
    angles[3] = angles[0] - 0x180;
    angles[4] = angles[0] - 0x200;
    angles[5] = angles[0] - 0x280;
    angles[6] = angles[0] - 0x300;
    angles[7] = angles[0] - 0x380;
    {
        s32 y;
        if (gSineTable[angles[7] & 0x3FF] < 0)
            y = (gSineTable[angles[7] & 0x3FF] / divisor) * scale >> 3;
        else
            y = -((gSineTable[angles[7] & 0x3FF] / divisor) * scale >> 3);
        do {
        objects[0].screenY = y + 0x50;
        } while (0);
    }
    if (gSineTable[angles[6] & 0x3FF] < 0)
        objects[1].screenY = center + ((gSineTable[angles[6] & 0x3FF] / divisor) * scale >> 3);
    else
        objects[1].screenY = center - ((gSineTable[angles[6] & 0x3FF] / divisor) * scale >> 3);
    if (gSineTable[angles[5] & 0x3FF] < 0)
        objects[2].screenY = center + ((gSineTable[angles[5] & 0x3FF] / divisor) * scale >> 3);
    else
        objects[2].screenY = center - ((gSineTable[angles[5] & 0x3FF] / divisor) * scale >> 3);
    if (gSineTable[angles[4] & 0x3FF] < 0)
        { struct FrameObject *p = &objects[3]; p->screenY = center + ((gSineTable[angles[4] & 0x3FF] / divisor) * scale >> 3); }
    else
        { struct FrameObject *p = &objects[3]; p->screenY = center - ((gSineTable[angles[4] & 0x3FF] / divisor) * scale >> 3); }
    if (gSineTable[angles[3] & 0x3FF] < 0)
        { struct FrameObject *p = &objects[4]; p->screenY = center + ((gSineTable[angles[3] & 0x3FF] / divisor) * scale >> 3); }
    else
        { struct FrameObject *p = &objects[4]; p->screenY = center - ((gSineTable[angles[3] & 0x3FF] / divisor) * scale >> 3); }
    if (gSineTable[angles[2] & 0x3FF] < 0)
        { struct FrameObject *p = &objects[5]; p->screenY = center + ((gSineTable[angles[2] & 0x3FF] / divisor) * scale >> 3); }
    else
        { struct FrameObject *p = &objects[5]; p->screenY = center - ((gSineTable[angles[2] & 0x3FF] / divisor) * scale >> 3); }
    if (gSineTable[angles[1] & 0x3FF] < 0)
        { struct FrameObject *p = &objects[6]; p->screenY = center + ((gSineTable[angles[1] & 0x3FF] / divisor) * scale >> 3); }
    else
        { struct FrameObject *p = &objects[6]; p->screenY = center - ((gSineTable[angles[1] & 0x3FF] / divisor) * scale >> 3); }
    if (gSineTable[angles[0] & 0x3FF] < 0)
        { struct FrameObject *p = &objects[7]; p->screenY = center + ((gSineTable[angles[0] & 0x3FF] / divisor) * scale >> 3); }
    else
        { struct FrameObject *p = &objects[7]; p->screenY = center - ((gSineTable[angles[0] & 0x3FF] / divisor) * scale >> 3); }
    if (((struct Context614 *)gMainContextPointer_03006F74)->scale == 0)
        done = 1;
    else {
        ((struct Context614 *)gMainContextPointer_03006F74)->scale--;
        ((struct Context614 *)gMainContextPointer_03006F74)->speed++;
    }
    return done;
}
