#ifndef GUARD_STATE0_DEBUG_MENU_H
#define GUARD_STATE0_DEBUG_MENU_H

#include "global.h"

/* Labels and dispatch are verified by forced emulator entry; normal entry is untraced. */
struct DebugMenuKeyBits { u32 unknown00:6, up:1, down:1; };
void sub_0800B814(void);
void sub_0800B858(void);
void sub_0800B890(void);
void sub_0800B8B0(void);
void sub_0800B938(void);
void sub_0800BA74(void);
void sub_0800BAB8(void);
void sub_0800BAD8(void);
void sub_0800BAF8(void);
void sub_0800BE6C(void);

void sub_0800BE8C(void);
void sub_0800C29C(void);
void sub_0800C2BC(void);
void sub_0800C6D8(void);
void sub_0800C6F8(void);
void sub_0800C7E4(void);
void sub_0800C804(void);
void sub_0800CBA8(void);
void sub_0800CBC8(void);
void sub_0800CE70(void);
void sub_0800CE90(void);
void sub_0800D168(void);
void sub_0800D188(void);
void sub_0800D25C(void);
void sub_0800D27C(void);
void sub_0800D3C4(void);
void sub_0800D3E4(void);
void sub_0800D664(void);
void sub_0800D684(void);
void sub_0800D6A8(void);
void sub_0800D710(void);
void sub_0800D90C(void);

#endif
