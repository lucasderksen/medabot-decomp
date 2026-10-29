/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_commands.h"
#include "continued_float_progress.h"
#include "continued_graphics.h"
#include "continued_late_graphics.h"
#include "continued_numeric.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "fresh_helpers.h"
#include "gba.h"
#include "graphics.h"
#include "interrupts.h"
#include "later_graphics.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "pose_channels.h"
#include "post_dispatch.h"
#include "record_helpers.h"
#include "render_work.h"
#include "scene_view.h"
#include "scene_program_data.h"
#include "scene_setup_data.h"
#include "serial.h"
#include "sound_samples.h"
#include "sound_voice.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_work.h"

union ScriptWord { long l; s32 i; };
struct ScriptScene
{
    s32 width;              /* 000 */
    s32 height;             /* 004 */
    u8 unknown08[0x88];
    float baseX;            /* 090 */
    float baseY;            /* 094 */
    float scale98;          /* 098 */
    s32 word9C;             /* 09C */
    s32 wordA0;             /* 0A0 */
    u8 unknownA4[0x4C];
    s32 active;             /* 0F0 */
    s32 opcode;             /* 0F4 */
    s32 tableIndex;         /* 0F8 */
    s32 pc;                 /* 0FC */
    union ScriptWord savedPc[16]; /* 100 */
    long depth;             /* 140 */
    const s32 *savedScript[16];   /* 144 */
    s32 actor;              /* 184 */
    long savedActor[16];    /* 188 */
    u8 unknown1C8[0xC];
    s32 flags1D4;           /* 1D4 */
    s32 word1D8;            /* 1D8 */
    s32 word1DC;            /* 1DC */
    s32 word1E0;            /* 1E0 */
    u8 unknown1E4[0x10];
    s32 fadeMode;           /* 1F4 */
    s32 fadeStep;           /* 1F8 */
    s32 fadeTimer;          /* 1FC */
    s32 fadeDelay;          /* 200 */
    s32 fadeLimit;          /* 204 */
    u8 fadeLevel;           /* 208 */
    u16 fadeMaskA;          /* 20A */
    u16 fadeMaskB;          /* 20C */
    u8 fadeRed;             /* 20E */
    u8 fadeGreen;           /* 20F */
    u8 fadeBlue;            /* 210 */
    s32 word214;            /* 214 */
    s32 word218;            /* 218 */
    s32 word21C;            /* 21C */
    s32 word220;            /* 220 */
    s32 words224[7];        /* 224 */
};
struct ScriptTimer
{
    long active;
    long timer;
    long delay;
    long limit;
    float value;
    float step;
};
struct ScriptWave
{
    volatile long mode;
    float value;
    float step;
    float phase;
    long timer;
    long delay;
    long limit;
    float phaseStep;
    long word20;
};
struct ScriptRamp
{
    long active;
    float value;
    float step;
    long timer;
    long delay;
    long limit;
};
struct ScriptBlink
{
    long active;
    long timer;
    long delay;
    long limit;
};
struct ScriptActor
{
    long active;                         /* 000 */
    long timer;                          /* 004 */
    long delay;                          /* 008 */
    long limit;                          /* 00C */
    struct FloatProgressWork motion[3]; /* 010 */
    struct ScriptTimer timers[2];       /* 0E8 */
    struct ScriptWave waves[2];         /* 118 */
    struct ScriptRamp ramps[3];         /* 160 */
    struct ScriptRamp alpha;            /* 1A8 */
    struct ScriptBlink hide;            /* 1C0 */
    struct ScriptBlink blink;           /* 1D0 */
    long word1E0;                        /* 1E0 */
    long word1E4;                        /* 1E4 */
    long word1E8;                        /* 1E8 */
    long word1EC;                        /* 1EC */
    long word1F0;                        /* 1F0 */
    long word1F4;                        /* 1F4 */
    long word1F8;                        /* 1F8 */
    long word1FC;                        /* 1FC */
    long word200;                        /* 200 */
    long word204;                        /* 204 */
    long flag208;                        /* 208 */
    u8 unknown20C[4];
    long count;                          /* 210 */
    s32 parent;                          /* 214 */
    s32 flag218;                        /* 218 */
    long when[16];                      /* 21C */
    s32 target[16];                     /* 25C */
    const s32 *pending[16];                 /* 29C */
    u8 objects[4];                      /* 2DC */
    s16 values2E0[4];                   /* 2E0 */
    u8 bytes2E8[4];                     /* 2E8 */
    long callActive;                     /* 2EC */
    long callTimer;                      /* 2F0 */
    long callDelay;                      /* 2F4 */
    long callLimit;                      /* 2F8 */
    long callArg;                        /* 2FC */
};
struct ScriptAffine
{
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    s32 pad[2];
};
struct ScriptContinued
{
    u8 unknown000[0x7FE];
    u8 byte7FE;
    u8 unknown7FF[0x44D];
    u8 byteC4C;
    u8 unknownC4D[5];
    u16 halfC52;
    u16 halfC54;
    s8 byteC56;
    s8 byteC57;
    u8 unknownC58[0xF];
    u8 byteC67;
    u8 unknownC68[0xE];
    u8 byteC76;
    u8 unknownC77[0x43];
    u8 byteCBA;
};
struct ScriptDma { u32 source, destination, control; };
struct ScriptBlend { u8 unknown00[0x24]; float float24; u8 unknown28[4]; float float2C; };

#include "map_object_spawns.h"
extern struct ScriptAffine gScriptAffine[64] asm("gLaterBuffer_03006D40");
extern struct ScriptScene gScriptScene asm("gLaterBuffer_03005350");
extern struct ScriptActor *gScriptActors asm("gSetupPointer_03006D30");
extern struct ScriptContinued gScriptContinued asm("gContinuedWork_030057E0");
extern struct ScriptBlend gScriptBlend asm("gBlendSetupWork_03006F40");
extern const struct SceneSource *const *const gScriptSources[32] asm("gUnknown_083D2F30");
extern u8 gScriptFresh[] asm("gFreshWork_03006D38");
extern u8 gUnknown_0202F9A0[];
extern void sub_08049CFC_2(u32 color, u32 weight) asm("sub_08049CFC");
extern void sub_0804B1B0(void);
extern void sub_08054014(void);
extern void sub_080568F4(void);
extern void sub_080569E4(struct FloatProgressWork *work, void *setup);

u32 sub_0805424C(void);

u32 sub_0805424C(void) {

    s32 setup[16];
    s32 zero;
    s32 flags;
    s32 frame;
    s32 extra;
    s32 i;
    s32 done;
    s32 pending;
    s32 base;
    struct FloatProgressWork *progress;
    struct ScriptTimer *timer;
    struct ScriptWave *wave;
    struct ScriptRamp *ramp;
    const s32 *script;
    s32 k;
    s32 j;
    s32 found;
    s32 index;
    long m;

    gScriptScene.active = 1;
    gScriptScene.tableIndex = gScriptScene.flags1D4 & 0x3F;
    script = gUnknown_083D5F70[gScriptScene.tableIndex];
loop:
    do
    {
    switch (gScriptScene.opcode = script[gScriptScene.pc])
    {
    case 1:
        gScriptScene.pc++;
        gScriptScene.word9C = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.wordA0 = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.baseX = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.baseY = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.word214 = 0x80;
        gScriptScene.word218 = 0;
        gScriptScene.word21C = 0x400;
        gScriptScene.word220 = 0x800;
        sub_08053464();
        for (i = 0; i < 16; i++)
        {
            gScriptActors[i].ramps[0].value = 1.0f;
            gScriptActors[i].ramps[1].value = 1.0f;
            gScriptActors[i].ramps[2].value = 1.0f;
        }
        gScriptScene.depth = 0;
        break;
    case 2:
        done = 0;
        found = 0;
        pending = 0;
        for (i = 0; i < 16; i++)
        {
            if (gScriptActors[i].active != 0 && gScriptActors[i].flag218 != 0)
            {
                for (j = 0; j < 16; j++)
                {
                    if (gScriptActors[i].pending[j] != 0)
                    {
                        pending++;
                        if (gScriptActors[i].timer >= gScriptActors[i].when[j])
                        {
                            gScriptScene.actor = gScriptActors[i].target[j];
                            gScriptActors[gScriptScene.actor].motion[0].float00 = gScriptActors[i].motion[0].float00;
                            gScriptActors[gScriptScene.actor].motion[1].float00 = gScriptActors[i].motion[1].float00;
                            gScriptActors[gScriptScene.actor].motion[2].float00 = gScriptActors[i].motion[2].float00;
                            gScriptScene.savedScript[gScriptScene.depth] = script;
                            script = (const s32 *)gScriptActors[i].pending[j];
                            gScriptScene.savedPc[gScriptScene.depth].l = gScriptScene.pc;
                            gScriptScene.depth++;
                            gScriptScene.pc = 0;
                            gScriptScene.opcode = script[0];
                            gScriptActors[i].pending[j] = 0;
                            found = 1;
                        }
                        if (found)
                            break;
                    }
                    if (found)
                        break;
                }
                if (pending == 0)
                    gScriptActors[i].flag218 = pending;
            }
        }
        if (found)
            break;
        for (i = 0; i < 16; i++)
        {
            if (gScriptActors[i].active != 0)
            {
                if (gScriptActors[i].delay <= gScriptActors[i].timer)
                {
                    for (j = 0; j < 3; j++)
                    {
                        if (j == 0)
                            progress = &gScriptActors[i].motion[0];
                        else if (j == 1)
                            progress = &gScriptActors[i].motion[1];
                        else if (j == 2)
                            progress = &gScriptActors[i].motion[2];
                        sub_08056F24(progress);
                    }
                    for (j = 0; j < 2; j++)
                    {
                        if (j == 0)
                            timer = &gScriptActors[i].timers[0];
                        else if (j == 1)
                            timer = &gScriptActors[i].timers[1];
                        if (timer->active != 0)
                        {
                            if (timer->delay <= timer->timer)
                            {
                                timer->value = timer->value + timer->step;
                                timer->timer++;
                                if (timer->limit != 0xFFFF && timer->timer >= timer->limit)
                                    timer->active = 0;
                            }
                            else
                            {
                                timer->timer++;
                            }
                        }
                    }
                    for (k = 0; k < 2; k++)
                    {
                        if (k == 0)
                            wave = &gScriptActors[i].waves[0];
                        else if (k == 1)
                            wave = &gScriptActors[i].waves[1];
                        if ((m = wave->mode) != 0)
                        {
                            if (wave->delay <= wave->timer)
                            {
                                if (m == 1)
                                {
                                    wave->value = wave->value + wave->step;
                                    for (j = 0; j < 4; j++)
                                    {
                                        if (k == 0)
                                            gScriptAffine[i * 4 + j].a = wave->value;
                                        else if (k == 1)
                                            gScriptAffine[i * 4 + j].b = wave->value;
                                    }
                                }
                                else if (m == 2)
                                {
                                    wave->value = wave->step * gAffineSineTable_080AE8F4[0xFF & (s32)wave->phase];
                                    for (j = 0; j < 4; j++)
                                    {
                                        if (k == 0)
                                            gScriptAffine[i * 4 + j].a = wave->value;
                                        else if (k == 1)
                                            gScriptAffine[i * 4 + j].b = wave->value;
                                    }
                                    wave->phase = wave->phase + wave->phaseStep;
                                }
                                else if (m == 3)
                                {
                                    wave->value = wave->step * gAffineSineTable_080AE8F4[(0xFF & (s32)wave->phase) + 0x40];
                                    for (j = 0; j < 4; j++)
                                    {
                                        if (k == 0)
                                            gScriptAffine[i * 4 + j].a = wave->value;
                                        else if (k == 1)
                                            gScriptAffine[i * 4 + j].b = wave->value;
                                    }
                                    wave->phase = wave->phase + wave->phaseStep;
                                }
                                wave->timer++;
                                if (wave->limit != 0xFFFF && wave->timer >= wave->limit)
                                    wave->mode = 4;
                            }
                            else
                            {
                                wave->timer++;
                            }
                        }
                    }
                    for (j = 0; j < 3; j++)
                    {
                        if (j == 0)
                            ramp = &gScriptActors[i].ramps[0];
                        else if (j == 1)
                            ramp = &gScriptActors[i].ramps[1];
                        else if (j == 2)
                            ramp = &gScriptActors[i].ramps[2];
                        if (ramp->active != 0)
                        {
                            if (ramp->delay <= ramp->timer)
                            {
                                ramp->value = ramp->value + ramp->step;
                                ramp->timer++;
                                if (ramp->limit != 0xFFFF && ramp->timer >= ramp->limit)
                                    ramp->active = 0;
                            }
                            else
                            {
                                ramp->timer++;
                            }
                        }
                    }
                    if (gScriptActors[i].alpha.active != 0)
                    {
                        if (gScriptActors[i].alpha.delay <= gScriptActors[i].alpha.timer)
                        {
                            gScriptActors[i].alpha.value = gScriptActors[i].alpha.value + gScriptActors[i].alpha.step;
                            for (j = 0; j < 4; j++)
                                gScriptAffine[i * 4 + j].c = 0xFF & (s32)gScriptActors[i].alpha.value;
                            gScriptActors[i].alpha.timer++;
                            if (gScriptActors[i].alpha.limit != 0xFFFF && gScriptActors[i].alpha.timer >= gScriptActors[i].alpha.limit)
                                gScriptActors[i].alpha.active = 0;
                        }
                        else
                        {
                            gScriptActors[i].alpha.timer++;
                        }
                    }
                    if (gScriptActors[i].flag208 != 0)
                    {
                        for (j = 0; j < gScriptActors[i].count; j++)
                            sub_08049440(gScriptActors[i].objects[j]);
                    }
                    if (gScriptActors[i].hide.active != 0)
                    {
                        if (gScriptActors[i].hide.delay <= gScriptActors[i].hide.timer)
                        {
                            for (j = 0; j < gScriptActors[i].count; j++)
                                gFrameObjects[gScriptActors[i].objects[j]].flags |= 0x4000;
                            gScriptActors[i].hide.timer++;
                            if (gScriptActors[i].hide.limit != 0xFFFF && gScriptActors[i].hide.timer >= gScriptActors[i].hide.limit)
                            {
                                for (j = 0; j < gScriptActors[i].count; j++)
                                    sub_08048888(gScriptActors[i].objects[j]);
                                gScriptActors[i].hide.active = 0;
                                gScriptActors[i].flag208 = 0;
                            }
                        }
                        else
                        {
                            gScriptActors[i].hide.timer++;
                        }
                    }
                    if (gScriptActors[i].blink.active != 0)
                    {
                        if (gScriptActors[i].blink.delay <= gScriptActors[i].blink.timer)
                        {
                            if (!(gScriptActors[i].blink.timer & 1))
                            {
                                for (j = 0; j < gScriptActors[i].count; j++)
                                    gFrameObjects[gScriptActors[i].objects[j]].flags &= 0xBFFF;
                            }
                            else
                            {
                                for (j = 0; j < gScriptActors[i].count; j++)
                                    gFrameObjects[gScriptActors[i].objects[j]].flags |= 0x4000;
                            }
                            gScriptActors[i].blink.timer++;
                            if (gScriptActors[i].blink.limit != 0xFFFF && gScriptActors[i].blink.timer >= gScriptActors[i].blink.limit)
                                gScriptActors[i].blink.active = 0;
                        }
                        else
                        {
                            gScriptActors[i].blink.timer++;
                        }
                    }
                    if (gScriptActors[i].callActive != 0)
                    {
                        if (gScriptActors[i].callDelay <= gScriptActors[i].callTimer)
                        {
                            sub_08047BA8(gScriptActors[i].callArg);
                            gScriptActors[i].callTimer++;
                            if (gScriptActors[i].callLimit != 0xFFFF && gScriptActors[i].callTimer >= gScriptActors[i].callLimit)
                                gScriptActors[i].callActive = 0;
                        }
                        else
                        {
                            gScriptActors[i].callTimer++;
                        }
                    }
                    gScriptActors[i].timer++;
                    if (gScriptActors[i].limit != 0xFFFF && gScriptActors[i].timer >= gScriptActors[i].limit)
                        done++;
                }
                else
                {
                    gScriptActors[i].timer++;
                }
            }
        }
        sub_08054014();
        for (i = 0; i < 16; i++)
        {
            if (gScriptActors[i].active == 2)
            {
                done++;
                for (j = 0; j < gScriptActors[i].count; j++)
                    sub_08048888(gScriptActors[i].objects[j]);
            }
        }
        for (i = 0; i < 16; i++)
        {
            if (gScriptActors[i].active != 0 && (gScriptActors[i].waves[0].mode | gScriptActors[i].waves[1].mode) == 0)
            {
                for (j = 0; j < 4; j++)
                {
                    if ((((struct FrameObject *)gFrameObjects)[gScriptActors[i].objects[j]].positionZ >> 8) > gScriptScene.word9C)
                    {
                        gScriptAffine[i * 4 + j].a = 0x101 - (((struct FrameObject *)gFrameObjects)[gScriptActors[i].objects[j]].positionZ >> 8) / gScriptScene.word9C;
                        gScriptAffine[i * 4 + j].b = 0x101 - (((struct FrameObject *)gFrameObjects)[gScriptActors[i].objects[j]].positionZ >> 8) / gScriptScene.word9C;
                    }
                    else
                    {
                        gScriptAffine[i * 4 + j].a = gScriptScene.word9C / (((struct FrameObject *)gFrameObjects)[gScriptActors[i].objects[j]].positionZ >> 8) + 0xFF;
                        gScriptAffine[i * 4 + j].b = gScriptScene.word9C / (((struct FrameObject *)gFrameObjects)[gScriptActors[i].objects[j]].positionZ >> 8) + 0xFF;
                    }
                }
            }
        }
        sub_080568F4();
        if (gScriptScene.fadeMode != 0)
        {
            if (gScriptScene.fadeDelay <= gScriptScene.fadeTimer)
            {
                gScriptScene.fadeTimer++;
                switch (gScriptScene.fadeMode)
                {
                case 1:
                    if (sub_08049E08(0x7FFF) != 0)
                    {
                        gScriptScene.fadeMode = 0;
                        done++;
                    }
                    break;
                case 2:
                    if (sub_08049E08(0x7FFF) != 0)
                    {
                        gScriptScene.fadeMode = 0;
                        done++;
                    }
                    break;
                case 3:
                    sub_08049A6C();
                    sub_08049EC0((u16)(((gScriptScene.fadeBlue << 10) | (gScriptScene.fadeGreen << 5)) | gScriptScene.fadeRed),
                                 gScriptScene.fadeLevel * gScriptScene.fadeStep, gScriptScene.fadeMaskA);
                    sub_08049ED4((u16)(((gScriptScene.fadeBlue << 10) | (gScriptScene.fadeGreen << 5)) | gScriptScene.fadeRed),
                                 gScriptScene.fadeLevel * gScriptScene.fadeStep, gScriptScene.fadeMaskB);
                    if (gScriptScene.fadeLevel < 0x20 / gScriptScene.fadeStep)
                    {
                        gScriptScene.fadeLevel++;
                    }
                    else
                    {
                        gUnknownCallback_030017F0 = DummyInterruptHandler;
                        gScriptScene.fadeMode = 0;
                        done++;
                    }
                    break;
                case 4:
                {
                    s32 weight;
                    s32 red;
                    s32 green;
                    s32 blue;
                    u16 color;
                    s32 level;
                    sub_08049A6C();
                    weight = gScriptScene.fadeLevel * gScriptScene.fadeStep;
                    red = weight - 1;
                    green = red;
                    blue = red;
                    if (red < gScriptScene.fadeRed)
                        red = gScriptScene.fadeRed;
                    if (green < gScriptScene.fadeGreen)
                        green = gScriptScene.fadeGreen;
                    if (blue < gScriptScene.fadeBlue)
                        blue = gScriptScene.fadeBlue;
                    color = (blue << 10) | (green << 5) | red;
                    sub_08049EC0(color, weight, gScriptScene.fadeMaskA);
                    sub_08049ED4(color, gScriptScene.fadeStep * gScriptScene.fadeLevel, gScriptScene.fadeMaskB);
                    if (gScriptScene.fadeLevel != 0)
                    {
                        gScriptScene.fadeLevel--;
                    }
                    else
                    {
                        gUnknownCallback_030017F0 = DummyInterruptHandler;
                        gScriptScene.fadeMode = 0;
                        done++;
                    }
                    break;
                }
                }
                if (gScriptScene.fadeLimit != 0xFFFF && gScriptScene.fadeTimer >= gScriptScene.fadeLimit)
                {
                    gUnknownCallback_030017F0 = DummyInterruptHandler;
                    gScriptScene.fadeMode = 0;
                    done++;
                }
            }
            else
            {
                gScriptScene.fadeTimer++;
            }
        }
        if (done != 0 && gScriptScene.fadeMode == 0)
        {
            gScriptScene.pc++;
            gScriptScene.opcode = script[gScriptScene.pc];
        }
        break;
    case 3:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].active = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].timer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].delay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].limit = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 5:
        gScriptScene.pc++;
        gScriptScene.pc++;
        break;
    case 6:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        if (script[gScriptScene.pc++] == 0)
        {
            gScriptActors[j].motion[0].float00 = script[gScriptScene.pc];
            gScriptScene.pc++;
        }
        else
        {
            gScriptActors[j].motion[0].float00 = (float)script[gScriptScene.pc] + gScriptActors[gScriptActors[j].parent].motion[0].float00;
            gScriptScene.pc++;
        }
        break;
    }
    case 7:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        if (script[gScriptScene.pc++] == 0)
        {
            gScriptActors[j].motion[1].float00 = script[gScriptScene.pc];
            gScriptScene.pc++;
        }
        else
        {
            gScriptActors[j].motion[1].float00 = (float)script[gScriptScene.pc] + gScriptActors[gScriptActors[j].parent].motion[1].float00;
            gScriptScene.pc++;
        }
        break;
    }
    case 8:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        if (script[gScriptScene.pc++] == 0)
        {
            gScriptActors[j].motion[2].float00 = script[gScriptScene.pc];
            gScriptScene.pc++;
        }
        else
        {
            gScriptActors[j].motion[2].float00 = (float)script[gScriptScene.pc] + gScriptActors[gScriptActors[j].parent].motion[2].float00;
            gScriptScene.pc++;
        }
        break;
    }
    case 9:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].timers[0].value = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 10:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].timers[1].value = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 11:
        gScriptScene.pc++;
        gScriptScene.pc++;
        {
        s32 actor;
        actor = gScriptScene.actor;
        gScriptActors[actor].waves[0].mode = script[gScriptScene.pc];
        do {
        gScriptScene.pc++;
        gScriptActors[actor].waves[0].value = script[gScriptScene.pc];
        } while (0);
        do
        {
            gScriptScene.pc++;
        } while (0);
        if (gScriptActors[actor].waves[0].mode != 0)
        {
            for (j = 0; j < 4; j++)
                gScriptAffine[actor * 4 + j].a = gScriptActors[actor].waves[0].value;
        }
        }
        break;
    case 12:
        do {
        gScriptScene.pc++;
        } while (0);
        gScriptScene.pc++;
        {
        s32 actor;
        do {
        actor = gScriptScene.actor;
        gScriptActors[actor].waves[1].mode = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[actor].waves[1].value = script[gScriptScene.pc];
        } while (0);
        do
        {
            gScriptScene.pc++;
        } while (0);
        if (gScriptActors[actor].waves[1].mode != 0)
        {
            for (j = 0; j < 4; j++)
                gScriptAffine[actor * 4 + j].b = gScriptActors[actor].waves[1].value;
        }
        }
        break;
    case 13:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].ramps[0].value = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 14:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].ramps[1].value = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 15:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].ramps[2].value = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 16:
    case 17:
    case 18:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        if (gScriptScene.opcode == 16)
            progress = &gScriptActors[j].motion[0];
        else if (gScriptScene.opcode == 17)
            progress = &gScriptActors[j].motion[1];
        else if (gScriptScene.opcode == 18)
            progress = &gScriptActors[j].motion[2];
        sub_080497C0(&script[gScriptScene.pc], setup, 0x40);
        gScriptScene.pc += 16;
        sub_080569E4(progress, setup);
        break;
    }
    case 23:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].ramps[0].active = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].ramps[0].step = script[gScriptScene.pc] / 10.0f;
        gScriptScene.pc++;
        gScriptActors[j].ramps[0].timer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].ramps[0].delay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].ramps[0].limit = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 24:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].ramps[1].active = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].ramps[1].step = script[gScriptScene.pc] / 10.0f;
        gScriptScene.pc++;
        gScriptActors[j].ramps[1].timer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].ramps[1].delay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].ramps[1].limit = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 25:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].ramps[2].active = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].ramps[2].step = script[gScriptScene.pc] / 10.0f;
        gScriptScene.pc++;
        gScriptActors[j].ramps[2].timer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].ramps[2].delay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].ramps[2].limit = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 19:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].timers[0].active = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].timers[0].step = script[gScriptScene.pc] * 0.125f;
        gScriptScene.pc++;
        gScriptActors[j].timers[0].timer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].timers[0].delay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].timers[0].limit = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 20:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].timers[1].active = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].timers[1].step = script[gScriptScene.pc] * 0.125f;
        gScriptScene.pc++;
        gScriptActors[j].timers[1].timer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].timers[1].delay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].timers[1].limit = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 21:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].waves[0].mode = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].waves[0].step = script[gScriptScene.pc] * 0.125f;
        gScriptScene.pc++;
        gScriptActors[j].waves[0].phase = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].waves[0].phaseStep = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].waves[0].timer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].waves[0].delay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].waves[0].limit = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 22:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].waves[1].mode = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].waves[1].step = script[gScriptScene.pc] * 0.125f;
        gScriptScene.pc++;
        gScriptActors[j].waves[1].phase = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].waves[1].phaseStep = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].waves[1].timer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].waves[1].delay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].waves[1].limit = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 26:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].alpha.active = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].alpha.step = script[gScriptScene.pc] * 0.125f;
        gScriptScene.pc++;
        gScriptActors[j].alpha.timer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].alpha.delay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].alpha.limit = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 27:
    {
        const struct SceneSource *source;
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        index = script[gScriptScene.pc];
        gScriptScene.pc++;
        flags = script[gScriptScene.pc];
        gScriptScene.pc++;
        frame = script[gScriptScene.pc];
        gScriptScene.pc++;
        extra = script[gScriptScene.pc];
        gScriptScene.pc++;
        source = gScriptSources[gScriptScene.tableIndex][j];
        gScriptActors[j].count = source->count;
        if (index < source->count)
        {
            gScriptActors[j].objects[index] = j * 4 + index;
            gScriptActors[j].values2E0[index] = 0;
            gScriptActors[j].bytes2E8[index] = 0;
            LZ77UnCompVram(gUnknown_0847E76C[gScriptScene.tableIndex], (void *)0x06016C00);
            if (!(gScriptScene.flags1D4 & 0x80))
            {
                volatile struct ScriptDma *dma = (void *)0x040000D4;
                dma->source = (u32)gUnknown_0847E704[gScriptScene.tableIndex];
                dma->destination = 0x050003A0;
                dma->control = 0x84000008;
                (void)dma->control;
            }
            else
            {
                volatile struct ScriptDma *dma = (void *)0x040000D4;
                dma->source = (u32)gUnknown_0847E704[gScriptScene.tableIndex];
                dma->destination = (u32)gUnknown_0202F9A0;
                dma->control = 0x84000008;
                (void)dma->control;
            }
            sub_08048864(gScriptActors[j].objects[index], (u16)flags, (u16)frame, 13, 1);
            gFrameObjects[gScriptActors[j].objects[index]].flags |= extra;
            gFrameObjects[gScriptActors[j].objects[index]].affineIndex = j * 4 + index;
        }
        break;
    }
    case 0x86:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        index = script[gScriptScene.pc++];
        gScriptActors[j].objects[index] = script[gScriptScene.pc++];
        gScriptActors[j].values2E0[index] = script[gScriptScene.pc++];
        gScriptActors[j].bytes2E8[index] = script[gScriptScene.pc++];
        gFrameObjects[gScriptActors[j].objects[index]].flags = script[gScriptScene.pc++];
        gFrameObjects[gScriptActors[j].objects[index]].affineIndex = j * 4 + index;
        frame = script[gScriptScene.pc++];
        if (frame != 0)
            gFrameObjects[gScriptActors[j].objects[index]].frameAndGroup = frame;
        break;
    }
    case 28:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].hide.active = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].hide.timer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].hide.delay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].hide.limit = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 29:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].flag208 = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].word204 = script[gScriptScene.pc];
        gScriptScene.pc++;
        {
            s32 n;
            for (n = 0; n < 4; n++)
                sub_08049420(gScriptActors[j].objects[n], (u8)gScriptActors[j].word204);
        }
        break;
    }
    case 30:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].blink.active = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].blink.timer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].blink.delay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].blink.limit = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 31:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].word1E0 = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].word1E4 = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].word1E8 = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 32:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].word1EC = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].word1F0 = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].word1F4 = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 33:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].word1F8 = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].word1FC = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].word200 = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 34:
        do {
        gScriptScene.pc++;
        } while (0);
        gScriptScene.savedActor[gScriptScene.depth] = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.actor = gScriptScene.savedActor[gScriptScene.depth];
        gScriptScene.savedScript[gScriptScene.depth] = script;
        script = (const s32 *)script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.savedPc[gScriptScene.depth].l = gScriptScene.pc;
        gScriptScene.depth++;
        gScriptScene.pc = 0;
        break;
    case 35:
        gScriptScene.pc++;
        gScriptScene.depth--;
        gScriptScene.pc = gScriptScene.savedPc[gScriptScene.depth].l;
        script = gScriptScene.savedScript[gScriptScene.depth];
        gScriptScene.actor = gScriptScene.savedActor[gScriptScene.depth];
        break;
    case 36:
    {
        s32 mode;
        gScriptScene.pc++;
        gScriptScene.savedActor[gScriptScene.depth] = script[gScriptScene.pc];
        gScriptScene.pc++;
        j = gScriptScene.savedActor[gScriptScene.depth];
        gScriptActors[gScriptScene.actor].target[j] = j;
        mode = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[gScriptScene.actor].flag218 = 0xFF & mode;
        gScriptActors[gScriptScene.actor].when[j] = script[gScriptScene.pc++];
        gScriptActors[gScriptScene.actor].pending[j] = (const s32 *)script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].parent = gScriptScene.actor;
        if ((mode & 0xFF00) == 0x100)
        {
            s32 relative;
            s32 slot;
            relative = script[gScriptScene.pc];
            gScriptScene.pc++;
            slot = script[gScriptScene.pc];
            gScriptScene.pc++;
            if (relative == 1)
            {
                long old = gScriptActors[gScriptScene.actor].when[j];
                if (slot == 0)
                    base = gScriptActors[gScriptScene.actor].motion[2].word24;
                gScriptActors[gScriptScene.actor].when[j] = base - old;
            }
        }
        break;
    }
    case 0x80:
        gScriptScene.pc++;
        gScriptScene.fadeTimer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeDelay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeLimit = script[gScriptScene.pc];
        gScriptScene.pc++;
        sub_08049D90(0x7FFF, 0.0f, 32.0f, 8.0f);
        gScriptScene.fadeMode = 1;
        break;
    case 0x81:
        gScriptScene.pc++;
        gScriptScene.fadeTimer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeDelay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeLimit = script[gScriptScene.pc];
        gScriptScene.pc++;
        sub_08049D18(0x7FFF, 32.0f, 0.0f, 8.0f);
        gScriptScene.fadeMode = 2;
        break;
    case 0x82:
        gScriptScene.pc++;
        gScriptScene.fadeLevel = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeMaskA = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeMaskB = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeRed = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeGreen = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeBlue = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeStep = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeTimer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeDelay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeLimit = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeMode = 3;
        sub_08049D0C();
        sub_080497E0(0x40, 0x2F00, 6, 8, 8, 8, 13, 11, 0);
        break;
    case 0x83:
    {
        s32 level;
        gScriptScene.pc++;
        level = script[gScriptScene.pc];
        gScriptScene.fadeLevel = level;
        gScriptScene.pc++;
        gScriptScene.fadeMaskA = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeMaskB = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeRed = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeGreen = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeBlue = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeStep = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeTimer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeDelay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeLimit = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.fadeMode = 4;
        if ((u8)level != 0)
        {
            if ((u8)level == 16)
            {
                sub_08049CFC_2(0x7FFF, 0x20);
                gScriptBlend.float24 = 32.0f;
                gScriptBlend.float2C = 0.0f;
                sub_080497E0(0x40, 0x2F00, 5, 8, 8, 8, 14, 12, 0);
            }
            else if ((u8)level == 8)
            {
                sub_080497E0(0x40, 0x2F00, 6, 8, 8, 8, 12, 10, 0);
            }
        }
        else
        {
            sub_080497E0(0x40, 0x2F00, 4, 8, 8, 8, 16, 16, 0);
        }
        break;
    }
    case 0x84:
        gScriptScene.pc++;
        sub_080505FC();
        sub_08049714(gFrameObjects, 0x2000);
        sub_08049714(gLaterBuffer_030055A0, 0x200);
        zero = 0;
        {
            volatile struct ScriptDma *dma = (void *)0x040000D4;
            dma->source = (u32)&zero;
            dma->destination = 0x07000000;
            dma->control = 0x85000100;
            (void)dma->control;
        }
        sub_080506BC();
        if (gScriptScene.tableIndex == 0x12)
        {
            if (gScriptFresh[5] <= 8)
                gScriptScene.word1E0 = gUnknown_083D2C2B[gScriptFresh[5]];
            else
                gScriptScene.word1E0 = 0;
            gScriptScene.word1D8 = gUnknown_083D2C34[gScriptFresh[5] * 4 + 2] * 16;
            gScriptScene.word1DC = gUnknown_083D2C34[gScriptFresh[5] * 4 + 3] * 16;
            gScriptContinued.halfC52 = gScriptScene.word1D8;
            gScriptContinued.halfC54 = gScriptScene.word1DC;
            gScriptContinued.byteC56 = sub_0805273C(gScriptContinued.halfC52);
            gScriptContinued.byteC57 = sub_08052760(gScriptContinued.halfC54);
            gScriptContinued.byte7FE = gScriptScene.word1E0;
            sub_0804842C(12, 0);
        }
        else if (gScriptScene.tableIndex == 0xE)
        {
            gScriptScene.word1E0 = gUnknown_083D2C58;
            gScriptScene.word1D8 = gUnknown_083D2C59[2] * 16;
            gScriptScene.word1DC = gUnknown_083D2C59[3] * 16;
            gScriptContinued.halfC52 = gScriptScene.word1D8;
            gScriptContinued.halfC54 = gScriptScene.word1DC;
            gScriptContinued.byteC56 = sub_0805273C(gScriptContinued.halfC52);
            gScriptContinued.byteC57 = sub_08052760(gScriptContinued.halfC54);
            gScriptContinued.byte7FE = gScriptScene.word1E0;
            sub_0804842C(10, 0);
        }
        gScriptContinued.byteCBA = 1;
        sub_080480E4();
        sub_0804387C();
        sub_080528F8(gScriptContinued.byte7FE);
        sub_08052AA4();
        sub_08048888(0x2F);
        sub_08048888(0x59);
        gFrameObjects[0x2F].flags = 0;
        gFrameObjects[0x59].flags = 0;
        for (j = 0; j < 0x28; j++)
            sub_08048888((u8)j);
        break;
    case 0x85:
        gScriptScene.pc++;
        gScriptScene.word214 = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.word218 = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.word21C = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.word220 = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    case 0x87:
        gScriptScene.pc++;
        gScriptScene.words224[0] = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.words224[1] = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.words224[2] = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.words224[3] = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.words224[4] = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.words224[5] = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptScene.words224[6] = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    case 0x89:
    {
        s32 from;
        s32 to;
        gScriptScene.pc++;
        from = script[gScriptScene.pc];
        gScriptScene.pc++;
        to = script[gScriptScene.pc];
        gScriptScene.pc++;
        switch (script[gScriptScene.pc++])
        {
        case 0:
            gScriptActors[to].motion[2].float00 = gScriptActors[from].motion[2].float00;
            break;
        case 1:
            gScriptActors[to].limit = gScriptActors[from].motion[2].word24;
            break;
        case 2:
            gScriptActors[to].limit = gScriptActors[from].motion[1].word24;
            break;
        case 3:
            gScriptActors[to].limit = gScriptActors[from].motion[0].word24;
            break;
        }
        break;
    }
    case 0x8A:
    {
        gScriptScene.pc++;
        gScriptScene.pc++;
        j = gScriptScene.actor;
        gScriptActors[j].callActive = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].callTimer = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].callDelay = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].callLimit = script[gScriptScene.pc];
        gScriptScene.pc++;
        gScriptActors[j].callArg = script[gScriptScene.pc];
        gScriptScene.pc++;
        break;
    }
    case 0x88:
        gScriptScene.pc++;
        gScriptContinued.byteC4C = script[gScriptScene.pc];
        gScriptScene.pc++;
        sub_0804B1B0();
        break;
    case 0x8B:
        gScriptScene.pc++;
        sub_080517F0();
        sub_08051E38(0);
        break;
    case 0:
    case 4:
    case 0x25:
        break;
    default:
        gScriptScene.opcode = 0;
        gScriptScene.pc = 0;
        break;
    }
    } while (0);
    if (gScriptScene.opcode == 0)
        goto end;
    if (gScriptScene.opcode == 1)
        goto end;
    if (gScriptScene.opcode == 2)
        goto end;
    if (gScriptScene.opcode != 4)
        goto loop;
    {
        gScriptScene.pc = 0;
        gScriptScene.active = 0;
        if ((gScriptScene.flags1D4 & 0x3F) != 0xD && (gScriptScene.flags1D4 & 0x3F) != 0x16)
        {
            s32 n;
            sub_08049318();
            for (n = 0; n < 0x20; n++)
                sub_08049374((u8)n);
        }
        if (gScriptScene.tableIndex == 0xE || gScriptScene.tableIndex == 0x12)
        {
            gScriptContinued.byteC67 = 1;
            sub_0805196C();
            sub_080517F0();
            sub_08052B70();
            sub_08052E0C(gScriptContinued.byteC67);
            if (gScriptContinued.byteC76 != 0)
            {
                sub_08052E34(gFrameObjects[0x2F].commandDelay);
                sub_08049420(0x30, (u8)(gFrameObjects[0x30].byte2B * 4 + gFrameObjects[0x30].commandDelay));
            }
            sub_0804B1B0();
        }
        if (gScriptScene.opcode != 4)
            goto loop;
    }
end:
    return gScriptScene.opcode;
}
