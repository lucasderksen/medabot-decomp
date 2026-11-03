#include "main.h"
#include "state0_callbacks.h"
#include "input.h"
#include "compression.h"
#include "bg_scroll.h"
#include "graphics.h"
#include "frame.h"
#include "interrupts.h"

void DispatchMainState0Substate2(void)
{
    gUnknownCallbacks_083AC454[gNestedCallbackIndex]();
}

void LoadThreeOptionGraphics(void)
{
    ClearBgScrolls();
    *(volatile u16 *)0x04000000 &= 0xF1FF;
    *(volatile u16 *)0x0400000A = 0x1805;
    *(volatile u16 *)0x0400000C = 0x1906;
    *(volatile u16 *)0x0400000E = 0x1A07;
    LeDecompress((const u8 *)0x084E4678, (void *)0x06004000);
    LoadSelectedOptionTiles();
    LoadLeTilemap(0, 0, (const u8 *)0x084F0C40, *(volatile u16 *)0x0400000A, 0);
    LoadLeTilemap(0, 0, (const u8 *)0x084F17DC, *(volatile u16 *)0x0400000C, 0);
    LoadLeTilemap(0, 0, (const u8 *)0x084F24CC, *(volatile u16 *)0x0400000E, 0);
    {
        volatile u32 *dma = (volatile u32 *)0x040000D4;
        dma[0] = 0x084F3A80;
        dma[1] = 0x0202FA00;
        dma[2] = 0x84000060;
        (void)dma[2];
    }
    CopyTilemapRect(4, 4, 5, 9, gUnknownPointers_083B4C60[72], *(volatile u16 *)0x0400000A, 0);
    *(volatile u16 *)0x04000000 |= 0x1F60;
    gUnknown_03000440[0x84] = 0;
    gNestedCallbackIndex++;
}

void FadeInThenInitThreeOptionCursor(void)
{
    ScrollBg3DecXIncY();
    if (gUnknown_03000440[0x84] <= 8)
    {
        BlendBgPaletteBanksNow(0, 32 - gUnknown_03000440[0x84] * 4, 0x1FFF);
        BlendObjPaletteBanksNow(0, 32 - gUnknown_03000440[0x84] * 4, 0xFFFF);
        gUnknown_03000440[0x84]++;
    }
    else
    {
        InitThreeOptionCursor();
        gNestedCallbackIndex++;
    }
}

void HandleThreeOptionInput(void)
{
    const u8 *pressed;
    ScrollBg3DecXIncY();
    RunFrameObjectCommands(gUnknownPointers_083B6100[0], 0);
    if (*(const u8 *)&gRepeatedKeys & KEY_UP)
    {
        if (gUnknown_03000440[0x8F] == 0)
            gUnknown_03000440[0x8F] = 2;
        else
            gUnknown_03000440[0x8F]--;
        PlaySoundEffect(2);
        LoadSelectedOptionTiles();
        gFrameObjects[0].screenX = 136 - gUnknown_03000440[0x8F] * 8;
        gFrameObjects[0].screenY = gUnknown_03000440[0x8F] * 24 + 32;
    }
    if (*(const u8 *)&gRepeatedKeys & KEY_DOWN)
    {
        if (gUnknown_03000440[0x8F] == 2)
            gUnknown_03000440[0x8F] = 0;
        else
            gUnknown_03000440[0x8F]++;
        PlaySoundEffect(2);
        LoadSelectedOptionTiles();
        gFrameObjects[0].screenX = 136 - gUnknown_03000440[0x8F] * 8;
        gFrameObjects[0].screenY = gUnknown_03000440[0x8F] * 24 + 32;
    }
    pressed = (const u8 *)&gNewKeys;
    if (*pressed & KEY_B)
    {
        PlaySoundEffect(5);
        gNestedCallbackIndex++;
    }
    if (*pressed & KEY_A)
    {
        PlaySoundEffect(4);
        InitFrameObjectCommands(gUnknownPointers_083B6100[1], 0);
        StartBlendFade(6, 63, 32);
        gUnknown_03000440[0x84] = 0;
        gNestedCallbackIndex = 8;
    }
}

void BeginThreeOptionFadeOut(void)
{
    ScrollBg3DecXIncY();
    ClearFrameObjects(0, 1);
    SnapshotPalettes();
    gUnknown_03000440[0x84] = 0;
    FadeOutMusic(8);
    gNestedCallbackIndex++;
}

void StepThreeOptionFadeOut(void)
{
    ScrollBg3DecXIncY();
    if (gUnknown_03000440[0x84] <= 8)
    {
        BlendBgPaletteBanksNow(0, gUnknown_03000440[0x84] * 4, 0x1FFF);
        BlendObjPaletteBanksNow(0, gUnknown_03000440[0x84] * 4, 0xFFFF);
        gUnknown_03000440[0x84]++;
    }
    else
        gNestedCallbackIndex++;
}

void ReturnToFourRowSelection(void)
{
    PlayMusic(6);
    gMainSubstate = 1;
    gNestedCallbackIndex = 16;
}

void WaitThreeOptionBlendFade(void)
{
    ScrollBg3DecXIncY();
    RunFrameObjectCommands(gUnknownPointers_083B6100[1], 0);
    if (StepBlendFade())
        gNestedCallbackIndex++;
}

void sub_080036F4(void)
{
    volatile u32 *dma = (volatile u32 *)0x040000D4;
    dma[0] = 0x06002800;
    dma[1] = 0x02020800;
    dma[2] = 0x84000200;
    (void)dma[2];
    switch (gUnknown_03000440[0x8F])
    {
    case 0:
        FillBytes(gUnknown_03000440 + 0x50, 20, 0);
        gMainSubstate = 3;
        gNestedCallbackIndex = 0;
        break;
    case 1:
        FillBytes(gUnknown_03000440 + 0x3C, 20, 0);
        gMainSubstate = 4;
        gNestedCallbackIndex = 0;
        break;
    default:
        FillBytes(gUnknown_03000440 + 0x3C, 20, 0);
        gMainSubstate = 5;
        gNestedCallbackIndex = 0;
        break;
    }
}

void RestoreThreeOptionGraphics(void)
{
    volatile u32 *dma;
    ClearBgScrolls();
    *(volatile u16 *)0x04000000 &= 0xF0FF;
    *(volatile u16 *)0x0400000A = 0x0500;
    *(volatile u16 *)0x0400000A = 0x1805;
    *(volatile u16 *)0x0400000C = 0x1906;
    *(volatile u16 *)0x0400000E = 0x1A07;
    LeDecompress((const u8 *)0x084E4678, (void *)0x06004000);
    LoadSelectedOptionTiles();
    dma = (volatile u32 *)0x040000D4;
    dma[0] = 0x02020800;
    dma[1] = 0x06002800;
    dma[2] = 0x84000200;
    (void)dma[2];
    LoadLeTilemap(0, 0, (const u8 *)0x084F0C40, *(volatile u16 *)0x0400000A, 0);
    LoadLeTilemap(0, 0, (const u8 *)0x084F17DC, *(volatile u16 *)0x0400000C, 0);
    LoadLeTilemap(0, 0, (const u8 *)0x084F24CC, *(volatile u16 *)0x0400000E, 0);
    dma[0] = 0x084F3A80;
    dma[1] = 0x05000000;
    dma[2] = 0x84000060;
    (void)dma[2];
    CopyTilemapRect(4, 4, 5, 9, gUnknownPointers_083B4C60[72], *(volatile u16 *)0x0400000A, 0);
    *(volatile u16 *)0x04000000 |= 0x1F60;
    StartBlendFade(5, 63, 32);
    gUnknown_03000440[0x84] = 0;
    gNestedCallbackIndex++;
}

void WaitFadeThenInitThreeOptionCursor(void)
{
    ScrollBg3DecXIncY();
    if (StepBlendFade())
    {
        InitThreeOptionCursor();
        gNestedCallbackIndex++;
    }
}

void ResumeThreeOptionInput(void)
{
    ScrollBg3DecXIncY();
    gNestedCallbackIndex = 2;
}

void LoadSelectedOptionTiles(void)
{
    const u8 *source;
    switch (gUnknown_03000440[0x8F])
    {
    case 0:
        source = (const u8 *)0x084C2440;
        break;
    case 1:
        source = (const u8 *)0x084C2620;
        break;
    default:
        source = (const u8 *)0x084C27F0;
        break;
    }
    LeDecompress(source, (void *)0x06007E00);
}

void InitThreeOptionCursor(void)
{
    LeDecompress((const u8 *)0x084C8714, (void *)0x06016C00);
    {
        volatile u32 *dma = (volatile u32 *)0x040000D4;
        dma[0] = 0x084E43F8;
        dma[1] = 0x050003C0;
        dma[2] = 0x84000008;
        (void)dma[2];
    }
    gFrameObjects[0].flags = 0xC004;
    gFrameObjects[0].screenX = 136 - gUnknown_03000440[0x8F] * 8;
    gFrameObjects[0].screenY = gUnknown_03000440[0x8F] * 24 + 32;
    gFrameObjects[0].palette = 14;
    gFrameObjects[0].tableSelector = 0;
    gFrameObjects[0].priority = 255;
    InitFrameObjectCommands(gUnknownPointers_083B6100[0], 0);
}

void ScrollBg3DecXIncY(void)
{
    if (gFrameCounter & 1)
    {
        gBgScroll3.x--;
        gBgScroll3.y++;
    }
}
