/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "frame.h"
#include "main_callbacks.h"


s32 sub_08070648(u32 inputIndex);

s32 sub_08070648(u32 inputIndex) {

 u32 index,root,offset,scale;
 struct FrameObject *object;
 struct FrameObject *base;
 struct FrameObject *command;
 index=(u8)inputIndex;
 root=(u32)gFrameObjects;
 offset=index<<6;
 object=(struct FrameObject*)(root+offset);
 scale=object->scaleX;
 if(scale<=0x3F) goto updateX;
 scale=object->scaleY;
 if(scale>0x3F) return 0;
 goto updateY;
 updateX: {
  scale+=8;
  object->scaleX=scale;
  if((u8)scale>0x40) object->scaleX=0x40;
 }
 goto updateCommand;
 updateY: {
  scale+=8;
  object->scaleY=scale;
  if((u8)scale>0x40) object->scaleY=0x40;
 }
 updateCommand:
 base=gFrameObjects;
 command=&base[index];
 command->commandOffset++;
 return 1;
}
