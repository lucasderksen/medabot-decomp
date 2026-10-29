#ifndef GUARD_SCENE_SETUP_DATA_H
#define GUARD_SCENE_SETUP_DATA_H
#include "main_callbacks.h"

/* 0804842C indexes four-byte records and reads offsets 0/1 or 2/3. */
struct SceneTransitionChoice { u8 firstFlag, firstScene, secondMode, secondScene; };

extern const u8 gContinuedLookup_083D2A30[16];
extern const u8 gObjectFactorBytes_083D2A40[3];
extern const u8 gObjectRowBytes_083D2A43[64];
extern const u8 gUnknown_083D2A83[5];
extern const u8 gFrameByteLookup_083D2A88[16];
extern const u8 gSceneEightByteRows_083D2A98[128];
extern const u8 gActionPaletteSelector_083D2B18[14];
extern const u8 gFreshBytes_083D2B26[16];
extern const u8 gSetupByteLookup_083D2B66[5];
extern const u8 gSelectorLookup_083D2B6B[192];
extern const u8 gUnknown_083D2C2B[9];
extern const u8 gUnknown_083D2C34[36];
extern const u8 gUnknown_083D2C59[4];
extern const u8 gFramePriorityLookup_083D2C5D[176];
extern const u8 gObjectAuxiliaryLookup_083D2D0D[176];
extern const u8 gCopiedBytes_083D2DBD[176];
extern const u8 gSceneSourceAlignment_083D2E6D[3];
extern const struct SceneTransitionChoice gSceneTransitionChoices_083D2B36[12];
extern const u8 gUnknown_083D2C58;
extern const MainCallback gUnknownCallbacks_083D5FF4[64];

#endif
