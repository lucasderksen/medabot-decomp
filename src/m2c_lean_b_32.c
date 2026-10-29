/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_debug_menu.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct SetupPart38BC0 {
    u8 pad0;
    u8 kind1;
    u8 pad2[3];
    u8 value5;
    u8 pad6[0x12];
};
struct SetupRecord38BC0 {
    u8 pad0[0x48];
    struct SetupPart38BC0 parts[3];
    u8 pad90[0x29];
    u8 byteB9;
    u8 padBA[0x1C];
    u8 flagsD6;
    u8 padD7[0x29];
};

extern s32 sub_08035880(u32, u32, u32);
extern s32 sub_080358B8(u32, u32, u32);
extern struct SetupRecord38BC0 gSetupRecords38BC0[] asm("gSetupBuffer_03000590");
extern void sub_0803579C(u32, u32);
extern void sub_08035814(u32);
extern void sub_080358F0(u32);

s32 sub_08033184(s32 slot);
void sub_08038BC0(void);
void sub_08041164(void *dest, u32 value);
void sub_0804126C(u8 *out, u32 value);

s32 sub_08033184(s32 slot) {

    u32 fill;
    u32 i;
    s32 offset;
    u8 *setup;
    u8 *part;
    struct ObjectSortEntry *entry;

    fill = 0;
    CpuFastSet(&fill, gObjectSortEntries, 0x01000080);
    i = 0;
    setup = gSetupBuffer_03000590;
    for (offset = 0; i <= 3; offset += 0x18, i++) {
        do {
            entry = &gObjectSortEntries[i];
        } while (0);
        entry->word4 = i;
        part = &setup[offset + (slot << 8)];
        if (part[0x59] != 0 && part[0x59] != part[0x4C])
            entry->key = part[0x4C] - part[0x59];
    }
    sub_0804242C(4);
    if (gObjectSortEntries[0].key != 0)
        return gObjectSortEntries[0].word4 + 1;
    return 0;
}

void sub_08038BC0(void) {

    u8 *part;
    u8 kind;

    gCounter6ED08_03001800.valueE8 = 0;
    sub_0803579C(gCounter6ED08_03001800.slot87, gCounter6ED08_03001800.partA7);
    if (sub_08035880(gCounter6ED08_03001800.slot87, gCounter6ED08_03001800.partA7, gCounter6ED08_03001800.value88) != 0)
        gCounter6ED08_03001800.valueE8 += gSetupRecords38BC0[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].value5 * 16;
    if (sub_080358B8(gCounter6ED08_03001800.slot87, gCounter6ED08_03001800.partA7, gCounter6ED08_03001800.value88) != 0)
        gCounter6ED08_03001800.valueE8 += gSetupRecords38BC0[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].value5 * 16;
    if (4 & gSetupRecords38BC0[gCounter6ED08_03001800.slot87].flagsD6) do {
        gCounter6ED08_03001800.valueE8 += gSetupRecords38BC0[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].value5;
    } while (0);
    do {
        gCounter6ED08_03001800.valueE8 += gCounter6ED08_03001800.records28[gCounter6ED08_03001800.record89].value0;
        sub_080358F0(gCounter6ED08_03001800.slot87);
    } while (0);
    part = (u8 *)gSetupRecords38BC0 + (gCounter6ED08_03001800.partA7 * 0x18 + (gCounter6ED08_03001800.slot87 << 8));
    kind = part[0x49];
    if (kind == 8)
        goto add;
    if (kind == 9) {
    add:
        gCounter6ED08_03001800.valueE8 += part[0x4D];
    }
    if (gSetupRecords38BC0[gCounter6ED08_03001800.slot87].parts[gCounter6ED08_03001800.partA7].kind1 == 0x34
        && gCounter6ED08_03001800.records28[gCounter6ED08_03001800.byte8A].kind3 == 0x33)
        gCounter6ED08_03001800.valueE8 += gCounter6ED08_03001800.records28[gCounter6ED08_03001800.byte8A].value4;
    sub_08035814(gCounter6ED08_03001800.slot87);
    sub_08035754(&gCounter6ED08_03001800.valueE8, gSetupRecords38BC0[gCounter6ED08_03001800.value88].byteB9);
}

void sub_08041164(void *dest, u32 value) {

    u8 digits[5];
    volatile u32 rest;
    u8 digit;
    u8 position;
    u8 i;
    s32 started;

    digits[0] = value / 10000;
    rest = value - value / 10000 * 10000;
    digits[1] = rest / 1000;
    rest = rest - rest / 1000 * 1000;
    digits[2] = rest / 100;
    rest = rest - rest / 100 * 100;
    digits[3] = rest / 10;
    rest = rest - rest / 10 * 10;
    digits[4] = rest;
    digit = 0;
    started = 0;
    position = 0;
    for (i = 0; i <= 9; i++) {
        if (i == 0) {
            ((u8 *)dest)[position] = 0x4C;
            position++;
        } else if (i == 4) {
            ((u8 *)dest)[position] = 0x40;
            position++;
        } else {
            if (i <= 2) {
                if (digits[digit] == 0) {
                    if (started) {
                        ((u8 *)dest)[position] = digits[digit] + 0x35;
                        position++;
                    }
                } else {
                    ((u8 *)dest)[position] = digits[digit] + 0x35;
                    started = 1;
                    position++;
                }
            } else {
                ((u8 *)dest)[position] = digits[digit] + 0x35;
                position++;
            }
            do {
                digit++;
                if (digit == 5) {
                    ((u8 *)dest)[position] = 0xFE;
                    return;
                }
            } while (0);
        }
    }
}

void sub_0804126C(u8 *out, u32 value) {

    u8 digits[5];
    volatile u32 rest;
    u8 digit;
    u8 position;
    u8 i;
    s32 started;

    digits[0] = value / 10000;
    rest = value - value / 10000 * 10000;
    digits[1] = rest / 1000;
    rest = rest - rest / 1000 * 1000;
    digits[2] = rest / 100;
    rest = rest - rest / 100 * 100;
    digits[3] = rest / 10;
    rest = rest - rest / 10 * 10;
    digits[4] = rest;
    digit = 0;
    started = 0;
    position = 0;
    for (i = 0; i <= 9; i++) {
        if (i == 0) {
        } else if (i == 4) {
            out[position] = 0x40;
            position++;
        } else {
            if (i <= 2) {
                if (digits[digit] == 0) {
                    if (started) {
                        out[position] = digits[digit] + 0x35;
                        position++;
                    }
                } else {
                    out[position] = digits[digit] + 0x35;
                    started = 1;
                    position++;
                }
            } else {
                out[position] = digits[digit] + 0x35;
                position++;
            }
            do {
                digit++;
                if (digit == 5) {
                    out[position] = 0xFE;
                    return;
                }
            } while (0);
        }
    }
}
