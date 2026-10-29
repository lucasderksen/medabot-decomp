/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"

struct ContinuedSceneReturnWork {u8 pad00[4];s16 previousState;};

extern const u8 gUnknown_087B2EE0[];
extern const u8 gUnknown_087C23B8[];
extern const u8 gUnknown_087C378C[];
extern const u8 gUnknown_087C4B1C[];
extern const u8 gUnknown_087C4CE8[];
extern const u8 gUnknown_087C4F34[];
extern const u8 gUnknown_087C52A4[];
extern const u8 gUnknown_087C5404[];
extern const u8 gUnknown_087C568C[];
extern struct ContinuedSceneReturnWork gGraphicsTransferCounter;

void sub_080709D4(void);

void sub_080709D4(void) {
    s16 *destinationX;
    s32 horizontalOffset;
    struct FrameObject *leftFrame;
    struct FrameObject *rightFrame;
    struct FrameObject *upperFrame;
    struct FrameObject *sourceFrame;
    s32 nextCounter;
    s32 rightSlot;
    s32 priority;
    s32 counter;

    LZ77UnCompVram(gUnknown_087C23B8, (void *)0x06004000);
    LZ77UnCompVram(gUnknown_087C378C, (void *)0x06008000);
    LZ77UnCompVram(gUnknown_087C4B1C, (void *)0x06006800);
    LZ77UnCompVram(gUnknown_087C4CE8, (void *)0x06007000);
    LZ77UnCompVram(gUnknown_087C4F34, (void *)0x06007800);
    LZ77UnCompVram(gUnknown_087C52A4, (void *)0x0600A800);
    LZ77UnCompVram(gUnknown_087C5404, (void *)0x0600B000);
    LZ77UnCompVram(gUnknown_087C568C, (void *)0x0600B800);
    LZ77UnCompVram(gUnknown_087B2EE0, (void *)0x06010000);
    counter = 0;
    do {
        sub_08048864((u8) counter, 0xC800U, 0x50EU, 4U, 3U);
        leftFrame = &gFrameObjects[counter];
        horizontalOffset = counter * 8;
        leftFrame->screenX = horizontalOffset + 0x78;
        leftFrame->screenY = 0;
        priority = counter + 0x40;
        leftFrame->priority = priority;
        nextCounter = counter + 1;
        leftFrame->commandStopped = nextCounter;
        rightSlot = counter + 0xB;
        sub_08048864((u8) rightSlot, 0xC800U, 0x50EU, 4U, 3U);
        rightFrame = &gFrameObjects[rightSlot];
        rightFrame->screenX = 0x70 - horizontalOffset;
        rightFrame->screenY = 0;
        rightFrame->priority = priority;
        rightFrame->commandStopped = counter + 0xC;
        counter = nextCounter;
    } while ((s32) counter <= 0xA);
    gFrameObjects[0xA].commandStopped = 0xFF;
    gFrameObjects[0x15].commandStopped = 0xFF;
    counter = 0;
    upperFrame = &gFrameObjects[0x16];
    do {
        sub_08048864((u8)(counter + 0x16), 0xCC00U, 0U, (u8) counter, 1U);
        upperFrame->screenY = 0x40;
        upperFrame++;
        counter += 1;
    } while ((s32) counter <= 3);
    gFrameObjects[0x16].screenX = 0x10;
    gFrameObjects[0x16].priority = 8;
    gFrameObjects[0x17].screenX = 0xD0;
    gFrameObjects[0x17].priority = 8;
    gFrameObjects[0x18].screenX = 0x10;
    gFrameObjects[0x18].priority = 4;
    gFrameObjects[0x18].screenY = 0x30;
    gFrameObjects[0x19].screenX = 0xD0;
    gFrameObjects[0x19].priority = 6;
    counter = 0;
    destinationX = &gFrameObjects[0x1A].screenX;
    sourceFrame = &gFrameObjects[0x16];
    do {
        sub_08048864((u8)(counter + 0x1A), 0xCC08U, 0x513U, 0xEU, 3U);
        destinationX[0] = (s16) (u16) sourceFrame->screenX;
        destinationX[1] = 0x40;
        destinationX += 0x20;
        sourceFrame++;
        counter += 1;
    } while (counter <= 3);
    gFrameObjects[0x1C].screenY = 0x38;
    /* Observed signed halfword at transfer-work +4. */
    gGraphicsTransferCounter.previousState = 6;
    gUnknown_0300137C = 4;
}
