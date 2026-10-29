#ifndef GUARD_GBA_H
#define GUARD_GBA_H

#include "global.h"

/* Hardware constants used by the reconstructed initialization routines. */
#define EWRAM ((void *)0x02000000)
#define IWRAM ((void *)0x03000000)
#define PALETTE_RAM ((void *)0x05000000)
#define VRAM ((void *)0x06000000)
#define OAM ((void *)0x07000000)

#define REG_DISPSTAT (*(volatile u16 *)0x04000004)
#define REG_IE (*(volatile u16 *)0x04000200)
#define REG_IF (*(volatile u16 *)0x04000202)
#define REG_IME (*(volatile u16 *)0x04000208)

#define DISPSTAT_VBLANK_IRQ (1u << 3)
#define IRQ_VBLANK (1u << 0)
#define IRQ_HBLANK (1u << 1)
#define IRQ_VCOUNT (1u << 2)
#define IRQ_TIMER0 (1u << 3)
#define IRQ_TIMER1 (1u << 4)
#define IRQ_TIMER2 (1u << 5)
#define IRQ_TIMER3 (1u << 6)
#define IRQ_SERIAL (1u << 7)
#define IRQ_DMA0 (1u << 8)
#define IRQ_DMA1 (1u << 9)
#define IRQ_DMA2 (1u << 10)
#define IRQ_DMA3 (1u << 11)
#define IRQ_KEYPAD (1u << 12)
#define IRQ_GAMEPAK (1u << 13)

/* CpuSet's count is in selected units; CpuFastSet's count is in words. */
#define CPU_SET_FILL (1u << 24)
#define CPU_SET_32BIT (1u << 26)

typedef void (*IntrFunc)(void);
#define BIOS_INTR_VECTOR (*(IntrFunc volatile *)0x03007FFC)

struct OamEntry
{
    u16 attr0;
    u16 attr1;
    u16 attr2;
    u16 affine;
};

/* Word registers at each DMA channel's source-address register. */
struct DmaTransfer
{
    const void *source;
    void *destination;
    u32 control;
};

void CpuSet(const void *source, void *destination, u32 control);
void CpuFastSet(const void *source, void *destination, u32 control);
s32 Div(s32 numerator, s32 denominator);
s32 DivArm(s32 denominator, s32 numerator);

#endif
