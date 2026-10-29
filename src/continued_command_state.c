#include "global.h"
#include "post_dispatch.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];
extern u8 gContinuedOtherWork_030057A0[];
extern const void *const gStateScripts_084144B4[];
extern const void *const *const gStateScriptTables_0847DF24[];

struct OtherCommandWork
{
    u8 unknown00[0x2E];
    u16 selection;
    u16 entry;
};

void sub_0804DC38(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *state = work + 0xC93;
    switch (*state)
    {
    case 0:
        {
            struct OtherCommandWork *other;
            u32 high, low;
            sub_08047C00();
            other = (struct OtherCommandWork *)gContinuedOtherWork_030057A0;
            other->selection = work[0xC94] - 2;
            high = work[0xC95] << 8;
            low = work[0xC96];
            low |= high;
            other->entry = low;
            if (sub_0804B738())
                sub_08050290();
            (*state)++;
            break;
        }
    case 1:
        {
            const void *const *scripts;
            u32 high, low, index;
            if (work[0xC94] <= 1)
                scripts = gStateScripts_084144B4;
            else
                scripts = gStateScriptTables_0847DF24[work[0xC94] - 2];
            high = work[0xC95] << 8;
            low = work[0xC96];
            index = high | low;
            if (sub_08047C24(0, 0, 0, scripts[index]))
                sub_08050290();
            break;
        }
    }
}
