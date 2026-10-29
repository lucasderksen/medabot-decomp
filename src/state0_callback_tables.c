#include "state0_next_helpers.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "interrupts.h"

/* Adjacent independently referenced table starts establish these intervals.
 * Names/slot roles remain provisional; see docs/STATE0.md. */
extern void sub_08002554(void);
extern void sub_08002574(void);
extern void sub_080025B4(void);
extern void sub_080026A4(void);
extern void sub_080026E0(void);
extern void sub_08002730(void);
extern void sub_0800275C(void);
extern void sub_0800277C(void);
extern void sub_080027BC(void);
extern void sub_080027DC(void);
extern void sub_080028AC(void);
extern void sub_08002A2C(void);
extern void sub_08002AF8(void);
extern void sub_08002C34(void);
extern void sub_08002D48(void);
extern void sub_08002DF4(void);
extern void sub_08002EC4(void);
extern void sub_08002F70(void);
extern void sub_08003018(void);
extern void sub_08003104(void);
extern void sub_08003374(void);
extern void sub_08003394(void);
extern void sub_080034A4(void);
extern void sub_08003504(void);
extern void sub_08003620(void);
extern void sub_08003654(void);
extern void sub_080036A8(void);
extern void sub_080036C8(void);
extern void sub_080036F4(void);
extern void sub_08003784(void);
extern void sub_080038CC(void);
extern void sub_080038F0(void);
extern void sub_080039E0(void);
extern void sub_08007584(void);
extern void sub_0800B890(void);
extern void sub_0800D9DC(void);
extern void sub_08012970(void);
extern void sub_08030860(void);
extern void sub_08033840(void);
extern void sub_0803D538(void);

const MainCallback gMainState0Callbacks[64] =
{
    sub_08002554,
    sub_080027BC,
    sub_08003374,
    sub_080039E0,
    sub_08007584,
    sub_0800D9DC,
    sub_08010264,
    sub_08012970,
    sub_08030860,
    sub_08033840,
    sub_0803D538,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0800B890,
};

const MainCallback gUnknownCallbacks_083AC3C8[15] =
{
    sub_08002574,
    sub_080025B4,
    sub_080026A4,
    sub_080026E0,
    sub_08002730,
    sub_0800275C,
    sub_0800277C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const MainCallback gUnknownCallbacks_083AC404[20] =
{
    sub_080027DC,
    sub_080028AC,
    sub_08002A2C,
    sub_08002AF8,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08002C34,
    sub_08002D48,
    sub_08002DF4,
    sub_08002EC4,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08002F70,
    sub_08003018,
    sub_08003104,
    DummyInterruptHandler,
};

const MainCallback gUnknownCallbacks_083AC454[19] =
{
    sub_08003394,
    sub_080034A4,
    sub_08003504,
    sub_08003620,
    sub_08003654,
    sub_080036A8,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_080036C8,
    sub_080036F4,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08003784,
    sub_080038CC,
    sub_080038F0,
};


extern void sub_08003A38(void);
extern void sub_08003D4C(void);
extern void sub_08003DE0(void);
extern void sub_08003E54(void);
extern void sub_08003EA0(void);
extern void sub_08003EE0(void);
extern void sub_08003F28(void);
extern void sub_08003F74(void);
extern void sub_08003FE8(void);
extern void sub_08004028(void);
extern void sub_0800406C(void);
extern void sub_080043A8(void);
extern void sub_0800442C(void);
extern void sub_080044F8(void);
extern void sub_0800454C(void);
extern void sub_080045C4(void);
extern void sub_080045DC(void);
extern void sub_08004610(void);
extern void sub_08004644(void);
extern void sub_08004764(void);
extern void sub_08004798(void);
extern void sub_080047EC(void);
extern void sub_08004840(void);
extern void sub_08004874(void);
extern void sub_080048B0(void);
extern void sub_080048D8(void);
extern void sub_080049C8(void);
extern void sub_080049EC(void);
extern void sub_08004A18(void);
extern void sub_08004A40(void);
extern void sub_08004A78(void);
extern void sub_08004AF8(void);
extern void sub_08004C58(void);
extern void sub_08004CA4(void);
extern void sub_08004DB4(void);
extern void sub_08004DF0(void);
extern void sub_08004E40(void);

const MainCallback gUnknownCallbacks_083AC4A0[64] =
{
    sub_08003A38,
    sub_08003D4C,
    sub_08003DE0,
    sub_08003E54,
    sub_08003EA0,
    sub_08003EE0,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08003F28,
    sub_08003F74,
    DummyInterruptHandler,
    sub_08003FE8,
    sub_08004028,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0800406C,
    sub_080043A8,
    sub_0800442C,
    sub_080044F8,
    sub_0800454C,
    sub_080045C4,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_080045DC,
    sub_08004610,
    sub_08004644,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08004764,
    sub_08004798,
    sub_080047EC,
    sub_08004840,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08004764,
    sub_08004874,
    sub_080048B0,
    sub_080048D8,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_080049C8,
    sub_080049EC,
    sub_08004A18,
    sub_08004A40,
    sub_08004A78,
    sub_08004AF8,
    sub_08004C58,
    sub_08004A40,
    sub_08004C58,
    sub_08004CA4,
    sub_08004DB4,
    sub_08004DF0,
    sub_08004E40,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};
