/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"


void sub_0801A678(void);

void sub_0801A678(void) {
    u8 *base;
    u8 *pairCursor;
    u32 firstPairAddress;
    u32 pairIndex, nextPair, pairByteOffset, clearValue;

    pairIndex = 0;
    base = gState0TransferWork.bytes;
    pairCursor = base + 0x45;
    do {
        nextPair = pairIndex + 1;
        pairCursor[0] = pairCursor[2];
        pairCursor[1] = pairCursor[3];
        pairCursor += 2;
        pairIndex = nextPair;
    } while (nextPair <= 4);
    clearValue = 0;
    pairByteOffset = nextPair * 2;
    firstPairAddress = (u32)base + 0x45;
    *(u8 *)(pairByteOffset + firstPairAddress) = clearValue;
    pairByteOffset += 1;
    *(u8 *)(pairByteOffset + firstPairAddress) = clearValue;
}
