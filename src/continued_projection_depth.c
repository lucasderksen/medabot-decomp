#include "global.h"
#include "gba.h"
#include "frame.h"
#include "continued_commands.h"
#include "continued_numeric.h"
#include "continued_map_data.h"

struct NumericView
{
    s32 word00;
    s32 word04;
    s32 word08;
    s32 word0C;
    float float10;
    float float14;
    float float18;
    float float1C;
    float float20;
    float float24;
    float float28;
    float float2C;
    float float30;
    float float34;
    float float38;
    float float3C;
    float float40;
    float float44;
    float float48;
    float float4C;
    float float50;
    float float54;
    float float58;
    float float5C;
    u8 unknown60[0x40];
    s32 wordA0;
    u8 unknownA4[0x10];
    s32 wordB4;
    s32 wordB8;
    u8 unknownBC[0x110];
    s32 word1CC;
    s32 word1D0;
};

void sub_08053C14(float first, float second, float third)
{
    float firstResult, secondResult, thirdResult;
    struct FrameObject *objects;
    struct NumericView *work;
    u8 *record;
    u8 *records;
    struct FrameObject *object;
    u32 depth;
    s32 recordIndex;
    u8 *objectIndices;
    s32 *cursor;
    sub_08053C7C(first, second, third, &firstResult, &secondResult, &thirdResult);
    sub_08053DE0(firstResult, secondResult);
    objects = gFrameObjects;
    work = (struct NumericView *)gLaterBuffer_03005350;
    recordIndex = work->word1CC;
    records = gSetupPointer_03006D30;
    record = (u8 *)(recordIndex * 0x300 + (u32)records);
    cursor = (s32 *)(record + 0x20C);
    objectIndices = record + 0x2DC;
    object = &objects[objectIndices[*cursor]];
    depth = (s32)thirdResult;
    depth <<= 8;
    object->positionZ = (u8)object->positionZ | depth;
}
