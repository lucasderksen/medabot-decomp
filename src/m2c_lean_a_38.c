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
#include "encounter_choices.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_command_data.h"
#include "frame_objects.h"
#include "gba.h"
#include "link_menu.h"
#include "main.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "serial.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct SaveHeaderView { u32 money; u8 name[0x10]; u16 half14; u16 half16; s32 time18; };
struct Main2MenuContext
{
    u8 unknown00[2];
    s16 halfword02;
    u8 unknown04[0x15];
    u8 selection;
    u8 unknown1A[0x2E];
    s8 byte48;
};

extern const u8 gUnknown_080AF960[];
extern const u8 gUnknown_0850F298[];
extern const u8 gUnknown_0878DC74[];
extern s32 sub_0807CEC8(s32, s32);
extern struct SaveHeaderView gSaveHeaderView_03002B70 asm("gPostDispatchWord_03002B70");
extern u32 sub_0807CD2C(u32, u32);
extern u32 sub_0807CDF8(u32, u32);
extern u8 gCopy6280C0202F800[];
extern u8 gCopy6280C0202F9E0[];
extern u8 gFamilyKeyBytes49558_0300058C;
extern u8 gUnknown_0202F9A0[];
extern void sub_08060BE4(u32, u32);

void sub_0805D860(void);
void sub_0805FB4C(s32 step);
void sub_080615D4(void);

void sub_0805D860(void) {

    u32 count;
    s32 i;
    u8 *bytes;

    count = 0;
    for (i = 0; i < 30; i++) {
        if (0x80 & gInventoryRecords[i].byte0)
            count++;
    }
    sub_08059F58(count, 2, 10, 4, 10, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
    count = 0;
    bytes = gObjectHalfwordBytes;
    for (i = 0; i < 0x1E0; i++) {
        if (*bytes != 0)
            count++;
        bytes += 2;
    }
    sub_08059F58(count, 3, 9, 6, 11, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
    count = sub_0807CEC8(gSaveHeaderView_03002B70.time18, 0xE10);
    sub_08059F58(sub_0807CD2C(count, 60), 2, 7, 8, 12, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
    sub_08059F58(sub_0807CDF8(count, 60), -2, 10, 8, 12, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
    sub_08059F58(gSaveHeaderView_03002B70.half16, 4, 3, 11, 13, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
    sub_08059F58(gSaveHeaderView_03002B70.half14, 0, 8, 11, 13, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
    sub_08041164(gDebugMenuTextBuffer, gSaveHeaderView_03002B70.money);
    sub_08040DB8(gDebugMenuTextBuffer, 1, 15, 9, 7, 15, 1, 0);
    sub_08040DB8(gSaveHeaderView_03002B70.name, 13, 14, 4, 10, 13, 0, 0);
    sub_080415E8(1, 0x16, 7);
    CpuFastSet(gUnknown_0878DC74, gEquipmentPaletteShadow, 0x80);
    CpuFastSet(gUnknown_0850F298, gUnknown_0202F9A0, 8);
    CpuFastSet(gMain2NameTransfer_084E43D8, gCopy6280C0202F9E0, 8);
    CpuFastSet(gUnknown_080AF960, gCopy6280C0202F800, 8);
    gDebugMenuTextBuffer[-0x1A] = 0;
    gUnknown_0300137C++;
}

void sub_0805FB4C(s32 step) {

    u16 row[32];
    u32 zero;
    u16 *dst;
    u16 *src;
    s32 k;
    u32 offset;

    if (step <= 7)
    {
        zero = 0;
        CpuFastSet(&zero, row, 0x01000010);
        CpuSet((u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000000) + (7 - step), row, (step + 1) & 0x1FFFFF);
        CpuSet((void *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x0600002C), &row[0x1D - step], (step + 1) & 0x1FFFFF);
    }
    else
    {
        step -= 8;
        CpuFastSet((void *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000000), row, 0x10);
        dst = &row[14];
        src = &row[13 - step];
        for (k = 13; k >= 0; k--)
        {
            if (k <= step)
                *dst = row[0];
            else
                *dst = *src--;
            dst--;
        }
        dst = &row[15];
        src = &row[16 + step];
        for (k = 13; k >= 0; k--)
        {
            if (k <= step)
                *dst = row[0x1D];
            else
                *dst = *src++;
            dst++;
        }
    }
    offset = 0x06000000;
    for (k = 19; k >= 0; k--)
    {
        CpuFastSet(row, (void *)((((*(volatile u16 *)0x0400000A >> 8) & 0x1F) << 11) + offset), 0x10);
        offset += 0x40;
    }
}

void sub_080615D4(void) {

    s8 i;

    for (i = 0; i <= 3; i++)
    {
        if ((gFrameCounter >> 3) & 1)
            gFrameObjects[i + 12].flags |= 0x4000;
        else if (((struct Main2MenuContext *)gMainContextPointer_03006F74)->selection == i)
            gFrameObjects[((struct Main2MenuContext *)gMainContextPointer_03006F74)->selection + 12].flags &= 0xBFFF;
    }
    if (0x40 & gFamilyKeyBytes49558_0300058C)
    {
        sub_08074DE0(2);
        ((struct Main2MenuContext *)gMainContextPointer_03006F74)->selection = 0;
        sub_08060BE4(0, gFrameCounter);
    }
    if (0x80 & gFamilyKeyBytes49558_0300058C)
    {
        sub_08074DE0(2);
        ((struct Main2MenuContext *)gMainContextPointer_03006F74)->selection = 3;
        sub_08060BE4(3, gFrameCounter);
    }
    if (0x20 & gFamilyKeyBytes49558_0300058C)
    {
        sub_08074DE0(2);
        ((struct Main2MenuContext *)gMainContextPointer_03006F74)->selection = 1;
        sub_08060BE4(1, gFrameCounter);
    }
    if (0x10 & gFamilyKeyBytes49558_0300058C)
    {
        sub_08074DE0(2);
        ((struct Main2MenuContext *)gMainContextPointer_03006F74)->selection = 2;
        sub_08060BE4(2, gFrameCounter);
    }
    if (!(7 & gFrameCounter))
        sub_08060BE4(((struct Main2MenuContext *)gMainContextPointer_03006F74)->selection, gFrameCounter);
    if (1 & gFamilyKeyBytes49558_0300058C)
    {
        sub_08074DE0(4);
        for (i = 0; i <= 3; i++)
            gFrameObjects[i + 12].flags |= 0x4000;
        if (((struct Main2MenuContext *)gMainContextPointer_03006F74)->selection == 4)
        {
        next:
            gUnknown_0300137C = 0xB;
            return;
        }
        gState0TypedWork.bytes[0x84] = 0;
        ((struct Main2MenuContext *)gMainContextPointer_03006F74)->byte48 = 0x2D;
        gUnknown_0300137C = 0xC;
        return;
    }
    if (2 & gFamilyKeyBytes49558_0300058C)
    {
        sub_08074DE0(5);
        for (i = 0; i <= 3; i++)
            gFrameObjects[i + 12].flags &= 0xBFFF;
        *(volatile u16 *)0x04000000 |= 0x200;
        gFrameObjects[8].flags |= 0x4000;
        ((struct Main2MenuContext *)gMainContextPointer_03006F74)->halfword02 = 0x10;
        goto next;
    }
}
