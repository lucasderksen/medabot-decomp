

#include "record_helpers.h"

void sub_08064BEC(void);
void sub_08064C0C(void);
void sub_08064C2C(void);
void sub_08064C4C(void);
void LZ77UnCompWram(const void *source, void *destination);

extern u8 gUnknown_03005290[];
extern u8 gUnknown_030052B0[];
extern u8 gUnknown_030052D0[];
extern u8 gUnknown_030052F0[];

struct DmaRegisters
{
    u32 source;
    u32 destination;
    u32 control;
};

void sub_08044CDC(u32 mode)
{
    switch (mode)
    {
    case 0: sub_08064BEC(); break;
    case 1: sub_08064C0C(); break;
    case 2: sub_08064C2C(); break;
    case 3: sub_08064C4C(); break;
    }
}

u32 sub_08044D0C(const void *source, void *destination)
{
    u32 header = *(const u32 *)source;
    u32 bytes = header >> 8;
    if (((u8)header >> 4) == 1)
        LZ77UnCompWram(source, destination);
    else
    {
        u32 count = header >> 10;
        CpuSet(source, destination, count & 0x1FFFFF);
        {
        volatile struct DmaRegisters *dma = (volatile struct DmaRegisters *)0x040000D4;
        dma->source = (u32)((const u8 *)source + (header >> 9));
        dma->destination = (u32)((u8 *)destination + (header >> 9));
        { u32 control = 0x80000000; control |= count; dma->control = control; }
        dma->control;
        }
    }
    return bytes;
}

u32 sub_08044D64(u32 *destination, const u32 *source, u32 bytes)
{
    while (bytes > 3)
    {
        *destination++ = *source++;
        bytes -= 4;
    }
    return bytes;
}

u32 sub_08044D78(u16 *destination, const u16 *source, u32 bytes)
{
    while (bytes > 1)
    {
        *destination++ = *source++;
        bytes -= 2;
    }
    return bytes;
}

void sub_08044D90(u8 *destination, const u8 *source, u32 bytes)
{
    while (bytes != 0)
    {
        *destination++ = *source++;
        bytes--;
    }
}

u32 sub_08044E64(s32 shape, s32 size)
{
    u32 result = 0;
    switch (shape)
    {
    case 0:
        switch (size)
        {
        case 0: result = 0x00080008; break;
        case 0x40000000: result = 0x00100010; break;
        case (s32)0x80000000: result = 0x00200020; break;
        case (s32)0xC0000000: result = 0x00400040; break;
        }
        break;
    case 0x4000:
        switch (size)
        {
        case 0: result = 0x00080010; break;
        case 0x40000000: result = 0x00080020; break;
        case (s32)0x80000000: result = 0x00100020; break;
        case (s32)0xC0000000: result = 0x00200040; break;
        }
        break;
    case 0x8000:
        switch (size)
        {
        case 0: result = 0x00100008; break;
        case 0x40000000: result = 0x00200008; break;
        case (s32)0x80000000: result = 0x00200010; break;
        case (s32)0xC0000000: result = 0x00400020; break;
        }
        break;
    }
    return result;
}

void sub_08044F54(const void *source, u32 tile, void *scratch, u32 useCpu)
{
    u16 destinationTile = tile;
    tile = (u16)tile;
    if (source != 0)
    {
        u32 bytes = sub_08044D0C(source, scratch);
        if (useCpu != 0)
            CpuSet(scratch, (u8 *)0x06010000 + tile * 32, (bytes & 0x7FFFFF) / 4 | CPU_SET_32BIT);
        else
        {
            volatile struct DmaRegisters *dma = (volatile struct DmaRegisters *)0x040000B0;
            dma->source = (u32)scratch;
            dma->destination = (u32)((u8 *)0x06010000 + destinationTile * 32);
            dma->control = (bytes >> 2) | 0x94000000;
            dma->control;
        }
    }
}

void sub_08045A14(struct OamEntry *objects, const u16 *parameters)
{
    s32 i;
    for (i = 31; i >= 0; i--)
    {
        objects++->affine = *parameters++;
        objects++->affine = *parameters++;
        objects++->affine = *parameters++;
        objects++->affine = *parameters++;
    }
}

u32 sub_08045A40(s32 y, s32 x)
{
    u32 result = 0;
    if (y > -64 && x > -32 && y <= 159 && x <= 239)
        result = 1;
    return result;
}

void sub_08046CC8(s32 first, s32 second, s32 third, s32 fourth)
{
    if (first >= 0)
        gUnknown_030052D0[13] = -gUnknown_030052D0[13] - 2;
    if (second >= 0)
        gUnknown_03005290[13] = -gUnknown_03005290[13] - 2;
    if (third >= 0)
        gUnknown_030052B0[13] = -gUnknown_030052B0[13] - 2;
    if (fourth >= 0)
        gUnknown_030052F0[13] = -gUnknown_030052F0[13] - 2;
}


#include "record_helpers.h"

u32 sub_08045328(struct RecordObjectWork *work, struct OamEntry *objects, const void *source, const void *palette, const u32 *header, const struct RecordObjectPlacement *placement, u8 bank, u16 tile)
{
    work->objects = objects;
    work->placement = placement;
    {
        u32 descriptor = *header;
        work->rows = (descriptor << 20) >> 28;
        work->columns = (descriptor << 16) >> 28;
    }
    work->key = placement->key;
    return sub_08045120(objects, source, palette, header, placement, bank, tile);
}

u32 sub_080458B8(const struct RecordObjectList *list, struct OamEntry *output, u16 limit)
{
    u16 result = 0;
    u16 i;
    u16 count = list->count;
    for (i = 0; i < count; i++)
    {
        result += sub_080455E0(list->entries[i], output, result, limit);
        if (result >= limit)
            break;
    }
    return result;
}

u32 sub_08045A60(const struct RecordObjectWork *work, struct OamEntry *output, u16 index, u32 unused, u32 priority, u8 mode)
{
    return (u16)sub_08045680(work, output, index, (s8)priority, 128, mode);
}


#include "record_helpers.h"

void sub_08045A8C(struct RecordObjectWork *work, u16 y, u16 x, u32 mode)
{
    if (mode != 0)
    {
        if (mode == 1)
        {
            {
                u32 offset = ((u8 *)work->objects)[0];
                offset += y;
                y = offset;
            }
            {
                u32 offset = ((u32)work->objects[0].attr1 << 23) >> 23;
                offset += x;
                x = offset;
            }
        }
        else
        {
            {
                s32 offset = work->placement->y;
                s16 signedValue = y;
                y = signedValue + offset;
            }
            {
                s32 offset = work->placement->x;
                s16 signedValue = x;
                x = signedValue + offset;
            }
        }
    }
    sub_0804538C(work, (s16)y, (s16)x, work->key);
}

u32 sub_08045AEC(struct RecordObjectWork *work, struct OamEntry *output, u16 index, s16 y, s16 x, u16 key, u8 priority, u8 mode)
{
    u16 result = index;
    if (sub_08045A40(y, x) != 0)
    {
        sub_0804538C(work, y, x, (s16)key);
        result = (u16)sub_08045680(work, output, result, (s8)priority, 128, mode);
    }
    return result;
}


#include "record_helpers.h"

struct OamWords { u32 words[2]; };

u32 sub_08045908(struct RecordObjectList *list, struct OamEntry *output, u16 limit)
{
    u16 count = list->count;
    u16 result = 0;
    u16 i, j;
    for (i = 0; i < count; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            struct RecordObjectWork *first = list->entries[i];
            struct RecordObjectWork *second = list->entries[j];
            if ((u16)first->key > (u16)second->key)
            {
                list->entries[i] = second;
                list->entries[j] = first;
            }
        }
        result += sub_080455E0(list->entries[i], output, result, limit);
        if (result >= limit)
            break;
    }
    return result;
}

void sub_080459A4(struct OamEntry *objects, u16 start, u16 end)
{
    if (end > start)
    {
        struct OamEntry *first = objects + start;
        s32 i, j;
        for (i = start; i < end - 1; i++)
        {
            struct OamEntry *scan = first;
            for (j = i; j < end; j++)
            {
                if ((s16)first->affine > (s16)scan->affine)
                {
                    struct OamWords temporary = *(struct OamWords *)first;
                    *(struct OamWords *)first = *(struct OamWords *)scan;
                    *(struct OamWords *)scan = temporary;
                }
                scan++;
            }
            first++;
        }
    }
}

void sub_08045D1C(u8 *work)
{
    work[0x1096] = 0;
    work[0x1097] = 0;
}


#include "record_helpers.h"

void sub_08046034(const struct RecordAssetSet *const *sets, struct RecordTileBlock *records, const u32 *commands, u8 selector, u8 recordIndex)
{
    const struct RecordAssetSet *set = sets[selector];
    if (commands != 0 && (*(const u8 *)commands & 0x3F) != 0)
    {
        u32 address = recordIndex * sizeof(*records);
        struct RecordTileBlock *record = (struct RecordTileBlock *)(address + (u32)records);
        do
        {
            u32 command = *commands;
            if (selector == (command << 26 >> 26))
            {
                s32 bytes = sub_08044D0C(set->entries[command << 18 >> 24].source, (void *)0x02030800);
                if (bytes != 0)
                    CpuSet((void *)0x02030800, (u8 *)0x06010000 + (((u32)record->tile << 22) >> 17), (bytes / 2) & 0x1FFFFF);
                return;
            }
            commands++;
        } while ((*(const u8 *)commands & 0x3F) != 0);
    }
}


#include "record_helpers.h"

void ObjAffineSet(const void *, void *, u32, u32);
struct ObjectAffineInput { s16 xScale; s16 yScale; u16 angle; };
struct ObjectAffineOutput { s16 pa, pb, pc, pd; };
extern const struct ObjectAffineOutput gUnknownAffine_080ABD5C;

u32 sub_08045B68(struct RecordObjectWork *work, struct OamEntry *output, u16 index, s16 y, s16 x, u16 key, u8 priority, u8 flip, u16 scale, u16 *affine, u32 mode)
{
    u16 result = index;
    if (sub_08045A40(y, x) != 0)
    {
        sub_0804538C(work, y, x, (s16)key);
        result = (u16)sub_08045794(work, output, result, (s8)priority, 128, mode);
        if (affine != 0)
        {
            mode *= 4;
            if (flip != 0)
                affine[mode] = -scale;
            else
                affine[mode] = scale;
            affine[++mode] = 0;
            affine[++mode] = 0;
            affine[++mode] = scale;
        }
    }
    return result;
}

u32 sub_08045C30(struct RecordObjectWork *work, struct OamEntry *output, u16 index, s16 y, s16 x, u16 key, u8 priority, u16 angle, u16 *affine, u32 mode)
{
    u16 result = index;
    if (sub_08045A40(y, x) != 0)
    {
        sub_0804538C(work, y, x, (s16)key);
        result = (u16)sub_08045794(work, output, result, (s8)priority, 128, mode);
        if (affine != 0)
        {
            struct ObjectAffineInput input = { 0x100, 0x100, -(u32)(u16)angle };
            struct ObjectAffineOutput matrix;
                        matrix = gUnknownAffine_080ABD5C;
            ObjAffineSet(&input, &matrix, 1, 2);
            mode *= 4;
            affine[mode] = matrix.pa;
            affine[++mode] = matrix.pb;
            affine[++mode] = matrix.pc;
            affine[++mode] = matrix.pd;
        }
    }
    return result;
}


#include "record_helpers.h"

void sub_0804589C(struct RecordObjectList *list, struct RecordObjectWork **entries)
{
    list->entries = entries;
    list->count = 0;
}

void sub_080458A4(struct RecordObjectList *list, struct RecordObjectWork *work, s32 key)
{
    work->key = key;
    list->entries[list->count] = work;
    list->count++;
}


#include "record_helpers.h"

u32 sub_080454F0(const struct OamEntry *objects, u16 count, u16 key)
{
    u16 middle = 0;
    if (count != 0)
    {
        u16 low = 0;
        u32 high = (u16)(count - 1);
        s16 value;
        middle = high;
        middle /= 2;
        while (middle != low && middle != high && (s16)(value = objects[middle].affine) != (s16)key)
        {
            if (value < (s16)key)
                low = middle;
            if (value > (s16)key)
                high = middle;
            middle = (low + high) / 2;
        }
        while (middle < count && (s16)objects[middle].affine <= (s16)key)
            middle++;
    }
    return middle;
}
