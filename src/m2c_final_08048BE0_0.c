/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "frame.h"
#include "main_callbacks.h"
#include "pose_channels.h"
#include "scene_animation.h"

extern u8 gContinuedByte_03002B64;

void sub_08048BE0(void);

void sub_08048BE0(void) {

  if (gContinuedByte_03002B64 & 2)
  {
    if (gContinuedByte_03002B64 & 0x40)
    {
      gBackgroundState_03005310.scrollY[0] -= 4;
      gBackgroundState_03005310.scrollY[1] -= 4;
      gBackgroundState_03005310.scrollY[2] -= 4;
    }
    if (gContinuedByte_03002B64 & 0x80)
    {
      gBackgroundState_03005310.scrollY[0] += 4;
      gBackgroundState_03005310.scrollY[1] += 4;
      gBackgroundState_03005310.scrollY[2] += 4;
    }
    if (gContinuedByte_03002B64 & 0x20)
    {
      gBackgroundState_03005310.scrollX[0] -= 4;
      gBackgroundState_03005310.scrollX[1] -= 4;
      gBackgroundState_03005310.scrollX[2] -= 4;
    }
    if (gContinuedByte_03002B64 & 0x10)
    {
      gBackgroundState_03005310.scrollX[0] += 4;
      gBackgroundState_03005310.scrollX[1] += 4;
      gBackgroundState_03005310.scrollX[2] += 4;
    }
  }
  if (gContinuedByte_03002B64 & 0x10)
  {
    FORCE_REGISTER(u32 next, r0) = gBackgroundState_03005310.angle + 1; /* FAKE MATCH: keeps angle + 1 and the masked result in r0 as in the reference */
    FORCE_REGISTER(u16 mask, r1) = 0xFFFF; /* FAKE MATCH: a u16 in r1 makes reload load 0xFFFF into r3 and copy it to r1 as the reference does */
    next = (next & mask) % 0x100;
    gBackgroundState_03005310.angle = next;
  }
  if (gContinuedByte_03002B64 & 0x20)
  {
    gBackgroundState_03005310.angle = (gBackgroundState_03005310.angle + 0xFF) & 0xFF;
  }
}
