/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"


void sub_08072C3C(void *arg0);

void sub_08072C3C(void *arg0) {
  u8 new_var;
  u8 *temp_r0;
  temp_r0 = *((u8 **) (((s8 *) arg0) + 0x14));
  new_var = *temp_r0;
  *((u8 *) (((s8 *) arg0) + 0x54)) = (u8) new_var;
  *((u8 **) (((s8 *) arg0) + 0x14)) = (u8 *) (temp_r0 + 1);
  if ((*((u8 *) (((s8 *) arg0) + 0x54))) == 0)
  {
    *((u8 *) (((s8 *) arg0) + 0x54)) = 8U;
  }
  *((u8 *) (((s8 *) arg0) + 0x50)) = (u8) ((*((u8 *) (((s8 *) arg0) + 0x50))) | 8);
}
