#include "bg_scroll.h"
#include "main.h"
#include "input.h"
#include "display_helpers.h"
#include "frame_objects.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"

/* Partial backing access model over canonical objects; no new data extent. */
struct ObservedActionFrameBacking
{
    u8 unknown000[0x842];
    u16 screenX842;
    u8 unknown844[4];
    u8 scaleX848;
    u8 unknown849[0x19];
    u8 commandStopped862;
};

struct ObservedActionWorkBacking { u8 unknown00[0xAA]; u8 stateAA; };

void sub_0801C988(void)
{
    struct ObservedActionFrameBacking *objects = (void *)gFrameObjects;
    objects->scaleX848 += 8;
    if (objects->scaleX848 == 64)
    {
        struct ObservedActionWorkBacking *work = (void *)&gState0TransferWork;
        if (work->stateAA <= 31)
            sub_08074DE0(63);
        work->stateAA++;
    }
}

void sub_0801CB24(void)
{
    const void *const *messages = gState0PartMessages_083C6F68;
    u8 *work = gState0TransferWork.bytes;
    const void *message = messages[work[0xD0]];
    u8 *scratch = gDebugMenuTextBuffer;
    sub_0803F63C(message, scratch, 14);
    scratch += 20;
    sub_08041490(scratch, *(u16 *)&work[0xC8], 53);
    work[0xA6] = 18;
    work[0xAA]++;
}

void sub_0801CBA4(void)
{
    u8 *work = gState0TransferWork.bytes;
    u8 *destination;
    u32 state;
    if (work[0xD1])
    {
        sub_08074DE0(59);
        sub_08035194(work[0x87]);
        destination = &work[0xA6];
        *destination = 19;
        destination += 4;
        state = 26;
    }
    else
    {
        destination = &work[0xAA];
        state = 32;
    }
    *destination = state;
}

void sub_0801CBE4(void)
{
    u8 *records = gSetupBuffer_03000590;
    u8 *work = gState0TransferWork.bytes;
    u32 row = work[0x87];
    u8 *destination;
    u32 state;
    if (records[row * 256 + 0x59] == 0)
    {
        sub_08035234(row);
        destination = &work[0xAA];
        state = 47;
    }
    else
    {
        destination = &work[0xAA];
        state = 32;
    }
    *destination = state;
}

void sub_0801CC58(void)
{
    u8 *work = gUnknown_03000440;
    u8 *counter = &work[0x84];
    sub_080353AC(*counter);
    (*counter)++;
    if (*counter > 29)
    {
        u16 position;
        sub_08074DE0(63);
        gBgScroll3.y = 0;
        *counter = 0;
        position = ((struct ObservedActionFrameBacking *)gFrameObjects)->screenX842;
        *(u16 *)&work[0x86] = position;
        gState0TransferWork.bytes[0xAA]++;
    }
}
