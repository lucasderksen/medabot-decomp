/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Continued3ED28Frames { u8 pad00[0x80]; struct FrameObject frame; };
struct Continued3ED28Work { u8 pad00[0x1A3]; u8 limit1A3; };

extern void sub_0803EC50(void);

s32 sub_0803ED28(void);

s32 sub_0803ED28(void) {
 struct Continued3ED28Frames *frames;
 struct Continued3ED28Work *work;
 s32 y; s32 limit;
 sub_0803EC50();
 frames=(void *)&gFrameObjects;
 y=frames->frame.screenY;
 work=(void *)&gState0TransferWork;
 limit=work->limit1A3;
 if(y>=limit) {
  frames->frame.screenY=limit;
  return 1;
 }
 frames->frame.unknown23[1]++;
 return 0;
}
