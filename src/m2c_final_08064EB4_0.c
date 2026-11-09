/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "bios_lz77_streams.h"
#include "composite_graphics.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "fallback_map_assets.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "map_metadata.h"
#include "native_le_streams.h"
#include "record_helpers.h"
#include "scene_graphics_loads.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"

struct MenuContext64EB4 {
    u8 pad00[0x2E];
    u8 cursor2E;
    u8 pad2F[7];
    s16 tile36;
};

extern struct MenuContext64EB4 *gMenuContext64EB4 asm("gMainContextPointer_03006F74");
extern u32 gPostDispatchWord_03002B70;
extern u8 gScratch6030C02030000[];

void sub_08064EB4(void);

void sub_08064EB4(void) {

    u32 size;
    u8 i;

    {
        s32 v;
        *(volatile u16 *)0x0400000A = v = 0x1F05;
        *(volatile u16 *)0x0400000C = v = 0x1E06;
        *(volatile u16 *)0x0400000E = v = 0x1D07;
    }
    sub_0805BA34(gBiosLz77Stream_0879B828, *(volatile u16 *)0x0400000A);
    sub_0805BA34(gBiosLz77Stream_0879B980, *(volatile u16 *)0x0400000C);
    sub_0805BA34(gBiosLz77Stream_0879BAB0, *(volatile u16 *)0x0400000E);
    size = sub_08044D0C(gBiosLz77Stream_0879AF8C, gScratch6030C02030000);
    {
        /* FAKE MATCH: loading the destination straight into r1 keeps CSE from sharing 0x06004000 with size + 0x06004000 below; the reference loads the literal twice */
        FORCE_REGISTER(void *dest, r1) = (void *)0x06004000;
        CpuSet(gScratch6030C02030000, dest, (size << 10) >> 11);
    }
    gMenuContext64EB4->tile36 = (size >> 5) - 1;
    CpuFastSet(gUnknownBytes_084C29D8, (void *)(size + 0x06004000), 0x400);
    LeDecompress(gNativeLeStream_08785FB4, (void *)0x06010000);
    LeDecompress(gNativeLeStream_084C8034, (void *)0x06017400);
    gFrameObjects[8].flags = 0x8000;
    gFrameObjects[8].tableSelector = 2;
    gFrameObjects[8].palette = 0;
    gFrameObjects[8].frameAndGroup = 6;
    gFrameObjects[8].screenX = 0xC;
    gFrameObjects[8].screenY = gMenuContext64EB4->cursor2E * 16 + 0x1C;
    for (i = 0; i <= 1; i++) {
        gFrameObjects[i + 10].flags = 0x8000;
        gFrameObjects[i + 10].tableSelector = 2;
        gFrameObjects[i + 10].palette = 0;
        gFrameObjects[i + 10].frameAndGroup = 8;
        gFrameObjects[i + 10].screenX = 0x20;
        gFrameObjects[i + 10].screenY = i * 0x48 + 0x14;
    }
    gFrameObjects[11].flags |= 0x2000;
    gFrameObjects[7].flags = 0xC000;
    gFrameObjects[7].tableSelector = 2;
    gFrameObjects[7].palette = 0xA;
    gFrameObjects[7].frameAndGroup = 0x1A;
    gFrameObjects[7].screenX = 0x98;
    gFrameObjects[7].screenY = 0;
    sub_08041164(gDebugMenuTextBuffer, gPostDispatchWord_03002B70);
    sub_08040DB8(gDebugMenuTextBuffer, 0, 0x15, 1, 7, 0xF, 1, 0);
    gUnknown_0300137C++;
}
