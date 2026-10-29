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
#include "display_effects.h"
#include "encounter_choices.h"
#include "frame.h"
#include "frame_command_data.h"
#include "frame_objects.h"
#include "graphics.h"
#include "input.h"
#include "link_menu.h"
#include "main.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_callbacks.h"
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
struct Main2PartRecord
{
    u16 identifier;
    u8 byte2;
    u8 byte3;
    u32 value;
};
struct Main2PartTable { struct Main2PartRecord r[0x78]; };

extern u32 gPostDispatchWord_03002B70;
extern u32 gUnknown_02040004[];
extern u8 gFamilyKeyBytes49558_0300058C;
extern u8 gObjectSortBytes[] asm("gObjectSortEntries");
extern u8 gUnknown_02023001[];
extern u8 gUnknown_02023002[];
extern u8 gUnknown_02023003[];
extern u8 gUnknown_02023078;
extern void sub_0805A0CC(u32, s32, s32, s32, s32, s32);
extern void sub_0805B22C(u32);
extern void sub_0805B984(void);

void sub_08061F00(void);

void sub_08061F00(void) {

    u8 row;
    u8 index;
    u8 *sort;
    u8 *p;
    struct Main2PartContext *keyCtx;
    s8 i;
    u32 add;
    struct Main2PartContext *ctx;

    sub_08041C14(8, gFrameCounter, 4);
    sub_0805B984();
    if (8 & (u8)gRepeatedKeys)
    {
        if (((struct Main2PartContext *)gMainContextPointer_03006F74)->count20 == 0)
            goto buzzer;
        sub_08074DE0(4);
        gState0TypedWork.bytes[0x84] = 0;
        gUnknown_0300137C = 9;
        return;
    }
    if (((struct Main2PartContext *)gMainContextPointer_03006F74)->byte05 == 0)
    {
        if (gFrameCounter & 8)
        {
            if (gObjectSortBytes[((struct Main2PartContext *)gMainContextPointer_03006F74)->row1A] != 0)
                gFrameObjects[11].flags |= 0x4000;
            if (gPostDispatchWord_03002B70 >= gObjectSortBytes[0] * ((struct Main2PartTable *)0x02040000)->r[0].value
                    + gObjectSortBytes[1] * ((struct Main2PartTable *)0x02040000)->r[1].value
                    + gObjectSortBytes[2] * ((struct Main2PartTable *)0x02040000)->r[2].value
                    + gObjectSortBytes[3] * ((struct Main2PartTable *)0x02040000)->r[3].value
                    + ((struct Main2PartTable *)0x02040000)->r[((struct Main2PartContext *)gMainContextPointer_03006F74)->row1A].value
                && ((struct Main2PartTable *)0x02040000)->r[((struct Main2PartContext *)gMainContextPointer_03006F74)->row1A].byte2 + gObjectSortBytes[((struct Main2PartContext *)gMainContextPointer_03006F74)->row1A] <= 0x62)
                gFrameObjects[12].flags |= 0x4000;
        }
        else
        {
            gFrameObjects[11].flags &= 0xBFFF;
            gFrameObjects[12].flags &= 0xBFFF;
        }
    }
    else
    {
        if (gFrameCounter & 8)
        {
            index = ((struct Main2PartContext *)gMainContextPointer_03006F74)->row1A + gObjectSortBytes[0x78];
            if (gObjectSortBytes[index] != 0)
                gFrameObjects[11].flags |= 0x4000;
            if (((struct Main2PartTable *)0x02040000)->r[index].byte2 > gObjectSortBytes[index])
                gFrameObjects[12].flags |= 0x4000;
        }
        else
        {
            gFrameObjects[11].flags &= 0xBFFF;
            gFrameObjects[12].flags &= 0xBFFF;
        }
    }
    if (((struct Main2PartContext *)gMainContextPointer_03006F74)->count20 > 1)
    {
        if (0x40 & (u8)gRepeatedKeys)
        {
            if (((struct Main2PartContext *)gMainContextPointer_03006F74)->row1A == 0)
            {
                if (gUnknown_02023078 == 0)
                    goto reposition;
                gUnknown_02023078--;
                goto redraw;
            }
            ((struct Main2PartContext *)gMainContextPointer_03006F74)->row1A--;
            sub_08074DE0(2);
            goto reposition;
        }
        if (0x80 & (u8)gRepeatedKeys)
        {
            if (((struct Main2PartContext *)gMainContextPointer_03006F74)->row1A + gUnknown_02023078 >= ((struct Main2PartContext *)gMainContextPointer_03006F74)->count20 - 1)
                goto reposition;
            if (((struct Main2PartContext *)gMainContextPointer_03006F74)->row1A == 3)
            {
                gUnknown_02023078++;
            redraw:
                sub_0805B22C(1);
                sub_0805B984();
                goto refresh;
            }
            if (((struct Main2PartContext *)gMainContextPointer_03006F74)->row1A >= ((struct Main2PartContext *)gMainContextPointer_03006F74)->count20)
                goto reposition;
            ((struct Main2PartContext *)gMainContextPointer_03006F74)->row1A++;
            sub_08074DE0(2);
            goto reposition;
        }
    }
    if (0x10 & (u8)gRepeatedKeys)
    {
        keyCtx = ((struct Main2PartContext *)gMainContextPointer_03006F74);
        sort = ((u8 *)0x02023000);
        p = sort + 0x78;
        index = keyCtx->row1A + *p;
        if (keyCtx->byte05 == 0)
        {
            {
            s16 s = *p;
            u32 j1, j2, j3;
            if (gPostDispatchWord_03002B70 >= sort[s] * ((struct Main2PartTable *)0x02040000)->r[s].value
                    + sort[j1 = s + 1] * ((struct Main2PartTable *)0x02040000)->r[j1].value
                    + sort[j2 = s + 2] * ((struct Main2PartTable *)0x02040000)->r[j2].value
                    + sort[j3 = s + 3] * ((struct Main2PartTable *)0x02040000)->r[j3].value
                    + ((struct Main2PartTable *)0x02040000)->r[index].value
                && ((struct Main2PartTable *)0x02040000)->r[index].byte2 + sort[index] <= 0x62)
            {
                sort[index]++;
                goto refresh;
            }
            }
        }
        else if (((struct Main2PartTable *)0x02040000)->r[index].byte2 > ((u8 *)0x02023000)[index])
        {
            ((u8 *)0x02023000)[index]++;
            goto refresh;
        }
    }
    if (0x20 & (u8)gRepeatedKeys)
    {
        index = ((struct Main2PartContext *)gMainContextPointer_03006F74)->row1A + gObjectSortBytes[0x78];
        if (gObjectSortBytes[index] != 0)
        {
            gObjectSortBytes[index]--;
            goto refresh;
        }
    }
    if (1 & gFamilyKeyBytes49558_0300058C)
    {
        if (((struct Main2PartContext *)gMainContextPointer_03006F74)->total1C == 0)
        {
        buzzer:
            sub_08074DE0(6);
            return;
        }
        sub_08074DE0(4);
        for (i = 0; i <= 1; i++)
            gFrameObjects[i + 11].flags &= 0xBFFF;
        sub_080415E8(1, 0x16, 7);
        sub_0803FAA0(1, 0, 0);
        gUnknown_0300137C = 6;
        return;
    }
    if (!(2 & gFamilyKeyBytes49558_0300058C))
        return;
    sub_08074DE0(5);
    sub_08040D0C(0x61, 7);
    sub_08040D0C(0xD, 0x34);
    sub_08040D0C(0x45, 0x1C);
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C++;
    return;
reposition:
    gFrameObjects[8].screenY = ((struct Main2PartContext *)gMainContextPointer_03006F74)->row1A * 16 + 0x54;
    gFrameObjects[11].screenY = ((struct Main2PartContext *)gMainContextPointer_03006F74)->row1A * 16 + 0x54;
    gFrameObjects[12].screenY = ((struct Main2PartContext *)gMainContextPointer_03006F74)->row1A * 16 + 0x54;
    return;
refresh:
    sub_08074DE0(2);
    if (((struct Main2PartContext *)gMainContextPointer_03006F74)->count20 != 0)
        sub_0805A0CC(gObjectSortBytes[gObjectSortBytes[0x78]], 2, 0x1B, 10, 6, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
    if (((struct Main2PartContext *)gMainContextPointer_03006F74)->count20 > 1)
        sub_0805A0CC(((u8 *)0x02023000)[gUnknown_02023078 + 1], 2, 0x1B, 12, 6, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
    if (((struct Main2PartContext *)gMainContextPointer_03006F74)->count20 > 2)
        sub_0805A0CC(((u8 *)0x02023000)[gUnknown_02023078 + 2], 2, 0x1B, 14, 6, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
    if (((struct Main2PartContext *)gMainContextPointer_03006F74)->count20 > 3)
        sub_0805A0CC(((u8 *)0x02023000)[gUnknown_02023078 + 3], 2, 0x1B, 16, 6, (*(volatile u16 *)0x0400000A >> 8) & 0x1F);
    ((struct Main2PartContext *)gMainContextPointer_03006F74)->total1C = 0;
    for (i = 0; i <= 0x77; i++)
    {
        ctx = ((struct Main2PartContext *)gMainContextPointer_03006F74);
        if (ctx->byte05 == 0)
            add = gObjectSortBytes[i] * ((struct Main2PartTable *)0x02040000)->r[i].value;
        else
            { add = gObjectSortBytes[i] * ((struct Main2PartTable *)0x02040000)->r[i].value; add >>= 1; }
        ctx->total1C += add;
    }
    if (((struct Main2PartContext *)gMainContextPointer_03006F74)->total1C > 99999)
        ((struct Main2PartContext *)gMainContextPointer_03006F74)->total1C = 99999;
    sub_08040D0C(0x61, 7);
    sub_08041164(gDebugMenuTextBuffer, ((struct Main2PartContext *)gMainContextPointer_03006F74)->total1C);
    sub_08040DB8(gDebugMenuTextBuffer, 0x61, 0x13, 5, 7, 0xC, 2, 0);
}
