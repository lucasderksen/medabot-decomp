/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "effect_work.h"
#include "frame.h"
#include "input.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 sub_0805B8EC();
extern void sub_080605A0();
extern void sub_08060620();

void sub_0801AEB4(void);
s32 sub_08048B70(s32 left, s32 right);
void sub_08060A54(void);
void sub_0806A078(u8 *destination,u8 *source);
s32 sub_08070778(u8 slot);

void sub_0801AEB4(void) {
  u8 *work = gState0TransferWork.bytes;
  u8 *cursor = work + 0x9C;
  u8 **cursor_address;
  *cursor = 0;
  cursor++;
  *cursor = 0;
  cursor++;
  *cursor = 0;
  cursor++;
  *cursor = 0;
  cursor++;
  *(*(cursor_address = &cursor)) = 0;
}

s32 sub_08048B70(s32 left, s32 right) {
  s32 product = ((s16) left) * ((s16) right);
  s32 rounded = product;
  if (product < 0)
  {
    rounded += 0xFF;
  }
  product = ((u32)rounded) << 8;
  return ((s32) product) >> 16;
}

void sub_08060A54(void) {
    s8 temp_r4;
    u32 *counter;
    u32 keys;

    sub_080605A0();
    sub_08060620();
    if (sub_0805B8EC() == 0) {
        if ((keys=*(u8 *)&gNewKeys), (3 & keys)) {
            if (gMainSubstate == 0xA) {
                sub_08074DE0(5U);
                (*(s8 *)((u8 *)(gMainContextPointer_03006F74) + 0x48)) = 1;
            } else {
                temp_r4 = 1 & keys;
                if (temp_r4 != 0) {
                    sub_08074DE0(4U);
                    (*(s8 *)((u8 *)(gMainContextPointer_03006F74) + 0x48)) = 1;
                } else {
                    sub_08074DE0(5U);
                    (*(s8 *)((u8 *)(gMainContextPointer_03006F74) + 0x48)) = temp_r4;
                }
            }
            (*(s8 *)((u8 *)(gMainContextPointer_03006F74) + 0)) = 0;
            counter=&gUnknown_0300137C;
            *counter += 1;
        }
    } else {
        sub_0803FB0C();
        counter=&gUnknown_0300137C;
        *counter=4;
    }
}

void sub_0806A078(u8 *destination,u8 *source) {
 do {*destination++=*source;}while(*source++<=0xF8U);}

s32 sub_08070778(u8 slot) {
  struct FrameObject *frames = gFrameObjects;
  struct FrameObject *object = &frames[slot];
  u8 *counter = ((u8 *) object) + 0x21;
  int reset;
  u32 before = *counter;
  if (before <= 0x47)
  {
    *counter = before + 1;
  }
  else
  {
    u16 old = *((u16 *) (((u8 *) object) + 2));
    reset = 0;
    if ((*((s16 *) (((u8 *) object) + 2))) > 0x168)
    {
      u32 zero = reset;
      *((u16 *) (((u8 *) object) + 2)) = reset;
      *counter = zero;
    }
    else
    {
      *((u16 *) (((u8 *) object) + 2)) = old + 6;
    }
  }
  return 1;
}
