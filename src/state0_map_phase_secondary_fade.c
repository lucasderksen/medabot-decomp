#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "main.h"
#include "object_helpers.h"


void sub_08013DE4(void)
{
    u8 counter;
    sub_080182D0();
    sub_08017CE8();
    sub_08018218();
    sub_0801830C();
    counter = *(u8 *)&gFrameCounter;
    sub_08041C14(8, counter, sub_0801827C());
    sub_080182AC();
    if (sub_080425DC())
        gUnknown_0300137C++;
}
