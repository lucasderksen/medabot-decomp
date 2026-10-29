#include "global.h"
#include "frame.h"
#include "continued_commands.h"
#include "later_graphics.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_030055A0[];

struct SnapshotActionFlags
{
    u8 index:5;
    u8 unknown:1;
    u8 skip:1;
    u8 active:1;
} __attribute__((packed));

struct SnapshotWorkView
{
    u8 unknown00[0x7DC];
    u8 x;
    u8 y;
    struct SnapshotActionFlags flags;
    u8 selector;
};

struct SnapshotMetadata
{
    u16 value;
    u16 unknown02;
};

void sub_080505FC(void)
{
    s32 i;
    sub_08049714(gUnknown_030057E0 + 0x7DC, 0x20);
    for (i = 0; i <= 5; i++)
    {
        struct SnapshotMetadata *metadata = (struct SnapshotMetadata *)gLaterBuffer_030055A0;
        u32 frameIndex = i + 79;
        if (metadata[frameIndex].value)
        {
            struct FrameObject *objects = gFrameObjects;
            struct FrameObject *object = &objects[frameIndex];
            u32 x = sub_0805273C((u16)(object->positionX.value >> 8));
            u8 *base = gUnknown_030057E0;
            struct SnapshotWorkView *work = (struct SnapshotWorkView *)(base + i * 4);
            work->x = x;
            work->y = sub_08052760((u16)(object->positionY >> 8));
            work->selector = ((object->byte2B & 15) << 4) | (object->commandDelay & 3);
            work->flags.index = i;
            work->flags.skip = object->unknown2C[1] & 1;
            work->flags.active = 1;
        }
    }
}
