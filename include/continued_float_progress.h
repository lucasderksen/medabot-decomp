#ifndef GUARD_CONTINUED_FLOAT_PROGRESS_H
#define GUARD_CONTINUED_FLOAT_PROGRESS_H
#include "global.h"

/* Observed 0x48-byte pointee view; original complete type is unknown. */
struct FloatProgressWork
{
    float float00, float04;
    u32 unknown08;
    s32 word0C;
    float float10, float14, float18, float1C;
    s32 word20, word24;
    float float28, float2C, float30, float34, float38, float3C, float40;
    s32 word44;
};
u32 sub_08056F24(struct FloatProgressWork *work);
#endif
