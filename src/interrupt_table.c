#include "gba.h"
#include "audio.h"

extern void sub_08002438(void);
extern void VBlankHandler(void);
extern void HBlankHandler(void);
extern void DummyInterruptHandler(void);

/* 0x0807E860: dispatcher slots use a custom priority order, rather than
 * increasing GBA interrupt bit order. All fourteen pointers are copied at boot.
 */
const IntrFunc gDefaultIntrTable[14] =
{
    sub_08002438,
    VBlankHandler,
    DummyInterruptHandler,
    HBlankHandler,
    DummyInterruptHandler,
    Dma1AudioHandler,
    Dma2AudioHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};
