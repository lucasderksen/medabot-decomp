#ifndef GUARD_OBJECT_NUMERIC_HELPERS_H
#define GUARD_OBJECT_NUMERIC_HELPERS_H
#include "global.h"
void sub_08048864(u32 index, u32 flags, u32 frame, u32 palette, u32 selector);
void sub_08048888(u32 index);
s32 sub_080488AC(s32 value);
s32 sub_08048B88(s32 numerator, s32 denominator);
s32 sub_08048BA0(s32 denominator);
void sub_08048BB8(void);
void sub_08048CA8(const u16 *source, u16 *destination, s32 rows, s32 columns,
                 s32 maximumRows, s32 stride, u32 addition);
void sub_08048A8C(void);
/* Copied callee: observed word arguments and explicit narrowing by callers. */
s32 sub_08048B70(s32 left, s32 right);

#endif
