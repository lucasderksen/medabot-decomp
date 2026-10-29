#include "reset.h"
#include "gba.h"
#include "initialization.h"
#include "input.h"
#include "main.h"
#include "serial.h"

#define gUnknown_03005030 (*(s8 *)0x03005030)
#define gUnknown_03002B8C (*(u32 *)0x03002B8C)
#define gUnknown_0300137C (*(u32 *)0x0300137C)
#define REG_BLDCNT (*(volatile u16 *)0x04000050)
#define REG_BLDY (*(volatile u16 *)0x04000054)
#define REG_SOUNDCNT_X (*(volatile u16 *)0x04000084)
#define REG_DMA0CNT_H (*(volatile u16 *)0x040000BA)

extern void VBlankIntrWait(void);

/* Two halfword views of the outgoing four-byte serial payload. */
struct ResetSerialWork
{
    u32 polledBits;
    u16 word04;
    s16 word06;
};

/* 0x080008C0; reinitialize the game within the running main loop. */
void ResetGame(void)
{
    u32 i;

    if (gUnknown_03005030 != 0)
    {
        ((struct ResetSerialWork *)&gMainSerialWork)->word04 = 0xFFFF;
        ((struct ResetSerialWork *)&gMainSerialWork)->word06 = -1;
        for (i = 0; i <= 7; i++)
        {
            sub_080022DC(gMainSerialWork.unknown04);
            VBlankIntrWait();
        }
        gUnknown_03005030 = 0;
        sub_080021A4();
    }

    VBlankIntrWait();
    REG_BLDCNT = 0xFF;
    REG_BLDY = 0x10;
    REG_SOUNDCNT_X = 0;
    REG_IME = 0;
    ResetMemory();
    InitInterrupts();
    sub_080020C8();
    gMainState = 3;
    gUnknown_03002B8C = 0;
    gUnknown_0300137C = 0;
    REG_DMA0CNT_H = 0;
}

/* 0x08000964; A+B+Select held when Start becomes newly pressed. */
s32 sub_08000964(void)
{
    if (((u8)gHeldKeys & (KEY_A | KEY_B | KEY_SELECT | KEY_START))
            == (KEY_A | KEY_B | KEY_SELECT | KEY_START)
        && ((u8)gNewKeys & KEY_START) != 0)
    {
        ResetGame();
        ReadKeys();
        return 1;
    }
    return 0;
}

void Nullsub_080009B4(void)
{
}

void Nullsub_080009B8(void)
{
}
