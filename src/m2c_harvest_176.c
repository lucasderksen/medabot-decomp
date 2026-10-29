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
#include "gba.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedFC3CFrame33 { u8 pad00[0x840]; struct FrameObject frame; };
struct ContinuedFrame35Mirror {
 u8 prefix[0x8C2];s16 x,y;
 u8 gap[0x8E8-0x8C6];u8 group;u8 kind;u8 gap2;u8 active;
 u8 tileX,clear,field2,field3;u16 delay;
};

extern const u16 gUnknown_085104B8[32];
#include "action_scene_data.h"
extern void sub_0801BCE4(u32,s32,s32);
extern void sub_0801BD1C(const void *,s32,s32);
extern void sub_0803D450(void);
extern void sub_0803D4AC(void);

void sub_0802FC3C(void);
void sub_0803A474(void);

void sub_0802FC3C(void) {
 struct ContinuedFC3CFrame33 *frames;
 u8 *work;
 u8 *bank;
 sub_08040CD0(0x21, 2);
 CpuFastSet(gUnknown_085104B8, (void *)0x050002C0, 0x10u);
 frames = (struct ContinuedFC3CFrame33 *)&gFrameObjects;
 frames->frame.flags = 0xC624;
 frames->frame.tableSelector = 0;
 work = gState0TransferWork.bytes;
 bank = work + 0x87;
 frames->frame.screenX = (u16)gFrameObjects[*bank * 4 + 0x5D].screenX;
 frames->frame.screenY = (u16)gFrameObjects[*bank * 4 + 0x5D].screenY - 4;
 frames->frame.palette = 7;
 frames->frame.scaleX = 0x80;
 frames->frame.scaleY = 0x80;
 frames->frame.angle = 0;
 frames->frame.priority = 0xF0;
 frames->frame.frameAndGroup = 0x8302;
 work[0xAA]++;
}

void sub_0803A474(void) {
 u8 *setup,*work,*initialWork;struct ContinuedFrame35Mirror *frames;
 s32 offset,halfWidth;u32 value;void *record;
 sub_0803D450();
 sub_08040CD0(0x23,1);
 setup=gSetupBuffer_03000590;initialWork=gState0TransferWork.bytes;
 offset=initialWork[0x87]<<8;record=setup+offset;
 if(*(u8*)(record+0xDD)<=3U)
  value=setup[initialWork[0xA7]*0x18+offset+0x49];
 else value=*(u8*)(record+0xA8)+0x50;
 sub_0801BCE4(value,*(s16*)((work=gState0TransferWork.bytes)+0x10A),9);
 frames=(void*)gFrameObjects;
 frames->field2=*(u16*)(work+0x102);
 frames->field3=*(u16*)(work+0x104);
 frames->active=*(u16*)(work+0x10E);
 frames->delay=*(u16*)(work+0x10C);
 frames->kind=0x11;
 sub_0801BD1C(gUnknown_083CEDF4[frames->active],1,1);
 frames->y=*(u16*)(work+0x108);
 if(!(2&work[0xF8])) {
  frames->x=*(u16*)(work+0x106);
  frames->tileX=*(u16*)(work+0x110);
 }
 else {
  halfWidth=frames->field2>>1;
  frames->x=((0x1E - halfWidth)-(*(u16*)(work+0x106)+halfWidth))-1;
  frames->tileX=work[0x110]+2;
 }
 ((struct ContinuedFrame35Mirror*)gFrameObjects)->clear=0;
 ((struct ContinuedFrame35Mirror*)gFrameObjects)->group=0;
 sub_0803D4AC();
}
