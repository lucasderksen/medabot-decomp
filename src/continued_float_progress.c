/* Observed 0x48-byte float/word access view; original type and role unknown. */
#include "continued_float_progress.h"
#include "background_state.h"

u32 sub_08056F24(struct FloatProgressWork *work)
{
    u32 result = 0;
    s32 step = 1;
    s32 mode = work->word0C;
    if (mode)
    {
        float threshold = (float)work->word20;
        if (threshold <= work->float1C)
        {
            switch (mode)
            {
            case 16:
            case 17:
                if (work->float1C < (float)work->word20 + work->float2C)
                    work->float00 += work->float3C;
                break;
            case 18:
            case 19:
                if (work->float1C < (float)work->word20 + work->float2C)
                {
                    float amount = (float)step;
                    const s16 *table;
                    u32 phase;
                    work->float14 += work->float3C * amount;
                    if (work->float14 >= 64.0f)
                        work->float14 = 64.0f;
                    table = gAffineSineTable_080AE8F4;
                    phase = (s32)(work->float14 + 192.0f) & 255;
                    work->float00 += work->float40 * ((float)table[phase] + 256.0f) * (1.0f / 256.0f) * amount;
                }
                else
                    work->float00 += work->float40;
                break;
            case 20:
            case 21:
                if (work->float1C < (float)work->word20 + work->float2C)
                    work->float00 += work->float3C;
                else
                {
                    const s16 *table;
                    u32 phase;
                    float value, amount, coefficient;
                    s32 converted;
                    work->float14 += work->float40;
                    if (work->float14 >= 64.0f)
                        work->float14 = 64.0f;
                    table = gAffineSineTable_080AE8F4;
                    converted = (s32)work->float14;
                    phase = 255;
                    phase &= converted;
                    phase += 64;
                    value = (float)*(const s16 *)((u32)table + phase * 2);
                    coefficient = work->float3C;
                    coefficient *= value;
                    value = coefficient;
                    value *= 1.0f / 256.0f;
                    amount = (float)step;
                    value *= amount;
                    work->float00 += value;
                }
                break;
            case 23:
            {
                const s16 *table;
                u32 phase;
                float value, amount, coefficient;
                work->float14 += work->float3C;
                table = gAffineSineTable_080AE8F4;
                phase = (s32)work->float14 & 255;
                value = (float)table[phase];
                coefficient = work->float40;
                coefficient *= value;
                value = coefficient;
                amount = (float)step;
                value *= amount;
                work->float00 = work->float04 + value;
                break;
            }
            }
            work->float1C += 1.0f;
            if (work->word24 != 65535 && work->float1C >= (float)work->word24)
            {
                work->word0C = 0;
                result = 1;
            }
        }
        else
            work->float1C += 1.0f;
    }
    return result;
}
