#include "coordinate_helpers.h"
#include "compression.h"
#include "frame_objects.h"

extern const s16 gUnknownSines_083D6A2C[];
extern const s16 gUnknownSines_083D6C2C[];
extern const u8 *const gUnknownPointers_083B1A08[];
#include "encounter_records.h"
extern const u8 gUnknownBytes_083B2AEC[];

struct TileCoordinates sub_08042CA0(u32 angle, u32 radius, u32 x, u32 y, u32 reduceY, u32 reduceX)
{
    struct TileCoordinates result;
    if (radius < reduceY)
        reduceY = radius;
    if (radius < reduceX)
        reduceX = radius;
    x += (u32)((float)gUnknownSines_083D6C2C[angle] * ((float)(radius - reduceX) * (1.0f / 256.0f)));
    y += (u32)((float)gUnknownSines_083D6A2C[angle] * ((float)(radius - reduceY) * (1.0f / 256.0f)));
    result.x = x & 0x1FF;
    result.y = y & 0xFF;
    return result;
}

void sub_08042D94(u32 first, u32 second, u32 third, u32 fourth, u32 graphicsSlot)
{
    LeDecompress(gUnknownPointers_083B1A08[((first << 2) + (first << 1))], (void *)(0x06010000 + (graphicsSlot << 10)));
    LeDecompress(gUnknownPointers_083B1A08[((second << 2) + (second << 1)) + 1], (void *)(0x06010080 + (graphicsSlot << 10)));
    LeDecompress(gUnknownPointers_083B1A08[((second << 2) + (second << 1)) + 2], (void *)(0x06010100 + (graphicsSlot << 10)));
    LeDecompress(gUnknownPointers_083B1A08[((third << 2) + (third << 1)) + 3], (void *)(0x06010180 + (graphicsSlot << 10)));
    LeDecompress(gUnknownPointers_083B1A08[((third << 2) + (third << 1)) + 4], (void *)(0x06010200 + (graphicsSlot << 10)));
    LeDecompress(gUnknownPointers_083B1A08[((fourth << 2) + (fourth << 1)) + 5], (void *)(0x06010280 + (graphicsSlot << 10)));
}

void sub_08042E58(u32 first, u32 second, u32 third, u32 fourth, u32 tileGroup, u32 firstObject, u32 x, u32 y, u32 flip, u32 flagGroup, u32 priority)
{
    sub_08040CD0(firstObject, 4);
    gFrameObjects[firstObject].flags = 0;
    gFrameObjects[firstObject].flags = 0xC004 | (flagGroup << 10);
    if (flip)
        gFrameObjects[firstObject].flags |= 0x1000;
    else
        gFrameObjects[firstObject].flags &= 0xEFFF;
    gFrameObjects[firstObject].screenX = x;
    gFrameObjects[firstObject].screenY = y - 4;
    gFrameObjects[firstObject].frameAndGroup = tileGroup * 8 + 0x500;
    gFrameObjects[firstObject].palette = *(const u8 *)((u32)gUnknownBytes_083BEB94 + first);
    gFrameObjects[firstObject].tableSelector = 0;
    gFrameObjects[firstObject].priority = priority + 2;
    gFrameObjects[firstObject + 1].flags = 0;
    gFrameObjects[firstObject + 1].flags = 0xC004 | (flagGroup << 10);
    if (flip)
    {
        gFrameObjects[firstObject + 1].flags |= 0x1000;
        gFrameObjects[firstObject + 1].frameAndGroup = tileGroup * 8 + 0x502;
        gFrameObjects[firstObject + 1].priority = priority;
    }
    else
    {
        gFrameObjects[firstObject + 1].flags &= 0xEFFF;
        gFrameObjects[firstObject + 1].frameAndGroup = tileGroup * 8 + 0x501;
        gFrameObjects[firstObject + 1].priority = priority + 3;
    }
    gFrameObjects[firstObject + 1].screenX = x - 8;
    gFrameObjects[firstObject + 1].screenY = y + 4;
    gFrameObjects[firstObject + 1].palette = *(const u8 *)((u32)gUnknownBytes_083BEB94 + second);
    gFrameObjects[firstObject + 1].tableSelector = 0;
    gFrameObjects[firstObject + 1].scaleX = 64;
    gFrameObjects[firstObject + 1].scaleY = 64;
    gFrameObjects[firstObject + 1].angle = 0;
    gFrameObjects[firstObject + 2].flags = 0;
    gFrameObjects[firstObject + 2].flags = 0xC004 | (flagGroup << 10);
    if (flip)
    {
        gFrameObjects[firstObject + 2].flags |= 0x1000;
        gFrameObjects[firstObject + 2].frameAndGroup = tileGroup * 8 + 0x503;
        gFrameObjects[firstObject + 2].priority = priority + 3;
    }
    else
    {
        gFrameObjects[firstObject + 2].flags &= 0xEFFF;
        gFrameObjects[firstObject + 2].frameAndGroup = tileGroup * 8 + 0x504;
        gFrameObjects[firstObject + 2].priority = priority;
    }
    gFrameObjects[firstObject + 2].screenX = x + 8;
    gFrameObjects[firstObject + 2].screenY = y + 4;
    gFrameObjects[firstObject + 2].palette = *(const u8 *)((u32)gUnknownBytes_083BEB94 + third);
    gFrameObjects[firstObject + 2].tableSelector = 0;
    gFrameObjects[firstObject + 2].scaleX = 64;
    gFrameObjects[firstObject + 2].scaleY = 64;
    gFrameObjects[firstObject + 2].angle = 0;
    gFrameObjects[firstObject + 3].flags = 0;
    gFrameObjects[firstObject + 3].flags = 0xC004 | (flagGroup << 10);
    if (flip)
        gFrameObjects[firstObject + 3].flags |= 0x1000;
    else
        gFrameObjects[firstObject + 3].flags &= 0xEFFF;
    gFrameObjects[firstObject + 3].screenX = x;
    gFrameObjects[firstObject + 3].screenY = y + 4;
    gFrameObjects[firstObject + 3].frameAndGroup = tileGroup * 8 + 0x505;
    gFrameObjects[firstObject + 3].palette = *(const u8 *)((u32)gUnknownBytes_083BEB94 + fourth);
    gFrameObjects[firstObject + 3].tableSelector = 0;
    gFrameObjects[firstObject + 3].priority = priority + 1;
}

void sub_0804305C(u32 first, u32 second, u32 third, u32 fourth, u32 tileGroup, u32 firstObject, u32 x, u32 y, u32 flip, u32 flagGroup, u32 priority)
{
    gFrameObjects[firstObject].flags |= 0xC004 | (flagGroup << 10);
    if (flip)
        gFrameObjects[firstObject].flags |= 0x1000;
    else
        gFrameObjects[firstObject].flags &= 0xEFFF;
    gFrameObjects[firstObject].screenX = x;
    gFrameObjects[firstObject].screenY = y - 4;
    gFrameObjects[firstObject].frameAndGroup = tileGroup * 8 + 0x500;
    gFrameObjects[firstObject].palette = *(const u8 *)((u32)gUnknownBytes_083BEB94 + first);
    gFrameObjects[firstObject].tableSelector = 0;
    gFrameObjects[firstObject].priority = priority + 2;
    gFrameObjects[firstObject + 1].flags |= 0xC004 | (flagGroup << 10);
    if (flip)
    {
        gFrameObjects[firstObject + 1].flags |= 0x1000;
        gFrameObjects[firstObject + 1].frameAndGroup = tileGroup * 8 + 0x502;
        gFrameObjects[firstObject + 1].priority = priority;
    }
    else
    {
        gFrameObjects[firstObject + 1].flags &= 0xEFFF;
        gFrameObjects[firstObject + 1].frameAndGroup = tileGroup * 8 + 0x501;
        gFrameObjects[firstObject + 1].priority = priority + 3;
    }
    gFrameObjects[firstObject + 1].screenX = x - 8;
    gFrameObjects[firstObject + 1].screenY = y + 4;
    gFrameObjects[firstObject + 1].palette = *(const u8 *)((u32)gUnknownBytes_083BEB94 + second);
    gFrameObjects[firstObject + 1].tableSelector = 0;
    gFrameObjects[firstObject + 2].flags |= 0xC004 | (flagGroup << 10);
    if (flip)
    {
        gFrameObjects[firstObject + 2].flags |= 0x1000;
        gFrameObjects[firstObject + 2].frameAndGroup = tileGroup * 8 + 0x503;
        gFrameObjects[firstObject + 2].priority = priority + 3;
    }
    else
    {
        gFrameObjects[firstObject + 2].flags &= 0xEFFF;
        gFrameObjects[firstObject + 2].frameAndGroup = tileGroup * 8 + 0x504;
        gFrameObjects[firstObject + 2].priority = priority;
    }
    gFrameObjects[firstObject + 2].screenX = x + 8;
    gFrameObjects[firstObject + 2].screenY = y + 4;
    gFrameObjects[firstObject + 2].palette = *(const u8 *)((u32)gUnknownBytes_083BEB94 + third);
    gFrameObjects[firstObject + 2].tableSelector = 0;
    gFrameObjects[firstObject + 3].flags |= 0xC004 | (flagGroup << 10);
    if (flip)
        gFrameObjects[firstObject + 3].flags |= 0x1000;
    else
        gFrameObjects[firstObject + 3].flags &= 0xEFFF;
    gFrameObjects[firstObject + 3].screenX = x;
    gFrameObjects[firstObject + 3].screenY = y + 4;
    gFrameObjects[firstObject + 3].frameAndGroup = tileGroup * 8 + 0x505;
    gFrameObjects[firstObject + 3].palette = *(const u8 *)((u32)gUnknownBytes_083BEB94 + fourth);
    gFrameObjects[firstObject + 3].tableSelector = 0;
    gFrameObjects[firstObject + 3].priority = priority + 1;
}

void sub_08043240(u32 firstObject, u32 increment)
{
    u32 i;
    gFrameObjects[firstObject + 1].flags |= 0x200;
    gFrameObjects[firstObject + 2].flags |= 0x200;
    for (i = 0; i < 16; i++)
        ;
    gFrameObjects[firstObject].unknown23[1] = increment;
    gFrameObjects[firstObject + 1].unknown23[1] = increment;
    gFrameObjects[firstObject + 2].unknown23[1] = increment;
    gFrameObjects[firstObject + 3].unknown23[1] = increment;
}

void sub_080432A0(u32 firstObject, u32 tileGroup, u32 unused)
{
    u32 phase;
    union { struct TileCoordinates pair; s32 packed; } coordinates;
    s32 copy;
    gFrameObjects[firstObject].screenX = gFrameObjects[firstObject + 3].screenX;
    gFrameObjects[firstObject + 3].unknown23[3] += gFrameObjects[firstObject + 3].unknown23[1];
    if (gFrameObjects[firstObject + 3].unknown23[3] > 63)
    {
        gFrameObjects[firstObject + 3].unknown23[3] -= 64;
        gFrameObjects[firstObject + 3].commandOffset = (gFrameObjects[firstObject + 3].commandOffset + 1) & 3;
        gFrameObjects[firstObject + 3].frameAndGroup = tileGroup * 8 + (u16)(0x505 + gUnknownBytes_083B2AEC[gFrameObjects[firstObject + 3].commandOffset]);
    }
    gFrameObjects[firstObject + 1].unknown23[3] += gFrameObjects[firstObject + 1].unknown23[1];
    phase = gFrameObjects[firstObject + 1].unknown23[3] / 2;
    if (gFrameObjects[firstObject + 1].unknown23[3] > 63)
    {
        phase = 32;
        gFrameObjects[firstObject + 1].unknown23[3] -= 64;
    }
    switch (gFrameObjects[firstObject + 1].commandOffset)
    {
    case 0:
        gFrameObjects[firstObject + 1].angle = phase * 4;
        coordinates.pair = sub_08042BC0(phase + 96, 5, gFrameObjects[firstObject + 3].screenX, gFrameObjects[firstObject + 3].screenY);
        copy = coordinates.packed;
        gFrameObjects[firstObject + 1].screenX = copy - 5;
        gFrameObjects[firstObject + 1].screenY = (copy >> 16) - 3;
        break;
    case 1:
        gFrameObjects[firstObject + 1].angle = 128 - phase * 4;
        coordinates.pair = sub_08042BC0(128 - phase, 5, gFrameObjects[firstObject + 3].screenX, gFrameObjects[firstObject + 3].screenY);
        copy = coordinates.packed;
        gFrameObjects[firstObject + 1].screenX = copy - 5;
        gFrameObjects[firstObject + 1].screenY = (copy >> 16) - 3;
        break;
    case 2:
        gFrameObjects[firstObject + 1].angle = 1024 - phase * 4;
        coordinates.pair = sub_08042BC0(96 - phase, 5, gFrameObjects[firstObject + 3].screenX, gFrameObjects[firstObject + 3].screenY);
        copy = coordinates.packed;
        gFrameObjects[firstObject + 1].screenX = copy - 5;
        gFrameObjects[firstObject + 1].screenY = (copy >> 16) - 3;
        break;
    case 3:
        gFrameObjects[firstObject + 1].angle = phase * 4 + 896;
        coordinates.pair = sub_08042BC0(phase + 64, 5, gFrameObjects[firstObject + 3].screenX, gFrameObjects[firstObject + 3].screenY);
        copy = coordinates.packed;
        gFrameObjects[firstObject + 1].screenX = copy - 5;
        gFrameObjects[firstObject + 1].screenY = (copy >> 16) - 3;
        break;
    }
    if (phase == 32)
        gFrameObjects[firstObject + 1].commandOffset = (gFrameObjects[firstObject + 1].commandOffset + 1) & 3;
    gFrameObjects[firstObject + 2].unknown23[3] += gFrameObjects[firstObject + 2].unknown23[1];
    phase = gFrameObjects[firstObject + 2].unknown23[3] / 2;
    if (gFrameObjects[firstObject + 2].unknown23[3] > 63)
    {
        phase = 32;
        gFrameObjects[firstObject + 2].unknown23[3] -= 64;
    }
    switch (gFrameObjects[firstObject + 2].commandOffset)
    {
    case 2:
        gFrameObjects[firstObject + 2].angle = phase * 4;
        coordinates.pair = sub_08042BC0(phase + 32, 5, gFrameObjects[firstObject + 3].screenX, gFrameObjects[firstObject + 3].screenY);
        copy = coordinates.packed;
        gFrameObjects[firstObject + 2].screenX = copy + 5;
        gFrameObjects[firstObject + 2].screenY = (copy >> 16) - 3;
        break;
    case 3:
        gFrameObjects[firstObject + 2].angle = 128 - phase * 4;
        coordinates.pair = sub_08042BC0(64 - phase, 5, gFrameObjects[firstObject + 3].screenX, gFrameObjects[firstObject + 3].screenY);
        copy = coordinates.packed;
        gFrameObjects[firstObject + 2].screenX = copy + 5;
        gFrameObjects[firstObject + 2].screenY = (copy >> 16) - 3;
        break;
    case 0:
        gFrameObjects[firstObject + 2].angle = 1024 - phase * 4;
        coordinates.pair = sub_08042BC0(32 - phase, 5, gFrameObjects[firstObject + 3].screenX, gFrameObjects[firstObject + 3].screenY);
        copy = coordinates.packed;
        gFrameObjects[firstObject + 2].screenX = copy + 5;
        gFrameObjects[firstObject + 2].screenY = (copy >> 16) - 3;
        break;
    case 1:
        gFrameObjects[firstObject + 2].angle = phase * 4 + 896;
        coordinates.pair = sub_08042BC0(phase, 5, gFrameObjects[firstObject + 3].screenX, gFrameObjects[firstObject + 3].screenY);
        copy = coordinates.packed;
        gFrameObjects[firstObject + 2].screenX = copy + 5;
        gFrameObjects[firstObject + 2].screenY = (copy >> 16) - 3;
        break;
    }
    if (phase == 32)
        gFrameObjects[firstObject + 2].commandOffset = (gFrameObjects[firstObject + 2].commandOffset + 1) & 3;
    if (gUnknownBytes_083B2AEC[gFrameObjects[firstObject + 3].commandOffset] != 0)
    {
        gFrameObjects[firstObject].screenY = gFrameObjects[firstObject + 3].screenY - 7;
        gFrameObjects[firstObject + 1].screenY++;
        gFrameObjects[firstObject + 2].screenY++;
    }
    else
        gFrameObjects[firstObject].screenY = gFrameObjects[firstObject + 3].screenY - 8;
}
