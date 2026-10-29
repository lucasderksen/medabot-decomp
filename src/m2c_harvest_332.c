/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "later_graphics.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern u32 sub_08032FD0(u32,u32);
extern u32 sub_08032FFC(void);
extern u32 sub_0803301C(void);
extern u32 sub_080332B4(u32);
extern u32 sub_080332D0(u32);
extern void sub_08033154(u32,u32);

void sub_08032A68(void);
void sub_08032C08(void);

void sub_08032A68(void) {

    /* Three candidates per scan; byte cursors retain the whole transfer buffer. */
    u32 entryIndex;

    gState0TransferWork.bytes[0x60] = (u8) sub_08032FB8((u32) gState0TransferWork.bytes[0x5C]);
    entryIndex = 0;
    {
        u8 *setup = gSetupBuffer_03000590;
        u8 *work = gState0TransferWork.bytes;
        u32 address = (u32)work;
        u8 *cursor = (u8 *)(address + 0x60);
        u8 *slots = (u8 *)(address + 0x61);
        do {
            if (((*(u8 *)(((*cursor)<<8)+(u32)setup+0x40)) != 0) && (sub_080332B4((*cursor)) != 0) && (sub_08032FD0((*cursor), setup[(work[0x5C]<<8)+6]) != 0)) {
                (*(u8 *)(entryIndex+(u32)slots)) = (*cursor) + 1;
            }
            (*cursor) = (u8) ((*cursor) + 1);
            entryIndex += 1;
        } while (entryIndex <= 2U);
    }
    if (sub_08032FFC() != 0) {
        gState0TransferWork.bytes[0x5E] = sub_0803301C() + 1;
    } else {
        gState0TransferWork.bytes[0x60] = (u8) sub_08032FB8((u32) gState0TransferWork.bytes[0x5C]);
        entryIndex = 0;
        {
            u8 *setup = gSetupBuffer_03000590;
            u8 *work = gState0TransferWork.bytes;
            u32 address = (u32)work;
            u8 *cursor = (u8 *)(address + 0x60);
            u8 *slots = (u8 *)(address + 0x61);
            do {
                if (((*(u8 *)(((*cursor)<<8)+(u32)setup+0x40)) != 0) && (sub_080332B4((*cursor)) != 0)) {
                    (*(u8 *)(entryIndex+(u32)slots)) = (*cursor) + 1;
                }
                (*cursor) = (u8) ((*cursor) + 1);
                entryIndex += 1;
            } while (entryIndex <= 2U);
        }
        if (sub_08032FFC() != 0) {
            gState0TransferWork.bytes[0x5E] = sub_0803301C() + 1;
        } else {
            gState0TransferWork.bytes[0x60] = (u8) sub_08032FB8((u32) gState0TransferWork.bytes[0x5C]);
            entryIndex = 0;
            {
                u8 *setup = gSetupBuffer_03000590;
                u8 *work = gState0TransferWork.bytes;
                u32 address = (u32)work;
                u8 *cursor = (u8 *)(address + 0x60);
                u8 *slots = (u8 *)(address + 0x61);
                do {
                    if (((*(u8 *)(((*cursor)<<8)+(u32)setup+0x40)) != 0) && (sub_08032FD0((*cursor), setup[(work[0x5C]<<8)+6]) != 0)) {
                        (*(u8 *)(entryIndex+(u32)slots)) = (*cursor) + 1;
                    }
                    (*cursor) = (u8) ((*cursor) + 1);
                    entryIndex += 1;
                } while (entryIndex <= 2U);
            }
            if (sub_08032FFC() != 0) {
                gState0TransferWork.bytes[0x5E] = sub_0803301C() + 1;
            } else {
                gState0TransferWork.bytes[0x60] = (u8) sub_08032FB8((u32) gState0TransferWork.bytes[0x5C]);
                gState0TransferWork.bytes[0x5E] = sub_08033090((u32) gState0TransferWork.bytes[0x60]) + 1;
            }
        }
    }
    gState0TransferWork.bytes[0x5F] = 1;
    sub_08033154(gState0TransferWork.bytes[0x5C], gState0TransferWork.bytes[0x5D]);
}

void sub_08032C08(void) {

    /* Three candidates per scan; byte cursors retain the whole transfer buffer. */
    u32 entryIndex;

    gState0TransferWork.bytes[0x60] = (u8) sub_08032FB8((u32) gState0TransferWork.bytes[0x5C]);
    entryIndex = 0;
    {
        u8 *setup = gSetupBuffer_03000590;
        u8 *work = gState0TransferWork.bytes;
        u32 address = (u32)work;
        u8 *cursor = (u8 *)(address + 0x60);
        u8 *slots = (u8 *)(address + 0x61);
        do {
            if (((*(u8 *)(((*cursor)<<8)+(u32)setup+0x40)) != 0) && (sub_080332D0((*cursor)) != 0) && (sub_08032FD0((*cursor), setup[(work[0x5C]<<8)+6]) != 0)) {
                (*(u8 *)(entryIndex+(u32)slots)) = (*cursor) + 1;
            }
            (*cursor) = (u8) ((*cursor) + 1);
            entryIndex += 1;
        } while (entryIndex <= 2U);
    }
    if (sub_08032FFC() != 0) {
        gState0TransferWork.bytes[0x5E] = sub_0803301C() + 1;
    } else {
        gState0TransferWork.bytes[0x60] = (u8) sub_08032FB8((u32) gState0TransferWork.bytes[0x5C]);
        entryIndex = 0;
        {
            u8 *setup = gSetupBuffer_03000590;
            u8 *work = gState0TransferWork.bytes;
            u32 address = (u32)work;
            u8 *cursor = (u8 *)(address + 0x60);
            u8 *slots = (u8 *)(address + 0x61);
            do {
                if (((*(u8 *)(((*cursor)<<8)+(u32)setup+0x40)) != 0) && (sub_080332D0((*cursor)) != 0)) {
                    (*(u8 *)(entryIndex+(u32)slots)) = (*cursor) + 1;
                }
                (*cursor) = (u8) ((*cursor) + 1);
                entryIndex += 1;
            } while (entryIndex <= 2U);
        }
        if (sub_08032FFC() != 0) {
            gState0TransferWork.bytes[0x5E] = sub_0803301C() + 1;
        } else {
            gState0TransferWork.bytes[0x60] = (u8) sub_08032FB8((u32) gState0TransferWork.bytes[0x5C]);
            entryIndex = 0;
            {
                u8 *setup = gSetupBuffer_03000590;
                u8 *work = gState0TransferWork.bytes;
                u32 address = (u32)work;
                u8 *cursor = (u8 *)(address + 0x60);
                u8 *slots = (u8 *)(address + 0x61);
                do {
                    if (((*(u8 *)(((*cursor)<<8)+(u32)setup+0x40)) != 0) && (sub_08032FD0((*cursor), setup[(work[0x5C]<<8)+6]) != 0)) {
                        (*(u8 *)(entryIndex+(u32)slots)) = (*cursor) + 1;
                    }
                    (*cursor) = (u8) ((*cursor) + 1);
                    entryIndex += 1;
                } while (entryIndex <= 2U);
            }
            if (sub_08032FFC() != 0) {
                gState0TransferWork.bytes[0x5E] = sub_0803301C() + 1;
            } else {
                gState0TransferWork.bytes[0x60] = (u8) sub_08032FB8((u32) gState0TransferWork.bytes[0x5C]);
                gState0TransferWork.bytes[0x5E] = sub_08033090((u32) gState0TransferWork.bytes[0x60]) + 1;
            }
        }
    }
    sub_08033154(gState0TransferWork.bytes[0x5C], gState0TransferWork.bytes[0x5D]);
}
