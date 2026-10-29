#ifndef GUARD_ACTION_SCENE_DATA_H
#define GUARD_ACTION_SCENE_DATA_H
#include "global.h"

#define ACTION_SCENE_COUNT 132
#define ACTION_MOTION_GROUPS 31
#define ACTION_MOTION_DIRECTIONS 32
#define ACTION_MOTION_FRAMES 4
/* Units are 32-byte tiles. A zero units halfword ends a graphic-piece list;
 * such terminals occupy two bytes, so the backing store remains flat. */
struct ActionGraphicPiece { u16 units, asset; };
extern const u8 gActionByteWords_083C6A04[676];
extern const u8 *const gActionBytePointers_083C6CA8[ACTION_SCENE_COUNT];
/* Physical spans include the zero tails before the following stored objects;
 * the original C declaration bounds are not recovered. */
extern const u8 gActionParameterLengths_083C6EB8[144];
extern const u8 gActionPartText_083C6F48[29];
extern const void *const gState0PartMessages_083C6F68[4];
/* Native index: group * 256 + direction * 8 + frame * 2; Y then X.
 * Each halfword holds a signed delta, added modulo the screen masks. */
extern const u16 gUnknownWords_083C6F78[ACTION_MOTION_GROUPS * 256];
extern const u8 gActionPoseVariants_083CAD78[124];
extern const s16 gActionHalfwordWords_083CADF4[6584];
extern const s16 *const gUnknown_083CE164[ACTION_SCENE_COUNT];
extern const u8 gUnknown_083CE374[156];
extern const u16 gActionGraphicWords_083CE410[248];
extern const struct ActionGraphicPiece *const gUnknown_083CE600[ACTION_SCENE_COUNT];
extern const u16 gActionTileAnimationWords_083CE810[754];
extern const void *const gUnknown_083CEDF4[37];
extern const u8 gUnknown_083CEE88[128];
extern const u8 gUnknown_083CEF08[128];
extern const u8 gUnknown_083CEF88[128];
extern const u8 gUnknown_083CF008[64];
extern const u8 gUnknown_083CF048[64];
extern const u8 gUnknown_083CF088[64];
extern const u8 gUnknown_083CF0C8[64];
extern const u8 gUnknown_083CF108[64];
extern const u8 gUnknown_083CF148[64];
extern const u8 gUnknown_083CF188[64];
extern const u8 gUnknown_083CF1C8[64];
extern const u8 gUnknown_083CF208[64];
extern const u8 gUnknown_083CF248[64];
extern const u8 gUnknown_083CF288[64];
extern const u8 gUnknown_083CF2C8[64];
#endif
