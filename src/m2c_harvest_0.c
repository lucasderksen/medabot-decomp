/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "sound_work.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "effect_work.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "input.h"
#include "main.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

extern s32 gGlyphs_084BFC64;
extern s32 gUnknown_0202FC00;
extern s32 gUnknown_0202FE00;
extern s32 gUnknown_03001830;
extern s32 gUnknown_03006F88;
extern s32 gUnknown_03006F8C;
extern s32 gUnknown_084E4498;
extern s32 gUnknown_084E44B8;
extern s32 gUnknown_084E4578;
extern s32 gUnknown_084E4618;
extern s32 gUnknown_0850FD18;
extern s32 gUnknown_085100D8;
extern s32 gUnknown_08510158;
extern s32 gUnknown_087C9F48;
extern u8 gContinuedByte_03002B64;
extern u8 gUnknown_084881E0;
extern u8 gUnknown_08488200;
extern u8 gUnknown_08488240;
extern u8 gUnknown_08488290;
extern u8 gUnknown_084882CC;
extern u8 gUnknown_08488344;
extern u8 gUnknown_08488380;
extern u8 gUnknown_084883BC;
extern u8 gUnknown_084883F8;
extern u8 gUnknown_08488450;
extern u8 gUnknown_084C9A84;
extern u8 gUnknown_084CA064;
extern u8 gUnknown_084D7318;
extern u8 gUnknown_084DCD28;
extern u8 gUnknown_084DD368;
extern void *gUnknown_03007014;
extern void *gUnknown_08485A70;

void sub_080103A4(void);
void sub_08015738(void);
void sub_08015A90(void);
void sub_08015AFC(void);
void sub_080166AC(void);
void sub_08016894(u32 value);
void sub_08017004(void);
void sub_08017104(void);
void sub_08017208(u32 value);
void sub_08018074(u32 first, u32 second, u32 third, u32 fourth);
void sub_080182AC(void);
void sub_0801C188(void);
void sub_0801DED4(void);
void sub_0801DF0C(void);
void sub_0801EAC4(void);
void sub_0801EBB8(void);
void sub_0801EED4(void);
void sub_0801EFC8(void);
void sub_0801F474(void);
void sub_0801F5AC(void);
void sub_08020040(void);
void sub_080209A0(void);
void sub_08020CEC(void);
void sub_08021DEC(void);
void sub_0802213C(void);
void sub_08022380(void);
void sub_080227C0(void);
void sub_08022C90(void);
void sub_0802306C(void);
void sub_080230A4(void);
void sub_08023414(void);
void sub_08023718(void);
void sub_08023AB0(void);
void sub_08023C78(void);
void sub_08024078(void);
void sub_080247F4(void);
void sub_08025174(void);
void sub_08025F14(void);
void sub_08026444(void);
void sub_08026EC0(void);
void sub_08026FC0(void);
void sub_080270BC(void);
void sub_0802747C(void);
void sub_08028230(void);
void sub_08028270(void);
void sub_080283EC(void);
void sub_08029828(void);
void sub_08029DF4(void);
void sub_0802A0D0(void);
void sub_0802A694(void);
void sub_0802AAB8(void);
void sub_0802ACB4(void);
void sub_0802AFE8(void);
void sub_0802BD94(void);
void sub_0802C294(void);
void sub_0802C62C(void);
void sub_0802CBD0(void);
void sub_0802D670(void);
void sub_0802DC9C(void);
void sub_0802EAC0(void);
void sub_0802F018(void);
void sub_0802F610(void);
void sub_0802FE38(void);
void sub_08030238(void);
void sub_080305C8(void);
void sub_0803080C(void);
void sub_08030C94(void);
void sub_08030CA0(void);
void sub_08030CAC(void);
void sub_08030F10(void);
void sub_08031174(void);
void sub_080312CC(void);
void sub_08031608(void);
void sub_08036340(s32 arg0);
u32 sub_08036E54(u32 arg0);
void sub_08039430(void);
void sub_080396C4(void);
void sub_0803D5A0(void);
void sub_0803D634(void);
void sub_0803D674(void);
void sub_0803E768(void);
void sub_0803E774(void);
void sub_0803E780(void);
s32 sub_0803E79C(void);
void sub_0803E894(void);
void sub_0803ED10(void);
void sub_08040B5C(void);
void sub_080513B8(void);
void sub_08052BD0(void);
void sub_0805AC8C(void);
void sub_0805BB38(u16 arg0);
void sub_08060DAC(void);
void sub_08060DC8(void);
void sub_080640DC(void);
void sub_08064BBC(void);
void sub_08064BEC(void);
void sub_08064C0C(void);
void sub_08064C2C(void);
void sub_08064C4C(void);
void sub_08064DA8(void);
void sub_08064DF4(void);
void sub_08067BDC(u32 value);
s32 sub_08068920(void);
s32 sub_0806A718(void);
s32 sub_0806B130(void);
s32 sub_0806B1F8(u32 inputIndex);
void sub_0806B4A4(void);
void sub_0806E9C0(void);
void sub_0806EA54(void);
void sub_0806F0E0(void);
void sub_0806F9B8(void);
void sub_08070804(void);
s32 sub_08071DFC(void);
void sub_08072B18(void *arg0, u8 arg1);
void sub_08073E1C(void *arg0);
void sub_08073F90(void *arg0);
void sub_08073FB8(void *arg0);
s32 sub_08074540(void);
s32 sub_08075130(void);

void sub_080103A4(void) {
    if ((u32) gState0TypedWork.bytes[0x85] <= 2U) {
        if (1 & gState0TypedWork.bytes[0x85]) {
            gUnknown_0300137C = 1;
        } else {
            gUnknown_0300137C = 3;
        }
        gState0TypedWork.bytes[0x85] += 1;
        return;
    }
    gUnknown_0300137C += 1;
}

void sub_08015738(void) {
    LoadLeTilemap(0xEU, 3U, &gUnknown_08488200, (u32) *(u16 *)0x0400000E, 0x200U);
}

void sub_08015A90(void) {
    LoadLeTilemap(0U, 0xDU, &gUnknown_084882CC, (u32) *(u16 *)0x0400000A, 0x258U);
    LoadLeTilemap(0U, 0x11U, &gUnknown_084881E0, (u32) *(u16 *)0x0400000A, 0x210U);
    LoadLeTilemap(0xCU, 0xFU, &gUnknown_08488240, (u32) *(u16 *)0x0400000A, 0x230U);
    LoadLeTilemap(0x14U, 0x10U, &gUnknown_08488290, (u32) *(u16 *)0x0400000A, 0x240U);
}

void sub_08015AFC(void) {
    LoadLeTilemap(0xCU, 0x15U, &gUnknown_08488240, (u32) *(u16 *)0x0400000A, 0x230U);
    LoadLeTilemap(0x14U, 0x15U, &gUnknown_08488290, (u32) *(u16 *)0x0400000A, 0x240U);
}

void sub_080166AC(void) {
    LoadLeTilemap(9U, 0x15U, &gUnknown_08488344, (u32) *(u16 *)0x04000008, 0x288U);
    LoadLeTilemap(0x12U, 0x15U, &gUnknown_084883F8, (u32) *(u16 *)0x0400000A, 0x2D0U);
}

void sub_08016894(u32 value) {
    gFrameObjects[4].flags = 0xC404;
    gFrameObjects[4].tableSelector = 0;
    gFrameObjects[4].screenX = 0x78;
    gFrameObjects[4].screenY = 0x84;
    gFrameObjects[4].palette = 0xA;
    gFrameObjects[4].priority = 0xC0;
    gFrameObjects[4].frameAndGroup = (value * 4) + 0x607;
}

void sub_08017004(void) {
    LoadLeTilemap(9U, 0x15U, &gUnknown_08488380, (u32) *(u16 *)0x04000008, 0x2A0U);
    LoadLeTilemap(0x12U, 0x15U, &gUnknown_084883BC, (u32) *(u16 *)0x0400000A, 0x2B8U);
}

void sub_08017104(void) {
    gFrameObjects->flags = 0xC404;
    gFrameObjects->tableSelector = 0;
    gFrameObjects->screenX = 0x78;
    gFrameObjects->screenY = 0x78;
    gFrameObjects->palette = 0xA;
    gFrameObjects->priority = 0xC0;
    gFrameObjects->frameAndGroup = 0x61A;
}

void sub_08017208(u32 value) {
    gFrameObjects[4].flags = 0xC404;
    gFrameObjects[4].tableSelector = 0;
    gFrameObjects[4].screenX = 0x84;
    gFrameObjects[4].screenY = 0x78;
    gFrameObjects[4].palette = 0xA;
    gFrameObjects[4].priority = 0xC0;
    gFrameObjects[4].frameAndGroup = (value * 4) + 0x61D;
}

void sub_08018074(u32 first, u32 second, u32 third, u32 fourth) {
    gState0TypedWork.bytes[0x98] = (u8) first;
    gState0TypedWork.bytes[0x99] = (u8) second;
    gState0TypedWork.bytes[0x9A] = (u8) third;
    (*(s8 *)((u8 *)((&gState0TypedWork.bytes[0x99] + 1)) + 1)) = (s8) fourth;
}

void sub_080182AC(void) {
    if (gFrameCounter & 1) {
        gBgScroll3.x += 1;
        gBgScroll3.y += 1;
    }
}

void sub_0801C188(void) {
    LeDecompress(&gUnknown_084CA064, (void *)0x06014E00);
    CpuFastSet(&gUnknown_084E4618, (void *)0x050002C0, 8U);
    gState0TransferWork.bytes[0x9C] += 1;
}

void sub_0801DED4(void) {
    gState0TransferWork.bytes[0xB5] = 1;
}

void sub_0801DF0C(void) {
    s32 sp0;
    s32 sp4;

    gState0TypedWork.bytes[0x84] = 0;
    sp0 = 0;
    CpuFastSet(&sp0, (void *)0x05000120, 0x01000008U);
    sp4 = 0x11111111;
    CpuFastSet(&sp4, (void *)0x06004120, 0x01000008U);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0801EAC4(void) {
    gState0TransferWork.bytes[0xB5] = 1;
}

void sub_0801EBB8(void) {
    gState0TypedWork.widths.word86 = 0x3C;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0801EED4(void) {
    gState0TransferWork.bytes[0xAA] = 0xA;
}

void sub_0801EFC8(void) {
    if (gFrameCounter & 1) {
        gFrameObjects[0xA].screenY = (u16) gFrameObjects[0xA].screenY + 1;
        if (gFrameObjects[0xA].screenY == (*(u16 *)((u8 *)(gFrameObjects) + 0x2B0))) {
            gState0TypedWork.widths.word86 = 0x3C;
            gState0TransferWork.bytes[0xAA] += 1;
        }
    }
}

void sub_0801F474(void) {
    gState0TransferWork.bytes[0xAA] = 0x3E;
}

void sub_0801F5AC(void) {
    gState0TransferWork.bytes[0xB5] = 1;
}

void sub_08020040(void) {
    gState0TransferWork.bytes[0xAA] = 0;
}

void sub_080209A0(void) {
    gState0TransferWork.bytes[0xAA] = 2;
}

void sub_08020CEC(void) {
    gState0TransferWork.bytes[0xAA] = 2;
}

void sub_08021DEC(void) {
    gState0TransferWork.bytes[0xA6] = 0x25;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802213C(void) {
    gState0TransferWork.bytes[0xA6] = 0x23;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08022380(void) {
    if (gState0TransferWork.bytes[0x58] == 0) {
        gState0TransferWork.bytes[0xA6] = 0x72;
        gState0TransferWork.bytes[0x58] = 1;
    } else {
        gState0TransferWork.bytes[0xA6] = 0x73;
        gState0TransferWork.bytes[0x58] = 0;
    }
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_080227C0(void) {
    gState0TransferWork.bytes[0xA6] = 0x1B;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08022C90(void) {
    gState0TransferWork.bytes[0xA6] = 0x29;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802306C(void) {
    LeDecompress(&gUnknown_084D7318, (void *)0x06014800);
    CpuFastSet(&gUnknown_0850FD18, (void *)0x050002C0, 0x10U);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_080230A4(void) {
    SnapshotPalettes();
    gState0TypedWork.bytes[0x84] = 0;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08023414(void) {
    gState0TransferWork.bytes[0xA6] = 0x1C;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08023718(void) {
    gState0TransferWork.bytes[0xA6] = 0x1D;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08023AB0(void) {
    gState0TransferWork.bytes[0xA6] = 0x2C;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08023C78(void) {
    gState0TransferWork.bytes[0xA6] = 0x2B;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08024078(void) {
    gState0TransferWork.bytes[0xA6] = 0x2D;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_080247F4(void) {
    gState0TransferWork.bytes[0xA6] = 0x2E;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08025174(void) {
    gState0TransferWork.bytes[0xA6] = 0x33;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08025F14(void) {
    gState0TransferWork.bytes[0xA6] = 0x75;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08026444(void) {
    gState0TransferWork.bytes[0xA6] = 0x2A;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08026EC0(void) {
    gState0TransferWork.bytes[0xAA] = 2;
}

void sub_08026FC0(void) {
    gState0TransferWork.bytes[0xAA] = 4;
}

void sub_080270BC(void) {
    LeDecompress(&gUnknown_084DCD28, (void *)0x06014800);
    CpuFastSet(&gUnknown_085100D8, (void *)0x050002E0, 8U);
    gFrameObjects[0x21].flags = 0xC624;
    gFrameObjects[0x21].tableSelector = 0;
    gFrameObjects[0x21].screenX = 0x78;
    gFrameObjects[0x21].screenY = 0x30;
    gFrameObjects[0x21].scaleX = 0x80;
    gFrameObjects[0x21].scaleY = 0x80;
    gFrameObjects[0x21].palette = 7;
    gFrameObjects[0x21].priority = 0xF0;
    gFrameObjects[0x21].frameAndGroup = 0x6500;
    gFrameObjects[0x22].flags = 0x4624;
    gFrameObjects[0x22].tableSelector = 0;
    gFrameObjects[0x22].screenX = 0x78;
    gFrameObjects[0x22].screenY = 0x50;
    gFrameObjects[0x22].scaleX = 0x80;
    gFrameObjects[0x22].scaleY = 0x80;
    gFrameObjects[0x22].palette = 7;
    gFrameObjects[0x22].priority = 0xF0;
    gFrameObjects[0x22].frameAndGroup = 0x6501;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802747C(void) {
    gState0TransferWork.bytes[0xA6] = 0x3A;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08028230(void) {
    gState0TransferWork.bytes[0xA6] = 0x50;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08028270(void) {
    LeDecompress(&gUnknown_084DD368, (void *)0x06014800);
    CpuFastSet(&gUnknown_08510158, (void *)0x050002E0, 8U);
    gFrameObjects[0x21].frameAndGroup = 0x6A00;
    gFrameObjects[0x21].screenY = (u16) gFrameObjects[0x21].screenY + 4;
    gFrameObjects[0x21].unknown23[4] = 0;
    gState0TypedWork.widths.word86 = 0x3C;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_080283EC(void) {
    gState0TransferWork.bytes[0xA6] = 0x64;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08029828(void) {
    gState0TransferWork.bytes[0xA6] = 0x53;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08029DF4(void) {
    gState0TransferWork.bytes[0xA6] = 0x3B;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802A0D0(void) {
    gState0TransferWork.bytes[0xA6] = 0x3C;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802A694(void) {
    gState0TransferWork.bytes[0xA6] = 0x54;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802AAB8(void) {
    gState0TransferWork.bytes[0xA6] = 0x65;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802ACB4(void) {
    gState0TransferWork.bytes[0xA6] = 0x45;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802AFE8(void) {
    gState0TransferWork.bytes[0xA6] = 0x44;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802BD94(void) {
    gFrameObjects[0x21].flags = 0xC604;
    gFrameObjects[0x21].tableSelector = 0;
    gFrameObjects[0x21].screenX = 0x78;
    gFrameObjects[0x21].screenY = 0x40;
    gFrameObjects[0x21].palette = 6;
    gFrameObjects[0x21].priority = 0xF0;
    gFrameObjects[0x21].frameAndGroup = 0x4800;
    gFrameObjects[0x21].scaleX = 0x40;
    gFrameObjects[0x21].scaleY = 0x40;
    gFrameObjects[0x21].angle = 0;
    gFrameObjects[0x21].unknown2C[1] = 0;
    gFrameObjects[0x21].unknown2C[2] = 1;
    gState0TypedWork.widths.word86 = 0;
    gState0TypedWork.bytes[0x84] = 0;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802C294(void) {
    gState0TransferWork.bytes[0xA6] = 0x5B;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802C62C(void) {
    gState0TransferWork.bytes[0xA6] = 0x5C;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802CBD0(void) {
    gState0TransferWork.bytes[0xA6] = 0x59;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802D670(void) {
    gState0TransferWork.bytes[0xA6] = 0x42;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802DC9C(void) {
    gState0TransferWork.bytes[0xA6] = 0x5E;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802EAC0(void) {
    gState0TransferWork.bytes[0xA6] = 0x67;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802F018(void) {
    gState0TransferWork.bytes[0xA6] = 0x68;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802F610(void) {
    gState0TransferWork.bytes[0xA6] = 0x51;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802FE38(void) {
    gState0TransferWork.bytes[0xA6] = 0x4F;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08030238(void) {
    if (gState0TypedWork.widths.word86 == 0xC) {
        gState0TransferWork.bytes[0xAA] += 1;
        return;
    }
    gState0TypedWork.widths.word86 += 1;
    gFrameObjects[0x21].screenY = (u16) gFrameObjects[0x21].screenY + 2;
    gFrameObjects[0x22].screenY = (u16) gFrameObjects[0x22].screenY + 2;
    gFrameObjects[0x23].screenY = (u16) gFrameObjects[0x23].screenY + 2;
    gFrameObjects[0x24].screenY = (u16) gFrameObjects[0x24].screenY + 2;
}

void sub_080305C8(void) {
    gState0TransferWork.bytes[0xA6] = 0x6A;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0803080C(void) {
    gState0TransferWork.bytes[0xB5] = 1;
}

void sub_08030C94(void) {
    gUnknown_0300137C = 0x40;
}

void sub_08030CA0(void) {
    gUnknown_0300137C = 0x50;
}

void sub_08030CAC(void) {
    CpuFastSet(&gUnknown_084E4498, (void *)0x05000300, 8U);
    CpuFastSet(&gUnknown_084E44B8, (void *)0x05000320, 8U);
    CpuFastSet(gState0Palette_084E44D8, (void *)0x05000340, 8U);
    gMainSubstate = 7;
    gUnknown_0300137C = 0x46;
}

void sub_08030F10(void) {
    LeDecompress(&gUnknown_084C9A84, (void *)0x06014800);
    CpuFastSet(&gUnknown_084E4578, (void *)0x050003E0, 8U);
    gFrameObjects[0x21].flags = 0xC624;
    gFrameObjects[0x21].tableSelector = 0;
    gFrameObjects[0x21].screenX = 0x78;
    gFrameObjects[0x21].screenY = 0x40;
    gFrameObjects[0x21].palette = 0xF;
    gFrameObjects[0x21].priority = 0xC0;
    gFrameObjects[0x21].frameAndGroup = 0x902;
    gFrameObjects[0x21].scaleY = 0x80;
    gFrameObjects[0x21].scaleX = 0x40;
    gUnknown_0300137C += 1;
}

void sub_08031174(void) {
    LeDecompress(&gUnknown_084C9A84, (void *)0x06014800);
    CpuFastSet(&gUnknown_084E4578, (void *)0x050003E0, 8U);
    gFrameObjects[0x21].flags = 0xC624;
    gFrameObjects[0x21].tableSelector = 0;
    gFrameObjects[0x21].screenX = 0x78;
    gFrameObjects[0x21].screenY = 0x40;
    gFrameObjects[0x21].palette = 0xF;
    gFrameObjects[0x21].priority = 0xC0;
    gFrameObjects[0x21].frameAndGroup = 0x903;
    gFrameObjects[0x21].scaleY = 0x80;
    gFrameObjects[0x21].scaleX = 0x40;
    gUnknown_0300137C += 1;
}

void sub_080312CC(void) {
    SnapshotPalettes();
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C += 1;
}

void sub_08031608(void) {
    gUnknown_0300137C = 0x4F;
}

void sub_08036340(s32 arg0) {
    u32 var_r1;

    var_r1 = 4;
    if (arg0 == 0) {
        var_r1 = 0x12;
    }
    LoadLeTilemap(var_r1, 0U, &gUnknown_08488450, (u32) *(u16 *)0x0400000A, 0x329U);
}

u32 sub_08036E54(u32 arg0) {
    u32 var_r0;

    var_r0 = arg0;
    if (var_r0 > 0x63U) {
        return 0x63U;
    }
    if (var_r0 == 0) {
        var_r0 = 1;
    }
    return var_r0;
}

void sub_08039430(void) {
    gFrameObjects->unknown23[7] = 1;
    gState0TransferWork.bytes[0xB5] = 1;
}

void sub_080396C4(void) {
    gFrameObjects->unknown23[7] = 1;
}

void sub_0803D5A0(void) {
    s32 sp0;

    sp0 = 0;
    CpuFastSet(&sp0, &gState0TransferWork, 0x01000100U);
    gState0TypedWork.widths.word86 = 0;
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C += 1;
}

void sub_0803D634(void) {
    if (gUnknown_03000B90 == 0) {
        gState0TypedWork.bytes[0x8D] = (u8) gFrameCounter;
        gMainSerialOutgoingWork.word06 = gState0TypedWork.bytes[0x8D] + 0x8000;
    }
    gUnknown_0300137C += 1;
}

void sub_0803D674(void) {
    if (gUnknown_03000B90 != 0) {
        if (0x8000 & gMainSerialOutgoingWork.words[0][1]) {
            gState0TypedWork.bytes[0x8D] = (u8) gMainSerialOutgoingWork.words[0][1];
            goto block_3;
        }
    } else {
block_3:
        gUnknown_0300137C += 1;
    }
}

void sub_0803E768(void) {
    gUnknown_0300137C = 6;
}

void sub_0803E774(void) {
    gUnknown_0300137C = 5;
}

void sub_0803E780(void) {
    if (gState0TypedWork.bytes[0x89] == 1) {
        gMainSerialOutgoingWork.word06 = 0;
    }
}

s32 sub_0803E79C(void) {
    gMainSerialOutgoingWork.word06 = 0xFFFE;
    if ((gMainSerialOutgoingWork.words[0][1] == 0xFFFE) && (gMainSerialOutgoingWork.words[1][1] == gMainSerialOutgoingWork.words[0][1])) {
        return 1;
    }
    return 0;
}

void sub_0803E894(void) {
    if (gFrameCounter & 1) {
        gBgScroll3.x += 1;
        gBgScroll3.y += 1;
    }
}

void sub_0803ED10(void) {
    gFrameObjects[2].unknown23[1] = 0;
    gFrameObjects[2].unknown23[2] = 1;
}

void sub_08040B5C(void) {
    u32 var_r5;
    void *var_r4;

    var_r5 = 0;
    var_r4 = (void *)0x06000280;
    do {
        CpuSet(&gGlyphs_084BFC64, var_r4, 0x20U);
        var_r4 += 0x40;
        var_r5 += 1;
    } while (var_r5 <= 0x33U);
    gState0TypedWork.bytes[0x1B] += 1;
}

void sub_080513B8(void) {
    gBackgroundState_03005310.unknown00[0] = 1;
    gBackgroundState_03005310.unknown00[1] = 0;
}

void sub_08052BD0(void) {
    gFrameObjects[0x2F].flags = 0;
    gFrameObjects[0x59].flags = 0;
}

void sub_0805AC8C(void) {
    CpuFastSet(&gUnknown_0202FC00, (void *)0x05000200, 0x80U);
    CpuFastSet(&gUnknown_0202FE00, (void *)0x05000000, 0x80U);
}

void sub_0805BB38(u16 arg0) {
    u16 temp_r0;

    temp_r0 = arg0;
    gNewKeys = temp_r0 & ~(*(u16 *)((u8 *)(gMainContextPointer_03006F74) + 0x78));
    gReleasedKeys = (*(u16 *)((u8 *)(gMainContextPointer_03006F74) + 0x78)) & ~temp_r0;
    (*(u16 *)((u8 *)(gMainContextPointer_03006F74) + 0x78)) = temp_r0;
}

void sub_08060DAC(void) {
    (*(s8 *)((u8 *)(gMainContextPointer_03006F74) + 5)) = 0;
    (*(s8 *)((u8 *)(gMainContextPointer_03006F74) + 6)) = 0;
    gUnknown_0300137C = 0xE;
}

void sub_08060DC8(void) {
    gUnknown_0300137C = 1;
}

void sub_080640DC(void) {
    gUnknown_0300137C += 1;
}

void sub_08064BBC(void) {
    gMainSerialOutgoingWork.word06 = 0xFEDF;
    if ((gMainSerialOutgoingWork.words[0][1] == 0xFEDF) && (gMainSerialOutgoingWork.words[1][1] == gMainSerialOutgoingWork.words[0][1])) {
        gMainSubstate = 0x14;
        gUnknown_0300137C = 0;
    }
}

void sub_08064BEC(void) {
    gMainState = 2;
    gMainSubstate = 0x1A;
    gUnknown_0300137C = 0;
}

void sub_08064C0C(void) {
    gMainState = 2;
    gMainSubstate = 0x11;
    gUnknown_0300137C = 0;
}

void sub_08064C2C(void) {
    gMainState = 2;
    gMainSubstate = 0x10;
    gUnknown_0300137C = 0;
}

void sub_08064C4C(void) {
    gMainState = 2;
    gMainSubstate = 0x14;
    gUnknown_0300137C = 0;
}

void sub_08064DA8(void) {
    gUnknown_0300137C = 1;
}

void sub_08064DF4(void) {
    (*(s8 *)((u8 *)(gMainContextPointer_03006F74) + 0x2E)) = 0;
    (*(s8 *)((u8 *)(gMainContextPointer_03006F74) + 0x2F)) = 0;
    gUnknown_0300137C += 1;
}

void sub_08067BDC(u32 value) {
    gQuantityResult_030017EC = (u8) value;
    gMainState = 2;
    gMainSubstate = 0x18;
    gUnknown_0300137C = 0;
}

s32 sub_08068920(void) {
    return 1;
}

s32 sub_0806A718(void) {
    s32 temp_r0;

    if (((u32) (*(u8 *)((u8 *)(&gUnknown_03006F8C) + 0)) > 2U) && ((u32) (*(u8 *)((u8 *)(&gUnknown_03006F8C) + 1)) > 2U) && ((u32) (*(u8 *)((u8 *)(&gUnknown_03006F8C) + 2)) > 2U)) {
        temp_r0 = gUnknown_03006F88 + 1;
        gUnknown_03006F88 = temp_r0;
        if (temp_r0 > 0xF0) {
            return 1;
        }
    }
    return 0;
}

s32 sub_0806B130(void) {
    return 0;
}

s32 sub_0806B1F8(u32 inputIndex) {
    /* Uniform callback index; this handler does not use it. */
    return 1;
}

void sub_0806B4A4(void) {
    if (gFrameCounter & 1) {
        gBgScroll3.x -= 1;
        gBgScroll3.y += 1;
    }
}

void sub_0806E9C0(void) {
    gMainState = 3;
    gMainSubstate = 1;
    gUnknown_0300137C = 0;
}

void sub_0806EA54(void) {
    if (8 & gContinuedByte_03002B64) {
        gMain2Byte_03007008 = 1;
        gRenderMode = 0;
        gMainState = 3;
        gMainSubstate = 2;
        gUnknown_0300137C = 0;
    }
}

void sub_0806F0E0(void) {
    LZ77UnCompVram(gUnknown_08485A70, (void *)0x06010000);
    LZ77UnCompVram(&gUnknown_087C9F48, &gUnknown_03001830);
    gUnknown_0300137C = 6;
}

void sub_0806F9B8(void) {
    gMainState = 3;
    gMainSubstate = 2;
    gUnknown_0300137C = 0;
}

void sub_08070804(void) {
    if (gFrameCounter & 1) {
        gBgScroll3.y += 1;
    }
}

s32 sub_08071DFC(void) {
    gState0TransferWork.bytes[0x10] += 1;
    return 1;
}

void sub_08072B18(void *arg0, u8 arg1) {
    (*(s32 *)((u8 *)(arg0) + 0x2C)) = (s32) arg1;
}

void sub_08073C5C(const struct SoundSampleHeader *const *bank) {
    gFamilySoundRoot74028->instruments = bank;
}

void sub_08073C70(const struct SoundSampleHeader *const *bank) {
    gFamilySoundRoot74028->drums = bank;
}

void sub_08073E1C(void *arg0) {
    (*(s8 *)((u8 *)(arg0) + 0x3E)) = 3;
}

void sub_08073F90(void *arg0) {
    (*(s8 *)((u8 *)(arg0) + 0x3E)) = 5;
}

void sub_08073FB8(void *arg0) {
    (*(s8 *)((u8 *)(arg0) + 0x3E)) = 4;
}

s32 sub_08074540(void) {
    return ((u8) (*(u8 *)((u8 *)(gUnknown_03007014) + 0x72C)) >> 1) & 1;
}

void sub_08074A78(const struct SoundSongHeader *const *bank) {
    gFamilySoundRoot74028->music = bank;
}

void sub_08074D3C(const struct SoundSongHeader *const *bank) {
    gFamilySoundRoot74028->effects = bank;
}

void sub_08074FE8(const struct SoundAuxBank *bank) {
    gFamilySoundRoot74028->aux = bank;
}

s32 sub_08075130(void) {
    s32 var_r2;

    var_r2 = 0;
    if (((*(s16 *)((u8 *)(gUnknown_03007014) + 0x44)) != 0) || ((*(s16 *)((u8 *)(gUnknown_03007014) + 0xB8)) != 0) || ((*(s16 *)((u8 *)(gUnknown_03007014) + 0x12C)) != 0) || ((*(s16 *)((u8 *)(gUnknown_03007014) + 0x1A0)) != 0) || ((*(s16 *)((u8 *)(gUnknown_03007014) + 0x3E4)) != 0) || ((*(s16 *)((u8 *)(gUnknown_03007014) + 0x458)) != 0)) {
        var_r2 = 1;
    }
    return var_r2;
}
