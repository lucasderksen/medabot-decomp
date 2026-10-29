#include "bios_lz77_streams.h"
#include "ui_graphics_data.h"

extern const u16 gScenePalette_087CDCE0[16][16];
extern const u16 gScenePalette_087D1E74[16][16];
extern const u16 gScenePalette_087D5758[16][16];

const u8 *const gSceneBackgroundGraphics_08486DC4[12] = {
    (const u8 *)gBiosLz77Stream_087C9FF4,
    (const u8 *)gBiosLz77Stream_087CDEE0,
    (const u8 *)gBiosLz77Stream_087D5958,
    (const u8 *)gBiosLz77Stream_087D83E4,
    (const u8 *)gBiosLz77Stream_087DB0AC,
    (const u8 *)gBiosLz77Stream_087DDFB4,
    (const u8 *)gBiosLz77Stream_087E1C04,
    (const u8 *)gBiosLz77Stream_087D2074,
    (const u8 *)gBiosLz77Stream_087E5258,
    (const u8 *)gBiosLz77Stream_087E7BC8,
    (const u8 *)gBiosLz77Stream_087EA7B8,
    (const u8 *)gBiosLz77Stream_087ED750,
};

const u8 *const gSceneBackgroundMaps_08486DF4[12] = {
    (const u8 *)gBiosLz77Stream_087CD9B0,
    (const u8 *)gBiosLz77Stream_087D1B48,
    (const u8 *)gBiosLz77Stream_087F013C,
    (const u8 *)gBiosLz77Stream_087F0460,
    (const u8 *)gBiosLz77Stream_087F0788,
    (const u8 *)gBiosLz77Stream_087F0AA0,
    (const u8 *)gBiosLz77Stream_087F0DD0,
    (const u8 *)gBiosLz77Stream_087D5440,
    (const u8 *)gBiosLz77Stream_087F1100,
    (const u8 *)gBiosLz77Stream_087F13FC,
    (const u8 *)gBiosLz77Stream_087F16FC,
    (const u8 *)gBiosLz77Stream_087F1A1C,
};

const u8 *const gSceneBackgroundPalettes_08486E24[12] = {
    (const u8 *)gScenePalette_087CDCE0,
    (const u8 *)gScenePalette_087D1E74,
    (const u8 *)gBackgroundPaletteBank_087F1D40,
    (const u8 *)gBackgroundPaletteBank_087F1F00,
    (const u8 *)gBackgroundPaletteBank_087F20C0,
    (const u8 *)gBackgroundPaletteBank_087F2280,
    (const u8 *)gBackgroundPaletteBank_087F2440,
    (const u8 *)gScenePalette_087D5758,
    (const u8 *)gBackgroundPaletteBank_087F2600,
    (const u8 *)gBackgroundPaletteBank_087F2800,
    (const u8 *)gBackgroundPaletteBank_087F29C0,
    (const u8 *)gBackgroundPaletteBank_087F2B80,
};

volatile u32 *const gSoundFifos_08486E54[2] = {
    (volatile u32 *)0x040000A0,
    (volatile u32 *)0x040000A4,
};

volatile u32 *const gSoundTimers_08486E5C[2] = {
    (volatile u32 *)0x04000100,
    (volatile u32 *)0x04000104,
};

volatile u16 *const gSoundDmaControls_08486E64[2] = {
    (volatile u16 *)0x040000C6,
    (volatile u16 *)0x040000D2,
};
