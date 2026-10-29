/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "frame_command_data.h"
#include "frame_objects.h"
#include "graphics.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Main2PartContext
{
    u8 unknown00[5];
    u8 byte05;
    u8 unknown06[0x13];
    u8 selection19;
    u8 row1A;
    u8 unknown1B;
    u32 total1C;
    u8 count20;
};
struct Main2PartRecord
{
    u16 identifier;
    u8 byte2;
    u8 byte3;
    u32 value;
};

extern u32 gPostDispatchWord_03002B70;

void sub_08062614(void);

void sub_08062614(void) {

    s8 i;
    u32 money;

    if (sub_08041674() == 0)
        return;
    gState0TypedWork.bytes[0x84] = 0;
    gState0TypedWork.bytes[0x1B] = 0;
    if (gState0TypedWork.bytes[0x2A] == 0)
    {
        if (((struct Main2PartContext *)gMainContextPointer_03006F74)->byte05 == 0)
        {
            gPostDispatchWord_03002B70 -= ((struct Main2PartContext *)gMainContextPointer_03006F74)->total1C;
            for (i = 0; i <= 0x77; i++)
            {
                u8 *slot;
                struct Main2PartRecord *records = (struct Main2PartRecord *)0x02040000;
                slot = &gObjectHalfwordBytes[records[i].identifier * 2 + ((struct Main2PartContext *)gMainContextPointer_03006F74)->selection19 * 0xF0];
                *slot += ((u8 *)0x02023000)[i];
            }
        }
        else
        {
            money = gPostDispatchWord_03002B70 + ((struct Main2PartContext *)gMainContextPointer_03006F74)->total1C;
            if (money < 99999)
                gPostDispatchWord_03002B70 = money;
            else
                gPostDispatchWord_03002B70 = 99999;
            for (i = 0; i <= 0x77; i++)
            {
                u8 *slot;
                struct Main2PartRecord *records = (struct Main2PartRecord *)0x02040000;
                slot = &gObjectHalfwordBytes[records[i].identifier * 2 + ((struct Main2PartContext *)gMainContextPointer_03006F74)->selection19 * 0xF0];
                *slot -= ((u8 *)0x02023000)[i];
            }
        }
        sub_08040D0C(0, 7);
        sub_08041164(gDebugMenuTextBuffer, gPostDispatchWord_03002B70);
        sub_08040DB8(gDebugMenuTextBuffer, 0, 0x15, 1, 7, 15, 1, 0);
        gDebugMenuTextBuffer[-0x1A] = 0;
    }
    gUnknown_0300137C++;
}
