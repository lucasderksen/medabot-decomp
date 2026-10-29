#ifndef GUARD_CONTINUED_MAP_DATA_H
#define GUARD_CONTINUED_MAP_DATA_H
#include "global.h"

#define CONTINUED_MAP_COUNT 192

extern const u8 gContinuedMapDimensions_083F8900[CONTINUED_MAP_COUNT][2];
extern const void *const gContinuedMapTiles_083F8A80[CONTINUED_MAP_COUNT];
extern const void *const gContinuedMapExtra_083F8D80[CONTINUED_MAP_COUNT];
extern const void *const gContinuedMapData_083F9080[CONTINUED_MAP_COUNT][3];

/* Observed first eight bytes at the setup pointer; complete size unknown. */
struct MapHalfwordPairs { u16 low0, high0, low1, high1; };
extern void *gSetupPointer_03006D14;
extern void *gSetupPointer_030057D8;
extern void *gSetupPointer_03006D30;
extern const u8 gSceneEightByteRows_083D2A98[];
#endif
