/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_display.h"
#include "state0_work.h"


u32 LeDecompressVram(const u8 *source, void *destination);

u32 LeDecompressVram(const u8 *source, void *destination) {

    u32 size;
    u32 remaining;
    u8 *dst;
    const u8 *src;
    s32 n;
    const u8 *from;

    if (source[0] != 'L' || source[1] != 'e')
        return 0;
    size = source[2] | (source[3] << 8) | (source[4] << 16);
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
                n = src[0] + (src[1] << 8);
                src += 2;
                from = dst - ((n & 0xFFF) + 5);
                n = ((u32)n >> 12) + 3;
                remaining -= n;
                for (n = n - 1; n != -1; n--)
                {
                    u16 *p = (u16 *)((u32)dst & ~1);
                    u16 s = *(u16 *)((u32)from & ~1);
                    u16 old = *p;
                    if ((u32)from & 1)
                    {
                        if ((u32)dst & 1)
                            *p = (old & 0xFF) | (s & 0xFF00);
                        else
                            *p = (old & 0xFF00) | (s >> 8);
                    }
                    else
                    {
                        if ((u32)dst & 1)
                            *p = (old & 0xFF) | (s << 8);
                        else
                            *p = (old & 0xFF00) | (s & 0xFF);
                    }
                    dst++;
                    from++;
                }
                break;
            }
            case 1:
            {
                n = *src++;
                from = dst - ((n & 3) + 1);
                n = ((u32)n >> 2) + 2;
                remaining -= n;
                for (n = n - 1; n != -1; n--)
                {
                    u16 *p = (u16 *)((u32)dst & ~1);
                    u16 s = *(u16 *)((u32)from & ~1);
                    u16 old = *p;
                    if ((u32)from & 1)
                    {
                        if ((u32)dst & 1)
                            *p = (old & 0xFF) | (s & 0xFF00);
                        else
                            *p = (old & 0xFF00) | (s >> 8);
                    }
                    else
                    {
                        if ((u32)dst & 1)
                            *p = (old & 0xFF) | (s << 8);
                        else
                            *p = (old & 0xFF00) | (s & 0xFF);
                    }
                    dst++;
                    from++;
                }
                break;
            }
            case 3:
                {
                    u16 *q = (u16 *)((u32)dst & ~1);
                    u16 value = *q;
                    if ((u32)dst & 1)
                        *q = (value & 0xFF) | (*src << 8);
                    else
                        *q = (value & 0xFF00) | *src;
                }
                dst++;
                src++;
                {
                    u16 *q = (u16 *)((u32)dst & ~1);
                    u16 value = *q;
                    if ((u32)dst & 1)
                        *q = (value & 0xFF) | (*src << 8);
                    else
                        *q = (value & 0xFF00) | *src;
                }
                dst++;
                src++;
                {
                    u16 *q = (u16 *)((u32)dst & ~1);
                    u16 value = *q;
                    if ((u32)dst & 1)
                        *q = (value & 0xFF) | (*src << 8);
                    else
                        *q = (value & 0xFF00) | *src;
                }
                dst++;
                src++;
                remaining -= 3;
                break;
            case 2:
                {
                    u16 *q = (u16 *)((u32)dst & ~1);
                    u16 value = *q;
                    if ((u32)dst & 1)
                        *q = (value & 0xFF) | (*src << 8);
                    else
                        *q = (value & 0xFF00) | *src;
                }
                dst++;
                src++;
                remaining -= 1;
                break;
            }
        }
    }
    return size;
}
