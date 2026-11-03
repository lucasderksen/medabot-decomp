/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "frame.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_work.h"

struct MosaicRampWork6FB5C {u8 unknown00[6];u16 rate;u32 counter;};

extern s32 __divsi3(s32,s32);
extern s32 __modsi3(s32,s32);

s32 sub_0806FB5C(void);

s32 sub_0806FB5C(void) {

  s32 nibble;
  volatile u16 *mosaic;
  struct MosaicRampWork6FB5C *work;
  s32 count;
  u16 rate;
  u8 step;
  work = (struct MosaicRampWork6FB5C *)gState0TransferWork.bytes;
  rate = work->rate;
  count = work->counter;
  if (__modsi3(count, rate) == 0)
  {
    step = 16U - ((u32) __divsi3(count, rate));
    *((volatile u16 *) 0x04000054) = (s16) step;
    mosaic = (volatile u16 *) 0x0400004C;
    nibble = step;
    nibble = 0xF & nibble;
    *mosaic = nibble | (nibble * 0x10);
    if (step == 0)
    {
      work->counter = (s32) step;
      return 1;
    }
  }
 do { work->counter = work->counter + 1; return 0; } while (0);
}
