/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "object_numeric_helpers.h"

extern s32 gUnknown_0807C430;

void sub_08069EDC(void);

void sub_08069EDC(void) {
    volatile u32 *dma;
    volatile u16 *blend;
    sub_08048864(1U, 0xC808U, 0x10BU, 3U, 3U);
    gFrameObjects[1].screenY = 0x40;
    gFrameObjects[1].unknown1A = 0;
    dma=(void*)0x040000D4;
    dma[0]=(u32)&gUnknown_0807C430;
    dma[1]=0x05000260;
    dma[2]=0x84000008;
    (void)dma[2];
    *(volatile u16*)0x04000050=0xC40;
    *(volatile u16*)0x04000052=0x10;
}
