#include "frame_objects.h"
#include "display_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"

void sub_080339F4(void)
{
    sub_0801C4FC();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

void sub_08033A10(void)
{
    sub_0801D2F0();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

void sub_08033A78(void)
{
    sub_0801D380();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

void sub_08033A94(void)
{
    sub_0801D40C();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}

void sub_08033AB0(void)
{
    sub_0801D580();
    if (gState0TransferWork.bytes[0xB5])
        sub_08034F08();
}
