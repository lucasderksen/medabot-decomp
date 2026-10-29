/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"


void sub_08072B34(void *arg0);

void sub_08072B34(void *arg0) {
  int new_var;
  s8 *new_var3;
  u8 **new_var5;
  int new_var6;
  u8 *new_var4;
  u8 *temp_r1;
  u8 new_var2;
  temp_r1 = *((u8 **) (((s8 *) arg0) + 0x14));
  new_var2 = (u8) (*temp_r1);
  *((u8 *) (((s8 *) arg0) + 0x67)) = new_var2;
  new_var = 0x14;
  new_var5 = (u8 **) (((s8 *) arg0) + new_var);
  *new_var5 = (u8 *) (temp_r1 + 1);
  new_var3 = (s8 *) arg0;
  new_var4 = (u8 *) (new_var3 + 0x50);
  new_var6 = 0x20 | (*((u8 *) (((s8 *) arg0) + 0x50)));
  *new_var4 = (u8) new_var6;
}
