#ifndef GUARD_MAP_OBJECT_SPAWNS_H
#define GUARD_MAP_OBJECT_SPAWNS_H
#include "global.h"

#define MAP_OBJECT_MAP_COUNT 192
#define SCRIPT_GRAPHIC_SLOT_COUNT 26
/* Native 080513C8 sorts by order, tests visibilityMask using work[7FF],
 * and separates the attribute type nibble from its low twelve-bit ID.
 * Appearance FF suppresses actor creation; other values hold group/frame. */
struct MapObjectSpawn {
    u8 x, y;
    u16 attributes;
    u8 appearance;
    u8 order;
    u16 visibilityMask;
};
/* Special map 83 has a 21-column, 27-row direction-remapping grid. */
extern const u8 gObjectCellBytes_0847E40C[21 * 27];
extern const u8 gFreshBytes_0847E644[MAP_OBJECT_MAP_COUNT];
extern const void *const gUnknown_0847E704[SCRIPT_GRAPHIC_SLOT_COUNT];
extern const void *const gUnknown_0847E76C[SCRIPT_GRAPHIC_SLOT_COUNT];
extern const struct MapObjectSpawn gMapObjectSpawnBank_0847E7D4[2380];
extern const struct MapObjectSpawn *const gMapObjectLists_08483234[MAP_OBJECT_MAP_COUNT];
#endif
