#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_callbacks.h"
#include "bg_scroll.h"
#include "compression.h"

extern const u8 gState0MapImage_084C7F08[];
extern const u8 gState0MapPalette_084C8014[];

void sub_080103F4(void)
{
    volatile u32 *dma;
    *(volatile u16 *)0x04000000 |= 0x100;
    *(volatile u16 *)0x04000008 = 0x500;
    gBgScroll0.x = 0;
    gBgScroll0.y = 0;
    LeDecompress(gState0MapImage_084C7F08, (void *)0x06002600);
    dma = (volatile u32 *)0x040000D4;
    dma[0] = (u32)gState0MapPalette_084C8014;
    dma[1] = 0x050001A0;
    dma[2] = 0x84000008;
    (void)dma[2];
    gState0TypedWork.bytes[0x3F] = 0;
    gState0TypedWork.selection.word48 = 0;
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C++;
}
