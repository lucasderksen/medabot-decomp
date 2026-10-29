#ifndef GUARD_PART_LABEL_BANKS_H
#define GUARD_PART_LABEL_BANKS_H
#include "global.h"

/* Native labels and roots share one object for fixed-length copy bounds. */
struct PartLabelBank { u8 text[4884]; const void *labels[480]; };
extern const struct PartLabelBank gPartLabelBank_083BA838;

struct AuxiliaryPartLabelBank { u8 text[532]; const u8 *labels[60]; };
extern const struct AuxiliaryPartLabelBank gAuxiliaryPartLabelBank_083BE654;

/* Four six-character encoded part codes per model, each followed by FE.
 * The native pointer directory follows the 480 fixed-width strings. */
struct PartCodeLabelBank { u8 text[480][7]; const u8 *labels[480]; };
extern const struct PartCodeLabelBank gPartCodeLabelBank_083BC2CC;

#endif
