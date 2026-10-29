#include "main_menu_data.h"
#include "equipment_helpers.h"
#include "compression.h"
#include "continued_commands.h"
#include "fresh_helpers.h"
#include "gba.h"
#include "object_helpers.h"
extern u8 gUnknown_03000440[];
extern u8 gUnknown_030057E0[];
extern u8 gFreshWork_030064A0[];
#include "map_object_spawns.h"

void sub_08048000(u32 first)
{
    (*(volatile u16 *)0x04000008) = 0x500;
    (*(volatile u16 *)0x04000000) = 0x1F60;
    sub_080415E8((u8)first, 22, 7);
    gFreshWork_030064A0[0x64] = 0;
}

u32 sub_08048038(void)
{
    u32 result = 0;
    u32 address = (u32)gFreshWork_030064A0;
    u8 *status;
    address += 0x64;
    status = (u8 *)address;
    switch (*status)
    {
    case 1:
        if (!sub_08041CD4()) break;
    case 0:
        gUnknown_03000440[0x1B] = result;
        (*status)++;
        break;
    case 2:
        result = sub_08041674();
        break;
    }
    return result;
}

u32 sub_08048088(u32 mode)
{
    u32 result = 0;
    switch (mode)
    {
    case 0: { const u8 *table = (const u8 *)gEquipmentTable_083BEC10; u32 offset = gUnknown_030057E0[0x7FE] * 8; offset += 2; result = *(const u8 *)(offset + (u32)table); } break;
    case 1: { const u8 *table = (const u8 *)gEquipmentTable_083BEC10; u32 offset = gUnknown_030057E0[0x7FE] * 8; offset += 3; result = *(const u8 *)(offset + (u32)table); } break;
    }
    return result;
}

const void *sub_080480D4(u32 index)
{
    return gFreshPointers_08483ED8[index];
}

u32 sub_080483F8(void)
{
    const u8 *work = gUnknown_030057E0;
    u32 result;
    if (work[0xC30] != 255)
    {
        const u8 *table = gFreshBytes_0847E644;
        u32 index;
        index = work[0x7FE];
        result = table[index];
    }
    else result = work[0xC31];
    return result;
}

#include "bg_scroll.h"
#include "map_metadata.h"
s32 sub_08048684(s32 index);
void sub_08048708(void);
void sub_0804B2B0(void);
void sub_0804B1B0(void);
extern const u8 *const gFreshPointers_083F7E80[];
extern u8 gFreshWork_03006D38[];
extern const u8 *gFreshPointer_030057DC;
struct FreshScrollSettings { u8 pad00[0x1E]; u16 x[3]; u16 pad24; u16 y[3]; };
extern struct FreshScrollSettings gFreshSettings_03005310;
struct FreshDmaRegisters { u32 source, destination, control; };

void sub_080480E4(void)
{
    u32 zero = 0;
    gBgScroll1.x = gFreshSettings_03005310.x[0];
    gBgScroll1.y = gFreshSettings_03005310.y[0];
    gBgScroll2.x = gFreshSettings_03005310.x[1];
    gBgScroll2.y = gFreshSettings_03005310.y[1];
    gBgScroll3.x = gFreshSettings_03005310.x[2];
    gBgScroll3.y = gFreshSettings_03005310.y[2];
    sub_0804830C();
    sub_08048708();
    sub_0804B2B0();
    gUnknown_030057E0[0xC36] = zero;
    sub_08048174();
    sub_080513C8(gUnknown_030057E0[0xCBA]);
    sub_08052784();
    sub_080517F0();
    sub_08052B70();
    sub_08052F64();
    sub_08053108();
    sub_08048288();
    gUnknown_030057E0[0xC4C] = 1;
    sub_0804B1B0();
}

void sub_08048174(void)
{
    const u8 *source = gFreshPointers_08409480[gUnknown_030057E0[0x7FE]];
    u8 units = source[0];
    if (gUnknown_030057E0[0xC34] && source[2])
    {
        u8 *timer = gUnknown_030057E0 + 0xC36;
        if (*timer) (*timer)--;
        else
        {
            u8 *index = gUnknown_030057E0 + 0xC35;
            volatile struct FreshDmaRegisters *dma;
            /* The unchecked native byte cursor can fetch adjacent animation records. */
            if (*((const u8 *)(*index + (u32)source + 3)) == 255) *index = 0;
            {
            u32 address = (u32)gFreshPointer_030057DC + *((const u8 *)(*index + (u32)source + 3)) * units * 32;
            dma = (volatile struct FreshDmaRegisters *)0x040000D4;
            dma->source = address;
            dma->destination = 0x06009020;
            dma->control = (units * 16) | 0x80000000;
            dma->control;
            }
            (*index)++;
            *timer = 2;
        }
    }
}

s32 sub_08048210(s32 value)
{
    if (value == 0)
        value = gFreshBytes_083D2B26[gUnknown_030057E0[0xC5C]];
    else if (value <= 0xAF) { }
    else if (value <= 0xBF) { }
    else if (value <= 0xCF) { }
    else if (value <= 0xFE)
        {
        const u8 *const *tables = gFreshPointers_08413EE0;
        s32 index = value - 0xD0;
        const u8 *table = *((const u8 *const *)((u32)tables + (u32)index * 4));
        u32 address = (u32)gUnknown_030057E0;
        address += 0xC38;
        /* Native selectors can fetch adjacent ROM after the stored 13-byte rows. */
        value = *((const u8 *)((u32)table + *((u8 *)(index + address))));
    }
    else value = 255;
    if (value != 255 && value > 0xBF)
        { s32 delta = (value - 0xC0) * 2; s32 extra = gFreshWork_03006D38[6]; extra += 40; value = delta + extra; }
    return value;
}

void sub_08048288(void)
{
    s32 index = 0;
    u8 *destination = (u8 *)0x06010000;
    s32 value;
    while ((value = sub_08048684(index)) != 255)
    {
        if (gFreshPointers_083F7E80[value] == 0) value = 1;
        LZ77UnCompVram(gFreshPointers_083F7E80[value], destination);
        destination += 0x900;
        index++;
    }
}

void sub_080482CC(s32 value)
{
    s32 index = sub_08048210(value);
    const u8 *const *table = gFreshPointers_083F7E80;
    u8 *destination = (u8 *)0x06010000;
    s32 count = 11;
    do
    {
        if (table[index] == 0) index = 1;
        LZ77UnCompVram(table[index], destination);
        destination += 0x900;
        count--;
    } while (count >= 0);
}

extern const u8 *const gFreshPointers_083F9980[];

void sub_0804830C(void)
{
    const u8 *source = gFreshPointers_083F9980[gUnknown_030057E0[0x7FE]];
    if (source)
    {
        volatile struct FreshDmaRegisters *dma = (volatile struct FreshDmaRegisters *)0x040000D4;
        dma->source = (u32)source;
        dma->destination = 0x0202FA00;
        dma->control = 0x84000068;
        dma->control;
    }
    else
    {
        volatile struct FreshDmaRegisters *dma = (volatile struct FreshDmaRegisters *)0x040000D4;
        dma->source = 0x080AC72C;
        dma->destination = 0x0202FA00;
        dma->control = 0x84000008;
        dma->control;
        dma->source = 0x080AC7CC;
        dma->destination = 0x0202FA20;
        dma->control = 0x84000008;
        dma->control;
        dma->source = 0x080AC86C;
        dma->destination = 0x0202FA40;
        dma->control = 0x84000008;
        dma->control;
        dma->source = 0x080AC90C;
        dma->destination = 0x0202FA60;
        dma->control = 0x84000008;
        dma->control;
        dma->source = 0x080AC72C;
        dma->destination = 0x0202FA80;
        dma->control = 0x84000008;
        dma->control;
        dma->source = 0x080AC72C;
        dma->destination = 0x0202FAA0;
        dma->control = 0x84000008;
        dma->control;
        dma->source = 0x080AC72C;
        dma->destination = 0x0202FAC0;
        dma->control = 0x84000008;
        dma->control;
        dma->source = 0x080AC9AC;
        dma->destination = 0x0202FAE0;
        dma->control = 0x84000008;
        dma->control;
        dma->source = 0x080ACA4C;
        dma->destination = 0x0202FB00;
        dma->control = 0x84000008;
        dma->control;
    }
}
