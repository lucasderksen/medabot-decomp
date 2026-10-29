#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "display_helpers.h"
#include "object_helpers.h"
#include "tile_text.h"
#include "initialization.h"


void sub_08014E7C(void)
{
    sub_0803F624(gSetupBuffer_03000590, 0x600, 0);
}

void sub_08014EC8(void)
{
    sub_08014EE8();
    sub_08014F44();
    sub_08014F90(0, gState0TransferWork.bytes[0x5A]);
}
