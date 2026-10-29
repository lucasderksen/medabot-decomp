#include "global.h"
#include "object_numeric_helpers.h"

#include "background_state.h"

void sub_08048A8C(void)
{
    const s16 *table = gAffineSineTable_080AE8F4;
    struct BackgroundState *work = &gBackgroundState_03005310;
    {
        u32 phase = work->angle;
        s32 value;
        s16 reciprocal;
        phase += 64;
        value = table[phase];
        reciprocal = sub_08048BA0(work->scaleX);
        work->pa = sub_08048B70(value, reciprocal);
    }
    {
        s32 value = table[work->angle];
        s16 reciprocal = sub_08048BA0(work->scaleX);
        work->pb = sub_08048B70(value, reciprocal);
    }
    {
        s32 value = (s16)-table[work->angle];
        s16 reciprocal = sub_08048BA0(work->scaleY);
        work->pc = sub_08048B70(value, reciprocal);
    }
    {
        u32 phase = work->angle;
        s32 value;
        s16 reciprocal;
        phase += 64;
        value = table[phase];
        reciprocal = sub_08048BA0(work->scaleY);
        work->pd = sub_08048B70(value, reciprocal);
    }
    work->dx = (120 - work->x) * 256 - work->pa * 120 - work->pb * 80;
    work->dy = (120 - work->y) * 256 - work->pc * 120 - work->pd * 80;
}
