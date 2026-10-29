/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"
#include "sound_work.h"


void sub_08074A04(void);

void sub_08074A04(void) {

  s32 zero;
  s32 i;
  struct SoundChannelState *track;
  s32 offset;
  u32 flags;
  i = 0;
  track = gFamilySoundRoot74028->channels;
  offset = 0;
  flags = (u32)&track->flags;
  loop:
  {
    const struct SoundTrackInit *init = (const struct SoundTrackInit *) (((const u8 *) gSoundTrackInitializers) + offset);
    zero = 0;
    *(u8 *)(flags + 1) = i;
    track->refreshAddress = init->refreshAddress;
    track->updateAddress = init->updateAddress;
    *(u8 *)(flags + 0x14) = init->kind;
    /* Equivalent to OR 0x5F; this form preserves the reference's registers. */
    *(u8 *)flags = ~(~*(u8 *)flags & ~0x5F);
    track->position = (track->counter = zero);
    if (init->queueIndex != 0xFF)
    {
      track->queue = ((u8 *) gFamilySoundRoot74028) + ((init->queueIndex * 0x34) + 0x5EC);
      sub_080741F4(track);
    }
    sub_0807455C(track, 0);
    offset += 12;
    i++;
    flags += 0x74;
    track++;
  }

  if (i <= 12)
  {
    goto loop;
  }
}
