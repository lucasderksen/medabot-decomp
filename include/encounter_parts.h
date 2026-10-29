#ifndef GUARD_ENCOUNTER_PARTS_H
#define GUARD_ENCOUNTER_PARTS_H

#include "global.h"

struct EncounterPartyParts
{
    u8 head[3];
    u8 right[3];
    u8 left[3];
    u8 legs[3];
};

/* Three parties; shifted byte views retain the rendering helpers' part bases. */
union EncounterParts
{
    struct EncounterPartyParts parties[3];
    u8 head[36];
    struct { u8 prefix[3]; u8 values[33]; } right;
    struct { u8 prefix[6]; u8 values[30]; } left;
    struct { u8 prefix[9]; u8 values[27]; } legs;
};

extern union EncounterParts gEncounterParts;
extern const u8 gEncounterFrameSlots[3][3];
extern const u8 gEncounterRowY[3];

typedef char EncounterPartsSize[(sizeof(union EncounterParts) == 36) ? 1 : -1];

#endif
