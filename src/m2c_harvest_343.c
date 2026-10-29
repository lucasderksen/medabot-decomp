/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "serial.h"
#include "state0_work.h"

struct ContinuedPhaseWork28 {u8 before[0xAA];u8 phase;};

extern u8 gUnknown_030018D2[3];

void sub_0802A4C4(void);

void sub_0802A4C4(void) {

  s32 finished;
  u32 index;
  u8 *frameCursor;
  u8 *selected;
  struct FrameObject *frames;
  u32 nextScale;
  finished = 0;
  index = 0;
  selected = gUnknown_030018D2;
  frames = gFrameObjects;
  /* Traverse the complete 128-frame backing; frames 35..37, byte 8. */
  frameCursor = (u8 *)frames + 0x8C8;
  do
  {
    if (*(u8 *)(index - (0U - (u32)selected)) != 0)
    {
      *((u16 *) (((s8 *) frameCursor) + 0x10)) = (u16) (((*((u16 *) (((s8 *) frameCursor) + 0x10))) + 0x20) & 0x3FF);
      *((u8 *) (((s8 *) frameCursor) + 0)) -= 4;
      nextScale = (*((u8 *) (((s8 *) frameCursor) + 1))) - 4;
      *((u8 *) (((s8 *) frameCursor) + 1)) = nextScale;
      if (((u8) nextScale) == 4)
      {
        finished = 1;
      }
    }
    frameCursor += 0x40;
    index += 1;
  }
  while (index <= 2U);
  if (finished != 0)
  {
    sub_08040CD0(0x24U, 3U);
    ((struct ContinuedPhaseWork28 *) (&gState0TransferWork))->phase = (u8) (((struct ContinuedPhaseWork28 *) (&gState0TransferWork))->phase + 1);
  }
}
