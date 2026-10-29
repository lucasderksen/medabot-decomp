#ifndef GUARD_BRIDGE_SEGMENTS_H
#define GUARD_BRIDGE_SEGMENTS_H
#include "global.h"
struct BridgeSegment {
    u8 startX, startY, endX, endY;
};
extern const struct BridgeSegment gBridgeSegments_08485AEC[8][3];
#endif
