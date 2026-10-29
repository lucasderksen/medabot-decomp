/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Continued39BFCFrame3 { u8 pad00[0xC0]; struct FrameObject frame; };
struct Continued39BFCWork { u8 pad00[0xF8]; u8 flagsF8; u8 padF9[9]; u16 word102; u16 word104; u16 word106; u8 pad108[0x4C]; u16 word154; u16 word156; u16 word158; u16 word15A; };
struct FrameWork601D4 {u8 pad00[0x46];u16 frame1;u8 pad48[0x12];u16 timer1;};
struct Dma6941C {const void *volatile source;void *volatile destination;volatile u32 control;};

extern const u16 gFrames080AFAE0[12];
extern s32 sub_0807CEC8(s32,s32);
extern void sub_0803D450(void);
extern void sub_0803D4AC(void);
extern void sub_0805FB4C(s32);

void sub_08039BFC(void);
void sub_080601D4(void);
void sub_0806941C(u8 slot);

void sub_08039BFC(void) {
 struct Continued39BFCFrame3 *frames;
 struct Continued39BFCWork *work;
 u8 mask;

 sub_0803D450();
 frames = (struct Continued39BFCFrame3 *)&gFrameObjects;
 work = (struct Continued39BFCWork *)&gState0TransferWork;
 frames->frame.unknown23[1] = work->word102;
 frames->frame.unknown2C[1] = work->word106;
 mask = 2 & work->flagsF8;
 if (mask == 0) {
  frames->frame.unknown2C[0] = mask;
  frames->frame.unknown23[2] = work->word104;
  frames->frame.screenX = work->word154;
  frames->frame.screenY = work->word156;
 } else {
  frames->frame.unknown2C[0] = 1;
  frames->frame.unknown23[2] = (0x20 - *(u8 *)&work->word104) & 0x1F;
  frames->frame.screenX = work->word158;
  frames->frame.screenY = work->word15A;
 }

 ((struct Continued39BFCFrame3 *)&gFrameObjects)->frame.unknown23[6] = 9;
 sub_0803D4AC();
}

void sub_080601D4(void) {
 u32 next;
 u8 *work;
 const u16 *frames;
 work=(u8 *)gMainContextPointer_03006F74;
 *(u16 *)(work+0x3A)+=1;
 sub_0805FB4C(*(s16 *)(work+0x3A)+8);
 next=((struct FrameWork601D4 *)gFrameObjects)->timer1+1;
 ((struct FrameWork601D4 *)gFrameObjects)->timer1=next;
 if((u16)next>0x47)((struct FrameWork601D4 *)gFrameObjects)->timer1=0;
 frames=gFrames080AFAE0;
 ((struct FrameWork601D4 *)gFrameObjects)->frame1=frames[(u16)sub_0807CEC8(((struct FrameWork601D4 *)gFrameObjects)->timer1,6)];
 if(*(s16 *)((u8 *)gMainContextPointer_03006F74+0x3A)>0xD){
  *(s8 *)gMainContextPointer_03006F74=0;gUnknown_0300137C--;
 }
}

void sub_0806941C(u8 slot) {
 u16 entries[24];
 u16 *cursor;
 s32 count;
 s32 first;
 s32 second;
 s32 third;
 struct BgScroll *scroll;
 struct Dma6941C *dma;
 count=0;
 scroll=&gBgScroll2;
 first=slot*8-0x6E00;
 second=slot*8-0x5DC0;
 third=slot*8-0x4D80;
 cursor=entries;
 do {
  cursor[0]=first+count;
  cursor[8]=second+count;
  cursor[16]=third+count;
  cursor++;
  count++;
 }while(count<=7);
 dma=(struct Dma6941C *)0x040000D4;
 dma->source=entries;
 dma->destination=(void *)((slot<<6)+0x0600F000);
 dma->control=0x80000018;
 (void)dma->control;
 scroll->y=0-((12-slot)*8);
}
