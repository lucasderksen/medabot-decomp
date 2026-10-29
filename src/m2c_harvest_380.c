/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "continued_numeric.h"

extern s32 sub_0807CD2C(s32, s32);

u8 sub_080669AC(u32 target, u32 current, u32 divisor) {
    u8 targetByte, currentByte;
    u32 targetWord, currentWord;
    s32 step;
    u8 divisorByte;
    u32 output;

    targetByte = target;
    targetWord = targetByte;
    currentByte = current;
    currentWord = currentByte;
    divisorByte = divisor;
    step = sub_0807CD2C((s32)targetByte - currentByte, divisorByte);
    if (step != 0) {
        output = currentByte + step;
        goto finish;
    }
    if (targetByte == currentByte)
        return currentByte;
    if (targetWord > currentByte)
        output = currentByte + 1;
    else
        output = currentWord - 1;
finish:
    return output;
}
