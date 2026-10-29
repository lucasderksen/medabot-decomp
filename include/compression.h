#ifndef GUARD_COMPRESSION_H
#define GUARD_COMPRESSION_H

#include "global.h"

/* Descriptive names for the game's custom six-byte "Le" format. */
u32 LeDecompress(const u8 *source, void *destination);
u32 LeDecompressBytes(const u8 *source, void *destination, u32 size);
u32 LeDecompressVram(const u8 *source, void *destination);

void LZ77UnCompVram(const void *source, void *destination);
extern const u8 gSetupCompressed_085FB6A4[];
void LZ77UnCompWram(const void *source, void *destination);
#endif
