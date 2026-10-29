/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "bios_lz77.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "scene_view.h"
#include "sound_samples.h"
#include "sprite_layouts.h"
#include "state0_work.h"

struct HalfwordPair { u16 first; u16 second; };


void sub_0805AE4C(void);

void sub_0805AE4C(void) {

  u16 count = 0;
  s16 i;
  u8 value;
  u8 flag;
  for (i = 0; i <= 0x3F; i++)
  {
    value = gObjectCountPairs[i][0];
    flag = value & 0x80;
    if (flag)
    {
      ((struct HalfwordPair *) 0x02040000)[i].first = value & 0x7F;
      value = 1;
      ((struct HalfwordPair *) 0x02040000)[i].second = gObjectCountPairs[i][value];
      count++;
    }
    else
    {
      ((struct HalfwordPair *) 0x02040000)[i].second = flag;
    }
  }

  ((u8 *) gMainContextPointer_03006F74)[0x10] = count;
}
