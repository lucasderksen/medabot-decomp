#include "compression.h"

/* 0x080009BC: route memory-mapped destinations to halfword writes. */
u32 LeDecompress(const u8 *source, void *destination)
{
    if (source[0] != 'L' || source[1] != 'e')
        return 0;

    if ((u32)destination - 0x04000001u <= 0x03FFFFFEu)
        return LeDecompressVram(source, destination);
    else
    {
        u32 size = source[2] | (source[3] << 8) | (source[4] << 16);
        return LeDecompressBytes(source, destination, size);
    }
}
