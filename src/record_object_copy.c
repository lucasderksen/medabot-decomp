

#include "record_helpers.h"

struct OamWords { u32 words[2]; };

struct ObjectAttributes
{
    u32 y:8, affineMode:2, mode:2, mosaic:1, color:1, shape:2;
    u32 x:9, matrixLow:3, hFlip:1, vFlip:1, size:2;
    u32 tile:10, priority:2, palette:4, key:16;
};

u32 sub_08045794(const struct RecordObjectWork *work, struct OamEntry *output, u16 index, s32 inputPriority, u32 inputLimit, u32 mode)
{
    u8 priority = inputPriority;
    u16 limit = inputLimit;
    u32 count = work->rows * work->columns;
    u16 i;
    output = sub_08045588(output, index, count, work->key);
    for (i = 0; i < count && index < limit; output++, index++, i++)
    {
        struct ObjectAttributes *object = (struct ObjectAttributes *)output;
        *(struct OamWords *)output = ((const struct OamWords *)work->objects)[i];
        object->palette += (s8)priority;
        object->key = work->key;
        object->matrixLow = mode;
        object->hFlip = (mode >> 3) & 1;
        object->vFlip = mode >> 4;
        if ((u16)work->key > 300)
            object->priority = 3;
        else if ((u16)work->key > 200)
            object->priority = 2;
        else if ((u16)work->key > 100)
            object->priority = 1;
    }
    return index;
}

#include "record_helpers.h"



u32 sub_08045680(const struct RecordObjectWork *work, struct OamEntry *output, u16 index, s32 inputPriority, u32 inputLimit, u32 inputMode)
{
    u8 priority = inputPriority;
    u16 limit = inputLimit;
    u8 mode = inputMode;
    u32 count = work->rows * work->columns;
    u16 i;
    output = sub_08045588(output, index, count, work->key);
    for (i = 0; i < count && index < limit; output++, index++, i++)
    {
        struct ObjectAttributes *object = (struct ObjectAttributes *)output;
        *(struct OamWords *)output = ((const struct OamWords *)work->objects)[i];
        object->palette += (s8)priority;
        object->hFlip = mode & 1;
        object->vFlip = (mode >> 1) % 2;
        object->key = work->key;
        if ((u16)work->key > 300)
            object->priority = 3;
        else if ((u16)work->key > 200)
            object->priority = 2;
        else if ((u16)work->key > 100)
            object->priority = 1;
    }
    return index;
}

#include "record_helpers.h"

struct OamEntry *sub_08045588(struct OamEntry *objects, u16 count, s32 inputGap, s32 inputKey)
{
    u16 gap = inputGap;
    u16 key = inputKey;
    u16 previous = count;
    count--;
    if (previous != 0)
    {
        struct OamEntry *destination = objects + (count + gap);
        objects += count;
        {
        s32 signedKey = (s16)key;
        do
        {
            if ((s16)objects->affine <= signedKey)
                break;
            *(struct OamWords *)destination = *(struct OamWords *)objects;
            if (count == 0)
            {
                objects--;
                break;
            }
            count--;
            objects--;
            destination--;
        } while (1);
        }
        objects++;
    }
    return objects;
}

u32 sub_080455E0(const struct RecordObjectWork *work, struct OamEntry *output, u16 index, u16 limit)
{
    u16 i = 0;
    for (i = 0; i < work->rows * work->columns && index < limit; i++, index++)
    {
        struct ObjectAttributes *object = (struct ObjectAttributes *)(struct OamEntry *)(index * 8 + (u32)output);
        ((struct OamWords *)output)[index] = ((const struct OamWords *)work->objects)[i];
        output[index].affine = work->key;
        if ((u16)work->key > 300)
            object->priority = 3;
        else if ((u16)work->key > 200)
            object->priority = 2;
        else if ((u16)work->key > 100)
            object->priority = 1;
    }
    return index;
}
