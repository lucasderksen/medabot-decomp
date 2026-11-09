#include "state0_part_markers.h"
#include "state0_next_helpers.h"


#include "state0_callbacks.h"
#include "state0_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "main.h"
#include "display_helpers.h"
#include "effect_work.h"
#include "object_helpers.h"
#include "graphics.h"
#include "compression.h"
#include "render_work.h"
#include "tile_text.h"

extern const MainCallback gState0NextCallbacks_083ACCD4[];
extern const void *const gState0NextText_083B4C60[];
extern const void *const gState0NextScripts_083B5578[];
void BlendBgPaletteBanksNow(u32, u32, u32);
void BlendObjPaletteBanksNow(u32, u32, u32);
void InitDialogue(u32, u32, u32);

void DispatchPartListCallbacks(void)
{
    if (!sub_0803EED8())
    {
        if (gRenderMode == 2)
        {
            u32 fill = 512;
            CpuFastSet(&fill, gRenderWork->objects, 0x01000100);
        }
        gState0NextCallbacks_083ACCD4[gNestedCallbackIndex]();
    }
}

void sub_0800DA34(void)
{
    volatile u16 *bg0;
    volatile u16 *bg1;
    volatile u16 *bg2;
    volatile u16 *bg3;
    u32 fill;
    if (gState0TypedWork.bytes[0x42] == 1) UpdateSelectedPartPreview();
    else if (gState0TypedWork.bytes[0x3C] == 4) PlayMusic(7);
    *(volatile u16 *)0x04000000 &= 0xF0FF;
    bg0 = (volatile u16 *)0x04000008;
    *bg0 = 0x500;
    bg1 = (volatile u16 *)0x0400000A;
    *bg1 = 0x1801;
    bg2 = (volatile u16 *)0x0400000C;
    *bg2 = 0x1902;
    bg3 = (volatile u16 *)0x0400000E;
    *bg3 = 0x1A03;
    LeDecompress((const void *)0x084ED4F0, (void *)0x06004000);
    LeDecompress((const void *)0x084C4830, (void *)0x06006000);
    LeDecompress((const void *)0x084C4B4C, (void *)0x06006A00);
    LeDecompress((const void *)0x084C3F0C, (void *)0x06006C00);
    LeDecompress((const void *)0x084C88B8, (void *)0x06017E00);
    LeDecompress((const void *)0x08487DD8, (void *)0x06007000);
    LeDecompress((const void *)0x084C8034, (void *)0x06017400);
    LoadLeTilemap(0, 0, (const u8 *)0x084F0AF0, *bg0, 512);
    LoadLeTilemap(0, 0, (const u8 *)0x084F1514, *bg1, 512);
    LoadLeTilemap(0, 0, (const u8 *)0x084F2190, *bg2, 512);
    LoadLeTilemap(0, 0, (const u8 *)0x084F32D4, *bg3, 512);
    if (gState0TypedWork.bytes[0x42] == 1)
    {
        CpuFastSet((const void *)0x084F4A00, (void *)0x0202FA00, 112);
        CpuFastSet((const void *)0x05000200, (void *)0x0202F800, 128);
        CpuFastSet((const void *)0x0850F318, (void *)0x0202F9A0, 8);
        CpuFastSet((const void *)0x084E43F8, (void *)0x0202F9C0, 8);
        CpuFastSet((const void *)0x084885E0, (void *)0x0202FB60, 8);
        gState0TypedWork.bytes[0x84] = 0;
    }
    else
    {
        CpuFastSet((const void *)0x084F4A00, (void *)0x05000000, 112);
        CpuFastSet((const void *)0x0850F318, (void *)0x050003A0, 8);
        CpuFastSet((const void *)0x084E43F8, (void *)0x050003C0, 8);
        CpuFastSet((const void *)0x084885E0, (void *)0x05000160, 8);
        StartBlendFade(5, 63, 32);
    }
    fill = 0;
    CpuFastSet(&fill, gFrameObjects, 0x01000800);
    *(volatile u16 *)0x04000000 |= 0x1F60;
    CopyTilemapRect(10, 2, 16, 0, gState0NextText_083B4C60[gState0TypedWork.bytes[0x3E] + 89], *(volatile u16 *)0x04000008, 512);
    SplitPartIndexIntoPageRow();
    sub_08042950(gState0TypedWork.bytes[0x3F] + 1, 11, 2, 2, *(volatile u16 *)0x0400000A, 0x7360);
    DrawPartPageNames();
    DrawPartPageCounts();
    DrawPartPageAssignedCounts();
    DrawPartPageStatusTiles();
    InitPartPageMarkerPair();
    PlacePartRowCursor();
    gState0TypedWork.bytes[0x44] = 0;
    if (gState0TypedWork.bytes[0x42] != 1) InitPartListPreview();
    gNestedCallbackIndex++;
}

void sub_0800DD88(void)
{
    ScrollBg3Diagonally3();
    BlinkPartPageMarkerPair();
    SetObjectXWobble(3, *(u8 *)&gFrameCounter, 80);
    UpdateSelectedPartPreview();
    InitDialogue(1, 2, 0);
    gNestedCallbackIndex++;
}

void sub_0800DDC0(void)
{
    ScrollBg3Diagonally3();
    BlinkPartPageMarkerPair();
    SetObjectXWobble(3, *(u8 *)&gFrameCounter, 80);
    UpdateSelectedPartPreview();
    if (RunDialogue(gState0NextScripts_083B5578[16])) gNestedCallbackIndex++;
}

void sub_0800DE00(void)
{
    ScrollBg3Diagonally3();
    BlinkPartPageMarkerPair();
    SetObjectXWobble(3, *(u8 *)&gFrameCounter, 80);
    UpdateSelectedPartPreview();
    if (MovePartRowOnUpDown()) return;
    if (MovePartPageOnLeftRight()) return;
    if (CyclePartCategoryOnLR()) return;
    if (*(u8 *)&gNewKeys & 2)
    {
        if (gState0TypedWork.bytes[0x3C] == 4) PlaySoundEffect(6);
        else
        {
            PlaySoundEffect(5);
            gNestedCallbackIndex++;
        }
    }
    else if (*(u8 *)&gNewKeys & 1)
    {
        if ((u16)sub_08042114(gState0TypedWork.bytes[0x3D], gState0TypedWork.bytes[0x3E]))
        {
            PlaySoundEffect(4);
            if (gState0TypedWork.bytes[0x3C] == 4) gNestedCallbackIndex = 64;
            else gNestedCallbackIndex = 10;
        }
        else PlaySoundEffect(6);
    }
}

void sub_0800DEC8(void)
{
    StartBlendFade(6, 63, 32);
    CpuFastSet((const void *)0x084E43D8, (void *)0x050003E0, 8);
    ScrollBg3Diagonally3();
    BlinkPartPageMarkerPair();
    SetObjectXWobble(3, *(u8 *)&gFrameCounter, 80);
    UpdateSelectedPartPreview();
    gNestedCallbackIndex++;
}

void sub_0800DF14(void)
{
    ScrollBg3Diagonally3();
    BlinkPartPageMarkerPair();
    SetObjectXWobble(3, *(u8 *)&gFrameCounter, 80);
    UpdateSelectedPartPreview();
    if (StepBlendFade()) gNestedCallbackIndex++;
}

void sub_0800DF4C(void)
{
    ClearFrameObjects(0, 128);
    gRenderMode = 0;
    gMainSubstate = 2;
    gNestedCallbackIndex = 16;
}


#include "state0_callbacks.h"
#include "state0_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "main.h"
#include "display_helpers.h"
#include "effect_work.h"
#include "object_helpers.h"
#include "graphics.h"
#include "compression.h"
#include "render_work.h"
#include "tile_text.h"

extern const MainCallback gState0NextCallbacks_083ACCD4[];
extern const void *const gState0NextText_083B4C60[];
extern const void *const gState0NextScripts_083B5578[];
void BlendBgPaletteBanksNow(u32, u32, u32);
void BlendObjPaletteBanksNow(u32, u32, u32);
void InitDialogue(u32, u32, u32);

void sub_0800DD00(void)
{
    ScrollBg3Diagonally3();
    BlinkPartPageMarkerPair();
    SetObjectXWobble(3, *(u8 *)&gFrameCounter, 80);
    UpdateSelectedPartPreview();
    { u8 *work = gState0TypedWork.bytes;
    u8 *state = work + 0x42;
    if (*state == 1)
    {
        if (work[0x84] <= 8)
        {
            BlendBgPaletteBanksNow(0, 32 - work[0x84] * 4, 0xFFFF);
            BlendObjPaletteBanksNow(0, 32 - work[0x84] * 4, 0xF0FF);
            work[0x84]++;
            return;
        }
    }
    else if (!StepBlendFade()) return;
    *state = 0;
    gNestedCallbackIndex++;
    }
}

void sub_0800DF78(void)
{
    ScrollBg3Diagonally3();
    BlinkPartPageMarkerPair();
    SetObjectXWobble(3, *(u8 *)&gFrameCounter, 80);
    UpdateSelectedPartPreview();
    SnapshotPalettes();
    gState0TypedWork.bytes[0x84] = 0;
    gNestedCallbackIndex++;
}

void sub_0800DFB8(void)
{
    ScrollBg3Diagonally3();
    BlinkPartPageMarkerPair();
    SetObjectXWobble(3, *(u8 *)&gFrameCounter, 80);
    UpdateSelectedPartPreview();
    if (gState0TypedWork.bytes[0x84] <= 8)
    {
        BlendBgPaletteBanksNow(0, gState0TypedWork.bytes[0x84] * 4, 0xFFFF);
        BlendObjPaletteBanksNow(0, gState0TypedWork.bytes[0x84] * 4, 0xF0FF);
        gState0TypedWork.bytes[0x84]++;
    }
    else gNestedCallbackIndex = 16;
}


#include "state0_callbacks.h"
#include "state0_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "main.h"
#include "display_helpers.h"
#include "effect_work.h"
#include "object_helpers.h"
#include "graphics.h"
#include "compression.h"
#include "render_work.h"
#include "tile_text.h"

extern const MainCallback gState0NextCallbacks_083ACCD4[];
extern const void *const gState0NextText_083B4C60[];
extern const void *const gState0NextScripts_083B5578[];
void BlendBgPaletteBanksNow(u32, u32, u32);
void BlendObjPaletteBanksNow(u32, u32, u32);
void InitDialogue(u32, u32, u32);

u32 CycleSelectablePartOnLeftRight(void);
extern const void *const gState0NextScripts_083BE564[];
extern const void *const gState0NextScripts_083BEAAC[];
void sub_0800E2B0(void)
{
    u8 *work;
    ScrollBg3Diagonally3();
    UpdateSelectedPartPreview();
    BlinkPartDetailMarkerPair();
    work = gState0TypedWork.bytes;
    if (work[0x3C] == 0 || work[0x3C] == 4)
    {
        if (work[0x84] <= 8)
        {
            BlendBgPaletteBanksNow(0, 32 - work[0x84] * 4, 0xFFFF);
            BlendObjPaletteBanksNow(0, 32 - work[0x84] * 4, 0xF0FF);
            work[0x84]++;
            return;
        }
    }
    else if (!StepBlendFade()) return;
    gNestedCallbackIndex++;
}

void sub_0800E328(void)
{
    ScrollBg3Diagonally3();
    UpdateSelectedPartPreview();
    BlinkPartDetailMarkerPair();
    InitDialogue(1, 2, 0);
    gNestedCallbackIndex++;
}

void sub_0800E3A0(void)
{
    ScrollBg3Diagonally3();
    UpdateSelectedPartPreview();
    BlinkPartDetailMarkerPair();
    if (CycleSelectablePartOnLeftRight())
    {
        RestartDialogueText();
        gNestedCallbackIndex--;
    }
    else if (*(u8 *)&gNewKeys & KEY_B)
    {
        PlaySoundEffect(5);
        gNestedCallbackIndex++;
    }
    else if (*(u8 *)&gNewKeys & KEY_START)
    {
        PlaySoundEffect(4);
        switch (gState0TypedWork.bytes[0x3E])
        {
        case 0: gState0TypedWork.bytes[0x43] = 3; break;
        case 1:
        case 2: gState0TypedWork.bytes[0x43] = 4; break;
        case 3: gState0TypedWork.bytes[0x43] = 5; break;
        }
        gNestedCallbackIndex = 32;
    }
}

void sub_0800E43C(void)
{
    u8 *work;
    ScrollBg3Diagonally3();
    UpdateSelectedPartPreview();
    BlinkPartDetailMarkerPair();
    work = gState0TypedWork.bytes;
    if (work[0x3C] == 0 || work[0x3C] == 4)
    {
        SnapshotPalettes();
        work[0x84] = 0;
    }
    else StartBlendFade(6, 63, 32);
    gNestedCallbackIndex++;
}

void sub_0800E488(void)
{
    u8 *work;
    ScrollBg3Diagonally3();
    UpdateSelectedPartPreview();
    BlinkPartDetailMarkerPair();
    work = gState0TypedWork.bytes;
    if (work[0x3C] == 0 || work[0x3C] == 4)
    {
        if (work[0x84] <= 8)
        {
            BlendBgPaletteBanksNow(0, work[0x84] * 4, 0xFFFF);
            BlendObjPaletteBanksNow(0, work[0x84] * 4, 0xF0FF);
            work[0x84]++;
            return;
        }
    }
    else if (!StepBlendFade()) return;
    gNestedCallbackIndex++;
}


#include "state0_callbacks.h"
#include "state0_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "main.h"
#include "display_helpers.h"
#include "effect_work.h"
#include "object_helpers.h"
#include "graphics.h"
#include "compression.h"
#include "render_work.h"
#include "tile_text.h"

extern const MainCallback gState0NextCallbacks_083ACCD4[];
extern const void *const gState0NextText_083B4C60[];
extern const void *const gState0NextScripts_083B5578[];
void BlendBgPaletteBanksNow(u32, u32, u32);
void BlendObjPaletteBanksNow(u32, u32, u32);
void InitDialogue(u32, u32, u32);

u32 CycleSelectablePartOnLeftRight(void);
extern const void *const gState0NextScripts_083BE564[];
extern const void *const gState0NextScripts_083BEAAC[];
#include "equipment_helpers.h"
#include "record_helpers.h"
void FadeOutMusic(u32);
extern const u8 *const gState0NextCommands_083B6100[];
extern u32 gUnknownMask_03002B68;
void sub_0800E4F8(void)
{
    UpdateSelectedPartPreview();
    ClearFrameObjects(0, 128);
    switch (gState0TypedWork.bytes[0x3C])
    {
    case 0:
    case 4: gNestedCallbackIndex = 0; break;
    case 1:
        gRenderMode = 0;
        gMainSubstate = 3;
        gNestedCallbackIndex = 16;
        switch (gState0TypedWork.bytes[0x3E])
        {
        case 0: gState0TypedWork.bytes[0x98] = gState0TypedWork.bytes[0x3D]; break;
        case 1: gState0TypedWork.bytes[0x99] = gState0TypedWork.bytes[0x3D]; break;
        case 2: gState0TypedWork.bytes[0x9A] = gState0TypedWork.bytes[0x3D]; break;
        case 3: gState0TypedWork.bytes[0x9B] = gState0TypedWork.bytes[0x3D]; break;
        }
        break;
    case 2:
        { u32 zero = 0; CpuFastSet(&zero, (void *)0x05000200, 0x01000080); }
        { u32 zero = 0; CpuFastSet(&zero, (void *)0x05000000, 0x01000080); }
        gRenderMode = 0;
        gMainSubstate = 6;
        gNestedCallbackIndex = 101;
        break;
    case 3:
        { u32 zero = 0; CpuFastSet(&zero, (void *)0x05000200, 0x01000080); }
        { u32 zero = 0; CpuFastSet(&zero, (void *)0x05000000, 0x01000080); }
        gRenderMode = 0;
        gMainState = 2;
        gMainSubstate = 25;
        gNestedCallbackIndex = 0;
        break;
    }
}

void sub_0800E654(void)
{
    ScrollBg3Diagonally3();
    UpdateSelectedPartPreview();
    HideFrameObjects(1, 5);
    CpuFastSet((const void *)0x084E4418, (void *)0x050003C0, 8);
    InitTableCursorObject();
    RestartDialogueText();
    gNestedCallbackIndex++;
}

void sub_0800E690(void)
{
    ScrollBg3Diagonally3();
    UpdateSelectedPartPreview();
    RunFrameObjectCommands(gState0NextCommands_083B6100[3], 6);
    if (RunDialogue(gState0NextScripts_083B5578[5])) gNestedCallbackIndex++;
}

void sub_0800E9F0(void)
{
    ScrollBg3Diagonally3();
    UpdateSelectedPartPreview();
    HideFrameObjects(6, 1);
    CpuFastSet((const void *)0x084E43F8, (void *)0x050003C0, 8);
    RestartDialogueText();
    InitPartDetailMarkerPair();
    gNestedCallbackIndex = 19;
}

void sub_0800EA2C(void)
{
    ScrollBg3Diagonally3();
    UpdateSelectedPartPreview();
    gFrameObjects[1].flags &= 0xBFFF;
    gFrameObjects[2].flags &= 0xBFFF;
    LoadLeTilemap(18, 5, (const void *)0x08488494, *(volatile u16 *)0x04000008, 896);
    gState0TypedWork.bytes[0x4A] = 0;
    InitObject4RowCursor();
    gNestedCallbackIndex++;
}

void WaitRowCursorBlinkAndShrink(void)
{
    ScrollBg3Diagonally3();
    UpdateSelectedPartPreview();
    if (StepRowCursorBlinkShrink())
    {
        HideFrameObjects(4, 1);
        gNestedCallbackIndex++;
    }
}

void sub_0800EB60(void)
{
    ScrollBg3Diagonally3();
    UpdateSelectedPartPreview();
    switch (gState0TypedWork.bytes[0x4A])
    {
    case 0: gNestedCallbackIndex = 10; break;
    case 1: FadeOutMusic(8); gNestedCallbackIndex++; break;
    case 2: gNestedCallbackIndex = 4; break;
    }
}

void sub_0800EBB8(void)
{
    gUnknownMask_03002B68 = (gState0TypedWork.bytes[0x3E] << 16) + gState0TypedWork.bytes[0x3D];
    gNestedCallbackIndex++;
}

void sub_0800EBE4(void)
{
    ClearFrameObjects(0, 128);
    ClearBgScrolls2();
    sub_08044CDC(2);
}


#include "state0_callbacks.h"
#include "state0_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "main.h"
#include "display_helpers.h"
#include "effect_work.h"
#include "object_helpers.h"
#include "graphics.h"
#include "compression.h"
#include "render_work.h"
#include "tile_text.h"

extern const MainCallback gState0NextCallbacks_083ACCD4[];
extern const void *const gState0NextText_083B4C60[];
extern const void *const gState0NextScripts_083B5578[];
void BlendBgPaletteBanksNow(u32, u32, u32);
void BlendObjPaletteBanksNow(u32, u32, u32);
void InitDialogue(u32, u32, u32);

u32 CycleSelectablePartOnLeftRight(void);
extern const void *const gState0NextScripts_083BE564[];
extern const void *const gState0NextScripts_083BEAAC[];
#include "equipment_helpers.h"
#include "record_helpers.h"
void FadeOutMusic(u32);
extern const u8 *const gState0NextCommands_083B6100[];
extern u32 gUnknownMask_03002B68;
void sub_0800E6C8(void)
{
    u32 up;
    ScrollBg3Diagonally3();
    UpdateSelectedPartPreview();
    RunFrameObjectCommands(gState0NextCommands_083B6100[3], 6);
    up = (u8)(*(u8 *)&gRepeatedKeys & KEY_UP);
    if (up)
    {
        u8 *work = gState0TypedWork.bytes;
        if (work[0x44] == 0) work[0x44] = work[0x45] - 1;
        else work[0x44]--;
        PlaySoundEffect(2);
        UpdateTableCursorPosition();
    }
    else if (*(u8 *)&gRepeatedKeys & KEY_DOWN)
    {
        u8 *work = gState0TypedWork.bytes;
        if (work[0x44] == work[0x45] - 1) work[0x44] = up;
        else work[0x44]++;
        PlaySoundEffect(2);
        UpdateTableCursorPosition();
    }
    else if (*(u8 *)&gNewKeys & KEY_A)
    {
        PlaySoundEffect(4);
        InitTableCursorObject();
        RestartDialogueText();
        gNestedCallbackIndex++;
    }
    else if (*(u8 *)&gNewKeys & (KEY_B | KEY_START))
    {
        PlaySoundEffect(5);
        gNestedCallbackIndex = 36;
    }
}
