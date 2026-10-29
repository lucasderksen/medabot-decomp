#ifndef GUARD_INVENTORY_KIND_DATA_H
#define GUARD_INVENTORY_KIND_DATA_H

#include "global.h"

/* ROM stride16; recordByte fields name their observed inventory destinations. */
struct InventoryKindMetadata {
    u8 identifier;
    u8 recordByte4;
    u8 recordByte6;
    u8 levelThresholds[4];
    u8 recordByte7;
    u8 baseStats[8];
};
extern const struct InventoryKindMetadata gInventoryKindMetadata[30];
extern const u8 *const gInventoryAppearanceAssets[30][5];

#endif
