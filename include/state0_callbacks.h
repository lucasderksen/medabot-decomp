#ifndef GUARD_STATE0_CALLBACKS_H
#define GUARD_STATE0_CALLBACKS_H

#include "global.h"
#include "main_callbacks.h"
#include "frame_objects.h"
#include "object_helpers.h"
#include "utility_helpers.h"

/* Provisional RAM names and observed call interfaces; see docs/STATE0.md. */
extern u8 gUnknown_03000440[];
extern u8 gUnknown_03002B70[];
extern u32 gUnknown_0300137C;
extern const void *const gUnknownPointers_083B5578[];
extern const MainCallback gMainState0Callbacks[64];
extern const MainCallback gUnknownCallbacks_083AC3C8[15];
extern const MainCallback gUnknownCallbacks_083AC404[20];
extern const MainCallback gUnknownCallbacks_083AC4A0[64];
extern u32 sub_0803F51C(u32, u32, u32, u32, u32, u32);
extern u32 sub_0803FB3C(const void *);
extern void sub_0803FB0C(void);
extern u32 gMainSubstate;
extern void sub_0803FAA0(u32, u32, u32);
extern void sub_08074B88(u32);
extern const void *const gUnknownPointers_083B4C60[];
extern void sub_0803F15C(u32, u32, u32, u32, const void *, u32, u32);
extern void sub_08041164(void *, u32);
extern void sub_08003300(void);
extern const void *const gUnknownPointers_083B6100[];
extern void sub_08074DE0(u32);
extern void sub_080750F0(u32);
extern void sub_0803EF8C(u32, u32, u32, u32, u32, u32);
extern u8 gUnknown_03000588;
extern u32 gMainState;
extern void sub_0803F684(u32, u32, u32);
extern void sub_0803F998(u32, u32, u32);
extern void sub_0804765C(u32);
extern void sub_080480E4(void);
extern void sub_08048830(void);
extern void sub_080497E0(u8 control, u16 targets, u8 type, u8 frames, u8 frames2, u8 frames3, u8 first, u8 second, u8 third);
extern u32 sub_08049A6C(void);
extern const MainCallback gUnknownCallbacks_083AC454[19];
extern void sub_08003904(void);
extern void sub_080039BC(void);
extern void sub_0800393C(void);
extern u32 sub_080425DC(void);
extern void sub_0803F624(void *, u32, u32);

void sub_080025B4(void);
void sub_080026A4(void);
void sub_080026E0(void);
void sub_08002730(void);
void sub_0800275C(void);
void sub_0800277C(void);
void sub_080027BC(void);
void sub_080027DC(void);
void sub_080028AC(void);
void sub_08002A2C(void);
void sub_08002AF8(void);
void sub_08002C34(void);
void sub_08002D48(void);
void sub_08002DF4(void);
void sub_08002EC4(void);
void sub_08002F70(void);
void sub_08003018(void);
void sub_08003104(void);
void sub_08003300(void);
void sub_08003374(void);
void sub_08003394(void);
void sub_080034A4(void);
void sub_08003504(void);
void sub_08003620(void);
void sub_08003654(void);
void sub_080036A8(void);
void sub_080036C8(void);
void sub_080036F4(void);

void sub_08003784(void);

void sub_080038CC(void);

void sub_080038F0(void);

#endif
