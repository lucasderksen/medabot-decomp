/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_work.h"


void sub_08027E1C(void);

void sub_08027E1C(void) {
    u8 mask;u8 *setupBase=gSetupBuffer_03000590;
    u8 *destination;
    u32 selector;
    u8 flags;
    u8 *selected1;
    u8 *selected2;
    u8 *selected3;
    u8 *selected4;
    u8 *selected5;
    u8 *initial;

    initial = setupBase+(gState0TransferWork.bytes[0x87] << 8);
    selector = initial[0xA8] - 4;
    switch (selector) {
    case 0:
        selected1 = (gState0TransferWork.bytes[0x87] << 8) + gSetupBuffer_03000590;
        destination = (u8 *)(selected1 + 0xD6);
        flags = selected1[0xD6];
        mask = 1;
        goto storeFlags;
    case 1:
        selected2 = (gState0TransferWork.bytes[0x87] << 8) + gSetupBuffer_03000590;
        destination = (u8 *)(selected2 + 0xD6);
        flags = selected2[0xD6];
        mask = 8;
        goto storeFlags;
    case 2:
        selected3 = (gState0TransferWork.bytes[0x87] << 8) + gSetupBuffer_03000590;
        destination = (u8 *)(selected3 + 0xD6);
        flags = selected3[0xD6];
        mask = 2;
        goto storeFlags;
    case 3:
        selected4 = (gState0TransferWork.bytes[0x87] << 8) + gSetupBuffer_03000590;
        destination = (u8 *)(selected4 + 0xD6);
        flags = selected4[0xD6];
        mask = 0x10;
        goto storeFlags;
    case 4:
        selected5 = (gState0TransferWork.bytes[0x87] << 8) + gSetupBuffer_03000590;
        destination = (u8 *)(selected5 + 0xD6);
        flags = selected5[0xD6];
        mask = 4;
storeFlags:
        *destination = mask | flags;
        break;
    default:
        initial[0xD6]=(0x20 | initial[0xD6]) | initial[0xD6];
        break;
    }
    gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
}
