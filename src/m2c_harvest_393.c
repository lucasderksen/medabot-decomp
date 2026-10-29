/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "continued_blend_work.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 sub_0803725C(void);
extern void sub_0803579C(u32, s32);
extern void sub_08035814(s32);
extern void sub_08036270(void);
extern void sub_08037280(u32, u32);

void sub_080209D8(void);

void sub_080209D8(void) {

  u8 *setup = gSetupBuffer_03000590;
  u8 *work = gState0TransferWork.bytes;
  u32 partOffset = work[0x8B] * 24;
  u16 increment;
  u32 offset = partOffset + (work[0x88] << 8);
  u8 *state;
  u32 kind;
  increment = 1;
  if ((*((u8 *) ((offset + ((u32) setup)) + 0x59))) == 0)
  {
    u8 *bank = work + 0x87;
    u32 initialBank = *bank;
    u8 *part = work + 0xA7;
    s32 result;
    sub_0803579C(initialBank, *part);
    sub_08035814(*bank);
    result = sub_0803725C();
    if (result != 0)
    {
      state = work + 0xA6;
      kind = 0x1A;
    }
    else
    {
      sub_08037280(*bank, *part);
      sub_08036270();
      work[0xAA]++;
      work[0xAB] = result;
      return;
    }
  }
  else
  {
    state = work + 0xA6;
    kind = 0x27;
  }
  *state = kind;
  state += 4;
  *state = 2;
  state = (u8 *) (((u32) state) + increment);
  *state = 1;
}
