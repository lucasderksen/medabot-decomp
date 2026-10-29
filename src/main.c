#include "main.h"
#include "initialization.h"
#include "input.h"

#define REG_DISPCNT (*(volatile u16 *)0x04000000)
#define REG_WAITCNT (*(volatile u16 *)0x04000204)

/* Only accessed fields are named. Gameplay roles remain provisional. */
struct UnknownMainCounter
{
    u8 unknown00[0x18];
    u32 counter18;
};

#define gUnknown_03002B8C (*(u32 *)0x03002B8C)
#define gUnknown_0300137C (*(u32 *)0x0300137C)
#define gUnknown_03001784 (*(u16 *)0x03001784)
#define gUnknown_03005030 (*(s8 *)0x03005030)
#define gUnknown_03002410 (*(u8 *)0x03002410)
#define gUnknown_03000588 (*(u8 *)0x03000588)
#define gUnknown_03000B90 (*(u8 *)0x03000B90)
#define gUnknown_03002B70 (*(struct UnknownMainCounter *)0x03002B70)

extern void InitAudio(void *context);
extern void VBlankIntrWait(void);
extern s32 sub_08000964(void);
extern void sub_08001520(void);

/* 0x0800025C. This entry loops forever; original names are unknown. */
void GameMain(void)
{
    s32 i;

    REG_WAITCNT = 0x4014;
    ResetMemory();
    InitInterrupts();
    REG_DISPCNT = 0x60;
    gMainState = 3;
    gUnknown_03002B8C = 0;
    gUnknown_0300137C = 0;
    sub_080020C8();
    InitAudio((void *)0x03002430);
    gUnknown_03001784 = 0;
    gUnknown_03005030 = 0;
    gUnknown_03002410 = 0;
    gMainSerialWork.disappeared = 0;
    gMainSerialWork.appeared = 0;

    for (;;)
    {
        s32 previousBits;
        s32 result;

        VBlankIntrWait();
        gUnknown_03002410 = 0;
        ReadKeys();
        gFrameCounter++;

        if (gUnknown_03000588 != 0 && gUnknown_03002B70.counter18 <= 0x014996FE)
            gUnknown_03002B70.counter18++;

        previousBits = gSerialState.rememberedBits;
        gMainSerialWork.appeared = 0;
        gMainSerialWork.disappeared = 0;
        gMainSerialWork.polledBits = sub_080021F4(gMainSerialWork.words);

        for (i = 0; i < 4; i++)
        {
            if (gMainSerialWork.polledBits & (1 << i))
            {
                gMainSerialWork.missingPolls[i] = 0;
                if (((previousBits >> i) & 1) == 0)
                {
                    gSerialState.rememberedBits |= 1 << i;
                    gMainSerialWork.appeared |= 0xFF;
                }
            }
            else
            {
                if ((s8)gMainSerialWork.missingPolls[i] > 10)
                {
                    if ((gSerialState.rememberedBits >> i) & 1)
                        gMainSerialWork.disappeared |= 0xFF;
                    gSerialState.rememberedBits &= ~(1 << i);
                    gMainSerialWork.missingPolls[i] = 0;
                }
                else
                {
                    gMainSerialWork.missingPolls[i]++;
                }
            }
        }

        result = sub_08000964();
        if (result != 0)
        {
            VBlankIntrWait();
            InitAudio((void *)0x03002430);
            VBlankIntrWait();
        }
        else if (gUnknown_03005030 != 0)
        {
            s32 index = 0;
            if (gUnknown_03000B90 == 0)
                index = 1;

            if (gMainSerialWork.words[index][0] == 0xFFFF
                && gMainSerialWork.words[index][1] == 0xFFFF)
            {
                gMainState = 0;
                gUnknown_03002B8C = 10;
                gUnknown_0300137C = 16;
            }
        }

        gMainCallbacks[gMainState]();
        sub_08001520();
        sub_080022DC(gMainSerialWork.unknown04);
    }
}
