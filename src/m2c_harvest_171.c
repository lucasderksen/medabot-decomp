/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedTieInput { u8 pad00[0x29]; u8 first29; u8 pad2A[7]; u8 second31; };
struct ContinuedTieState { u8 pad00[0x89]; u8 mode89; u8 pad8A[0x12]; u8 decision9C; };
struct ContinuedSetupFrame33 { u8 pad00[0x840]; struct FrameObject frame; };
struct ContinuedFrame4Mirror {
 u8 prefix[0x102];s16 x,y;
 u8 gap[0x129-0x106];u8 kind;u8 gap2;u8 active;
 u8 tileX,clear,field2,field3;u16 delay;
};

extern const u8 *const gState0NextCommands_083B6100[0x23];
extern const u8 gActionMotionPalette_0850F8D8[0x20];
#include "action_scene_data.h"
extern struct ContinuedTieInput gUnknown_03001800;
extern u32 sub_0801B4C8(s32);
extern s32 sub_0801B4F8(u32);
extern void sub_0801BCE4(u32,s32,s32);
extern void sub_0801BD1C(const void *,s32,s32);
extern void sub_0803D450(void);
extern void sub_0803D4AC(void);

void sub_0801B53C(void);
void sub_0801FEE8(void);
void sub_0803B754(void);

void sub_0801B53C(void) {
 u32 first, second, mode;
 struct ContinuedTieState *state;
 first = sub_0801B4C8(0);
 second = sub_0801B4C8(3);
 if (first < second) goto one;
 if (second < first) goto two;
 first = sub_0801B4F8(0);
 second = sub_0801B4F8(3);
 if (first < second) goto one;
 if (second < first) goto two;
 if (gUnknown_03001800.first29 > gUnknown_03001800.second31) {
 one:
  ((struct ContinuedTieState*)gUnknown_03000440)->decision9C = 1;
  return;
 }
 if (gUnknown_03001800.first29 < gUnknown_03001800.second31) {
 two:
  ((struct ContinuedTieState*)gUnknown_03000440)->decision9C = 2;
  return;
 }
 state = (struct ContinuedTieState*)gUnknown_03000440;
 mode = state->mode89;
 if (mode != 1) {
  if (sub_080424B8() & 1) {
   state->decision9C = 1;
   return;
  }
  goto late_two;
 }
 if (gUnknown_03000B90 == 0) {
  if (sub_080424B8() & mode) goto late_one;
  goto late_two;
 }
 if (sub_080424B8() & mode) {
 late_two:
  state->decision9C = 2;
  return;
 }
 late_one:
 state->decision9C = mode;
}

void sub_0801FEE8(void) {
 struct ContinuedSetupFrame33 *frames;
 u8 *work;
 u32 zero;
 LeDecompress(gActionMotionAsset_084CDF48, (void *)0x06014800);
 CpuFastSet(gActionMotionPalette_0850F8D8, (void *)0x050002E0, 8u);
 frames = (struct ContinuedSetupFrame33 *)&gFrameObjects;
 frames->frame.flags = (zero = 0, 0xC004);
 frames->frame.tableSelector = zero;
 work = gState0TransferWork.bytes;
 frames->frame.screenX = (u16)gFrameObjects[work[0x51] * 4 + 0x5D].screenX;
 frames->frame.screenY = (u16)gFrameObjects[work[0x51] * 4 + 0x5D].screenY - 4;
 frames->frame.palette = 7;
 frames->frame.priority = 0xF0;
 sub_08040B90(gState0NextCommands_083B6100[0x22], 0x21);
 work[0xAA]++;
}

void sub_0803B754(void) {
 u8 *setup,*work,*initialWork;struct ContinuedFrame4Mirror *frames;
 s32 offset;u32 value,halfWidth;void *record;
 sub_0803D450();
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
 frames->kind=0x10;
 sub_0801BD1C(gUnknown_083CEDF4[frames->active],0,0);
 frames->y=*(u16*)(work+0x108);
 frames->tileX=*(u16*)(work+0x110);
 if(!(2&work[0xF8])) frames->x=*(u16*)(work+0x106);
 else {
  halfWidth=frames->field2>>1;
  frames->x=(0x1E - halfWidth)-(*(u16*)(work+0x106)+halfWidth);
 }
 ((struct ContinuedFrame4Mirror*)gFrameObjects)->clear=0;
 sub_0803D4AC();
}
