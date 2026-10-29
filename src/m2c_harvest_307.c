/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "frame.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct CV { u8 p0[0x60]; u8 b60; u8 p61[0xAA - 0x61]; u8 bAA; u8 pAB[0xD2 - 0xAB]; u8 bD2[4]; u8 bD6[6]; };

extern struct CV gCounter6ED08_03001800;
extern u8 gUnknown_03001800[];
extern u8 gUnknown_084D819C;

void sub_08027494(void);
void sub_0802A5C0(void);

void sub_08027494(void) {

    s32 temp_r2;
    u32 temp_r1_3;
    u32 var_r5;
    u8 *temp_r1_2;
    u8 *temp_r4;
    u8 *new_var2;
    u32 new_var;
    u8 *temp_r1;
    u32 tmp;
    u8 *p59;

    var_r5 = 0;
    do {
        new_var = (u32) gSetupBuffer_03000590;
        temp_r2 = (gCounter6ED08_03001800.b60 + var_r5) << 8;
        temp_r1 = (u8 *) (temp_r2 + new_var);
        if ((temp_r1[0x40] != 0) && (temp_r1[0x59] != 0)) {
            temp_r4 = &gCounter6ED08_03001800.bD2[var_r5];
            temp_r1_2 = &gSetupBuffer_03000590[((0x7F & (*temp_r4)) * 0x18) + temp_r2];
            p59 = &temp_r1_2[0x59];
            tmp = gCounter6ED08_03001800.bD6[var_r5 * 2];
            *p59 = (u8) (*p59 - tmp);
            sub_08035194(gCounter6ED08_03001800.b60 + var_r5);
            if (!(0x7F & (*temp_r4))) {
                temp_r1_3 = gCounter6ED08_03001800.b60 + var_r5;
                new_var2 = gSetupBuffer_03000590;
                if (new_var2[(temp_r1_3 << 8) + 0x59] == 0) {
                    sub_08035234(temp_r1_3);
                }
            }
        }
        var_r5 += 1;
    } while (var_r5 <= 2U);
    gCounter6ED08_03001800.bAA = (u8) (gCounter6ED08_03001800.bAA + 1);
}

void sub_0802A5C0(void) {

    u32 i;
    u8 *temp_r0;
    u8 *g;
    u8 *q;
    u8 *r;
    u8 *b;
    LeDecompress(&gUnknown_084D819C, (void *)0x06017E00);
    i = 0;
    g = gUnknown_03001800;
    b = gDebugMenuTextBuffer;
    temp_r0 = b + 0x14;
    do {
        q = g + 0xD2;
        if (*(u8 *)(i + (u32)q) != 0) {
            switch (i) {
            case 0:
                sub_0801A28C(b, *(u16 *)((i << 1) + (u32)(r = g + 0xD6)), 0U);
                sub_0801A418(b, g[0x60] + i, 0x21);
                break;
            case 1:
                sub_0801A28C(temp_r0, *(u16 *)(g + 0xD8), 0U);
                sub_0801A418(temp_r0, g[0x60] + 1, 0x21);
                break;
            case 2:
                sub_0801A28C((b + 0x28), *(u16 *)(g + 0xDA), 0U);
                sub_0801A418((b + 0x28), g[0x60] + 2, 0x21);
                break;
            }
        }
        i += 1;
    } while (i <= 2U);
    sub_08074DE0(0x5BU);
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_03001800[0xAA] += 1;
}
