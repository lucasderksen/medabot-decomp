#include "global.h"

/* Sound choices and one 16-color name-entry palette. */
const u8 gMain2SoundChoiceData_080AF8CA[3] __attribute__((aligned(1))) = { 0x09, 0x0A, 0x0B };

const u16 gNameEntryPalette_080AF988[16] = {
    0x7FFF, 0x0091, 0x031F, 0x7FDE, 0x7B7B, 0x45EF, 0x7C00, 0x6000, 0x001F, 0x001A, 0x439F, 0x2AFC, 0x1638, 0x0194, 0x3E73, 0x0048,
};

/* Three rows of masks consumed by the selector tile loop. */
const u16 gMain2TileMasks_080AF8B8[3][3] = {
    { 0xE000, 0x03C0, 0x000F },
    { 0x1C00, 0x0038, 0x0000 },
    { 0x6000, 0x0180, 0x0006 },
};

/* The following four bytes are shared with the neighboring mask object. */
const u32 gMain2BlendSteps_080AF868[20] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    9, 9, 8, 7, 6, 5, 4, 3, 2, 1,
};
