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

struct RecordProjectionView
{
    s32 word00;
    u8 unknown04[0x18];
    s32 word1C;
    u8 unknown20[0x44];
    s32 word64;
    u8 unknown68[0x38];
    float floatA0;
    u8 unknownA4[8];
    s32 wordAC;
    u8 unknownB0[0x130];
    s32 word1E0;
    u16 half1E4;
    u16 unknown1E6;
    u16 half1E8;
    u16 unknown1EA;
    s32 word1EC;
    u8 byte1F0;
    u8 unknown1F1[3];
    u8 byte1F4;
    u8 unknown1F5[3];
    s32 word1F8;
    s32 word1FC;
    s32 word200;
    u8 unknown204[8];
    s32 cursor;
    u8 unknown210[0xCC];
    u8 objectIndices[4];
    u16 xOffsets[4];
    u8 yOffsets[4];
    u8 unknown2EC[0x14];
};
struct ProjectedCursorView
{
    s32 first;
    s32 second;
    u8 unknown08[0x110];
    s32 recordIndex;
};
#define gRecordProjectionViews ((struct RecordProjectionView *)gSetupPointer_03006D30)
#define gNumericView (*(struct NumericView *)gLaterBuffer_03005350)
void sub_08053DE0(float first, float second)
{
    struct ProjectedCursorView *projected = (struct ProjectedCursorView *)(gLaterBuffer_03005350 + 0xB4);
    s32 *index;
    struct FrameObject *objects;
    s32 x;
    sub_08053D78(first, second, &projected->first, &projected->second);
    objects = gFrameObjects;
    index = &projected->recordIndex;
    {
        u32 selected = *index;
        struct RecordProjectionView *records = gSetupPointer_03006D30;
        struct RecordProjectionView *current = (struct RecordProjectionView *)(selected * 0x300 + (u32)records);
        s32 *cursorPointer = &current->cursor;
        u8 *objectIndices = current->objectIndices;
        s32 cursor;
        struct FrameObject *object;
        s32 coordinate;
        cursor = *cursorPointer;
        object = &objects[objectIndices[cursor]];
        coordinate = projected->first;
        coordinate += current->xOffsets[cursor];
        object->screenX = coordinate;
    }
    {
        u32 selected = *index;
        struct RecordProjectionView *records = gSetupPointer_03006D30;
        struct RecordProjectionView *current = (struct RecordProjectionView *)(selected * 0x300 + (u32)records);
        s32 *cursorPointer = &current->cursor;
        u8 *objectIndices = current->objectIndices;
        s32 cursor;
        struct FrameObject *object;
        s32 coordinate;
        cursor = *cursorPointer;
        object = &objects[objectIndices[cursor]];
        coordinate = projected->second;
        coordinate += current->yOffsets[cursor];
        object->screenY = coordinate;
    }
    {
    u32 selected = *index;
    struct RecordProjectionView *records = gSetupPointer_03006D30;
    struct RecordProjectionView *record = (struct RecordProjectionView *)(selected * 0x300 + (u32)records);
    if (record->word1EC && (u8)projected->second >= record->byte1F0 && (u8)projected->second <= record->byte1F4)
    {
        record->word00 = 2;
        gRecordProjectionViews[*index].wordAC = 0;
    }
    }
    {
    struct NumericView *work = (struct NumericView *)gLaterBuffer_03005350;
    s32 *contextIndex = &work->word1CC;
    u32 selected = *contextIndex;
    struct RecordProjectionView *records = gSetupPointer_03006D30;
    struct RecordProjectionView *record = (struct RecordProjectionView *)(selected * 0x300 + (u32)records);
    if (record->word1E0)
    {
        x = work->wordB4 & 0x1FF;
        if (x >= record->half1E4 && x <= record->half1E8)
        {
            record->word00 = 2;
            gRecordProjectionViews[gNumericView.word1CC].word64 = 0;
            gRecordProjectionViews[gNumericView.word1CC].word1C = 0;
        }
    }
    }
    {
    struct NumericView *work = (struct NumericView *)gLaterBuffer_03005350;
    s32 *contextIndex = &work->word1CC;
    u32 selected = *contextIndex;
    struct RecordProjectionView *records = gSetupPointer_03006D30;
    struct RecordProjectionView *record = (struct RecordProjectionView *)(selected * 0x300 + (u32)records);
    if (record->word1F8)
    {
        if (record->floatA0 <= (float)record->word1FC)
        {
            record->word00 = 2;
            gRecordProjectionViews[gNumericView.word1CC].wordAC = 0;
        }
        selected = *contextIndex;
        records = gSetupPointer_03006D30;
        record = (struct RecordProjectionView *)(selected * 0x300 + (u32)records);
        if (record->floatA0 >= (float)record->word200)
        {
            record->word00 = 2;
            gRecordProjectionViews[gNumericView.word1CC].wordAC = 0;
        }
    }
    }
}
