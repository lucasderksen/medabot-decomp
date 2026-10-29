/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "continued_late_graphics.h"
#include "display_effects.h"
#include "frame.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern const u8 gUnknown_08485764[3][3];
extern const u8 gUnknown_08485783[][7];
extern s32 gUnknown_03006FE0[3];
extern u8 gUnknown_03006F84;
extern u8 gUnknown_03006F8C[3];
extern u8 gUnknown_03006FD0[3][3];

void sub_08067870(void);
void sub_0806AA10(void);

void sub_08067870(void) {

    sub_08066D8C();
    if (gState0TypedWork.bytes[0x84] < 0x41) {
        sub_0803F684(0, 0x20 - gState0TypedWork.bytes[0x84] / 2, 0xFFFF);
        sub_0803F998(0, 0x20 - gState0TypedWork.bytes[0x84] / 2, 0xFFFF);
        gState0TypedWork.bytes[0x84]++;
        ((u8 *)gMainContextPointer_03006F74)[5] = 0;
    } else {
        gUnknown_0300137C++;
    }
}

void sub_0806AA10(void) {

    s32 i;

    for (i = 0; i < 3; i++) {
        u8 *state = &gUnknown_03006F8C[i];
        if (*state <= 2) {
            if (gUnknown_08485783[gUnknown_03006F84][gUnknown_03006FD0[i][*state]] <= ++gUnknown_03006FE0[i]) {
                gFrameObjects[gUnknown_08485764[i][*state]].unknown1A++;
                gUnknown_03006FE0[i] = 0;
            }
        }
    }
}
