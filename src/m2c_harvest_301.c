/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern u8 gUnknown_030004F2;
extern u8 gUnknown_03000506;
extern u8 gUnknown_03001800[];

void sub_08029D28(void);
void sub_0802E358(void);

void sub_08029D28(void) {

    u32 i;
    u8 *g;
    u8 *q;
    u32 t;
    i = 0;
    g = gUnknown_03001800;
    do {
        q = g + 0xD2;
        if (*(u8 *)(i + (u32)q) != 0) {
            switch (i) {
            case 0:
                sub_0801A574(gDebugMenuTextBuffer, g[0x60] + i, 0x21U);
                break;
            case 1:
                sub_0801A574(&gUnknown_030004F2, g[0x60] + 1, 0x21U);
                break;
            case 2:
                sub_0801A574(&gUnknown_03000506, g[0x60] + 2, 0x21U);
                break;
            }
        }
        i += 1;
    } while (i <= 2U);
    t = gState0TypedWork.bytes[0x84] + 1;
    gState0TypedWork.bytes[0x84] = t;
    if ((gState0TypedWork.bytes[0x89] == 0) && (1 & *(u8 *)&gRepeatedKeys) && ((u8)t > 0x32U)) {
        gState0TypedWork.bytes[0x84] = 0x78;
    }
    if (gState0TypedWork.bytes[0x84] == 0x78) {
        sub_08040CD0((u8) ((u32) ((gUnknown_03001800[0x60] << 0x1A) + 0x21000000) >> 0x18), 0xCU);
        gUnknown_03001800[0xAA] += 1;
    }
}

void sub_0802E358(void) {

    u32 i;
    u8 *g;
    u8 *q;
    u32 t;
    i = 0;
    g = gUnknown_03001800;
    do {
        q = g + 0xD2;
        if (*(u8 *)(i + (u32)q) != 0) {
            switch (i) {
            case 0:
                sub_0801A574(gDebugMenuTextBuffer, g[0x60] + i, 0x21U);
                break;
            case 1:
                sub_0801A574(&gUnknown_030004F2, g[0x60] + 1, 0x21U);
                break;
            case 2:
                sub_0801A574(&gUnknown_03000506, g[0x60] + 2, 0x21U);
                break;
            }
        }
        i += 1;
    } while (i <= 2U);
    t = gState0TypedWork.bytes[0x84] + 1;
    gState0TypedWork.bytes[0x84] = t;
    if ((gState0TypedWork.bytes[0x89] == 0) && (1 & *(u8 *)&gRepeatedKeys) && ((u8)t > 0x32U)) {
        gState0TypedWork.bytes[0x84] = 0x78;
    }
    if (gState0TypedWork.bytes[0x84] == 0x78) {
        sub_08040CD0((u8) ((u32) ((gUnknown_03001800[0x60] << 0x1A) + 0x21000000) >> 0x18), 0xCU);
        gUnknown_03001800[0xAA] += 1;
    }
}
