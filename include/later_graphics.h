#ifndef GUARD_LATER_GRAPHICS_H
#define GUARD_LATER_GRAPHICS_H

#include "global.h"

void sub_080490E0(u16 *destination, u32 selector, u32 attributes);
/* Observed word argument slots; values are narrowed at entry. The last two
 * slots are supplied by callers but are not read by this implementation. */
void sub_08049110(u16 *destination, u32 selector, u32 attributes, u32 row,
                  u32 column, u32 unused5, u32 unused6);
void sub_08049140(const u16 *source, u16 *destination, s32 height, s32 width,
                  s32 maximumHeight, s32 stride, u32 tileOffset, u32 palette);
void sub_08049198(u32 index, const void *source);
void sub_08049344(u32 index);
void sub_08049318(void);
void sub_08049420(u32 index, u32 value);
void sub_080496EC(void);
void sub_080496F0(u32 index, const void *source);
void sub_08049714(void *destination, u32 size);
void sub_08049728(void *destination, u32 size, u32 value);
s32 sub_08049740(const void *first, const void *second, s32 size);
u32 sub_08049768(const void *source, s32 size);
void sub_080497C0(const void *source, void *destination, u32 size);

void sub_08049374(u32 index);
u32 sub_08049780(u32 range);

#endif
