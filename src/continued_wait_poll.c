#include "global.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_030055A0[];

struct ObjectEntry
{
    u16 identifier;
    u16 unknown02;
};

void sub_0804E5F0(u32 first, u32 second)
{
    u8 firstByte = first;
    u8 secondByte = second;
    s32 missing = 0;
    s32 progress = 0;
    s32 i;
    u8 *work = gUnknown_030057E0;

    switch (work[0xC93])
    {
    case 0:
        {
            const struct ObjectEntry *entries;
            const u8 *argument;
            i = 0;
            entries = (const struct ObjectEntry *)gLaterBuffer_030055A0;
            argument = work + 0xC94;
            for (; i < 4; i++)
            {
                u32 index = (u8)i;
                if (sub_0804DBF0(index) != -1)
                {
                    s32 entry = sub_0804DBF0(index);
                    entry += 79;
                    if (entries[entry].identifier)
                    {
                        if (secondByte == 1)
                            sub_080500BC((u8)(sub_0804DBF0(index) + 79),
                                        *argument, firstByte);
                        else
                            sub_08050124((u8)(sub_0804DBF0(index) + 79),
                                        *argument, firstByte);
                    }
                }
            }
            gUnknown_030057E0[0xC93]++;
            break;
        }
    case 1:
        {
            const struct ObjectEntry *entries;
            i = 0;
            entries =
                (const struct ObjectEntry *)gLaterBuffer_030055A0;
            for (; i < 4; i++)
            {
                s32 entry = sub_0804DBF0((u8)i);
                if (entry != -1)
                {
                    entry += 79;
                    if (entries[entry].identifier)
                        progress += sub_0805018C((u8)entry, secondByte);
                    else
                        progress++;
                }
                else
                    missing++;
            }
            if (missing == 4)
                sub_08050290();
            if (progress != 0)
                sub_08050290();
            break;
        }
    }
}
