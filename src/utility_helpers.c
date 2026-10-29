

#include "utility_helpers.h"
#include "main.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "display_helpers.h"
#include "compression.h"
#include "object_helpers.h"

#include "action_scene_data.h"
extern const u8 gUnknownBytes_083B2AF0[];
extern u8 gUnknown_030057E0[];
extern u8 gUnknown_03000BE0[];
void sub_08043E78(void);
void sub_08043FEC(u32);

void sub_08044094(void)
{
    gMainState = 1;
    gMainSubstate = 1;
    gUnknown_0300137C = 7;
}

u32 sub_080440B4(void)
{
    u32 count = 0;
    u32 i;
    for (i = 0; i < 9; i++)
        if (gUnknownRecords_030017A0[i].unknown00[0] == 3)
            count++;
    return count;
}

u32 sub_080440D4(void)
{
    u32 i;
    for (i = 0; i < 480; i++)
        if (gObjectHalfwordBytes[i * 2] != gObjectHalfwordBytes[i * 2 + 1])
            return 0;
    return 1;
}

void sub_08044100(void)
{
    sub_08043E78();
    sub_08043FEC(gState0TransferWork.bytes[0x38]);
}

void sub_08044118(u32 width, u32 height, u32 x, u32 y, u32 control, u16 *destination)
{
    u32 screenOffset = ((control >> 8) & 31) << 11;
    u32 xAddress = x * 2 + 0x06000000;
    const u16 *source = (const u16 *)(screenOffset + xAddress + y * 64);
    u32 row, column;
    for (row = 0; row < height; row++)
    {
        const u16 *in = source + row * 32;
        for (column = 0; column < width; column++)
            *destination++ = *in++;
    }
}

void sub_08044160(u32 width, u32 height, u32 x, u32 y, u32 control, const u16 *source)
{
    u32 screenOffset = ((control >> 8) & 31) << 11;
    u32 xAddress = x * 2 + 0x06000000;
    u16 *destination = (u16 *)(screenOffset + xAddress + y * 64);
    u32 row, column;
    for (row = 0; row < height; row++)
    {
        u16 *out = destination + row * 32;
        for (column = 0; column < width; column++)
            *out++ = *source++;
    }
}

void sub_080441A8(const void *source)
{
    LeDecompress(source, (void *)0x02027000);
}

void sub_08044B28(const void *source, void *destination)
{
    LeDecompress(source, destination);
}

u32 sub_08044B34(u32 input)
{
    u8 value = input;
    if (value == 0)
        return gUnknownBytes_083B2AF0[gUnknown_030057E0[0xC5C]];
    return value;
}

void sub_08044B58(void)
{
    gUnknown_03000BE0[0] |= 0xC0;
    gUnknownRecords_030017A0[0].unknown00[0] = 3;
    gUnknownRecords_030017A0[0].unknown00[2] = 1;
    gUnknownRecords_030017A0[0].byte3 = 0x2B;
    gUnknownRecords_030017A0[0].byte4 = 0x2B;
    gUnknownRecords_030017A0[0].byte5 = 0x2B;
    gUnknownRecords_030017A0[0].byte6 = 0x2B;
    gObjectHalfwordBytes[0x57] = 1;
    gObjectHalfwordBytes[0x147] = 1;
    gObjectHalfwordBytes[0x237] = 1;
    gObjectHalfwordBytes[0x327] = 1;
}


#include "utility_helpers.h"
#include "main.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "display_helpers.h"
#include "compression.h"
#include "object_helpers.h"

extern const u8 gUnknownBytes_083B2AF0[];
extern u8 gUnknown_030057E0[];
extern u8 gUnknown_03000BE0[];
void sub_08043E78(void);
void sub_08043FEC(u32);

void sub_0804422C(u32 objectIndex)
{
    struct FrameObject *base = gFrameObjects;
    struct FrameObject *object = &base[objectIndex];
    u32 xMask = 0x1FF;
    if (object->unknown23[1] != 0)
    {
        object->screenY = (object->screenY + gUnknownWords_083C6F78[((object->unknown23[1] - 1) << 8) + (object->unknown23[2] << 3) + ((object->unknown23[4] & 3) << 1)]) & 0xFF;
        object->screenX = (object->screenX + gUnknownWords_083C6F78[((object->unknown23[1] - 1) << 8) + (object->unknown23[2] << 3) + ((object->unknown23[4] & 3) << 1) + 1]) & xMask;
        object->unknown23[4]++;
    }
}

u32 sub_080442B4(s32 x1, s32 y1, s32 x2, s32 y2)
{
    u32 xSign, ySign;
    float dx, dy;
    s32 count;
    if (x1 <= x2)
    {
        xSign = 0;
        dx = x2 - x1;
    }
    else
    {
        xSign = 1;
        dx = x1 - x2;
    }
    if (y1 <= y2)
    {
        ySign = 0;
        dy = y2 - y1;
    }
    else
    {
        ySign = 1;
        dy = y1 - y2;
    }
    if (xSign == 0)
    {
        if (ySign == 0)
        {
            if (dx == 0.0f)
                return 16;
            if (dy == 0.0f)
                return 8;
            if (dx == dy)
                return 12;
            if (dx > dy)
            {
                count = (s32)((dx + dy * 0.5f) / dy);
                if (count > 4)
                {
                    if (gFrameCounter & 3)
                        count = 4;
                    else
                        count = 3;
                }
                return 12 - count;
            }
            else
            {
                count = (s32)((dy + dx * 0.5f) / dx);
                if (count > 4)
                {
                    if (gFrameCounter & 3)
                        count = 4;
                    else
                        count = 3;
                }
                return count + 12;
            }
        }
        else if (ySign == 1)
        {
            if (dx == 0.0f)
                return 0;
            if (dy == 0.0f)
                return 8;
            if (dx == dy)
                return 4;
            if (dx > dy)
            {
                count = (s32)((dx + dy * 0.5f) / dy);
                if (count > 4)
                {
                    if (gFrameCounter & 3)
                        count = 4;
                    else
                        count = 3;
                }
                return count + 4;
            }
            else
            {
                count = (s32)((dy + dx * 0.5f) / dx);
                if (count > 4)
                {
                    if (gFrameCounter & 3)
                        count = 4;
                    else
                        count = 3;
                }
                return 4 - count;
            }
        }
    }
    if (xSign == 1)
    {
        if (ySign == 1)
        {
            if (dx == 0.0f)
                return 0;
            if (dy == 0.0f)
                return 24;
            if (dx == dy)
                return 28;
            if (dx > dy)
            {
                count = (s32)((dx + dy * 0.5f) / dy);
                if (count > 4)
                {
                    if (gFrameCounter & 3)
                        count = 4;
                    else
                        count = 3;
                }
                return 28 - count;
            }
            else
            {
                count = (s32)((dy + dx * 0.5f) / dx);
                if (count > 4)
                {
                    if (gFrameCounter & 3)
                        count = 4;
                    else
                        count = 3;
                }
                return count + 28;
            }
        }
        else if (ySign == 0)
        {
            if (dx == 0.0f)
                return 16;
            if (dy == 0.0f)
                return 24;
            if (dx == dy)
                return 20;
            if (dx > dy)
            {
                count = (s32)((dx + dy * 0.5f) / dy);
                if (count > 4)
                {
                    if (gFrameCounter & 3)
                        count = 4;
                    else
                        count = 3;
                }
                return count + 20;
            }
            else
            {
                count = (s32)((dy + dx * 0.5f) / dx);
                if (count > 4)
                {
                    if (gFrameCounter & 3)
                        count = 4;
                    else
                        count = 3;
                }
                return 20 - count;
            }
        }
    }
}


#include "utility_helpers.h"
#include "state0_display.h"
#include "main.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "display_helpers.h"
#include "compression.h"
#include "object_helpers.h"

extern const u8 gUnknownBytes_083B2AF0[];
extern u8 gUnknown_030057E0[];
extern u8 gUnknown_03000BE0[];
extern u8 gUnknown_03000490[];
extern u8 gUnknown_0300047C[];
extern u32 gUnknown_03000430;
extern u8 *gUnknownPointer_03002414;
extern u8 *gUnknownPointer_03005308;
extern u8 gUnknown_02026000[];
extern u8 gUnknown_020260D0[];
extern u8 gUnknown_020268F0[];
extern u8 gUnknown_02024000[];
extern const u8 gUnknownBytes_083D1D78[];
void sub_08043CA8(void);
void sub_08043E78(void);
void sub_08043FEC(u32);

void sub_080441B8(void)
{
    {
        u32 zero = 0;
        CpuFastSet(&zero, (void *)0x05000200, CPU_SET_FILL | 0x80);
    }
    {
        u32 zero = 0;
        CpuFastSet(&zero, (void *)0x05000000, CPU_SET_FILL | 0x80);
    }
    sub_0803F624(gUnknown_03000490, 20, 0);
    gUnknown_03000490[0] = 3;
    gState0TransferWork.bytes[0x41] = 0;
    gState0TransferWork.bytes[0x42] = 0;
    gState0TransferWork.bytes[0x43] = 0;
    gMainState = 0;
    gMainSubstate = 3;
    gUnknown_0300137C = 0;
}

void sub_080445F4(void)
{
    sub_0803F624(gUnknown_02026000, 0xD0, 0);
    sub_0803F624(gUnknown_020260D0, 0x820, 0);
    sub_0803F624(gUnknown_020268F0, 0x60, 0);
    gUnknown_03000430 = 2;
    gUnknownPointer_03002414 = gUnknown_02024000;
    {
        u32 zero = 0;
        CpuFastSet(&zero, gUnknownPointer_03002414, CPU_SET_FILL | 0x426);
    }
    gUnknownPointer_03005308 = gUnknown_020268F0;
    {
        u32 fill = 0x200;
        CpuFastSet(&fill, gUnknownPointer_03002414 + 0xB84, CPU_SET_FILL | 0x100);
    }
    gUnknownPointer_03002414[0x1094] = 0;
    gUnknownPointer_03002414[0x1095] = 0;
    sub_08047414((struct RecordDisplayWork *)gUnknown_02026000, (struct RenderWork *)gUnknownPointer_03002414, gUnknownBytes_083D1D78, gUnknown_020260D0);
}

void sub_08044BA8(u32 mode, u32 value)
{
    sub_08043CA8();
    sub_08040CD0(0, 128);
    gUnknown_03000440[0x96] = 0;
    gUnknown_03000430 = 0;
    sub_0803F624(gUnknown_03000440 + 0x3C, 20, 0);
    gUnknown_03000440[0x3C] = 3;
    gUnknown_03000440[0x3D] = value;
    switch (mode)
    {
    case 0:
        gUnknown_03000440[0x3E] = 0;
        break;
    case 1:
        gUnknown_03000440[0x3E] = 1;
        break;
    case 2:
        gUnknown_03000440[0x3E] = 2;
        break;
    case 3:
        gUnknown_03000440[0x3E] = 3;
        break;
    }
    gMainState = 0;
    gMainSubstate = 5;
    gUnknown_0300137C = 16;
}

void sub_08044C38(u32 mode)
{
    sub_08043CA8();
    sub_0803F624(gUnknown_0300047C, 20, 0);
    sub_0803F624(gUnknown_0300047C + 20, 20, 0);
    gUnknown_0300047C[0x4D] = 1;
    gUnknown_0300047C[0x51] = 0;
    switch (mode)
    {
    case 0:
        gUnknown_0300047C[0] = 4;
        gMainState = 0;
        gMainSubstate = 4;
        gUnknown_0300137C = 0;
        break;
    case 1:
        gUnknown_0300047C[0] = 4;
        gMainState = 0;
        gMainSubstate = 5;
        gUnknown_0300137C = 0;
        break;
    case 2:
        gUnknown_0300047C[0xFC] = 0;
        gMainState = 0;
        gMainSubstate = 10;
        gUnknown_0300137C = 0;
        break;
    case 3:
        gUnknown_0300047C[0xFC] = 1;
        gMainState = 0;
        gMainSubstate = 10;
        gUnknown_0300137C = 0;
        break;
    }
}
