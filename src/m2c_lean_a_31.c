/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Part16AD8 {
    u8 name[13];
    u8 pad0D[3];
    u8 byte10;
    u8 data11[6];
    u8 id17;
};
struct Setup16AD8 {
    u8 pad00[0x48];
    struct Part16AD8 parts[4];
    u8 padA8[0x21];
    u8 kindC9;
    u8 partCA;
    u8 padCB[0x35];
};
struct Part16C0C {
    u8 name[13];
    u8 pad0D[3];
    u8 byte10;
    u8 data11[6];
    u8 id17;
};
struct Setup16C0C {
    u8 pad00[0x48];
    struct Part16C0C parts[4];
    u8 padA8[0x21];
    u8 kindC9;
    u8 partCA;
    u8 padCB[0x35];
};
struct Setup18D0C {
    u8 pad00[0xC4];
    u8 byteC4;
    u8 byteC5;
    u8 counterC6;
    u8 byteC7;
    u8 byteC8;
    u8 padC9[5];
    u8 flagsCE;
    u8 padCF[0x31];
};
struct Setup18DF4 {
    u8 pad00[0xC9];
    u8 kindC9;
    u8 byteCA;
    u8 counterCB;
    u8 byteCC;
    u8 byteCD;
    u8 flagsCE;
    u8 padCF[0x31];
};

extern const u8 *const gUnknownPointers_083B7048[];
extern const u8 *const gUnknown_083C4B90[];
extern s32 sub_08016E5C(u32, s32);
extern s32 sub_08018FF0(u32 bank, u32 part, s32 amount);
extern struct Setup16AD8 gSetup16AD8[] asm("gSetupBuffer_03000590");
extern struct Setup16C0C gSetup16C0C[] asm("gSetupBuffer_03000590");
extern struct Setup18D0C gSetup18D0C[] asm("gSetupBuffer_03000590");
extern struct Setup18DF4 gSetup18DF4[] asm("gSetupBuffer_03000590");
extern u32 gUnknown_084E45F8[];
extern u32 sub_08018EE0(u32 bank);
extern u32 sub_08018F0C(u32 bank, u32 part, u32 amount);
extern u32 sub_08018F6C(u32 side);

void sub_08016AD8(void);
void sub_08016C0C(void);
void sub_08018D0C(u32 bank);
void sub_08018DF4(u32 bank);
void sub_0801B004(u32 slot);
s32 sub_0801B0E8(u32 slot);

void sub_08016AD8(void) {

    sub_08040D0C(0x2D, 0xD);
    switch (gCounter6ED08_03001800.buffer64[0x1E]) {
    case 0:
        sub_08042678(gDebugMenuTextBuffer, 0xD);
        break;
    case 1:
    case 2:
    case 3:
        if (gSetup16AD8[gCounter6ED08_03001800.buffer64[0x1C]].parts[gCounter6ED08_03001800.buffer64[0x1E] - 1].data11[0] == 0) {
            sub_08041D04(gUnknown_083C4B90[0], gDebugMenuTextBuffer, 0xE);
        } else if (gSetup16AD8[gCounter6ED08_03001800.buffer64[0x1C]].kindC9 == 0x2B
            && gCounter6ED08_03001800.buffer64[0x1E] == gSetup16AD8[gCounter6ED08_03001800.buffer64[0x1C]].partCA) {
            sub_08041D04(gUnknown_083C4B90[1], gDebugMenuTextBuffer, 0xE);
        } else if (sub_08016E5C(gCounter6ED08_03001800.buffer64[0x1C], gCounter6ED08_03001800.buffer64[0x1E] - 1) != 0) {
            sub_08041D04(gUnknown_083C4B90[1], gDebugMenuTextBuffer, 0xE);
        } else if (gCounter6ED08_03001800.buffer64[0x1E] == 1 && gSetup16AD8[gCounter6ED08_03001800.buffer64[0x1C]].parts[0].byte10 == 0) {
            sub_08041D04(gUnknown_083C4B90[2], gDebugMenuTextBuffer, 0xE);
        } else {
            sub_08041D04(gUnknownPointers_083B7048[gSetup16AD8[gCounter6ED08_03001800.buffer64[0x1C]].parts[gCounter6ED08_03001800.buffer64[0x1E] - 1].name[2]],
                gDebugMenuTextBuffer, 0xE);
        }
        break;
    }
    sub_08040DB8(gDebugMenuTextBuffer, 0x2D, 0x13, 0xE, 0xA, 0xE, 0, 0);
}

void sub_08016C0C(void) {

    s32 shown;
    u8 flag;

    shown = 0;
    switch (gCounter6ED08_03001800.buffer64[0x1E]) {
    case 0:
        break;
    case 1:
    case 2:
    case 3:
        if (gSetup16C0C[gCounter6ED08_03001800.buffer64[0x1C]].parts[gCounter6ED08_03001800.buffer64[0x1E] - 1].data11[0] == 0) {
            sub_08041D04(gUnknown_083C4B90[0], gDebugMenuTextBuffer, 0xE);
            shown = 1;
        } else if (gSetup16C0C[gCounter6ED08_03001800.buffer64[0x1C]].kindC9 == 0x2B
                && gCounter6ED08_03001800.buffer64[0x1E] == gSetup16C0C[gCounter6ED08_03001800.buffer64[0x1C]].partCA) {
            sub_08041D04(gUnknown_083C4B90[1], gDebugMenuTextBuffer, 0xE);
            shown = 1;
        } else if (sub_08016E5C(gCounter6ED08_03001800.buffer64[0x1C], gCounter6ED08_03001800.buffer64[0x1E] - 1) != 0) {
            sub_08041D04(gUnknown_083C4B90[1], gDebugMenuTextBuffer, 0xE);
            shown = 1;
        } else if (gCounter6ED08_03001800.buffer64[0x1E] == 1 && gSetup16C0C[gCounter6ED08_03001800.buffer64[0x1C]].parts[0].byte10 == 0) {
            sub_08041D04(gUnknown_083C4B90[2], gDebugMenuTextBuffer, 0xE);
            shown = 1;
        }
        break;
    }
    if (shown) {
        flag = 8 & gState0TypedWork.bytes[0x84];
        if (flag) {
            sub_08040D0C(0x2D, 0xD);
        } else {
            sub_08040DB8(&gState0TypedWork.bytes[0x9E], 0x2D, 0x13, 0xE, 0xA, 0xE, flag, flag);
        }
    }
}

void sub_08018D0C(u32 bank) {

    s32 value;
    s32 found;
    u32 count;
    u32 part;
    u32 result;

    value = gSetup18D0C[bank].counterC6 - 4;
    if (value <= 0) {
        gSetup18D0C[bank].byteC4 = 0;
        gSetup18D0C[bank].byteC5 = 0;
        gSetup18D0C[bank].counterC6 = 0;
        gSetup18D0C[bank].byteC7 = 0;
        gSetup18D0C[bank].flagsCE |= 1;
        gCounter6ED08_03001800.flags55 |= 2;
        return;
    }
    gSetup18D0C[bank].counterC6 = value;
    if (gSetup18D0C[bank].byteC4 == 0x1F) {
        gCounter6ED08_03001800.value59 = gSetup18D0C[bank].byteC7;
        gCounter6ED08_03001800.buffer64[0x22] = 0;
        found = 0;
        count = 0;
        do {
            part = sub_08018EE0(bank);
            if (part == 0) {
                goto done;
            }
            result = sub_08018F0C(bank, part - 1, gCounter6ED08_03001800.value59);
            gCounter6ED08_03001800.buffer64[0x22] += result;
            gCounter6ED08_03001800.value59 = (0xFF00 & result) >> 8;
            found = 1;
            if (gCounter6ED08_03001800.value59 == 0) {
                goto done;
            }
        } while (++count <= 3);
    done:
        if (found) {
            gSetup18D0C[bank].byteC8 = gCounter6ED08_03001800.buffer64[0x22];
            gSetup18D0C[bank].flagsCE |= 4;
            gCounter6ED08_03001800.flags55 |= 8;
        }
    }
}

void sub_08018DF4(u32 bank) {

    s32 value;
    s32 found;
    u32 count;
    u32 part;
    u32 result;

    value = gSetup18DF4[bank].counterCB - 4;
    if (value <= 0) {
        gSetup18DF4[bank].kindC9 = 0;
        gSetup18DF4[bank].byteCA = 0;
        gSetup18DF4[bank].counterCB = 0;
        gSetup18DF4[bank].byteCC = 0;
        gSetup18DF4[bank].flagsCE |= 2;
        gCounter6ED08_03001800.flags55 |= 4;
        return;
    }
    gSetup18DF4[bank].counterCB = value;
    if (gSetup18DF4[bank].kindC9 == 0x13 || gSetup18DF4[bank].kindC9 == 0x14) {
        gCounter6ED08_03001800.value59 = gSetup18DF4[bank].byteCC;
        gCounter6ED08_03001800.buffer64[0x22] = 0;
        found = 0;
        count = 0;
        do {
            part = sub_08018F6C(bank);
            if (part == 0) {
                goto done;
            }
            result = sub_08018FF0(bank, part - 1, gCounter6ED08_03001800.value59);
            gCounter6ED08_03001800.buffer64[0x22] += result;
            gCounter6ED08_03001800.value59 = (0xFF00 & result) >> 8;
            found = 1;
            if (gCounter6ED08_03001800.value59 == 0) {
                goto done;
            }
        } while (++count <= 3);
    done:
        if (found) {
            gSetup18DF4[bank].byteCD = gCounter6ED08_03001800.buffer64[0x22];
            gSetup18DF4[bank].flagsCE |= 8;
            gCounter6ED08_03001800.flags55 |= 0x10;
        }
    }
}

void sub_0801B004(u32 slot) {

    u32 i;
    union { struct TileCoordinates tile; s32 packed; } c;

    CpuFastSet(gUnknown_084E45F8, (void *)0x050002C0, 8);
    for (i = 0; i <= 7; i++) {
        sub_08040CD0(i + 0x21, 1);
        gFrameObjects[0x21 + i].flags = ((gCounter6ED08_03001800.byte3C + 2) << 10) | 0x4204;
        gFrameObjects[0x21 + i].tableSelector = 0;
        gFrameObjects[0x21 + i].palette = 6;
        gFrameObjects[0x21 + i].priority = 0x81;
        gFrameObjects[0x21 + i].frameAndGroup = 0xA10;
        gFrameObjects[0x21 + i].commandDelay = i << 5;
        gFrameObjects[0x21 + i].commandOffset = gFrameObjects[0x5D + slot * 4].screenY;
        gFrameObjects[0x21 + i].unknown23[5] = 0;
        gFrameObjects[0x21 + i].unknown23[4] = i * 4;
        gFrameObjects[0x21 + i].unknown23[3] = 0;
        c.tile = sub_08042CA0(gFrameObjects[0x21 + i].commandDelay, 0x10, gFrameObjects[0x5D + slot * 4].screenX,
            gFrameObjects[0x21 + i].commandOffset, 8, 0);
        gFrameObjects[0x21 + i].screenX = c.packed;
        gFrameObjects[0x21 + i].screenY = c.packed >> 16;
        gFrameObjects[0x21 + i].scaleX = 4;
        gFrameObjects[0x21 + i].scaleY = 4;
    }
}

s32 sub_0801B0E8(u32 slot) {

    u32 i;
    u32 empty;
    union { struct TileCoordinates tile; s32 packed; } c;

    empty = 0;
    for (i = 0; i <= 7; i++) {
        if (gFrameObjects[0x21 + i].flags == 0) {
            empty++;
        } else {
            gFrameObjects[0x21 + i].flags = 0x8000 | gFrameObjects[0x21 + i].flags;
            gFrameObjects[0x21 + i].unknown23[5]++;
            gFrameObjects[0x21 + i].commandDelay -= 8;
            if (!(7 & gFrameObjects[0x21 + i].unknown23[5])) {
                gFrameObjects[0x21 + i].commandOffset--;
            }
            c.tile = sub_08042CA0(gFrameObjects[0x21 + i].commandDelay, gFrameObjects[0x21 + i].unknown23[3] + 0x10,
                gFrameObjects[slot * 4 + 0x5D].screenX, gFrameObjects[0x21 + i].commandOffset, 8, 0);
            gFrameObjects[0x21 + i].screenX = c.packed;
            gFrameObjects[0x21 + i].screenY = c.packed >> 16;
            if (gFrameObjects[0x21 + i].commandDelay > 0x80) {
                gFrameObjects[0x21 + i].priority = slot * 4 + 0x59;
            } else {
                gFrameObjects[0x21 + i].priority = 0x81;
            }
            if (gFrameObjects[0x21 + i].commandOffset > gFrameObjects[slot * 4 + 0x5D].screenY - 8
                && gFrameObjects[0x21 + i].scaleX != 0x40) {
                gFrameObjects[0x21 + i].scaleX += 4;
                gFrameObjects[0x21 + i].scaleY += 4;
            }
            if (gFrameObjects[0x21 + i].commandOffset < gFrameObjects[slot * 4 + 0x5D].screenY - 12
                && gFrameObjects[0x21 + i].scaleX != 4) {
                gFrameObjects[0x21 + i].scaleX -= 4;
                gFrameObjects[0x21 + i].scaleY -= 4;
            }
            if (gFrameObjects[0x21 + i].commandDelay == 0xC0
                && gFrameObjects[0x21 + i].commandOffset < gFrameObjects[slot * 4 + 0x5D].screenY - 0x10) {
                sub_08040CD0(0x21 + i, 1);
            }
        }
    }
    if (empty == 8) {
        return 1;
    }
    return 0;
}
