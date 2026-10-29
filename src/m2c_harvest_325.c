/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "frame_objects.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct FrameSelection2A9B8 { u8 p0[0x60]; u8 firstSourceSlot; u8 p61[0xAA - 0x61]; u8 phase; u8 pAB[0xD2 - 0xAB]; u8 selected[3]; };

extern const u8 *const gState0NextCommands_083B6100[];
extern s32 sub_08019440(s32);
extern struct FrameSelection2A9B8 gCounter6ED08_03001800;
extern void sub_080383E8(void);

void sub_0802A9B8(void);

void sub_0802A9B8(void) {

    s32 finished;
    s32 active;
    u32 slot;

    finished = 0;
    active = 0;
    slot = 0;
    do {
        if (gCounter6ED08_03001800.selected[slot] != 0) {
            active += 1;
            sub_08019544(gCounter6ED08_03001800.firstSourceSlot + slot);
            if (sub_08019440(gCounter6ED08_03001800.firstSourceSlot + slot) != 0) {
                finished += 1;
            }
            sub_08040BD8(gState0NextCommands_083B6100[99], (u8) (slot + 0x22));
            gFrameObjects[0x22 + slot].screenX = gFrameObjects[((gCounter6ED08_03001800.firstSourceSlot + slot) << 2) + 0x5D].screenX;
            gFrameObjects[0x22 + slot].screenY = gFrameObjects[((gCounter6ED08_03001800.firstSourceSlot + slot) << 2) + 0x5D].screenY - 0x10;
            sub_0801BC04(gCounter6ED08_03001800.firstSourceSlot + slot);
        }
        slot += 1;
    } while (slot <= 2U);
    sub_08040BD8(gState0NextCommands_083B6100[98], 0x21U);
    if (!(0x3F & gState0TypedWork.widths.word86)) {
        sub_08074DE0(0x33U);
    }
    gState0TypedWork.widths.word86 += 1;
    sub_080383E8();
    if ((finished == active) && ((u32) gState0TypedWork.widths.word86 > 0x3CU)) {
        sub_08040CD0(0x21U, 0x1BU);
        sub_0801A0D0();
        gCounter6ED08_03001800.phase = gCounter6ED08_03001800.phase + 1;
    }
}
