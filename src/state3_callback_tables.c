#include "global.h"

extern void sub_0806E460(void);
extern void sub_0806EA98(void);
extern void sub_0806D588(void);
extern void sub_0806E130(void);
extern void sub_08068DD0(void);
extern void sub_0806B744(void);
extern void sub_080708D8(void);
extern void sub_08000840(void);
extern s32 sub_08068920(void);
extern s32 sub_08068924(void);
extern s32 sub_08068978(void);
extern s32 sub_08068A84(void);
extern s32 sub_08068B74(void);
extern s32 sub_08068BC4(void);
extern s32 sub_08068CC8(void);
extern void sub_08068E00(void);
extern void sub_08068E88(void);
extern void sub_08068EA8(void);
extern void sub_08068F08(void);
extern void sub_08068F34(void);
extern void sub_08068F50(void);
extern void sub_08069168(void);
extern void sub_08069194(void);
extern void sub_080691E0(void);
extern void sub_0806920C(void);
extern void sub_08069258(void);
extern void sub_080692A8(void);
extern void sub_080692EC(void);

void (*const gMainState3Callbacks[8])(void) = {
    sub_0806E460,
    sub_0806EA98,
    sub_0806D588,
    sub_0806E130,
    sub_08068DD0,
    sub_0806B744,
    sub_080708D8,
    sub_08000840,
};

s32 (*const gUnknown_08485708[5])(void) = {
    sub_08068920,
    sub_08068924,
    sub_08068924,
    sub_08068978,
    sub_08068A84,
};

s32 (*const gUnknown_0848571C[5])(void) = {
    sub_08068920,
    sub_08068B74,
    sub_08068B74,
    sub_08068BC4,
    sub_08068CC8,
};

void (*const gUnknown_08485730[13])(void) = {
    sub_08068E00,
    sub_08068E88,
    sub_08068EA8,
    sub_08068F08,
    sub_08068F34,
    sub_08068F50,
    sub_08069168,
    sub_08069194,
    sub_080691E0,
    sub_0806920C,
    sub_08069258,
    sub_080692A8,
    sub_080692EC,
};
