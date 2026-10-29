#include "continued_commands.h"
#include "global.h"
extern u8 gUnknown_030057E0[];
struct Record8 { u8 first, second; u16 identifier; u8 unknown4[4]; };
struct SearchWork { u8 unknown00[0x5DC]; struct Record8 records[64]; };
s32 sub_0804D8F4(u32 identifier)
{
    u16 narrowed = identifier;
    s32 i;
    struct SearchWork *work;
    i = 0;
    work = (struct SearchWork *)gUnknown_030057E0;
    for (; i < 64; i++)
    {
        u32 value = work->records[i].identifier & 0xFFF;
        if (value == narrowed)
            return i;
    }
    if (i == 64)
        return -1;
}

void * sub_0804D938(u32 identifier)
{
    u16 narrowed = identifier;
    s32 i;
    struct SearchWork *work;
    i = 0;
    work = (struct SearchWork *)gUnknown_030057E0;
    for (; i < 64; i++)
    {
        u32 value = work->records[i].identifier & 0xFFF;
        if (value == narrowed)
            return &work->records[i];
    }
    if (i == 64)
        return 0;
}
