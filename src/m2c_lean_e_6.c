/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "composite_graphics.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "input.h"
#include "link_menu.h"
#include "main.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "scene_view.h"
#include "serial.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct NameEntryContext
{
    u8 unknown00[2];
    u16 timer02;
    u8 unknown04[2];
    u8 direction06;
    u8 unknown07;
    s32 offset08;
    u8 unknown0C;
    u8 column0D;
    u8 row0E;
    u8 length0F;
    u8 unknown10[0x48];
    u8 name58[16];
    u8 defaultName68[16];
};

extern const u8 gUnknown_080AF9C8[];
extern u8 gFrameByteMetrics[][2];

void sub_0805EA44(void);

void sub_0805EA44(void) {

    s32 i;
    s32 x;
    u8 zero;
    s32 blank;
    u8 (*metrics)[2];

    {
        struct FrameObject *objects = gFrameObjects;
        u16 frame = (sub_0807CEC8(gFrameCounter, 6) & 3) + 0x26;
        *(u16 *)((u32)objects + 0x106) = frame;
    }
    {
        struct NameEntryContext *context = ((struct NameEntryContext *)gMainContextPointer_03006F74);
        u8 direction;
        if (context->direction06)
        {
            if (context->timer02++ <= 7)
                context->offset08++;
            else
            {
                direction = 0;
                context->timer02 = 0;
                goto store;
            }
        }
        else
        {
            if (context->timer02++ <= 7)
                context->offset08--;
            else
            {
                context->timer02 = 0;
                direction = 1;
            store:
                context->direction06 = direction;
            }
        }
    }
    if (0x10 & (u8)gRepeatedKeys)
    {
        sub_08074DE0(2);
        {
            u8 column = ((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D;
            if (((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E == 3 ? column == 2 : column == 25)
                ((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D = 0;
            else
                ((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D = ((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D + 1;
        }
    }
    if (0x20 & (u8)gRepeatedKeys)
    {
        sub_08074DE0(2);
        if (((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D == 0)
        {
            ((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D = ((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E == 3 ? 2 : 25;
        }
        else
            ((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D--;
    }
    if (0x40 & (u8)gRepeatedKeys)
    {
        sub_08074DE0(2);
        if (((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E == 0)
        {
            ((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E = 3;
            if (((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D <= 8)
                ((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D = 0;
            else if (((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D <= 16)
                ((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D = 1;
            else
                ((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D = 2;
        }
        else
        {
            ((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E--;
            if (((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E == 2) {
                struct NameEntryContext *context = (struct NameEntryContext *)gMainContextPointer_03006F74;
                u32 base = (u32)gUnknown_080AF9C8;
                u32 offset = context->column0D;
                context->column0D = *(const u8 *)(base + offset);
            }
        }
    }
    if (0x80 & (u8)gRepeatedKeys)
    {
        sub_08074DE0(2);
        if (((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E == 3)
        {
            ((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E = 0;
            {
                struct NameEntryContext *context = (struct NameEntryContext *)gMainContextPointer_03006F74;
                u32 base = (u32)gUnknown_080AF9C8;
                u32 offset = context->column0D;
                context->column0D = *(const u8 *)(base + offset);
            }
        }
        else
        {
            ((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E++;
            if (((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E == 3)
            {
                if (((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D <= 8)
                    ((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D = 0;
                else if (((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D <= 16)
                    ((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D = 1;
                else
                    ((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D = 2;
            }
        }
    }
    if (((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E == 3)
    {
        do {
        struct NameEntryContext *context = ((struct NameEntryContext *)gMainContextPointer_03006F74);
        do {
        gFrameObjects[0].screenX = (context->column0D << 6) - (s16)(context->offset08 / 2 - 24);
        } while (0);
        gFrameObjects[0].screenY = 0x8C;
        gFrameObjects[1].screenX = (context->column0D << 6) + (s16)(context->offset08 / 2 + 0x58);
        } while (0);
        gFrameObjects[1].screenY = blank = 0x8C;
        gFrameObjects[0].frameAndGroup = 5;
        gFrameObjects[1].frameAndGroup = 5;
        gFrameObjects[0].flags &= 0xDFFF;
        gFrameObjects[1].flags |= 0x1000;
    }
    else
    {
        s32 x0;
        gFrameObjects[0].screenX = x0 = ((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D * 8 + 20;
        gFrameObjects[0].screenY = ((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E * 24 + (s16)(((struct NameEntryContext *)gMainContextPointer_03006F74)->offset08 / 2 + 0x40);
        gFrameObjects[1].screenX = x0;
        gFrameObjects[1].screenY = ((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E * 24 - (s16)(((struct NameEntryContext *)gMainContextPointer_03006F74)->offset08 / 2 - 0x50);
        do {
        gFrameObjects[0].frameAndGroup = 8;
        gFrameObjects[1].frameAndGroup = 8;
        gFrameObjects[0].flags |= 0x2000;
        gFrameObjects[1].flags &= 0xEFFF;
        } while (0);
    }
    if (8 & ((u8 *)&gNewKeys)[0])
    {
    start:
        sub_08074DE0(4);
        ((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E = 3;
        ((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D = 2;
    }
    else if (1 & ((u8 *)&gNewKeys)[1])
    {
    space:
        if (((struct NameEntryContext *)gMainContextPointer_03006F74)->length0F <= 9)
        {
            sub_08074DE0(4);
            ((struct NameEntryContext *)gMainContextPointer_03006F74)->name58[((struct NameEntryContext *)gMainContextPointer_03006F74)->length0F] = 0;
            ((struct NameEntryContext *)gMainContextPointer_03006F74)->length0F++;
            if (((struct NameEntryContext *)gMainContextPointer_03006F74)->length0F == 10)
            {
                gFrameObjects[4].flags &= 0xBFFF;
                sub_08040D0C(5, 10);
                sub_08040DB8(((struct NameEntryContext *)gMainContextPointer_03006F74)->name58, 5, 5, 3, 10, 13, 1, 0);
                goto start;
            }
            goto redraw;
        }
        sub_08074DE0(6);
        goto redraw;
    }
    else if (1 & ((u8 *)&gNewKeys)[0])
    {
        if (((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E == 3)
        {
            switch (((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D)
            {
            case 0:
                goto space;
            case 1:
                goto erase;
            case 2:
            {
                gFrameObjects[4].flags &= 0xBFFF;
                blank = 1;
                for (i = 0; i < sizeof(((struct NameEntryContext *)gMainContextPointer_03006F74)->name58); i++)
                {
                    if (((struct NameEntryContext *)gMainContextPointer_03006F74)->name58[i] == 0xFE)
                        break;
                    if (((struct NameEntryContext *)gMainContextPointer_03006F74)->name58[i] != 0)
                    {
                        blank = 0;
                        break;
                    }
                }
                if (blank)
                    CpuSet(((struct NameEntryContext *)gMainContextPointer_03006F74)->defaultName68, ((struct NameEntryContext *)gMainContextPointer_03006F74)->name58, 8);
                sub_08040D0C(5, 10);
                sub_08040DB8(((struct NameEntryContext *)gMainContextPointer_03006F74)->name58, 5, 5, 3, 10, 13, 1, 0);
                sub_08074DE0(7);
                gUnknown_0300137C++;
                return;
            }
            }
        }
        if (((struct NameEntryContext *)gMainContextPointer_03006F74)->length0F <= 9)
        {
            sub_08074DE0(4);
            ((struct NameEntryContext *)gMainContextPointer_03006F74)->name58[((struct NameEntryContext *)gMainContextPointer_03006F74)->length0F] = ((struct NameEntryContext *)gMainContextPointer_03006F74)->row0E * 26 + ((struct NameEntryContext *)gMainContextPointer_03006F74)->column0D + 1;
            ((struct NameEntryContext *)gMainContextPointer_03006F74)->length0F++;
            if (((struct NameEntryContext *)gMainContextPointer_03006F74)->length0F == 10)
            {
                gFrameObjects[4].flags &= 0xBFFF;
                sub_08040D0C(5, 10);
                sub_08040DB8(((struct NameEntryContext *)gMainContextPointer_03006F74)->name58, 5, 5, 3, 10, 13, 1, 0);
                goto start;
            }
            goto redraw;
        }
        sub_08074DE0(6);
    redraw:
        sub_08040D0C(5, 10);
        sub_08040DB8(((struct NameEntryContext *)gMainContextPointer_03006F74)->name58, 5, 5, 3, 10, 13, 1, 0);
    }
    else if (gNewKeys & 0x202)
    {
    erase:
        sub_08074DE0(5);
        if (((struct NameEntryContext *)gMainContextPointer_03006F74)->length0F != 0)
        {
            ((struct NameEntryContext *)gMainContextPointer_03006F74)->length0F--;
            ((struct NameEntryContext *)gMainContextPointer_03006F74)->name58[((struct NameEntryContext *)gMainContextPointer_03006F74)->length0F] = 0xFE;
        }
        else
        {
            ((struct NameEntryContext *)gMainContextPointer_03006F74)->length0F = 0;
            ((struct NameEntryContext *)gMainContextPointer_03006F74)->name58[((struct NameEntryContext *)gMainContextPointer_03006F74)->length0F] = 0xFE;
        }
        sub_08040D0C(5, 10);
        sub_08040DB8(((struct NameEntryContext *)gMainContextPointer_03006F74)->name58, 5, 5, 3, 10, 13, 1, 0);
        gFrameObjects[4].flags |= 0x4000;
    }
    else
        return;
    gFrameObjects[4].screenX = sub_0805E300(((struct NameEntryContext *)gMainContextPointer_03006F74)->name58) + 40;
    gFrameObjects[4].screenY = 27;
    x = gFrameObjects[4].screenX + 2;
    i = ((struct NameEntryContext *)gMainContextPointer_03006F74)->length0F;
    if (i <= 9)
    {
        do {
        zero = 0;
        metrics = gFrameByteMetrics;
        } while (0);
        do
        {
            gFrameObjects[i + 5].flags = 0xC000;
            gFrameObjects[i + 5].tableSelector = zero;
            gFrameObjects[i + 5].palette = 13;
            gFrameObjects[i + 5].frameAndGroup = 0x42;
            {
                s16 sx = x;
                gFrameObjects[i + 5].screenX = sx;
            }
            gFrameObjects[i + 5].screenY = 28;
            gFrameObjects[i + 5].priority = 0xFF;
            x += metrics[0x43][0];
            i++;
        } while (i <= 9);
    }
}
