/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"

extern u32 sub_0807CEC8(u32,u32);
extern void sub_08073AB8(u32, void *);
extern void sub_08073B2C(s32);
extern void sub_08073CDC(void *);
extern void sub_08073DF4(void *);
extern void sub_08074024(void *);
extern volatile u32 *const gUnknown_08486E5C[];

void sub_08074118(void *arg0);

void sub_08074118(void *arg0) {

    s32 temp_r1_2;
 u32 denominator;
    u16 temp_r5;
    void *temp_r1;
    void *temp_r2;

    if ((*(void **)((u8 *)(arg0) + 0)) == 0) {
        (*(s32 *)((u8 *)(arg0) + 0x44)) = (s32) ((u32)(*(s32 *)((u8 *)(arg0) + 0x44)) + 1U);
        return;
    }
    temp_r5 = (*(s32 *)((u8 *)(arg0) + 0xC)) & 1;
    if (temp_r5 == 0) {
        sub_08074024(arg0);
        (*(u32 *)((u8 *)(arg0) + 8)) = (u32) ((*(u32 *)((u8 *)(arg0) + 8)) + 0x10);
        if ((*(u16 *)((u8 *)(arg0) + 0x38)) != 0) {
 (*(u16 *)((u8 *)(arg0) + 0x36))+=(*(u16 *)((u8 *)(arg0) + 0x38));
            (*(u16 *)((u8 *)(arg0) + 0x38)) = temp_r5;
        }
        temp_r2 = (*(void **)((u8 *)(arg0) + 0));
        if ((u32) (*(u32 *)((u8 *)(temp_r2) + 0)) <= (u32) (*(u32 *)((u8 *)(arg0) + 8))) {
            if ((*(s32 *)((u8 *)(temp_r2) + 8)) & 1) {
                sub_08073B2C((*(u8 *)((u8 *)(arg0) + 0x3A)));
                temp_r1 = (*(void **)((u8 *)(arg0) + 0));
                (*(u32 *)((u8 *)(arg0) + 8)) = (u32) (*(u32 *)((u8 *)(temp_r1) + 0xC));
                sub_08073AB8((*(u8 *)((u8 *)(arg0) + 0x3A)), temp_r1 + ((*(u32 *)((u8 *)(temp_r1) + 0xC)) + 0x10));
                goto block_8;
            }
            goto block_9;
        }
block_8:
        if ((u32) (*(u16 *)((u8 *)(arg0) + 0x34)) <= (u32) (*(u16 *)((u8 *)(arg0) + 0x36))) {
block_9:
            sub_08073DF4(arg0);
            return;
        }
        if ((*(s32 *)((u8 *)(arg0) + 0xC)) & 2) {
            denominator = (u32)(*(s32 *)((u8 *)(arg0) + 4))+(u32)(*(s32 *)((u8 *)(arg0) + 0x14));
 temp_r1_2 = (0x10000 - sub_0807CEC8(0x01000000, denominator)) | 0x800000;
            (*(s32 *)((u8 *)(arg0) + 0x10)) = temp_r1_2;
            *gUnknown_08486E5C[(u32)(*(u8 *)((u8 *)(arg0) + 0x3A))-1U] = temp_r1_2;
            (*(s32 *)((u8 *)(arg0) + 0xC)) = (s32) ((*(s32 *)((u8 *)(arg0) + 0xC)) & ~2);
        }
        if ((*(s32 *)((u8 *)(arg0) + 0xC)) & 4) {
            sub_08073CDC(arg0);
            (*(s32 *)((u8 *)(arg0) + 0xC)) = (s32) ((*(s32 *)((u8 *)(arg0) + 0xC)) & ~4);
        }
    }
}
