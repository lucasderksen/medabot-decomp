/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "frame_objects.h"
#include "gba.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"

extern void sub_08062A10(u32);
extern void sub_08062B48(u8, u8, u32);
extern void sub_08062C98(void);

void sub_08063474(void);

void sub_08063474(void) {

    u16 hiddenOamAttribute;
    u16 *fill;
    struct LinkSwapContext *ctx;
    u32 zero;
    s32 remaining;
    u16 elapsed;

    ctx = gMainContextPointer_03006F74;
    elapsed = (*(u16 *)((u8 *)ctx + 0x3C));
    (*(u16 *)((u8 *)ctx + 0x3C)) = (u16) (elapsed + 1);
    remaining = 0x10 - (s16) elapsed;
    if (remaining != 0) {
        (*(volatile u16 *)((u8 *)((void *)0x04000050) + 0)) = 0xE50;
        (*(volatile u16 *)((u8 *)((void *)0x04000050) + 2)) = (s16) (((u32)(0x10 - remaining) << 8) | remaining);
        (*(volatile u16 *)((u8 *)((void *)0x04000050) + 4)) = 8;
        sub_08062B48(ctx->firstX, ctx->firstY, 0);
        sub_08062B48(((struct LinkSwapContext *)gMainContextPointer_03006F74)->secondX, ((struct LinkSwapContext *)gMainContextPointer_03006F74)->secondY, 1);
        if (remaining == 1) {
            sub_08040CD0(0U, 0x80U);
        }
    } else {
        remaining = ctx->firstX;
        {
            u32 next = ctx->secondX;
            zero = 0;
            ctx->firstX = next;
        }
        ((struct LinkSwapContext *)gMainContextPointer_03006F74)->secondX = remaining;
        remaining = ((struct LinkSwapContext *)gMainContextPointer_03006F74)->firstY;
        ((struct LinkSwapContext *)gMainContextPointer_03006F74)->firstY = (u8) ((struct LinkSwapContext *)gMainContextPointer_03006F74)->secondY;
        ((struct LinkSwapContext *)gMainContextPointer_03006F74)->secondY = remaining;
        sub_08062A10(zero);
        sub_08062A10(1);
        ((struct LinkSwapContext *)gMainContextPointer_03006F74)->timer = zero;
        gUnknown_0300137C += 1;
        fill = &hiddenOamAttribute;
        *fill = 0x200;
        CpuSet(fill, gRenderWork->objects, 0x01000200U);
    }
    sub_08062C98();
}
