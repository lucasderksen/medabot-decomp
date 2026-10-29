#include "continued_commands.h"
#include "frame.h"
#include "later_graphics.h"
#include "object_numeric_helpers.h"
#include "post_dispatch.h"

extern u8 gUnknown_030057E0[];
extern u8 gContinuedRecordBuffer_030063F0[];
extern u8 gContinuedByte_03002B64;
extern u8 gLaterBuffer_03006D20[];
extern const u8 gContinuedLookup_083D2A30[];
extern const u8 gContinuedLookup_083D262C[];
extern void sub_0804D980(void *record);

/* Partial observed flag byte; bit meanings and record count are provisional. */
struct RecordFlagsByte
{
    u8 slot : 5;
    u8 unknown5 : 1;
    s8 active : 1;
    u8 unknown7 : 1;
} __attribute__((packed));

struct CommandRecord8
{
    u8 unknown00[2];
    u16 word02;
    struct RecordFlagsByte flags04;
    u8 unknown05[3];
};

void sub_0804BB14(void)
{
    u8 *buffer;
    u8 *data;
    struct FrameObject *objects;
    sub_0804D8CC(4);
    gContinuedByte_03002B64 = 0;
    buffer = gContinuedRecordBuffer_030063F0;
    sub_080497C0(buffer, buffer + 16, 8);
    sub_08049714(buffer, 8);
    objects = gFrameObjects;
    objects[47].unknown23[5] = 0;
    objects[47].unknown23[3] = 0;
    objects[47].unknown23[4] = 0;
    data = buffer + 0x4F;
    *data = 1;
    data += 0x35;
    sub_080500BC(47, data[objects[47].unknown23[3]],
                  gContinuedLookup_083D2A30[buffer[0x4C]]);
    sub_08052E0C(objects[47].commandDelay);
    buffer[0x79] = 1;
}

void sub_0804BC6C(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *selection = work + 0xCB4;
    u8 *flags = work + *selection * 8 + 0x5E0;
    *flags &= 0x7F;
    if ((s8)(work[*selection * 8 + 0x5E0] * 2) < 0)
    {
        sub_08048888((u8)(((struct RecordFlagsByte *)(work + *selection * 8 + 0x5E0))->slot + 49));
        sub_08048888((u8)(((struct RecordFlagsByte *)(work + *selection * 8 + 0x5E0))->slot + 91));
    }
}

void sub_0804BD70(void)
{
    u8 *work, *high, *low;
    u32 value, part;
    u16 *destination;
    u32 zero;
    sub_0804D8CC(2);
    work = gUnknown_030057E0;
    high = work + 0xC94;
    part = *high << 8;
    low = work + 0xC95;
    value = *low;
    value |= part;
    destination = (u16 *)(work + 0xC8E);
    zero = 0;
    *destination = value;
    *(u16 *)(work + 0xC8A) = zero;
    {
    u32 highPart = *high << 8;
    u32 decoded = *low;
    decoded |= highPart;
    if (sub_0804D938(decoded))
    {
        u32 highPart = *high << 8;
        u32 decoded = *low;
        decoded |= highPart;
        work[0xCB4] = sub_0804D8F4(decoded);
    }
    }
}

void sub_0804BF34(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *row = work + work[0xCB4] * 8;
    if ((*(u16 *)(row + 0x5DE) & 0xFFF) == *(u16 *)(work + 0xC8E))
    {
        u8 *buffer = gLaterBuffer_03006D20;
        struct FrameObject *objects;
        u32 zero, y;
        buffer[10] = ((struct RecordFlagsByte *)(row + 0x5E0))->slot + 49;
        objects = gFrameObjects;
        y = objects[buffer[10]].positionY >> 8;
        zero = 0;
        *(u16 *)(buffer + 8) = y;
        objects[buffer[10]].unknown23[5] = zero;
        sub_08047BA8(112);
        work[0xC89] = 1;
    }
}

void sub_0804BFB4(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    u8 *row;
    work[0xC94] = value;
    row = work + work[0xCB4] * 8;
    if ((*(u16 *)(row + 0x5DE) & 0xFFF) == *(u16 *)(work + 0xC8E))
    {
        u8 *buffer = gLaterBuffer_03006D20;
        buffer[10] = ((struct RecordFlagsByte *)(row + 0x5E0))->slot + 49;
        buffer[0] = value;
        buffer[1] = 0;
        buffer[2] = 8;
        buffer[3] = 8;
        work[0xC89] = 1;
    }
}
