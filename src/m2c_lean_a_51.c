/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "bios_lz77.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "encoded_label_catalog.h"
#include "encoded_labels.h"
#include "frame.h"
#include "part_label_banks.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "scene_view.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

extern u16 gUnknown_083AF600[];

void sub_080368C4(u8 *text, s32 first, s32 table, u16 x, u16 y);
void sub_080369C8(u8 *text, s32 first, s32 table, u16 x, u16 y);

void sub_080368C4(u8 *text, s32 first, s32 table, u16 x, u16 y) {

    u32 i;
    u32 k;

    for (i = 0; i <= 4; i++) {
        if (text[i] == 0xFE)
            return;
        gFrameObjects[first + i].flags = 0xC624;
        gFrameObjects[first + i].tableSelector = 0;
        { s32 t = (s16)x; t += gUnknown_083AF600[k = table * 2]; gFrameObjects[first + i].screenX = t & 0x1FF; }
        { s32 t = (s16)y; t += gUnknown_083AF600[k + 1]; gFrameObjects[first + i].screenY = t & 0xFF; }
        gFrameObjects[first + i].priority = 0x80;
        gFrameObjects[first + i].frameAndGroup = text[i] + 0x2D00;
        gFrameObjects[first + i].unknown23[0] = 0;
        gFrameObjects[first + i].scaleY = 0x40;
        gFrameObjects[first + i].scaleX = 0x40;
        gFrameObjects[first + i].palette = 0xE;
        switch (text[6]) {
        case 2:
            gFrameObjects[first + i].screenX = 0xFFFC + gFrameObjects[first + i].screenX + i * 8;
            break;
        case 3:
            gFrameObjects[first + i].screenX = 0xFFF8 + gFrameObjects[first + i].screenX + i * 8;
            break;
        case 4:
            gFrameObjects[first + i].screenX = 0xFFF4 + gFrameObjects[first + i].screenX + i * 8;
            break;
        }
    }
}

void sub_080369C8(u8 *text, s32 first, s32 table, u16 x, u16 y) {

    u32 i;
    u32 k;

    for (i = 0; i <= 4; i++) {
        if (text[i] == 0xFE)
            return;
        gFrameObjects[first + i].flags = 0xC404;
        gFrameObjects[first + i].tableSelector = 0;
        { s32 t = (s16)x; t += gUnknown_083AF600[k = table * 2]; gFrameObjects[first + i].screenX = t & 0x1FF; }
        { s32 t = (s16)y; t += gUnknown_083AF600[k + 1]; gFrameObjects[first + i].screenY = t & 0xFF; }
        gFrameObjects[first + i].priority = 0x80;
        gFrameObjects[first + i].frameAndGroup = text[i] + 0x2D00;
        gFrameObjects[first + i].unknown23[0] = 0;
        gFrameObjects[first + i].palette = 0xE;
        switch (text[6]) {
        case 2:
            gFrameObjects[first + i].screenX = 0xFFFC + gFrameObjects[first + i].screenX + i * 8;
            break;
        case 3:
            gFrameObjects[first + i].screenX = 0xFFF8 + gFrameObjects[first + i].screenX + i * 8;
            break;
        case 4:
            gFrameObjects[first + i].screenX = 0xFFF4 + gFrameObjects[first + i].screenX + i * 8;
            break;
        }
    }
}
