#include "effect_work.h"
#include "interrupts.h"

const IntrFunc gUnknownCallbacks_083B291C[9] =
{
    sub_0803FB6C,
    sub_0803FB94,
    sub_0803FBDC,
    sub_0803FC20,
    sub_0803FCC8,
    sub_0803FD28,
    sub_080408D0,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const IntrFunc gUnknownCallbacks_083B2940[5] =
{
    sub_080408F4,
    sub_08040914,
    sub_08040934,
    sub_08040954,
    sub_08040974,
};

const IntrFunc gUnknownCallbacks_083B2954[6] =
{
    sub_08040994,
    sub_08040A00,
    sub_08040A40,
    sub_08040AF0,
    sub_08040B0C,
    sub_08040B50,
};

const IntrFunc gUnknownCallbacks_083B296C[6] =
{
    sub_08040994,
    sub_08040A00,
    sub_08040A40,
    sub_08040AF0,
    sub_08040B0C,
    sub_08040B50,
};

const IntrFunc gUnknownCallbacks_083B2984[1] =
{
    sub_08040B50,
};

const IntrFunc gUnknownCallbacks_083B2988[2] =
{
    sub_08040B5C,
    sub_08040B50,
};

const IntrFunc gUnknownCallbacks_083B2990[1] =
{
    sub_08040B50,
};
