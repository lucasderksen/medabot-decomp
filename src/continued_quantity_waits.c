#include "global.h"
#include "continued_commands.h"
#include "continued_graphics.h"
#include "post_dispatch.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_030055A0[];

void sub_0804EF5C(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_08047C00();
        sub_08047BA8(14);
        if (sub_08047E30())
            *state = 1;
        else
        {
            sub_08047E3C(work[0xC94]);
            *state = 2;
        }
        break;
    case 1:
        if (sub_08047C24(0, 0, 0, gQuantityScripts_0847E388[30]))
            sub_08050290();
        break;
    case 2:
        if (sub_08047C24(0, 0, 0, gQuantityScripts_0847E388[work[0xC94] + 31]))
            sub_08050290();
        break;
    }
}

void sub_0804EFFC(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        sub_08049D90(32767, 0.0f, 32.0f, 8.0f);
        goto increment;
    case 1:
        if (!sub_08049E08(32767))
            break;
        sub_08049D18(32767, 32.0f, 0.0f, 8.0f);
increment:
        (*state)++;
        break;
    case 2:
        if (sub_08049E08(32767))
        {
            work[0xC94]--;
            if (work[0xC94])
                *state = 0;
            else
                sub_08050290();
        }
        break;
    }
}

struct ObjectEntry
{
    u16 identifier;
    u16 unknown02;
};

void sub_0804F0A4(void)
{
    s32 missing = 0;
    s32 progress = 0;
    s32 i = 0;
    const struct ObjectEntry *entries =
        (const struct ObjectEntry *)gLaterBuffer_030055A0;
    for (; i < 4; i++)
    {
        u32 index = (u8)i;
        if (sub_0804DBF0(index) != -1)
        {
            s32 entry = sub_0804DBF0(index);
            entry += 79;
            if (entries[entry].identifier)
                progress += sub_0805082C((u8)(sub_0804DBF0(index) + 79));
            else
                missing++;
        }
    }
    if (missing == 4)
        progress = 1;
    if (progress != 0)
        sub_08050290();
}
