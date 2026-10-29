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
void sub_0803F684(u32, u32, u32);
void sub_0803F998(u32, u32, u32);
void sub_0803FAA0(u32, u32, u32);

void sub_0800D9DC(void)
{
    if (!sub_0803EED8())
    {
        if (gRenderMode == 2)
        {
            u32 fill = 512;
            CpuFastSet(&fill, gRenderWork->objects, 0x01000100);
        }
        gState0NextCallbacks_083ACCD4[gUnknown_0300137C]();
    }
}

void sub_0800DA34(void)
{
    volatile u16 *bg0;
    volatile u16 *bg1;
    volatile u16 *bg2;
    volatile u16 *bg3;
    u32 fill;
    if (gState0TypedWork.bytes[0x42] == 1) sub_0800F440();
    else if (gState0TypedWork.bytes[0x3C] == 4) sub_08074B88(7);
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
        sub_0804253C(5, 63, 32);
    }
    fill = 0;
    CpuFastSet(&fill, gFrameObjects, 0x01000800);
    *(volatile u16 *)0x04000000 |= 0x1F60;
    sub_0803F15C(10, 2, 16, 0, gState0NextText_083B4C60[gState0TypedWork.bytes[0x3E] + 89], *(volatile u16 *)0x04000008, 512);
    sub_0800EC20();
    sub_08042950(gState0TypedWork.bytes[0x3F] + 1, 11, 2, 2, *(volatile u16 *)0x0400000A, 0x7360);
    sub_0800EC44();
    sub_0800ED10();
    sub_0800EDA0();
    sub_0800EE34();
    sub_0800EEE4();
    sub_0800EFB0();
    gState0TypedWork.bytes[0x44] = 0;
    if (gState0TypedWork.bytes[0x42] != 1) sub_0800F218();
    gUnknown_0300137C++;
}

void sub_0800DD88(void)
{
    sub_0800EBFC();
    sub_0800EF58();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 80);
    sub_0800F440();
    sub_0803FAA0(1, 2, 0);
    gUnknown_0300137C++;
}

void sub_0800DDC0(void)
{
    sub_0800EBFC();
    sub_0800EF58();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 80);
    sub_0800F440();
    if (sub_0803FB3C(gState0NextScripts_083B5578[16])) gUnknown_0300137C++;
}

void sub_0800DE00(void)
{
    sub_0800EBFC();
    sub_0800EF58();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 80);
    sub_0800F440();
    if (sub_0800EFFC()) return;
    if (sub_0800F08C()) return;
    if (sub_0800F148()) return;
    if (*(u8 *)&gNewKeys & 2)
    {
        if (gState0TypedWork.bytes[0x3C] == 4) sub_08074DE0(6);
        else
        {
            sub_08074DE0(5);
            gUnknown_0300137C++;
        }
    }
    else if (*(u8 *)&gNewKeys & 1)
    {
        if ((u16)sub_08042114(gState0TypedWork.bytes[0x3D], gState0TypedWork.bytes[0x3E]))
        {
            sub_08074DE0(4);
            if (gState0TypedWork.bytes[0x3C] == 4) gUnknown_0300137C = 64;
            else gUnknown_0300137C = 10;
        }
        else sub_08074DE0(6);
    }
}

void sub_0800DEC8(void)
{
    sub_0804253C(6, 63, 32);
    CpuFastSet((const void *)0x084E43D8, (void *)0x050003E0, 8);
    sub_0800EBFC();
    sub_0800EF58();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 80);
    sub_0800F440();
    gUnknown_0300137C++;
}

void sub_0800DF14(void)
{
    sub_0800EBFC();
    sub_0800EF58();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 80);
    sub_0800F440();
    if (sub_080425DC()) gUnknown_0300137C++;
}

void sub_0800DF4C(void)
{
    sub_08040CD0(0, 128);
    gRenderMode = 0;
    gMainSubstate = 2;
    gUnknown_0300137C = 16;
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
void sub_0803F684(u32, u32, u32);
void sub_0803F998(u32, u32, u32);
void sub_0803FAA0(u32, u32, u32);

void sub_0800DD00(void)
{
    sub_0800EBFC();
    sub_0800EF58();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 80);
    sub_0800F440();
    { u8 *work = gState0TypedWork.bytes;
    u8 *state = work + 0x42;
    if (*state == 1)
    {
        if (work[0x84] <= 8)
        {
            sub_0803F684(0, 32 - work[0x84] * 4, 0xFFFF);
            sub_0803F998(0, 32 - work[0x84] * 4, 0xF0FF);
            work[0x84]++;
            return;
        }
    }
    else if (!sub_080425DC()) return;
    *state = 0;
    gUnknown_0300137C++;
    }
}

void sub_0800DF78(void)
{
    sub_0800EBFC();
    sub_0800EF58();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 80);
    sub_0800F440();
    SnapshotPalettes();
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_0800DFB8(void)
{
    sub_0800EBFC();
    sub_0800EF58();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 80);
    sub_0800F440();
    if (gState0TypedWork.bytes[0x84] <= 8)
    {
        sub_0803F684(0, gState0TypedWork.bytes[0x84] * 4, 0xFFFF);
        sub_0803F998(0, gState0TypedWork.bytes[0x84] * 4, 0xF0FF);
        gState0TypedWork.bytes[0x84]++;
    }
    else gUnknown_0300137C = 16;
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
void sub_0803F684(u32, u32, u32);
void sub_0803F998(u32, u32, u32);
void sub_0803FAA0(u32, u32, u32);

u32 sub_0800FDD8(void);
extern const void *const gState0NextScripts_083BE564[];
extern const void *const gState0NextScripts_083BEAAC[];
void sub_0800E2B0(void)
{
    u8 *work;
    sub_0800EBFC();
    sub_0800F440();
    sub_0800FD74();
    work = gState0TypedWork.bytes;
    if (work[0x3C] == 0 || work[0x3C] == 4)
    {
        if (work[0x84] <= 8)
        {
            sub_0803F684(0, 32 - work[0x84] * 4, 0xFFFF);
            sub_0803F998(0, 32 - work[0x84] * 4, 0xF0FF);
            work[0x84]++;
            return;
        }
    }
    else if (!sub_080425DC()) return;
    gUnknown_0300137C++;
}

void sub_0800E328(void)
{
    sub_0800EBFC();
    sub_0800F440();
    sub_0800FD74();
    sub_0803FAA0(1, 2, 0);
    gUnknown_0300137C++;
}

void sub_0800E3A0(void)
{
    sub_0800EBFC();
    sub_0800F440();
    sub_0800FD74();
    if (sub_0800FDD8())
    {
        sub_0803FB0C();
        gUnknown_0300137C--;
    }
    else if (*(u8 *)&gNewKeys & KEY_B)
    {
        sub_08074DE0(5);
        gUnknown_0300137C++;
    }
    else if (*(u8 *)&gNewKeys & KEY_START)
    {
        sub_08074DE0(4);
        switch (gState0TypedWork.bytes[0x3E])
        {
        case 0: gState0TypedWork.bytes[0x43] = 3; break;
        case 1:
        case 2: gState0TypedWork.bytes[0x43] = 4; break;
        case 3: gState0TypedWork.bytes[0x43] = 5; break;
        }
        gUnknown_0300137C = 32;
    }
}

void sub_0800E43C(void)
{
    u8 *work;
    sub_0800EBFC();
    sub_0800F440();
    sub_0800FD74();
    work = gState0TypedWork.bytes;
    if (work[0x3C] == 0 || work[0x3C] == 4)
    {
        SnapshotPalettes();
        work[0x84] = 0;
    }
    else sub_0804253C(6, 63, 32);
    gUnknown_0300137C++;
}

void sub_0800E488(void)
{
    u8 *work;
    sub_0800EBFC();
    sub_0800F440();
    sub_0800FD74();
    work = gState0TypedWork.bytes;
    if (work[0x3C] == 0 || work[0x3C] == 4)
    {
        if (work[0x84] <= 8)
        {
            sub_0803F684(0, work[0x84] * 4, 0xFFFF);
            sub_0803F998(0, work[0x84] * 4, 0xF0FF);
            work[0x84]++;
            return;
        }
    }
    else if (!sub_080425DC()) return;
    gUnknown_0300137C++;
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
void sub_0803F684(u32, u32, u32);
void sub_0803F998(u32, u32, u32);
void sub_0803FAA0(u32, u32, u32);

u32 sub_0800FDD8(void);
extern const void *const gState0NextScripts_083BE564[];
extern const void *const gState0NextScripts_083BEAAC[];
#include "equipment_helpers.h"
#include "record_helpers.h"
void sub_080750F0(u32);
extern const u8 *const gState0NextCommands_083B6100[];
extern u32 gUnknownMask_03002B68;
void sub_0800E4F8(void)
{
    sub_0800F440();
    sub_08040CD0(0, 128);
    switch (gState0TypedWork.bytes[0x3C])
    {
    case 0:
    case 4: gUnknown_0300137C = 0; break;
    case 1:
        gRenderMode = 0;
        gMainSubstate = 3;
        gUnknown_0300137C = 16;
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
        gUnknown_0300137C = 101;
        break;
    case 3:
        { u32 zero = 0; CpuFastSet(&zero, (void *)0x05000200, 0x01000080); }
        { u32 zero = 0; CpuFastSet(&zero, (void *)0x05000000, 0x01000080); }
        gRenderMode = 0;
        gMainState = 2;
        gMainSubstate = 25;
        gUnknown_0300137C = 0;
        break;
    }
}

void sub_0800E654(void)
{
    sub_0800EBFC();
    sub_0800F440();
    sub_08040D0C(1, 5);
    CpuFastSet((const void *)0x084E4418, (void *)0x050003C0, 8);
    sub_0800FF50();
    sub_0803FB0C();
    gUnknown_0300137C++;
}

void sub_0800E690(void)
{
    sub_0800EBFC();
    sub_0800F440();
    sub_08040BD8(gState0NextCommands_083B6100[3], 6);
    if (sub_0803FB3C(gState0NextScripts_083B5578[5])) gUnknown_0300137C++;
}

void sub_0800E9F0(void)
{
    sub_0800EBFC();
    sub_0800F440();
    sub_08040D0C(6, 1);
    CpuFastSet((const void *)0x084E43F8, (void *)0x050003C0, 8);
    sub_0803FB0C();
    sub_0800FCF0();
    gUnknown_0300137C = 19;
}

void sub_0800EA2C(void)
{
    sub_0800EBFC();
    sub_0800F440();
    gFrameObjects[1].flags &= 0xBFFF;
    gFrameObjects[2].flags &= 0xBFFF;
    LoadLeTilemap(18, 5, (const void *)0x08488494, *(volatile u16 *)0x04000008, 896);
    gState0TypedWork.bytes[0x4A] = 0;
    sub_08010040();
    gUnknown_0300137C++;
}

void sub_0800EB34(void)
{
    sub_0800EBFC();
    sub_0800F440();
    if (sub_0801013C())
    {
        sub_08040D0C(4, 1);
        gUnknown_0300137C++;
    }
}

void sub_0800EB60(void)
{
    sub_0800EBFC();
    sub_0800F440();
    switch (gState0TypedWork.bytes[0x4A])
    {
    case 0: gUnknown_0300137C = 10; break;
    case 1: sub_080750F0(8); gUnknown_0300137C++; break;
    case 2: gUnknown_0300137C = 4; break;
    }
}

void sub_0800EBB8(void)
{
    gUnknownMask_03002B68 = (gState0TypedWork.bytes[0x3E] << 16) + gState0TypedWork.bytes[0x3D];
    gUnknown_0300137C++;
}

void sub_0800EBE4(void)
{
    sub_08040CD0(0, 128);
    sub_08043CA8();
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
void sub_0803F684(u32, u32, u32);
void sub_0803F998(u32, u32, u32);
void sub_0803FAA0(u32, u32, u32);

u32 sub_0800FDD8(void);
extern const void *const gState0NextScripts_083BE564[];
extern const void *const gState0NextScripts_083BEAAC[];
#include "equipment_helpers.h"
#include "record_helpers.h"
void sub_080750F0(u32);
extern const u8 *const gState0NextCommands_083B6100[];
extern u32 gUnknownMask_03002B68;
void sub_0800E6C8(void)
{
    u32 up;
    sub_0800EBFC();
    sub_0800F440();
    sub_08040BD8(gState0NextCommands_083B6100[3], 6);
    up = (u8)(*(u8 *)&gRepeatedKeys & KEY_UP);
    if (up)
    {
        u8 *work = gState0TypedWork.bytes;
        if (work[0x44] == 0) work[0x44] = work[0x45] - 1;
        else work[0x44]--;
        sub_08074DE0(2);
        sub_0800FFF4();
    }
    else if (*(u8 *)&gRepeatedKeys & KEY_DOWN)
    {
        u8 *work = gState0TypedWork.bytes;
        if (work[0x44] == work[0x45] - 1) work[0x44] = up;
        else work[0x44]++;
        sub_08074DE0(2);
        sub_0800FFF4();
    }
    else if (*(u8 *)&gNewKeys & KEY_A)
    {
        sub_08074DE0(4);
        sub_0800FF50();
        sub_0803FB0C();
        gUnknown_0300137C++;
    }
    else if (*(u8 *)&gNewKeys & (KEY_B | KEY_START))
    {
        sub_08074DE0(5);
        gUnknown_0300137C = 36;
    }
}
