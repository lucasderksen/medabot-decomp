#include "global.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "object_helpers.h"
#include "frame_objects.h"
#include "graphics.h"
#include "display_effects.h"
#include "effect_work.h"
#include "audio.h"
#include "serial.h"
#include "main_callbacks.h"

/* Partial access view only; backing extent/original declaration is unknown. */
struct Main2ReturnWork
{
    u8 unknown00[0x2A];
    u8 byte2A;
    u8 unknown2B[0x59];
    u8 phase;
};
#define WORK ((struct Main2ReturnWork *)gUnknown_03000440)
#define CONTEXT_HALFWORDS ((u16 *)gMainContextPointer_03006F74)
#define MAIN_FLAGS_BYTE (*(u8 *)&gMainFlagsWord_03001784)
#define DISPCNT (*(volatile u16 *)0x04000000)

s32 sub_0805DDEC(s32 mode)
{
    s32 result = 0;
    u32 zero = result;
    u8 *buffer = (u8 *)0x02030000;
    u16 savedIe;
    CpuSet(&zero, buffer, 0x0500072E);
    REG_IME = 0;
    savedIe = REG_IE;
    REG_IE = 0x2020;
    REG_IME = 1;
    switch (mode)
    {
    case 0:
        MAIN_FLAGS_BYTE |= 1;
        sub_0805E010(buffer);
        result = sub_0805E248((void *)0x02030000, 0);
        break;
    case 1:
        result = sub_0805E138(buffer);
        sub_0805DF18(buffer);
        break;
    case 2:
        {
            u32 flags = MAIN_FLAGS_BYTE;
            s32 mask = -2;
            mask &= flags;
            MAIN_FLAGS_BYTE = mask;
        }
        {
            s32 index = 0;
            u32 destination = (u32)buffer;
            for (; index <= 15; index++)
                *(u8 *)(index + destination) = gMain2SaveSignature_084836C5[index];
        }
        result = sub_0805E248((void *)0x02030000, 0);
        break;
    }
    REG_IE = savedIe | REG_IE;
    return result;
}
