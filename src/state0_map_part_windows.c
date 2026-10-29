#include "state0_next_helpers.h"
#include "state0_work.h"
#include "utility_helpers.h"
#include "frame.h"

void sub_080123A0(void)
{
    u8 *work = gState0TransferWork.bytes;
    switch (work[0x168])
    {
    case 0:
        sub_08044934(0, work[0x169], 0, 194, 80, 1, 8, 0, 1);
        break;
    case 1:
        sub_08044934(0, work[0x169], 1, 204, 56, 1, 7, 0, 1);
        break;
    case 2:
        sub_08044934(0, work[0x169], 2, 184, 56, 1, 6, 1, 1);
        break;
    case 3:
        sub_08044934(0, work[0x169], 3, 194, 46, 1, 5, 0, 1);
        break;
    }
}

void sub_08012468(void)
{
    if (gState0TransferWork.bytes[0x16A])
    {
        u8 *object = (u8 *)gFrameObjects;
        u8 *direction = object + 0x68;
        if (*direction == 0)
        {
            object[0x49] += 2;
            if (object[0x49] == 128)
                *direction = 1;
        }
        else
        {
            object[0x49] -= 2;
            if (object[0x49] == 64)
                *direction = 0;
        }
    }
}

void sub_080124B8(void)
{
    u8 *work;
    sub_080445F4();
    work = gState0TransferWork.bytes;
    switch (work[0x168])
    {
    case 0:
        sub_08044934(0, work[0x169], 0, 194, 60, 1, 8, 0, 0);
        break;
    case 1:
        sub_08044934(0, work[0x169], 1, 204, 40, 1, 7, 0, 0);
        break;
    case 2:
        sub_08044934(0, work[0x169], 2, 184, 40, 1, 6, 1, 0);
        break;
    case 3:
        sub_08044934(0, work[0x169], 3, 194, 30, 1, 5, 0, 0);
        break;
    }
}
