#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "coordinate_helpers.h"


void sub_08012F00(void)
{
    {
        u8 *work;
        u8 *selection;
        sub_080195C0();
        work = gState0TransferWork.bytes;
        selection = work + 0x80;
        sub_080164F4(*selection);
        sub_080432A0(*selection * 4 + 0x5A, *selection, 0);
        switch (work[0x81])
        {
        case 0:
            sub_08015564(*selection, work[0x82]);
            break;
        case 1:
            {
                u8 *amount = work + 0x82;
                if (*amount != 0)
                    sub_08015668(*selection, *amount - 1);
                else
                    sub_08015564(*selection, 0);
            }
            break;
        default:
            sub_08015358(*selection);
            break;
        }
    }
    {
        u8 *work = gState0TransferWork.bytes;
        u8 *selection = work + 0x80;
        u32 selected = *selection;
        u8 component = selected % 3u;
        sub_08015A00(selected, 0x28, component * 24 + 0x24);
        work[0x81] = 0;
        work[0x82] = 0;
        (*selection)++;
        if (work[0x84] == 0)
        {
            if (*selection != 3 && *selection < work[0x5A])
                gUnknown_0300137C = 4;
            else if (gUnknown_03000440[0x89] != 1)
                gUnknown_0300137C = 64;
            else
                gUnknown_0300137C = 144;
        }
        else
            gUnknown_0300137C++;
    }
}

void sub_08012FF8(void)
{
    sub_080195C0();
    sub_08018900(gState0TransferWork.bytes[0x87]);
    sub_08018AB4(0);
    if (gUnknown_03000440[0x89] != 1)
        gUnknown_0300137C = 69;
    else
        gUnknown_0300137C = 160;
}
