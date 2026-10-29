#include "main_callbacks.h"

extern void sub_08002534(void);
extern void sub_0804763C(void);
extern void sub_0805BBE0(void);
extern void sub_08068440(void);
extern void Nullsub_08000258(void);

/* 0x083ABF98..0x083ABFB0. The next table has a separate reference at
 * 0x08001760, confirming this table's boundary. State 3 is selected on boot;
 * state 0 is selected by the main-loop serial reset check. Names are pending.
 */
const MainCallback gMainCallbacks[6] =
{
    sub_08002534,
    sub_0804763C,
    sub_0805BBE0,
    sub_08068440,
    Nullsub_08000258,
    Nullsub_08000258,
};
