/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "continued_late_graphics.h"
#include "effect_work.h"
#include "frame.h"
#include "main_callbacks.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ScriptContext66714 {
    u8 pad000[5];
    u8 cursor05;
    u8 pad006[0x44];
    s8 flag4A;
    u8 pad04B[5];
    u8 block50[0x220];
    u8 script270[4];
    u8 text274[0x40];
};

extern struct ScriptContext66714 *gScriptContext66714 asm("gMainContextPointer_03006F74");

void sub_08066714(void);

void sub_08066714(void) {

    const u8 *src;
    u8 *dst;
    s32 i;
    u16 w0;
    u16 w1;
    struct ScriptContext66714 *ctx;

    src = gMain2ScriptSlots_08485678[15];
    ctx = gScriptContext66714;
    dst = &ctx->script270[0];
    *dst = 0xFB;
    dst = &ctx->script270[1];
    *dst = 0;
    dst = &ctx->script270[2];
    *dst = 0xC;
    dst = &ctx->script270[3];
    *dst = 0;
    dst = ctx->text274;
    i = 0;
    do {
        dst[i] = src[i];
        i++;
    } while (dst[i] != 0xFF);
    dst[i] = src[i];
    i++;
    dst[i] = src[i];
    if (sub_0803FB3C(gScriptContext66714->script270) != 0) {
        if (gState0TypedWork.bytes[0x2A] == 0)
            gMainSerialOutgoingWork.word06 = 0xFF00;
        else
            gMainSerialOutgoingWork.word06 = 0xFF01;
        w0 = gMainSerialOutgoingWork.words[0][1];
        w1 = gMainSerialOutgoingWork.words[1][1];
        if ((w0 & 0xFF00) == 0xFF00 && (w1 & 0xFF00) == 0xFF00) {
            sub_0803FB0C();
            if (w0 == w1) {
                sub_080656DC(gScriptContext66714->block50, 0, 0, 1, 0xC0);
                gUnknown_0300137C = 5;
                gScriptContext66714->flag4A = w0 != 0xFF00;
                return;
            }
            gUnknown_0300137C = 3;
            gScriptContext66714->cursor05 = 6;
        }
    }
}
