/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Work16288 { u8 pad[0x81]; u8 value81; u8 pad82; u8 choice83; };
struct Part17E00 { u8 unknown00[0x17]; u8 byte17; };
struct Setup17E00 { u8 unknown00[0x48]; struct Part17E00 parts[4]; u8 unknownA8[0x58]; };
struct Part17F9C { u8 unknown00[4]; u8 byte04; u8 unknown05[0xC]; u8 byte11; u8 unknown12[6]; };
struct Setup17F9C { u8 unknown00[0x48]; struct Part17F9C parts[4]; u8 unknownA8[0x58]; };
struct SetupBF14 { u8 unknown00; u8 byte01; u8 unknown02[0x1E]; u8 name20[8]; u8 name28[8]; u8 unknown30[0xD0]; };
struct InventoryBF14 { u8 unknown00[0x20]; u8 name20[8]; u8 name28[8]; u8 unknown30[0x10]; };

extern const u8 gUnknown_083AD4F6[];
extern const u8 gUnknown_083AD4FC[];
extern struct InventoryBF14 gInventoryBF14[] asm("gInventoryRecords");
extern struct Setup17E00 gSetup17E00[] asm("gSetupBuffer_03000590");
extern struct Setup17F9C gSetup17F9C[] asm("gSetupBuffer_03000590");
extern struct SetupBF14 gSetupBF14[] asm("gSetupBuffer_03000590");
extern struct Work16288 gWork16288 asm("gCounter6ED08_03001800");
extern u32 sub_08016138(u32);
extern void sub_08074DE0(u32);

void sub_08016288(void);
void sub_08017E00(void);
void sub_08017F9C(void);
void sub_0801A4F4(u8 *source, u32 selected, u32 first, s32 x, s32 y);
void sub_0801BF14(u32 index);

void sub_08016288(void) {

    const u8 *table;

    if (gWork16288.choice83 != 0) {
        if (sub_08016138(gWork16288.choice83 - 1) != 0) {
            if (gWork16288.choice83 == 1) {
                u32 base = (u32)gUnknown_083AD4F6;
                u32 offset = gWork16288.value81;
                gWork16288.value81 = *(const u8 *)(base + offset);
            } else {
                u32 base = (u32)gUnknown_083AD4FC;
                u32 offset = gWork16288.value81;
                gWork16288.value81 = *(const u8 *)(base + offset);
            }
            gWork16288.choice83 = 0;
            sub_08015F24();
        }
    } else {
        if (*(u8 *)&gRepeatedKeys & 0x10) {
            sub_08074DE0(2);
            gWork16288.choice83 = 1;
        }
        if (*(u8 *)&gRepeatedKeys & 0x20) {
            sub_08074DE0(2);
            gWork16288.choice83 = 2;
        }
    }
}

void sub_08017E00(void) {

    u32 i;

    sub_08040D0C(0x20, 0x38);
    for (i = 0; i < 4; i++) {
        sub_08041D04(gPartTextPointers_083BBB4C[gSetup17E00[gState0TypedWork.bytes[0x3D] + gState0TypedWork.bytes[0x3C] * 3].parts[i].byte17 * 4 + i],
                     &gState0TypedWork.bytes[0x9E], 15);
        sub_08040DB8(&gState0TypedWork.bytes[0x9E], (u8)(i * 14 + 0x20), 13, i * 2 + 4, 10, 13, 1, 2);
    }
}

void sub_08017F9C(void) {

    u32 i;
    u16 palette;

    for (i = 0; i < 4; i++) {
        if (gSetup17F9C[gState0TypedWork.bytes[0x3D] + gState0TypedWork.bytes[0x3C] * 3].parts[i].byte11 != 0)
            palette = 0xA000;
        else
            palette = 0xB000;
        sub_08042950(gSetup17F9C[gState0TypedWork.bytes[0x3D] + gState0TypedWork.bytes[0x3C] * 3].parts[i].byte11,
                     0x17, i * 2 + 4, 3, *(volatile u16 *)0x0400000A, palette | 0x390);
        sub_08042698(1, 2, 0x1A, i * 2 + 4, *(volatile u16 *)0x0400000A, palette | 0x3A4);
        sub_08042950(gSetup17F9C[gState0TypedWork.bytes[0x3D] + gState0TypedWork.bytes[0x3C] * 3].parts[i].byte04,
                     0x1B, i * 2 + 4, 3, *(volatile u16 *)0x0400000A, palette | 0x390);
    }
}

void sub_0801A4F4(u8 *source, u32 selected, u32 first, s32 x, s32 y) {

    u32 i;
    u32 root;

    i = 0;
    root = (u32)gFrameObjects;
    for (; i < 5; i++) {
        if (source[i] == 0xFE)
            return;
        ((struct FrameObject *)(root + ((first + selected * 4 + i) << 6)))->flags = 0xC224;
        ((struct FrameObject *)(root + ((first + selected * 4 + i) << 6)))->tableSelector = 0;
        ((struct FrameObject *)(root + ((first + selected * 4 + i) << 6)))->screenY = y;
        ((struct FrameObject *)(root + ((first + selected * 4 + i) << 6)))->screenX = x + i * 8;
        ((struct FrameObject *)(root + ((first + selected * 4 + i) << 6)))->priority = 0x90;
        ((struct FrameObject *)(root + ((first + selected * 4 + i) << 6)))->frameAndGroup = source[i] + 0x5100;
        ((struct FrameObject *)(root + ((first + selected * 4 + i) << 6)))->commandDelay = i * 4;
        ((struct FrameObject *)(root + ((first + selected * 4 + i) << 6)))->commandOffset = 0;
        ((struct FrameObject *)(root + ((first + selected * 4 + i) << 6)))->scaleY = 0x40;
        ((struct FrameObject *)(root + ((first + selected * 4 + i) << 6)))->scaleX = 0x40;
        ((struct FrameObject *)(root + ((first + selected * 4 + i) << 6)))->palette = 0xC;
    }
}

void sub_0801BF14(u32 index) {

    u32 slot;
    u32 i;

    slot = sub_08041D3C(gSetupBF14[index].byte01) - 1;
    for (i = 0; i < 8; i++) {
        gInventoryBF14[slot].name20[i] = gSetupBF14[index].name20[i];
        gInventoryBF14[slot].name28[i] = gSetupBF14[index].name28[i];
    }
}
