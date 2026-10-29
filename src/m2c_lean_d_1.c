/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "composite_graphics.h"
#include "continued_commands.h"
#include "continued_map_data.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "graphics.h"
#include "state0_display.h"
#include "state0_work.h"

extern void *gSetupPointer_030057D8;

void sub_08053280(u32 indexWord);

void sub_08053280(u32 indexWord) {

    u16 index = indexWord;
    s32 field;
    if ((index & 1) == 0)
    {
        u8 *data = gSetupPointer_030057D8;
        u8 value;
        data += index / 2;
        field = (*data & 0x70) >> 4;
        value = field + 1;
        *data = (*data & 0x8F) | (value << 4);
    }
    else
    {
        u8 *data = gSetupPointer_030057D8;
        data += index / 2;
        field = *data & 7;
        field++;
        *data = field | (*data & 0xF8);
    }
}
