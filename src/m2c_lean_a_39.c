/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Main2TimerContext
{
    u8 unknown00[0x3A];
    s16 timer3A;
};

extern const s8 gUnknown_080AFAD2[];
extern const u16 gUnknown_080AFABA[];
extern s32 sub_0807CD2C(s32, s32);
extern s32 sub_0807CEC8(s32, s32);
extern u8 gFamilyKeyBytes49558_0300058C;
extern void sub_0805FB4C(s32);

void sub_0805FFF8(void);

void sub_0805FFF8(void) {

    s32 done = 0;
    u16 step;
    s32 scale;
    u16 y;

    const u16 *table;

    if (((struct Main2TimerContext *)gMainContextPointer_03006F74)->timer3A <= 7)
    {
        if (++((struct Main2TimerContext *)gMainContextPointer_03006F74)->timer3A == 4)
        {
            *(volatile u16 *)0x04000000 &= 0xFEFF;
            *(volatile u16 *)0x04000000 |= 0x200;
            sub_08074DE0(0x17);
        }
        if (((struct Main2TimerContext *)gMainContextPointer_03006F74)->timer3A <= 3)
            gFrameObjects[1].screenY--;
        else
            gFrameObjects[1].screenY++;
    }
    else
    {
        if ((u16)((struct Main2TimerContext *)gMainContextPointer_03006F74)->timer3A < 0x32)
            ((struct Main2TimerContext *)gMainContextPointer_03006F74)->timer3A++;
        step = ((struct Main2TimerContext *)gMainContextPointer_03006F74)->timer3A - 9;
        if (step == 0)
            gFrameObjects[0].flags |= 0x4000;
        if (step < 20)
        {
            scale = sub_0807CD2C(step << 6, 20);
            y = scale - 0x20;
            gFrameObjects[0].scaleX = -0x80 - scale;
            gFrameObjects[0].scaleY = -0x80 - scale;
        }
        else
        {
            step -= 20;
            if (step == 0)
            {
                gFrameObjects[0].scaleX = 0x40;
                gFrameObjects[0].scaleY = 0x40;
            }
            if (step < 13)
            {
                y = gUnknown_080AFAD2[step] + 0x20;
            }
            else
            {
                y = 0x20;
                step -= 13;
                if (step < 8)
                    sub_0805FB4C(step);
                else
                    done = 1;
            }
        }
        gFrameObjects[0].screenY = y;
    }
    if (++gFrameObjects[1].unknown1A > 0x47)
        gFrameObjects[1].unknown1A = 0;
    table = gUnknown_080AFABA;
    gFrameObjects[1].frameAndGroup = table[(u16)sub_0807CEC8(gFrameObjects[1].unknown1A, 6)];
    if ((1 & gFamilyKeyBytes49558_0300058C) && done != 0)
    {
        gFrameObjects[1].flags = 0xCA20;
        ((struct Main2TimerContext *)gMainContextPointer_03006F74)->timer3A = 0;
        gUnknown_0300137C += 2;
    }
}
