/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "equipment_helpers.h"
#include "gba.h"
#include "main_callbacks.h"
#include "state0_work.h"


void sub_0805BFEC(u32 first, u32 second);

void sub_0805BFEC(u32 first, u32 second) {

    u16 scratch[32];
    s32 selectedBank = (u8)first;
    u32 paletteBase;
    u8 blendAmount = (u8)second;
    s32 bankIndex;
    u32 bankOffset;
    s32 nextBank;
    s32 colorIndex;

    paletteBase = (u32)gEquipmentPaletteShadow;
    bankIndex = 0;
    do {
        {
            u32 copyOffset = bankIndex << 6;
            CpuSet((void *)(copyOffset + paletteBase), scratch, 0x04000010U);
            bankOffset = copyOffset;
        }
        nextBank = bankIndex + 1;
        if (bankIndex == selectedBank) {
            for (colorIndex = 0; colorIndex <= 15; colorIndex++) {
                u16 a = scratch[colorIndex];
                u16 b = scratch[colorIndex + 16];
                s32 redA = a & 31, greenA = (a >> 5) & 31, blueA = (a >> 10) & 31;
                s32 redB = b & 31, greenB = (b >> 5) & 31, blueB = (b >> 10) & 31;

                redA = (redA - redB) * blendAmount / 32 + redB;
                greenA = (greenA - greenB) * blendAmount / 32 + greenB;
                blueA = (blueA - blueB) * blendAmount / 32 + blueB;
                /* Unsigned shifts also preserve the ROM's extrapolated bit patterns. */
                scratch[colorIndex] = ((u32)blueA << 10) | ((u32)greenA << 5) | (u32)redA;
            }
        }
        CpuSet(scratch, (void *)(0x05000000U + bankOffset), 0x04000008U);
        bankIndex = nextBank;
    } while (bankIndex <= 2);
}
