#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_callbacks.h"
#include "equipment_helpers.h"
#include "tile_text.h"
#include "frame.h"

extern u8 gUnknown_030057E0[];

void sub_0801214C(void)
{
    if (gUnknown_03000440[0x132] == 0 && sub_08042278(50)
        && gUnknown_030057E0[0xC2D] == 0)
    {
        struct FrameObject *object = gFrameObjects;
        object->flags = 0xC404;
        object->screenX = 8;
        object->screenY = 80;
        object->palette = 11;
        object->priority = 0xC0;
        object->frameAndGroup = 0x700;
    }
}

void sub_080121A8(void)
{
    u8 *work = gState0TransferWork.bytes;
    sub_0803F63C(gState0ScrollControls_083C3C84[work[0x38]], work + 0x39, 8);
}

void sub_080121CC(void)
{
    s32 threshold = sub_080121F0();
    if (threshold < sub_08043C94() || sub_08012234() == 0)
        sub_080122F4(3);
}
