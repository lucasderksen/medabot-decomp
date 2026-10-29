#ifndef GUARD_CONTINUED_SCENE_RECORDS_H
#define GUARD_CONTINUED_SCENE_RECORDS_H
#include "global.h"

/* Matched definitions in m2c_harvest_42.c and m2c_harvest_46.c. */
s32 sub_0803598C(s32 slot, s32 index, s32 value);
s32 sub_080359D8(s32 slot, s32 index, s32 value);
s32 sub_08035A24(s32 slot, s32 index, s32 value);
s32 sub_08035A70(s32 slot, s32 index, s32 value);
/* Observed stride-eight RAM record view. Names and original source types remain provisional; the array extent is unknown. */
union SelectionFlags
{
    u8 value;
    struct { u8 index : 5; u8 unknown : 1; u8 auxiliary : 1; u8 active : 1; } __attribute__((packed)) bits;
} __attribute__((packed));
struct SelectionRecord
{
    u8 x, y;
    u16 attributes;
    union SelectionFlags flags;
    u8 frame;
    u16 unknown06;
};
extern struct SelectionRecord gSelectionRecords_03005DBC[];
/* A zero directions byte stops 08052624's scan; value selects a map script.
 * Stored bank/directory bounds are in map_metadata.h. Map 81 scans its next
 * map's first (zero) record because its own 32 stored slots have no sentinel. */
struct CellDirectionRecord { u8 x, y, directions, value; };
extern const struct CellDirectionRecord *const gCellDirectionTables_0840F880[];
extern u8 gLaterBuffer_03003810[];
#endif
