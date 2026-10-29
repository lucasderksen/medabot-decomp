#ifndef GUARD_ENCODED_LABEL_CATALOG_H
#define GUARD_ENCODED_LABEL_CATALOG_H
#include "global.h"

/* Native label bytes and roots, kept together for fixed-length copy bounds. */
struct MedalTypeLabelBank { u8 text[216]; const void *labels[34]; };
extern const struct MedalTypeLabelBank gMedalTypeLabelBank_083B64B8;

struct AttributeLabelBank { u8 text[212]; const void *labels[27]; };
extern const struct AttributeLabelBank gAttributeLabelBank_083B6618;

struct PartNameLabelBank { u8 text[620]; const void *labels[52]; };
extern const struct PartNameLabelBank gPartNameLabelBank_083B724C;

struct ModelNameLabelBank { u8 text[1116]; const void *labels[120]; };
extern const struct ModelNameLabelBank gModelNameLabelBank_083BA1FC;

struct LegTypeLabelBank { u8 text[52]; const void *labels[7]; };
extern const struct LegTypeLabelBank gLegTypeLabelBank_083BEAC8;

#endif
