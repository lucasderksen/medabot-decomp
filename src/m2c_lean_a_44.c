/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_command_data.h"
#include "gba.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Main2PartContext
{
    u8 unknown00[5];
    u8 byte05;
    u8 unknown06[0x13];
    u8 selection19;
    u8 row1A;
    u8 unknown1B;
    u32 total1C;
    u8 count20;
};
struct Main2TimerContext
{
    u8 unknown00[0x3A];
    s16 timer3A;
};

extern const u8 gUnknownPalette_0850F358[];
extern const u8 gUnknown_084C7F54[];
extern const u8 gUnknown_0850F498[];
extern const u8 gUnknown_08799F20[];
extern u8 gCopy6280C0202F9C0[];
extern u8 gCopy6280C0202F9E0[];
extern u8 gObjectSortBytes[] asm("gObjectSortEntries");
extern u8 gSwap6355C0202F880[];
extern u8 gUnknown_0202F840[];
extern u8 gUnknown_0202F860[];
extern u8 gUnknown_0202F980[];
extern u8 gUnknown_0202F9A0[];
extern void sub_0805A0CC(u32, s32, s32, s32, s32, s32);
extern void sub_0805B22C(u32);

void sub_08061CE0(void);
void sub_08062C98(void);

void sub_08061CE0(void) {

    *(volatile u16 *)0x04000000 |= 0x1000;
    CpuFastSet(gUnknownPalette_0850F358, gUnknown_0202F9A0, 8);
    CpuFastSet(gUnknownWords_084E43F8, gUnknown_0202F840, 8);
    CpuFastSet(gUnknown_084C7F54, gUnknown_0202F860, 8);
    CpuFastSet(gUnknownPalette_0850F358 + 0x100, gCopy6280C0202F9C0, 8);
    CpuFastSet(gUnknownPalette_0850F358 - 0xC0, gCopy6280C0202F9E0, 8);
    CpuFastSet(gUnknownPalette_0850F358 - 0xC0, gUnknown_0202F980, 8);
    CpuFastSet(gUnknown_0850F498, gSwap6355C0202F880, 0x40);
    CpuFastSet(gUnknown_08799F20, gEquipmentPaletteShadow, 0x80);
    gState0TypedWork.bytes[0x84] = 0;
    sub_0805B22C(((struct Main2PartContext *)gMainContextPointer_03006F74)->byte05);
    if (((struct Main2PartContext *)gMainContextPointer_03006F74)->count20 != 0)
    {
        sub_0805A0CC(gObjectSortBytes[gObjectSortBytes[0x78]], 2, 0x1B, 10, 6, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
        gFrameObjects[8].flags |= 0x4000;
    }
    if (((struct Main2PartContext *)gMainContextPointer_03006F74)->count20 > 1)
        sub_0805A0CC(((u8 *)0x02023000)[((u8 *)0x02023000)[0x78] + 1], 2, 0x1B, 12, 6, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
    if (((struct Main2PartContext *)gMainContextPointer_03006F74)->count20 > 2)
        sub_0805A0CC(((u8 *)0x02023000)[((u8 *)0x02023000)[0x78] + 2], 2, 0x1B, 14, 6, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
    if (((struct Main2PartContext *)gMainContextPointer_03006F74)->count20 > 3)
        sub_0805A0CC(((u8 *)0x02023000)[((u8 *)0x02023000)[0x78] + 3], 2, 0x1B, 16, 6, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
    gUnknown_0300137C++;
}

void sub_08062C98(void) {

    s32 frame;
    s32 i;
    s32 dest;
    s32 source;
    s32 next;
    u32 base;

    switch (((struct Main2TimerContext *)gMainContextPointer_03006F74)->timer3A / 128)
    {
    case 0:
        frame = ((struct Main2TimerContext *)gMainContextPointer_03006F74)->timer3A >> 1;
        break;
    case 1:
        frame = ((struct Main2TimerContext *)gMainContextPointer_03006F74)->timer3A >> 2;
        break;
    case 2:
        frame = ((struct Main2TimerContext *)gMainContextPointer_03006F74)->timer3A >> 3;
        break;
    case 3:
        frame = ((struct Main2TimerContext *)gMainContextPointer_03006F74)->timer3A >> 4;
        break;
    default:
        frame = ((struct Main2TimerContext *)gMainContextPointer_03006F74)->timer3A >> 5;
        break;
    }
    frame &= 3;
    if (--((struct Main2TimerContext *)gMainContextPointer_03006F74)->timer3A < 0)
        ((struct Main2TimerContext *)gMainContextPointer_03006F74)->timer3A = 0x3F;
    do {
    i = 0;
    next = frame + 2;
    base = 0x0600D800;
    dest = 0x1C0;
    } while (0);
    source = frame << 9;
loop:
    CpuSet((void *)(source + base), (void *)(dest + 0x0600E804), 12);
    CpuSet((void *)((((next & 3) * 8 + i) << 6) + base), (void *)(dest + 0x0600E820), 12);
    dest += 0x40;
    source += 0x40;
    i++;
    if (i <= 7)
        goto loop;
}
