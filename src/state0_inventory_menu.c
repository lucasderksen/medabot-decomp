#include "state0_callbacks.h"
#include "state0_inventory_menu.h"
#include "state0_work.h"
#include "state0_inventory.h"
#include "display_helpers.h"
#include "graphics.h"
#include "compression.h"
#include "frame.h"
#include "main.h"
#include "input.h"

extern const MainCallback gUnknownCallbacks_083AC86C[];
extern const u8 gUnknownPalette_0850F2F8[];
void sub_080093F8(void);
void sub_0800941C(void);
void sub_0800944C(void);
void sub_08009484(void);
void sub_08009540(void);
void sub_08009620(void);
void sub_080096BC(void);
void sub_08009750(void);
void sub_080097E0(void);
void sub_0800988C(void);
void sub_08009900(void);
void sub_0800994C(void);
void sub_080099A4(void);
void sub_08009A38(void);
void sub_08009AF8(void);
void sub_08009BC8(void);
void sub_08009CDC(void);
void sub_08009D30(void);
void sub_08009DA0(void);
void sub_08044CDC(u32);

void sub_08007584(void)
{
    if (!sub_0803EED8())
        gUnknownCallbacks_083AC86C[gUnknown_0300137C]();
}

void sub_080075AC(void)
{
    *(volatile u16 *)0x04000000 &= 0xF0FF;
    *(volatile u16 *)0x04000008 = 0x0500;
    *(volatile u16 *)0x0400000A = 0x1801;
    *(volatile u16 *)0x0400000C = 0x1902;
    *(volatile u16 *)0x0400000E = 0x1A03;
    LeDecompress((const u8 *)0x084E8804, (void *)0x06004000);
    LeDecompress((const u8 *)0x084C3AF8, (void *)0x06006000);
    LeDecompress((const u8 *)0x084C3A24, (void *)0x06006280);
    LeDecompress((const u8 *)0x084C50D0, (void *)0x06007400);
    LeDecompress((const u8 *)0x084C5250, (void *)0x06007600);
    LeDecompress((const u8 *)0x084C8034, (void *)0x06017400);
    LeDecompress((const u8 *)0x084C88B8, (void *)0x06017E00);
    LeDecompress((const u8 *)0x08487DD8, (void *)0x06006A00);
    LoadLeTilemap(0, 0, (const u8 *)0x084F08E8, *(volatile u16 *)0x04000008, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F10FC, *(volatile u16 *)0x0400000A, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F1A90, *(volatile u16 *)0x0400000C, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F2AF4, *(volatile u16 *)0x0400000E, 0x200);
    CpuFastSet((const void *)0x084F4140, (void *)0x05000000, 0x70);
    CpuFastSet((const void *)0x084885E0, (void *)0x05000160, 8);
    CpuFastSet((const void *)0x0850F498, (void *)0x05000200, 0x40);
    CpuFastSet(gUnknownPalette_0850F2F8, (void *)0x05000300, 8);
    CpuFastSet(gUnknownPalette_0850F2F8 - 64, (void *)0x05000320, 8);
    CpuFastSet((const void *)0x084E4438, (void *)0x050003A0, 8);
    CpuFastSet(gUnknownPalette_0850F2F8 + 192, (void *)0x05000340, 8);
    CpuFastSet((const void *)0x084E43F8, (void *)0x050003C0, 8);
    {
        u32 fill = 0;
        CpuFastSet(&fill, gFrameObjects, CPU_SET_FILL | 0x800);
    }
    *(volatile u16 *)0x04000000 |= 0x1F60;
    sub_0800941C();
    sub_0803F15C(10, 2, 5, 2, gUnknownPointers_083B4C60[gState0TypedWork.bytes[0x3F] + 75], *(volatile u16 *)0x0400000A, 0x200);
    sub_08009484();
    sub_08009540();
    sub_08009620();
    sub_080096BC();
    sub_08009750();
    sub_080097E0();
    sub_0800988C();
    sub_08009900();
    sub_0800944C();
    sub_08009CDC();
    sub_08009D30();
    sub_08009DA0();
    sub_0804253C(5, 63, 32);
    if (gState0TypedWork.bytes[0x3C] == 4 && !gState0TypedWork.bytes[0x4B])
    {
        gState0TypedWork.bytes[0x4B] = 1;
        sub_08074B88(7);
    }
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_08007834(void)
{
    sub_080093F8();
    sub_0800994C();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 24);
    if (sub_080425DC()) gUnknown_0300137C++;
}

void sub_08007868(void)
{
    u32 cancel;
    sub_080093F8(); sub_0800994C();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 24);
    sub_08009AF8(); sub_080099A4(); sub_08009A38(); sub_08009BC8();
    cancel = (u8)(*(u8 *)&gNewKeys & 2);
    if (cancel)
    {
        u8 *work = gState0TypedWork.bytes;
        if (work[0x3E] & 0x80)
        {
            sub_08074DE0(2); work[0x3E] = 0; sub_08009AF8();
            goto done;
        }
        sub_08074DE0(5); gUnknown_0300137C++;
        goto done;
    }
    if (*(u8 *)&gNewKeys & 1)
    {
        u8 *work = gState0TypedWork.bytes;
        u32 selected = work[0x3F] * 6 + work[0x40];
        work[0x3D] = selected;
        if (gInventoryRecords[work[0x3D]].byte0 & 0x80)
        {
            sub_08074DE0(4);
            if (work[0x3C] == 4)
            {
                gUnknown_0300137C = 96;
                goto done;
            }
            work[0x42] = cancel;
            sub_0804253C(6, 63, 32);
            gUnknown_0300137C = 7;
            goto done;
        }
    }
    else goto done;
    sub_08074DE0(6);
done:
    return;
}

void sub_08007964(void)
{
    sub_0804253C(6, 63, 32);
    sub_080093F8(); sub_0800994C();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 24);
    gUnknown_0300137C++;
}

void sub_08007998(void)
{
    sub_080093F8(); sub_0800994C();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 24);
    if (sub_080425DC()) gUnknown_0300137C++;
}

void sub_080079CC(void)
{
    sub_08040CD0(0, 128);
    if (gState0TypedWork.bytes[0x3C] == 4)
        sub_08044CDC(0);
    else
    {
        gMainSubstate = 2;
        gUnknown_0300137C = 16;
    }
}


#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_inventory.h"
#include "display_helpers.h"
#include "graphics.h"
#include "compression.h"
#include "frame.h"
#include "main.h"
#include "input.h"

extern const u8 gUnknownPalette_0850F3D8[];
void sub_080093F8(void);
void sub_08009E4C(void);
void sub_08009EF4(void);
void sub_08009F50(void);
void sub_08009F90(void);
void sub_0800A000(void);
void sub_0800A05C(void);
void sub_0800A0B8(void);
void sub_0800A0FC(void);
void sub_0800A180(void);
void sub_0800A1E4(void);
void sub_0800A2B4(void);
void sub_0800B498(void);

void sub_08007A04(void)
{
    *(volatile u16 *)0x04000000 &= 0xF0FF;
    *(volatile u16 *)0x04000008 = 0x0500;
    *(volatile u16 *)0x0400000A = 0x1801;
    *(volatile u16 *)0x0400000C = 0x1902;
    *(volatile u16 *)0x0400000E = 0x1A03;
    LeDecompress((const u8 *)0x084E9650, (void *)0x06004000);
    LeDecompress((const u8 *)0x084C3A24, (void *)0x06006280);
    LeDecompress((const u8 *)0x084C3BF8, (void *)0x06006800);
    LeDecompress((const u8 *)0x084C88B8, (void *)0x06017E00);
    LoadLeTilemap(0, 0, (const u8 *)0x084F0920, *(volatile u16 *)0x04000008, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F1180, *(volatile u16 *)0x0400000A, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F1C28, *(volatile u16 *)0x0400000C, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F2C88, *(volatile u16 *)0x0400000E, 0x200);
    CpuFastSet((const void *)0x084F4300, (void *)0x05000000, 0x70);
    CpuFastSet(gUnknownPalette_0850F3D8, (void *)0x05000340, 8);
    CpuFastSet(gUnknownPalette_0850F3D8 - 96, (void *)0x05000360, 8);
    CpuFastSet(gUnknownPalette_0850F3D8 - 288, (void *)0x05000380, 8);
    CpuFastSet(gUnknownPalette_0850F3D8 - 256, (void *)0x050003A0, 8);
    CpuFastSet((const void *)0x084E43F8, (void *)0x050003C0, 8);
    {
        u32 fill = 0;
        CpuFastSet(&fill, gFrameObjects, CPU_SET_FILL | 0x800);
    }
    *(volatile u16 *)0x04000000 |= 0x1F60;
    gState0TypedWork.bytes[0x44] = 0;
    sub_08009E4C(); sub_08009EF4(); sub_08009F50(); sub_08009F90();
    sub_0800A000(); sub_0800A05C(); sub_0800A0B8(); sub_0800A0FC();
    sub_0804253C(5, 63, 32);
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_08007BD8(void)
{
    sub_080093F8(); sub_0800A180();
    if (sub_080425DC()) gUnknown_0300137C++;
}

void sub_08007BFC(void)
{
    sub_080093F8(); sub_0800A180();
    sub_0803FAA0(1, 2, 0);
    gUnknown_0300137C++;
}

void sub_08007C20(void)
{
    sub_080093F8(); sub_0800A180();
    if (sub_0803FB3C(gUnknownPointers_083B5578[4]))
        gUnknown_0300137C++;
}

void sub_08007C4C(void)
{
    u32 right;
    u8 *keys;
    sub_080093F8(); sub_0800A180(); sub_0800A1E4(); sub_0800A2B4();
    keys = (u8 *)&gNewKeys;
    if (keys[0] & 2)
    {
        sub_08074DE0(5);
        gUnknown_0300137C++;
    }
    else if (keys[1] & 2)
    {
        sub_08074DE0(2);
        gState0TypedWork.bytes[0x42] = (gState0TypedWork.bytes[0x42] - 1) & 3;
        gUnknown_0300137C = 20;
    }
    else if ((right = keys[1] & 1))
    {
        sub_08074DE0(2);
        gState0TypedWork.bytes[0x42] = (gState0TypedWork.bytes[0x42] + 1) & 3;
        gUnknown_0300137C = 20;
    }
    else if (keys[0] & 8)
    {
        sub_08074DE0(4);
        gState0TypedWork.bytes[0x43] = right;
        gUnknown_0300137C = 72;
    }
}


void sub_08007D04(void)
{
    sub_0804253C(6, 63, 32);
    sub_080093F8(); sub_0800A180();
    gUnknown_0300137C++;
}

void sub_08007D28(void)
{
    sub_08040CD0(0, 128);
    switch (gState0TypedWork.bytes[0x3C])
    {
    case 1:
    {
        u8 *work = gState0TypedWork.bytes;
        u32 selected = work[0x3D];
        work[0x97] = selected;
        gMainSubstate = 3;
        gUnknown_0300137C = 16;
        break;
    }
    case 2:
    {
        u32 first;
        u32 second;
        sub_0800B498();
        first = 0;
        CpuFastSet(&first, (void *)0x05000200, CPU_SET_FILL | 0x80);
        second = 0;
        CpuFastSet(&second, (void *)0x05000000, CPU_SET_FILL | 0x80);
        gMainSubstate = 7;
        gUnknown_0300137C = 60;
        break;
    }
    case 0: case 3: case 4:
        gUnknown_0300137C = 0;
        break;
    }
}

void sub_08007DDC(void)
{
    sub_08040CD0(0, 128);
    switch (gState0TypedWork.bytes[0x42])
    {
    case 0: gUnknown_0300137C = 8; break;
    case 1: gUnknown_0300137C = 24; break;
    case 2: gUnknown_0300137C = 40; break;
    default: gUnknown_0300137C = 56; break;
    }
}


#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_inventory.h"
#include "display_helpers.h"
#include "graphics.h"
#include "compression.h"
#include "frame.h"
#include "main.h"
#include "input.h"

extern const u8 gUnknownPalette_0850F358[];
extern const void *const gUnknownPointers_083B7D80[];
void sub_080093F8(void);
void sub_08009E4C(void);
void sub_08009EF4(void);
void sub_08009F50(void);
void sub_08009F90(void);
void sub_0800A0FC(void);
void sub_0800A180(void);
void sub_0800A1E4(void);
void sub_0800A2E8(void);
void sub_0800A594(void);
void sub_0800A854(void);
u32 sub_0800A8A0(void);
u32 sub_0800A928(void);
u32 sub_0800A960(void);

void sub_08007E38(void)
{
    *(volatile u16 *)0x04000000 &= 0xF0FF;
    *(volatile u16 *)0x04000008 = 0x0500;
    *(volatile u16 *)0x0400000A = 0x1801;
    *(volatile u16 *)0x0400000C = 0x1902;
    *(volatile u16 *)0x0400000E = 0x1A03;
    LeDecompress((const u8 *)0x084EA5C0, (void *)0x06004000);
    LeDecompress((const u8 *)0x084C3A24, (void *)0x06006280);
    LeDecompress((const u8 *)0x084C3D40, (void *)0x06006000);
    LeDecompress((const u8 *)0x084C3E64, (void *)0x06006680);
    LeDecompress((const u8 *)0x084C88B8, (void *)0x06017E00);
    LoadLeTilemap(0, 0, (const u8 *)0x084F0994, *(volatile u16 *)0x04000008, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F127C, *(volatile u16 *)0x0400000A, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F1D58, *(volatile u16 *)0x0400000C, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F2E1C, *(volatile u16 *)0x0400000E, 0x200);
    CpuFastSet((const void *)0x084F44C0, (void *)0x05000000, 0x70);
    CpuFastSet(gUnknownPalette_0850F358, (void *)0x05000340, 8);
    CpuFastSet(gUnknownPalette_0850F358 + 32, (void *)0x05000360, 8);
    CpuFastSet(gUnknownPalette_0850F358 - 160, (void *)0x05000380, 8);
    CpuFastSet(gUnknownPalette_0850F358 - 128, (void *)0x050003A0, 8);
    CpuFastSet((const void *)0x084E43F8, (void *)0x050003C0, 8);
    {
        u32 fill = 0;
        CpuFastSet(&fill, gFrameObjects, CPU_SET_FILL | 0x800);
    }
    *(volatile u16 *)0x04000000 |= 0x1F60;
    gState0TypedWork.bytes[0x44] = 0;
    gState0TypedWork.bytes[0x46] = 0;
    sub_08009E4C(); sub_08009EF4(); sub_08009F50(); sub_08009F90();
    sub_0800A0FC(); sub_0800A2E8(); sub_0800A594(); sub_0800A854();
    sub_0804253C(5, 63, 32);
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_0800801C(void)
{
    sub_080093F8(); sub_0800A180();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 8);
    if (sub_080425DC()) gUnknown_0300137C++;
}

void sub_08008050(void)
{
    sub_080093F8(); sub_0800A180();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 8);
    sub_0803FAA0(1, 2, 0);
    gUnknown_0300137C++;
}

void sub_08008084(void)
{
    const void *const *messages;
    sub_080093F8(); sub_0800A180();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 8);
    messages = gUnknownPointers_083B7D80;
    if (sub_0803FB3C(messages[sub_0800A960()])) gUnknown_0300137C++;
}

void sub_080080C8(void)
{
    u8 *keys;
    sub_080093F8(); sub_0800A180();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 8);
    if (sub_0800A8A0())
    {
        sub_0803FB0C();
        gUnknown_0300137C++;
    }
    else
    {
        sub_0800A1E4();
        if (sub_0800A928())
        {
            sub_0803FB0C();
            gUnknown_0300137C++;
        }
        else
        {
            keys = (u8 *)&gNewKeys;
            if (keys[0] & 2)
            {
                sub_08074DE0(5);
                gUnknown_0300137C = 30;
            }
            else if (keys[1] & 2)
            {
                sub_08074DE0(2);
                gState0TypedWork.bytes[0x42] = (gState0TypedWork.bytes[0x42] - 1) & 3;
                gUnknown_0300137C = 36;
            }
            else if (keys[1] & 1)
            {
                sub_08074DE0(2);
                gState0TypedWork.bytes[0x42] = (gState0TypedWork.bytes[0x42] + 1) & 3;
                gUnknown_0300137C = 36;
            }
            else if (keys[0] & 8)
            {
                sub_08074DE0(4);
                gState0TypedWork.bytes[0x43] = 1;
                gUnknown_0300137C = 72;
            }
        }
    }
}

void sub_080081BC(void)
{
    const void *const *messages;
    sub_080093F8(); sub_0800A180();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 8);
    messages = gUnknownPointers_083B7D80;
    if (sub_0803FB3C(messages[sub_0800A960()])) gUnknown_0300137C--;
}

void sub_08008200(void)
{
    sub_0804253C(6, 63, 32);
    sub_080093F8(); sub_0800A180();
    sub_08041C14(3, *(u8 *)&gFrameCounter, 8);
    gUnknown_0300137C++;
}


#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_inventory.h"
#include "display_helpers.h"
#include "graphics.h"
#include "compression.h"
#include "frame.h"
#include "main.h"
#include "input.h"

extern const u8 gUnknownPalette_0850F2B8[];
extern const void *const gUnknownPointers_083B83DC[];
void sub_080093F8(void);
void sub_08009E4C(void);
void sub_08009EF4(void);
void sub_08009F50(void);
void sub_08009F90(void);
void sub_0800A0FC(void);
void sub_0800A180(void);
void sub_0800A1E4(void);
void sub_0800AB0C(void);
void sub_0800ABA4(void);
void sub_0800ABF0(void);
void sub_0800AC2C(void);
void sub_0800ACA8(void);
void sub_0800AD00(void);
void sub_0800AED0(void);
void sub_0800AF0C(void);
void sub_0800AF64(void);

void sub_08008234(void)
{
    *(volatile u16 *)0x04000000 &= 0xF0FF;
    *(volatile u16 *)0x04000008 = 0x0500;
    *(volatile u16 *)0x0400000A = 0x1801;
    *(volatile u16 *)0x0400000C = 0x1902;
    *(volatile u16 *)0x0400000E = 0x1A03;
    LeDecompress((const u8 *)0x084EB408, (void *)0x06004000);
    LeDecompress((const u8 *)0x084C3A24, (void *)0x06006280);
    LeDecompress((const u8 *)0x084C3FC0, (void *)0x06006800);
    LeDecompress((const u8 *)0x084C41AC, (void *)0x06006C00);
    LeDecompress((const u8 *)0x084C50D0, (void *)0x06007400);
    LeDecompress((const u8 *)0x084C5250, (void *)0x06007600);
    LeDecompress((const u8 *)0x084C88B8, (void *)0x06017E00);
    LoadLeTilemap(0, 0, (const u8 *)0x084F0A0C, *(volatile u16 *)0x04000008, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F1314, *(volatile u16 *)0x0400000A, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F1E90, *(volatile u16 *)0x0400000C, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F2FB0, *(volatile u16 *)0x0400000E, 0x200);
    CpuFastSet((const void *)0x084F4680, (void *)0x05000000, 0x70);
    CpuFastSet((const void *)0x0850F498, (void *)0x05000200, 0x40);
    CpuFastSet(gUnknownPalette_0850F2B8, (void *)0x05000380, 8);
    CpuFastSet(gUnknownPalette_0850F2B8 + 32, (void *)0x050003A0, 8);
    CpuFastSet((const void *)0x084E43F8, (void *)0x050003C0, 8);
    {
        u32 fill = 0;
        CpuFastSet(&fill, gFrameObjects, CPU_SET_FILL | 0x800);
    }
    *(volatile u16 *)0x04000000 |= 0x1F60;
    gState0TypedWork.bytes[0x44] = 0;
    gState0TypedWork.bytes[0x46] = 0;
    sub_08009E4C(); sub_08009EF4(); sub_08009F50(); sub_08009F90(); sub_0800A0FC();
    sub_0800AB0C(); sub_0800ABA4(); sub_0800AED0(); sub_0800AF0C(); sub_0800AF64();
    sub_0804253C(5, 63, 32);
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_08008430(void)
{
    sub_080093F8(); sub_0800A180();
    if (sub_080425DC()) gUnknown_0300137C++;
}

void sub_08008454(void)
{
    sub_080093F8(); sub_0800A180();
    sub_0803FAA0(1, 2, 0);
    gUnknown_0300137C++;
}

void sub_08008478(void)
{
    sub_080093F8(); sub_0800A180();
    if (sub_0803FB3C(gUnknownPointers_083B5578[12])) gUnknown_0300137C++;
}

void sub_080084A4(void)
{
    u8 *keys;
    sub_080093F8(); sub_0800A180(); sub_0800A1E4(); sub_0800ABF0();
    keys = (u8 *)&gNewKeys;
    if (keys[0] & 1)
    {
        u8 *work;
        sub_08074DE0(4);
        sub_08040D0C(1, 2);
        work = gState0TypedWork.bytes;
        work[0x46] = 0;
        work[0x3F] = 0;
        gUnknown_0300137C = 48;
    }
    else if (keys[0] & 2)
    {
        sub_08074DE0(5);
        gUnknown_0300137C++;
    }
    else if (keys[1] & 2)
    {
        sub_08074DE0(2);
        gState0TypedWork.bytes[0x42] = (gState0TypedWork.bytes[0x42] - 1) & 3;
        gUnknown_0300137C = 52;
    }
    else if (keys[1] & 1)
    {
        sub_08074DE0(2);
        gState0TypedWork.bytes[0x42] = (gState0TypedWork.bytes[0x42] + 1) & 3;
        gUnknown_0300137C = 52;
    }
    else if (keys[0] & 8)
    {
        sub_08074DE0(4);
        gState0TypedWork.bytes[0x43] = 2;
        gUnknown_0300137C = 72;
    }
}

void sub_08008590(void)
{
    sub_0804253C(6, 63, 32);
    sub_080093F8(); sub_0800A180();
    gUnknown_0300137C++;
}

void sub_080085B4(void)
{
    sub_080093F8();
    if (!gState0TypedWork.bytes[0x3F]) sub_0800AC2C();
    else sub_0800ACA8();
    sub_0803FB0C();
    gUnknown_0300137C++;
}

void sub_080085E8(void)
{
    u8 *work;
    const void *message;
    sub_080093F8();
    work = gState0TypedWork.bytes;
    if (!work[0x3F])
    {
        const void *const *messages;
        u8 *records;
        u32 index;
        u8 *field;
        sub_0800AD00();
        messages = gUnknownPointers_083B83DC;
        records = (u8 *)gInventoryRecords;
        field = &work[0x46];
        index = work[0x3D] * 64 + *field;
        records += 24;
        message = messages[records[index]];
    }
    else message = gUnknownPointers_083B5578[15];
    if (sub_0803FB3C(message)) gUnknown_0300137C++;
}


#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_inventory.h"
#include "display_helpers.h"
#include "graphics.h"
#include "compression.h"
#include "frame.h"
#include "main.h"
#include "input.h"

extern const u8 gUnknownPalette_0850F2B8[];
void sub_080093F8(void);
void sub_08009EA0(void);
void sub_08009EF4(void);
void sub_08009F50(void);
void sub_08009FC8(void);
void sub_0800A0FC(void);
void sub_0800A180(void);
void sub_0800A1E4(void);
void sub_0800AA1C(void);
void sub_0800AAC0(void);
void sub_0800AB0C(void);
void sub_0800ABA4(void);
void sub_0800AC2C(void);
void sub_0800ACA8(void);
void sub_0800AD00(void);
u32 sub_0800AD58(void);
u32 sub_0800ADE8(void);
u32 sub_0800AE54(void);
void sub_0800AFF8(void);
void sub_0800B0F8(void);
void sub_0800B130(void);
void sub_0800B174(void);
void sub_0800B468(void);
void sub_0800B5E8(void);

void sub_08008650(void)
{
    u8 *work;
    u8 *page;
    sub_080093F8();
    work = gState0TypedWork.bytes;
    page = &work[0x3F];
    if (!*page)
    {
        u32 accept;
        sub_0800AD00();
        if (sub_0800AD58())
        {
            sub_0800AB0C(); sub_0803FB0C();
            gUnknown_0300137C--;
            return;
        }
        if (sub_0800ADE8())
        {
            sub_0803FB0C(); gUnknown_0300137C--;
            return;
        }
        accept = *(u8 *)&gNewKeys & 1;
        if (accept)
        {
            sub_08074DE0(4); sub_08040D0C(1, 2);
            sub_0800ACA8(); sub_0803FB0C();
            *page = 1;
            gUnknown_0300137C--;
            return;
        }
        if (*(u8 *)&gNewKeys & 2)
        {
            sub_08074DE0(5); sub_08040D0C(1, 2);
            work[0x46] = accept;
            sub_0800A0FC(); sub_0803FB0C();
            gUnknown_0300137C = 43;
            return;
        }
    }
    else
    {
        u32 changed;
        u32 accept;
        sub_08041C5C(3, *(u8 *)&gFrameCounter, 48);
        changed = sub_0800AE54();
        if (changed)
        {
            sub_0800AB0C(); sub_0800ABA4(); sub_0800ACA8();
            return;
        }
        accept = *(u8 *)&gNewKeys & 1;
        if (accept)
        {
            sub_08074DE0(4); sub_08040D0C(3, 1);
            work[0x46] = changed;
            sub_0800A0FC(); sub_0803FB0C();
            gUnknown_0300137C = 43;
            return;
        }
        if (*(u8 *)&gNewKeys & 2)
        {
            sub_08074DE0(5); sub_08040D0C(3, 1);
            sub_0800AC2C(); sub_0803FB0C();
            *page = accept;
            gUnknown_0300137C--;
            return;
        }
    }
    if (*(u8 *)&gNewKeys & 8)
    {
        sub_08074DE0(4);
        gState0TypedWork.bytes[0x46] |= 128;
        gState0TypedWork.bytes[0x43] = 2;
        gUnknown_0300137C = 72;
    }
}

void sub_080087CC(void)
{
    *(volatile u16 *)0x04000000 &= 0xF0FF;
    *(volatile u16 *)0x04000008 = 0x0500;
    *(volatile u16 *)0x0400000A = 0x1801;
    *(volatile u16 *)0x0400000C = 0x1902;
    *(volatile u16 *)0x0400000E = 0x1A03;
    LeDecompress((const u8 *)0x084EC1F8, (void *)0x06004000);
    LeDecompress((const u8 *)0x084C3A24, (void *)0x06007480);
    LeDecompress((const u8 *)0x084C3E64, (void *)0x06007880);
    LeDecompress((const u8 *)0x084C88B8, (void *)0x06017E00);
    LoadLeTilemap(0, 0, (const u8 *)0x084F0A80, *(volatile u16 *)0x04000008, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F13C8, *(volatile u16 *)0x0400000A, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F1FA0, *(volatile u16 *)0x0400000C, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F3140, *(volatile u16 *)0x0400000E, 0x200);
    CpuFastSet((const void *)0x084F4840, (void *)0x05000000, 0x70);
    CpuFastSet(gUnknownPalette_0850F2B8, (void *)0x05000380, 8);
    CpuFastSet(gUnknownPalette_0850F2B8 + 32, (void *)0x050003A0, 8);
    CpuFastSet((const void *)0x084E43F8, (void *)0x050003C0, 8);
    {
        u32 fill = 0;
        CpuFastSet(&fill, gFrameObjects, CPU_SET_FILL | 0x800);
    }
    *(volatile u16 *)0x04000000 |= 0x1F60;
    gState0TypedWork.selection.word48 = 0;
    gState0TypedWork.bytes[0x3F] = 0;
    sub_08009EA0(); sub_08009EF4(); sub_08009F50(); sub_08009FC8(); sub_0800A0FC();
    sub_0800AFF8(); sub_0800B0F8(); sub_0800B174();
    sub_0804253C(5, 63, 32);
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_08008980(void)
{
    sub_080093F8(); sub_0800A180(); sub_0800B130();
    if (sub_080425DC()) gUnknown_0300137C++;
}

void sub_080089A8(void)
{
    u8 *keys;
    sub_080093F8(); sub_0800A180(); sub_0800B130();
    sub_0800A1E4(); sub_0800B468();
    keys = (u8 *)&gNewKeys;
    if (keys[0] & 2)
    {
        sub_08074DE0(5); gUnknown_0300137C++;
    }
    else if (keys[1] & 2)
    {
        sub_08074DE0(2);
        gState0TypedWork.bytes[0x42] = (gState0TypedWork.bytes[0x42] - 1) & 3;
        gUnknown_0300137C = 68;
    }
    else if (keys[1] & 1)
    {
        sub_08074DE0(2);
        gState0TypedWork.bytes[0x42] = (gState0TypedWork.bytes[0x42] + 1) & 3;
        gUnknown_0300137C = 68;
    }
}

void sub_08008A34(void)
{
    sub_0804253C(6, 63, 32);
    sub_080093F8(); sub_0800A180(); sub_0800B130();
    gUnknown_0300137C++;
}

void sub_08008B80(void)
{
    sub_080093F8(); sub_08040D0C(1, 5);
    CpuFastSet((const void *)0x084E4418, (void *)0x050003C0, 8);
    sub_0800AA1C(); sub_0803FB0C();
    gUnknown_0300137C++;
}

void sub_08008BB8(void)
{
    sub_080093F8();
    if (sub_0803FB3C(gUnknownPointers_083B5578[5])) gUnknown_0300137C++;
}

void sub_08008BE0(void)
{
    u32 up;
    sub_080093F8();
    sub_08040BD8(gUnknownPointers_083B6100[3], 6);
    up = (u8)(*(u8 *)&gRepeatedKeys & 64);
    if (up)
    {
        u8 *work = gState0TypedWork.bytes;
        if (!work[0x44]) work[0x44] = work[0x45] - 1;
        else work[0x44]--;
        sub_08074DE0(2); sub_0800AAC0();
    }
    else if (*(u8 *)&gRepeatedKeys & 128)
    {
        u8 *work = gState0TypedWork.bytes;
        if (work[0x44] == work[0x45] - 1) work[0x44] = up;
        else work[0x44]++;
        sub_08074DE0(2); sub_0800AAC0();
    }
    else if (*(u8 *)&gNewKeys & 1)
    {
        sub_08074DE0(4); sub_0800AA1C(); sub_0803FB0C();
        gUnknown_0300137C++;
    }
    else if (*(u8 *)&gNewKeys & 10)
    {
        sub_08074DE0(5); gUnknown_0300137C = 78;
    }
}


#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_inventory.h"
#include "display_helpers.h"
#include "graphics.h"
#include "frame.h"
#include "main.h"
#include "input.h"

void sub_080093F8(void);
void sub_08009AF8(void);
void sub_0800A0FC(void);
void sub_0800A854(void);
void sub_0800AFF8(void);
void sub_0800B174(void);
void sub_0800B5E8(void);
void sub_0800B668(void);
void sub_0800B6E8(void);
u32 sub_0800B768(void);
void sub_08044CDC(u32 mode);
extern u32 gUnknownMask_03002B68;
extern const void *const gUnknownPointers_083CF530[];

void sub_08008A5C(void)
{
    u32 up;
    sub_0800B5E8();
    up = (u8)(*(u8 *)&gRepeatedKeys & 64);
    if (up)
    {
        if (!gState0TypedWork.selection.word48) gState0TypedWork.selection.word48 = 7;
        else gState0TypedWork.selection.word48--;
        return;
    }
    if (*(u8 *)&gRepeatedKeys & 128)
    {
        if (gState0TypedWork.selection.word48 == 7) gState0TypedWork.selection.word48 = up;
        else gState0TypedWork.selection.word48++;
        return;
    }
    if (*(u8 *)&gRepeatedKeys & 16)
    {
        u8 *records = (u8 *)gInventoryRecords;
        u8 *work = gState0TypedWork.bytes;
        u16 *field = (u16 *)&work[0x48];
        u32 index = work[0x3D] * 64 + *field;
        u8 *value;
        records += 32;
        value = &records[index];
        if (*value != 100)
        {
            (*value)++; sub_0800AFF8();
            return;
        }
    }
    if (*(u8 *)&gRepeatedKeys & 32)
    {
        u8 *records = (u8 *)gInventoryRecords;
        u8 *work = gState0TypedWork.bytes;
        u16 *field = (u16 *)&work[0x48];
        u32 index = work[0x3D] * 64 + *field;
        u8 *value;
        records += 32;
        value = &records[index];
        if (*value)
        {
            (*value)--; sub_0800AFF8();
            return;
        }
    }
    if (*(u8 *)&gNewKeys & 4)
    {
        u8 *records = (u8 *)gInventoryRecords;
        u8 *work = gState0TypedWork.bytes;
        u16 *field = (u16 *)&work[0x48];
        u32 index = work[0x3D] * 64 + *field;
        records += 40;
        records[index] = 7;
        sub_0800B174();
    }
    else if (*(u8 *)&gNewKeys & 2)
    {
        sub_08040CD0(127, 1); gUnknown_0300137C = 58;
    }
}

void sub_080090D0(void)
{
    sub_080093F8(); sub_08040D0C(6, 1);
    CpuFastSet((const void *)0x084E43F8, (void *)0x050003C0, 8);
    switch (gState0TypedWork.bytes[0x42])
    {
    case 0:
        sub_0803FB0C(); sub_0800A0FC(); gUnknown_0300137C = 11;
        break;
    case 1:
        sub_0803FB0C(); sub_0800A0FC(); sub_0800A854(); gUnknown_0300137C = 27;
        break;
    case 2:
        if (gState0TypedWork.bytes[0x46] & 128)
        {
            gState0TypedWork.bytes[0x46] &= 127;
            gUnknown_0300137C = 48;
        }
        else
        {
            sub_0803FB0C(); sub_0800A0FC(); gUnknown_0300137C = 43;
        }
        break;
    }
}

void sub_08009174(void)
{
    sub_080093F8(); sub_08009AF8();
    gFrameObjects[1].flags &= 0xBFFF;
    gFrameObjects[2].flags &= 0xBFFF;
    LoadLeTilemap(18, 12, (const u8 *)0x08488494, *(volatile u16 *)0x04000008, 0x350);
    gState0TypedWork.bytes[0x4A] = 0;
    sub_0800B668(); gUnknown_0300137C++;
}

void sub_080091E0(void)
{
    sub_080093F8(); sub_08009AF8();
    sub_08041C14(7, *(u8 *)&gFrameCounter, 168);
    sub_0800B6E8();
    if (*(u8 *)&gNewKeys & 1)
    {
        sub_08074DE0(4);
        sub_0800B668(); gUnknown_0300137C++;
    }
    else if (*(u8 *)&gNewKeys & 2)
    {
        sub_08074DE0(5);
        gState0TypedWork.bytes[0x4A] = 2;
        sub_0800B668(); gUnknown_0300137C++;
    }
}

void sub_08009248(void)
{
    sub_080093F8(); sub_08009AF8();
    if (sub_0800B768())
    {
        sub_08040D0C(7, 1); gUnknown_0300137C++;
    }
}

void sub_08009274(void)
{
    sub_080093F8(); sub_08009AF8();
    switch (gState0TypedWork.bytes[0x4A])
    {
    case 0:
        gState0TypedWork.bytes[0x42] = 0;
        sub_0804253C(6, 63, 32); gUnknown_0300137C = 7;
        break;
    case 1: gUnknown_0300137C++; break;
    case 2: gUnknown_0300137C = 2; break;
    }
}

void sub_080092D4(void)
{
    u8 *work;
    struct InventoryRecord *records;
    struct InventoryRecord *record;
    u32 selected;
    sub_080093F8(); sub_08009AF8();
    records = gInventoryRecords;
    work = gState0TypedWork.bytes;
    record = &records[work[0x3D]];
    if (record->byte0 & 64)
    {
        sub_0803FAA0(1, 2, 0);
        work[0x84] = 9;
        gUnknown_0300137C++;
    }
    else
    {
        selected = (1U << record->byte1) & gUnknownMask_03002B68;
        if (selected)
        {
            sub_0803FAA0(1, 2, 0);
            work[0x84] = 8;
            gUnknown_0300137C++;
        }
        else
        {
            sub_08040CD0(5, 1); sub_080750F0(8);
            work[0x3E] = selected;
            gUnknown_0300137C = 104;
        }
    }
}

void sub_08009374(void)
{
    const void *const *messages;
    sub_080093F8(); sub_08009AF8();
    messages = gUnknownPointers_083CF530;
    if (sub_0803FB3C(messages[gState0TypedWork.bytes[0x84]])) gUnknown_0300137C = 2;
}

void sub_080093AC(void)
{
    sub_0803F63C(&gInventoryRecords[gState0TypedWork.bytes[0x3D]], gObjectSortEntries, 64);
    gUnknown_0300137C++;
}

void sub_080093E0(void)
{
    sub_08040CD0(0, 128); sub_08043CA8(); sub_08044CDC(1);
}
