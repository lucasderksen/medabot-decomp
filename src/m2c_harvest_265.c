/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_work.h"

struct FamilyWork3C8AC {u8 pad[0xF8];u8 flags;};

extern const void*const gUnknown_083B4C60[];
extern const void*const gUnknown_083CEDF4[];
extern struct FamilyWork3C8AC gUnknown_03001800;
extern void sub_0801BD58(const void*,u32);

void sub_0803C8AC(void);

void sub_0803C8AC(void) {

    struct FrameObject *temp_r0_2;
    struct FrameObject *temp_r0_3;
    struct FrameObject *temp_r2;
    struct FrameObject *temp_r4;
    u16 temp_r0;
    u8 temp_r6;
    u32 frameRoot;
    u32 lateRoot;

    frameRoot=(u32)gFrameObjects;
    temp_r2=(struct FrameObject*)(frameRoot+((u32)gState0TypedWork.bytes[0x12F]<<6));
    temp_r0 = (*(u16 *)((u8 *)(temp_r2) + 0x30));
    if (temp_r0 != 0) {
        (*(u16 *)((u8 *)(temp_r2) + 0x30)) = (u16) (temp_r0 - 1);
        return;
    }
    sub_0801BD58(gUnknown_083CEDF4[temp_r2->byte2B], 1);
    temp_r0_2 = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
    temp_r0_2->unknown23[5] += 1;
    temp_r4 = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
    if (1 & temp_r4->unknown23[5]) {
        temp_r6 = temp_r4->unknown23[4];
        if (temp_r6 == 0) {
            if (!(2 & gUnknown_03001800.flags)) {
                sub_0803F1C8((u32) temp_r4->unknown2C[2], (u32) temp_r4->unknown2C[3], (temp_r4->screenX + temp_r4->unknown2C[1]) & 0x3F, (u32) temp_r4->screenY, gUnknown_083B4C60[temp_r4->unknown2C[0]], (u32) *(volatile u16*)0x04000008, (u32) temp_r6);
            } else {
                sub_0803F1C8((u32) temp_r4->unknown2C[2], (u32) temp_r4->unknown2C[3], (temp_r4->screenX - temp_r4->unknown2C[1]) & 0x3F, (u32) temp_r4->screenY, gUnknown_083B4C60[temp_r4->unknown2C[0]], (u32) *(volatile u16*)0x04000008, (u32) temp_r6);
            }
            lateRoot=(u32)gFrameObjects;
            temp_r0_3=(struct FrameObject*)(lateRoot+((u32)gState0TypedWork.bytes[0x12F]<<6));
            temp_r0_3->unknown2C[1] += 1;
        }
    }
}
