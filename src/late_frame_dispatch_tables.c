#include "global.h"

extern s32 sub_0806DE9C(u8);
extern s32 sub_0806DFC0(u8);
extern s32 sub_0806DFF0(u8);
extern s32 sub_0806E014(u8);
extern s32 sub_0806E038(u8);
extern s32 sub_0806E074(u8);
extern s32 sub_080705E0(u8);
extern s32 sub_08070648(u8);
extern s32 sub_080706A4(u8);
extern s32 sub_08070734(u8);
extern s32 sub_08070778(u8);
extern s32 sub_0807190C(u8);
extern s32 sub_080719B8(u8);
extern s32 sub_08071A64(u8);
extern s32 sub_08071B64(u8);
extern s32 sub_08071C68(u8);
extern s32 sub_08071CBC(u8);
extern s32 sub_08071D10(u8);
extern s32 sub_08071D88(u8);

s32 (*const gTimedFrameCallbacks_08485994[8])(u8) = {
    sub_0806DE9C,
    sub_0806DFC0,
    sub_0806DFF0,
    sub_0806E014,
    sub_0806E038,
    sub_0806E038,
    sub_0806E074,
    sub_0806E074,
};

s32 (*const gTimedFrameCallbacks_08485B4C[5])(u8) = {
    sub_080705E0,
    sub_08070648,
    sub_080706A4,
    sub_08070734,
    sub_08070778,
};

s32 (*const gFrameCallbacks_08485BB8[8])(u8) = {
    sub_0807190C,
    sub_080719B8,
    sub_08071A64,
    sub_08071B64,
    sub_08071C68,
    sub_08071CBC,
    sub_08071D10,
    sub_08071D88,
};

const u8 gTimedFrameIntervals_084859B4[8] __attribute__((aligned(1))) = { 2, 2, 1, 1, 29, 4, 3, 2 };

const u8 gTimedFrameIntervals_08485B60[5] __attribute__((aligned(1))) = { 1, 1, 4, 1, 1 };

const u8 gTimedFrameAlignment_08485B65[3] __attribute__((aligned(1))) = { 0, 0, 0 };

const s8 gSceneArcOffsets_08485924[64] = {
    0, 2, 4, 7, 9, 11, 13, 16, 18, 20, 22, 24, 26, 28, 30, 32,
    33, 35, 37, 38, 39, 41, 42, 43, 44, 45, 45, 46, 47, 47, 47, 47,
    47, 47, 47, 47, 47, 46, 45, 45, 44, 43, 42, 41, 39, 38, 37, 35,
    33, 32, 30, 28, 26, 24, 22, 20, 18, 16, 13, 11, 9, 7, 4, 2,
};
