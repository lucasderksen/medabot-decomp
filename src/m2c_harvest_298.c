/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "effect_work.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"

struct E4 { u8 count; u8 b[3]; };

extern struct E4 gUnknown_083AD502[];
extern u8 gUnknown_084850E3;

u32 sub_08016438(u32 value);
void sub_080665FC(void);

u32 sub_08016438(u32 value) {

    s32 var_r5;
    struct FrameObject *var_r3;
    struct FrameObject *objs;
    u32 var_ip;
    u32 var_r6;
    u8 *var_r2;
    u8 temp_r0;
    u8 temp_r0_2;
    u8 temp_r0_3;
    u8 temp_r1;
    u8 temp_r1_2;
    u8 temp_r7;

    var_ip = 1;
    temp_r7 = gUnknown_083AD502[value].count;
    var_r6 = 0;
    if (var_r6 < (u32) temp_r7) {
        objs = gFrameObjects;
        var_r3 = objs + 0x3C;
        var_r2 = &objs[0x3C].commandOffset;
        do {
            if ((*(u8 *)((u8 *)(var_r2) + 3)) != 0) {
                var_r5 = 0x12;
            } else {
                var_r5 = 0x16;
            }
            (*(u8 *)((u8 *)(var_r2) + 0)) = (*(u8 *)((u8 *)(var_r2) + 0)) + 1;
            if (!((*(u8 *)((u8 *)(var_r2) + 0)) & 3)) {
                temp_r0 = ((*(u8 *)((u8 *)(var_r2) + 1)) + 1) & 3;
                (*(u8 *)((u8 *)(var_r2) + 1)) = temp_r0;
                var_r3->frameAndGroup = var_r5 + (temp_r0 | 0x600);
            }
            if ((*(u8 *)((u8 *)(var_r2) + 5)) != (*(u8 *)((u8 *)(var_r2) + 3))) {
                var_ip = 0;
                temp_r0_2 = (*(u8 *)((u8 *)(var_r2) + 6));
                if (temp_r0_2 != 0) {
                    (*(u8 *)((u8 *)(var_r2) + 6)) = (u8) (temp_r0_2 - 1);
                } else {
                    if ((*(u8 *)((u8 *)(var_r2) + 3)) == 0) {
                        if ((*(u8 *)((u8 *)(var_r2) + 4)) != 0) {
                            var_r3->screenX = (u16) var_r3->screenX + 4;
                        } else {
                            var_r3->screenX = (u16) var_r3->screenX - 4;
                        }
                    } else {
                        var_r3->screenY = (u16) var_r3->screenY + 4;
                    }
                    (*(u8 *)((u8 *)(var_r2) + 7)) = (*(u8 *)((u8 *)(var_r2) + 7)) + 1;
                    if (!((*(u8 *)((u8 *)(var_r2) + 7)) & 1)) {
                        (*(u8 *)((u8 *)(var_r2) + 3)) = (u8) ((*(u8 *)((u8 *)(var_r2) + 3)) + 1);
                    }
                }
            }
            var_r3++;
            var_r2 += 0x40;
            var_r6 += 1;
        } while (var_r6 < (u32) temp_r7);
    }
    return var_ip;
}

void sub_080665FC(void) {

    u8 *c;
    u8 *p;
    u8 *src;
    u8 *rec;

    c = (u8 *)gMainContextPointer_03006F74;
    p = c + 0x270;
    *p = 0xFB;
    p = c + 0x271;
    *p = 1;
    p = c + 0x272;
    *p = 0xC;
    p = c + 0x273;
    *p = 0;
    p = c + 0x274;
    src = &gUnknown_084850E3;
    while ((*p = *src) != 0xFF) {
        p++;
        src++;
    }
    *p = 0xFFU;
    p[1] = 4;
    p = (u8 *)gMainContextPointer_03006F74 + 0x270;
    if (sub_0803FB3C(p) != 0) {
        sub_0803FB0C();
        sub_080415E8(1U, 0x16U, 7U);
        gUnknown_0300137C += 1;
    }
}
