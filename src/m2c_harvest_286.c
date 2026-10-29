/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "tile_text.h"

struct FrameCommand33 {u8 pad0[0x1A];u16 delay;u8 pad1C[4];u8 command,offset;u8 pad22[0x12];u16 field34;};


u32 sub_0806DFF0(u32 frame);
void sub_08071DB8(u32 command,u32 frame,u32 field34);

u32 sub_0806DFF0(u32 frame) {

 u32 offset;
 u32 frameRoot;
 struct FrameObject *object;
 u32 x;
 offset=frame<<24;
 frameRoot=(u32)gFrameObjects;
 offset>>=18;
 object=(void *)(offset+frameRoot);
 x=(u16)object->screenX;
 x-=8;
 object->screenX=x;
 if((s16)x<=120)return 0;
 return 1;
}

void sub_08071DB8(u32 command,u32 frame,u32 field34) {

 u32 offset;
 u32 frameRoot;
 struct FrameCommand33 *object;
 offset=frame<<24;
 frameRoot=(u32)gFrameObjects;
 offset>>=18;
 object=(void *)(offset+frameRoot);
 object->command=command;
 object->offset=0;
 object->field34=field34;
 object->delay=0;
}
