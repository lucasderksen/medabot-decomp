/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "later_graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern const u8 *gState0NextCommands_083B6100[];

void sub_0803A130(void);
void sub_0803ACB4(void);

void sub_0803A130(void) {
 /* The ROM leaves R5 unchanged if all nine slots are busy.
  * selected is intentionally uninitialized on that path. */
 u32 i,selected;
 u8 slot;struct FrameObject *object;u8 *work;u32 zero;
 sub_0803D450();i=0;
 if(gFrameObjects[0xA].flags==0)selected=0xA;
 else {
search:
  i++;
  if(i<=8) {
   struct FrameObject *frames=gFrameObjects;
   u32 index=i+0xA;
   if(frames[index].flags==0)selected=index;
   else goto search;
  }
 }
 slot=selected;sub_08040CD0(slot,1);
 {struct FrameObject *frames=gFrameObjects;object=&frames[selected];}work=gState0TransferWork.bytes;
 object->flags=(zero=0,*(u16*)(work+0x10E)<<10);object->flags|=0x4004;
 object->tableSelector=zero;object->palette=0xE;object->priority=0x80;
 object->unknown2C[1]=*(u16*)(work+0x110);
 sub_08040B90(gState0NextCommands_083B6100[object->unknown2C[1]],slot);
 object->byte2B=*(u16*)(work+0x102);
 object->screenY=*(u16*)(work+0x106);
 object->unknown23[1]=*(u16*)(work+0x10A);
 object->unknown2C[0]=*(u16*)(work+0x10C);
 object->unknown23[6]=0xB;
 if((work[0xF8]&2)==0) {
  object->screenX=*(u16*)(work+0x104);
  object->unknown23[2]=*(u16*)(work+0x108);
 }else {
  object->flags|=0x1000;
  object->screenX=0xF0-*(u16*)(work+0x104);
  object->unknown23[2]=(0x20-work[0x108])&0x1F;
 }
 sub_0803D4AC();
}

void sub_0803ACB4(void) {
 /* The ROM leaves R5 unchanged if all nine slots are busy.
  * selected is intentionally uninitialized on that path. */
 u32 i,selected;
 u8 slot;struct FrameObject *object;u8 *work;u32 zero;
 sub_0803D450();i=0;
 if(gFrameObjects[0xA].flags==0)selected=0xA;
 else {
search:
  i++;
  if(i<=8) {
   struct FrameObject *frames=gFrameObjects;
   u32 index=i+0xA;
   if(frames[index].flags==0)selected=index;
   else goto search;
  }
 }
 slot=selected;sub_08040CD0(slot,1);
 {struct FrameObject *frames=gFrameObjects;object=&frames[selected];}work=gState0TransferWork.bytes;
 object->flags=(zero=0,*(u16*)(work+0x10E)<<10);object->flags|=0x4004;
 object->tableSelector=zero;object->palette=0xE;object->priority=0x80;
 object->unknown2C[1]=*(u16*)(work+0x110);
 sub_08040B90(gState0NextCommands_083B6100[object->unknown2C[1]],slot);
 object->byte2B=*(u16*)(work+0x102);
 object->screenY=*(u16*)(work+0x106);
 object->unknown23[1]=*(u16*)(work+0x10A);
 object->unknown2C[0]=*(u16*)(work+0x10C);
 object->unknown23[6]=0xD;
 if((work[0xF8]&2)==0) {
  object->screenX=*(u16*)(work+0x104);
  object->unknown23[2]=*(u16*)(work+0x108);
 }else {
  object->flags|=0x1000;
  object->screenX=0xF0-*(u16*)(work+0x104);
  object->unknown23[2]=(0x20-work[0x108])&0x1F;
 }
 sub_0803D4AC();
}
