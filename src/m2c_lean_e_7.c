/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "fallback_map_assets.h"
#include "frame.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "scene_animation.h"
#include "state0_work.h"

struct Main2MenuTiles
{
    u8 unknown00[0x38];
    u16 tileBase38;
};


void sub_08060BE4(u32 selection, u32 frame);

void sub_08060BE4(u32 selection, u32 frame) {

    s16 tile;
    s32 i;
    s32 k;
    u16 *top;
    u16 *bottom;
    u32 column;
    u32 row;
    u16 palette;
    u32 screenBlock;
    const u8 *columns;

    tile = (s16)(selection * 4 + ((struct Main2MenuTiles *)gMainContextPointer_03006F74)->tileBase38 + 5) | (s16)0xC000;
    *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000152) = tile++;
    *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000154) = tile++;
    *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000192) = tile++;
    *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000194) = tile;
    for (i = 0; i <= 3; i++)
    {
        /* Wrap: cse1 forgets the BG0CNT constants before the bottom row, and the
           column table constant is hoisted by loop.c after them as in the reference. */
        do {
            screenBlock = (*(volatile u16 *)0x0400000C >> 8) & 0x1F;
            columns = (const u8 *)0x080AFB80;
            {
                top = (u16 *)((screenBlock << 11) + (column = columns[i * 2] * 2 + 0x06000000)
                              + ((row = ((const u8 *)0x080AFB81)[i * 2]) << 6));
            }
        } while (0);
        bottom = (u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + column + ((row + 1) << 6));
        /* Wrap: weights the frame & 8 test so it is allocated before the hoisted constants. */
        do { if (!(frame & 8)) goto plain; } while (0);
        palette = i == selection ? 0x6000 : 0x5000;
        goto chosen;
    plain:
        palette = 0x5000;
    chosen:
        for (k = 0; k < 8; k++)
        {
            *top = (0xFFF & *top) | palette;
            top++;
            *bottom = (0xFFF & *bottom) | palette;
            bottom++;
        }
    }
}
