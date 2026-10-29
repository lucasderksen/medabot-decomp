#ifndef GUARD_PART_METADATA_DATA_H
#define GUARD_PART_METADATA_DATA_H
#include "global.h"
/* 08042B58 copies one 16-byte part slot. Field names retain unknown meaning.
 * Rank and scoreFactor are used by 0805B0D8; score is scoreFactor * 100.
 * Slot 3 byte01 is also used as a value biased by 100 in 08068F50. */
struct PartMetadataRecord {
    u8 byte00, byte01, byte02, rank;
    u8 bytes04[7];
    u8 scoreFactor;
    u8 bytes0C[4];
};
extern const struct PartMetadataRecord gPartMetadata_083B83FC[120][4];
#endif
