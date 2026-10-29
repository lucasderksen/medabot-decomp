/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "equipment_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct CV { u8 pad[0xC8]; s16 a; s16 b; s16 c; };

extern s32 gCounter6ED08_03001800;
extern struct CV gUnknown_03001800;

void sub_0803579C(u32 arg0, s32 arg1);
void sub_08036CCC(s32 a, s32 b, s32 c);

void sub_0803579C(u32 arg0, s32 arg1) {

  s32 temp_r6; s32 t; u8 *temp_r4; u8 *base; u8 *setup; u16 *score; u8 *var_r1; u8 *p20; s32 idx; u32 v;
  base = (u8 *) (p20 = (u8 *)&gCounter6ED08_03001800);
  score = (u16 *) (base + 0xE8);
  setup = gSetupBuffer_03000590;
  t = arg1 * 0x18;
  temp_r6 = arg0 << 8;
  t += temp_r6;
  temp_r4 = setup + t;
  *score = (u16) (*score + temp_r4[0x4D]);
  *score = (u16) ((*score) + sub_0803576C(arg0));
  *score = (u16) ((sub_080424B8() & 7) + (*score));
  idx = temp_r4[0x4A] + temp_r6;
  p20 = setup + 0x20;
  *score = (u16) (*score + p20[idx]);
  if (sub_08042B80(temp_r4[0x4A]) != 0)
  {
    var_r1 = temp_r6 + setup;
    var_r1 += 0xA6;
  }
  else
  {
    var_r1 = (u8 *)(temp_r6 + (s32)setup); var_r1 += 0xA5;
    ;
  }
  *score = (u16) (*score + *var_r1);
}

void sub_08036CCC(s32 a, s32 b, s32 c) {

    u8 *setup = gSetupBuffer_03000590;
    u8 *s = setup + (b * 24 + (a << 8));
    s32 d = s[0x4c] - s[0x59];
    struct CV *g; struct CV *g2; s16 *q;
    if (d > c) {
        g = &gUnknown_03001800;
        g->a = c;
        g->c = c;
        g->b = 0;
    } else {
        g2 = &gUnknown_03001800;
        g2->a = d;
        g2->c = d;
        g2->b = c - d;
    }
}
