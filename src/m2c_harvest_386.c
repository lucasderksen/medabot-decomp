/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "continued_selector_assets.h"
#include "frame.h"
#include "record_helpers.h"
#include "serial.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Dma70C0C {
    u32 source;
    u32 destination;
    u32 control;
};

extern const u16 gTransfer70C0C0807C890[16];
extern const u16 gTransfer70C0C085E1FD8[16];
extern const u16 gTransfer70C0C085E2F8C[16];
extern const u16 gTransfer70C0C085E4840[16];
extern const u16 gTransfer70C0C085E5048[16];
extern const u32 gTransfer70C0C087C5E50[104];
extern const u8 gTransfer70C0C085E1FF8[];
extern const u8 gTransfer70C0C085E2FAC[];
extern const u8 gTransfer70C0C085E4860[];
extern const u8 gTransfer70C0C085E5068[];
extern const u8 gTransfer70C0C087C5A10[];
extern u8 gUnknown_02031000[0x3480];
extern void sub_08068460(u32, u32, u32);

void sub_08070C0C(void);

void sub_08070C0C(void) {

    const void *imageSource;
    void *cursor;
    volatile struct Dma70C0C *dma;

    LZ77UnCompVram(gTransfer70C0C087C5A10, gUnknown_02031000);
    dma = (volatile struct Dma70C0C *)0x040000D4;
    dma->source = (u32)gTransfer70C0C087C5E50;
    dma->destination = 0x05000000;
    dma->control = 0x84000068;
    (void)dma->control;
    LZ77UnCompVram(gTransfer70C0C085E5068, (void *)0x06011B00);
    LZ77UnCompVram(gTransfer70C0C085E4860, (void *)0x06012400);
    LZ77UnCompVram(gTransfer70C0C085E2FAC, (void *)0x06012D00);
    /* Retain source-before-destination lifetime for the final LZ call. */
    imageSource = gTransfer70C0C085E1FF8;
    cursor = (void *)((void *)0x06013600);
    LZ77UnCompVram(imageSource, (void *)cursor);
    dma->source = (u32)gTransfer70C0C085E5048;
    dma->destination = 0x05000200;
    dma->control = 0x80000010;
    (void)dma->control;
    dma->source = (u32)gTransfer70C0C085E4840;
    dma->destination = 0x05000220;
    dma->control = 0x80000010;
    (void)dma->control;
    dma->source = (u32)gTransfer70C0C085E2F8C;
    dma->destination = 0x05000240;
    dma->control = 0x80000010;
    (void)dma->control;
    dma->source = (u32)gTransfer70C0C085E1FD8;
    dma->destination = 0x05000260;
    dma->control = 0x80000010;
    (void)dma->control;
    dma->source = (u32)gTransfer70C0C0807C890;
    dma->destination = 0x050003C0;
    dma->control = 0x80000010;
    (void)dma->control;
    /* Separate palette at 0807C850: compute its address as an integer. */
    dma->source = (u32)(const void *)((u32)gTransfer70C0C0807C890 - 0x40);
    dma->destination = 0x05000280;
    dma->control = 0x80000010;
    (void)dma->control;
    /* MMIO cursor arithmetic uses integer addresses throughout. */
    cursor = (void *)0x0400000A;
    *(volatile u16 *)cursor = 0xd05;
    cursor = (void *)((u32)cursor+2U);
    *(volatile u16 *)cursor = 0xe06;
    cursor = (void *)((u32)cursor+2U);
    *(volatile u16 *)cursor = 0xf07;
    cursor = (void *)((u32)cursor+66U);
    *(volatile u16 *)cursor = 0xc40;
    cursor = (void *)((u32)cursor+2U);
    *(volatile u16 *)cursor = 0xa0c;
    gState0TransferWork.bytes[0xC] = 0;
    gBgScroll3.x = 0;
    gBgScroll3.y = 0;
    gState0TransferWork.bytes[0xD] = 1;
    /* ROM helper narrows its three incoming words internally. */
    sub_08068460(4, 2, 0);
    *(volatile u16 *)0x04000000 |= 0x1E00;
    gUnknown_0300137C = 1;
}
