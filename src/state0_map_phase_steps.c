#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "display_effects.h"
#include "coordinate_helpers.h"
#include "display_helpers.h"


void sub_08012B40(void)
{
    u8 *base = gUnknown_03000440;
    u8 *counter = base;
    counter += 0x84;
    if (*counter <= 8)
    {
        BlendBgPaletteBanksNow(0, 32 - *counter * 4, 0xFFFF);
        BlendObjPaletteBanksNow(0, 32 - *counter * 4, 0xFFFF);
        (*counter)++;
    }
    else
        gNestedCallbackIndex++;
}

void sub_08012B94(void)
{
    sub_080195C0();
    if (gUnknown_03000440[0x89] != 1)
        sub_0801531C(3);
    gNestedCallbackIndex++;
}

void sub_08012BC0(void)
{
    sub_080195C0();
    sub_08016370(gState0TransferWork.bytes[0x80]);
    gNestedCallbackIndex++;
}

void sub_08012BE4(void)
{
    sub_080195C0();
    if (sub_08016438(gState0TransferWork.bytes[0x80]))
        gNestedCallbackIndex++;
}

void sub_08012C0C(void)
{
    u8 *selection;
    sub_080195C0();
    selection = gState0TransferWork.bytes;
    selection += 0x80;
    CycleActionSpriteFrames(*selection);
    sub_08015A90();
    sub_08015B3C(*selection);
    sub_08015BA8(*selection);
    sub_08015C40(*selection);
    sub_08015E68(*selection);
    sub_08015F24();
    sub_08015F78();
    sub_08043240(*selection * 4 + 0x5A, 8);
    gNestedCallbackIndex++;
}
