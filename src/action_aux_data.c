#include "action_aux_data.h"
/* Priority records, sprite count/kind/x/y records, phase lookup, signed motion steps, and setup remap. */

const u8 gState0PriorityTable_083AD470[128] __attribute__((aligned(1))) = {
    0x01, 0x02, 0x03, 0xFF,
    0x02, 0x03, 0x01, 0xFF,
    0x03, 0x01, 0x02, 0xFF,
    0x01, 0x03, 0x02, 0xFF,
    0x02, 0x01, 0x03, 0xFF,
    0x03, 0x02, 0x01, 0xFF,
    0x01, 0x02, 0x03, 0xFF,
    0x02, 0x03, 0x01, 0xFF,
    0x03, 0x01, 0x02, 0xFF,
    0x01, 0x03, 0x02, 0xFF,
    0x02, 0x01, 0x03, 0xFF,
    0x03, 0x02, 0x01, 0xFF,
    0x01, 0x02, 0x03, 0xFF,
    0x02, 0x03, 0x01, 0xFF,
    0x03, 0x01, 0x02, 0xFF,
    0x01, 0x03, 0x02, 0xFF,
    0x02, 0x01, 0x03, 0xFF,
    0x03, 0x02, 0x01, 0xFF,
    0x01, 0x02, 0x03, 0xFF,
    0x02, 0x03, 0x01, 0xFF,
    0x03, 0x01, 0x02, 0xFF,
    0x01, 0x03, 0x02, 0xFF,
    0x02, 0x01, 0x03, 0xFF,
    0x03, 0x02, 0x01, 0xFF,
    0x01, 0x02, 0x03, 0xFF,
    0x02, 0x03, 0x01, 0xFF,
    0x03, 0x01, 0x02, 0xFF,
    0x01, 0x03, 0x02, 0xFF,
    0x02, 0x01, 0x03, 0xFF,
    0x03, 0x02, 0x01, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
};

const struct ActionSpriteSetup gActionSpriteSetup[6] __attribute__((aligned(1))) = {
    { 10, 0, 12, 44 },
    { 7, 0, 12, 68 },
    { 4, 0, 12, 92 },
    { 10, 1, 228, 44 },
    { 7, 1, 228, 68 },
    { 4, 1, 228, 92 },
};

const u8 gUnknown_083AD51A[6] __attribute__((aligned(1))) = {
    0x10, 0x18, 0x20, 0x28, 0x30, 0x38,
};

const u8 gFrameStepBytes_083AD533[32] __attribute__((aligned(1))) = {
    0xFC, 0xFD, 0xFD, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF,
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
    0x01, 0x01, 0x02, 0x02, 0x02, 0x03, 0x03, 0x00,
};

const u8 gUnknown_083AD553[32] __attribute__((aligned(1))) = {
    0x01, 0x00, 0x03, 0x02, 0x05, 0x01, 0x04, 0x03,
    0x01, 0x04, 0x02, 0x05, 0x00, 0x03, 0x04, 0x00,
    0x05, 0x03, 0x00, 0x04, 0x05, 0x01, 0x03, 0x02,
    0x02, 0x05, 0x00, 0x03, 0x01, 0x00, 0x02, 0x04,
};

const u8 gUnknown_083AD573[6] __attribute__((aligned(1))) = {
    0x03, 0x04, 0x05, 0x00, 0x01, 0x02,
};

const u8 gUnknown_083AD579[7] __attribute__((aligned(1))) = {
    0x00, 0x04, 0x05, 0x06, 0x01, 0x02, 0x03,
};

const u8 gActionBaseStats[27][8] = {
    { 4, 4, 1, 1, 2, 1, 2, 1 },
    { 1, 1, 4, 4, 1, 2, 1, 2 },
    { 1, 1, 3, 3, 2, 2, 2, 2 },
    { 1, 1, 3, 3, 2, 2, 2, 2 },
    { 1, 1, 3, 3, 2, 2, 2, 2 },
    { 1, 1, 3, 3, 2, 2, 2, 2 },
    { 3, 3, 1, 1, 2, 2, 2, 2 },
    { 3, 3, 1, 1, 2, 2, 2, 2 },
    { 3, 3, 1, 1, 2, 2, 2, 2 },
    { 3, 3, 1, 1, 2, 2, 2, 2 },
    { 2, 2, 1, 1, 2, 4, 2, 2 },
    { 1, 1, 2, 2, 2, 2, 2, 4 },
    { 2, 2, 1, 1, 4, 2, 2, 2 },
    { 1, 1, 2, 2, 2, 4, 2, 2 },
    { 2, 2, 1, 1, 2, 4, 2, 2 },
    { 2, 2, 3, 3, 1, 2, 1, 2 },
    { 2, 2, 3, 3, 1, 2, 1, 2 },
    { 2, 2, 2, 2, 2, 2, 3, 1 },
    { 2, 2, 2, 2, 2, 1, 3, 2 },
    { 2, 2, 2, 2, 2, 2, 3, 1 },
    { 2, 2, 2, 1, 1, 2, 2, 4 },
    { 2, 4, 2, 4, 1, 1, 1, 1 },
    { 2, 1, 2, 1, 1, 1, 4, 4 },
    { 2, 2, 2, 2, 4, 1, 2, 1 },
    { 3, 2, 2, 2, 4, 1, 1, 1 },
    { 2, 2, 2, 2, 2, 2, 2, 2 },
    { 2, 2, 2, 2, 2, 2, 2, 2 },
};

extern void DummyInterruptHandler(void);
extern void sub_0801C0F8(void);
extern void sub_0801C110(void);
extern void sub_0801C138(void);
void (*const gUnknown_083AD580[4])(void) = {
    sub_0801C0F8,
    sub_0801C110,
    sub_0801C138,
    DummyInterruptHandler,
};

extern void DummyInterruptHandler(void);
extern void sub_0801C188(void);
extern void sub_0801C1C0(void);
extern void sub_0801C23C(void);
extern void sub_0801C298(void);
void (*const gUnknown_083AD590[5])(void) = {
    sub_0801C188,
    sub_0801C1C0,
    sub_0801C23C,
    sub_0801C298,
    DummyInterruptHandler,
};

extern void sub_0801C32C(void);
extern void sub_0801C360(void);
extern void sub_0801C388(void);
extern void sub_0801C3B0(void);
extern void sub_0801C3F8(void);
extern void sub_0801C40C(void);
extern void sub_0801C444(void);
extern void sub_0801C470(void);
extern void sub_0801C4A4(void);
extern void sub_0801C4E0(void);
void (*const gUnknown_083AD5A4[10])(void) = {
    sub_0801C32C,
    sub_0801C360,
    sub_0801C388,
    sub_0801C3B0,
    sub_0801C3F8,
    sub_0801C40C,
    sub_0801C444,
    sub_0801C470,
    sub_0801C4A4,
    sub_0801C4E0,
};
