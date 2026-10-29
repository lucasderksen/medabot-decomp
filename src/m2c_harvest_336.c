/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "later_graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct FrameSelectionF6CC {u8 prefix[0xD2];u8 selected[3];};

extern const u8 *const gState0NextCommands_083B6100[]; /* Observed index0x6D. */
extern const u8 gUnknown_084E2E24[];
extern const u8 gUnknown_084E4658[32];
extern const u8 gUnknown_08510498[32];

void sub_0802F6CC(void);

void sub_0802F6CC(void) {


    /* Three selected frame slots, within the complete 128-record array. */
    struct FrameObject *frame;
    struct FrameObject (*frameBase)[128];
    u32 entryIndex;
    u32 frameIndex;

    LeDecompress(gUnknown_084E2E24, (void *)0x06014800);
    CpuFastSet(gUnknown_08510498, (void *)0x050002E0, 8U);
    CpuFastSet(gUnknown_084E4658, (void *)0x050002C0, 8U);
    entryIndex = 0;
    do {
        if (((struct FrameSelectionF6CC *)gState0TransferWork.bytes)->selected[entryIndex] != 0) {
            frameBase = &gFrameObjects;
            frameIndex = entryIndex + 0x21;
            frame = (struct FrameObject *)((u8 *)frameBase + (frameIndex<<6));
            frame->flags = 0xC404;
            frame->tableSelector = 0;
            frame->screenX = 0x78;
            frame->screenY = 0xF0;
            frame->palette = 7;
            frame->priority = 0xF0;
            frame->unknown23[1] = 4;
            frame->unknown23[2] = 0;
            (*(s16 *)((u8 *)frame+0x30)) = 0;
            sub_08040B90(gState0NextCommands_083B6100[0x6D], frameIndex);
            if (1 & gState0TransferWork.bytes[0xF8]) {
                frame->flags |= 0x1000;
            }
        }
        entryIndex += 1;
    } while (entryIndex <= 2U);
    sub_08074DE0(0x61U);
    gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
}
