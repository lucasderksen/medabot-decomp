#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "equipment_helpers.h"
#include "graphics.h"
#include "interrupts.h"

extern u8 gUnknown_030057E0[];

void sub_08011344(void)
{
    volatile u32 *dma;
    u32 zero;
    u8 *work;
    u8 *selected;
    u8 *state;
    u8 *identifier;
    ClearFrameObjects(0, 128);
    ClearBgScrolls2();
    FillTilemapRect(32, 32, 0, 0, *(volatile u16 *)0x04000008, 0);
    FillTilemapRect(32, 32, 0, 0, *(volatile u16 *)0x0400000A, 0);
    FillTilemapRect(32, 32, 0, 0, *(volatile u16 *)0x0400000C, 0);
    FillTilemapRect(32, 32, 0, 0, *(volatile u16 *)0x0400000E, 0);
    StartBlendFade(5, 0x3F, 32);
    gUnknownCallback_030017F0 = DummyInterruptHandler;
    zero = 0;
    dma = (volatile u32 *)0x040000D4;
    dma[0] = (u32)&zero;
    dma[1] = 0x05000200;
    dma[2] = 0x85000080;
    (void)dma[2];
    zero = 0;
    dma[0] = (u32)&zero;
    dma[1] = 0x05000000;
    dma[2] = 0x85000080;
    (void)dma[2];
    work = gState0TransferWork.bytes;
    selected = work + 0x186;
    {
        u32 index = *selected;
        u32 scaled = index * 8;
        u8 *items = work + 0x16E;
        u32 value = items[scaled];
        value--;
        value = FindInventoryRecordById(value);
        state = gUnknown_03000440;
        value--;
        identifier = state + 0x133;
        *identifier = value;
    }
    {
        u32 index = *selected;
        u32 scaled = index * 8;
        u8 *items = work + 0x170;
        u32 value = items[scaled];
        state[0x134] = value;
    }
    {
        u32 index = *selected;
        u32 scaled = index * 8;
        u8 *items = work + 0x171;
        u32 value = items[scaled];
        state[0x135] = value;
    }
    {
        u32 index = *selected;
        u32 scaled = index * 8;
        u8 *items = work + 0x172;
        u32 value = items[scaled];
        state[0x136] = value;
    }
    {
        u32 index = *selected;
        u32 scaled = index * 8;
        u8 *items = work + 0x173;
        u32 value = items[scaled];
        state[0x137] = value;
    }
    sub_08067BDC(*identifier);
    (*selected)++;
}

void sub_08011500(void)
{
    u8 *work;
    PlayMusic(1);
    ClearFrameObjects(0, 128);
    ClearBgScrolls2();
    FillTilemapRect(32, 32, 0, 0, *(volatile u16 *)0x04000008, 0);
    FillTilemapRect(32, 32, 0, 0, *(volatile u16 *)0x0400000A, 0);
    FillTilemapRect(32, 32, 0, 0, *(volatile u16 *)0x0400000C, 0);
    FillTilemapRect(32, 32, 0, 0, *(volatile u16 *)0x0400000E, 0);
    work = gUnknown_030057E0;
    work[0xC2D] = 0;
    work[0xC2E] = 0;
    work[0xC2F] = 0;
    gUnknownCallback_030017F0 = DummyInterruptHandler;
    sub_0804765C(0);
}

void sub_080115B4(void)
{
    sub_08012098();
    StepFirstBgAutoScroll();
    sub_080123A0();
    sub_08012468();
    SnapshotPalettes();
    gUnknown_03000440[0x84] = 0;
    gNestedCallbackIndex++;
}

void sub_080115E8(void)
{
    sub_08012098();
    StepFirstBgAutoScroll();
    sub_080123A0();
    sub_08012468();
    if (gUnknown_03000440[0x84] <= 8)
    {
        BlendBgPaletteBanksNow(0, gUnknown_03000440[0x84] * 4, 0xFFFF);
        BlendObjPaletteBanksNow(0, gUnknown_03000440[0x84] * 4, 0xFFFF);
        gUnknown_03000440[0x84]++;
    }
    else
        gNestedCallbackIndex++;
}

void sub_08011644(void)
{
    volatile u32 *dma = (volatile u32 *)0x040000D4;
    dma[0] = 0x06002800;
    dma[1] = 0x02020800;
    dma[2] = 0x84000200;
    (void)dma[2];
    dma[0] = 0x06000280;
    dma[1] = 0x02021000;
    dma[2] = 0x84000380;
    (void)dma[2];
    dma[0] = (u32)gFrameObjects;
    dma[1] = 0x02028000;
    dma[2] = 0x84000800;
    (void)dma[2];
    StartBlendFade(5, 0x3F, 32);
    gUnknownCallback_030017F0 = DummyInterruptHandler;
    gNestedCallbackIndex++;
}
