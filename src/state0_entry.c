#include "state0_callbacks.h"
#include "render_work.h"

extern u32 sub_0803EED8(void);
extern const MainCallback gUnknownCallbacks_083AC4A0[];

void sub_080039E0(void)
{
    if (!sub_0803EED8())
    {
        if (gRenderMode == 2)
        {
            u32 fill = 0x200;
            CpuFastSet(&fill, gRenderWork->objects, CPU_SET_FILL | 0x100);
        }
        gUnknownCallbacks_083AC4A0[gUnknown_0300137C]();
    }
}


#include "state0_callbacks.h"
#include "compression.h"
#include "graphics.h"
#include "frame.h"

extern void sub_08043CA8(void);
extern void sub_080054C0(void);
extern void sub_08004FD0(void);
extern void sub_08005000(void);
extern void sub_08004E98(void);
extern void sub_0800508C(void);
extern void sub_08005118(void);
extern void sub_0800519C(void);
extern void sub_0800522C(void);
extern void sub_08005948(void);
extern void sub_0800750C(void);
extern void sub_0800529C(void);
extern void sub_08005628(void);
extern const u8 gUnknownPalette_0850F2B8[];

void sub_08003A38(void)
{
    switch (gUnknown_03000440[0x139])
    {
    case 0:
        sub_08043CA8();
        if (gUnknown_03000440[0x56] == 1)
            sub_080054C0();
        *(volatile u16 *)0x04000000 &= 0xF0FF;
        *(volatile u16 *)0x04000008 = 0x0500;
        *(volatile u16 *)0x0400000A = 0x1801;
        *(volatile u16 *)0x0400000C = 0x1902;
        *(volatile u16 *)0x0400000E = 0x1A03;
        LeDecompress((const u8 *)0x084E6BF0, (void *)0x06004000);
        LeDecompress((const u8 *)0x084C50D0, (void *)0x06006000);
        LeDecompress((const u8 *)0x084C5250, (void *)0x06006200);
        LeDecompress((const u8 *)0x084C89C8, (void *)0x06016C00);
        LeDecompress((const u8 *)0x084C8034, (void *)0x06017400);
        gUnknown_03000440[0x139]++;
        break;
    case 1:
        if (gUnknown_03000440[0x56] == 1)
            sub_080054C0();
        LoadLeTilemap(0, 0, (const u8 *)0x084F0878, *(volatile u16 *)0x04000008, 0x200);
        LoadLeTilemap(0, 0, (const u8 *)0x084F0EFC, *(volatile u16 *)0x0400000A, 0x200);
        LoadLeTilemap(0, 0, (const u8 *)0x084F1858, *(volatile u16 *)0x0400000C, 0x200);
        LoadLeTilemap(0, 0, (const u8 *)0x084F27CC, *(volatile u16 *)0x0400000E, 0x200);
        if (gUnknown_03000440[0x56] == 1)
        {
            CpuFastSet((const void *)0x084F3C20, (void *)0x0202FA00, 0x60);
            CpuFastSet((const void *)0x0850F498, (void *)0x0202F800, 0x40);
            CpuFastSet(gUnknownPalette_0850F2B8, (void *)0x0202F9A0, 8);
            CpuFastSet(gUnknownPalette_0850F2B8 + 32, (void *)0x0202F9C0, 8);
            CpuFastSet((const void *)0x084E4458, (void *)0x0202F980, 8);
            CpuFastSet((const void *)0x084E4478, (void *)0x0202F9E0, 8);
            gUnknown_03000440[0x84] = 0;
        }
        else
        {
            CpuFastSet((const void *)0x084F3C20, (void *)0x05000000, 0x60);
            CpuFastSet((const void *)0x0850F498, (void *)0x05000200, 0x40);
            CpuFastSet(gUnknownPalette_0850F2B8, (void *)0x050003A0, 8);
            CpuFastSet(gUnknownPalette_0850F2B8 + 32, (void *)0x050003C0, 8);
            CpuFastSet((const void *)0x084E4458, (void *)0x05000380, 8);
            CpuFastSet((const void *)0x084E4478, (void *)0x050003E0, 8);
            sub_0804253C(5, 63, 32);
        }
        {
            u32 fill = 0;
            CpuFastSet(&fill, gFrameObjects, CPU_SET_FILL | 0x800);
        }
        *(volatile u16 *)0x04000000 |= 0x1F40;
        *(volatile u16 *)0x04000000 &= 0xFFDF;
        gUnknown_03000440[0x139]++;
        break;
    case 2:
        if (gUnknown_03000440[0x56] == 1)
            sub_080054C0();
        gUnknown_03000440[0x96] = 1;
        sub_08004FD0();
        sub_08005000();
        sub_08004E98();
        sub_0800508C();
        sub_08005118();
        sub_0800519C();
        sub_0800522C();
        sub_08005948();
        sub_0800750C();
        if (gUnknown_03000440[0x56] == 0)
        {
            sub_0800529C();
            if (gUnknown_03000440[0x50] == 3)
                sub_08074B88(7);
        }
        else if (gUnknown_03000440[0x52] & 0x80)
            sub_08005628();
        gUnknown_0300137C++;
        gUnknown_03000440[0x139] = 0;
        break;
    }
}


#include "state0_callbacks.h"
#include "input.h"
#include "graphics.h"
#include "render_work.h"

extern void sub_08004E74(void);
extern void sub_08004EF8(u32);
extern void sub_080054C0(void);
extern void sub_08005798(void);
extern void sub_0800598C(void);
extern void sub_0800712C(void);
extern u32 sub_080058A4(void);
extern u32 sub_08005588(void);
extern void sub_0800725C(void);
extern void sub_080072EC(void);
extern void sub_08007408(void);

/* Repeated observed calls, expanded inline to preserve the original sequence. */
#define ENTRY_FRAME_WORK(extra) do { \
    sub_08004E74(); \
    sub_08004EF8(0); \
    sub_08004EF8(1); \
    sub_08004EF8(2); \
    sub_08004EF8(3); \
    sub_080054C0(); \
    extra; \
    sub_0800598C(); \
} while (0)

void sub_08003D4C(void)
{
    ENTRY_FRAME_WORK(sub_08005798());
    if (gUnknown_03000440[0x56] == 1)
    {
        if (gUnknown_03000440[0x84] <= 8)
        {
            sub_0803F684(0, 32 - gUnknown_03000440[0x84] * 4, 0xFFFF);
            sub_0803F998(0, 32 - gUnknown_03000440[0x84] * 4, 0xF0FF);
            gUnknown_03000440[0x84]++;
        }
        else
        {
            gUnknown_03000440[0x56] = 0;
            gUnknown_0300137C++;
        }
    }
    else if (sub_080425DC())
    {
        gUnknown_03000440[0x56] = 0;
        gUnknown_0300137C++;
    }
}

void sub_08003DE0(void)
{
    ENTRY_FRAME_WORK(sub_08005798());
    sub_0800712C();
    if (!sub_080058A4() && !sub_08005588())
    {
        const u8 *pressed = (const u8 *)&gNewKeys;
        if (*pressed & KEY_B)
            sub_0800725C();
        else if (*pressed & KEY_A)
            sub_080072EC();
        else if (*pressed & KEY_START)
            sub_08007408();
    }
}

void sub_08003E54(void)
{
    ENTRY_FRAME_WORK((void)0);
    sub_0804253C(6, 63, 32);
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_08003EA0(void)
{
    ENTRY_FRAME_WORK((void)0);
    if (sub_080425DC())
        gUnknown_0300137C++;
}

void sub_08003EE0(void)
{
    CpuFastSet((const void *)0x084E43D8, (void *)0x050003E0, 8);
    sub_08040CD0(0, 128);
    gUnknown_03000440[0x96] = 0;
    gRenderMode = 0;
    gMainSubstate = 2;
    gUnknown_0300137C = 16;
}

void sub_08003F28(void)
{
    ENTRY_FRAME_WORK(sub_08005798());
    SnapshotPalettes();
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}

void sub_08003F74(void)
{
    ENTRY_FRAME_WORK(sub_08005798());
    if (gUnknown_03000440[0x84] <= 8)
    {
        sub_0803F684(0, gUnknown_03000440[0x84] * 4, 0xFFFF);
        sub_0803F998(0, gUnknown_03000440[0x84] * 4, 0xF0FF);
        gUnknown_03000440[0x84]++;
    }
    else
        gUnknown_0300137C = 16;
}

void sub_08003FE8(void)
{
    ENTRY_FRAME_WORK((void)0);
    sub_0803FAA0(1, 2, 0);
    gUnknown_0300137C++;
}

void sub_08004028(void)
{
    ENTRY_FRAME_WORK((void)0);
    if (sub_0803FB3C(gUnknownPointers_083B5578[22]))
        gUnknown_0300137C = 2;
}


#include "state0_callbacks.h"
#include "compression.h"
#include "graphics.h"
#include "frame.h"

extern const u8 gUnknownPalette_0850F2B8[];
extern void sub_080054C0(void);
extern void sub_080059D0(void);
extern void sub_08006238(u32);
extern void sub_08006284(u32);
extern void sub_080062D0(u32);
extern void sub_0800631C(u32);
extern void sub_08006368(u32);
extern void sub_08005AD0(void);
extern void sub_08005B44(void);
extern void sub_08005C10(void);
extern void sub_08005BB4(void);
extern void sub_08005C9C(void);
extern void sub_08005D1C(void);
extern void sub_08005E00(void);
extern void sub_08005E84(void);
extern void sub_08005F68(void);
extern void sub_08005FEC(void);
extern void sub_080060D0(void);
extern void sub_08006154(void);
extern void sub_080063B4(void);
extern void sub_08006414(void);
extern void sub_08006494(void);
extern void sub_0800656C(void);
extern void sub_08042E58(u32, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32);

void sub_0800406C(void)
{
    if (gUnknown_03000440[0x56] == 0)
        sub_080054C0();
    *(volatile u16 *)0x04000000 &= 0xF0FF;
    *(volatile u16 *)0x04000008 = 0x0500;
    *(volatile u16 *)0x0400000A = 0x1801;
    *(volatile u16 *)0x0400000C = 0x1902;
    *(volatile u16 *)0x0400000E = 0x1A03;
    LeDecompress((const u8 *)0x084E776C, (void *)0x06004000);
    LeDecompress((const u8 *)0x084C50D0, (void *)0x06006000);
    LeDecompress((const u8 *)0x084C5250, (void *)0x06006200);
    LeDecompress((const u8 *)0x084C3A24, (void *)0x06007480);
    LeDecompress((const u8 *)0x084C3BF8, (void *)0x06006800);
    LeDecompress((const u8 *)0x084C55CC, (void *)0x06006E00);
    LeDecompress((const u8 *)0x084C88B8, (void *)0x06017E00);
    LeDecompress((const u8 *)0x084C8034, (void *)0x06017400);
    LoadLeTilemap(0, 0, (const u8 *)0x084F08B0, *(volatile u16 *)0x04000008, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F0F68, *(volatile u16 *)0x0400000A, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F198C, *(volatile u16 *)0x0400000C, 0x200);
    LoadLeTilemap(0, 0, (const u8 *)0x084F2960, *(volatile u16 *)0x0400000E, 0x200);
    if (gUnknown_03000440[0x56] == 0)
    {
        CpuFastSet((const void *)0x084F3DC0, (void *)0x0202FA00, 0x70);
        CpuFastSet((const void *)0x0850F498, (void *)0x0202F800, 0x40);
        CpuFastSet(gUnknownPalette_0850F2B8 + 64, (void *)0x0202F980, 8);
        CpuFastSet(gUnknownPalette_0850F2B8 + 128, (void *)0x0202F9A0, 8);
        CpuFastSet(gUnknownPalette_0850F2B8, (void *)0x0202F9E0, 8);
        CpuFastSet((const void *)0x084E43F8, (void *)0x0202F9C0, 8);
        gUnknown_03000440[0x5A] = 0;
        sub_080059D0();
        gUnknown_03000440[0x84] = 0;
    }
    else
    {
        CpuFastSet((const void *)0x084F3DC0, (void *)0x05000000, 0x70);
        CpuFastSet((const void *)0x0850F498, (void *)0x05000200, 0x40);
        CpuFastSet(gUnknownPalette_0850F2B8 + 64, (void *)0x05000380, 8);
        CpuFastSet(gUnknownPalette_0850F2B8 + 128, (void *)0x050003A0, 8);
        CpuFastSet(gUnknownPalette_0850F2B8, (void *)0x050003E0, 8);
        CpuFastSet((const void *)0x084E43F8, (void *)0x050003C0, 8);
        sub_0804253C(5, 63, 32);
    }
    {
        u32 fill = 0;
        CpuFastSet(&fill, gFrameObjects, CPU_SET_FILL | 0x800);
    }
    *(volatile u16 *)0x04000000 |= 0x1F40;
    *(volatile u16 *)0x04000000 &= 0xFFDF;
    gUnknown_03000440[0x53] = 0;
    gUnknown_03000440[0x96] = 1;
    sub_08006238(0);
    sub_08006284(0);
    sub_080062D0(0);
    sub_0800631C(0);
    sub_08006368(0);
    sub_08005AD0();
    sub_08005B44();
    sub_08005C10();
    sub_08005BB4();
    sub_08005C9C();
    sub_08005D1C();
    sub_08005E00();
    sub_08005E84();
    sub_08005F68();
    sub_08005FEC();
    sub_080060D0();
    sub_08006154();
    sub_080063B4();
    sub_08006414();
    sub_08042E58(gUnknown_03000440[0x98], gUnknown_03000440[0x99], gUnknown_03000440[0x9A], gUnknown_03000440[0x9B],
        0, 6, 168, 32, gUnknown_03000440[0x5E], 1, 5);
    sub_08006494();
    if (gUnknown_03000440[0x56] != 0)
        sub_0800656C();
    gUnknown_03000440[0x84] = 0;
    gUnknown_0300137C++;
}


#include "state0_callbacks.h"
#include "graphics.h"
#include "input.h"
#include "render_work.h"

extern void sub_08004E74(void);
extern void sub_08006764(void);
extern void sub_08006514(void);
extern void sub_08006824(void);
extern void sub_08006E44(void);
extern void sub_08006F14(void);
extern u32 sub_080068EC(void);
extern u32 sub_08006980(void);
extern u32 sub_08006A00(void);
extern u32 sub_08006A98(void);
extern u32 sub_08006B30(void);
extern u32 sub_08006BC8(void);
extern u32 sub_08006C64(void);
extern void sub_0800667C(void);
extern void sub_08006444(void);
extern u32 sub_08006F34(void);
extern void sub_08006FB0(void);
extern void sub_080070F0(void);
extern u8 gUnknown_0300047C[];

#define DESTINATION_FRAME_WORK() do { \
    sub_08004E74(); \
    sub_08006764(); \
    sub_08006514(); \
    sub_08006824(); \
    sub_08006E44(); \
    sub_08006F14(); \
} while (0)

void sub_080043A8(void)
{
    DESTINATION_FRAME_WORK();
    if (gUnknown_03000440[0x56] == 0)
    {
        if (gUnknown_03000440[0x84] <= 8)
        {
            sub_0803F684(0, 32 - gUnknown_03000440[0x84] * 4, 0xFFFF);
            sub_0803F998(0, 32 - gUnknown_03000440[0x84] * 4, 0xF0FF);
            gUnknown_03000440[0x84]++;
        }
        else
        {
            gUnknown_03000440[0x56] = 1;
            gUnknown_0300137C++;
        }
    }
    else if (sub_080425DC())
    {
        gUnknown_03000440[0x56] = 1;
        gUnknown_0300137C++;
    }
}

void sub_0800442C(void)
{
    DESTINATION_FRAME_WORK();
    if (!sub_080068EC() && !sub_08006980() && !sub_08006A00()
        && !sub_08006A98() && !sub_08006B30() && !sub_08006BC8() && !sub_08006C64())
    {
        const u8 *pressed = (const u8 *)&gNewKeys;
        if (*pressed & KEY_B)
        {
            sub_08074DE0(5);
            gUnknown_0300137C++;
        }
        else if (pressed[1] & 3)
        {
            sub_08074DE0(2);
            gUnknown_03000440[0x5E] ^= 1;
            sub_0800667C();
            sub_08006444();
        }
        else
        {
            u8 choice = sub_08006F34();
            if (choice == 2)
                sub_08074DE0(6);
            else if (choice == 1)
            {
                sub_08074DE0(4);
                gUnknown_0300137C = 24;
            }
        }
    }
}

void sub_080044F8(void)
{
    DESTINATION_FRAME_WORK();
    if (gUnknown_03000440[0x50] == 0)
    {
        SnapshotPalettes();
        gUnknown_03000440[0x84] = 0;
    }
    else
        sub_0804253C(6, 63, 32);
    gUnknown_0300137C++;
}

void sub_0800454C(void)
{
    DESTINATION_FRAME_WORK();
    if (gUnknown_03000440[0x50] == 0)
    {
        if (gUnknown_03000440[0x84] <= 8)
        {
            sub_0803F684(0, gUnknown_03000440[0x84] * 4, 0xFFFF);
            sub_0803F998(0, gUnknown_03000440[0x84] * 4, 0xF0FF);
            gUnknown_03000440[0x84]++;
        }
        else
            gUnknown_0300137C++;
    }
    else if (sub_080425DC())
        gUnknown_0300137C++;
}

void sub_080045C4(void)
{
    sub_08006764();
    sub_08006FB0();
    gUnknown_0300137C = 0;
}

void sub_080045DC(void)
{
    DESTINATION_FRAME_WORK();
    sub_0804253C(6, 63, 32);
    gUnknown_0300137C++;
}

void sub_08004610(void)
{
    DESTINATION_FRAME_WORK();
    if (sub_080425DC())
        gUnknown_0300137C++;
}

void sub_08004644(void)
{
    sub_08040CD0(0, 128);
    gUnknown_03000440[0x96] = 0;
    gRenderMode = 0;
    switch (gUnknown_03000440[0x5A])
    {
    case 0:
        sub_0803F624(gUnknown_0300047C, 20, 0);
        gUnknown_0300047C[0] = 1;
        gUnknown_0300047C[1] = gUnknown_0300047C[0x5B];
        sub_080070F0();
        gMainSubstate = 4;
        gUnknown_0300137C = 8;
        break;
    case 1:
        sub_0803F624(gUnknown_0300047C, 20, 0);
        gUnknown_0300047C[0] = 1;
        gUnknown_0300047C[1] = gUnknown_0300047C[0x5C];
        gUnknown_0300047C[2] = 0;
        gMainSubstate = 5;
        gUnknown_0300137C = 16;
        break;
    case 2:
        sub_0803F624(gUnknown_0300047C, 20, 0);
        gUnknown_0300047C[0] = 1;
        gUnknown_0300047C[1] = gUnknown_0300047C[0x5D];
        gUnknown_0300047C[2] = 1;
        gMainSubstate = 5;
        gUnknown_0300137C = 16;
        break;
    case 3:
        sub_0803F624(gUnknown_0300047C, 20, 0);
        gUnknown_0300047C[0] = 1;
        gUnknown_0300047C[1] = gUnknown_0300047C[0x5E];
        gUnknown_0300047C[2] = 2;
        gMainSubstate = 5;
        gUnknown_0300137C = 16;
        break;
    case 4:
        sub_0803F624(gUnknown_0300047C, 20, 0);
        gUnknown_0300047C[0] = 1;
        gUnknown_0300047C[1] = gUnknown_0300047C[0x5F];
        gUnknown_0300047C[2] = 3;
        gMainSubstate = 5;
        gUnknown_0300137C = 16;
        break;
    }
}
