#include "global.h"
#include "frame.h"
#include "later_graphics.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_030055A0[];
extern const u8 *const gRecordByteTables_08404334[];

void sub_0804F5DC(void)
{
    u8 *objects;
    u8 *entries;
    u8 *buffer;
    const u8 *source;
    u32 rows, columns, value;
    sub_080505FC();
    objects = (u8 *)&gFrameObjects[49];
    sub_08049714(objects, 0x900);
    objects += 0xA80;
    sub_08049714(objects, 0x900);
    entries = gLaterBuffer_030055A0 + 49 * 4;
    sub_08049714(entries, 0x90);
    entries += 42 * 4;
    sub_08049714(entries, 0x90);
    sub_080506BC();
    buffer = gUnknown_030057E0 + 0x810;
    sub_08049714(buffer, 0x400);
    source = gRecordByteTables_08404334[buffer[-18]];
    rows = *(u16 *)(buffer - 14) / 2;
    columns = *(u16 *)(buffer - 16) / 2;
    sub_080497C0(source, buffer, rows * columns);
    buffer += 0x4AA;
    value = 1;
    *buffer = value;
    sub_080513C8(value);
    sub_08052784();
    sub_08050290();
}
