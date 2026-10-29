#ifndef GUARD_INVENTORY_SELECTION_DATA_H
#define GUARD_INVENTORY_SELECTION_DATA_H
#include "global.h"
/* Six-byte copy stride in 08015668. Bytes 1 and 5 select dialogue tables. */
struct InventorySelectionRecord {
    u8 id, category, byte02, byte03, byte04, message;
};
struct InventoryCursorPoint { u8 tileX, tileY; };
/* Each concrete cursor table appends count points after this two-byte header. */
struct InventoryCursorHeader { u8 count, reserved; };
extern const struct InventorySelectionRecord gInventorySelectionRecords[52];
extern const u8 gInventorySelectionLists[30][3];
#endif
