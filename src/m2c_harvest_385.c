#include "frame.h"
#include "state0_work.h"
#include "display_helpers.h"
#include "frame_objects.h"

/* Preserve a distinct halfword snapshot for the countdown and zero entry. */
extern void sub_0801BD58(const void *, u32);
extern const void *const gState0NextText_083B4C60[];
extern const void *const gUnknown_083CEDF4[];


void sub_0803C7DC(void) {

    struct FrameObject *frames = gFrameObjects;
    const void *const *firstTable;
    const void *const *secondTable;
    struct FrameObject *initialFrame;
    struct FrameObject *clearedFrame;
    struct FrameObject *textFrame;
    u32 countdown;
    u16 snapshot;

    initialFrame = &frames[gState0TypedWork.bytes[0x12F]];
    countdown = (*(u16 *)((u8 *)initialFrame + 0x30));
    snapshot = countdown;
    if (snapshot != 0) {
        (*(u16 *)((u8 *)initialFrame + 0x30)) = (u16) (countdown - 1);
        return;
    }
    sub_0801BD58((firstTable=gUnknown_083CEDF4,firstTable[initialFrame->byte2B]), 0);
    if (gState0TypedWork.bytes[0x66] == 0xFF) {
        clearedFrame = &frames[gState0TypedWork.bytes[0x12F]];
        sub_0803EF8C((u32) clearedFrame->unknown2C[2], (u32) clearedFrame->unknown2C[3], (u32) clearedFrame->screenX, (u32) clearedFrame->screenY, (u32) *(volatile u16 *)0x04000008, (u32) snapshot);
        sub_08040CD0(gState0TypedWork.bytes[0x12F], 1U);
        return;
    }
    textFrame = &frames[gState0TypedWork.bytes[0x12F]];
    snapshot = textFrame->unknown2C[1];
    if (snapshot == 0) {
        sub_0803F15C((u32) textFrame->unknown2C[2], (u32) textFrame->unknown2C[3], (u32) textFrame->screenX, (u32) textFrame->screenY, (secondTable=gState0NextText_083B4C60,secondTable[textFrame->unknown2C[0]]), (u32) *(volatile u16 *)0x04000008, (u32) snapshot);
    }
}

void sub_0803C9E0(void) {

    struct FrameObject *frames = gFrameObjects;
    const void *const *firstTable;
    const void *const *secondTable;
    struct FrameObject *initialFrame;
    struct FrameObject *clearedFrame;
    struct FrameObject *textFrame;
    u32 countdown;
    u16 snapshot;

    initialFrame = &frames[gState0TypedWork.bytes[0x12F]];
    countdown = (*(u16 *)((u8 *)initialFrame + 0x30));
    snapshot = countdown;
    if (snapshot != 0) {
        (*(u16 *)((u8 *)initialFrame + 0x30)) = (u16) (countdown - 1);
        return;
    }
    sub_0801BD58((firstTable=gUnknown_083CEDF4,firstTable[initialFrame->byte2B]), 0);
    if (gState0TypedWork.bytes[0x66] == 0xFF) {
        clearedFrame = &frames[gState0TypedWork.bytes[0x12F]];
        sub_0803EFD8((u32) clearedFrame->unknown2C[2], (u32) clearedFrame->unknown2C[3], (u32) clearedFrame->screenX, (u32) clearedFrame->screenY, (u32) *(volatile u16 *)0x04000008, (u32) snapshot);
        sub_08040CD0(gState0TypedWork.bytes[0x12F], 1U);
        return;
    }
    textFrame = &frames[gState0TypedWork.bytes[0x12F]];
    snapshot = textFrame->unknown2C[1];
    if (snapshot == 0) {
        sub_0803F1C8((u32) textFrame->unknown2C[2], (u32) textFrame->unknown2C[3], (u32) textFrame->screenX, (u32) textFrame->screenY, (secondTable=gState0NextText_083B4C60,secondTable[textFrame->unknown2C[0]]), (u32) *(volatile u16 *)0x04000008, (u32) snapshot);
    }
}
