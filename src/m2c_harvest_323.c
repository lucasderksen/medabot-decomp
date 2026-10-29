/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_display.h"
#include "state0_work.h"

extern const u8 gUnknown_087CDEE0[];
extern const u8 gUnknown_087D1B48[];
extern const u8 gUnknown_087D1E74[];
extern void sub_08019184(u32 bank, u32 increment);

void sub_0801922C(u32 slot);
void sub_08070378(void);

void sub_0801922C(u32 slot) {

    u32 rawStatus;
    u8 status;
    u8 *record;
    u8 *setup;

    setup = gSetupBuffer_03000590;
    record = setup + (slot << 8);
    rawStatus = record[0xC9];
    status = rawStatus;
    if ((status != 0) && (((u32) (u8) (rawStatus - 0x11) <= 1U) || (status == 0x29))) {
        sub_08019184(slot, record[0xCC]);
    }
}

void sub_08070378(void) {
    /* DMA reads the fill word through its hardware source register. */
    u16 destination[640];
    u16 input[600];
    volatile u32 zero;
    volatile u32 *zeroPointer;
    s32 row, index, column, next, at30, at31, offset;
    u16 *source, *target, *pad30, *pad31, *inputRoot;
    volatile u32 *dma;
    const u8 *palette;

    LZ77UnCompVram(gUnknown_087CDEE0, (void *)0x06000000);
    LZ77UnCompVram(gUnknown_087D1B48, input);
    *(zeroPointer = &zero) = 0;
    {
        volatile u32 *first = (void *)0x040000D4;

        first[0] = (u32)zeroPointer;
        first[1] = 0x06007800;
        first[2] = 0x85000200;
        (void)first[2];
    }
    row = 0;
    palette = gUnknown_087D1E74;
    inputRoot = input;
    do {
        index = row << 5;
        offset = row << 4;
        next = row + 1;
        offset -= row;
        source = (u16 *)((u32)(offset << 2) + (u32)inputRoot);
        target = (u16 *)((u32)(row * 64) + (u32)destination);
        column = 29;
copy:
        *target = *source;
        source++;
        target++;
        column--;
        if (column >= 0) goto copy;

        at30 = index + 30;
        pad30 = at30 + destination;
        at31 = index + 31;
        pad31 = at31 + destination;
        *pad31 = 0;
        *pad30 = 0;
        row = next;
    } while (row <= 19);

    dma = (void *)0x040000D4;
    dma[0] = (u32)destination;
    dma[1] = 0x06007800;
    dma[2] = 0x80000280;
    (void)dma[2];
    dma[0] = (u32)palette;
    dma[1] = 0x05000000;
    dma[2] = 0x80000100;
    (void)dma[2];
    *(volatile u16 *)0x04000008 = 0xFC0;
    *(volatile u16 *)0x04000000 |= 0x100;
}
