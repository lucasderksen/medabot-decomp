#include "global.h"

/* Participant by encounter variant, added to an 8-bit sine phase. */
const u8 gEncounterPhaseOffsets[2][11] __attribute__((aligned(1))) = {
    { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 },
    { 140, 60, 100, 80, 60, 40, 20, 10, 5, 70, 25 },
};
