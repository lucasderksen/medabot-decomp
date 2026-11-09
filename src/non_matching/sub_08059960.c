/*
 * sub_08059960: not matching yet. The build assembles asm/non_matching/sub_08059960.inc
 * in its place; the C below is the closest attempt (docs/drafts/README.md).
 */

#include "global.h"
#include "action_aux_data.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "bitfields.h"
#include "composite_graphics.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "fallback_map_assets.h"
#include "frame.h"
#include "fresh_helpers.h"
#include "graphics.h"
#include "later_graphics.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "map_metadata.h"
#include "map_object_spawns.h"
#include "object_numeric_helpers.h"
#include "packed_fields.h"
#include "palette_transfer_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "scene_animation.h"
#include "scene_setup_data.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

struct NavigationWork9960
{
    u8 unknown00[0x20];
    u16 half20;
};
extern struct NavigationWork9960 gNavigationWork9960 asm("gContinuedOtherWork_030057A0");
extern u16 gUnknown_03006432;
extern u16 gUnknown_03006434;
extern u16 gNavigationBuffer9960[] asm("gLaterBuffer_030055A0");

static inline struct FrameObject *SetupNavigationObject(u32 index, s32 dx, s32 dy)
{
    struct FrameObject *obj = &gFrameObjects[index];
    struct FrameObject *shadow;
    s32 px, py, sx, sy;

    obj->value30 = gNavigationWork9960.half20;
    px = (obj->positionX.value & 0xFF) | ((gUnknown_03006432 + dx) << 8);
    obj->positionX.value = px;
    py = (obj->positionY & 0xFF) | ((gUnknown_03006434 + dy) << 8);
    obj->positionY = py;
    obj->flags = 0xC804;
    gFrameObjects[index].unknown2C[2] = 1;
    shadow = &gFrameObjects[index + 0x2A];
    shadow->flags = 0xCC0C;
    sx = (px >> 8) - gBgScroll1.x;
    obj->screenX = sx;
    sy = (py >> 8) - gBgScroll1.y;
    obj->screenY = sy;
    shadow->screenX = sx;
    shadow->screenY = sy + (u16)(gFrameObjects[index].unknown2C[0] - 5);
    return obj;
}

NONMATCH("asm/non_matching/sub_08059960.inc", void sub_08059960(void))
{
    struct FrameObject *obj;
    struct FrameObject *shadow;
    struct FrameObject *objects;

    sub_080482CC(gNavigationWork9960.half20);
    sub_0804877C(gNavigationWork9960.half20);
    objects = gFrameObjects;
    SetupNavigationObject(0x31, -48, 16)->frameAndGroup = 0x0;
    sub_08049420(0x31, 0x4);
    SetupNavigationObject(0x32, -16, 16)->frameAndGroup = 0xf;
    sub_08049420(0x32, 0x9);
    SetupNavigationObject(0x33, 16, 16)->frameAndGroup = 0x1e;
    sub_08049420(0x33, 0xe);
    SetupNavigationObject(0x34, 48, 16)->frameAndGroup = 0x2d;
    sub_08049420(0x34, 0x13);
    SetupNavigationObject(0x35, -48, -16)->frameAndGroup = 0x30;
    sub_08049420(0x35, 0x14);
    SetupNavigationObject(0x36, -16, -16)->frameAndGroup = 0x3f;
    sub_08049420(0x36, 0x19);
    SetupNavigationObject(0x37, 16, -16)->frameAndGroup = 0x4e;
    sub_08049420(0x37, 0x1e);
    SetupNavigationObject(0x38, 48, -16)->frameAndGroup = 0x5d;
    sub_08049420(0x38, 0x23);
    sub_08048888(0x39);
    sub_08048888(0x63);
    obj = &objects[0x39];
    obj->value30 = gNavigationWork9960.half20;
    if (gCopiedBytes_083D2DBD[gNavigationWork9960.half20] == 3)
    {
        u8 frame = sub_080502C8(0);
        u8 palette = ExtractHighNibble(0);
        sub_08048864(0x39, 0xC804, frame, palette, 1);
        objects[0x39].byte2B = ExtractHighNibble(0);
        obj->positionX.value = (obj->positionX.value & 0xFF) | ((gUnknown_03006432 - 0x30) << 8);
        obj->positionY = (obj->positionY & 0xFF) | ((gUnknown_03006434 + 0x30) << 8);
        gNavigationBuffer9960[0x72] = 0xFFFF;
        objects[0x39].unknown2C[0] = 0;
        sub_08049420(0x39, 0x60);
    }
    shadow = &objects[0x63];
    shadow->flags = 0;
    if (gObjectAuxiliaryLookup_083D2D0D[gNavigationWork9960.half20] != 0)
    {
        shadow->flags = 0xCC0C;
        shadow->screenX = obj->screenX;
        shadow->screenY = obj->screenY + (u16)(objects[0x39].unknown2C[0] - 5);
    }
}
END_NONMATCH
