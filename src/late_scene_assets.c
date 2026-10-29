#include "global.h"

extern const u16 gObjectPaletteBanks_0807C210[53][16];
extern const u8 gBiosLz77Stream_087B0AF0[];
extern const u8 gBiosLz77Stream_087B1CDC[];
extern const u8 gBiosLz77Stream_087C68B8[];
extern const u8 gBiosLz77Stream_087C7E20[];
extern const u8 gBiosLz77Stream_087C901C[];
extern const u8 gBiosLz77Stream_087C92B8[];

const u16 gLateSceneBackgroundPalettes[2][16] = {
    { 0x0000, 0x73FF, 0x377F, 0x029E, 0x01F8, 0x0172, 0x04EC, 0x0887, 0x77DF, 0x5F39, 0x4A73, 0x35AD, 0x294A, 0x2108, 0x1084, 0x126E },
    { 0x0000, 0x7FFC, 0x6B57, 0x56B2, 0x420D, 0x318A, 0x3694, 0x3210, 0x2DAC, 0x2126, 0x18C6, 0x02BB, 0x01D5, 0x7EDC, 0x7191, 0x4C45 },
};

const u8 *const gLateSceneTileStreams[2] = { gBiosLz77Stream_087C68B8, gBiosLz77Stream_087C7E20 };

const u8 *const gLateSceneMapStreams[2] = { gBiosLz77Stream_087C901C, gBiosLz77Stream_087C92B8 };

const u16 *const gLateSceneBackgroundPalettePointers[2] = { gLateSceneBackgroundPalettes[0], gLateSceneBackgroundPalettes[1] };

const u8 *const gLateSceneObjectStreams[2] = { gBiosLz77Stream_087B0AF0, gBiosLz77Stream_087B1CDC };

const u16 *const gLateSceneObjectPalettePointers[2] = { gObjectPaletteBanks_0807C210[27], gObjectPaletteBanks_0807C210[32] };

/* End command, key-wait mode 2, then two original zero alignment bytes. */
const u8 gLateSceneWaitScript[4] = { 0xFF, 2, 0, 0 };
