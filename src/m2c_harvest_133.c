/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "input.h"
#include "object_numeric_helpers.h"
#include "serial.h"

extern void sub_0806B718(s32);

s32 sub_0806C88C(void);

s32 sub_0806C88C(void) {
    u8 phase;
    /* ROM reserves an untouched 32-byte local region; original purpose unknown. */
    u8 reserved[32];

    phase = gFrameObjects->commandDelay;
    switch (phase) {                              /* irregular */
    case 0:
        sub_08048864(0U, 0xC000U, 0x33U, 0xCU, 3U);
        gFrameObjects->screenX = 0x78;
        gFrameObjects->screenY = 0x50;
        gFrameObjects->unknown1A = (u16) phase;
        gFrameObjects->commandDelay += 1;
        gFrameObjects[0x1E].frameAndGroup = (u16) phase;
        sub_08048864(0x21U, 0xCC08U, 0x12U, 2U, 3U);
        gFrameObjects[0x21].screenX = (s16) (u16) gFrameObjects[0x1E].screenX;
        gFrameObjects[0x21].screenY = (u16) gFrameObjects[0x1E].screenY + 0xA;
        break;
    case 1:
        gFrameObjects->unknown1A += 1;
        if ((gFrameObjects->unknown1A % 8) == 0) {
            gFrameObjects[0x20].screenY = (u16) gFrameObjects[0x20].screenY - 2;
        }
        if (((u32) gFrameObjects->unknown1A > 0xEBU) || (9 & (u8)gNewKeys)) {
            sub_0806B718(0);
            return 1;
        }
        break;
      default:
        break;
    }
    return 0;
}
