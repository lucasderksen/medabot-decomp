/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_command_handlers.h"
#include "main_callbacks.h"
#include "state0_work.h"


void sub_0806B0D4(void);

void sub_0806B0D4(void) {

  /* The scene dispatcher visits the first twenty of 128 frame records. */
  u8 frame = 0;
  do
  {
    u32 frames = (u32) gFrameObjects;
    struct FrameObject *object = (struct FrameObject *) (frames + (frame << 6));
    u8 *command = &object->commandDelay;
    if (*command)
    {
      if (gFrameCommandHandlers_084857D0[(*command) - 1](frame))
      {
        object->unknown1A++;
      }
      else
        if (*command)
      {
        sub_0806B530(frame, 0, 0, 0);
      }
    }
    frame++;
  }
  while (frame <= 19U);
}
