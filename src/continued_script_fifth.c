#include "global.h"
#include "continued_commands.h"
#include "later_graphics.h"

extern u8 gUnknown_030057E0[];

/* Private access view for offset 4 only; not indexed or a complete record layout.
 * Its union has compiler-specific alignment; selected rows use byte arithmetic. */
struct ScriptStatusRecordView
{
    u8 bytes[4];
    union { u8 value; struct { u8 selector:5; u8 unknown:3; } bits; } status;
    u8 unknown[3];
};

struct ScriptStatusByte
{
    u8 selector:5;
    u8 unknown:3;
} __attribute__((packed));

void sub_0804CF5C(void)
{
    u8 *work;
    sub_0804D8CC(3);
    work = gUnknown_030057E0;
    switch (work[0xC94])
    {
    case 0:
        {
            u8 *argument = work + 0xC96;
            if (sub_0804DBF0(*argument) != -1)
                sub_0804D9F8((u8)(sub_0804DBF0(*argument) + 79));
            break;
        }
    case 1:
        {
            u32 high = work[0xC95] << 8;
            u32 code = work[0xC96];
            code |= high;
            if (code != 0)
            {
                const struct ScriptStatusRecordView *record = sub_0804D938(code);
                if (record)
                    sub_0804D9F8((u8)(record->status.bits.selector + 49));
            }
            else
            {
                const struct ScriptStatusByte *status = (const struct ScriptStatusByte *)(work + (work[0xCB4] << 3) + 0x5E0);
                sub_0804D9F8((u8)(status->selector + 49));
            }
            break;
        }
    }
}
