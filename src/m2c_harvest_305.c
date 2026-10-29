/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "equipment_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern void sub_08019184(u32, u32);
extern s32 sub_08035590(s32);
extern u8 gUnknown_083AF4B0[];

void sub_08019108(s32 arg0);
void sub_08035528(u32 selected);

void sub_08019108(s32 arg0) {

  u8 *setup;
  s32 off;
  u8 *rec;
  u8 *pd;
  u32 temp_r0;
  u32 temp_r4;
  u8 *r;
  setup = gSetupBuffer_03000590;
  off = arg0 << 8;
  rec = (u8 *) (off + ((u32) setup));
  pd = rec + 0xDD;
  temp_r0 = *pd;
  if (temp_r0 != 0)
  {
    if (temp_r0 > 3U)
    {
      sub_08019184(arg0, 0xCU);
      return;
    }
    temp_r0 = 6U;
    temp_r4 = *pd;
    r = &setup[((temp_r4 - 1) * 0x18) + off];
    if (r[0x59] != 0)
    {
      if (temp_r4 == 1)
      {
        sub_08019184(arg0, temp_r0);
        return;
      }
      if (!(4 & rec[0xBD]))
      {
        sub_08019184(arg0, r[0x50]);
        return;
      }
      sub_08019184(arg0, r[0x51]);
    }
  }
}

void sub_08035528(u32 selected) {

    s32 temp_r4;
    s32 rnd;
    u8 temp_r0;
    u8 *temp_r6;
    u8 *tbl;
    u8 *p;
    u8 *setup;

    setup = gSetupBuffer_03000590;
    temp_r6 = setup + (selected << 8);
    p = temp_r6 + 0xE0;
    temp_r0 = *p;
    if (temp_r0 != 0) {
        tbl = gUnknown_083AF4B0;
        temp_r4 = sub_08035590(temp_r0 - 1);
        rnd = sub_080424B8();
        temp_r4 <<= 3;
        temp_r0 = tbl[temp_r4 + (rnd & 7)] + 1;
        p = temp_r6 + 0xE1;
        *p = temp_r0;
    }
}
