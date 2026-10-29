#ifndef GUARD_UTILITY_HELPERS_H
#define GUARD_UTILITY_HELPERS_H
#include "global.h"

void sub_08044094(void);
u32 sub_080440B4(void);
u32 sub_080440D4(void);
void sub_08044100(void);
void sub_08044118(u32 width, u32 height, u32 x, u32 y, u32 control, u16 *destination);
void sub_08044160(u32 width, u32 height, u32 x, u32 y, u32 control, const u16 *source);
void sub_080441A8(const void *source);
void sub_080441B8(void);
void sub_0804422C(u32 objectIndex);
u32 sub_080442B4(s32 x1, s32 y1, s32 x2, s32 y2);
void sub_080445F4(void);
void sub_080446B4(u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
void sub_080447EC(u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
void sub_08044934(u32, u8, u8, u16, u16, u32, u8, u8, u8);
u32 sub_08044A3C(u32,u32,u32);
void sub_08044B28(const void *source, void *destination);
u32 sub_08044B34(u32 input);
void sub_08044B58(void);
void sub_08044BA8(u32 mode, u32 value);
void sub_08044C38(u32 mode);
#endif
