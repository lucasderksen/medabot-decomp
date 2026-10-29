/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"

extern s32 gState0NextCommands_083B6100;

s32 sub_0803684C(s32 arg0);

s32 sub_0803684C(s32 arg0) {
  struct FrameObject *new_var2;
  u8 *new_var;
  __typeof__(gFrameObjects[0]) * array0;
  u8 *work0;
  s32 var_r7;
  struct FrameObject *temp_r4;
  u32 temp_r2;
  u32 var_r6;
  u32 temp_r0;
  u32 temp_r3;
  u32 temp_r5;
  var_r7 = 1;
  var_r6 = 0;
  do
  {
    new_var2 = gFrameObjects;
    temp_r3 = arg0 + var_r6;
    array0 = new_var2;
    temp_r4 = &array0[temp_r3];
    temp_r2 = temp_r4->flags;
    if (temp_r2 != 0)
    {
      new_var = temp_r4->unknown2C;
      temp_r0 = new_var[0];
      if (temp_r0 == 0)
      {
        temp_r4->flags = 0x8004 | temp_r2;
        temp_r4->palette = 0xE;
        temp_r5 = temp_r3;
        work0 = (u8 *) (&gState0NextCommands_083B6100);
        sub_08040BD8(*((u8 **) (((s8 *) work0) + 0x74)), temp_r5);
        if (temp_r4->commandStopped == 0xFF)
        {
          sub_08040CD0(temp_r5, 1U);
        }
        else
        {
          goto block_6;
        }
      }
      else
      {
        temp_r4->unknown2C[0] = temp_r0 - 1;
        block_6:
        var_r7 = 0;

      }
    }
    var_r6 += 1;
  }
  while (var_r6 <= 3U);
  return var_r7;
}
