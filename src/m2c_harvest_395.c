/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "serial.h"
#include "state0_work.h"

extern u8 gUnknown_030018D2[];

void sub_0802E8D4(void);

void sub_0802E8D4(void) {

  u32 stopped;
  struct FrameObject *scaleFrame;
  u32 index;
  u32 phase;
  u32 frameRoot;
  u32 offset;
  u32 address;
  u32 enabledRoot;
  u8 *enabled;
  u8 *work;
  struct FrameObject *frame;
  u32 scale;
 do { stopped = 0; index = 0; phase = 0x0A000000; } while (0);
  enabled = gUnknown_030018D2;
  enabledRoot = (u32) enabled;
  frameRoot = (u32) gFrameObjects;
  frame = (struct FrameObject *) (frameRoot + (phase >> 18));
  do
  {
    address = index;
    address += enabledRoot;
    if (*((u8 *) address))
    {
      scaleFrame = frame;
      scale = scaleFrame->scaleX;
      if (scale == 2)
      {
        stopped = 1;
        sub_08040CD0(phase >> 24, 1);
      }
      else
      {
        frame->scaleX = scale - 2;
        frame->scaleY -= 2;
      }
    }
    phase += 0x01000000;
    frame++;
    index++;
  }
  while (index <= 2);
  if (stopped)
  {
    work = gState0TransferWork.bytes;
    work += 0xAA;
    *work = (*work) + 1;
  }
}
