#ifndef GUARD_EQUIPMENT_MENU_DATA_H
#define GUARD_EQUIPMENT_MENU_DATA_H
#include "global.h"
/* 08019D9C sign-extends xOffset, but adds yAdd as an unsigned byte. */
struct EquipmentPlacement { s8 xOffset; u8 yAdd, paletteAdd, mirror; };
extern const struct EquipmentPlacement gEquipmentPlacements[17];
extern const u8 gEquipmentColumnLookup[7][11];
#endif
