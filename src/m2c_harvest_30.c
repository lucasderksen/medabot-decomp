/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "frame.h"
#include "frame_objects.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

s32 sub_08019600(u32);
s32 sub_08019720(u32);
s32 sub_08019B40(u32);

void sub_080195C0(void);
void sub_08027BA0(void);

void sub_080195C0(void) {
    __typeof__(&(gSetupBuffer_03000590)[0]) offset0;
    u32 var_r4;
    u8 *var_r5;

    sub_08040D0C(0x46U, 0x12U);
    var_r4 = 0;
    offset0 = gSetupBuffer_03000590;
    var_r5 = offset0 + 0x40;
    do {
        if (*var_r5 != 0) {
            sub_08019600(var_r4);
            sub_08019720(var_r4);
            sub_08019B40(var_r4);
        }
        var_r5 += 0x100;
        var_r4 += 1;
    } while (var_r4 <= 5U);
}

void sub_08027BA0(void) {
  union State0TypedWork *new_var;
  short temp_r1;
  new_var = &gState0TypedWork;
  gState0TypedWork.widths.word86 = (temp_r1 = (*new_var).widths.word86 + 1);
  gFrameObjects[0x21].angle = (gFrameObjects[0x21].angle + 0x40) & 0x3FF;
  if (((u32) temp_r1) > 0x3CU)
  {
    gState0TransferWork.bytes[0xAA] += 1;
  }
}
