/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_work.h"
#include "tile_text.h"


void sub_08015760(void);

void sub_08015760(void) {


    u32 index;
    u32 leftY, rightY;
    volatile u16 *leftControl, *rightControl;
    /* One counter spans both three-bank scans, matching its ROM lifetime. */
    index = 0;
    leftControl = (volatile u16 *)0x0400000E;
    leftY = 4;
    do {
        u8 *setup=gSetupBuffer_03000590;
        u8 *record=(u8 *)((index<<8)+(u32)setup);
        if (record[0x40])
            sub_08042698(2,2,2,leftY,*leftControl,(((u32)record[0x91] << 18) + 0x80840000U) >> 16);
        else
            sub_08042698(2,2,2,leftY,*leftControl,0x8230);
        leftY += 3;
        index++;
    } while (index <= 2);
    index = 0;
    rightControl = (volatile u16 *)0x0400000E;
    rightY = 4;
    do {
        u8 *setup=gSetupBuffer_03000590;
        u8 *record=(u8 *)(((index+3)<<8)+(u32)setup);
        if (record[0x40])
            sub_08042698(2,2,0x1A,rightY,*rightControl,(((u32)record[0x91] << 18) + 0x80840000U) >> 16);
        else
            sub_08042698(2,2,0x1A,rightY,*rightControl,0x8230);
        rightY += 3;
        index++;
    } while (index <= 2);
}
