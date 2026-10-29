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
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "equipment_helpers.h"
#include "fallback_map_assets.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "map_metadata.h"
#include "native_le_streams.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"

struct SetupContext67D00 { u8 pad00[0x36]; u16 value36; };

extern const u32 gUnknown_084E4438[] asm("gUnknown_084E4438");
extern const u32 gUnknown_087A56EC[] asm("gScenePalette_087A56EC");
extern const u8 gBiosLz77Stream_087A58EC[];
extern const u8 gBiosLz77Stream_087A918C[];
extern const u8 gBiosLz77Stream_087A92DC[];
extern const u8 gBiosLz77Stream_087A9518[];
extern const u8 gNativeLeStream_084C3A24[];
extern const u8 gNativeLeStream_084C8034[];
extern const u8 gUnknownPalette_0850F2B8[];
extern struct SetupContext67D00 *gSetupContext67D00 asm("gMainContextPointer_03006F74");
extern u16 gCopy6280C0202F800[];
extern u16 gCopy6280C0202F820[];
extern u16 gCopy6280C0202F9E0[];
extern u16 gUnknown_0202F840[] asm("gUnknown_0202F840");
extern u16 gUnknown_0202F860[] asm("gUnknown_0202F860");
extern u8 gScratch6030C02030000[];

void sub_08067D00(void);

void sub_08067D00(void) {

    u16 palette[16] = { 0, 0x6FFF, 0x6B7A, 0x66D5, 0x622F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    u32 fill;
    u8 item;
    u32 size;
    u32 block;
    s32 i;
    u32 tile;
    u16 *cell;
    u16 bgcnt;

    item = gQuantityResult_030017EC;
    sub_08074B88(0x19);
    fill = 0;
    CpuFastSet(&fill, (void *)0x06000000, 0x01006000);
    sub_08040CD0(0, 0x80);
    sub_080415BC();
    *(volatile u16 *)0x04000000 = 0x60;
    *(volatile u16 *)0x0400000A = 0x1E05;
    *(volatile u16 *)0x0400000C = 0x3D06;
    *(volatile u16 *)0x0400000E = 0x1C07;
    sub_0805BA34(gBiosLz77Stream_087A918C, *(volatile u16 *)0x0400000A);
    sub_0805BA34(gBiosLz77Stream_087A92DC, *(volatile u16 *)0x0400000C);
    sub_0805BA34(gBiosLz77Stream_087A9518, *(volatile u16 *)0x0400000E);
    size = sub_08044D0C(gBiosLz77Stream_087A58EC, gScratch6030C02030000);
    CpuFastSet(gScratch6030C02030000, (void *)0x06004000, (size << 9) >> 11);
    size = 0x1800;
    gSetupContext67D00->value36 = 0xC4;
    CpuFastSet(gUnknownBytes_084C29D8 + (gInventoryRecords[item].byte1 << 7), (void *)(size + 0x06000000), 0x20);
    LeDecompress(gNativeLeStream_084C3A24, (void *)(size + 0x06000080));
    tile = 0x60C0;
    do {
        bgcnt = *(volatile u16 *)0x04000008;
    } while (0);
    block = ((bgcnt >> 8) & 0x1F) << 11;
    cell = (u16 *)(block + 0x06000286);
    *cell = tile;
    cell = (u16 *)(block + 0x06000288);
    *cell = tile + 1;
    cell = (u16 *)(block + 0x060002C6);
    *cell = tile + 2;
    cell = (u16 *)(block + 0x060002C8);
    *cell = tile + 3;
    CpuFastSet(gUnknown_087A56EC, gEquipmentPaletteShadow, 0x80);
    CpuFastSet(gMain2NameTransfer_084E43D8, gCopy6280C0202F9E0, 8);
    LeDecompress(gNativeLeStream_08787144, (void *)0x06010000);
    CpuFastSet(gUnknown_084E4438, gCopy6280C0202F800, 8);
    CpuFastSet(gUnknownPalette_0850F2B8 + 0x40, gCopy6280C0202F820, 8);
    CpuFastSet(gUnknownPalette_0850F2B8, gUnknown_0202F840, 8);
    CpuFastSet(palette, gUnknown_0202F860, 8);
    LeDecompress(gNativeLeStream_084C8034, (void *)0x06017400);
    for (i = 0; i <= 0xF; i++) {
        gFrameObjects[i + 1].flags = 0xCA00;
        gFrameObjects[i + 1].screenX = 0x78;
        gFrameObjects[i + 1].screenY = 0x28;
        gFrameObjects[i + 1].tableSelector = 2;
        gFrameObjects[i + 1].palette = 3;
        gFrameObjects[i + 1].frameAndGroup = 0x117;
        gFrameObjects[i + 1].scaleX = 0x40;
        gFrameObjects[i + 1].scaleY = 0x40;
        gFrameObjects[i + 1].unknown1A = (i & 3) << 4;
    }
    *(volatile u16 *)0x04000050 = 0xC40;
    *(volatile u16 *)0x04000052 = 0x1010;
    *(volatile u16 *)0x04000054 = 8;
    gUnknown_0300137C++;
}
