/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "post_dispatch.h"
#include "record_helpers.h"
#include "render_work.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "utility_helpers.h"

struct BackgroundWork692EC {u8 pad0[0x39];u8 mode;};
struct Dma72188 {u32 source,destination,control;};
struct RenderPhase72188 {u8 pad0[0x10];u8 phase;};

extern struct BackgroundWork692EC gBackgroundWork692EC;
extern struct RenderPhase72188 gRenderPhase72188;
extern u8 gUnknown_03006F94;
extern void sub_08069320(void);
extern void sub_0806B718(u8);

void sub_080692EC(void);
s32 sub_08072188(void);

void sub_080692EC(void) {

    u32 var_r1,key;
    struct BackgroundWork692EC *work;

    sub_08069320();
    sub_08074B88(0U);
    work=&gBackgroundWork692EC;
    key=gUnknown_03006F94;
    var_r1 = 2;
    if (key == 1) {
        var_r1 = 1;
    }
    work->mode = var_r1;
    sub_08047850(0);
}

s32 sub_08072188(void) {

    u32 sp20;
    volatile struct Dma72188 *dma;

    if (4 & gFrameObjects[1].unknown1A) {
        gFrameObjects[1].screenY=0xC8;
    } else {
        gFrameObjects[1].screenY=0x42;
    }
    if (gFrameObjects[1].unknown1A++ > 0x1F) {
        sub_0806B718(1);
        sub_080445F4();
        sp20 = 0x200;
        dma=(volatile struct Dma72188 *)0x040000D4;
        dma->source=(u32)&sp20;
        dma->destination=(u32)gRenderWork->objects;
        dma->control=0x85000100;
        (void)dma->control;
        sub_080446B4(0U, 0x2BU, 0x2BU, 0x2BU, 0x2BU, 0x40U, 0x42U, 2U, 8U, 0U, 0U, 0U);
        gRenderPhase72188.phase = (u8) (gRenderPhase72188.phase + 1);
    }
    return 0;
}
