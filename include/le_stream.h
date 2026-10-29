#ifndef GUARD_LE_STREAM_H
#define GUARD_LE_STREAM_H

/* Native Le bytecode: four low-to-high two-bit commands per flag byte. */
enum LeCommand { LE_OP_FAR, LE_OP_NEAR, LE_OP_BYTE, LE_OP_TRIPLE };
#define LE_HEADER(size, reserved) 'L', 'e', ((size) & 255), (((size) >> 8) & 255), (((size) >> 16) & 255), (reserved)
#define LE_FLAGS(a, b, c, d) ((a) | ((b) << 2) | ((c) << 4) | ((d) << 6))
#define LE_FAR_WORD(distance, count) ((((count) - 3) << 12) | ((distance) - 5))
#define LE_FAR(distance, count) (LE_FAR_WORD(distance, count) & 255), (LE_FAR_WORD(distance, count) >> 8)
#define LE_NEAR(distance, count) ((((count) - 2) << 2) | ((distance) - 1))
#define LE_BYTE(value) (value)
#define LE_TRIPLE(a, b, c) (a), (b), (c)

#endif
