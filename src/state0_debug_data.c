

#include "main_callbacks.h"
#include "interrupts.h"

void sub_0800B8B0(void);
void sub_0800B938(void);
void sub_0800BA74(void);
void sub_0800BAB8(void);
void sub_0800BAD8(void);
void sub_0800BAF8(void);
void sub_0800BE6C(void);
void sub_0800BE8C(void);
void sub_0800C29C(void);
void sub_0800C2BC(void);
void sub_0800C6D8(void);
void sub_0800C6F8(void);
void sub_0800C7E4(void);
void sub_0800C804(void);
void sub_0800CBA8(void);
void sub_0800CBC8(void);
void sub_0800CE70(void);
void sub_0800CE90(void);
void sub_0800D168(void);
void sub_0800D188(void);
void sub_0800D25C(void);
void sub_0800D27C(void);
void sub_0800D3C4(void);
void sub_0800D3E4(void);
void sub_0800D664(void);
void sub_0800D684(void);
void sub_0800D6A8(void);
void sub_0800D710(void);
void sub_0800D90C(void);

/* Next independently referenced table starts at 083ACA80. */
const MainCallback gDebugMenuCallbacks_083ACA5C[9] __attribute__((section(".rodata.debug_table_3aca5c"))) = {
    sub_0800B8B0,
    sub_0800B938,
    sub_0800BA74,
    sub_0800BAB8,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler
};

/* Next independently referenced table starts at 083ACAC0. */
const MainCallback gDebugMenuPages_083ACA80[16] __attribute__((section(".rodata.debug_table_3aca80"))) = {
    sub_0800BAD8,
    sub_0800BE6C,
    sub_0800C29C,
    sub_0800C6D8,
    sub_0800C7E4,
    sub_0800CBA8,
    sub_0800CE70,
    sub_0800D168,
    sub_0800D25C,
    sub_0800D3C4,
    sub_0800D664,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler
};

/* Next independently referenced table starts at 083ACACC. */
const MainCallback gDebugMenuValues_083ACAC0[3] __attribute__((section(".rodata.debug_table_3acac0"))) = {
    sub_0800BAF8,
    DummyInterruptHandler,
    DummyInterruptHandler
};

/* Next independently referenced table starts at 083ACAD8. */
const MainCallback gDebugMenuProcessCallbacks_083ACACC[3] __attribute__((section(".rodata.debug_table_3acacc"))) = {
    sub_0800BE8C,
    DummyInterruptHandler,
    DummyInterruptHandler
};

/* Next independently referenced table starts at 083ACAE4. */
const MainCallback gDebugPartCallbacks_083ACAD8[3] __attribute__((section(".rodata.debug_table_3acad8"))) = {
    sub_0800C2BC,
    DummyInterruptHandler,
    DummyInterruptHandler
};

/* Next independently referenced table starts at 083ACAF0. */
const MainCallback gDebugTinpetCallbacks_083ACAE4[3] __attribute__((section(".rodata.debug_table_3acae4"))) = {
    sub_0800C6F8,
    DummyInterruptHandler,
    DummyInterruptHandler
};

/* Next independently referenced table starts at 083ACAFC. */
const MainCallback gDebugItemCallbacks_083ACAF0[3] __attribute__((section(".rodata.debug_table_3acaf0"))) = {
    sub_0800C804,
    DummyInterruptHandler,
    DummyInterruptHandler
};

/* Next independently referenced table starts at 083ACB08. */
const MainCallback gDebugFaceCallbacks_083ACAFC[3] __attribute__((section(".rodata.debug_table_3acafc"))) = {
    sub_0800CBC8,
    DummyInterruptHandler,
    DummyInterruptHandler
};

/* Next independently referenced table starts at 083ACB14. */
const MainCallback gDebugMedalImageCallbacks_083ACB08[3] __attribute__((section(".rodata.debug_table_3acb08"))) = {
    sub_0800CE90,
    DummyInterruptHandler,
    DummyInterruptHandler
};

/* Next independently referenced table starts at 083ACB20. */
const MainCallback gDebugRandomCallbacks_083ACB14[3] __attribute__((section(".rodata.debug_table_3acb14"))) = {
    sub_0800D188,
    DummyInterruptHandler,
    DummyInterruptHandler
};

/* Next independently referenced table starts at 083ACB2C. */
const MainCallback gDebugBattleCallbacks_083ACB20[3] __attribute__((section(".rodata.debug_table_3acb20"))) = {
    sub_0800D27C,
    DummyInterruptHandler,
    DummyInterruptHandler
};

/* Next independently referenced table starts at 083ACB38. */
const MainCallback gDebugSoundCallbacks_083ACB2C[3] __attribute__((section(".rodata.debug_table_3acb2c"))) = {
    sub_0800D3E4,
    DummyInterruptHandler,
    DummyInterruptHandler
};

/* Next independently referenced table starts at 083ACB48. */
const MainCallback gDebugMotionCallbacks_083ACB38[4] __attribute__((section(".rodata.debug_table_3acb38"))) = {
    sub_0800D684,
    sub_0800D6A8,
    sub_0800D710,
    sub_0800D90C
};

const u8 gDebugCategoryLabels_083ACB48[11][8] __attribute__((section(".rodata.debug_category_labels"))) = {
    { 0x10, 0x2C, 0x29, 0x1D, 0x1F, 0x2D, 0x2D, 0xFE }, /* Process */
    { 0x0D, 0x1F, 0x1E, 0x1B, 0x26, 0x00, 0x00, 0xFE }, /* Medal */
    { 0x10, 0x1B, 0x2C, 0x2E, 0x2D, 0x00, 0x00, 0xFE }, /* Parts */
    { 0x14, 0x23, 0x28, 0x2A, 0x1F, 0x2E, 0x00, 0xFE }, /* Tinpet */
    { 0x09, 0x2E, 0x1F, 0x27, 0x00, 0x00, 0x00, 0xFE }, /* Item */
    { 0x06, 0x1B, 0x1D, 0x1F, 0x00, 0x00, 0x00, 0xFE }, /* Face */
    { 0x0D, 0x1E, 0x26, 0x2A, 0x23, 0x1D, 0x00, 0xFE }, /* Mdlpic */
    { 0x12, 0x28, 0x1E, 0x43, 0x2E, 0x25, 0x00, 0xFE }, /* Rnd-tk; glyph 43 confirmed by forced emulator entry. */
    { 0x02, 0x1B, 0x2E, 0x2E, 0x26, 0x1F, 0x00, 0xFE }, /* Battle */
    { 0x13, 0x29, 0x2F, 0x28, 0x1E, 0x00, 0x00, 0xFE }, /* Sound */
    { 0x0D, 0x29, 0x2E, 0x23, 0x29, 0x28, 0x00, 0xFE }, /* Motion */
};

const void *const gDebugMenuCategoryText_083ACBA0[11] __attribute__((section(".rodata.debug_category_text"))) = {
    gDebugCategoryLabels_083ACB48[0],
    gDebugCategoryLabels_083ACB48[1],
    gDebugCategoryLabels_083ACB48[2],
    gDebugCategoryLabels_083ACB48[3],
    gDebugCategoryLabels_083ACB48[4],
    gDebugCategoryLabels_083ACB48[5],
    gDebugCategoryLabels_083ACB48[6],
    gDebugCategoryLabels_083ACB48[7],
    gDebugCategoryLabels_083ACB48[8],
    gDebugCategoryLabels_083ACB48[9],
    gDebugCategoryLabels_083ACB48[10]
};

const u8 gDebugProcessText_083ACBCC[3][8] __attribute__((section(".rodata.debug_process_labels"))) = {
    { 0x15, 0x2D, 0x1F, 0x2C, 0x00, 0x00, 0x00, 0xFE },
    { 0x06, 0x2F, 0x28, 0x1D, 0x43, 0x28, 0x29, 0xFE },
    { 0x13, 0x43, 0x20, 0x2F, 0x28, 0x1D, 0x00, 0xFE },
};

const void *const gDebugProcessLabels_083ACBE4[3] __attribute__((section(".rodata.debug_process_text"))) = { gDebugProcessText_083ACBCC[0], gDebugProcessText_083ACBCC[1], gDebugProcessText_083ACBCC[2] };
