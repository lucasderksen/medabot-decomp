/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "map_metadata.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "interrupts.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "rom_libc.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "state0_work.h"
#include "tile_text.h"
#include "continued_commands.h"
#include "later_graphics.h"
#include "palette_transfer_helpers.h"
#include "post_dispatch.h"
#include "render_work.h"
#include "state0_debug_menu.h"

struct Dma734 { const void *source; void *destination; u32 control; };

extern const u8 gUnknown_080AC71C[];
extern u16 gCopy6280C0202F800[];
extern u16 gUnknown_0202FC00[];
extern void sub_0805AC8C(void);

void sub_08048CF0(u16 *src, u16 *dst, s32 height, s32 width, s32 unused4, s32 unused5, s32 add);
void sub_0804B1B0(void);
void sub_08059734(u32 value, u32 digits, u32 x, u32 y);
void sub_0805ACB4(u16 color, s32 amount, s32 bank);

struct Work134 {
    u8 unknown000[0xC10];
    u8 savedC10[0x10];
    u8 copyC20[8];
    u8 unknownC28[0xC52 - 0xC28];
    u16 positionX;
    u16 positionY;
    u8 cellX;
    u8 cellY;
    u8 unknownC58[7];
    u8 byteC5F;
    u8 unknownC60[0xC6E - 0xC60];
    u16 otherX;
    u16 otherY;
    u8 otherCellX;
    u8 otherCellY;
    u8 unknownC74[2];
    u8 hasOther;
    u8 unknownC77[0xC93 - 0xC77];
    u8 state;
    u8 commands[4];
};

extern s32 sub_0807CD2C(s32 value, s32 divisor);
extern struct Work134 gWork134 asm("gContinuedWork_030057E0");
extern u32 sub_0807CEC8(u32 value, u32 divisor);
extern u32 sub_0807CF40(u32 value, u32 divisor);
extern u8 gContinuedByte_03002B64;

void sub_0804DF40(void);
void sub_0804E134(void);
void sub_0805A988(u32 number, s32 x, s32 y);

struct Context3A4 { u8 unknown00[0x36]; u16 tileBase; };
struct Context444 { u8 unknown00[0x36]; u16 tileBase; };
union TileEntryBCC {
    struct { u32 tile:10; u32 flip:2; u32 palette:4; } bits;
    u16 value;
    struct { u32 low:16; } clear;
};

extern s32 sub_0807CDF8(s32 value, s32 divisor);

void sub_0805A3A4(s32 number, s32 x, s32 y);
void sub_0805A444(s32 value, s32 x, s32 y);
void sub_0805ABCC(const u8 *text, u16 row, u16 x, u16 y, u8 count);

struct WorkE88 {
    u8 unknown000[0x7FE];
    u8 map;
    u8 unknown7FF[0xC48 - 0x7FF];
    u16 originX;
    u16 originY;
    u8 unknownC4C[6];
    u16 positionX;
    u16 positionY;
    u8 cellX;
    u8 cellY;
};

extern struct WorkE88 gWorkE88 asm("gContinuedWork_030057E0");

void sub_08052E88(void);

void sub_08048CF0(u16 *src, u16 *dst, s32 height, s32 width, s32 unused4, s32 unused5, s32 add) {

    s32 rows;
    s32 cols;
    s32 i;
    s32 j;

    rows = 0x20;
    if (height < 0x20)
        rows = height;
    for (i = 0; i < rows; i++) {
        cols = 0x20;
        if (width < 0x20)
            cols = width;
        for (j = 0; j < cols; j++)
            dst[i * 0x20 + j] = src[width * i + j] + add;
        if (width > 0x1F)
            for (j = 0; j < width - 0x20; j++)
                dst[0x400 + i * 0x20 + j] = src[width * i + 0x20 + j] + add;
    }
    if (height > 0x1F) {
        for (i = 0; i < height - 0x20; i++) {
            cols = 0x20;
            if (width < 0x20)
                cols = width;
            for (j = 0; j < cols; j++)
                dst[0x800 + i * 0x20 + j] = src[(i + 0x20) * width + j] + add;
            if (width > 0x1F)
                for (j = 0; j < width - 0x20; j++)
                    dst[0xC00 + i * 0x20 + j] = src[(i + 0x20) * width + 0x20 + j] + add;
        }
    }
}

void sub_0804B1B0(void) {

    s32 i;
    u32 root;
    u8 priority;

    if (gUnknown_030057E0[0xC4C] != 0) {
        for (i = 0x2E, root = (u32)gFrameObjects; i <= 0x7F; i++) {
            if (((struct FrameObject *)root)[i].priority == 0xFF)
                ((struct FrameObject *)root)[i].priority = 0xFF;
            else if (((struct FrameObject *)root)[i].priority != 0)
                ((struct FrameObject *)root)[i].priority = (((struct FrameObject *)root)[i].screenY + 0x10) / 4 + 0x40;
            else
                ((struct FrameObject *)root)[i].priority = 0;
            if (i == 0x30 && *(u16 *)(gUnknown_030057E0 + 0xC70) == *(u16 *)(gUnknown_030057E0 + 0xC54))
                *(u8 *)(root + 0xC0B) = *(u8 *)(root + 0xBCB) - 1;
            if (i == 0x59 && *(u16 *)(gUnknown_030057E0 + 0xC70) == *(u16 *)(gUnknown_030057E0 + 0xC54)) {
                priority = *(u8 *)(root + 0xC0B) - 1;
                *(u8 *)(root + 0x164B) = priority;
            }
        }
    }
}

void sub_08059734(u32 value, u32 digits, u32 x, u32 y) {

    u8 table[16];
    s32 i;
    u8 byte;
    u8 high;
    u8 low;

    memcpy(table, gUnknown_080AC71C, 16);
    for (i = 0; i < (s32)digits / 8; i++) {
        if ((s32)digits / 8 == 4) {
            if (i == 0)
                byte = value >> 24;
            if (i == 1)
                byte = (value & 0xFF0000) >> 16;
            if (i == 2)
                byte = (value & 0xFF00) >> 8;
            if (i == 3)
                byte = value;
        } else if ((s32)digits / 8 == 2) {
            if (i == 0)
                byte = (value & 0xFF00) >> 8;
            if (i == 1)
                byte = value;
        } else if ((s32)digits / 8 == 1) {
            if (i == 0)
                byte = value;
        }
        high = byte >> 4;
        low = byte - high * 16;
        ((volatile struct Dma734 *)0x040000D4)->source = gNumericTiles_080ACCF4 + table[high] * 32;
        ((volatile struct Dma734 *)0x040000D4)->destination = (void *)(gContinuedOtherWork_030057A0[0x13] * 32 + 0x06017A00);
        ((volatile struct Dma734 *)0x040000D4)->control = 0x84000008;
        ((volatile struct Dma734 *)0x040000D4)->control;
        sub_08048864(gContinuedOtherWork_030057A0[0x13], 0xC004, gContinuedOtherWork_030057A0[0x13] + 0x99, 0xE, 1);
        gFrameObjects[gContinuedOtherWork_030057A0[0x13]].screenX = x + i * 16;
        gFrameObjects[gContinuedOtherWork_030057A0[0x13]].screenY = y;
        gContinuedOtherWork_030057A0[0x13]++;
        ((volatile struct Dma734 *)0x040000D4)->source = gNumericTiles_080ACCF4 + table[low] * 32;
        ((volatile struct Dma734 *)0x040000D4)->destination = (void *)(gContinuedOtherWork_030057A0[0x13] * 32 + 0x06017A00);
        ((volatile struct Dma734 *)0x040000D4)->control = 0x84000008;
        ((volatile struct Dma734 *)0x040000D4)->control;
        sub_08048864(gContinuedOtherWork_030057A0[0x13], 0xC004, gContinuedOtherWork_030057A0[0x13] + 0x99, 0xE, 1);
        gFrameObjects[gContinuedOtherWork_030057A0[0x13]].screenX = x + i * 16 + 8;
        gFrameObjects[gContinuedOtherWork_030057A0[0x13]].screenY = y;
        gContinuedOtherWork_030057A0[0x13]++;
    }
}

void sub_0805ACB4(u16 color, s32 amount, s32 bank) {

    u32 i;
    s32 inverse;

    if (amount < 0)
        amount = 0;
    if (amount > 0x20)
        amount = 0x20;
    inverse = 0x20 - amount;
    for (i = 0; i < 0x100; i++) {
        if (i >= bank * 16 && i < (bank + 1) * 16) {
            gUnknown_0202FC00[i] = ((u32)((color & 0x1F) * amount + (gCopy6280C0202F800[i] & 0x1F) * inverse) >> 5)
                | (((u32)((color & 0x3E0) * amount + (gCopy6280C0202F800[i] & 0x3E0) * inverse) >> 5) & 0x3E0)
                | (((u32)((color & 0x7C00) * amount + (gCopy6280C0202F800[i] & 0x7C00) * inverse) >> 5) & 0x7C00);
        } else {
            gUnknown_0202FC00[i] = gCopy6280C0202F800[i];
        }
    }
    gUnknownCallback_03000B98 = sub_0805AC8C;
}

void sub_0804DF40(void) {

    u8 *work;
    struct FrameObject *object;
    u8 *copy;

    work = gUnknown_030057E0;
    switch (work[0xC93]) {
    case 0:
        sub_080497C0(work + 0xC10, work + 0xC18, 8);
        work[0xC10] = 0;
        work[0xC13] = 0;
        work[0xC17] = 0;
        sub_08052E0C(work[0xC94]);
        object = &gFrameObjects[0x2F];
        sub_080497C0(object, object - 1, 0x40);
        work[0xC5B] = 0;
        sub_08052BEC(0);
        object[0x2A].flags = 0xCC0C;
        object[1].flags = 0;
        object->unknown23[5] = 0;
        work[0xC5F] = 1;
        sub_08050B9C();
        sub_08047BA8(0x70);
        work[0xC93]++;
        break;
    case 1:
        sub_08050B9C();
        switch (work[0xC94]) {
        case 0:
            gContinuedByte_03002B64 |= 0x40;
            break;
        case 1:
            gContinuedByte_03002B64 |= 0x80;
            break;
        case 2:
            gContinuedByte_03002B64 |= 0x20;
            break;
        case 3:
            gContinuedByte_03002B64 |= 0x10;
            break;
        }
        gFrameObjects[0x2E].screenX = gFrameObjects[0x2F].screenX;
        if (gFrameObjects[0x2F].unknown23[5] < sub_0807CD2C(0x10, sub_08051940(0x2F)) * 2) {
            gFrameObjects[0x2E].screenY = gFrameObjects[0x2F].screenY
                - gScrollOscillationSines_083D6A2C[gFrameObjects[0x2F].unknown23[5] * (sub_08051940(0x2F) << 2)] / 16;
            gFrameObjects[0x2F].unknown23[5]++;
            if (gFrameObjects[0x2E].screenY / 4 <= (gFrameObjects[0x2F].screenY - 0x10) / 4)
                gFrameObjects[0x2E].priority = 0xFF;
            else
                sub_080487C8(0x2E);
        } else {
            gFrameObjects[0x2F].unknown23[3]++;
            gFrameObjects[0x2F].unknown23[5] = 0;
            copy = gUnknown_030057E0 + 0xC18;
            sub_080497C0(copy, copy - 8, 8);
            sub_08048888(0x2E);
            {
                u32 flag;
                copy[0x43] = flag = 1;
                sub_08052BEC(flag);
            }
            copy[0x47] = 0;
            sub_08050290();
        }
        break;
    }
}

void sub_0804E134(void) {

    switch (gWork134.state) {
    case 0:
        sub_08050B9C();
        if (gWork134.commands[gFrameObjects[0x2F].unknown23[3]] == 0xFF) {
            gWork134.state++;
            break;
        }
        if (gFrameObjects[0x2F].unknown23[5] == 0)
            break;
        switch ((gWork134.commands[gFrameObjects[0x2F].unknown23[3]] & 0xF0) >> 4) {
        case 0:
            gContinuedByte_03002B64 |= 0x40;
            break;
        case 1:
            gContinuedByte_03002B64 |= 0x80;
            break;
        case 2:
            gContinuedByte_03002B64 |= 0x20;
            break;
        case 3:
            gContinuedByte_03002B64 |= 0x10;
            break;
        }
        gFrameObjects[0x2F].unknown23[5]--;
        if (gFrameObjects[0x2F].unknown23[5] != 0)
            break;
        gFrameObjects[0x2F].unknown23[5] = sub_0807CD2C(0x10, sub_08051940(0x2F));
        gFrameObjects[0x2F].unknown23[4]--;
        if (gFrameObjects[0x2F].unknown23[4] != 0)
            break;
        gWork134.cellX = sub_0805273C(gWork134.positionX);
        gWork134.cellY = sub_08052760(gWork134.positionY);
        if (gWork134.hasOther != 0) {
            gWork134.otherCellX = sub_0805273C(gWork134.otherX);
            gWork134.otherCellY = sub_08052760(gWork134.otherY);
        }
        if (++gFrameObjects[0x2F].unknown23[3] > 3) {
            gWork134.state++;
            break;
        }
        if (gWork134.commands[gFrameObjects[0x2F].unknown23[3]] == 0xFF) {
            gWork134.state++;
            break;
        }
        sub_080500BC(0x2F, gWork134.commands[gFrameObjects[0x2F].unknown23[3]], gFrameObjects[0x2F].unknown23[7]);
        switch (gWork134.commands[gFrameObjects[0x2F].unknown23[3]] >> 4) {
        case 0:
            gContinuedByte_03002B64 |= 0x40;
            break;
        case 1:
            gContinuedByte_03002B64 |= 0x80;
            break;
        case 2:
            gContinuedByte_03002B64 |= 0x20;
            break;
        case 3:
            gContinuedByte_03002B64 |= 0x10;
            break;
        }
        break;
    case 1:
        sub_080497C0(gWork134.copyC20, gWork134.savedC10, 8);
        gWork134.byteC5F = 0;
        sub_08050290();
        break;
    }
}

void sub_0805A988(u32 number, s32 x, s32 y) {

    volatile u16 *dst;
    u16 digit;
    u32 palette;
    u32 base;

    palette = 1;
    base = 0x16;
    {
        volatile u16 *column = (volatile u16 *)0x0600B000 + x;
        dst = column + (y << 5);
    }
    digit = sub_0807CEC8(number, 1000000);
    if (digit != 0)
        *dst++ = (digit + base) | (palette << 12);
    else
        *dst++;
    digit = sub_0807CF40(sub_0807CEC8(number, 100000), 10);
    if (digit != 0 || sub_0807CEC8(number, 1000000) != 0)
        *dst++ = (digit + base) | (palette << 12);
    else
        *dst++;
    digit = sub_0807CF40(sub_0807CEC8(number, 10000), 10);
    if (digit != 0 || sub_0807CEC8(number, 1000000) != 0 || sub_0807CF40(sub_0807CEC8(number, 100000), 10) != 0)
        *dst++ = (digit + base) | (palette << 12);
    else
        *dst++;
    digit = sub_0807CF40(sub_0807CEC8(number, 1000), 10);
    if (digit != 0 || sub_0807CEC8(number, 1000000) != 0 || sub_0807CF40(sub_0807CEC8(number, 100000), 10) != 0
        || sub_0807CF40(sub_0807CEC8(number, 10000), 10) != 0)
        *dst++ = (digit + base) | (palette << 12);
    else
        *dst++;
    digit = sub_0807CF40(sub_0807CEC8(number, 100), 10);
    if (digit != 0 || sub_0807CEC8(number, 1000000) != 0 || sub_0807CF40(sub_0807CEC8(number, 100000), 10) != 0
        || sub_0807CF40(sub_0807CEC8(number, 10000), 10) != 0 || sub_0807CF40(sub_0807CEC8(number, 1000), 10) != 0)
        *dst++ = (digit + base) | (palette << 12);
    else
        *dst++;
    digit = sub_0807CF40(sub_0807CEC8(number, 10), 10);
    if (digit != 0 || sub_0807CEC8(number, 1000000) != 0 || sub_0807CF40(sub_0807CEC8(number, 100000), 10) != 0
        || sub_0807CEC8(number, 10000) != 0 || sub_0807CF40(sub_0807CEC8(number, 1000), 10) != 0
        || sub_0807CF40(sub_0807CEC8(number, 100), 10) != 0)
        *dst++ = (digit + base) | (palette << 12);
    else
        *dst++;
    *dst = (sub_0807CF40(number, 10) + base) | (palette << 12);
}

void sub_0805A3A4(s32 number, s32 x, s32 y) {

    volatile u16 *dst;
    u16 tile;
    u32 palette;
    s32 digit;

    palette = 0xD;
    tile = ((struct Context3A4 *)gMainContextPointer_03006F74)->tileBase + 0x16;
    {
        volatile u16 *column = (volatile u16 *)0x0600F000 + x;
        dst = column + (y << 5);
    }
    digit = sub_0807CDF8(sub_0807CD2C(number, 100), 10);
    if (digit != 0)
        *dst = (tile + digit) | (palette << 12);
    else
        *dst = digit;
    *dst++;
    if (sub_0807CDF8(sub_0807CD2C(number, 100), 10) != 0 || sub_0807CDF8(sub_0807CD2C(number, 10), 10) != 0)
        *dst = (tile + sub_0807CDF8(sub_0807CD2C(number, 10), 10)) | (palette << 12);
    else
        *dst = 0;
    *dst++;
    *dst = (tile + sub_0807CDF8(number, 10)) | (palette << 12);
}

void sub_0805A444(s32 value, s32 x, s32 y) {

    volatile u16 *dst;
    s16 tile;
    u32 palette;
    u32 block;

    value = sub_0807CDF8(value, 100);
    palette = 0xC;
    block = 0x1E;
    tile = ((struct Context444 *)gMainContextPointer_03006F74)->tileBase;
    {
        volatile u16 *column = (volatile u16 *)0x0600F000 + x;
        dst = column + (y << 5);
    }
    if (sub_0807CDF8(sub_0807CD2C(value, 100), 10) != 0 || sub_0807CDF8(sub_0807CD2C(value, 10), 10) != 0)
        *dst = (sub_0807CDF8(sub_0807CD2C(value, 10), 10) + (tile + 1)) | (palette << 12);
    else
        *dst = 0;
    *dst++;
    *dst = (sub_0807CDF8(value, 10) + (tile + 1)) | (palette << 12);
    dst = (volatile u16 *)(block << 11) + (x + 0x03000000) + ((y + 1) << 5);
    if (sub_0807CDF8(sub_0807CD2C(value, 100), 10) != 0 || sub_0807CDF8(sub_0807CD2C(value, 10), 10) != 0)
        *dst = (sub_0807CDF8(sub_0807CD2C(value, 10), 10) + (tile + 0xB)) | (palette << 12);
    else
        *dst = 0;
    *dst++;
    *dst = (sub_0807CDF8(value, 10) + (tile + 0xB)) | (palette << 12);
}

void sub_0805ABCC(const u8 *text, u16 row, u16 x, u16 y, u8 count) {

    union TileEntryBCC entry[1];
    u16 *destination;
    u16 i;

    entry->clear.low = 0;
    {
        u16 *column = (u16 *)0x0600B000 + x;
        destination = column + (y << 5);
    }
    entry->bits.palette = 1;
    for (i = 0; i < count; i++) {
        entry->bits.tile = (text + i)[row * count] + 0x9F;
        *destination++ = entry->value;
    }
}

void sub_08052E88(void) {

    s32 found = 0;
    const u8 *entry;
    s32 i;
    u8 map;

    map = gWorkE88.map;
    entry = gContinuedMapEntries_08412E60[map];

    i = 0;
    while (entry[i * 8] != 0xFF) {
        u8 x = entry[i * 8];
        u8 y = entry[i * 8 + 1];
        if (x == gWorkE88.cellX && y == gWorkE88.cellY) {
            gWorkE88.map = entry[i * 8 + 2];
            sub_080528F8(gWorkE88.map);
            sub_08052E0C(entry[i * 8 + 3] & 7);
            gWorkE88.positionX = entry[i * 8 + 6] * 16 + gWorkE88.originX;
            gWorkE88.positionY = entry[i * 8 + 7] * 16 + gWorkE88.originY;
            gWorkE88.cellX = sub_0805273C(gWorkE88.positionX);
            gWorkE88.cellY = sub_08052760(gWorkE88.positionY);
            sub_08052AA4();
            found = 1;
        }
        i++;
        if (found)
            break;
    }
    sub_0805309C();
}
