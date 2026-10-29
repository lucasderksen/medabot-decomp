/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"

extern void sub_0807495C(void *);

void sub_08072818(u8 *work);

void sub_08072818(u8 *work) {

    s32 remaining;
    s16 *p44 = (s16 *)(work + 0x44);
    u16 *p40;
    int zero;
    u16 *p42;
    u32 resetPosition;

    if (*p44 != 0) {
        remaining = *(s32 *)(work + 0x3C);
        p40 = (u16 *)(work + 0x40);
        if (remaining != 0) {
            remaining -= 1;
            *(s32 *)(work + 0x3C) = remaining;
        }
        if (remaining != 0) {
            *p40 = *p40 + (u16) *p44;
            if (*(u16 *)(work + 0x4A) != (((work + 0x4A)[0x1C] * *p40) & 0xF000)) {
                work[0x50] = 2 | work[0x50];
            }
        } else {
            p42 = (u16 *)(work + 0x42);
            resetPosition = *p42;
            zero = 0;
            *p40 = resetPosition;
            *p44 = zero;
            sub_0807495C(work);
        }
    }
}
