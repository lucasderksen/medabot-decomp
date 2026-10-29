/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "display_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "state0_work.h"

extern const void *const gState0NextText_083B4C60[];
extern const void *const gUnknown_083CEDF4[];
extern void sub_0801BD58(const void *, u32);

void sub_0803CAB0(void);

void sub_0803CAB0(void) {
    struct FrameObject *frames = gFrameObjects;
    const void *const *firstTable;
    const void *const *secondTable;
    struct FrameObject *temp_r2;
    struct FrameObject *temp_r4;
    u16 temp_r0;
    u8 temp_r6;

    temp_r2 = &frames[gState0TypedWork.bytes[0x12F]];
    temp_r0 = (*(u16 *)((u8 *)(temp_r2) + 0x30));
    if (temp_r0 != 0) {
        (*(u16 *)((u8 *)(temp_r2) + 0x30)) = (u16) (temp_r0 - 1);
        return;
    }
    firstTable = gUnknown_083CEDF4;
    sub_0801BD58(firstTable[temp_r2->byte2B], 0);
    if (gState0TypedWork.bytes[0x66] == 0xFF) {
        sub_08040CD0(gState0TypedWork.bytes[0x12F], 1U);
        return;
    }
    temp_r4 = &frames[gState0TypedWork.bytes[0x12F]];
    temp_r6 = temp_r4->unknown2C[1];
    if (temp_r6 == 0) {
        sub_0803F1C8((u32) temp_r4->unknown2C[2], (u32) temp_r4->unknown2C[3], (u32) temp_r4->screenX, (u32) temp_r4->screenY, (secondTable = gState0NextText_083B4C60, secondTable[temp_r4->unknown2C[0]]), (u32) *(volatile u16 *)0x04000008, (u32) temp_r6);
    }
}
