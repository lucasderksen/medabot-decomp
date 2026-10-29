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
#include "frame.h"
#include "gba.h"
#include "record_helpers.h"
#include "render_work.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedPartnerFrame2CC74 {u16 flags;s16 x,y;u16 group;u8 scaleX,scaleY,palette,priority;u8 gapC[0xC];u16 angle,unknown1A;u8 selector;u8 gap1D[6];u8 byte23,kind;u8 byte25;u8 gap26[0xA];u16 savedX;s16 savedY;u8 gap34[0xC];};
struct ContinuedPartnerFrames2CC74 {u8 prefix[0x840];struct ContinuedPartnerFrame2CC74 objects[95];};

extern const u8 gUnknown_084D7A04[];
extern const u8 gUnknown_0850FDD8[32];

void sub_0802CC74(void);

void sub_0802CC74(void) {

 u8 *work,*direction,*kind;
 struct ContinuedPartnerFrames2CC74 *frames;
 struct ContinuedPartnerFrame2CC74 *current;
 u32 i,zero,flags,y,scale;
 LeDecompress(gUnknown_084D7A04,(void *)0x06014800);
 CpuFastSet(gUnknown_0850FDD8,(void *)0x050002E0,8);
 i=0;
 work=gState0TransferWork.bytes;
 /* The 840-byte prefix plus 95 frames spans the complete 8192-byte array. */
 frames=(struct ContinuedPartnerFrames2CC74 *)gFrameObjects;
 zero=0;flags=0xC624;y=0xF0;
 direction=work+0xF8;
 current=&frames->objects[0];
 kind=(u8 *)frames+0x864;scale=0x40;
 do {
  /* i=0..2 indexes the three selection bytes; arithmetic is unsigned. */
  u8 *selection=work;
  selection+=0xD2;
  selection=(u8 *)(i - (0U - (u32)selection));
  if(*selection) {
   current->flags=flags;
   current->selector=0;
   current->x=0x78;
   current->y=y;
   current->scaleX=scale;
   current->scaleY=scale;
   current->palette=7;
   current->priority=y;
   current->group=0x4D00;
   kind[0]=4;
   kind[1]=0;
   current->savedX=zero;
   if(*direction&1) current->flags|=0x1000;
  }
  current++;kind+=64;i++;
 }while(i<=2);
 sub_08074DE0(0x61);
 gState0TransferWork.bytes[0xAA]++;
}
