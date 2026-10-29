#include "main_callbacks.h"

extern void DummyInterruptHandler(void);
extern void sub_0804A220(void);
extern void sub_0804A2F0(void);
extern void sub_0804A60C(void);
extern void sub_0804A6A0(void);
extern void sub_0804A6BC(void);
extern void sub_0804A6C8(void);
extern void sub_0804A6E0(void);
extern void sub_0804A6EC(void);
extern void sub_0804A6F8(void);
extern void sub_0804A724(void);
extern void sub_0804A734(void);
extern void sub_0804A764(void);
extern void sub_0804A900(void);
extern void sub_0804A944(void);
extern void sub_0804AA04(void);
extern void sub_0804AA44(void);
extern void sub_0804AA74(void);
extern void sub_0804AB04(void);
extern void sub_0804AB18(void);
extern void sub_0804AB24(void);
extern void sub_0804AB3C(void);
extern void sub_0804AB60(void);
extern void sub_0804ABA8(void);
extern void sub_0804ABC0(void);
extern void sub_0804ABCC(void);
extern void sub_0804AC14(void);
extern void sub_0804ACC8(void);
extern void sub_0804ACD4(void);
extern void sub_0804AD68(void);
extern void sub_0804ADB4(void);
extern void sub_0804AE80(void);
extern void sub_0804AEC8(void);
extern void sub_0804AF98(void);
extern void sub_0804AFB8(void);
extern void sub_0804AFCC(void);
extern void sub_0804AFE0(void);
extern void sub_0804B008(void);
extern void sub_0804B15C(void);
extern void sub_0805716C(void);

const MainCallback gMainState1Callbacks[10] = {
    DummyInterruptHandler, /* 0 */
    sub_0804A220, /* 1 */
    sub_0805716C, /* 2 */
    DummyInterruptHandler, /* 3 */
    DummyInterruptHandler, /* 4 */
    DummyInterruptHandler, /* 5 */
    DummyInterruptHandler, /* 6 */
    DummyInterruptHandler, /* 7 */
    DummyInterruptHandler, /* 8 */
    DummyInterruptHandler, /* 9 */
};

const MainCallback gFrameCallbacks_083D212C[53] = {
    sub_0804A2F0, /* 0 */
    sub_0804A60C, /* 1 */
    sub_0804A6A0, /* 2 */
    sub_0804A6BC, /* 3 */
    sub_0804A6C8, /* 4 */
    sub_0804A6E0, /* 5 */
    sub_0804A6EC, /* 6 */
    sub_0804A6F8, /* 7 */
    sub_0804A724, /* 8 */
    sub_0804A734, /* 9 */
    sub_0804A764, /* 10 */
    sub_0804A900, /* 11 */
    sub_0804B15C, /* 12 */
    sub_0804A944, /* 13 */
    sub_0804AA04, /* 14 */
    sub_0804B15C, /* 15 */
    sub_0804AA44, /* 16 */
    sub_0804AA74, /* 17 */
    sub_0804AB04, /* 18 */
    sub_0804AB18, /* 19 */
    sub_0804AB24, /* 20 */
    sub_0804B15C, /* 21 */
    sub_0804B15C, /* 22 */
    sub_0804B15C, /* 23 */
    sub_0804AB3C, /* 24 */
    sub_0804AB60, /* 25 */
    sub_0804ABA8, /* 26 */
    sub_0804B15C, /* 27 */
    sub_0804ABC0, /* 28 */
    sub_0804ABCC, /* 29 */
    sub_0804AC14, /* 30 */
    sub_0804B15C, /* 31 */
    sub_0804ACC8, /* 32 */
    sub_0804ACD4, /* 33 */
    sub_0804AD68, /* 34 */
    sub_0804ADB4, /* 35 */
    sub_0804B15C, /* 36 */
    sub_0804B15C, /* 37 */
    sub_0804B15C, /* 38 */
    sub_0804B15C, /* 39 */
    sub_0804AE80, /* 40 */
    sub_0804AEC8, /* 41 */
    sub_0804B15C, /* 42 */
    sub_0804B15C, /* 43 */
    sub_0804B15C, /* 44 */
    sub_0804B15C, /* 45 */
    sub_0804B15C, /* 46 */
    sub_0804B15C, /* 47 */
    sub_0804AF98, /* 48 */
    sub_0804AFB8, /* 49 */
    sub_0804AFCC, /* 50 */
    sub_0804AFE0, /* 51 */
    sub_0804B008, /* 52 */
};

/* Eight-byte records copied into transfer work at offset 0x39. */
const u8 gState0ScrollControls_083C3C84[22][8] = {
    { 1, 1, 4, 1, 2, 14, 0, 0 },
    { 1, 8, 4, 1, 7, 10, 0, 0 },
    { 1, 8, 1, 1, 9, 10, 0, 0 },
    { 2, 8, 1, 0, 1, 1, 0, 0 },
    { 2, 8, 1, 0, 1, 1, 0, 0 },
    { 0, 1, 2, 0, 1, 1, 0, 0 },
    { 0, 1, 2, 0, 1, 1, 0, 0 },
    { 0, 1, 2, 0, 1, 1, 0, 0 },
    { 2, 8, 1, 0, 1, 1, 0, 0 },
    { 0, 1, 2, 1, 8, 11, 0, 0 },
    { 1, 1, 2, 1, 10, 9, 0, 0 },
    { 1, 1, 4, 1, 4, 13, 0, 0 },
    { 1, 8, 4, 1, 9, 8, 0, 0 },
    { 1, 8, 1, 1, 10, 7, 0, 0 },
    { 0, 1, 4, 0, 1, 1, 0, 0 },
    { 0, 1, 4, 0, 1, 1, 0, 0 },
    { 0, 1, 4, 0, 1, 1, 0, 0 },
    { 0, 1, 4, 0, 1, 1, 0, 0 },
    { 0, 1, 4, 0, 1, 1, 0, 0 },
    { 0, 1, 4, 0, 1, 1, 0, 0 },
    { 0, 1, 4, 1, 11, 8, 0, 0 },
    { 1, 1, 2, 1, 8, 13, 0, 0 },
};
