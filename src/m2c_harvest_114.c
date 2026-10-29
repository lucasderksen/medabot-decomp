/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_work.h"

extern const u8 *gState0NextCommands_083B6100[];
extern u8 gUnknown_084DEE34;
extern u8 gUnknown_084DF444;
extern u8 gUnknown_084E4658;
extern u8 gUnknown_08510278;
extern u8 gUnknown_08510298;

void sub_08029868(void);
void sub_08029E34(void);

void sub_08029868(void) {
    const u8 **table;
    u32 zeroByte, command;
    u16 zeroHalf;
    u8 *commandDestination;

    LeDecompress(&gUnknown_084DEE34, (void *)0x06014800);
    CpuFastSet(&gUnknown_08510278, (void *)0x050002E0, 8U);
    CpuFastSet(&gUnknown_084E4658, (void *)0x050002C0, 8U);
    gFrameObjects[0x21].flags = 0xC604;
    gFrameObjects[0x21].tableSelector = (zeroHalf = 0, zeroByte = 0);
    gFrameObjects[0x21].screenY = 0xE0;
    gFrameObjects[0x21].palette = 7;
    gFrameObjects[0x21].priority = 0xF0;
    gFrameObjects[0x21].scaleX = 0x40;
    gFrameObjects[0x21].scaleY = 0x40;
    gFrameObjects[0x21].angle = zeroHalf;
    gFrameObjects[0x21].unknown23[5] = zeroByte;
    *(commandDestination = &gFrameObjects[0x21].unknown2C[2]) = (command = 0x5C);
    gFrameObjects[0x21].unknown23[6] = 6;
    gFrameObjects[0x21].byte2B = 0x20;
    gFrameObjects[0x21].unknown2C[0] = 0xC0;
    gFrameObjects[0x21].unknown2C[1] = zeroByte;
    table=gState0NextCommands_083B6100;
    sub_08040B90(table[command], 0x21U);
    if (1 & gState0TransferWork.bytes[0xF8]) {
        gFrameObjects[0x21].screenX=0xB8;
    } else {
        gFrameObjects[0x21].screenX=0x38;
    }
    gState0TransferWork.bytes[0x51] = 1;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08029E34(void) {
    const u8 **table;
    u32 zeroByte, command;
    u16 zeroHalf;
    u8 *commandDestination;

    LeDecompress(&gUnknown_084DF444, (void *)0x06014800);
    CpuFastSet(&gUnknown_08510298, (void *)0x050002E0, 8U);
    CpuFastSet(&gUnknown_084E4658, (void *)0x050002C0, 8U);
    gFrameObjects[0x21].flags = 0xC604;
    gFrameObjects[0x21].tableSelector = (zeroHalf = 0, zeroByte = 0);
    gFrameObjects[0x21].screenY = 0xE0;
    gFrameObjects[0x21].palette = 7;
    gFrameObjects[0x21].priority = 0xF0;
    gFrameObjects[0x21].scaleX = 0x40;
    gFrameObjects[0x21].scaleY = 0x40;
    gFrameObjects[0x21].angle = zeroHalf;
    gFrameObjects[0x21].unknown23[5] = zeroByte;
    *(commandDestination = &gFrameObjects[0x21].unknown2C[2]) = (command = 0x5C);
    gFrameObjects[0x21].unknown23[6] = 6;
    gFrameObjects[0x21].byte2B = 0x20;
    gFrameObjects[0x21].unknown2C[0] = 0xC0;
    gFrameObjects[0x21].unknown2C[1] = zeroByte;
    table=gState0NextCommands_083B6100;
    sub_08040B90(table[command], 0x21U);
    if (1 & gState0TransferWork.bytes[0xF8]) {
        gFrameObjects[0x21].screenX=0xB8;
    } else {
        gFrameObjects[0x21].screenX=0x38;
    }
    gState0TransferWork.bytes[0x51] = 2;
    gState0TransferWork.bytes[0xAA] += 1;
}
