#include "state0_work.h"
#include "tile_text.h"

/* Keep the full-segment count and partial tile entry in the original
 * halfword local. Re-read the amount after drawing the full segments. */
void sub_0803EA38(void) {

    u16 amount;
    u32 i;
    u32 segments;

    segments = 0;
    amount = gState0TransferWork.bytes[0x1A0] >> 3;
    i = 0;
    while (i < amount) {
        sub_08042698(1U, 1U, segments + 7, 0x12U, (u32) *(volatile u16 *)0x0400000A, 0x53D8U);
        segments += 1;
        i += 1;
    }
    amount = gState0TransferWork.bytes[0x1A0];
    amount &= 7;
    if (amount != 0) {
        sub_08042698(1U, 1U, segments + 7, 0x12U, (u32) *(volatile u16 *)0x0400000A, (amount |= 0x53D0));
        segments += 1;
    }
    i = segments;
    if (i <= 0xBU) {
        do {
            sub_08042698(1U, 1U, segments + 7, 0x12U, (u32) *(volatile u16 *)0x0400000A, 0x53D0U);
            segments += 1;
            i += 1;
        } while (i <= 0xBU);
    }
}
