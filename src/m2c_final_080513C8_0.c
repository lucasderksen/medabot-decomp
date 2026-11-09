/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "action_aux_data.h"
#include "action_scene_data.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_commands.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "graphics.h"
#include "later_graphics.h"
#include "link_menu.h"
#include "map_metadata.h"
#include "map_object_spawns.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "render_work.h"
#include "scene_animation.h"
#include "scene_setup_data.h"
#include "scene_view.h"
#include "sound_samples.h"
#include "sound_voice.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_debug_menu.h"
#include "state0_inventory.h"
#include "state0_work.h"
#include "tile_text.h"

struct SelectionWork13C8
{
    u8 unknown000[0x5DC];
    struct SelectionRecord records[0x44];   /* 5DC */
    u8 unknown7FC[2];
    u8 byte7FE;                             /* 7FE */
    u8 byte7FF;                             /* 7FF */
    u16 width;                              /* 800 */
    u8 unknown802[0xE];
    u8 map[0x438];                          /* 810 */
    u16 halfC48;                            /* C48 */
    u16 halfC4A;                            /* C4A */
    u8 unknownC4C[0x42];
    u16 halfC8E;                            /* C8E */
    u8 unknownC90[0x24];
    s8 byteCB4;                             /* CB4 */
    u8 unknownCB5[5];
    u8 byteCBA;                             /* CBA */
};
struct ObjectAttributes13C8
{
    u16 attributes;
    u16 unknown02;
};
union Coordinate13C8
{
    s32 value;
    struct { u32 fraction : 8; s32 integer : 24; } parts;
};
struct ObjectView13C8
{
    u8 unknown00[2];
    s16 screenX;                            /* 02 */
    s16 screenY;                            /* 04 */
    u8 unknown06[6];
    union Coordinate13C8 x;                 /* 0C */
    union Coordinate13C8 y;                 /* 10 */
    u8 unknown14[0x17];
    u8 byte2B;                              /* 2B */
    u8 unknown2C[4];
    s16 value30;                            /* 30 */
    u8 unknown32[0xE];
};

extern const struct SelectionRecord *const gMapObjectLists13C8[] asm("gMapObjectLists_08483234");
extern s32 PaletteFor13C8(u8 index) asm("sub_08048684");
extern struct ObjectAttributes13C8 gObjectAttributes13C8[] asm("gLaterBuffer_030055A0");
extern struct SelectionWork13C8 gSelectionWork13C8 asm("gContinuedWork_030057E0");
extern void Refresh13C8(u8 index) asm("sub_080487C8");
extern void SetFrame13C8(u8 index, u8 value, void *record) asm("sub_0805218C");
extern void SetObject13C8(u8 index, u16 flags, u8 frame, u8 palette, u8 selector) asm("sub_08048864");
extern void SetPose13C8(u8 index, u8 value) asm("sub_08049420");

void sub_080513C8(s32 value);

void sub_080513C8(s32 value) {

    s32 slot;
    struct SelectionRecord saved[64];
    s32 k;
    s32 row;
    s32 count;
    s32 found;
    struct SelectionRecord *records;
    s32 skip;
    const struct SelectionRecord *entry;
    s32 hi;
    s32 objIndex;
    s32 i;

    records = gSelectionRecords_03005DBC;
    sub_08049714(saved, 0x200);
    sub_080497C0(records, saved, 0x200);
    sub_08049714(records, 0x200);
    count = 0;
    slot = 0;
    k = 0;
    for (row = 0; row < 32; row++)
    {
        entry = gMapObjectLists13C8[gSelectionWork13C8.byte7FE];
        while (entry->x != 0xFF)
        {
            if (((entry->unknown06 >> gSelectionWork13C8.byte7FF) & 1) && entry->frame == row
                && sub_080531E0(0xFFF & entry->attributes) == 0)
            {
                skip = 0;
                found = 0;
                if (value == 0)
                {
                    skip = 0; /* FAKE MATCH: redundant store gives this arm a block of its own, so gcse inserts the work reload and slot + 1 here as the reference does */
                    goto store;
                }
                if (value >= 0)
                {
                    if (value <= 2)
                    {
                        for (k = 0; k <= 0x3F; k++)
                        {
                            if ((0xFFF & entry->attributes) == (0xFFF & saved[k].attributes))
                                found = 1;
                            if (found != 0)
                                break;
                        }
                        if (k != 0x40)
                        {
                            if (value == 1)
                            {
                                skip = 0; /* FAKE MATCH: dead store; flow deletes it only after reload, so value and k are reloaded before the value == 2 test as in the reference */
                                goto store;
                            }
                            if (value == 2 && saved[k].flags.bits.active != 1)
                                skip = 1;
                        }
                        else if (value == 2)
                        {
                            skip = 1;
                        }
                    }
                }
                if (skip != 0)
                    goto next;
            store:
                hi = entry->flags.value >> 4;
                gSelectionWork13C8.records[slot].x = entry->x;
                gSelectionWork13C8.records[slot].y = entry->y;
                gSelectionWork13C8.records[slot].attributes = entry->attributes;
                switch (entry->attributes >> 12)
                {
                case 0:
                case 4:
                case 6:
                    gSelectionWork13C8.map[entry->y * (gSelectionWork13C8.width >> 1) + entry->x] = 7;
                    break;
                }
                gSelectionWork13C8.records[slot].flags.bits.active = 1;
                if (entry->flags.value != 0xFF)
                {
                    if (count <= 0x1D)
                    {
                        switch (entry->attributes >> 12)
                        {
                        case 0:
                        case 2:
                        case 4:
                        case 6:
                            SetObject13C8(count + 0x31, 0xC804, hi * 12, hi, 1);
                            gSelectionWork13C8.records[slot].flags.bits.auxiliary = 1;
                            gFrameObjects[count + 0x31].value30 = PaletteFor13C8(hi);
                            Refresh13C8(count + 0x31);
                            if (gObjectAuxiliaryLookup_083D2D0D[(u16)gFrameObjects[count + 0x31].value30] != 0)
                                SetObject13C8(count + 0x5B, 0xCC0C, 0x90, 0xE, 1);
                            break;
                        }
                        objIndex = count + 0x31;
                        gSelectionWork13C8.records[slot].flags.bits.index = count;
                        hi = entry->flags.value >> 4;
                        gObjectAttributes13C8[objIndex].attributes = entry->attributes & 0xFFF;
                        {
                            struct ObjectView13C8 *objects = (struct ObjectView13C8 *)gFrameObjects;

                            objects[objIndex].byte2B = hi;
                            objects[objIndex].x.parts.integer = entry->x * 16 + gSelectionWork13C8.halfC48;
                            objects[objIndex].y.parts.integer = entry->y * 16 + gSelectionWork13C8.halfC4A;
                        }
                        SetFrame13C8(objIndex, 0xF & entry->flags.value, &gSelectionWork13C8.records[slot]);
                        SetPose13C8(objIndex, hi * 4 + (0xF & entry->flags.value));
                        if (value != 0 && found != 0)
                        {
                            SetFrame13C8(objIndex, saved[k].frame, &gSelectionWork13C8.records[slot]);
                            SetPose13C8(objIndex, saved[k].frame + hi * 4);
                        }
                        {
                            struct ObjectView13C8 *objects = (struct ObjectView13C8 *)gFrameObjects;
                            s32 obj = count + 0x31;
                            s32 shadow = count + 0x5B;

                            objects[obj].unknown2C[0] = 0;
                            objects[shadow].x.parts.integer = objects[obj].x.parts.integer;
                            objects[shadow].y.parts.integer = objects[obj].y.parts.integer - 5;
                            objects[shadow].screenX = objects[obj].screenX;
                            objects[shadow].screenY = objects[obj].screenY - 5;
                        }
                    }
                    count++;
                }
            next:
                slot++;
            }
            entry++;
        }
    }
    if (gSelectionWork13C8.halfC8E != 0)
    {
        for (i = 0; i <= 0x3F; i++)
        {
            if ((0xFFF & records->attributes) == gSelectionWork13C8.halfC8E)
            {
                gSelectionWork13C8.byteCB4 = i;
                break;
            }
            records++;
        }
    }
    gSelectionWork13C8.byteCBA = 2;
}
