#include "global.h"

/* Alignment after the last consumed LZ77 stream, outside its bytecode. */
const u8 gFinalLzAlignment_087F4442[2] __attribute__((aligned(1))) = { 0, 0 };

/* Sixteen-color bank transferred by sub_0806E7EC; ignored high bits retained. */
const u16 gBackgroundPalette_087F4444[16] __attribute__((aligned(1))) = {
    0x83E0, 0x98C6, 0x6740, 0x6739, 0xB5AD, 0x6F7B, 0x4E73, 0xDAD6,
    0x7FFE, 0xF39C, 0x676A, 0x73B7, 0x7392, 0x7BDD, 0xA94A, 0xFFFF
};

/* Cartridge trailing zero fill. This is ROM padding, not executable code. */
const u8 gRomTailZeroPadding_087F4464[48028] __attribute__((aligned(1))) = { 0 };
