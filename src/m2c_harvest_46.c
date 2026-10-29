/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s8 gUnknown_0300056F;
extern void (*gUnknown_083AF6B0[])(void);
s32 sub_0803579C(u8, u8);
s32 sub_08035814(u8);
s32 sub_0803725C();
s32 sub_08037280(u8, u8);

void sub_08023CB8(void);
s32 sub_08035A70(s32 arg0, s32 arg1, s32 arg2);
s32 sub_08037B9C(void);

void sub_08023CB8(void) {
    u8 *var_r1;
    u8 var_r0;

    sub_0803579C(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7]);
    sub_08035814(gState0TransferWork.bytes[0x87]);
    if (sub_0803725C() != 0) {
        gState0TransferWork.bytes[0xA6] = 0x1A;
        *(&gState0TransferWork.bytes[0xA6] + 4) = gState0TransferWork.bytes[0xAA] + 1;
    } else if (sub_080331F8((u32) gState0TransferWork.bytes[0x88]) == 0) {
        gState0TransferWork.bytes[0xA6] = 0x39;
        *(&gState0TransferWork.bytes[0xA6] + 4) = gState0TransferWork.bytes[0xAA] + 1;
    } else if (sub_080331F8((u32) gState0TransferWork.bytes[0x87]) == 0) {
        gState0TransferWork.bytes[0xA6] = 0x39;
        *(&gState0TransferWork.bytes[0xA6] + 4) = gState0TransferWork.bytes[0xAA] + 1;
    } else {
        sub_08036270();
        sub_08037280(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xA7]);
        gState0TransferWork.bytes[0xAA] = 4;
    }
}

s32 sub_08035A70(s32 arg0, s32 arg1, s32 arg2) {
  s8 *new_var;
  int new_var2;
  __typeof__(gSetupBuffer_03000590[0]) * array0;
  array0 = gSetupBuffer_03000590;
  if (!(!((2 & (*((u8 *) ((new_var = (s8 *) ((arg2 << 8) + gSetupBuffer_03000590)) + 0xC0)))) && ((*((u8 *) (((s8 *) (&array0[new_var2 = (arg1 * 0x18) + (arg0 << 8)])) + 0x49))) == 0x34))))
  {
    return 1;
  }
  return 0;
}

s32 sub_08037B9C(void) {
    s32 offset;
    s32 idle;
    u32 i;
    s8 *current;
    void (**handlers)(void);
    u8 *object;
    idle = 1;
    i = 0;
    current = &gUnknown_0300056F;
    offset = 0x840;
    handlers = gUnknown_083AF6B0;
    do {
        *current = i + 0x21;
        object = offset + (u8 *) gFrameObjects;
        if (object[0x29] != 0) {
            idle = 0;
        }
        handlers[object[0x29]]();
        offset += 0x40;
        i += 1;
    } while (i <= 0x1AU);
    return idle;
}
