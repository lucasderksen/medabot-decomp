

#include "global.h"

/* Encoded eight-byte display records; FE is the observed terminator. */
const u8 gDebugMedalText_083ACBF0[3][8] __attribute__((section(".rodata.debug_medal_text"))) = {
    { 0x07, 0x1F, 0x2E, 0x00, 0x00, 0x00, 0x00, 0xFE },
    { 0x0C, 0x29, 0x2D, 0x2E, 0x00, 0x00, 0x00, 0xFE },
    { 0x01, 0x26, 0x26, 0x00, 0x00, 0x00, 0x00, 0xFE },
};

const void *const gDebugMedalLabels_083ACC08[3] __attribute__((section(".rodata.debug_medal_labels"))) = { gDebugMedalText_083ACBF0[0], gDebugMedalText_083ACBF0[1], gDebugMedalText_083ACBF0[2] };

const u8 gDebugPartText_083ACC14[3][8] __attribute__((section(".rodata.debug_part_text"))) = {
    { 0x07, 0x1F, 0x2E, 0x00, 0x00, 0x00, 0x00, 0xFE },
    { 0x0C, 0x29, 0x2D, 0x2E, 0x00, 0x00, 0x00, 0xFE },
    { 0x01, 0x26, 0x26, 0x00, 0x00, 0x00, 0x00, 0xFE },
};

const void *const gDebugPartLabels_083ACC2C[3] __attribute__((section(".rodata.debug_part_labels"))) = { gDebugPartText_083ACC14[0], gDebugPartText_083ACC14[1], gDebugPartText_083ACC14[2] };

const u8 gDebugTinpetText_083ACC38[1][8] __attribute__((section(".rodata.debug_tinpet_text"))) = {
    { 0x07, 0x1F, 0x2E, 0x00, 0x00, 0x00, 0x00, 0xFE },
};

const void *const gDebugTinpetLabels_083ACC40[1] __attribute__((section(".rodata.debug_tinpet_labels"))) = { gDebugTinpetText_083ACC38[0] };

const u8 gDebugItemText_083ACC44[3][8] __attribute__((section(".rodata.debug_item_text"))) = {
    { 0x07, 0x1F, 0x2E, 0x00, 0x00, 0x00, 0x00, 0xFE },
    { 0x0C, 0x29, 0x2D, 0x2E, 0x00, 0x00, 0x00, 0xFE },
    { 0x01, 0x26, 0x26, 0x00, 0x00, 0x00, 0x00, 0xFE },
};

const void *const gDebugItemLabels_083ACC5C[3] __attribute__((section(".rodata.debug_item_labels"))) = { gDebugItemText_083ACC44[0], gDebugItemText_083ACC44[1], gDebugItemText_083ACC44[2] };

const u8 gDebugFaceText_083ACC68[2][8] __attribute__((section(".rodata.debug_face_text"))) = {
    { 0x0E, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE },
    { 0x0C, 0x29, 0x29, 0x25, 0x00, 0x00, 0x00, 0xFE },
};

const void *const gDebugFaceLabels_083ACC78[2] __attribute__((section(".rodata.debug_face_labels"))) = { gDebugFaceText_083ACC68[0], gDebugFaceText_083ACC68[1] };

/* No known menu reference; the stored pointers identify both records. */
const u8 gDebugChoiceText_083ACC80[2][8] __attribute__((section(".rodata.debug_choice_text"))) = {
    { 0x0E, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE },
    { 0x0C, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE },
};

const void *const gDebugChoiceLabels_083ACC90[2] __attribute__((section(".rodata.debug_choice_labels"))) = { gDebugChoiceText_083ACC80[0], gDebugChoiceText_083ACC80[1] };

const u8 gDebugRandomText_083ACC98[1][8] __attribute__((section(".rodata.debug_random_text"))) = {
    { 0x13, 0x31, 0x23, 0x2E, 0x1D, 0x22, 0x00, 0xFE },
};

const void *const gDebugRandomLabels_083ACCA0[1] __attribute__((section(".rodata.debug_random_labels"))) = { gDebugRandomText_083ACC98[0] };

const u8 gDebugBattleText_083ACCA4[1][8] __attribute__((section(".rodata.debug_battle_text"))) = {
    { 0x0E, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE },
};

const void *const gDebugBattleLabels_083ACCAC[1] __attribute__((section(".rodata.debug_battle_labels"))) = { gDebugBattleText_083ACCA4[0] };

const u8 gDebugSoundText_083ACCB0[2][8] __attribute__((section(".rodata.debug_sound_text"))) = {
    { 0x13, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE },
    { 0x02, 0x21, 0x27, 0x00, 0x00, 0x00, 0x00, 0xFE },
};

const void *const gDebugSoundLabels_083ACCC0[2] __attribute__((section(".rodata.debug_sound_labels"))) = { gDebugSoundText_083ACCB0[0], gDebugSoundText_083ACCB0[1] };

const u8 gDebugMotionText_083ACCC8[1][8] __attribute__((section(".rodata.debug_motion_text"))) = {
    { 0x0E, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE },
};

const void *const gDebugMotionLabels_083ACCD0[1] __attribute__((section(".rodata.debug_motion_labels"))) = { gDebugMotionText_083ACCC8[0] };

