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
#include "frame.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sprite_layouts.h"
#include "tile_text.h"

extern u16 sub_0807CEC8(u32 value, u32 divisor);
extern u16 sub_0807CF40(u32 value, u32 divisor);

void sub_0805A6C8(u16 number, u8 x, u8 y);

void sub_0805A6C8(u16 number, u8 x, u8 y) {

    volatile u16 *dst;
    u16 digit;
    u32 palette;
    u32 base;
    u32 block;

    palette = 1;
    base = 1;
    block = 0x16;
    dst = (volatile u16 *)(block << 11) + (x + 0x03000000) + (y << 5);
    digit = sub_0807CEC8(number, 10000);
    if (digit != 0)
        *dst++ = (digit + base) | (palette << 12);
    else
        *dst++;
    digit = sub_0807CF40(sub_0807CEC8(number, 1000), 10);
    if (digit != 0 || sub_0807CEC8(number, 10000) != 0)
        *dst++ = (digit + base) | (palette << 12);
    else
        *dst++;
    digit = sub_0807CF40(sub_0807CEC8(number, 100), 10);
    if (digit != 0 || sub_0807CEC8(number, 10000) != 0 || sub_0807CF40(sub_0807CEC8(number, 1000), 10) != 0)
        *dst++ = (digit + base) | (palette << 12);
    else
        *dst++;
    digit = sub_0807CF40(sub_0807CEC8(number, 10), 10);
    if (digit != 0 || sub_0807CEC8(number, 10000) != 0 || sub_0807CF40(sub_0807CEC8(number, 1000), 10) != 0
        || sub_0807CF40(sub_0807CEC8(number, 100), 10) != 0)
        *dst++ = (digit + base) | (palette << 12);
    else
        *dst++;
    *dst = (sub_0807CF40(number, 10) + base) | (palette << 12);

    dst = (volatile u16 *)(block << 11) + (x + 0x03000000) + ((y + 1) << 5);
    base = 0xB;
    digit = sub_0807CEC8(number, 10000);
    if (digit != 0)
        *dst++ = (digit + base) | (palette << 12);
    else
        *dst++;
    digit = sub_0807CF40(sub_0807CEC8(number, 1000), 10);
    if (digit != 0 || sub_0807CEC8(number, 10000) != 0)
        *dst++ = (digit + base) | (palette << 12);
    else
        *dst++;
    digit = sub_0807CF40(sub_0807CEC8(number, 100), 10);
    if (digit != 0 || sub_0807CEC8(number, 10000) != 0 || sub_0807CF40(sub_0807CEC8(number, 1000), 10) != 0)
        *dst++ = (digit + base) | (palette << 12);
    else
        *dst++;
    digit = sub_0807CF40(sub_0807CEC8(number, 10), 10);
    if (digit != 0 || sub_0807CEC8(number, 10000) != 0 || sub_0807CF40(sub_0807CEC8(number, 1000), 10) != 0
        || sub_0807CF40(sub_0807CEC8(number, 100), 10) != 0)
        *dst++ = (digit + base) | (palette << 12);
    else
        *dst++;
    *dst = (sub_0807CF40(number, 10) + base) | (palette << 12);
}
