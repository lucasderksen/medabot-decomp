/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "composite_graphics.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "encounter_choices.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_command_data.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "interrupts.h"
#include "link_menu.h"
#include "object_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"
#include "utility_helpers.h"

struct InventoryView27DC {
    u8 byte0;
    u8 id1;
    u16 exp2;
    u8 pad4;
    u8 level5;
    u8 pad6[2];
    u8 value8;
    u8 pad9[55];
};
struct Part17EA8 { u8 unknown00[0x17]; u8 byte17; };
struct Setup17EA8 { u8 unknown00; u8 byte01; u8 unknown02[0x46]; struct Part17EA8 parts[4]; u8 unknownA8[0x58]; };
struct PartB274 {
    u8 name[13];
    u8 pad0D;
    u8 flags0E;
    u8 flags0F;
    u8 byte10;
    u8 data11[6];
    u8 id17;
};
struct SetupB274 {
    u8 pad00[0x40];
    u8 active40;
    u8 pad41[7];
    struct PartB274 parts[4];
    u8 padA8[0x12];
    u8 byteBA;
    u8 padBB;
    u8 flagsBC;
    u8 flagsBD;
    u8 padBE[0x1F];
    u8 partDD;
    u8 partDE;
    u8 partDF;
    u8 padE0[0x20];
};
struct Frame3CC8C {
    u16 flags;
    s16 screenX;
    s16 screenY;
    u16 frameAndGroup;
    u8 scaleX;
    u8 scaleY;
    u8 palette;
    u8 priority;
    u8 pad0C[0x10];
    u8 tableSelector;
    u8 pad1D[0x0A];
    u8 palette27;
    u8 count28;
    u8 byte29;
    u8 pad2A;
    u8 delay2B;
    u8 limit2C;
    u8 command2D;
    u8 anchor2E;
    u8 pad2F;
    s16 offsetX30;
    s16 offsetY32;
    u8 pad34[0x0C];
};

extern const u8 *gState0NextCommands_083B6100[];
extern struct InventoryView27DC gInventoryView27DC[] asm("gInventoryRecords");
extern struct Setup17EA8 gSetup17EA8[] asm("gSetupBuffer_03000590");
extern struct SetupB274 gSetupB274[] asm("gSetupBuffer_03000590");
extern void sub_0801B3AC(u32 slot);

void sub_080127DC(void);
void sub_08012A20(void);
void sub_08017EA8(void);
void sub_0801B274(u32 slot);
void sub_0803CC8C(void);

void sub_080127DC(void) {

    u32 i;
    struct InventoryView27DC *record;
    u32 value;
    u8 *row;
    u32 index;

    sub_0803F624(gCounter6ED08_03001800.levelUp16E, 0x18, 0);
    for (i = 0; i <= 2; i++) {
        {
            u32 root = (u32)gSetupBuffer_03000590;
            row = (u8 *)((i << 8) + root);
        }
        if (row[0xBA] == 0)
            continue;
        index = sub_08041D3C(row[1]) - 1;
        {
            u32 base = (u32)gInventoryView27DC;
            record = (struct InventoryView27DC *)((index << 6) + base);
        }
        if (record->level5 == 100)
            continue;
        if (record->exp2 > gCounter6ED08_03001800.amount16C) {
            record->exp2 -= gCounter6ED08_03001800.amount16C;
            continue;
        }
        record->level5++;
        record->exp2 = (record->level5 + 1) * 100;
        gCounter6ED08_03001800.levelUp16E[i][0] = record->id1 + 1;
        sub_08041D04(gInventoryMetadata_083B62D8 + record->id1 * 16, gUnknown_0300052E, 0x10);
        value = sub_080420C4(record->level5, gUnknown_0300052E[3], gUnknown_0300052E[4], gUnknown_0300052E[5], gUnknown_0300052E[6]);
        if (value != record->value8) {
            gCounter6ED08_03001800.levelUp16E[i][1] = 1;
            gCounter6ED08_03001800.levelUp16E[i][2] = record->id1;
            gCounter6ED08_03001800.levelUp16E[i][3] = record->value8;
            gCounter6ED08_03001800.levelUp16E[i][4] = record->id1;
            gCounter6ED08_03001800.levelUp16E[i][5] = value;
            record->value8 = value;
        }
        sub_08041D04(gUnknownBytes_083B7F8C + record->id1 * 3, gUnknown_0300052E, 3);
        if (record->level5 == 10) {
            gCounter6ED08_03001800.levelUp16E[i][6] = 1;
            gCounter6ED08_03001800.levelUp16E[i][7] = gUnknown_0300052E[0];
        }
        if (record->level5 == 30) {
            gCounter6ED08_03001800.levelUp16E[i][6] = 1;
            gCounter6ED08_03001800.levelUp16E[i][7] = gUnknown_0300052E[1];
        }
        if (record->level5 == 60) {
            gCounter6ED08_03001800.levelUp16E[i][6] = 1;
            gCounter6ED08_03001800.levelUp16E[i][7] = gUnknown_0300052E[2];
        }
    }
}

void sub_08012A20(void) {

    s32 zero;

    switch (gState0TypedWork.bytes[0x139]) {
    case 0:
        sub_08043CA8();
        sub_08043E54();
        *(volatile u16 *)0x04000000 &= 0xF0FF;
        *(volatile u16 *)0x04000008 = 0x500;
        *(volatile u16 *)0x0400000A = 0x1901;
        *(volatile u16 *)0x0400000C = 0x1A0A;
        *(volatile u16 *)0x0400000E = 0x1B0B;
        if (sub_0801A788(0) != 0)
            gState0TypedWork.bytes[0x139]++;
        break;
    case 1:
        gState0TypedWork.bytes[0x84] = 0;
        zero = 0;
        CpuFastSet(&zero, gFrameObjects, 0x01000800);
        *(volatile u16 *)0x04000000 |= 0x1F40;
        *(volatile u16 *)0x04000000 &= 0xFFDF;
        gState0TypedWork.bytes[0x139]++;
        break;
    case 2:
        sub_08015738();
        sub_08015760();
        sub_080158F8();
        sub_080159BC();
        sub_0801BBC4();
        sub_08043F9C();
        sub_080441A8(gEquipmentAssets_083B2628[gCounter6ED08_03001800.shift38 * 5 + 1]);
        gUnknownCallback_030017F0 = sub_08044100;
        gUnknown_0300137C++;
        gState0TypedWork.bytes[0x139] = 0;
        break;
    }
}

void sub_08017EA8(void) {

    u32 i;
    u8 *work;

    i = 0;
    work = gState0TypedWork.bytes;
    for (; i < 4; i++) {
        sub_08042B58(gSetup17EA8[gState0TypedWork.bytes[0x3D] + gState0TypedWork.bytes[0x3C] * 3].parts[i].byte17, i,
                     &gState0TypedWork.bytes[0xEE]);
        sub_08041D04(&gInventoryMetadata_083B62D8[gSetup17EA8[gState0TypedWork.bytes[0x3D] + gState0TypedWork.bytes[0x3C] * 3].byte01 * 16],
                     &work[0x10E], 16);
        if (gState0TypedWork.bytes[0xEE] == work[0x10F])
            sub_08042698(2, 2, 0xB, i * 2 + 4, *(volatile u16 *)0x0400000A, (u16)(gState0TypedWork.bytes[0x115] * 4 + 0xD340));
        else
            sub_08042698(2, 2, 0xB, i * 2 + 4, *(volatile u16 *)0x0400000A, 0xD340);
    }
}

void sub_0801B274(u32 slot) {

    u32 i;
    s32 zero;
    s32 zero2;
    u8 *clear;

    do {
        gSetupB274[slot].flagsBD &= 0xFE;
        gSetupB274[slot].partDE = gSetupB274[slot].partDD;
        if (gSetupB274[slot].partDD == 0) {
            goto clear;
        }
        if (gSetupB274[slot].partDD > 3) {
        clear:
            gSetupB274[slot].partDF = 0;
        } else {
            gSetupB274[slot].partDF = gSetupB274[slot].parts[gSetupB274[slot].partDD - 1].name[1];
        }
    } while (0);
    for (i = 0; i <= 3; i++) {
        gSetupB274[slot].parts[i].flags0E = 0;
        gSetupB274[slot].parts[i].flags0F = 0;
    }
    zero = 0;
    clear = &gCounter6ED08_03001800.kindA8;
    CpuSet(&zero, clear, 0x05000008);
    zero2 = 0;
    CpuSet(&zero2, clear + 0x20, 0x05000008);
    for (i = 0; i <= 5; i++) {
        if (gSetupB274[i].active40 != 0 && (0x18 & gSetupB274[i].flagsBD)
            && (u8)(gSetupB274[i].partDE - 1) <= 2
            && gSetupB274[i].parts[gSetupB274[i].partDE - 1].data11[0] == 0) {
            gSetupB274[i].flagsBD = 0xE7 & gSetupB274[i].flagsBD;
        }
    }
    for (i = 0; i <= 5; i++) {
        if (gSetupB274[i].byteBA != 0) {
            gSetupB274[i].flagsBC = 0xF & gSetupB274[i].flagsBC;
        }
    }
    sub_0801B3AC(slot);
}

void sub_0803CC8C(void) {

    struct Frame3CC8C *self;
    struct Frame3CC8C *f;
    struct Frame3CC8C *g;
    u32 slot;
    u32 root;

    root = (u32)((struct Frame3CC8C *)gFrameObjects);
    self = (struct Frame3CC8C *)(root + (gState0TypedWork.bytes[0x12F] << 6));
    if (self->delay2B != 0) {
        self->delay2B--;
        return;
    }
    if (self->count28 != self->limit2C) {
        self->count28++;
        return;
    }
    self->count28 = 0;
    slot = sub_08040D78(0xE, 0x10);
    f = &((struct Frame3CC8C *)gFrameObjects)[slot];
    f->flags = 0xC404;
    f->tableSelector = 0;
    if (!(2 & gCounter6ED08_03001800.flagsF8))
        f->screenX = (((struct Frame3CC8C *)gFrameObjects)[((struct Frame3CC8C *)gFrameObjects)[gState0TypedWork.bytes[0x12F]].anchor2E].screenX + ((struct Frame3CC8C *)gFrameObjects)[gState0TypedWork.bytes[0x12F]].offsetX30) & 0x1FF;
    else
        { struct Frame3CC8C *anchor = &((struct Frame3CC8C *)gFrameObjects)[((struct Frame3CC8C *)gFrameObjects)[gState0TypedWork.bytes[0x12F]].anchor2E]; u16 off = ((struct Frame3CC8C *)gFrameObjects)[gState0TypedWork.bytes[0x12F]].offsetX30; f->screenX = (anchor->screenX - off) & 0x1FF; }
    {
    u32 root2 = (u32)((struct Frame3CC8C *)gFrameObjects);
    g = (struct Frame3CC8C *)(root2 + (slot << 6));
    }
    g->screenY = (((struct Frame3CC8C *)gFrameObjects)[((struct Frame3CC8C *)gFrameObjects)[gState0TypedWork.bytes[0x12F]].anchor2E].screenY + ((struct Frame3CC8C *)gFrameObjects)[gState0TypedWork.bytes[0x12F]].offsetY32) & 0xFF;
    g->palette = ((struct Frame3CC8C *)gFrameObjects)[gState0TypedWork.bytes[0x12F]].palette27;
    g->priority = 0x80;
    g->byte29 = 0x23;
    g->command2D = ((struct Frame3CC8C *)gFrameObjects)[gState0TypedWork.bytes[0x12F]].command2D;
    sub_08040B90(gState0NextCommands_083B6100[((struct Frame3CC8C *)gFrameObjects)[gState0TypedWork.bytes[0x12F]].command2D], slot);
}
