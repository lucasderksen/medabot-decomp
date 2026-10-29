#include "initialization.h"
#include "eeprom.h"

/* Matching C with agbcc 2.9-arm-000512, -O2 -mthumb-interwork.
 * There is no inline assembly or copied machine code here.
 */
extern IntrFunc const gDefaultIntrTable[14];
extern IntrFunc gUnknownCallback_03000B98;
extern IntrFunc gUnknownCallback_030017F0;
extern IntrFunc gUnknownCallback_03002C20;
void IntrMain(void);
void DummyInterruptHandler(void);

void InitInterrupts(void)
{
    CpuSet(gDefaultIntrTable, gIntrTable, CPU_SET_32BIT | 14);
    CpuSet((const void *)IntrMain, gIntrMainBuffer, CPU_SET_32BIT | 0x200);
    BIOS_INTR_VECTOR = (IntrFunc)gIntrMainBuffer;
    gUnknownCallback_03000B98 = DummyInterruptHandler;
    gUnknownCallback_030017F0 = DummyInterruptHandler;
    gUnknownCallback_03002C20 = DummyInterruptHandler;
    REG_IE = IRQ_VBLANK | IRQ_DMA1 | IRQ_DMA2 | IRQ_GAMEPAK;
    REG_DISPSTAT = DISPSTAT_VBLANK_IRQ;
    REG_IME = 1;
    Unknown_0807C8B0(0x40);
    Unknown_0805DEB0();
}

void ResetMemory(void)
{
    u32 zeroEwram;
    u32 zeroIwram;
    u32 zeroPalette;

    REG_IME = 0;
    zeroEwram = 0;
    CpuFastSet(&zeroEwram, EWRAM, CPU_SET_FILL | 0x10000);
    zeroIwram = 0;
    CpuFastSet(&zeroIwram, IWRAM, CPU_SET_FILL | 0x1F40);
    ResetSpritesAndVram();
    zeroPalette = 0;
    CpuFastSet(&zeroPalette, PALETTE_RAM, CPU_SET_FILL | 0x100);
    *(volatile u16 *)PALETTE_RAM = 0x7FFF;
}

void ResetSpritesAndVram(void)
{
    u32 oamValue;
    u32 zeroVram;
    s32 i;

    oamValue = 0xA0;
    CpuFastSet(&oamValue, OAM, CPU_SET_FILL | 0x100);
    /* Preserve the observed signed address comparison. Calculating the
     * terminating address as an integer avoids forming an array[-1] pointer.
     */
    i = 127;
    do
    {
        gOamShadow[i].attr0 = 0xA0;
        i--;
    } while ((s32)gOamShadow + i * 8 >= (s32)gOamShadow);
    zeroVram = 0;
    CpuFastSet(&zeroVram, VRAM, CPU_SET_FILL | 0x6000);
}
