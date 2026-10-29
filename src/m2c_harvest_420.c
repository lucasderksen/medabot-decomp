/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bios_lz77_streams.h"
#include "composite_graphics.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "fallback_map_assets.h"
#include "frame.h"
#include "gba.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "main_menu_data.h"
#include "map_metadata.h"
#include "native_le_streams.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "scene_graphics_loads.h"
#include "sound_samples.h"
#include "sound_voice.h"
#include "sound_work.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Main2MapContext
{
    u8 unknown00[0x17];
    u8 byte17;
    s8 byte18;
    u8 unknown19[0x1D];
    s16 halfword36;
};

extern const u8 gUnknown_080AFB20[];
extern const u8 gUnknown_087883F4[];
extern u8 gUnknown_030057E0[];

void sub_08060708(void);

void sub_08060708(void) {

    u32 block = 1;
    volatile u16 *bg1 = (volatile u16 *)0x0400000A;
    volatile u16 *bg2, *bg3;
    u32 length2;
    const u8 *source;
    u32 length;
    u32 control;
    u8 index;
    volatile u16 zero;


    control = 0x1E05;
    *bg1 = control;
    bg2 = (volatile u16 *)0x0400000C;
    control = 0x1D06;
    *bg2 = control;
    bg3 = (volatile u16 *)0x0400000E;
    control = 0x1C07;
    *bg3 = control;
    sub_0805BA34(gBiosLz77Stream_0878BA54, *bg1);
    sub_0805BA34(gBiosLz77Stream_0878BB28, *bg2);
    sub_0805BA34(gBiosLz77Stream_0878BC1C, *bg3);
    if (gMainSubstate == 0x17)
    {
        FORCE_REGISTER(u8 one, r0) = 1; /* FAKE MATCH: a fresh 1 as in the reference; cse otherwise stores block's register and the arms do not cross-jump */
        ((struct Main2MapContext *)gMainContextPointer_03006F74)->byte18 = one;
    }
    else
    {
        *(u16 *)((((*(volatile u16 *)0x0400000E >> 8) & 0x1F) << 11) + 0x06000248) =
            *(u16 *)((((*(volatile u16 *)0x0400000E >> 8) & 0x1F) << 11) + 0x0600021E);
        ((struct Main2MapContext *)gMainContextPointer_03006F74)->byte18 = 0;
    }
    switch (gUnknown_030057E0[0xC32])
    {
    case 0:
        for (index = 0; index <= 2; index++)
        {
            zero = 0;
            CpuSet((const void *)&zero, (u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000000) + 13 + ((index + 10) << 5), 0x01000005);
        }
    case 1:
        for (index = 0; index <= 2; index++)
        {
            zero = 0;
            CpuSet((const void *)&zero, (u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000000) + 8 + ((index + 4) << 5), 0x01000005);
        }
        break;
    }
    do {
    length = sub_08044D0C(gBiosLz77Stream_087889D4, (void *)0x02030000);
    } while (0);
    CpuFastSet((void *)0x02030000, (void *)(0x06000000 + (block << 14)), (length << 9) >> 11);
    source = gNativeLeStream_08785EC0;
    length2 = length + 0x06000000;
    LeDecompress(source, (void *)((block << 14) + length2));
    ((struct Main2MapContext *)gMainContextPointer_03006F74)->halfword36 = (length >> 5) - 1;
    CpuFastSet(gUnknown_087883F4, (void *)0x05000000, 0x70);
    LeDecompress(gNativeLeStream_08787144, (void *)0x06010000);
    CpuFastSet(gUnknown_080AFB20, (void *)0x05000200, 0x18);
    ((struct Main2MapContext *)gMainContextPointer_03006F74)->byte17 = gMain2SceneCursorChoices_08483774[gUnknown_030057E0[0x7FE]];
    gFrameObjects[0].flags = 0xC000;
    gFrameObjects[0].tableSelector = 2;
    gFrameObjects[0].screenY = 0x3C;
    gFrameObjects[0].palette = ((struct Main2MapContext *)gMainContextPointer_03006F74)->byte18;
    gFrameObjects[0].frameAndGroup = 0x10D;
    gFrameObjects[0].unknown1A = 0;
    gFrameObjects[1].flags = 0xC000;
    gFrameObjects[1].tableSelector = 2;
    gFrameObjects[1].screenX = gTable08483854[((struct Main2MapContext *)gMainContextPointer_03006F74)->byte17 * 2] * 8;
    gFrameObjects[1].screenY = gTable08483854[((struct Main2MapContext *)gMainContextPointer_03006F74)->byte17 * 2 + 1] * 8;
    gFrameObjects[1].palette = 2;
    gFrameObjects[1].frameAndGroup = 0x10E;
    gFrameObjects[0].screenX = gTable08483854[((struct Main2MapContext *)gMainContextPointer_03006F74)->byte17 * 2] * 8;
    gFrameObjects[0].screenY = gTable08483854[((struct Main2MapContext *)gMainContextPointer_03006F74)->byte17 * 2 + 1] * 8;
    sub_08044D0C(gBiosLz77Stream_087885B4, (void *)0x020301E0);
    gUnknown_0300137C++;
}
