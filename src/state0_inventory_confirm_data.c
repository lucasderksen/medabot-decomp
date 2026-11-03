

#include "state0_inventory_confirm.h"
#include "main_callbacks.h"

void ShrinkObject7ToHidden(void);
void sub_0800B858(void);
void DummyInterruptHandler(void);

/* Eight observed cursor positions, followed by a separately referenced table. */
const u16 gState0CursorCoordinates_083ACA2C[16] __attribute__((section(".rodata.confirm_coordinates"))) = {
    8, 72, 8, 96, 120, 72, 120, 96,
    8, 120, 8, 144, 120, 120, 120, 144
};

const MainCallback gState0ConfirmCallbacks_083ACA4C[4] __attribute__((section(".rodata.confirm_callbacks"))) = {
    sub_0800B79C, ShrinkObject7ToHidden, sub_0800B858, DummyInterruptHandler
};
