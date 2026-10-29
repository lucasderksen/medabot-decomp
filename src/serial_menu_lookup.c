#include "global.h"

const u8 gCopiedMasks_080AF864[4] = { 1, 3, 7, 15 };


/* Stored selector lookup bytes; callers form unchecked ROM addresses. */
const u8 gMenuByteLookup_080AFB88[16] __attribute__((aligned(1))) = {
    0x57, 0x57, 0x57, 0x57, 0x57, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x56, 0x44, 0x44, 0x1F, 0x00,
};
