#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_callbacks.h"
#include "bg_scroll.h"
#include "main.h"
#include "input.h"
#include "tile_text.h"

extern const void *const gState0NextText_083B4C60[];
struct KeyBytes { u8 low; u8 high; };

void sub_0800EBFC(void)
{
    if (gFrameCounter & 1)
    {
        gBgScroll3.x++;
        gBgScroll3.y++;
    }
}

void sub_0800EC20(void)
{
    gState0TypedWork.bytes[0x3F] = gState0TypedWork.bytes[0x3D] / 4;
    gState0TypedWork.bytes[0x40] = gState0TypedWork.bytes[0x3D] % 4;
}

void sub_0800EEE4(void)
{
    gFrameObjects[1].flags = 0xC804;
    gFrameObjects[1].screenX = 76;
    gFrameObjects[1].screenY = 24;
    gFrameObjects[1].frameAndGroup = 0x302;
    gFrameObjects[1].palette = 14;
    gFrameObjects[1].tableSelector = 0;
    gFrameObjects[1].priority = 128;
    gFrameObjects[2].flags = 0xC804;
    gFrameObjects[2].screenX = 140;
    gFrameObjects[2].screenY = 24;
    gFrameObjects[2].frameAndGroup = 0x303;
    gFrameObjects[2].palette = 14;
    gFrameObjects[2].tableSelector = 0;
    gFrameObjects[2].priority = 128;
}

void sub_0800EF58(void)
{
    if (gFrameCounter & 8)
    {
        gFrameObjects[1].flags &= 0xBFFF;
        gFrameObjects[2].flags &= 0xBFFF;
    }
    else
    {
        gFrameObjects[1].flags |= 0x4000;
        gFrameObjects[2].flags |= 0x4000;
    }
}

void sub_0800EFB0(void)
{
    gFrameObjects[3].flags = 0xC804;
    gFrameObjects[3].screenX = 80;
    gFrameObjects[3].screenY = gState0TypedWork.bytes[0x40] * 16 + 48;
    gFrameObjects[3].frameAndGroup = 0x307;
    gFrameObjects[3].palette = 14;
    gFrameObjects[3].tableSelector = 0;
    gFrameObjects[3].priority = 129;
}

u32 sub_0800EFFC(void)
{
    if (*(u8 *)&gRepeatedKeys & 64)
    {
        if (!gState0TypedWork.bytes[0x40]) gState0TypedWork.bytes[0x40] = 3;
        else gState0TypedWork.bytes[0x40]--;
    }
    if (*(u8 *)&gRepeatedKeys & 128)
    {
        if (gState0TypedWork.bytes[0x40] == 3) gState0TypedWork.bytes[0x40] = 0;
        else gState0TypedWork.bytes[0x40]++;
    }
    if (*(u8 *)&gRepeatedKeys & 192)
    {
        sub_08074DE0(2);
        gState0TypedWork.bytes[0x3D] = gState0TypedWork.bytes[0x3F] * 4 + gState0TypedWork.bytes[0x40];
        sub_0800EFB0();
        sub_0800F300();
        return 1;
    }
    return 0;
}

u32 sub_0800F08C(void)
{
    if (*(u8 *)&gRepeatedKeys & 32)
    {
        if (!gState0TypedWork.bytes[0x3F]) gState0TypedWork.bytes[0x3F] = 29;
        else gState0TypedWork.bytes[0x3F]--;
    }
    if (*(u8 *)&gRepeatedKeys & 16)
    {
        if (gState0TypedWork.bytes[0x3F] == 29) gState0TypedWork.bytes[0x3F] = 0;
        else gState0TypedWork.bytes[0x3F]++;
    }
    if (*(u8 *)&gRepeatedKeys & 48)
    {
        sub_08074DE0(2);
        gState0TypedWork.bytes[0x3D] = gState0TypedWork.bytes[0x3F] * 4 + gState0TypedWork.bytes[0x40];
        sub_08042950(gState0TypedWork.bytes[0x3F] + 1, 11, 2, 2, *(volatile u16 *)0x0400000A, 0x7360);
        sub_0800EC44();
        sub_0800ED10();
        sub_0800EDA0();
        sub_0800EE34();
        sub_0800F300();
        return 1;
    }
    return 0;
}

u32 sub_0800F148(void)
{
    if (((struct KeyBytes *)&gNewKeys)->high & 2)
    {
        if (!gState0TypedWork.bytes[0x3E]) gState0TypedWork.bytes[0x3E] = 3;
        else gState0TypedWork.bytes[0x3E]--;
    }
    if (((struct KeyBytes *)&gNewKeys)->high & 1)
    {
        if (gState0TypedWork.bytes[0x3E] == 3) gState0TypedWork.bytes[0x3E] = 0;
        else gState0TypedWork.bytes[0x3E]++;
    }
    if (((struct KeyBytes *)&gNewKeys)->high & 3)
    {
        sub_08074DE0(2);
        gState0TypedWork.bytes[0x3D] = gState0TypedWork.bytes[0x3F] * 4 + gState0TypedWork.bytes[0x40];
        sub_0803F15C(10, 2, 16, 0, gState0NextText_083B4C60[gState0TypedWork.bytes[0x3E] + 89], *(volatile u16 *)0x04000008, 512);
        sub_0800EC44();
        sub_0800ED10();
        sub_0800EDA0();
        sub_0800EE34();
        sub_0800F300();
        return 1;
    }
    return 0;
}
