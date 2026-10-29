#include "global.h"
#include "frame.h"
#include "later_graphics.h"
#include "continued_commands.h"
#include "packed_fields.h"

extern s32 __divsi3(s32 numerator, s32 denominator);

union NibbleView { u32 value; struct { u32 low:4; u32 high:4; u32 unused:24; } fields; };

void sub_080500BC(u32 inputIndex, u32 inputValue, u32 inputMode)
{
    u8 index = inputIndex;
    union NibbleView nibbles = {(u8)inputValue};
    u8 value;
    u8 mode = inputMode;
    u8 *objects = (u8 *)gFrameObjects;
    struct FrameObject *object = (void *)(index * 64 + objects);
    { u32 low = 15; low &= nibbles.value; object->unknown23[4] = low; }
    value = nibbles.fields.high;
    sub_08052D90(index, value);
    object->unknown23[7] = mode;
    object->unknown23[5] = __divsi3(16, sub_08051940(index));
    sub_08049420(index, (u8)sub_08050300(index, value));
}

void sub_08050124(u32 inputIndex, u32 inputValue, u32 mode)
{
    u8 index = inputIndex;
    union NibbleView nibbles = {(u8)inputValue};
    u8 value;
    u8 *objects = (u8 *)gFrameObjects;
    struct FrameObject *object = (void *)(index * 64 + objects);
    { u32 low = 15; low &= nibbles.value; object->unknown23[4] = low; }
    object->commandDelay = nibbles.fields.high;
    object->unknown23[7] = mode;
    object->unknown23[5] = __divsi3(16, sub_08051940(index));
}

