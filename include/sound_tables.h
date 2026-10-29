#ifndef GUARD_SOUND_TABLES_H
#define GUARD_SOUND_TABLES_H
#include "global.h"

/* PSG periods, wave volume codes, channel/FIFO masks and pitch ratios.
 * The native period lookup is unchecked; integer bus-address arithmetic
 * preserves its reads without imposing an artificial array index bound. */
u32 sub_080732B8(u32 index);

extern const u16 gUnknown_083ABB50[73];
extern const u8 gUnknown_083ABBE2[16];
extern const u8 gUnknown_083ABBF2[4];
extern const u8 gUnknown_083ABBF6[16];
extern const u16 gUnknown_083ABC08[2];
extern const u8 gUnknown_083ABC0C[2][16];
extern const u8 gUnknown_083ABC2C[2];
extern const u16 gUnknown_083ABC2E[2];
extern const u16 gUnknown_083ABC32[2][4];
extern const u16 gUnknown_083ABC42[2];
extern const u16 gPitchScale083ABC46[12];
extern const u16 gPitchLookupAnchor083ABC5E[129];

#endif
