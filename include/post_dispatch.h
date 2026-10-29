#ifndef GUARD_POST_DISPATCH_H
#define GUARD_POST_DISPATCH_H
#include "global.h"

void sub_0804765C(u32 mode);
void sub_08047850(s32 mode);
void sub_08047BA8(u32 value);
void sub_08047BB4(u32 value);
void sub_08047BC0(u32 value);
const void *sub_08047BCC(u32 index);
const void *sub_08047BDC(u32 index);
const void *sub_08047BEC(u32 index, u32 row);
u32 sub_08047D4C(void);
void sub_08047D58(u32 amount);
void sub_08047D74(u32 amount);
u32 sub_08047D8C(u8 value);
u32 sub_08047D9C(u8 index, u8 row);
u32 sub_08047DB0(u8 identifier);
void sub_08047DC0(u8 index, u8 amount);
void sub_08047DD8(u8 index, u8 amount);
void sub_08047DF0(u8 index, u8 row, u8 amount);
void sub_08047E08(u8 index, u8 row, u8 amount);
u32 sub_08047E20(u8 identifier);
u32 sub_08047E30(void);
void sub_08047E3C(u8 value);
void sub_08047E4C(void);
u32 sub_08047F9C(void);


struct PostDispatchTextBuffers { u8 *items[4]; };
extern const struct PostDispatchTextBuffers gPostDispatchTextBuffers_080ABD6C;
void sub_08047C00(void);
u32 sub_08047C24(u8 first, u8 second, u8 mode, const void *script);
void sub_08047C84(u32 index, s32 value);
void sub_08047CE4(u32 index, const u8 *source);
void sub_08047D24(u32 index, u32 value);
u32 sub_08047EF0(u8 value, u8 part);
s32 sub_08047F50(u8 value);
u32 sub_08047FBC(u8 value);

s32 sub_08047E50(u8 value, u8 part);

#endif
