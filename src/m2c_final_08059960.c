/*
 * sub_08059960: sets up the eight navigation frame objects 0x31-0x38 and their
 * shadows, then object 0x39. Byte-verified; names and types provisional.
 * Fake match: see the FAKE MATCH comments (docs/NONMATCHING.md).
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

union NavCoord { s32 value; struct { u32 fraction : 8; s32 integer : 24; } parts; };
struct NavObject
{
    s16 flags;
    s16 screenX;
    s16 screenY;
    u16 frameAndGroup;
    u8 unknown08[4];
    union NavCoord x;
    union NavCoord y;
    u8 unknown14[0x17];
    u8 byte2B;
    u8 unknown2C[4];
    s16 value30;
    u8 unknown32[0xE];
};
extern struct NavObject gNavObjects[] asm("gFrameObjects");

/* Unused locals: each one is dead and only adds RTL before cse (see SetupNav). */
#define NAV_PAD_SUM { s32 pad = gUnknown_03006432 + dx; }
#define NAV_PAD_LOAD { u32 pad = gUnknown_03006432; }
#define NAV_PAD_10(p) p p p p p p p p p p
#define NAV_PAD_30(p) NAV_PAD_10(p) NAV_PAD_10(p) NAV_PAD_10(p)

/* A u16 index parameter is copied into a register; the 0x5D copy made for
   the third object is what the eighth object's frame store reuses. */
static inline struct NavObject *GetNav(u16 i)
{
    return &gNavObjects[i];
}

static inline struct NavObject *SetupNav(u32 index, s32 dx, s32 dy)
{
    struct NavObject *obj = &gNavObjects[index];
    struct NavObject *shadow;
    /* FAKE MATCH: dead padding; the reference's helper expands to enough RTL that
       cse's 1,000-insn table flush lands in the fifth call, inside the screenX store
       below (gives its adds r7, r6, #0 base copy and the sb/r8 constants after it). */
    NAV_PAD_30(NAV_PAD_SUM)
    NAV_PAD_10(NAV_PAD_LOAD) NAV_PAD_LOAD NAV_PAD_LOAD NAV_PAD_LOAD
    obj->value30 = gNavigationWork9960.half20;
    obj->x.parts.integer = gUnknown_03006432 + dx;
    obj->y.parts.integer = gUnknown_03006434 + dy;
    obj->flags = 0xC804;
    obj->unknown2C[2] = 1;
    shadow = GetNav(index + 0x2A);
    shadow->flags = 0xCC0C;
    gNavObjects[index].screenX = obj->x.parts.integer - gBgScroll1.x;
    obj->screenY = obj->y.parts.integer - gBgScroll1.y;
    shadow->screenX = obj->screenX;
    shadow->screenY = obj->screenY + (s16)(obj->unknown2C[0] - 5);
    return obj;
}

void sub_08059960(void)
{
    struct NavObject *obj;
    struct NavObject *shadow;
    u32 index;
    u32 shadowIndex;

    LoadObjTilesIntoAllSlots(gNavigationWork9960.half20);
    sub_0804877C(gNavigationWork9960.half20);
    {
        u32 zero = 0;
        SetupNav(0x31, -48, 16)->frameAndGroup = zero;
        sub_08049420(0x31, 0x04);
    }
    SetupNav(0x32, -16, 16)->frameAndGroup = 0x0f; sub_08049420(0x32, 0x09);
    SetupNav(0x33, 16, 16)->frameAndGroup = 0x1e; sub_08049420(0x33, 0x0e);
    SetupNav(0x34, 48, 16)->frameAndGroup = 0x2d; sub_08049420(0x34, 0x13);
    SetupNav(0x35, -48, -16)->frameAndGroup = 0x30; sub_08049420(0x35, 0x14);
    SetupNav(0x36, -16, -16)->frameAndGroup = 0x3f; sub_08049420(0x36, 0x19);
    SetupNav(0x37, 16, -16)->frameAndGroup = 0x4e; sub_08049420(0x37, 0x1e);
    SetupNav(0x38, 48, -16)->frameAndGroup = 0x5d; sub_08049420(0x38, 0x23);
    index = 0x39;
    shadowIndex = index + 0x2A;
    ResetFrameObjectSlot(index);
    ResetFrameObjectSlot(shadowIndex);
    obj = &gNavObjects[index];
    obj->value30 = gNavigationWork9960.half20;
    if (gCopiedBytes_083D2DBD[gNavigationWork9960.half20] == 3)
    {
        u8 frame = sub_080502C8(0);
        u8 palette = ExtractHighNibble(0);
        InitFrameObject(0x39, 0xC804, frame, palette, 1);
        obj->byte2B = ExtractHighNibble(0);
        obj->x.parts.integer = gUnknown_03006432 - 0x30;
        obj->y.parts.integer = gUnknown_03006434 + 0x30;
        gNavigationBuffer9960[0x72] = 0xFFFF;
        obj->unknown2C[0] = 0;
        sub_08049420(0x39, 0x60);
    }
    shadow = GetNav(shadowIndex);
    { FORCE_REGISTER(u16 none, r0) = 0; shadow->flags = none; } /* FAKE MATCH: pins the cleared flags value to r0; local-alloc otherwise picks r3 and shifts the registers of the lookup test */
    if (gObjectAuxiliaryLookup_083D2D0D[gNavigationWork9960.half20] != 0)
    {
        shadow->flags = 0xCC0C;
        shadow->screenX = obj->screenX;
        shadow->screenY = obj->screenY + (s16)(obj->unknown2C[0] - 5);
    }
}
