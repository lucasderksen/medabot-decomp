/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "main_callbacks.h"
#include "serial.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern u16 gContinuedByte_03002B64;
s32 sub_0805BB38(u16);

void sub_0805BB6C(void);

void sub_0805BB6C(void) {
  u16 new_var;
  if (((s8) ((u8) gMainFlag_03005030)) != 0)
  {
    new_var = gUnknown_03000B90 != 0;
    if (new_var)
    {
      sub_0805BB38(gMainSerialOutgoingWork.words[0][0]);
      return;
    }
    gMainSerialOutgoingWork.word04 = gContinuedByte_03002B64;
    new_var = gMainSerialOutgoingWork.words[0][0];
    sub_0805BB38(new_var);
  }
}
