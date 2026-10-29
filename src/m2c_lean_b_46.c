/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_command_data.h"
#include "object_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_inventory.h"
#include "state0_work.h"

struct Inventory41D70 {
    u8 flags;
    u8 kind;
    s16 value2;
    u8 byte4;
    u8 level5;
    u8 byte6;
    u8 byte7;
    u8 byte8;
    u8 pad9[0x17];
    u8 stats[8];
    u8 pad28[0x18];
};

extern struct Inventory41D70 gInventory41D70[] asm("gInventoryRecords");

u32 sub_08041D70(u8 kind);

u32 sub_08041D70(u8 kind) {

    u32 i;

    sub_08041D04(gInventoryMetadata_083B62D8 + kind * 16, &gState0TypedWork.bytes[0xEE], 16);
    for (i = 0; i <= 0x1D; i++) {
        if (!(0x80 & gInventory41D70[i].flags)) {
            gInventory41D70[i].flags |= 0x80;
            gInventory41D70[i].kind = kind;
            gInventory41D70[i].byte4 = gState0TypedWork.bytes[0xEF];
            gInventory41D70[i].byte6 = gState0TypedWork.bytes[0xF0];
            gInventory41D70[i].byte7 = gState0TypedWork.bytes[0xF5];
            gInventory41D70[i].level5 = sub_0804206C();
            gInventory41D70[i].byte8 = sub_080420C4(gInventory41D70[i].level5, gState0TypedWork.bytes[0xF1], gState0TypedWork.bytes[0xF2], gState0TypedWork.bytes[0xF3], gState0TypedWork.bytes[0xF4]);
            gInventory41D70[i].value2 = (gInventory41D70[i].level5 + 1) * 100;
            if ((u8)(gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xF6] + gState0TypedWork.bytes[0xF6] > 100)
                gInventory41D70[i].stats[0] = 100;
            else
                gInventory41D70[i].stats[0] = gState0TypedWork.bytes[0xF6] + (gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xF6];
            if ((u8)(gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xF7] + gState0TypedWork.bytes[0xF7] > 100)
                gInventory41D70[i].stats[1] = 100;
            else
                gInventory41D70[i].stats[1] = gState0TypedWork.bytes[0xF7] + (gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xF7];
            if ((u8)(gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xF8] + gState0TypedWork.bytes[0xF8] > 100)
                gInventory41D70[i].stats[2] = 100;
            else
                gInventory41D70[i].stats[2] = gState0TypedWork.bytes[0xF8] + (gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xF8];
            if ((u8)(gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xF9] + gState0TypedWork.bytes[0xF9] > 100)
                gInventory41D70[i].stats[3] = 100;
            else
                gInventory41D70[i].stats[3] = gState0TypedWork.bytes[0xF9] + (gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xF9];
            if ((u8)(gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xFA] + gState0TypedWork.bytes[0xFA] > 100)
                gInventory41D70[i].stats[4] = 100;
            else
                gInventory41D70[i].stats[4] = gState0TypedWork.bytes[0xFA] + (gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xFA];
            if ((u8)(gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xFB] + gState0TypedWork.bytes[0xFB] > 100)
                gInventory41D70[i].stats[5] = 100;
            else
                gInventory41D70[i].stats[5] = gState0TypedWork.bytes[0xFB] + (gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xFB];
            if ((u8)(gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xFC] + gState0TypedWork.bytes[0xFC] > 100)
                gInventory41D70[i].stats[6] = 100;
            else
                gInventory41D70[i].stats[6] = gState0TypedWork.bytes[0xFC] + (gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xFC];
            if ((u8)(gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xFD] + gState0TypedWork.bytes[0xFD] > 100)
                gInventory41D70[i].stats[7] = 100;
            else
                gInventory41D70[i].stats[7] = gState0TypedWork.bytes[0xFD] + (gInventory41D70[i].level5 / 10u) * gState0TypedWork.bytes[0xFD];
            return i;
        }
    }
    return i;
}
