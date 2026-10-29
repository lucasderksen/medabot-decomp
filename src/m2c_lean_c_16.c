/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "bios_lz77.h"
#include "composite_graphics.h"
#include "continued_float_progress.h"
#include "continued_map_data.h"
#include "continued_numeric.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "render_work.h"
#include "scene_view.h"
#include "scene_program_data.h"
#include "serial.h"
#include "sound_samples.h"
#include "sound_voice.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "state0_work.h"
#include "tile_text.h"

struct FloatProgressSetup
{
    s32 mode;
    s32 word04;
    s32 word08;
    s32 word0C;
    s32 word10;
    s32 word14;
    s32 word18;
    s32 word1C;
    s32 word20;
    s32 word24;
    s32 word28;
    s32 word2C;
    s32 word30;
    s32 word34;
    s32 word38;
};
struct ContextA0CC { u8 unknown00[0x36]; u16 tileBase; };

extern u32 sub_0807CEC8(u32 value, u32 divisor);
extern u32 sub_0807CF40(u32 value, u32 divisor);

void sub_08054014(void);
void sub_080568F4(void);
void sub_080569E4(struct FloatProgressWork *work, struct FloatProgressSetup *setup);
void sub_0805A0CC(u16 value, s8 width, u8 x, u8 y, u8 palette, u8 block);

void sub_08054014(void) {

    s32 i;
    s32 k;
    const struct SceneSource *source;

    gSceneView.width = 0xF0;
    gSceneView.height = 0xA0;
    sub_08053858(-120.5f, 120.5f, -80.5f, 80.5f);
    sub_0805390C(-120.5f, 120.5f, -80.5f, 80.5f);
    sub_08053FBC(gSceneView.doubleA4, gSceneView.doubleAC);
    for (i = 0; i < 16; i++) {
        if (((struct SceneActor *)gSetupPointer_03006D30)[i].active != 0
            && ((struct SceneActor *)gSetupPointer_03006D30)[i].word04 >= ((struct SceneActor *)gSetupPointer_03006D30)[i].word08
            && ((struct SceneActor *)gSetupPointer_03006D30)[i].word1C0 != 0
            && ((struct SceneActor *)gSetupPointer_03006D30)[i].word1C4 >= ((struct SceneActor *)gSetupPointer_03006D30)[i].word1C8) {
            source = gUnknown_083D2F30[gSceneView.tableIndex][i];
            gSceneView.word1D0 = source->count;
            {
                const s32 (*from)[4] = source->rows;
                for (k = 0; k < 4; k++) {
                    gSceneView.rows[0][k] = from[0][k];
                    gSceneView.rows[1][k] = from[1][k];
                    gSceneView.rows[2][k] = from[2][k];
                }
            }
            sub_080539C0(gSceneView.baseX + ((struct SceneActor *)gSetupPointer_03006D30)[i].floatF8,
                         gSceneView.baseY + ((struct SceneActor *)gSetupPointer_03006D30)[i].float110,
                         gSceneView.word9C, gSceneView.wordA0);
            for (k = 0; k < 4; k++) {
                gSceneView.outA[k] = gSceneView.rows[0][k] * ((struct SceneActor *)gSetupPointer_03006D30)[i].float164 + ((struct SceneActor *)gSetupPointer_03006D30)[i].float10;
                gSceneView.outB[k] = gSceneView.rows[1][k] * ((struct SceneActor *)gSetupPointer_03006D30)[i].float17C + ((struct SceneActor *)gSetupPointer_03006D30)[i].float58;
                gSceneView.outC[k] = gSceneView.rows[2][k] * ((struct SceneActor *)gSetupPointer_03006D30)[i].float194 + ((struct SceneActor *)gSetupPointer_03006D30)[i].floatA0;
            }
            gSceneView.scale98 = source->rows[0][0];
            gSceneView.word1CC = i;
            sub_080534C4(gSceneView.outA, gSceneView.outB, gSceneView.outC);
        }
    }
}

void sub_080568F4(void) {

    s32 i;
    s32 k;
    s32 z;
    struct FrameObject *obj;

    if (gSceneView.wordF0 != 0) {
        for (i = 0; i < 16; i++) {
            for (k = 0; k < 4; k++) {
                {
                    u32 root = (u32)gFrameObjects;
                    obj = (struct FrameObject *)(root + (((struct SceneActor *)gSetupPointer_03006D30)[i].objects[k] << 6));
                }
                z = obj->positionZ >> 8;
                if (z > gSceneView.word9C) {
                    obj->priority = gSceneView.word218;
                    gFrameObjects[((struct SceneActor *)gSetupPointer_03006D30)[i].objects[k]].flags &= 0xF3FF;
                    gFrameObjects[((struct SceneActor *)gSetupPointer_03006D30)[i].objects[k]].flags |= gSceneView.word220;
                } else {
                    obj->priority = gSceneView.word214 + (gSceneView.word9C - z);
                    gFrameObjects[((struct SceneActor *)gSetupPointer_03006D30)[i].objects[k]].flags &= 0xF3FF;
                    gFrameObjects[((struct SceneActor *)gSetupPointer_03006D30)[i].objects[k]].flags |= gSceneView.word21C;
                }
            }
        }
    }
}

void sub_080569E4(struct FloatProgressWork *work, struct FloatProgressSetup *setup) {

    s32 mode;

    mode = setup->mode;
    work->word0C = mode;
    work->float10 = setup->word04 / 256;
    work->float14 = setup->word08;
    work->float18 = (float)setup->word0C * (1.0f / 256.0f);
    work->float1C = setup->word10;
    work->word20 = setup->word14;
    work->word24 = setup->word18;
    work->float28 = setup->word1C;
    work->float2C = setup->word20;
    work->float30 = setup->word24;
    work->float34 = setup->word28;
    work->float38 = setup->word2C;
    work->float3C = (float)setup->word30 * (1.0f / 256.0f);
    work->float40 = (float)setup->word34 * (1.0f / 256.0f);
    work->word44 = setup->word38;
    if (mode > 1)
        work->float04 = work->float00;
    switch (work->word0C)
    {
    case 16:
    {
        float q;
        q = work->float34 / sub_08053360(sub_080533A4(work->float3C));
        work->float2C = q;
        work->word24 = (float)work->word20 + q;
        if (work->word44 == 0)
            break;
        work->float00 = work->float00 - sub_08053380(work->float3C) * sub_080533A4(work->float34);
        break;
    }
    case 17:
    {
        float t;
        work->word24 = (float)work->word20 + work->float28;
        t = work->float3C;
        work->float34 = t * work->float2C;
        if (work->word44 == 0)
            break;
        work->float00 = work->float00 - sub_08053380(t) * sub_080533A4(work->float34);
        break;
    }
    case 18:
    {
        float x, acc, q;
        s32 n;
        const s16 *table;
        work->float3C = work->float34 * (1.0f / 64.0f);
        x = work->float14;
        acc = 0.0f;
        n = 0;
        table = gAffineSineTable_080AE8F4;
        for (;;)
        {
            if (work->float3C == 0.0f)
                break;
            x = x + work->float3C;
            if (x >= 64.0f)
                x = 64.0f;
            acc = acc + work->float40 * ((float)table[(s32)(x + 192.0f) & 0xFF] + 256.0f) * (1.0f / 256.0f);
            if (sub_080533A4(acc) >= work->float34)
                break;
            n++;
        }
        work->float2C = n;
        q = work->float38 / sub_08053360(sub_080533A4(work->float40));
        work->float30 = q;
        work->word24 = (float)work->word20 + work->float2C + q;
        work->float38 = work->float38 + (work->float34 - sub_080533A4(acc));
        if (work->word44 == 0)
            break;
        work->float00 = work->float00 - sub_08053380(work->float40) * (sub_080533A4(work->float34) + sub_080533A4(work->float38));
        break;
    }
    case 19:
    {
        float a, b, x;
        const s16 *table;
        work->word24 = (float)work->word20 + (a = work->float28);
        b = work->float2C;
        work->float30 = a - b;
        work->float3C = 64.0f / sub_08053360(b);
        work->float38 = work->float40 * work->float30;
        x = work->float14;
        work->float34 = 0.0f;
        table = gAffineSineTable_080AE8F4;
        for (;;)
        {
            if (work->float3C == 0.0f)
                break;
            x = x + work->float3C;
            work->float34 = work->float34 + work->float40 * ((float)table[(s32)(x + 192.0f) & 0xFF] + 256.0f) * (1.0f / 256.0f);
            if (x >= 64.0f)
                break;
        }
        if (work->word44 == 0)
            break;
        work->float00 = work->float00 - sub_08053380(work->float40) * (sub_080533A4(work->float34) + sub_080533A4(work->float38));
        break;
    }
    case 20:
    {
        float x, acc, q;
        s32 n;
        u32 phase;
        work->float40 = 64.0f / work->float38;
        x = work->float14;
        acc = 0.0f;
        n = 0;
        for (;;)
        {
            x = x + work->float40;
            if (x >= 64.0f)
                x = 64.0f;
            phase = ((s32)x & 0xFF) + 64;
            acc = acc + work->float3C * (float)gAffineSineTable_080AE8F4[phase] * (1.0f / 256.0f);
            if (x == 64.0f)
                break;
            n++;
        }
        work->float30 = n;
        work->float34 = work->float34 + (work->float38 - sub_080533A4(acc));
        work->float38 = sub_080533A4(acc);
        q = work->float34 / sub_08053360(sub_080533A4(work->float3C));
        work->float2C = q;
        work->word24 = (float)work->word20 + q + work->float30;
        if (work->word44 == 0)
            break;
        work->float00 = work->float00 - sub_08053380(work->float3C) * (sub_080533A4(work->float34) + sub_080533A4(work->float38));
        break;
    }
    case 21:
    {
        float a, b, c, x;
        u32 phase;
        const s16 *table;
        work->word24 = (float)work->word20 + (a = work->float28);
        b = work->float30;
        c = a - b;
        work->float2C = c;
        work->float34 = work->float3C * c;
        work->float40 = 64.0f / sub_08053360(b);
        x = work->float14;
        work->float38 = 0.0f;
        table = gAffineSineTable_080AE8F4;
        do
        {
            x = x + work->float40;
            phase = ((s32)x & 0xFF) + 64;
            work->float38 = work->float38 + work->float3C * (float)table[phase] * (1.0f / 256.0f);
        } while (!(x >= 64.0f));
        if (work->word44 == 0)
            break;
        work->float00 = work->float00 - sub_08053380(work->float3C) * (sub_080533A4(work->float34) + sub_080533A4(work->float38));
        break;
    }
    case 23:
    {
        float v;
        const s16 *table;
        work->word24 = (float)work->word20 + work->float28;
        table = gAffineSineTable_080AE8F4;
        v = work->float2C;
        work->float00 = work->float04 + work->float40 * (float)table[(s32)v & 0xFF];
        work->float14 = v;
        break;
    }
    }
}

void sub_0805A0CC(u16 value, s8 width, u8 x, u8 y, u8 palette, u8 block) {

    u16 digits[5];
    u16 *dst;
    u16 tile;
    u16 original;
    s32 i;

    original = value;
    tile = ((struct ContextA0CC *)gMainContextPointer_03006F74)->tileBase + 1;
    if (width != 0)
    {
        if (width > 0)
        {
            dst = (u16 *)(block << 11) + (x + width + 0x02FFFFFF) + (y << 5);
            for (i = 0; i < width; i++)
            {
                if (i != 0 && value == 0)
                    *dst-- = palette << 12;
                else
                {
                    *dst-- = (sub_0807CF40(value, 10) + tile) | (palette << 12);
                    value = sub_0807CEC8(value, 10);
                }
            }
            value = original;
            tile += 10;
            dst = (u16 *)(block << 11) + (x + width + 0x02FFFFFF) + ((y + 1) << 5);
            for (i = 0; i < width; i++)
            {
                if (i != 0 && value == 0)
                    *dst-- = palette << 12;
                else
                {
                    *dst-- = (sub_0807CF40(value, 10) + tile) | (palette << 12);
                    value = sub_0807CEC8(value, 10);
                }
            }
        }
        else
        {
            width = -width;
            dst = (u16 *)(block << 11) + (x + width + 0x02FFFFFF) + (y << 5);
            {
                for (i = 0; i < width; i++)
                {
                    if (i != 0 && value == 0)
                        *dst-- = tile | (palette << 12);
                    else
                    {
                        *dst-- = (sub_0807CF40(value, 10) + tile) | (palette << 12);
                        value = sub_0807CEC8(value, 10);
                    }
                }
            }
            value = original;
            tile += 10;
            dst = (u16 *)(block << 11) + (x + width + 0x02FFFFFF) + ((y + 1) << 5);
            for (i = 0; i < width; i++)
            {
                if (i != 0 && value == 0)
                    *dst-- = tile | (palette << 12);
                else
                {
                    *dst-- = (sub_0807CF40(value, 10) + tile) | (palette << 12);
                    value = sub_0807CEC8(value, 10);
                }
            }
        }
    }
    else
    {
        dst = (u16 *)(block << 11) + (x + 0x03000000) + (y << 5);
        for (i = 0; i < 5; i++)
        {
            digits[i] = sub_0807CF40(value, 10);
            if (digits[i] == 0 && i != 0)
                break;
            value = sub_0807CEC8(value, 10);
        }
        for (i--; i >= 0; i--)
            *dst++ = (digits[i] + tile) | (palette << 12);
        dst = (u16 *)(block << 11) + (x + 0x03000000) + ((y + 1) << 5);
        value = original;
        for (i = 0; i < 5; i++)
        {
            digits[i] = sub_0807CF40(value, 10);
            if (digits[i] == 0 && i != 0)
                break;
            value = sub_0807CEC8(value, 10);
        }
        for (i--; i >= 0; i--)
            *dst++ = (digits[i] + tile) | (palette << 12);
    }
}
