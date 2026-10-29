#include "global.h"

extern void DummyInterruptHandler(void);
extern void sub_0803B900(void);
extern void sub_0803B9A4(void);
extern void sub_0803BBE0(void);
extern void sub_0803BE44(void);
extern void sub_0803C044(void);
extern void sub_0803C0CC(void);
extern void sub_0803C33C(void);
extern void sub_0803C5F8(void);
extern void sub_0803C680(void);
extern void sub_0803C738(void);
extern void sub_0803C7DC(void);
extern void sub_0803C8AC(void);
extern void sub_0803C9E0(void);
extern void sub_0803CAB0(void);
extern void sub_0803CB54(void);
extern void sub_0803CBD0(void);
extern void sub_0803CC40(void);
extern void sub_0803CC8C(void);
extern void sub_0803CDCC(void);
extern void sub_0803CE18(void);
extern void sub_0803CECC(void);
extern void sub_0803CF7C(void);
extern void sub_0803CFC8(void);
extern void sub_0803D0BC(void);
extern void sub_0803D15C(void);
extern void sub_0803D2A8(void);
extern void sub_0803D3C0(void);
extern void sub_0803D5A0(void);
extern void sub_0803D5E0(void);
extern void sub_0803D608(void);
extern void sub_0803D634(void);
extern void sub_0803D674(void);
extern void sub_0803D6AC(void);
extern void sub_0803D71C(void);
extern void sub_0803D74C(void);
extern void sub_0803D928(void);
extern void sub_0803D980(void);
extern void sub_0803D9A0(void);
extern void sub_0803D9C8(void);
extern void sub_0803D9F0(void);
extern void sub_0803DA40(void);
extern void sub_0803DA90(void);
extern void sub_0803DAEC(void);
extern void sub_0803DB1C(void);
extern void sub_0803DB4C(void);
extern void sub_0803DB94(void);
extern void sub_0803DBB8(void);
extern void sub_0803DBE0(void);
extern void sub_0803DC0C(void);
extern void sub_0803DC3C(void);
extern void sub_0803DC58(void);
extern void sub_0803DC8C(void);
extern void sub_0803DCDC(void);
extern void sub_0803DE70(void);
extern void sub_0803DE90(void);
extern void sub_0803DEB0(void);
extern void sub_0803DEF0(void);
extern void sub_0803DF98(void);
extern void sub_0803E018(void);
extern void sub_0803E03C(void);
extern void sub_0803E098(void);
extern void sub_0803E0C0(void);
extern void sub_0803E0F0(void);
extern void sub_0803E120(void);
extern void sub_0803E170(void);
extern void sub_0803E1A4(void);
extern void sub_0803E1FC(void);
extern void sub_0803E234(void);
extern void sub_0803E270(void);
extern void sub_0803E2AC(void);
extern void sub_0803E2DC(void);
extern void sub_0803E314(void);
extern void sub_0803E374(void);
extern void sub_0803E434(void);
extern void sub_0803E48C(void);
extern void sub_0803E4B4(void);
extern void sub_0803E4D8(void);
extern void sub_0803E4F4(void);
extern void sub_0803E618(void);
extern void sub_0803E634(void);
extern void sub_0803E674(void);
extern void sub_0803E680(void);
extern void sub_0803E768(void);
extern void sub_0803E774(void);

void (*const gObjectPhaseCallbacks_083AFAEC[80])(void) = {
    DummyInterruptHandler,
    sub_0803B900,
    sub_0803B9A4,
    sub_0803BBE0,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0803BE44,
    sub_0803C044,
    sub_0803C0CC,
    sub_0803C5F8,
    sub_0803C33C,
    sub_0803C680,
    sub_0803C738,
    DummyInterruptHandler,
    sub_0803C7DC,
    sub_0803C8AC,
    sub_0803C9E0,
    sub_0803CAB0,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0803CB54,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0803CBD0,
    sub_0803CC40,
    sub_0803CC8C,
    sub_0803CDCC,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0803CE18,
    sub_0803CECC,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0803CF7C,
    sub_0803CFC8,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0803D0BC,
    DummyInterruptHandler,
    sub_0803D15C,
    DummyInterruptHandler,
    sub_0803D2A8,
    DummyInterruptHandler,
    sub_0803D3C0,
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
};

void (*const gScenePhaseCallbacks_083AFC78[96])(void) = {
    sub_0803D5A0,
    sub_0803D5E0,
    sub_0803D608,
    sub_0803D634,
    sub_0803D674,
    sub_0803D6AC,
    sub_0803D71C,
    sub_0803D74C,
    sub_0803D928,
    sub_0803D980,
    sub_0803D9A0,
    sub_0803D9C8,
    sub_0803D9F0,
    sub_0803DA90,
    sub_0803DAEC,
    DummyInterruptHandler,
    sub_0803E4B4,
    sub_0803E4D8,
    sub_0803E4F4,
    sub_0803E4D8,
    sub_0803E618,
    sub_0803E634,
    sub_0803E4B4,
    sub_0803E4D8,
    sub_0803E674,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0803D74C,
    sub_0803DB1C,
    sub_0803D928,
    sub_0803D980,
    sub_0803DB4C,
    sub_0803DB94,
    sub_0803DBB8,
    sub_0803DBE0,
    sub_0803DC0C,
    sub_0803DC3C,
    sub_0803D9C8,
    sub_0803DA40,
    sub_0803DC58,
    sub_0803DC8C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0803DCDC,
    sub_0803DE70,
    sub_0803DE90,
    sub_0803DEB0,
    sub_0803DEF0,
    sub_0803DF98,
    sub_0803E018,
    sub_0803E03C,
    sub_0803E098,
    sub_0803E0C0,
    sub_0803E0F0,
    sub_0803E120,
    sub_0803E170,
    sub_0803E1A4,
    sub_0803E1FC,
    sub_0803E234,
    sub_0803E270,
    sub_0803E2AC,
    sub_0803E2DC,
    sub_0803E314,
    sub_0803DC8C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0803E374,
    sub_0803E170,
    sub_0803E434,
    sub_0803E48C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0803E680,
    sub_0803D608,
    sub_0803D5E0,
    sub_0803D608,
    sub_0803E768,
    sub_0803D608,
    sub_0803E774,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const u8 gObjectScrollShifts_083AFC2C[12] = {
    0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0
};

const u8 gSceneBankChoices_083AFE78[16] = {
    0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0
};

const s16 gObjectVerticalSteps_083AFC38[32] = {
    -2, 0, -1, 0, -1, 0, 0, 0, 1, 0, 1, 0, 2, 0, 2, 0, 2, 0, 1, 0, 1, 0, 0, 0, -1, 0, -1, 0, -2, 0, -2, 0
};

const u8 gSceneRandomChoices_083AFDF8[32] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

const u8 gSceneChoiceRows_083AFE18[96] = {
    4, 0, 1, 2, 3, 4, 1, 4, 0, 3, 4, 2, 3, 1, 4, 4, 2, 0, 4, 3, 1, 2, 0, 4, 2, 4, 3, 0, 4, 1, 0, 2, 4, 4, 1, 3, 4, 0, 2, 1, 3, 4, 1, 4, 0, 3, 4, 2, 4, 0, 1, 4, 2, 3, 1, 4, 0, 2, 3, 4, 2, 1, 4, 3, 4, 0, 3, 2, 1, 4, 0, 4, 4, 3, 2, 0, 4, 1, 0, 4, 3, 4, 1, 2, 3, 0, 4, 1, 2, 4, 4, 3, 0, 2, 4, 1
};
