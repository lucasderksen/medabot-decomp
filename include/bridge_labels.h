#ifndef GUARD_BRIDGE_LABELS_H
#define GUARD_BRIDGE_LABELS_H
#include "global.h"
/* Glyph tokens: 0x14 ends the label; 0x15 emits a blank tile. */
struct BridgeLabelPool {
    u8 label0[8];
    u8 label1[9];
    u8 label2[13];
    u8 label3[10];
    u8 label4[8];
    u8 label5[6];
    u8 label6[12];
    u8 label7[9];
    u8 padding;
};
extern const struct BridgeLabelPool gBridgeLabelPool_08485A80;
extern const u8 *const gBridgeLabels_08485ACC[8];
#endif
