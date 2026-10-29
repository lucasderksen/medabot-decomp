#ifndef GUARD_GRAPHICS_H
#define GUARD_GRAPHICS_H

#include "gba.h"

struct GraphicsRows
{
    s32 width;
    s32 height;
    u32 unknown08;
    u32 unknown0C;
    u16 data[1];
};

extern u16 gTilemapEntryOffset;
extern s16 gSineTable[];
extern u32 gRandomTable[16];
extern u32 gRandomCounter;
union RandomWord
{
    u32 value;
    s16 halves[2];
};
extern union RandomWord gRandomValue;
extern union RandomWord gRandomState;

void LoadLeTilemap(u32 x, u32 y, const u8 *source, u32 control, u16 entryOffset);
void LoadLeTileRows(u32 x, u32 y, const u8 *source, u32 control);
void LoadLeData(const u8 *source, void *destination);
void CopyTilemap(u32 x, u32 y, const struct GraphicsRows *source, u32 control);
void CopyTileRows(u32 x, u32 y, const struct GraphicsRows *source, u32 control);
void CopyLargeTilemap(u16 *destination, const struct GraphicsRows *source);
void SetBg3Affine(s32 scale, s32 angle, s32 x, s32 y, s32 centerX, s32 centerY);
void PrepareBg2ScanlineAffine(s32 increment, s32 angle, s32 unused, s32 x, s32 y, s32 centerX, s32 centerY);
void StartBg2ScanlineDma(void);
void StopBg2ScanlineDma(void);
u32 NextRandom(u16 upperBound);
s32 Lerp4096(s32 a, s32 b, s32 weight);
void SnapshotPalettes(void);
void BlendPalettes(u16 color, u32 weight);
void ApplyBlendedPalettes(void);
void BlendPalette16(const u16 *source, u16 *destination, u16 color, u32 weight);

#endif
