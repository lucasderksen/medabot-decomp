#ifndef GUARD_ENCODED_LABELS_H
#define GUARD_ENCODED_LABELS_H
#include "global.h"

/* Whole-object byte views permit the original fixed-length label copies to
 * pass a terminator into the neighboring label or pointer data. */
struct ActionLabelBank { u8 text[60]; const u8 *labels[8]; };
extern const struct ActionLabelBank gActionLabelBank_083B700C;

struct MapPartLabelBank { u8 text[80]; const u8 *labels[11]; };
extern const struct MapPartLabelBank gMapPartLabelBank_083BEB18;

struct EncounterLabelBank { u8 text[900]; const u8 *labels[96]; };
extern const struct EncounterLabelBank gEncounterLabelBank_083C3D34;

/* Native absolute alias for the labels member above. */
extern const u8 *const gUnknownPointers_083B7048[8];

#endif
