#ifndef GUARD_ENCOUNTER_RECORDS_H
#define GUARD_ENCOUNTER_RECORDS_H
#include "global.h"

#define ENCOUNTER_MAP_COUNT 192
#define ENCOUNTER_RECORD_COUNT 246
#define ENCOUNTER_PALETTE_COUNT 124

/* 08011E20 copies 40 bytes and, when selectionMode is zero, independently
 * selects each of the four choice bytes in each 12-byte member. All stored
 * records have selectionMode == 1. Other byte meanings remain provisional. */
struct EncounterMemberRecord {
    u8 choices[4];
    u8 unknown04[8];
};
struct EncounterRecord {
    u8 assetIndex;
    u8 unknown01;
    u8 memberCount;
    u8 selectionMode;
    struct EncounterMemberRecord members[3];
};
extern const u8 gUnknownBytes_083BEB94[ENCOUNTER_PALETTE_COUNT];
extern const u8 gEquipmentTable_083BEC10[ENCOUNTER_MAP_COUNT][8];
extern const u8 gState0EquipmentChoices_083BF210[ENCOUNTER_MAP_COUNT][4];
extern const struct EncounterRecord gEncounterRecords_083BF510[ENCOUNTER_RECORD_COUNT];
extern const u8 *const gState0EncounterRecords_083C1B80[ENCOUNTER_RECORD_COUNT];
#endif
