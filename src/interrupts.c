#include "interrupts.h"
#include "serial.h"
#include "bg_scroll.h"
#include "render_work.h"

#define BIOS_INTR_CHECK (*(volatile u16 *)0x03007FF8)

extern volatile u16 gVBlankFlags;
extern s8 gVBlankMissedFrames;

extern u8 gBgScrollFlags;
extern u8 gUnknown_03000440[];
extern struct OamEntry gOamShadow[128];

extern void sub_08047204(void);
extern void sub_08045A14(void *first, void *second);
extern void sub_08074070(void);
extern void sub_08073274(void);

/* 0x080005D0; guard the main VBlank work against nested entry. */
void VBlankHandler(void)
{
    if ((gVBlankFlags & 1) == 0)
    {
        gVBlankFlags |= 1;
        RunVBlankWork();
        gVBlankFlags &= 0xFFFE;
        if (gMainSerialWork.polledBits & 0x80)
            sub_080023D8();

        REG_IME = 0;
        gVBlankMissedFrames++;
        if (gVBlankMissedFrames > 5 && gSerialState.sendReady != 0)
        {
            gMainSerialWork.disappeared = 0xFF;
            BIOS_INTR_CHECK |= IRQ_SERIAL;
        }
        BIOS_INTR_CHECK |= IRQ_VBLANK;
        REG_IME = 1;
    }
}

/* 0x0800065C; update scroll/OAM shadows, callbacks, and audio each VBlank. */
void RunVBlankWork(void)
{
    s32 i;

    if ((gBgScrollFlags & 1) == 0)
    {
        *(volatile u16 *)0x04000010 = gBgScroll0.x + gBgScrollBase.x;
        *(volatile u16 *)0x04000012 = gBgScroll0.y + gBgScrollBase.y;
        *(volatile u16 *)0x04000014 = gBgScroll1.x + gBgScrollBase.x;
        *(volatile u16 *)0x04000016 = gBgScroll1.y + gBgScrollBase.y;
        *(volatile u16 *)0x04000018 = gBgScroll2.x + gBgScrollBase.x;
        *(volatile u16 *)0x0400001A = gBgScroll2.y + gBgScrollBase.y;
        *(volatile u16 *)0x0400001C = gBgScroll3.x + gBgScrollBase.x;
        *(volatile u16 *)0x0400001E = gBgScroll3.y + gBgScrollBase.y;
    }

    if (gRenderMode != 0)
    {
        if (gRenderMode == 2)
        {
            sub_08047204();
            sub_08045A14(gRenderWork->objects, gRenderWork->unknownF8C);
            for (i = 0; i <= 87; i++)
                gOamShadow[i].affine = gRenderWork->objects[i].affine;
            for (i = 0; i <= 39; i++)
                gRenderWork->objects[i].affine = gOamShadow[88 + i].affine;
            if (gUnknown_03000440[0x131] == 0)
                CpuFastSet(gRenderWork->objects, (void *)0x070002C0, 0x50);
            gRenderWork->byte1094 = 0;
            gRenderWork->byte1095 = 0;
            if (gUnknown_03000440[0x12E] != 0)
                CpuFastSet(gOamShadow, OAM, 0xB0);
        }
        else
        {
            gRenderMode = 0;
        }
    }
    else if (gUnknown_03000440[0x12E] != 0)
    {
        CpuFastSet(gOamShadow, OAM, 0x100);
    }

    gUnknown_03000440[0x12E] = 0;
    gUnknownCallback_03000B98();
    gUnknownCallback_030017F0();
    gUnknownCallback_03000B98 = DummyInterruptHandler;
    BIOS_INTR_CHECK = IRQ_VBLANK;
    REG_IF = IRQ_VBLANK;
    sub_08074070();
    sub_08073274();
}

/* 0x08000824; the callback is initialized to DummyInterruptHandler. */
void HBlankHandler(void)
{
    gUnknownCallback_03002C20();
    REG_IF = IRQ_HBLANK;
}

/* 0x08000840. */
void DummyInterruptHandler(void)
{
}
