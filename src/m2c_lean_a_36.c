/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "display_helpers.h"
#include "effect_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "graphics.h"
#include "input.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_inventory_view.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Setup183A4 { u8 unknown00[0x40]; u8 active40; u8 unknown41[0xBF]; };

extern const u8 *const gUnknown_083C4B90[];
extern const u8 gUnknown_083AD524[];
extern const void *const gState0NextScripts_083B5578[];
extern const u8 *const gUnknownPointers_083B7048[];
extern const void *const gUnknown_083B6B48[];
extern const void *const gUnknown_083B6FA4[];
extern const void *const gUnknown_083B80C0[];
extern const void *const gUnknown_083B82F0[];
extern const void *const gUnknown_083BDA04[];
extern struct Setup183A4 gSetup183A4[] asm("gSetupBuffer_03000590");
extern u8 gDebugMenuTextBuffer[];
extern void sub_08017734(u32 mode);
extern void sub_08017A14(u32 first, u32 second);
extern void sub_08017A7C(u32 mode, u32 x, u32 y);
extern void sub_08017B24(void);
extern void sub_08017BD0(void);
extern void sub_08017D50(void);
extern void sub_08017D90(void);
extern void sub_08017E00(void);
extern void sub_08017EA8(void);
extern void sub_08017F9C(void);

void sub_08008CA0(void);
void sub_0800E78C(void);
void sub_080173B4(u32 value);
void sub_080183A4(void);

void sub_08008CA0(void) {

    u8 result;

    sub_080093F8();
    switch (gState0TypedWork.bytes[0x42]) {
    case 0:
        switch (gState0TypedWork.bytes[0x44]) {
        case 0:
            result = sub_0803FB3C(gState0NextScripts_083B5578[6]);
            break;
        case 1:
            result = sub_0803FB3C(gState0NextScripts_083B5578[7]);
            break;
        case 2:
            result = sub_0803FB3C(gUnknown_083B6B48[gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown02[2]]);
            break;
        case 3:
            result = sub_0803FB3C(gState0PartStatusMessages_083B722C[gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0]]);
            break;
        case 4:
            result = sub_0803FB3C(gState0NextScripts_083B5578[8]);
            break;
        }
        break;
    case 1:
        switch (gState0TypedWork.bytes[0x44]) {
        case 0:
            if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte5 > 9) {
                sub_08041D04(gUnknownBytes_083B7F8C + gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte1 * 3, &gState0TypedWork.bytes[0xEE], 3);
                sub_08041D04(gUnknownBytes_083B7E54 + gState0TypedWork.bytes[0xEE] * 6, &gState0TypedWork.bytes[0x10E], 6);
                result = sub_0803FB3C(gUnknown_083B80C0[gState0TypedWork.bytes[0x113]]);
            } else {
                result = sub_0803FB3C(gUnknown_083B80C0[4]);
            }
            break;
        case 1:
            if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte5 > 0x1D) {
                sub_08041D04(gUnknownBytes_083B7F8C + gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte1 * 3, &gState0TypedWork.bytes[0xEE], 3);
                sub_08041D04(gUnknownBytes_083B7E54 + gState0TypedWork.bytes[0xEF] * 6, &gState0TypedWork.bytes[0x10E], 6);
                result = sub_0803FB3C(gUnknown_083B80C0[gState0TypedWork.bytes[0x113]]);
            } else {
                result = sub_0803FB3C(gUnknown_083B80C0[4]);
            }
            break;
        case 2:
            if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte5 > 0x3B) {
                sub_08041D04(gUnknownBytes_083B7F8C + gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte1 * 3, &gState0TypedWork.bytes[0xEE], 3);
                sub_08041D04(gUnknownBytes_083B7E54 + gState0TypedWork.bytes[0xF0] * 6, &gState0TypedWork.bytes[0x10E], 6);
                result = sub_0803FB3C(gUnknown_083B80C0[gState0TypedWork.bytes[0x113]]);
            } else {
                result = sub_0803FB3C(gUnknown_083B80C0[4]);
            }
            break;
        case 3:
            result = sub_0803FB3C(gState0NextScripts_083B5578[9]);
            break;
        case 4:
            result = sub_0803FB3C(gState0NextScripts_083B5578[10]);
            break;
        case 5:
            switch (gState0TypedWork.bytes[0x46]) {
            case 0:
            if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte5 > 9) {
                sub_08041D04(gUnknownBytes_083B7F8C + gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte1 * 3, &gState0TypedWork.bytes[0xEE], 3);
                sub_08041D04(gUnknownBytes_083B7E54 + (&gState0TypedWork.bytes[0xEE])[gState0TypedWork.bytes[0x46]] * 6, &gState0TypedWork.bytes[0x10E], 6);
                result = sub_0803FB3C(gUnknown_083B82F0[gState0TypedWork.bytes[0x10F]]);
            } else {
                result = sub_0803FB3C(gState0NextScripts_083B5578[11]);
            }
            break;
            case 1:
            if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte5 > 0x1D) {
                sub_08041D04(gUnknownBytes_083B7F8C + gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte1 * 3, &gState0TypedWork.bytes[0xEE], 3);
                sub_08041D04(gUnknownBytes_083B7E54 + (&gState0TypedWork.bytes[0xEE])[gState0TypedWork.bytes[0x46]] * 6, &gState0TypedWork.bytes[0x10E], 6);
                result = sub_0803FB3C(gUnknown_083B82F0[gState0TypedWork.bytes[0x10F]]);
            } else {
                result = sub_0803FB3C(gState0NextScripts_083B5578[11]);
            }
            break;
            case 2:
            if (gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte5 > 0x3B) {
                sub_08041D04(gUnknownBytes_083B7F8C + gInventoryRecords[gState0TypedWork.bytes[0x3D]].byte1 * 3, &gState0TypedWork.bytes[0xEE], 3);
                sub_08041D04(gUnknownBytes_083B7E54 + (&gState0TypedWork.bytes[0xEE])[gState0TypedWork.bytes[0x46]] * 6, &gState0TypedWork.bytes[0x10E], 6);
                result = sub_0803FB3C(gUnknown_083B82F0[gState0TypedWork.bytes[0x10F]]);
            } else {
                result = sub_0803FB3C(gState0NextScripts_083B5578[11]);
            }
            break;
            }
            break;
        }
        break;
    case 2:
        switch (gState0TypedWork.bytes[0x44]) {
        case 0:
            result = sub_0803FB3C(gState0NextScripts_083B5578[13]);
            break;
        case 1:
            result = sub_0803FB3C(gState0NextScripts_083B5578[14]);
            break;
        }
        break;
    }
    if (result != 0) {
        sub_0803FB0C();
        gUnknown_0300137C = 0x49;
    }
}

void sub_0800E78C(void) {

    u8 result;

    sub_0800EBFC();
    sub_0800F440();
    switch (gState0TypedWork.bytes[0x3E]) {
    case 0:
        switch (gState0TypedWork.bytes[0x44]) {
        case 0:
            result = sub_0803FB3C(gUnknown_083B82F0[gState0TypedWork.bytes[0xF0]]);
            break;
        case 1:
            result = sub_0803FB3C(gUnknown_083B6FA4[gState0TypedWork.bytes[0xEE]]);
            break;
        case 2:
            result = sub_0803FB3C(gState0NextScripts_083B5578[sub_08042B80(gState0TypedWork.bytes[0xF0]) + 0x11]);
            break;
        case 3:
            result = sub_0803FB3C(gUnknown_083BDA04[0]);
            break;
        case 4:
            result = sub_0803FB3C(gUnknown_083BDA04[1]);
            break;
        case 5:
            result = sub_0803FB3C(gUnknown_083BDA04[2]);
            break;
        case 6:
            result = sub_0803FB3C(gUnknown_083BDA04[3]);
            break;
        }
        break;
    case 1:
    case 2:
        switch (gState0TypedWork.bytes[0x44]) {
        case 0:
            result = sub_0803FB3C(gUnknown_083B82F0[gState0TypedWork.bytes[0xF0]]);
            break;
        case 1:
            result = sub_0803FB3C(gUnknown_083B6FA4[gState0TypedWork.bytes[0xEE]]);
            break;
        case 2:
            result = sub_0803FB3C(gState0NextScripts_083B5578[sub_08042B80(gState0TypedWork.bytes[0xF0]) + 0x11]);
            break;
        case 3:
            result = sub_0803FB3C(gUnknown_083BDA04[0]);
            break;
        case 4:
            result = sub_0803FB3C(gUnknown_083BDA04[1]);
            break;
        case 5:
            result = sub_0803FB3C(gUnknown_083BDA04[2]);
            break;
        case 6:
            result = sub_0803FB3C(gUnknown_083BDA04[4]);
            break;
        case 7:
            result = sub_0803FB3C(gUnknown_083BDA04[5]);
            break;
        }
        break;
    case 3:
        switch (gState0TypedWork.bytes[0x44]) {
        case 0:
            result = sub_0803FB3C(gUnknown_083B6FA4[gState0TypedWork.bytes[0xEE]]);
            break;
        case 1:
            result = sub_0803FB3C(gState0NextScripts_083B5578[0x13]);
            break;
        case 2:
            result = sub_0803FB3C(gUnknown_083BDA04[0]);
            break;
        case 3:
            result = sub_0803FB3C(gUnknown_083BDA04[6]);
            break;
        case 4:
            result = sub_0803FB3C(gUnknown_083BDA04[7]);
            break;
        case 5:
            result = sub_0803FB3C(gUnknown_083BDA04[8]);
            break;
        case 6:
            result = sub_0803FB3C(gUnknown_083BDA04[9]);
            break;
        case 7:
            result = sub_0803FB3C(gUnknown_083BDA04[10]);
            break;
        }
        break;
    }
    if (result != 0) {
        sub_0803FB0C();
        gUnknown_0300137C = 0x21;
    }
}

void sub_080173B4(u32 value) {

    s32 done = 0;
    s32 cleared = 0;
    u8 *record;

    sub_08040D0C(0x24, 0xD);
    switch (gCounter6ED08_03001800.buffer64[0x1E]) {
    case 0:
        sub_08042678(gDebugMenuTextBuffer, 0xD);
        cleared = 1;
        break;
    case 1:
        {
        u32 root = (u32)gSetupBuffer_03000590;
        record = (u8 *)(root + (gCounter6ED08_03001800.buffer64[0x1C] << 8));
        }
        if (record[5] > 9) {
            if (gCounter6ED08_03001800.pad56[2] == 0) {
                if (record[0xC1] == 0x50) {
                    sub_08041D04(gUnknownBytes_083B7F8C + record[1] * 3, gUnknown_0300052E, 3);
                    sub_08041D04(gUnknownBytes_083B7E54 + gUnknown_0300052E[0] * 6, gUnknown_0300052E + 0x20, 6);
                    sub_0803F63C(gUnknownPointers_083B7048[gUnknown_0300052E[0x21]], gUnknown_0300052E - 0x50, 0xE);
                    sub_08017734(0);
                } else {
                    sub_08041D04(gUnknown_083C4B90[4], gDebugMenuTextBuffer, 0xE);
                    done = 1;
                }
            } else {
                sub_08041D04(gUnknown_083C4B90[1], gDebugMenuTextBuffer, 0xE);
                done = 1;
            }
        } else {
            sub_08041D04(gUnknown_083C4B90[5], gDebugMenuTextBuffer, 0xE);
            done = 1;
        }
        break;
    case 2:
        {
        u32 root = (u32)gSetupBuffer_03000590;
        record = (u8 *)(root + (gCounter6ED08_03001800.buffer64[0x1C] << 8));
        }
        if (record[5] > 0x1D) {
            if (gCounter6ED08_03001800.pad56[2] == 0) {
                if (record[0xC1] == 0x50) {
                    sub_08041D04(gUnknownBytes_083B7F8C + record[1] * 3, gUnknown_0300052E, 3);
                    sub_08041D04(gUnknownBytes_083B7E54 + gUnknown_0300052E[1] * 6, gUnknown_0300052E + 0x20, 6);
                    sub_0803F63C(gUnknownPointers_083B7048[gUnknown_0300052E[0x21]], gUnknown_0300052E - 0x50, 0xE);
                    sub_08017734(0);
                } else {
                    sub_08041D04(gUnknown_083C4B90[4], gDebugMenuTextBuffer, 0xE);
                    done = 1;
                }
            } else {
                sub_08041D04(gUnknown_083C4B90[1], gDebugMenuTextBuffer, 0xE);
                done = 1;
            }
        } else {
            sub_08041D04(gUnknown_083C4B90[5], gDebugMenuTextBuffer, 0xE);
            done = 1;
        }
        break;
    case 3:
        {
        u32 root = (u32)gSetupBuffer_03000590;
        record = (u8 *)(root + (gCounter6ED08_03001800.buffer64[0x1C] << 8));
        }
        if (record[5] > 0x3B) {
            if (gCounter6ED08_03001800.pad56[2] == 0) {
                if (record[0xC1] == 0x50) {
                    sub_08041D04(gUnknownBytes_083B7F8C + record[1] * 3, gUnknown_0300052E, 3);
                    sub_08041D04(gUnknownBytes_083B7E54 + gUnknown_0300052E[2] * 6, gUnknown_0300052E + 0x20, 6);
                    sub_0803F63C(gUnknownPointers_083B7048[gUnknown_0300052E[0x21]], gUnknown_0300052E - 0x50, 0xE);
                    sub_08017734(0);
                } else {
                    sub_08041D04(gUnknown_083C4B90[4], gDebugMenuTextBuffer, 0xE);
                    done = 1;
                }
            } else {
                sub_08041D04(gUnknown_083C4B90[1], gDebugMenuTextBuffer, 0xE);
                done = 1;
            }
        } else {
            sub_08041D04(gUnknown_083C4B90[5], gDebugMenuTextBuffer, 0xE);
            done = 1;
        }
        break;
    }
    if (done == 1 || cleared == 1)
        sub_08017734(1);
    if (value != 0) {
        if (done != 0) {
            if ((u8)(8 & gState0TypedWork.bytes[0x84]) == 0)
                sub_08040DB8(&gState0TypedWork.bytes[0x9E], 0x24, 0x13, 0xE, 0xA, 0xE, 0, 0);
        } else {
            sub_08040DB8(gDebugMenuTextBuffer, 0x24, 0x13, 0xE, 0xA, 0xE, done, done);
        }
    } else {
        sub_08040DB8(gDebugMenuTextBuffer, 0x24, 0x13, 0xE, 0xA, 0xE, value, value);
    }
}

void sub_080183A4(void) {

    s32 changed = 0;
    u32 x, y, offset, base;
    base = (u32)gUnknown_083AD524;
    offset = (gState0TypedWork.bytes[0x3D] + gState0TypedWork.bytes[0x3C] * 3) * 2;
    x = *(const u8 *)(offset + base);
    offset++;
    y = *(const u8 *)(offset + base);

    if (gState0TypedWork.bytes[0x3C] == 0) {
        if (0xA0 & (u8)gRepeatedKeys) {
            if (gState0TypedWork.bytes[0x3D] != 2) {
                if (gSetup183A4[gState0TypedWork.bytes[0x3D] + 1 + gState0TypedWork.bytes[0x3C] * 3].active40 != 0) {
                    sub_08017A7C(0, x, y);
                    gState0TypedWork.bytes[0x3D]++;
                    changed = 1;
                } else if (gState0TypedWork.bytes[0x3D] == 0 && gSetup183A4[gState0TypedWork.bytes[0x3D] + 2 + gState0TypedWork.bytes[0x3C] * 3].active40 != 0) {
                    sub_08017A7C(0, x, y);
                    gState0TypedWork.bytes[0x3D] = 2;
                    changed = 1;
                }
            }
        } else if (0x50 & (u8)gRepeatedKeys) {
            if (gState0TypedWork.bytes[0x3D] != 0) {
                if (gSetup183A4[gState0TypedWork.bytes[0x3D] - 1 + gState0TypedWork.bytes[0x3C] * 3].active40 != 0) {
                    sub_08017A7C(0, x, y);
                    gState0TypedWork.bytes[0x3D]--;
                    changed = 1;
                } else if (gState0TypedWork.bytes[0x3D] == 2 && gSetup183A4[gState0TypedWork.bytes[0x3D] - 2 + gState0TypedWork.bytes[0x3C] * 3].active40 != 0) {
                    sub_08017A7C(0, x, y);
                    gState0TypedWork.bytes[0x3D] = 0;
                    changed = 1;
                }
            }
        }
    } else {
        if (0x60 & (u8)gRepeatedKeys) {
            if (gState0TypedWork.bytes[0x3D] != 0) {
                if (gSetup183A4[gState0TypedWork.bytes[0x3D] - 1 + gState0TypedWork.bytes[0x3C] * 3].active40 != 0) {
                    sub_08017A7C(0, x, y);
                    gState0TypedWork.bytes[0x3D]--;
                    changed = 1;
                } else if (gState0TypedWork.bytes[0x3D] == 2 && gSetup183A4[gState0TypedWork.bytes[0x3D] - 2 + gState0TypedWork.bytes[0x3C] * 3].active40 != 0) {
                    sub_08017A7C(0, x, y);
                    gState0TypedWork.bytes[0x3D] = 0;
                    changed = 1;
                }
            }
        } else if (0x90 & (u8)gRepeatedKeys) {
            if (gState0TypedWork.bytes[0x3D] != 2) {
                if (gSetup183A4[gState0TypedWork.bytes[0x3D] + 1 + gState0TypedWork.bytes[0x3C] * 3].active40 != 0) {
                    sub_08017A7C(0, x, y);
                    gState0TypedWork.bytes[0x3D]++;
                    changed = 1;
                } else if (gState0TypedWork.bytes[0x3D] == 0 && gSetup183A4[gState0TypedWork.bytes[0x3D] + 2 + gState0TypedWork.bytes[0x3C] * 3].active40 != 0) {
                    sub_08017A7C(0, x, y);
                    gState0TypedWork.bytes[0x3D] = 2;
                    changed = 1;
                }
            }
        }
    }
    if (changed != 0) {
        sub_08074DE0(2);
        sub_08017B24();
        sub_08017BD0();
        sub_08017D50();
        sub_08017D90();
        sub_08017E00();
        sub_08017EA8();
        sub_08017F9C();
        sub_08015838(gState0TypedWork.bytes[0x3D] + gState0TypedWork.bytes[0x3C] * 3, gCounter6ED08_03001800.buffer64);
        sub_08018074(gCounter6ED08_03001800.buffer64[0], gCounter6ED08_03001800.buffer64[1],
                     gCounter6ED08_03001800.buffer64[2], gCounter6ED08_03001800.buffer64[3]);
        sub_08018180();
        sub_08017A14(gState0TypedWork.bytes[0x3C] * 3, 0);
        sub_08043240(0, 8);
        sub_08042698(2, 2, 0xB, 2, *(u16 *)0x0400000A, 0x63C0);
    }
}
