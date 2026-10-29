/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "record_helpers.h"
#include "state0_display.h"
#include "state0_work.h"


void sub_080491B8(u16 *destination, s32 row, s32 column, s32 width, s32 height, u32 value, u32 palette, u32 mode);
void sub_08049210(const u16 *source, u16 *destination, s32 row, s32 column, s32 width, s32 height, u32 tileOffset, u32 palette, u32 mode);
void sub_080492A8(const u16 *source, u16 *destination, s32 row, s32 column, s32 width, s32 height, u32 unused6, u32 unused7, u32 offset, u32 mode);

void sub_080491B8(u16 *destination, s32 row, s32 column, s32 width, s32 height, u32 value, u32 palette, u32 mode) {

    s32 stride;
    s32 i;
    u16 *next;
    s32 j;
    u16 *line;

    switch (mode) {
    case 0:
        stride = 0x20;
        break;
    case 1:
        stride = 0x40;
        break;
    }
    destination += stride * row + column;
    for (i = 0; i < height; i++) {
        line = destination;
        for (j = 0; j < width; j++)
            *destination++ = value + (palette << 12);
        next = line + stride;
        destination = next;
    }
}

void sub_08049210(const u16 *source, u16 *destination, s32 row, s32 column, s32 width, s32 height, u32 tileOffset, u32 palette, u32 mode) {

    s32 stride;
    s32 i;
    s32 j;
    u16 tile;
    u16 *line;
    u16 *next;

    switch (mode) {
    case 0:
        stride = 0x20;
        break;
    case 1:
        stride = 0x40;
        break;
    }
    destination += stride * row + column;
    for (i = 0; i < height; i++) {
        line = destination;
        for (j = 0; j < width; j++) {
            tile = *source;
            *destination++ = ((tile & 0x3FF) + tileOffset) | ((*source & 0xC00) | (palette << 12));
            source++;
        }
        next = line + stride;
        destination = next;
    }
}

void sub_080492A8(const u16 *source, u16 *destination, s32 row, s32 column, s32 width, s32 height, u32 unused6, u32 unused7, u32 offset, u32 mode) {

    s32 stride;
    s32 i;
    s32 j;
    u16 *line;
    const u16 *sourceLine;

    switch (mode) {
    case 0:
        stride = 0x20;
        break;
    case 1:
        stride = 0x40;
        break;
    }
    destination += stride * row + column;
    for (i = 0; i < height; i++) {
        sourceLine = source;
        line = destination;
        for (j = 0; j < width; j++) {
            *destination = *source + offset;
            destination++;
            source++;
        }
        source = sourceLine;
        destination = line + stride;
        source += stride;
    }
}
