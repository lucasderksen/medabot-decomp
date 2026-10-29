#include "state0_work.h"
#include "banked_commands.h"
#include "continued_map_data.h"
#include "continued_commands.h"
#include "continued_callbacks.h"
#include "continued_graphics.h"
#include "continued_map.h"
#include "gba.h"
#include "frame.h"
#include "initialization.h"
#include "later_graphics.h"
#include "object_numeric_helpers.h"
#include "background_state.h"
#include "fresh_helpers.h"
#include "equipment_helpers.h"
#include "blend_setup_helpers.h"

struct SetupDma { u32 source, destination, control; };
/* Partial view: byte38 is observed at 03005348; total work size is unknown. */
struct SetupBackgroundView { u8 bytes[0x38]; u8 byte38; };
extern u8 gUnknown_03000440[];
extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_030055A0[];
extern u8 gLaterBuffer_03006D20[];
extern const void *gSetupPointer_03005590;
extern void *gSetupPointer_030057DC;

void sub_0804A764(void)
{
    u32 fill;
    u32 zero;
    u32 control;
    volatile struct SetupDma *dma;
    u8 *work;
    struct SetupBackgroundView *settings;
    ResetSpritesAndVram();
    sub_08049714(gFrameObjects, 8192);
    sub_08049714(gLaterBuffer_030055A0, 512);
    zero = 0;
    fill = zero;
    dma = (volatile struct SetupDma *)0x040000D4;
    dma->source = (u32)&fill;
    dma->destination = 0x07000000;
    control = 0x85000100;
    dma->control = control;
    dma->control;
    sub_08049714(gUnknown_03000440, 316);
    sub_08049714(gSetupBuffer_03000590, 1536);
    work = gUnknown_030057E0;
    work[0xC88] = zero;
    work[0xC89] = zero;
    work[0xC93] = zero;
    *(u16 *)(work + 0xC8A) = zero;
    *(u16 *)(work + 0xC8E) = zero;
    work[0xC5F] = 0;
    work[0xC60] = 0;
    settings = (struct SetupBackgroundView *)&gBackgroundState_03005310;
    settings->byte38 = 0;
    sub_08049714(gLaterBuffer_03006D20, 16);
    sub_0804B248();
    settings->bytes[1] = 0;
    sub_080506BC();
    gSetupPointer_03005590 = gSetupData_08765EC0;
    gSetupPointer_030057D8 = work;
    gSetupPointer_03006D30 = (void *)0x02039000;
    gSetupPointer_03006D14 = (void *)0x02030000;
    gSetupPointer_030057DC = (void *)0x02038000;
    sub_08049714(gFrameObjects, 8192);
    sub_08049714(gLaterBuffer_030055A0, 512);
    fill = zero;
    dma->source = (u32)&fill;
    dma->destination = 0x07000000;
    dma->control = control;
    dma->control;
    *(volatile u16 *)0x04000050 = zero;
    *(volatile u16 *)0x04000054 = zero;
    *(volatile u16 *)0x04000000 = 0x1E40;
    work[0xCBA] = 2;
    sub_080480E4();
    sub_0804387C();
    sub_0804842C(28, 0);
    sub_08052AA4();
    sub_08048830();
    sub_08049D18(32767, 32.0f, 0.0f, 8.0f);
    sub_0804A210();
}
