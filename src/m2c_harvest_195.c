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
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Continued378A8Frames { u8 pad00[0x840]; struct FrameObject frame; };
struct Continued378A8Work { u8 pad00[0xF8]; u8 directionF8; };
struct Continued3EC50Frames { u8 pad00[0x80]; struct FrameObject frame; };

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gUnknown_083AD520[];

void sub_0801677C(void);
void sub_080378A8(void);
void sub_08037BF4(void);
void sub_0803EC50(void);

void sub_0801677C(void) {
 gFrameObjects[0].flags=0xC404;
 gFrameObjects[0].tableSelector=0;
 gFrameObjects[0].screenX=0x78;
 gFrameObjects[0].screenY=0x78;
 gFrameObjects[0].palette=10;
 gFrameObjects[0].priority=0xC0;
 { u32 base=(u32)gUnknown_083AD520; u32 index=gState0TransferWork.bytes[0x82];
   gFrameObjects[0].frameAndGroup=*(const u8 *)(base+index)+0x600; }
}

void sub_080378A8(void) {
 struct Continued378A8Work *work=(void *)&gState0TransferWork;
 if(!(work->directionF8&2)) {
  struct Continued378A8Frames *frames=(void *)&gFrameObjects;
  frames->frame.screenX=((u16)frames->frame.screenX+4)&0x1FF;
 } else {
  struct Continued378A8Frames *frames=(void *)&gFrameObjects;
  frames->frame.screenX=((u16)frames->frame.screenX-4)&0x1FF;
 }
}

void sub_08037BF4(void) {
 const u8 *const *commands=gState0NextCommands_083B6100;
 struct FrameObject *frames=gFrameObjects;
 u8 *work=gState0TypedWork.bytes;
 u8 *selected=work+0x12F;
 struct FrameObject *frame;
 u32 y;
 sub_08040BD8(commands[frames[*selected].unknown2C[2]],*selected);
 frame=&frames[*selected];
 y=(u16)frame->screenY;
 if(frame->screenY==20) frame->unknown23[6]++;
 else frame->screenY=(y+1)&0xFF;
}

void sub_0803EC50(void) {
 struct Continued3EC50Frames *frames=(void *)&gFrameObjects;
 u32 sum=frames->frame.unknown23[1]+frames->frame.commandDelay;
 u32 step=sum>>2;
 frames->frame.commandDelay=sum&3;
 if(frames->frame.unknown23[2]==0)
  frames->frame.screenY=((u16)frames->frame.screenY-step)&0xFF;
 else
  frames->frame.screenY=((u16)frames->frame.screenY+step)&0xFF;
}
