/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "display_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 gState0NextCommands_083B6100;
extern s32 gUnknown_0300049A;
extern s32 gUnknown_0300059A;

void sub_0801DD74(void);
void sub_08022FB4(void);

void sub_0801DD74(void) {
    u8 *work0;
    work0 = (u8 *) &gState0NextCommands_083B6100;
    sub_08040BD8((*(u8 **)((u8 *)(work0) + 0x70)), 0x21U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        sub_0803F63C((gState0TransferWork.bytes[0xDE] << 8) + (u8 *)&gUnknown_0300049A, gDebugMenuTextBuffer, 0xEU);
        gState0TransferWork.bytes[0xA6] = 0x16;
        sub_08040CD0(0x21U, 1U);
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08022FB4(void) {
    sub_0803F63C((gState0TransferWork.bytes[0x88] << 8) + (u8 *)&gUnknown_0300059A, gDebugMenuTextBuffer, 0xEU);
    gState0TransferWork.bytes[0xA6] = 0x28;
    gState0TransferWork.bytes[0xAA] += 1;
}
