#include "compression.h"

u32 LeDecompressBytes(const u8 *source, void *destination, u32 size)
{
    u32 remaining;
    u8 *dst;
    const u8 *src;

    remaining = size;
    dst = destination;
    src = source + 6;
    while (remaining != 0)
    {
        u8 flags = *src++;
        u32 i;
        for (i = 0; i < 4 && remaining != 0; i++, flags >>= 2)
        {
            switch (flags & 3)
            {
            case 0:
            {
                s32 n = src[0] + (src[1] << 8);
                const u8 *from;
                do {
                src += 2;
                from = dst - ((n & 0xFFF) + 5);
                } while (0);
                n = ((u32)n >> 12) + 3;
                remaining -= n;
                for (n = n - 1; n != -1; n--)
                    *dst++ = *from++;
                break;
            }
            case 1:
            {
                s32 n = *src++;
                const u8 *from = dst - ((n & 3) + 1);
                n = ((u32)n >> 2) + 2;
                remaining -= n;
                for (n = n - 1; n != -1; n--)
                    *dst++ = *from++;
                break;
            }
            case 3:
                do {
                *dst++ = *src++;
                } while (0);
                *dst++ = *src++;
                *dst++ = *src++;
                remaining -= 3;
                break;
            case 2:
                *dst++ = *src++;
                remaining -= 1;
                break;
            }
        }
    }
    return size;
}
