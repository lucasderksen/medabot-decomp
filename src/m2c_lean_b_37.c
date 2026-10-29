/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "battle_work.h"
#include "bios_lz77_streams.h"
#include "composite_graphics.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_command_data.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "native_le_streams.h"
#include "object_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct SetupContext675D4 {
    u8 pad00[0x3A];
    u16 timer3A;
    u16 value3C;
    u8 pad3E[0xA];
    u8 flags48[4];
    u8 pad4C[0x3E];
    u16 values8A[4];
    u16 values92[4];
    u16 values9A[4];
    u8 bytesA2[5];
    u8 bytesA7[5];
};

extern const u32 gUnknown_087A25A4[];
extern const u8 gUnknown_0850F458[];
extern struct SetupContext675D4 *gSetupContext675D4 asm("gMainContextPointer_03006F74");
extern u16 gCopy6280C0202F800[];
extern u8 gScratch6030C02030000[];
extern void sub_080668D4(u32);
extern void sub_08066A14(void);

void sub_080675D4(void);

void sub_080675D4(void) {

    u16 palette[64] = { 0, 0x6B40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x5EE0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x5280, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x4A40 };
    u32 fill;
    u32 size;
    s32 i, k;
    u32 root;

    sub_08074B88(5);
    fill = 0;
    CpuFastSet(&fill, (void *)0x06000000, 0x01006000);
    sub_08040CD0(0, 0x80);
    sub_080415BC();
    *(volatile u16 *)0x04000000 = 0x6060;
    *(volatile u16 *)0x04000008 = 0x1B04;
    sub_0805BA34(gBiosLz77Stream_087A4EF0, *(volatile u16 *)0x04000008);
    *(volatile u16 *)0x04000008 = 0x1F04;
    *(volatile u16 *)0x0400000A = 0x1E05;
    *(volatile u16 *)0x0400000C = 0x3D06;
    *(volatile u16 *)0x0400000E = 0x1C07;
    sub_0805BA34(gBiosLz77Stream_087A5058, *(volatile u16 *)0x0400000C);
    sub_0805BA34(gBiosLz77Stream_087A5294, *(volatile u16 *)0x0400000E);
    size = sub_08044D0C(gBiosLz77Stream_087A2604, gScratch6030C02030000);
    CpuFastSet(gScratch6030C02030000, (void *)0x06004000, (size << 9) >> 11);
    CpuFastSet(gUnknown_087A25A4, gEquipmentPaletteShadow, 0x18);
    CpuFastSet(palette, gCopy6280C0202F800, 0x20);
    LeDecompress(gNativeLeStream_08787144, (void *)0x06010000);
    CpuFastSet(gUnknown_0850F458, (void *)0x05000200, 8);
    for (i = 0; i < sizeof(gSetupContext675D4->bytesA2); i++) {
        gSetupContext675D4->bytesA2[i] = 0x78;
        gSetupContext675D4->bytesA7[i] = 0x50;
    }
    i = 0;
    root = (u32)gFrameObjects;
    for (; i < sizeof(gSetupContext675D4->values8A) / sizeof(gSetupContext675D4->values8A[0]); i++) {
        gSetupContext675D4->values8A[i] = 0;
        gSetupContext675D4->values92[i] = 0;
        gSetupContext675D4->values9A[i] = 0;
    }
    gSetupContext675D4->value3C = 0;
    for (i = 0; i <= 0x47; i = k) {
        k = i + 1;
        ((struct FrameObject *)root)[k].flags = 0xC800;
        ((struct FrameObject *)root)[k].tableSelector = 2;
        ((struct FrameObject *)root)[k].palette = sub_0807CD2C(i, 0x12);
        ((struct FrameObject *)root)[k].frameAndGroup = 0x116;
    }
    sub_08066A14();
    sub_080668D4(0x32);
    *(volatile u16 *)0x04000042 = 0xF0;
    *(volatile u16 *)0x04000046 = 0x1888;
    *(volatile u16 *)0x04000040 = 0xF0;
    *(volatile u16 *)0x04000044 = 0x2880;
    *(volatile u16 *)0x04000048 = 0x3D3F;
    *(volatile u16 *)0x0400004A = 0;
    *(volatile u16 *)0x04000000 |= 0x100;
    *(volatile u16 *)0x04000000 |= 0x200;
    *(volatile u16 *)0x04000000 |= 0x400;
    *(volatile u16 *)0x04000000 |= 0x800;
    *(volatile u16 *)0x04000000 |= 0x1000;
    *(volatile u16 *)0x04000050 = 0x844;
    *(volatile u16 *)0x04000052 = 0x1004;
    *(volatile u16 *)0x04000054 = 8;
    gSetupContext675D4->timer3A = 0;
    gSetupContext675D4->flags48[0] = 0;
    gSetupContext675D4->flags48[1] = 0;
    gSetupContext675D4->flags48[2] = 0;
    gSetupContext675D4->flags48[3] = 0;
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C++;
}
