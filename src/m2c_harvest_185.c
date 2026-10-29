/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedPartnerFrame25378 {u16 flags;s16 x,y;u16 group;u8 scaleX,scaleY,palette,priority;u8 gapC[0xC];u16 angle,unknown1A;u8 selector;u8 gap1D[6];u8 byte23,kind;u8 gap25[0xB];u16 savedX;s16 savedY;u8 gap34[0xC];};
struct ContinuedPartnerFrames25378 {u8 prefix[0x840];struct ContinuedPartnerFrame25378 first,second;};

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gUnknown_084D8AC8[];
extern const u8 gUnknown_0850FF38[64];

void sub_080264E4(void);
void sub_0805FC94(void);

void sub_080264E4(void) {
 struct ContinuedPartnerFrames25378 *frames;
 u8 *work;
 LeDecompress(gUnknown_084D8AC8,(void *)0x06014800);
 CpuFastSet(gUnknown_0850FF38,(void *)0x050002C0,16);
 frames=(struct ContinuedPartnerFrames25378 *)gFrameObjects;
 frames->first.flags=0xC404;
 frames->first.selector=0;
 work=gState0TransferWork.bytes;
 frames->first.x=(u16)gFrameObjects[work[0x87]*4+0x5D].screenX;
 frames->first.y=(u16)gFrameObjects[work[0x87]*4+0x5D].screenY-4;
 frames->first.palette=6;
 frames->first.priority=0xE0;
 sub_08040B90(gState0NextCommands_083B6100[0x4B],0x21);
 frames->second.flags=0xC404;
 frames->second.selector=0;
 frames->second.x=(u16)gFrameObjects[work[0x87]*4+0x5D].screenX;
 frames->second.y=(u16)gFrameObjects[work[0x87]*4+0x5D].screenY-6;
 frames->second.palette=7;
 frames->second.priority=0xF0;
 sub_08040B90(gState0NextCommands_083B6100[0x4C],0x22);
 sub_08074DE0(0x5E);
 gState0TypedWork.widths.word86=0;
 work[0xAA]++;
}

void sub_0805FC94(void) {
 u32 fill=0;
 CpuFastSet(&fill,(void *)0x06000000,0x01006000U);
 sub_08059E50();sub_080415BC();
 *(volatile u16 *)0x04000040=0xF0;
 *(volatile u16 *)0x04000044=0x80;
 *(volatile u16 *)0x04000048=0x3F3F;
 *(volatile u16 *)0x0400004A=0x2F;
 *(volatile u16 *)0x04000000=0x2060;
 *(volatile u16 *)0x04000050=0x2BF;
 sub_08074B88(0x12U);
 *(volatile u16 *)0x04000054=0x10;
 gUnknown_0300137C++;
}
