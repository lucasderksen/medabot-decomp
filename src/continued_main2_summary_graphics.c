#include "global.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "object_helpers.h"
#include "frame_objects.h"
#include "display_effects.h"
#include "effect_work.h"
#include "bg_scroll.h"
#include "record_helpers.h"
#include "compression.h"
#include "state0_inventory.h"
#include "equipment_helpers.h"
#include "main_callbacks.h"
struct Main2PhaseWork { u8 unknown00[0x84]; u8 phase; };
#define PHASE_WORK ((struct Main2PhaseWork *)gUnknown_03000440)
#define CONTEXT ((u8 *)gMainContextPointer_03006F74)
#define DISPCNT (*(volatile u16 *)0x04000000)

/* Only this observed halfword is represented, not a full context layout. */
struct Main2TileContext { u8 unknown00[0x36]; u16 halfword36; };
#define TILE_CONTEXT ((struct Main2TileContext *)gMainContextPointer_03006F74)

void sub_0805D790(void)
{
    volatile u16 *bg1 = (volatile u16 *)0x0400000A;
    volatile u16 *bg2, *bg3;
    u32 control = 0x1E05;
    u32 length;
    u8 *scratch;
    *bg1 = control;
    bg2 = (volatile u16 *)0x0400000C;
    control -= 0xFF;
    *bg2 = control;
    bg3 = (volatile u16 *)0x0400000E;
    control = 0x3C07;
    *bg3 = control;
    sub_0805BA34(gMain2StatsMap_0878F004, *bg1);
    sub_0805BA34(gMain2StatsMap_0878F1D4, *bg2);
    sub_0805BA34(gMain2StatsMap_0878F2F8, *bg3);
    {
        const u8 *source = gMain2StatsTiles_0878DE74;
        scratch = (u8 *)0x02030000;
        length = sub_08044D0C(source, scratch);
    }
    CpuSet(scratch, (void *)0x06004000, (length << 10) >> 11);
    {
        const u8 *source = gMain2AdditionalTiles_08785EC0;
        u32 destination = 0x06000000;
        destination += length;
        destination += 0x4000;
        LeDecompress(source, (void *)destination);
    }
    {
        struct Main2TileContext *context = TILE_CONTEXT;
        u32 zero;
        length >>= 5;
        length--;
        zero = 0;
        context->halfword36 = length;
        LeDecompress(gMain2ObjectTiles_08785FB4, (void *)0x06010000);
        gFrameObjects[0].flags = 0xC000;
        gFrameObjects[0].tableSelector = 2;
        gFrameObjects[0].palette = zero;
        gFrameObjects[0].frameAndGroup = 35;
        gFrameObjects[0].screenX = 208;
        gFrameObjects[0].screenY = 24;
    }
    gUnknown_0300137C++;
}
