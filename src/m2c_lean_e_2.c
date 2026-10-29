/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "encounter_parts.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "render_work.h"
#include "scene_view.h"
#include "sound_samples.h"
#include "sound_voice.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "state0_work.h"
#include "tile_text.h"

struct Setup19720 { u8 unknown00[0xC9]; u8 kindC9; u8 unknownCA[0x36]; };

extern const u8 *const gCommands19720[] asm("gUnknownPointers_083B6100");
extern const u8 gUnknown_083C4DE0[];
extern const u8 gUnknown_083C4DE4[];
extern const u8 gUnknown_083C4DE8[];
extern const u8 gUnknown_083C4DEC[];
extern const u8 gUnknown_083C4DF0[];
extern const u8 gUnknown_083C4DF4[];
extern const u8 gUnknown_083C4E10[];
extern const u8 gUnknown_083C4E14[];
extern const u8 gUnknown_083C4E18[];
extern const u8 gUnknown_083C4E1C[];
extern struct Setup19720 gSetup19720[] asm("gSetupBuffer_03000590");
extern void sub_08019D9C(u32 index, u32 slot, u32 mode, u32 priority);

void sub_08019720(u32 arg0);
void sub_0803F1C8(u32 width, u32 height, u32 x, u32 y, const void *data, u32 control, u32 entryOffset);

void sub_08019720(u32 arg0) {


    if (gSetup19720[arg0].kindC9 == 0)
        return;
    if (gSetup19720[arg0].kindC9 == 0xD || gSetup19720[arg0].kindC9 == 0xE)
    {
        struct FrameObject *objects = gFrameObjects;
        u32 slot = arg0 * 3 + 0x47;
        struct FrameObject *object = &objects[slot];
        if (object->flags != 0 && object->unknown23[0] == gSetup19720[arg0].kindC9)
            sub_08040BD8(gCommands19720[6], slot);
        else
            sub_08040B90(gCommands19720[6], arg0 * 3 + 0x47);
        sub_08041D04(gUnknown_083C4DE0, gUnknown_0300052E, 4);
        sub_08019D9C(arg0, 1, 1, gFrameObjects[0x5D + arg0 * 4].priority + 4);
    }
    else if (gSetup19720[arg0].kindC9 == 0x11 || gSetup19720[arg0].kindC9 == 0x12 || gSetup19720[arg0].kindC9 == 0x29)
    {
        struct FrameObject *objects = gFrameObjects;
        u32 slot = arg0 * 3 + 0x47;
        struct FrameObject *object = &objects[slot];
        if (object->flags != 0 && object->unknown23[0] == gSetup19720[arg0].kindC9)
            sub_08040BD8(gCommands19720[8], slot);
        else
            sub_08040B90(gCommands19720[8], arg0 * 3 + 0x47);
        sub_08041D04(gUnknown_083C4DEC, gUnknown_0300052E, 4);
        sub_08019D9C(arg0, 1, 1, gFrameObjects[0x5D + arg0 * 4].priority + 4);
    }
    else if (gSetup19720[arg0].kindC9 == 0x13 || gSetup19720[arg0].kindC9 == 0x14)
    {
        struct FrameObject *objects = gFrameObjects;
        u32 slot = arg0 * 3 + 0x47;
        struct FrameObject *object = &objects[slot];
        if (object->flags != 0 && object->unknown23[0] == gSetup19720[arg0].kindC9)
        {
            if (gSetup19720[arg0].kindC9 == 0x13)
                sub_08040BD8(gCommands19720[9], slot);
            else
                sub_08040BD8(gCommands19720[10], slot);
        }
        else
        {
            if (gSetup19720[arg0].kindC9 == 0x13)
                sub_08040B90(gCommands19720[9], arg0 * 3 + 0x47);
            else
                sub_08040B90(gCommands19720[10], arg0 * 3 + 0x47);
        }
        if (gSetup19720[arg0].kindC9 == 0x13)
            sub_08041D04(gUnknown_083C4DF0, gUnknown_0300052E, 4);
        else
            sub_08041D04(gUnknown_083C4DF4, gUnknown_0300052E, 4);
        sub_08019D9C(arg0, 1, 1, gFrameObjects[0x5D + arg0 * 4].priority - 2);
    }
    else if (gSetup19720[arg0].kindC9 == 0xF || gSetup19720[arg0].kindC9 == 0x10)
    {
        struct FrameObject *objects = gFrameObjects;
        u32 slot = arg0 * 3 + 0x47;
        struct FrameObject *object = &objects[slot];
        if (object->flags != 0 && object->unknown23[0] == gSetup19720[arg0].kindC9)
            sub_08040BD8(gCommands19720[7], slot);
        else
            sub_08040B90(gCommands19720[7], arg0 * 3 + 0x47);
        if (gSetup19720[arg0].kindC9 == 0xF)
            sub_08041D04(gUnknown_083C4DE4, gUnknown_0300052E, 4);
        else
            sub_08041D04(gUnknown_083C4DE8, gUnknown_0300052E, 4);
        sub_08019D9C(arg0, 1, 1, gFrameObjects[0x5D + arg0 * 4].priority + 4);
    }
    else if (gSetup19720[arg0].kindC9 == 0x2B)
    {
        struct FrameObject *objects = gFrameObjects;
        u32 slot = arg0 * 3 + 0x47;
        struct FrameObject *object = &objects[slot];
        if (object->flags != 0 && object->unknown23[0] == gSetup19720[arg0].kindC9)
            sub_08040BD8(gCommands19720[16], slot);
        else
            sub_08040B90(gCommands19720[16], arg0 * 3 + 0x47);
        sub_08041D04(gUnknown_083C4E10, gUnknown_0300052E, 4);
        sub_08019D9C(arg0, 1, 1, gFrameObjects[0x5D + arg0 * 4].priority + 4);
    }
    else if (gSetup19720[arg0].kindC9 == 0x2C)
    {
        struct FrameObject *objects = gFrameObjects;
        u32 slot = arg0 * 3 + 0x47;
        struct FrameObject *object = &objects[slot];
        if (object->flags != 0 && object->unknown23[0] == gSetup19720[arg0].kindC9)
            sub_08040BD8(gCommands19720[17], slot);
        else
            sub_08040B90(gCommands19720[17], arg0 * 3 + 0x47);
        sub_08041D04(gUnknown_083C4E14, gUnknown_0300052E, 4);
        sub_08019D9C(arg0, 1, 1, gFrameObjects[0x5D + arg0 * 4].priority + 4);
    }
    else if (gSetup19720[arg0].kindC9 == 0x2E)
    {
        struct FrameObject *objects = gFrameObjects;
        u32 slot = arg0 * 3 + 0x47;
        struct FrameObject *object = &objects[slot];
        if (object->flags != 0 && object->unknown23[0] == gSetup19720[arg0].kindC9)
            sub_08040BD8(gCommands19720[18], slot);
        else
            sub_08040B90(gCommands19720[18], arg0 * 3 + 0x47);
        sub_08041D04(gUnknown_083C4E18, gUnknown_0300052E, 4);
        sub_08019D9C(arg0, 1, 1, gFrameObjects[0x5D + arg0 * 4].priority + 4);
    }
    else if (gSetup19720[arg0].kindC9 == 0x2F)
    {
        struct FrameObject *objects = gFrameObjects;
        u32 slot = arg0 * 3 + 0x47;
        struct FrameObject *object = &objects[slot];
        if (object->flags != 0 && object->unknown23[0] == gSetup19720[arg0].kindC9)
            sub_08040BD8(gCommands19720[19], slot);
        else
            sub_08040B90(gCommands19720[19], arg0 * 3 + 0x47);
        sub_08041D04(gUnknown_083C4E1C, gUnknown_0300052E, 4);
        sub_08019D9C(arg0, 1, 1, gFrameObjects[0x5D + arg0 * 4].priority + 4);
    }
}

void sub_0803F1C8(u32 width, u32 height, u32 x, u32 y, const void *data, u32 control, u32 entryOffset) {

    const u16 *source;
    u32 base;
    u16 *out;
    u32 row;
    u32 column;
    s32 left;
    s32 rowsLeft;
    u32 xAddress;
    u32 screen;

    gTilemapEntryOffset = entryOffset;
    source = data;
    if (x < 0x20)
    {
        if (y < 0x20)
        {
            screen = control >> 8; screen &= 0x1F; screen <<= 11;
            xAddress = x * 2 + 0x06000000;
            base = screen + xAddress + (y << 6);
            rowsLeft = 0x20 - y;
            for (row = 0; row < height; row++)
            {
                left = 0x20 - x;
                out = (u16 *)base + (row << 5);
                for (column = 0; column < width; column++)
                {
                    *out = *source + gTilemapEntryOffset;
                    source++;
                    out++;
                    if (--left == 0)
                        out += 0x3E0;
                }
                if (--rowsLeft == 0)
                    base += 0x800;
            }
        }
        else
        {
            y -= 0x20;
            screen = control >> 8; screen &= 0x1F; screen <<= 11;
            xAddress = x * 2 + 0x06000000;
            screen += xAddress;
            screen += y << 6;
            base = screen + 0x1000;
            for (row = 0; row < height; row++)
            {
                left = 0x20 - x;
                out = (u16 *)base + (row << 5);
                for (column = 0; column < width; column++)
                {
                    *out = *source + gTilemapEntryOffset;
                    source++;
                    out++;
                    if (--left == 0)
                        out += 0x3E0;
                }
            }
        }
    }
    else
    {
        if (y < 0x20)
        {
            screen = control >> 8; screen &= 0x1F; screen <<= 11;
            xAddress = (x - 0x20) * 2 + 0x06000000;
            screen += xAddress;
            screen += y << 6;
            base = screen + 0x800;
            rowsLeft = 0x20 - y;
            for (row = 0; row < height; row++)
            {
                out = (u16 *)base + (row << 5);
                for (column = 0; column < width; column++)
                {
                    *out = *source + gTilemapEntryOffset;
                    source++;
                    out++;
                }
                if (--rowsLeft == 0)
                    base += 0x800;
            }
        }
        else
        {
            y -= 0x20;
            screen = control >> 8; screen &= 0x1F; screen <<= 11;
            xAddress = (x - 0x20) * 2 + 0x06000000;
            screen += xAddress;
            screen += y << 6;
            base = screen + 0x1800;
            for (row = 0; row < height; row++)
            {
                out = (u16 *)base + (row << 5);
                for (column = 0; column < width; column++)
                {
                    *out = *source + gTilemapEntryOffset;
                    source++;
                    out++;
                }
            }
        }
    }
}
