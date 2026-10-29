/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "record_helpers.h"
#include "state0_work.h"

struct ContinueThresholdWork38F34 {
    u8 pad[0x88];
    u8 bank;
    u8 gap[0x5F];
    s16 input;
    u8 gap2[4];
    s16 value;
    u8 gap3[2];
    u16 saved;
};


s32 sub_08038F34(s16 threshold);

s32 sub_08038F34(s16 threshold) {

  struct ContinueThresholdWork38F34 *root = (struct ContinueThresholdWork38F34 *)&gState0TransferWork;
  s16 *input = &root->input;
  u8 *setup;
  u8 *record;
  if ((*input) > threshold)
  {
    root->value = 0;
    setup = gSetupBuffer_03000590;
    record=(u8 *)(((u32)root->bank<<8)-(0U-(u32)setup));
    record += 0xBC;
    {
      u32 flags = *record;
      u32 mask = 0x4C;
      mask |= flags;
      *record = mask;
    }
    root->saved = *input;
    return 1;
  }
  return 0;
}
