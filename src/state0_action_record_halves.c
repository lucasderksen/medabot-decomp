#include "equipment_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "global.h"
#include "state0_next_helpers.h"

/* Partial observed access coverage, not an original complete work type. */
struct ObservedActionResultWork {
    u8 unknown00[0x60];
    u8 byte60;
    u8 unknown61[0x26];
    u8 selected87, selected88;
    u8 unknown89[0x2C];
    u8 completeB5;
    u8 unknownB6[2];
    u8 byteB8;
    u8 unknownB9[0x1D];
    u16 halfD6[4];
    u8 unknownDE[0xE];
    u16 halfEC;
    u8 unknownEE[8];
    u8 byteF6, unknownF7, byteF8;
    u8 unknownF9[6];
    u8 flagsFF;
    u8 unknown100[0x14];
    u8 byte114, byte115;
    u8 unknown116[0x49];
    u8 byte15F, byte160, byte161;
    u8 unknown162[0x26];
    u8 byte188, byte189;
};

/* Physical stride and named access bytes only, with no array extent claim. */
struct ObservedActionResultRecord {
    u8 unknown00[0xDE];
    u8 byteDE, unknownDF, byteE0, byteE1;
    u8 unknownE2[0x1E];
};

void sub_08034910(void)
{
    u32 count = 0;
    struct ObservedActionResultWork *work = (void *)gState0TransferWork.bytes;
    u8 *setup = gSetupBuffer_03000590;
    u8 *selected = &work->selected87;
    u16 *sum = &work->halfEC;
    do
    {
        u32 outputOffset = count * 2;
        u32 outputBase = (u32)work + 0xD6;
        *(u16 *)(outputOffset + outputBase) = setup[*selected * 256 + count * 24 + 0x59] / 2;
        *sum += setup[*selected * 256 + count * 24 + 0x59] / 2;
        count++;
    } while (count <= 3);
    sub_08034F08();
}
