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

void sub_0805DD88(void)
{
    gMainFlag_03005030 = 0;
    sub_080021A4();
    VBlankIntrWait();
    *(volatile u16 *)0x04000050 = 0xFF;
    *(volatile u16 *)0x04000054 = 16;
    *(volatile u16 *)0x04000084 = 0;
    gMainState = 3;
    gMainSubstate = 0;
    gUnknown_0300137C = 0;
    *(volatile u16 *)0x040000BA = 0;
    VBlankIntrWait();
    InitAudio((void *)0x03002430);
    VBlankIntrWait();
}
