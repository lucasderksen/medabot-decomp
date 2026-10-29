#include "state0_next_helpers.h"
#include "main.h"
#include "interrupts.h"


/* Adjacent referenced bases ACE14 and ACE24 establish four pointer words. */
const MainCallback gState0RowObjectCallbacks_083ACE14[4]
    __attribute__((section(".rodata.state0_row_object_callbacks"))) =
{
    sub_08010170,
    sub_080101E8,
    sub_0801022C,
    DummyInterruptHandler,
};
