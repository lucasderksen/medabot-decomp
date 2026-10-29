#include "global.h"

extern void sub_080675D4(void);
extern void sub_08067870(void);
extern void sub_080678D4(void);
extern void sub_08067974(void);
extern void sub_08067A70(void);
extern void sub_08067ACC(void);
extern void sub_08067B28(void);
extern void sub_08067D00(void);
extern void sub_08067F64(void);
extern void sub_08068238(void);
extern void sub_08068298(void);
extern void sub_08068328(void);
extern void sub_08068374(void);
extern void sub_080683C8(void);

void (*const gBackgroundScrollCallbacks_080B0020[7])(void) = {
    sub_080675D4,
    sub_08067870,
    sub_080678D4,
    sub_08067974,
    sub_08067A70,
    sub_08067ACC,
    sub_08067B28,
};

void (*const gBackgroundScrollCallbacks_080B003C[7])(void) = {
    sub_08067D00,
    sub_08067F64,
    sub_08068238,
    sub_08068298,
    sub_08068328,
    sub_08068374,
    sub_080683C8,
};
