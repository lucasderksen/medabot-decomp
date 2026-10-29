/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_commands.h"
#include "continued_map.h"
#include "continued_map_data.h"
#include "gba.h"
#include "later_graphics.h"
#include "map_resources.h"
#include "record_helpers.h"
#include "render_work.h"
#include "sound_voice.h"
#include "state0_display.h"
#include "tile_selector_expansion.h"

struct ContinuedWork2B0 {
    u8 unknown000[0x7FE];
    u8 map;
    u8 unknown7FF;
    u16 width800;
    u16 height802;
    u16 width804;
    u16 height806;
    u8 unknown808[8];
    u8 buffer810[0x400];
    u8 unknownC10[0x38];
    u16 halfC48;
    u16 halfC4A;
};
struct Dma2B0 { const void *source; void *destination; u32 control; };

extern const u16 gUnknown_080AC74C[];
extern const u16 gUnknown_080AC7EC[];
extern const u16 gUnknown_080AC88C[];
extern const u16 gUnknown_080AC92C[];
extern const u16 gUnknown_080AC9CC[];
extern const u16 gUnknown_080ACA6C[];
extern const u8 *const gRecordByteTables_08404334[];
extern struct ContinuedWork2B0 gContinuedWork_030057E0;
extern u8 *gLaterBuffer_03006D14;
extern void *gFreshPointer_030057DC;

void sub_0804B2B0(void);

void sub_0804B2B0(void) {

    s32 i;
    volatile struct Dma2B0 *dma;

    *(volatile u16 *)0x0400000A = 0xC609;
    *(volatile u16 *)0x0400000C = 0xEA0A;
    *(volatile u16 *)0x0400000E = 0xEE0B;
    sub_080528F8(gContinuedWork_030057E0.map);
    gContinuedWork_030057E0.width800 = sub_080529AC(gContinuedWork_030057E0.map, 0);
    gContinuedWork_030057E0.height802 = sub_080529AC(gContinuedWork_030057E0.map, 1);
    gContinuedWork_030057E0.width804 = sub_080529DC(gContinuedWork_030057E0.map, 0);
    gContinuedWork_030057E0.height806 = sub_080529DC(gContinuedWork_030057E0.map, 1);
    sub_0804B298();
    sub_08049714(gContinuedWork_030057E0.buffer810, 0x400);
    sub_080497C0(gRecordByteTables_08404334[gContinuedWork_030057E0.map], gContinuedWork_030057E0.buffer810, (gContinuedWork_030057E0.height802 >> 1) * (gContinuedWork_030057E0.width800 >> 1));
    if (gContinuedMapData_083F9080[gContinuedWork_030057E0.map][0] != 0 && gContinuedMapTiles_083F8A80[gContinuedWork_030057E0.map] != 0) {
        LZ77UnCompVram(gContinuedMapTiles_083F8A80[gContinuedWork_030057E0.map], (void *)0x06009000);
        LZ77UnCompVram(gContinuedMapData_083F9080[gContinuedWork_030057E0.map][0], gLaterBuffer_03006D14);
        sub_08048CF0((u16 *)(gLaterBuffer_03006D14 + 0x10), (u16 *)0x06003000, gContinuedWork_030057E0.height806, gContinuedWork_030057E0.width804, 0x40, 0x40, 0x80);
        i = gContinuedWork_030057E0.map * 3 + 1;
        LZ77UnCompVram((*gContinuedMapData_083F9080)[i], gLaterBuffer_03006D14);
        sub_08048CF0((u16 *)(gLaterBuffer_03006D14 + 0x10), (u16 *)0x06005000, gContinuedWork_030057E0.height806, gContinuedWork_030057E0.width804, 0x40, 0x40, 0x80);
        i = gContinuedWork_030057E0.map * 3 + 2;
        LZ77UnCompVram((*gContinuedMapData_083F9080)[i], gLaterBuffer_03006D14);
        sub_08048CF0((u16 *)(gLaterBuffer_03006D14 + 0x10), (u16 *)0x06007000, gContinuedWork_030057E0.height806, gContinuedWork_030057E0.width804, 0x40, 0x40, 0x80);
        if (gContinuedMapExtra_083F8D80[gContinuedWork_030057E0.map] != 0)
            LZ77UnCompVram(gContinuedMapExtra_083F8D80[gContinuedWork_030057E0.map], gFreshPointer_030057DC);
    } else {
        sub_08049714((void *)0x06009000, 0x80);
        dma = (volatile struct Dma2B0 *)0x040000D4;
        dma->source = gUnknown_080AC74C; dma->destination = (void *)0x06009080; dma->control = 0x80000040; dma->control;
        dma->source = gUnknown_080AC7EC; dma->destination = (void *)0x06009100; dma->control = 0x80000040; dma->control;
        dma->source = gUnknown_080AC88C; dma->destination = (void *)0x06009180; dma->control = 0x80000040; dma->control;
        dma->source = gUnknown_080AC92C; dma->destination = (void *)0x06009200; dma->control = 0x80000040; dma->control;
        dma->source = gUnknown_080AC74C; dma->destination = (void *)0x06009280; dma->control = 0x80000040; dma->control;
        dma->source = gUnknown_080AC74C; dma->destination = (void *)0x06009300; dma->control = 0x80000040; dma->control;
        dma->source = gUnknown_080AC74C; dma->destination = (void *)0x06009380; dma->control = 0x80000040; dma->control;
        dma->source = gUnknown_080AC9CC; dma->destination = (void *)0x06009400; dma->control = 0x80000040; dma->control;
        dma->source = gUnknown_080ACA6C; dma->destination = (void *)0x06009480; dma->control = 0x80000040; dma->control;
        sub_08049728(gLaterBuffer_03006D14, gContinuedWork_030057E0.height802 * gContinuedWork_030057E0.width800, 8);
        sub_08048E24(gLaterBuffer_03006D14, (u16 *)0x06003000, gContinuedWork_030057E0.height802, gContinuedWork_030057E0.width800, 0x40, 0x40, gContinuedWork_030057E0.halfC4A / 8, gContinuedWork_030057E0.halfC48 / 8, 0x80);
        sub_08048E24(gLaterBuffer_03006D14, (u16 *)0x06005000, gContinuedWork_030057E0.height802, gContinuedWork_030057E0.width800, 0x40, 0x40, gContinuedWork_030057E0.halfC4A / 8, gContinuedWork_030057E0.halfC48 / 8, 0x80);
        sub_08048E24(gContinuedWork_030057E0.buffer810, (u16 *)0x06007000, gContinuedWork_030057E0.height802, gContinuedWork_030057E0.width800, 0x40, 0x40, gContinuedWork_030057E0.halfC4A / 8, gContinuedWork_030057E0.halfC48 / 8, 0x80);
    }
    sub_08052AA4();
    sub_08052C30();
}
