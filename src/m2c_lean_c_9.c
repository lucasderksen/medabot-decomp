/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "battle_work.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "frame_command_handlers.h"
#include "input.h"
#include "main.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct MenuContext61338 {
    u8 pad00[2];
    s16 value02;
    u8 pad04;
    u8 cursor05;
    s8 flag06;
};

extern struct MenuContext61338 *gMenuContext61338 asm("gMainContextPointer_03006F74");
extern u8 gFamilyKeyBytes49558_0300058C;
extern void sub_08060BE4(u32, u32);

void sub_08061338(void);
s32 sub_0806B248(u32 index);

void sub_08061338(void) {

    sub_08041C14(8, gFrameCounter, 8);
    if (0x40 & (u8)gRepeatedKeys) {
        sub_08074DE0(2);
        if (gMenuContext61338->cursor05 != 0)
            gMenuContext61338->cursor05--;
        else
            gMenuContext61338->cursor05 = 2;
    }
    if (0x80 & (u8)gRepeatedKeys) {
        sub_08074DE0(2);
        if (gMenuContext61338->cursor05 < 2)
            gMenuContext61338->cursor05++;
        else
            gMenuContext61338->cursor05 = 0;
    }
    gFrameObjects[8].screenY = gMenuContext61338->cursor05 * 24 + 0x20;
    if (1 & gFamilyKeyBytes49558_0300058C) {
        sub_08074DE0(4);
        switch (gMenuContext61338->cursor05) {
        case 0:
            gMenuContext61338->value02 = 0;
            gUnknown_0300137C = 8;
            gMenuContext61338->flag06 = 0;
            sub_08060BE4(0, 0);
            break;
        case 1:
            gMenuContext61338->value02 = 0;
            gUnknown_0300137C = 8;
            gMenuContext61338->flag06 = 0;
            sub_08060BE4(0, 0);
            break;
        case 2:
        cancel:
            gState0TypedWork.bytes[0x84] = 0;
            gUnknown_0300137C = 6;
            break;
        }
    } else if (2 & gFamilyKeyBytes49558_0300058C) {
        sub_08074DE0(5);
        goto cancel;
    }
}

s32 sub_0806B248(u32 index) {

    u8 i = index;
    struct FrameObject *obj;

    if (gFrameObjects[i].unknown1A < 0x10)
        *(volatile s16 *)0x04000052 = 0x1000 | gFrameObjects[i].unknown1A;
    else if (gFrameObjects[i].unknown1A < 0x20)
        *(volatile s16 *)0x04000052 = ((0x20 - gFrameObjects[i].unknown1A) << 8) | 0x10;
    obj = &gFrameObjects[i];
    if (1 & obj->unknown1A)
        obj->screenY--;
    if (obj->unknown1A > 0x3F) {
        *(volatile s16 *)0x04000050 = 0;
        return 0;
    }
    return 1;
}
