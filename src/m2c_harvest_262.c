/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_float_progress.h"

struct Work72D68 {u8 pad0[0x14];u8 *script;u8 pad18[0xC];s32 word24,word28,word2C;u8 pad30[0x20];u8 flags50;u8 pad51[0x12];u8 byte63,byte64;};

extern void sub_08072910(void *, u8);
extern void sub_08072AC0(void *);
extern void sub_08072AFC(void *, s32);
extern void sub_08072B18(void *, u8);
extern void sub_08072B20(void *, u32);
extern void sub_08072B34(void *);
extern void sub_08072B50(void *, s32);
extern void sub_08072B64(void *);
extern void sub_08072B74(void *);
extern void sub_08072B90(void *);
extern void sub_08072BAC(void *);
extern void sub_08072BB8(void *);
extern void sub_08072BCC(void *);
extern void sub_08072BE4(void *);
extern void sub_08072BF8(void *);
extern void sub_08072C10(void *);
extern void sub_08072C20(void *);
extern void sub_08072C34(void *);
extern void sub_08072C3C(void *);
extern void sub_08072C64(void *);
extern void sub_08072C74(void *);
extern void sub_08072CA0(void *);
extern void sub_08072CB0(void *);
extern void sub_08072D04(void *);
extern void sub_08072D28(void *);
extern void sub_08072D4C(void *);
extern void sub_08072D5C(void *);

void sub_08072D68(void *arg0);

void sub_08072D68(void *arg0) {

    s32 temp_r0_5;
    u32 temp_r0_2;
    u8 *temp_r0;
    u8 *temp_r0_3;
    u8 *temp_r0_4;
    u8 temp_r2;
    u8 parameter;

    temp_r0 = ((struct Work72D68 *)arg0)->script;
    if (temp_r0 == 0) {
        return;
    }
    temp_r2 = *temp_r0;
    ((struct Work72D68 *)arg0)->script = (u8 *) (temp_r0 + 1);
    temp_r0_2 = temp_r2;
    switch (temp_r0_2) {                            /* switch 1; irregular */
    case 0xE0:
        goto applyNoArg;
    case 0xE1:                                         /* switch 1 */
        temp_r0_3 = ((struct Work72D68 *)arg0)->script;
        parameter = *temp_r0_3;
        ((struct Work72D68 *)arg0)->script = (u8 *) (temp_r0_3 + 1);
        sub_08072B18(arg0, parameter);
        return;
    case 0xE2:                                         /* switch 1 */
        temp_r0_4 = ((struct Work72D68 *)arg0)->script;
        parameter = *temp_r0_4;
        ((struct Work72D68 *)arg0)->script = (u8 *) (temp_r0_4 + 1);
        sub_08072B20(arg0, parameter);
        return;
    case 0xE3:                                         /* switch 1 */
        sub_08072B34(arg0);
        return;
    case 0xE4:                                         /* switch 1 */
        sub_08072B50(arg0, 0);
        return;
    case 0xE5:                                         /* switch 1 */
        sub_08072B50(arg0, 0x40);
        return;
    case 0xE6:                                         /* switch 1 */
        sub_08072B50(arg0, 0x80);
        return;
    case 0xE7:                                         /* switch 1 */
        sub_08072B50(arg0, 0xC0);
        return;
    case 0xE8:                                         /* switch 1 */
        sub_08072B64(arg0);
        return;
    case 0xE9:                                         /* switch 1 */
        sub_08072B74(arg0);
        return;
    case 0xEA:                                        /* switch 1 */
        sub_08072B90(arg0);
        return;
    case 0xEB:                                        /* switch 1 */
        sub_08072BAC(arg0);
        return;
    case 0xF0:                                        /* switch 1 */
        sub_08072BB8(arg0);
        return;
    case 0xF1:                                        /* switch 1 */
        sub_08072BCC(arg0);
        return;
    case 0xF2:                                        /* switch 1 */
        sub_08072BE4(arg0);
        return;
    case 0xF3:                                        /* switch 1 */
        sub_08072BF8(arg0);
        return;
    case 0xF4:                                        /* switch 1 */
        sub_08072C10(arg0);
        return;
    case 0xF5:                                        /* switch 1 */
        sub_08072C20(arg0);
        return;
    case 0xF6:                                        /* switch 1 */
        sub_08072C34(arg0);
        return;
    case 0xF7:                                        /* switch 1 */
        sub_08072C3C(arg0);
        return;
    case 0xF8:                                        /* switch 1 */
        sub_08072C64(arg0);
        return;
    case 0xF9:                                        /* switch 1 */
        sub_08072C74(arg0);
        return;
    case 0xFA:                                        /* switch 1 */
        sub_08072CA0(arg0);
        return;
    case 0xFB:                                        /* switch 1 */
        sub_08072CB0(arg0);
        return;
    case 0xFC:                                        /* switch 1 */
        sub_08072D04(arg0);
        return;
    case 0xFD:                                        /* switch 1 */
        sub_08072D28(arg0);
        return;
    case 0xFE:                                        /* switch 1 */
        sub_08072D4C(arg0);
        return;
    case 0xFF:                                        /* switch 1 */
        sub_08072D5C(arg0);
        return;
    default:                                        /* switch 1 */
        temp_r0_5 = 0xF0 & temp_r2;
        switch (temp_r0_5) {                        /* switch 2; irregular */
        case 0x80:
applyNoArg:                                  /* switch 2 */
            sub_08072AC0(arg0);
            return;
        case 0xD0:                                  /* switch 2 */
            sub_08072AFC(arg0, temp_r2 & 0xF);
            if ((((struct Work72D68 *)arg0)->byte63 == 1) && (((struct Work72D68 *)arg0)->byte64 == 3) && (((struct Work72D68 *)arg0)->word24 == 0)) {
                ((struct Work72D68 *)arg0)->word28 = (s32) ((struct Work72D68 *)arg0)->word2C;
                ((struct Work72D68 *)arg0)->flags50 |= 0x50;
                return;
            }
        case 0xA0:                                  /* switch 2 */
        case 0xC0:                                  /* switch 2 */
        case 0xB0:                                  /* switch 2 */
        case 0x90:                                  /* switch 2 */
            return;
        default:                                    /* switch 2 */
            sub_08072910(arg0, temp_r2);
            break;
        }
        break;
    }
}
