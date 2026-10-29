/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "main_callbacks.h"


s32 sub_0806B2B8(u32 arg0);

s32 sub_0806B2B8(u32 arg0) {
    u32 zero;
    void *temp_r2;
    struct FrameObject *frames;

    arg0=(u32)arg0<<24;
    frames=gFrameObjects;
    temp_r2=(void*)(((u32)arg0>>18)+(u32)frames);
    if (1 & (*(u16 *)((u8 *)(temp_r2) + 0x1A))) {
        (*(u8 *)((u8 *)(temp_r2) + 8)) = (u8) ((*(u8 *)((u8 *)(temp_r2) + 8)) - 1);
        (*(u8 *)((u8 *)(temp_r2) + 9)) = (u8) ((*(u8 *)((u8 *)(temp_r2) + 9)) - 1);
    }
    (*(u16 *)((u8 *)(temp_r2) + 0x18)) = (u16) ((*(u16 *)((u8 *)(temp_r2) + 0x18)) + 0x40);
    if ((u32)(*(u16 *)((u8 *)(temp_r2) + 0x1A))>0x8FU) {
        zero=0;
        (*(u16 *)((u8 *)(temp_r2) + 0x18))=zero;
        return zero;
    }
    return 1;
}
