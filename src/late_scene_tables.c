#include "bridge_labels.h"

extern void DummyInterruptHandler(void);
extern s32 sub_0806B130(u8);
extern s32 sub_0806B134(u8);
extern s32 sub_0806B1A8(u8);
extern s32 sub_0806B1D0(u8);
extern s32 sub_0806B1F8(u8);
extern s32 sub_0806B1FC(u8);
extern s32 sub_0806B248(u8);
extern s32 sub_0806B2B8(u8);
extern s32 sub_0806B2F4(u8);
extern s32 sub_0806B3D8(u8);
extern s32 sub_0806B484(u8);
extern void sub_0806B764(void);
extern void sub_0806B820(void);
extern void sub_0806BB24(void);
extern void sub_0806BB44(void);
extern void sub_0806BB64(void);
extern void sub_0806BC48(void);
extern void sub_0806BC94(void);
extern void sub_0806BCC4(void);
extern void sub_0806BCFC(void);
extern void sub_0806BD3C(void);
extern void sub_0806D600(void);
extern void sub_0806D6AC(void);
extern void sub_0806D6E4(void);
extern void sub_0806D7A0(void);
extern void sub_0806D8AC(void);
extern void sub_0806D9A8(void);
extern void sub_0806DAA4(void);
extern void sub_0806DBFC(void);
extern void sub_0806DC7C(void);
extern void sub_0806DCC0(void);
extern void sub_0806E150(void);
extern void sub_0806E184(void);
extern void sub_0806E1EC(void);
extern void sub_0806E2A0(void);
extern void sub_0806E3C4(void);
extern void sub_0806E3F8(void);
extern void sub_0806E4CC(void);
extern void sub_0806E504(void);
extern void sub_0806E5E0(void);
extern void sub_0806E6E4(void);
extern void sub_0806E7EC(void);
extern void sub_0806E90C(void);
extern void sub_0806E93C(void);
extern void sub_0806E96C(void);
extern void sub_0806E9C0(void);
extern void sub_0806EAC0(void);
extern void sub_0806EAF4(void);
extern void sub_0806EB28(void);
extern void sub_0806EBA4(void);
extern void sub_0806EC30(void);
extern void sub_0806ED08(void);
extern void sub_0806EEA8(void);
extern void sub_0806F0E0(void);
extern void sub_0806F114(void);
extern void sub_0806F1C0(void);
extern void sub_0806F21C(void);
extern void sub_0806F23C(void);
extern void sub_0806F578(void);
extern void sub_0806F5A0(void);
extern void sub_0806F8D8(void);
extern void sub_0806F914(void);
extern void sub_0806F934(void);
extern void sub_0806F9B8(void);
extern void sub_08070914(void);
extern void sub_080709D4(void);
extern void sub_08070C0C(void);
extern void sub_08070D74(void);
extern void sub_08071030(void);
extern void sub_0807105C(void);
extern void sub_080710AC(void);
extern void sub_080710F4(void);
extern void sub_08071138(void);
extern void sub_08071164(void);
extern void sub_080712C8(void);
extern void sub_08071304(void);
extern void sub_08071460(void);
extern void sub_08071630(void);
extern void sub_08071744(void);
extern void sub_08071778(void);
extern s32 sub_08071DFC(void);
extern s32 sub_08071E0C(void);
extern s32 sub_08071E8C(void);
extern s32 sub_08071EFC(void);
extern s32 sub_08071F74(void);
extern s32 sub_08071FF8(void);
extern s32 sub_08072080(void);
extern s32 sub_08072188(void);
extern s32 sub_08072234(void);
extern s32 sub_080722B0(void);

s32 (*const gFrameCommandCallbacks_084857D0[11])(u8) = {
    sub_0806B134,
    sub_0806B1A8,
    sub_0806B1D0,
    sub_0806B1F8,
    sub_0806B1FC,
    sub_0806B248,
    sub_0806B2B8,
    sub_0806B2F4,
    sub_0806B3D8,
    sub_0806B484,
    sub_0806B130,
};

void (*const gScene6B744Callbacks_084858FC[10])(void) = {
    sub_0806B764,
    sub_0806B820,
    sub_0806BB24,
    sub_0806BB44,
    sub_0806BB64,
    sub_0806BC48,
    sub_0806BC94,
    sub_0806BCC4,
    sub_0806BCFC,
    sub_0806BD3C,
};

void (*const gScene6D588Callbacks_08485964[12])(void) = {
    sub_0806D6E4,
    sub_0806E150,
    sub_0806D600,
    sub_0806D6AC,
    sub_0806D7A0,
    sub_0806D8AC,
    sub_0806D9A8,
    sub_0806DAA4,
    sub_0806DBFC,
    sub_0806DC7C,
    sub_0806DCC0,
    DummyInterruptHandler,
};

void (*const gScene6E130Callbacks_084859BC[7])(void) = {
    sub_0806E1EC,
    sub_0806E150,
    sub_0806E184,
    sub_0806E2A0,
    sub_0806E3C4,
    sub_0806E3F8,
    DummyInterruptHandler,
};

void (*const gScene6E460Callbacks_084859D8[12])(void) = {
    sub_0806E504,
    sub_0806E150,
    sub_0806E184,
    sub_0806E4CC,
    sub_0806E5E0,
    sub_0806E90C,
    sub_0806E6E4,
    sub_0806E93C,
    sub_0806E7EC,
    sub_0806E96C,
    sub_0806E9C0,
    DummyInterruptHandler,
};

void (*const gScene6EA98Callbacks_08485A08[20])(void) = {
    sub_0806EC30,
    sub_0806E150,
    sub_0806EBA4,
    sub_0806EAC0,
    sub_0806EAF4,
    sub_0806EB28,
    sub_0806ED08,
    sub_0806EEA8,
    sub_0806F0E0,
    sub_0806F114,
    sub_0806F1C0,
    sub_0806F21C,
    sub_0806F23C,
    sub_0806F578,
    sub_0806F5A0,
    sub_0806F8D8,
    sub_0806F914,
    sub_0806F934,
    sub_0806F9B8,
    DummyInterruptHandler,
};

void (*const gScene708D8Callbacks_08485B68[19])(void) = {
    sub_08070914,
    sub_0806E150,
    sub_0806E184,
    sub_080709D4,
    sub_08070C0C,
    sub_08070D74,
    sub_08071030,
    sub_0807105C,
    sub_080710AC,
    sub_080710F4,
    sub_08071138,
    sub_08071164,
    sub_080712C8,
    sub_08071304,
    sub_08071460,
    sub_08071630,
    sub_08071744,
    sub_08071778,
    DummyInterruptHandler,
};

s32 (*const gScene71DDCCallbacks_08485BD8[10])(void) = {
    sub_08071E0C,
    sub_08071E8C,
    sub_08071EFC,
    sub_08071F74,
    sub_08071DFC,
    sub_08071FF8,
    sub_08072080,
    sub_08072188,
    sub_08072234,
    sub_080722B0,
};

const struct BridgeLabelPool gBridgeLabelPool_08485A80 = {
    { 10, 7, 15, 15, 7, 9, 4, 20 },
    { 14, 4, 18, 12, 9, 18, 4, 14, 20 },
    { 15, 17, 1, 10, 0, 2, 6, 7, 11, 5, 17, 11, 20 },
    { 12, 2, 6, 7, 16, 15, 17, 8, 0, 20 },
    { 0, 11, 16, 4, 11, 11, 0, 20 },
    { 15, 19, 12, 14, 3, 20 },
    { 13, 7, 13, 12, 21, 6, 0, 10, 10, 4, 14, 20 },
    { 16, 0, 16, 0, 2, 8, 4, 14, 20 },
    0, /* Align the following pointer table. */
};

const u8 *const gBridgeLabels_08485ACC[8] = {
    gBridgeLabelPool_08485A80.label1,
    gBridgeLabelPool_08485A80.label2,
    gBridgeLabelPool_08485A80.label3,
    gBridgeLabelPool_08485A80.label0,
    gBridgeLabelPool_08485A80.label5,
    gBridgeLabelPool_08485A80.label6,
    gBridgeLabelPool_08485A80.label7,
    gBridgeLabelPool_08485A80.label4,
};
