/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "continued_map_data.h"
#include "continued_numeric.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

struct ProjectionCounts { u8 unknown00[0x1CC]; s32 record; s32 count; };


void sub_08053B04(const float *first, const float *second, const float *third);
void sub_08058070(u32 mode);

void sub_08053B04(const float *first, const float *second, const float *third) {

    s32 i;
    float x, y, z;

    x = first[0];
    y = second[0];
    z = third[0];
    sub_08053BE0(x, y, z);
    for (i = 1; i < ((struct ProjectionCounts *)gLaterBuffer_03005350)->count; i++) {
        x = first[i];
        y = second[i];
        z = third[i];
        *(s32 *)((u8 *)gSetupPointer_03006D30 + ((struct ProjectionCounts *)gLaterBuffer_03005350)->record * 0x300 + 0x20C) = i;
        sub_08053C14(x, y, z);
    }
    x = first[0];
    y = second[0];
    z = third[0];
    *(s32 *)((u8 *)gSetupPointer_03006D30 + ((struct ProjectionCounts *)gLaterBuffer_03005350)->record * 0x300 + 0x20C) = 0;
    sub_08053C14(x, y, z);
}

void sub_08058070(u32 mode) {

    u32 palette;

    palette = sub_08057D80(0) == 0 ? 12 : 13;
    sub_08048864(0x20, 0xC004, 0x91, palette, 1);
    gFrameObjects[0x20].screenX = (16 - gContinuedCommandWork_030064A0[0x6F]) * 8 + (mode * 8 + 0x90);
    gFrameObjects[0x20].screenY = 0x18;
    gFrameObjects[0x20].priority = 0xFF;
    palette = sub_08057D80(1) == 0 ? 12 : 13;
    sub_08048864(0x21, 0xC004, 0x92, palette, 1);
    gFrameObjects[0x21].screenX = (16 - gContinuedCommandWork_030064A0[0x6F]) * 8 + (mode * 8 + 0x90);
    gFrameObjects[0x21].screenY = 0x28;
    gFrameObjects[0x21].priority |= 0xFF;
    palette = sub_08057D80(2) == 0 ? 12 : 13;
    sub_08048864(0x22, 0xC004, 0x93, palette, 1);
    gFrameObjects[0x22].screenX = (16 - gContinuedCommandWork_030064A0[0x6F]) * 8 + (mode * 8 + 0x90);
    gFrameObjects[0x22].screenY = 0x38;
    gFrameObjects[0x22].priority |= 0xFF;
    palette = sub_08057D80(3) == 0 ? 12 : 13;
    sub_08048864(0x23, 0xC004, 0x94, palette, 1);
    gFrameObjects[0x23].screenX = (16 - gContinuedCommandWork_030064A0[0x6F]) * 8 + (mode * 8 + 0x90);
    gFrameObjects[0x23].screenY = 0x48;
    gFrameObjects[0x23].priority |= 0xFF;
}
