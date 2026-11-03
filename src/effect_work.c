#include "effect_work.h"
#include "display_helpers.h"
#include "display_effects.h"
#include "graphics.h"
#include "compression.h"
#include "input.h"
#include "text_glyphs.h"

/* Character bytes are unchecked in the reference, including empty inserts.
 * Form mapped ROM addresses before glyph offsets can leave a stored bank. */
extern void PlaySoundEffect(u32);

extern u8 gUnknown_03000440[];
extern const void *const gUnknownPointers_083B4C60[];

struct EffectWork
{
    u8 first;
    u8 second;
    u8 mode;
    u8 unknown03;
    u8 state;
    u8 unknown05[3];
    const u8 *script;
    u16 position;
    u8 frame;
    u8 mapBank;
    u8 graphicsBank;
    u8 graphicsFrame;
    u8 graphicsActive;
    u8 wait;
    u8 x;
    u8 remaining;
    u8 bits;
    u8 line;
    u8 inWord;
    u8 wrap;
    u8 delay;
    u8 substate;
    u8 blend;
    u8 unknown1D[3];
    const u8 *secondary;
    u8 secondaryPosition;
    u8 unknown25;
    u8 transition;
    u8 font;
};

#define WORK ((struct EffectWork *)gUnknown_03000440)

/* Read-only access view for the explicit position/delay rereads in the ROM.
 * These access qualifiers reproduce observed loads; original field types
 * and any concurrency rationale have not been established. */
struct EffectDelayWork
{
    u8 unknown00[8];
    const u8 *script;
    volatile u16 position;
    u8 unknown0E[12];
    volatile u8 delay;
};
#define DELAY_WORK ((const struct EffectDelayWork *)gUnknown_03000440)

void RestartDialogueText(void)
{
    struct EffectWork *work = WORK;
    work->state = 4;
    work->position = 0;
    work->x = 0;
    work->remaining = 0;
    work->bits = 0;
    work->line = 0;
    work->inWord = 0;
    work->wrap = 0;
    work->delay = 0;
    work->substate = 0;
    work->secondaryPosition = 0;
    work->unknown25 = 0;
    work->font = 0;
}

u32 RunDialogue(const void *script)
{
    struct EffectWork *work = WORK;
    work->script = script;
    gUnknownCallbacks_083B291C[work->state]();
    if (work->state > 7)
        return 1;
    return 0;
}

void BeginDialogueFadeToColor(void)
{
    struct EffectWork *work = WORK;
    if (work->first == 0)
    {
        SnapshotPalettes();
        work->blend = 0;
        work->state++;
    }
    else
        work->state = 2;
}

void StepDialogueFadeToColor(void)
{
    u32 color = 0x1B2;
    struct EffectWork *work = WORK;
    BlendBgPaletteBanksNow(color, work->blend * 2, 0x1FFF);
    BlendObjPaletteBanksNow(color, work->blend * 2, 0x3FFF);
    if (work->blend > 8)
        work->state++;
    else
        work->blend++;
}

void BeginDialogueBoxOpen(void)
{
    struct EffectWork *work = WORK;
    if (work->mode == 1)
        work->state = 4;
    else
    {
        work->state++;
        work->transition = 0;
        *(volatile u16 *)0x04000000 |= 0x100;
        {
            volatile u16 *control = (void *)0x04000008;
            *control = (u16)0x500;
        }
    }
}

void AdvanceDialoguePosition(void)
{
    WORK->position++;
}

void StepDialogueBoxOpen(void)
{
    switch (WORK->transition)
    {
    case 0:
        LeDecompress((const u8 *)0x084870CC, (void *)0x06000020);
        LoadLeTilemap(0, 13, (const u8 *)0x0848809C, *(volatile u16 *)0x04000008, 1);
        WORK->transition++;
        break;
    case 1:
        LeDecompress((const u8 *)0x08486FC0, (void *)0x06000020);
        LoadLeTilemap(0, 13, (const u8 *)0x08488044, *(volatile u16 *)0x04000008, 1);
        WORK->transition++;
        break;
    case 2:
        LeDecompress((const u8 *)0x08486E6C, (void *)0x06000020);
        LoadLeTilemap(0, 13, (const u8 *)0x08487FDC, *(volatile u16 *)0x04000008, 1);
        WORK->transition++;
        break;
    default:
        WORK->state++;
        break;
    }
}

void BeginDialogueText(void)
{
    u32 i = 0;
    u32 destination = 0x06000280;
    for (; i < 52; i++)
    {
        CpuFastSet((const void *)0x084BFC64, (void *)destination, 16);
        destination += 64;
    }
    CopyTilemapRect(26, 4, 2, 14, gUnknownPointers_083B4C60[18], *(volatile u16 *)0x04000008, 0);
    WORK->state++;
    RunDialogueCommands();
}

void StepDialogueBoxClose(void)
{
    switch (WORK->transition)
    {
    case 3:
        LeDecompress((const u8 *)0x08486FC0, (void *)0x06000020);
        LoadLeTilemap(0, 13, (const u8 *)0x08488044, *(volatile u16 *)0x04000008, 1);
        WORK->transition--;
        break;
    case 2:
        LeDecompress((const u8 *)0x084870CC, (void *)0x06000020);
        LoadLeTilemap(0, 13, (const u8 *)0x0848809C, *(volatile u16 *)0x04000008, 1);
        WORK->transition--;
        break;
    case 1:
        FillTilemapRect(30, 6, 0, 13, *(volatile u16 *)0x04000008, 0);
        WORK->transition--;
        break;
    default:
        WORK->substate++;
        break;
    }
}

void DispatchDialogueEndMode(void)
{
    const IntrFunc *table = gUnknownCallbacks_083B2940;
    struct EffectWork *work = WORK;
    table[work->script[work->position + 1]]();
}

void BreakDialogueLine(void)
{
    if (WORK->x & 7)
    {
        u8 tile = (WORK->x + 8) / 8 - 1;
        CpuSet((const void *)0x02020000,
               (u8 *)0x06000280 + tile * 64 + WORK->line * 13 * 128, 32);
    }
    WORK->x = 0;
    WORK->bits = 0;
    WORK->inWord = 0;
    WORK->wrap = 0;
    if (WORK->line == 1)
        WORK->wrap = 2;
    else
        WORK->line = 1;
}

void DrawDialogueGlyph(void)
{
    u8 width;
    u8 oldBits;
    u8 character;
    u8 i;
    if (WORK->inWord == 0)
    {
        u8 done;
        width = 0;
        oldBits = 0;
        done = 0;
        while (done == 0)
        {
            character = WORK->script[WORK->position + oldBits++];
            if (WORK->font)
                width += gGlyphMetrics_083B5008[character * 2];
            else
                width += gGlyphMetrics_083B4E08[character * 2];
            character = WORK->script[WORK->position + oldBits];
            if (character > 0xF7)
                break;
            if (character == 0)
            {
                done = 1;
                if (WORK->font)
                    width += gGlyphMetrics_083B5008[0];
                else
                    width += gGlyphMetrics_083B4E08[0];
            }
        }
        WORK->remaining = width;
        if (WORK->x + width > 208)
            WORK->wrap = 1;
        else
            WORK->inWord = 1;
    }
    if (WORK->wrap == 0)
    {
        character = WORK->script[WORK->position];
        if (WORK->font)
            width = gGlyphMetrics_083B5008[character * 2];
        else
            width = gGlyphMetrics_083B4E08[character * 2];
        WORK->x += width;
        WORK->remaining -= width;
        if (WORK->bits == 0)
        {
            if (WORK->font)
            {
                WORK->bits = gGlyphMetrics_083B5008[character * 2];
                CpuSet((const void *)((u32)gGlyphs_084C59A4 + (u32)character * 64), (void *)0x02020000, 32);
            }
            else
            {
                WORK->bits = gGlyphMetrics_083B4E08[character * 2];
                CpuSet((const void *)((u32)gGlyphs_084BFC64 + (u32)character * 64), (void *)0x02020000, 32);
            }
        }
        else
        {
            oldBits = WORK->bits;
            if (WORK->font)
                CpuSet((const void *)((u32)gGlyphs_084C59A4 + (u32)character * 64), (void *)0x02020040, 32);
            else
                CpuSet((const void *)((u32)gGlyphs_084BFC64 + (u32)character * 64), (void *)0x02020040, 32);
            for (i = 0; i < 16; i++)
                ((u32 *)0x02020000)[i] |= ((u32 *)0x02020040)[i] << (oldBits * 4);
            WORK->bits += width;
        }
        if (WORK->bits > 7)
        {
            u8 tile = WORK->x / 8 - 1;
            CpuSet((const void *)0x02020000,
                   (u8 *)0x06000280 + tile * 64 + WORK->line * 13 * 128, 32);
            WORK->wait = 1;
            if (WORK->bits == 8)
                WORK->bits = 0;
            else
            {
                WORK->bits -= 8;
                oldBits = 8 - oldBits;
                if (WORK->font)
                    CpuSet(gGlyphs_084C59A4, (void *)0x02020000, 32);
                else
                    CpuSet(gGlyphs_084BFC64, (void *)0x02020000, 32);
                for (i = 0; i < 16; i++)
                    ((u32 *)0x02020000)[i] |= ((u32 *)0x02020040)[i] >> (oldBits * 4);
            }
        }
        if (WORK->remaining == 0)
            WORK->inWord = 0;
        WORK->position++;
    }
}

void SetDialoguePortrait(void)
{
    u32 x;
    if (WORK->x & 7)
    {
        u8 tile = (WORK->x + 8) / 8 - 1;
        CpuFastSet((const void *)0x02020000,
                   (u8 *)0x06000280 + tile * 64 + WORK->line * 13 * 128, 16);
    }
    WORK->x = 0;
    if (WORK->second == 2)
        WORK->position += 4;
    else
    {
        u8 mapBank = WORK->script[WORK->position + 1];
        u8 bank = sub_08044B34(WORK->script[WORK->position + 2]);
        u8 frame = WORK->script[WORK->position + 3];
        if (WORK->graphicsActive == 1)
        {
            x = WORK->mapBank == 0 ? 19 : 3;
            if (WORK->mapBank == mapBank && WORK->graphicsBank == bank)
            {
                if (bank == 0xFF)
                    FillTilemapRect(8, 8, x, 5, *(volatile u16 *)0x04000008, 0);
                else
                    DrawPortrait(bank, frame, x, 5, mapBank);
                WORK->mapBank = mapBank;
                WORK->graphicsBank = bank;
                WORK->graphicsFrame = frame;
                WORK->position += 4;
            }
            else
            {
                if (WORK->second == 0)
                {
                    if ((u8)StepPortraitAnimation(WORK->graphicsBank, WORK->graphicsFrame, x, 5, WORK->mapBank, 1) == 1)
                    {
                        WORK->frame = 0;
                        WORK->graphicsActive = 0;
                    }
                }
                else
                {
                    FillTilemapRect(8, 8, x, 5, *(volatile u16 *)0x04000008, 0);
                    WORK->frame = 0;
                    WORK->graphicsActive = 0;
                }
            }
        }
        else
        {
            x = mapBank == 0 ? 19 : 3;
            if (bank != 0xFF)
            {
                if (WORK->second == 0)
                {
                    if ((u8)StepPortraitAnimation(bank, frame, x, 5, mapBank, 0) == 1)
                {
                    WORK->frame = 0;
                    WORK->graphicsActive = 1;
                    WORK->mapBank = mapBank;
                    WORK->graphicsBank = bank;
                    WORK->graphicsFrame = frame;
                    WORK->position += 4;
                }
                }
                else
                {
                    DrawPortrait(bank, frame, x, 5, mapBank);
                    WORK->graphicsActive = 1;
                    WORK->mapBank = mapBank;
                    WORK->graphicsBank = bank;
                    WORK->graphicsFrame = frame;
                    WORK->position += 4;
                }
            }
            else
            {
                WORK->mapBank = mapBank;
                WORK->graphicsBank = bank;
                WORK->graphicsFrame = frame;
                WORK->position += 4;
            }
        }
    }
}

void WaitDialogueDelaySkippable(void)
{
    if (WORK->delay == 0)
    {
        if (WORK->x & 7)
        {
            u8 tile = (WORK->x + 8) / 8 - 1;
            CpuFastSet((const void *)0x02020000,
                       (u8 *)0x06000280 + tile * 64 + WORK->line * 13 * 128, 16);
        }
        {
            u16 position = WORK->position;
            WORK->delay = WORK->script[DELAY_WORK->position + 1];
            if (DELAY_WORK->delay == 0xFF)
                WORK->position = position + 2;
        }
    }
    else
    {
        if (WORK->delay == 0xFF)
            WORK->position += 2;
        else
        {
            WORK->delay--;
            if (WORK->delay == 0)
                WORK->position += 2;
            else if (gUnknown_03000440[0x89] == 0 && (*(u8 *)&gRepeatedKeys & 3))
            {
                WORK->delay = 0;
                WORK->position += 2;
            }
        }
    }
}

void RunDialogueCommands(void)
{
    WORK->wait = 0;
    do
    {
        switch (WORK->script[WORK->position])
        {
        case 0xF9:
            if (WORK->wrap == 1)
            {
                WORK->wait = 0;
                BreakDialogueLine();
            }
            else if (WORK->wrap == 2)
            {
                WORK->wait = 1;
                WaitDialoguePageInput();
            }
            else
            {
                WORK->wait = 0;
                DrawDialogueReplacementGlyph();
                if (WORK->delay == 0xFF)
                    WORK->wait = 0;
            }
            break;
        case 0xFA:
            WaitDialogueDelaySkippable();
            if (WORK->delay == 0xFF)
                WORK->wait = 0;
            else
                WORK->wait = 1;
            break;
        case 0xF7:
            WaitDialogueDelay();
            if (WORK->delay == 0xFF)
                WORK->wait = 0;
            else
                WORK->wait = 1;
            break;
        case 0xFB:
            SetDialoguePortrait();
            WORK->wait = 1;
            break;
        case 0xFC:
            if ((u8)WaitDialoguePageInput() == 1)
                WORK->position++;
            break;
        case 0xFD:
            if (WORK->wrap == 2)
            {
                WORK->wait = 1;
                if ((u8)WaitDialoguePageInput() == 1)
                    WORK->position++;
            }
            else
            {
                WORK->wait = 0;
                BreakDialogueLine();
                if (WORK->wrap == 0)
                    WORK->position++;
            }
            break;
        case 0xFE:
            AdvanceDialoguePosition();
            break;
        case 0xF8:
            WORK->font ^= 1;
            WORK->position++;
            break;
        case 0xFF:
            EndDialogueText();
            WORK->wait = 1;
            break;
        default:
            if (WORK->wrap == 1)
            {
                WORK->wait = 0;
                BreakDialogueLine();
            }
            else if (WORK->wrap == 2)
            {
                WORK->wait = 1;
                WaitDialoguePageInput();
            }
            else
            {
                WORK->wait = 0;
                DrawDialogueGlyph();
                if (WORK->delay == 0xFF)
                    WORK->wait = 0;
            }
            break;
        }
    } while (WORK->wait == 0);
}

u32 WaitDialoguePageInput(void)
{
    if (WORK->x & 7)
    {
        u8 tile = (WORK->x + 8) / 8 - 1;
        CpuSet((const void *)0x02020000,
               (u8 *)0x06000280 + tile * 64 + WORK->line * 13 * 128, 32);
    }
    if ((u8)(WORK->unknown25 & 8))
        CopyTilemapRect(2, 1, 14, 18, gUnknownPointers_083B4C60[73], *(volatile u16 *)0x04000008, 0);
    else
        CopyTilemapRect(2, 1, 14, 18, gUnknownPointers_083B4C60[74], *(volatile u16 *)0x04000008, 0);
    WORK->unknown25++;
    WORK->wait = 1;
    if (*(u8 *)&gRepeatedKeys & 3)
    {
        u8 i;
        PlaySoundEffect(13);
        WORK->x = 0;
        WORK->bits = 0;
        WORK->inWord = 0;
        WORK->wrap = 0;
        WORK->line = 0;
        WORK->unknown25 = 0;
        CopyTilemapRect(2, 1, 14, 18, gUnknownPointers_083B4C60[73], *(volatile u16 *)0x04000008, 0);
        for (i = 0; i < 52; i++)
            CpuSet((const void *)0x084BFC64, (u8 *)0x06000280 + i * 64, 32);
        WORK->wait = 0;
        return 1;
    }
    return 0;
}

void RemoveDialoguePortrait(void)
{
    struct EffectWork *work = WORK;
    if (work->second != 2 && work->graphicsActive == 1)
    {
        u32 x;
        if (work->mapBank == 0)
            x = 19;
        else
            x = 3;
        if (work->second == 0)
        {
            if ((u8)StepPortraitAnimation(work->graphicsBank, work->graphicsFrame, x, 5, work->mapBank, 1) == 1)
            {
                work->frame = 0;
                work->graphicsActive = 0;
                work->substate++;
            }
        }
        else
        {
            FillTilemapRect(8, 8, x, 5, *(volatile u16 *)0x04000008, 0);
            work->frame = 0;
            work->graphicsActive = 0;
            work->substate++;
        }
    }
    else
        work->substate++;
}

void WaitDialogueDelay(void)
{
    if (WORK->delay == 0)
    {
        if (WORK->x & 7)
        {
            u8 tile = (WORK->x + 8) / 8 - 1;
            CpuFastSet((const void *)0x02020000,
                       (u8 *)0x06000280 + tile * 64 + WORK->line * 13 * 128, 16);
        }
        {
            u16 position = WORK->position;
            WORK->delay = WORK->script[DELAY_WORK->position + 1];
            if (DELAY_WORK->delay == 0xFF)
                WORK->position = position + 2;
        }
    }
    else
    {
        if (WORK->delay == 0xFF)
            WORK->position += 2;
        else
        {
            WORK->delay--;
            if (WORK->delay == 0)
                WORK->position += 2;
        }
    }
}

void EndDialogueText(void)
{
    if (WORK->x & 7)
    {
        u8 tile = (WORK->x + 8) / 8 - 1;
        CpuFastSet((const void *)0x02020000,
                   (u8 *)0x06000280 + tile * 64 + WORK->line * 13 * 128, 16);
    }
    WORK->x = 0;
    switch (WORK->script[WORK->position + 1])
    {
    case 0:
    case 2:
    case 3:
        if (*(u8 *)&gRepeatedKeys & 3)
        {
            PlaySoundEffect(13);
            WORK->state++;
        }
        break;
    case 1:
    case 4:
        WORK->state++;
        break;
    default:
        WORK->state++;
        break;
    }
}

void RunDialogueEndMode0(void)
{
    gUnknownCallbacks_083B2954[WORK->substate]();
}

void RunDialogueEndMode1(void)
{
    gUnknownCallbacks_083B296C[WORK->substate]();
}

void RunDialogueEndMode2(void)
{
    gUnknownCallbacks_083B2984[WORK->substate]();
}

void RunDialogueEndMode3(void)
{
    gUnknownCallbacks_083B2988[WORK->substate]();
}

void RunDialogueEndMode4(void)
{
    gUnknownCallbacks_083B2990[WORK->substate]();
}

void BeginDialogueBoxClose(void)
{
    struct EffectWork *work = WORK;
    if (work->mode == 1)
    {
        FillTilemapRect(30, 6, 0, 13, *(volatile u16 *)0x04000008, 0);
        work->substate += 2;
    }
    else
        work->substate++;
}

void BeginDialogueFadeFromColor(void)
{
    struct EffectWork *work = WORK;
    if (work->first == 0)
        work->substate++;
    else
        work->substate += 2;
}

void StepDialogueFadeFromColor(void)
{
    u32 color = 0x1B2;
    struct EffectWork *work = WORK;
    BlendBgPaletteBanksNow(color, work->blend * 2, 0x1FFF);
    BlendObjPaletteBanksNow(color, work->blend * 2, 0x1FFF);
    if (work->blend == 0)
        work->substate++;
    else
        work->blend--;
}

void DrawDialogueReplacementGlyph(void)
{
    u8 width;
    u8 oldBits;
    u8 character;
    u8 i;
    if (WORK->inWord == 0)
    {
        u8 done;
        width = 0;
        oldBits = 0;
        done = 0;
        WORK->secondaryPosition = 0;
        while (done == 0)
        {
            switch (WORK->script[WORK->position + 1])
            {
            case 1:
                WORK->secondary = gUnknown_03000440 + 0x9E;
                break;
            case 2:
                WORK->secondary = gUnknown_03000440 + 0xB2;
                break;
            case 3:
                WORK->secondary = gUnknown_03000440 + 0xC6;
                break;
            case 4:
                WORK->secondary = gUnknown_03000440 + 0xDA;
                break;
            case 0:
            default:
                WORK->secondary = (const u8 *)0x03002B74;
                break;
            }
            character = WORK->secondary[WORK->secondaryPosition + oldBits++];
            if (WORK->font)
                width += gGlyphMetrics_083B5008[character * 2];
            else
                width += gGlyphMetrics_083B4E08[character * 2];
            character = WORK->secondary[WORK->secondaryPosition + oldBits];
            if (character > 0xF7)
                done = 1;
        }
        WORK->remaining = width;
        if (WORK->x + width > 208)
            WORK->wrap = 1;
        else
            WORK->inWord = 1;
    }
    if (WORK->wrap == 0)
    {
        character = WORK->secondary[WORK->secondaryPosition];
        if (WORK->font)
            width = gGlyphMetrics_083B5008[character * 2];
        else
            width = gGlyphMetrics_083B4E08[character * 2];
        WORK->x += width;
        WORK->remaining -= width;
        if (WORK->bits == 0)
        {
            if (WORK->font)
                WORK->bits = gGlyphMetrics_083B5008[character * 2];
            else
                WORK->bits = gGlyphMetrics_083B4E08[character * 2];
            if (WORK->font)
                CpuSet((const void *)((u32)gGlyphs_084C59A4 + (u32)character * 64), (void *)0x02020000, 32);
            else
                CpuSet((const void *)((u32)gGlyphs_084BFC64 + (u32)character * 64), (void *)0x02020000, 32);
        }
        else
        {
            oldBits = WORK->bits;
            if (WORK->font)
                CpuSet((const void *)((u32)gGlyphs_084C59A4 + (u32)character * 64), (void *)0x02020040, 32);
            else
                CpuSet((const void *)((u32)gGlyphs_084BFC64 + (u32)character * 64), (void *)0x02020040, 32);
            for (i = 0; i < 16; i++)
                ((u32 *)0x02020000)[i] |= ((u32 *)0x02020040)[i] << (oldBits * 4);
            WORK->bits += width;
        }
        if (WORK->bits > 7)
        {
            u8 tile = WORK->x / 8 - 1;
            CpuSet((const void *)0x02020000,
                   (u8 *)0x06000280 + tile * 64 + WORK->line * 13 * 128, 32);
            WORK->wait = 1;
            if (WORK->bits == 8)
                WORK->bits = 0;
            else
            {
                WORK->bits -= 8;
                oldBits = 8 - oldBits;
                if (WORK->font)
                    CpuSet(gGlyphs_084C59A4, (void *)0x02020000, 32);
                else
                    CpuSet(gGlyphs_084BFC64, (void *)0x02020000, 32);
                for (i = 0; i < 16; i++)
                    ((u32 *)0x02020000)[i] |= ((u32 *)0x02020040)[i] >> (oldBits * 4);
            }
        }
        if (WORK->remaining == 0)
        {
            WORK->inWord = 0;
            WORK->position += 2;
        }
        WORK->secondaryPosition++;
    }
}
