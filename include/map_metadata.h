#ifndef GUARD_MAP_METADATA_H
#define GUARD_MAP_METADATA_H
#include "continued_scene_records.h"

#define MAP_METADATA_COUNT 192
#define MAP_TILE_ANIMATION_COUNT 153
struct MapTileAnimation
{
    u8 tileUnits;
    u8 frameCount;
    u8 totalTiles;
    u8 sequence[128];
};
/* Native 08052E88 reads destination map/direction and destination cell X/Y.
 * 08052C68 reads the high flags nibble as an interaction value. */
struct MapExitRecord
{
    u8 x, y, destinationMap, flags;
    u8 unknown04[2];
    u8 destinationX, destinationY;
};
extern const struct MapTileAnimation gMapTileAnimations_08404634[MAP_TILE_ANIMATION_COUNT];
extern const u8 *const gFreshPointers_08409480[256];
extern const struct CellDirectionRecord gMapDirectionRows_08409880[MAP_METADATA_COUNT * 32];
extern const struct CellDirectionRecord *const gCellDirectionTables_0840F880[MAP_METADATA_COUNT];
extern const u8 gMapDialogueBytes_0840FB80[8031];
extern const void *const gContinuedScripts_08411AE0[202];
extern const u8 gMapExitBytes_08411E08[4184];
extern const u8 *const gContinuedMapEntries_08412E60[MAP_METADATA_COUNT];
extern const u8 *const gPaletteSelectorTables_08413160[MAP_METADATA_COUNT];
extern const u8 gMapPaletteSelectors_08413460[MAP_METADATA_COUNT][14];
extern const u8 *const gFreshPointers_08413EE0[16];
extern const u8 gMapIndirectSelectors_08413F20[16][13];
#endif
