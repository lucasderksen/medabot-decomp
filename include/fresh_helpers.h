#ifndef GUARD_FRESH_HELPERS_H
#define GUARD_FRESH_HELPERS_H
#include "global.h"
#include "scene_asset_data.h"
#include "map_metadata.h"
void StartChoiceBoxAfterDialogue(u32 first);
u32 RunChoiceBoxAfterDialogue(void);
u32 sub_08048088(u32 mode);
const void *sub_080480D4(u32 index);
void sub_080480E4(void);
void StepMapTileAnimation(void);
s32 sub_08048210(s32 value);
void LoadSelectedObjTileSlots(void);
void LoadObjTilesIntoAllSlots(s32 value);
void LoadMapBgPalettes(void);
u32 sub_080483F8(void);
#endif
