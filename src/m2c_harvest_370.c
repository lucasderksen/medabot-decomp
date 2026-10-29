/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "tile_text.h"

extern u32 __udivsi3(u32 numerator, u32 denominator);
extern u32 __umodsi3(u32 numerator, u32 denominator);

void sub_0805A558(u32 number, u32 x, u32 y);

void sub_0805A558(u32 number, u32 x, u32 y) {

    u32 value = (u16)number;
    u32 column = (u8)x, row = (u8)y;
    s32 columnAddress;
    u16 digit;
    volatile u16 *cursor;
    u32 palette = 1;
    u32 glyphBase = 22;

    columnAddress = column * 2U + 0x0600B000U;
    cursor = (volatile u16 *)(columnAddress + (row << 6));
    digit = (u16)__udivsi3(value, 10000);
    if (digit) {
        *cursor = (digit + glyphBase) | (palette << 12);
    } else {
        *cursor = digit;
    }
    (void)*cursor;
    cursor++;

    digit = (u16)__umodsi3((u16)__udivsi3(value, 1000), 10);
    if (digit || (u16)__udivsi3(value, 10000)) {
        *cursor = (digit + glyphBase) | (palette << 12);
        palette <<= 12;
    } else {
        *cursor = digit;
        palette <<= 12;
    }
    (void)*cursor;
    cursor++;

    digit = (u16)__umodsi3((u16)__udivsi3(value, 100), 10);
    if (digit || (u16)__udivsi3(value, 10000) ||
        (u16)__umodsi3((u16)__udivsi3(value, 1000), 10)) {
        *cursor = (digit + glyphBase) | palette;
    } else {
        *cursor = digit;
    }
    (void)*cursor;
    cursor++;

    digit = (u16)__umodsi3((u16)__udivsi3(value, 10), 10);
    if (digit || (u16)__udivsi3(value, 10000) ||
        (u16)__umodsi3((u16)__udivsi3(value, 1000), 10) ||
        (u16)__umodsi3((u16)__udivsi3(value, 100), 10)) {
        *cursor = (digit + glyphBase) | palette;
    } else {
        *cursor = digit;
    }
    (void)*cursor;
    cursor++;
    *cursor = (__umodsi3(value, 10) + glyphBase) | palette;
}
