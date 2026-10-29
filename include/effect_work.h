#ifndef GUARD_EFFECT_WORK_H
#define GUARD_EFFECT_WORK_H

#include "gba.h"

extern const IntrFunc gUnknownCallbacks_083B291C[9];
extern const IntrFunc gUnknownCallbacks_083B2940[5];
extern const IntrFunc gUnknownCallbacks_083B2954[6];
extern const IntrFunc gUnknownCallbacks_083B296C[6];
extern const IntrFunc gUnknownCallbacks_083B2984[1];
extern const IntrFunc gUnknownCallbacks_083B2988[2];
extern const IntrFunc gUnknownCallbacks_083B2990[1];

/* Observed byte/halfword interfaces; field roles remain provisional. */
void sub_0803FB0C(void);
u32 sub_0803FB3C(const void *script);
void sub_0803FB6C(void);
void sub_0803FB94(void);
void sub_0803FBDC(void);
void sub_0803FC20(void);
void sub_0803FCC8(void);
void sub_0803FD28(void);
void sub_0803FEA8(void);
void sub_0803FEB8(void);
void sub_08040038(void);
void sub_080402B4(void);
void sub_0804056C(void);
u32 sub_080405D0(void);
void sub_0804070C(void);
void sub_080407A4(void);
void sub_08040820(void);
void sub_080408D0(void);
void sub_080408F4(void);
void sub_08040914(void);
void sub_08040934(void);
void sub_08040954(void);
void sub_08040974(void);
void sub_08040994(void);
void sub_08040A00(void);
void sub_08040A40(void);
void sub_08040AF0(void);
void sub_08040B0C(void);
/* Subsequent routines are referenced as zero-argument table callbacks. */
void sub_08040B50(void);
void sub_08040B5C(void);

#endif
