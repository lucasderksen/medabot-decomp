#include "global.h"
#include "continued_commands.h"
#include "later_graphics.h"
#include "background_state.h"
#include "continued_scene_records.h"

struct RandomSelectionWork { u32 unknown00; u32 phase; };

void sub_080521A8(void)
{
    struct SelectionRecord *record = gSelectionRecords_03005DBC;
    if ((((struct RandomSelectionWork *)&gBackgroundState_03005310)->phase & 3) == 0)
    {
        union SelectionFlags flags;
        u8 index;
        record += (u8)sub_08049780(64);
        flags = record->flags;
        if ((flags.value & 0x80) && (record->attributes >> 12) == 0)
        {
            index = flags.bits.index + 49;
            sub_0805218C(index, (u8)sub_08049780(4), record);
        }
    }
}
