#include "global.h"

/* Signed vertical offsets selected by the low six bits of commandOffset. */
const s8 gFrameMotionOffsets_080B00C8[64] = {
     4,  3, -2, -1,  2,  1, -2, -1,
    -2,  0,  0, -1,  4,  3,  2,  1,
     4,  3, -4, -3, -4, -3,  2,  1,
     4,  3, -2, -1,  4,  3, -4, -3,
     0,  0, -4, -3, -2, -1, -4, -3,
    -2, -1, -4, -3,  2,  1,  4,  3,
     2,  1,  0,  0,  4,  3, -4, -3,
     2,  1,  4,  3, -4, -3,  0,  0,
};
