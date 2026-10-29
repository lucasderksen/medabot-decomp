/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_commands.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "post_dispatch.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

extern const u16 gUnknown_080AF8B8[][3];
extern const u8 *const gUnknownPointers_083B1A08[];
#include "encounter_records.h"
extern u8 gFreshWork_03006D38[];

void sub_08050358(u32 first, u32 second, u32 third, u32 fourth);
void sub_0805B188(s32 index, s32 part, s32 slot);
void sub_0805BE0C(u32 first);

void sub_08050358(u32 first, u32 second, u32 third, u32 fourth) {

    u8 flags = first;
    u8 b = second;
    u8 c = third;
    s32 low;
    u8 d = fourth;
    u32 index = flags & 0xF;
    struct FrameObject *object;

    if ((flags & 0xF0) && sub_08052C68(c, d) && gFreshWork_03006D38[3])
        sub_08047BA8(gSetupByteLookup_083D2B66[gFreshWork_03006D38[3]]);
    sub_0804DBD0(index, (u8)sub_08050710());
    do {
        sub_080503FC((u8)sub_0804DBF0(index), b, c, d);
        if (flags & 0x40) {
            u32 root;
            s32 y;
            s32 high;
            s32 slot = sub_0804DBF0(index);
            root = (u32)gFrameObjects;
            object = (struct FrameObject *)(root + ((slot + 0x4F) << 6));
            y = object->positionY;
            high = ((y >> 8) + 5) << 8;
            low = 0xFF;
            low = y & low;
            object->positionY = low | high;
        }
    } while (0);
}

void sub_0805B188(s32 index, s32 part, s32 slot) {

    switch (part) {
    case 0:
        LeDecompress(gUnknownPointers_083B1A08[(index << 2) + (index << 1)], (void *)(slot * 0x80 + 0x06013340));
        break;
    case 1:
        LeDecompress(gUnknownPointers_083B1A08[(index << 2) + (index << 1) + 1], (void *)(slot * 0x80 + 0x06013340));
        break;
    case 2:
        LeDecompress(gUnknownPointers_083B1A08[(index << 2) + (index << 1) + 3], (void *)(slot * 0x80 + 0x06013340));
        break;
    case 3:
        LeDecompress(gUnknownPointers_083B1A08[(index << 2) + (index << 1) + 5], (void *)(slot * 0x80 + 0x06013340));
        break;
    }
    gFrameObjects[slot + 0x6E].palette = *(const u8 *)((u32)gUnknownBytes_083BEB94 + index) + 4;
}

void sub_0805BE0C(u32 first) {

    u8 selectedRow = first;
    u8 choices[3] = { gMainByte_03001788, gMainByte_03001360, gMainByte_03000B94 };
    s32 row;
    s32 column;
    s32 k;
    volatile u16 *p;
    u16 mask;
    u16 tile;
    u16 value;
    u16 bits;

    for (row = 0; row <= 2; row++) {
        for (column = 0; column <= 2; column++) {
            p = (volatile u16 *)((((*(volatile u16 *)0x04000008 >> 8) & 0x1F) << 11) + 0x06000000) + (((row * 3 + 11) << 5) + 7);
            mask = gUnknown_080AF8B8[row][column];
            for (k = 0; k < 16; k++) {
                if (mask & 0x8000) {
                    tile = *p & 0xFFF;
                    if (selectedRow == row)
                        *p = (choices[row] == column ? 0xA000 : 0x8000) | tile;
                    else
                        *p = (choices[row] == column ? 0x9000 : 0x8000) | tile;
                }
                mask <<= 1;
                p++;
            }
        }
    }
}
