/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct CV { u8 p0[0x51]; u8 b51; u8 p52[0x60 - 0x52]; u8 b60; u8 p61[0x87 - 0x61]; u8 b87; u8 p88[0xAA - 0x88]; u8 bAA; u8 pAB[0xD2 - 0xAB]; u8 bD2[3]; };

extern s32 sub_0803836C();
extern struct CV gCounter6ED08_03001800;

void sub_0802B810(void);

void sub_0802B810(void) {

  u32 var_r3;
  u8 *temp_r2;
  u8 *setup;
  u8 *new_var;
  s8 *var_r1;
  s8 var_r0;
  sub_0803836C();
  gCounter6ED08_03001800.b60 = (u8) sub_08032FC4((u32) gCounter6ED08_03001800.b87);
  var_r3 = 0;
  do
  {
    setup = gSetupBuffer_03000590;
    temp_r2 = (u8 *) (((gCounter6ED08_03001800.b60 + var_r3) << 8) + ((u32) setup));
    if ((temp_r2[0x40] != 0) && (temp_r2[0x59] != 0))
    {
      gCounter6ED08_03001800.bD2[var_r3] = 1;
    }
    var_r3 += 1;
  }
  while (var_r3 <= 2U);
  new_var = gSetupBuffer_03000590;
  switch (new_var[(gCounter6ED08_03001800.b87 << 8) + 0xA8])
  {
    case 31:
      var_r1 = (s8 *) (&gCounter6ED08_03001800.b51);
      var_r0 = 0;
      goto block_16;

    case 33:
      var_r1 = (s8 *) (&gCounter6ED08_03001800.b51);
      var_r0 = 1;
      goto block_16;

    case 35:
      var_r1 = (s8 *) (&gCounter6ED08_03001800.b51);
      var_r0 = 2;
      goto block_16;

    case 37:
      var_r1 = (s8 *) (&gCounter6ED08_03001800.b51);
      var_r0 = 3;
      block_16:
    *var_r1 = var_r0;

      break;

  }

  gCounter6ED08_03001800.bAA = gCounter6ED08_03001800.bAA + 1;
}
