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
#include "state0_callbacks.h"
#include "state0_work.h"
#include "tile_text.h"

struct Continued23118Frame33 { u8 pad00[0x840]; struct FrameObject frame; };
struct ContinuedPartnerFrame25378 {u16 flags;s16 x,y;u16 group;u8 scaleX,scaleY,palette,priority;u8 gapC[0xC];u16 angle,unknown1A;u8 selector;u8 gap1D[6];u8 byte23,kind;u8 gap25[0xB];u16 savedX;s16 savedY;u8 gap34[0xC];};
struct ContinuedPartnerFrames25378 {u8 prefix[0x840];struct ContinuedPartnerFrame25378 first,second;};
struct Continued25974Frame34 { u8 pad00[0x880]; struct FrameObject frame; };

extern void sub_08037424(u32);

void sub_08023118(void);
void sub_08025378(void);
void sub_08025974(void);

void sub_08023118(void) {
 struct Continued23118Frame33 *frames;
 u8 *work;
 u8 *bank;
 frames = (struct Continued23118Frame33 *)&gFrameObjects;
 frames->frame.flags = 0xC604;
 frames->frame.tableSelector = 0;
 work = gState0TransferWork.bytes;
 bank = work + 0x87;
 frames->frame.screenX = (u16)gFrameObjects[*bank * 4 + 0x5D].screenX;
 frames->frame.screenY = (u16)gFrameObjects[*bank * 4 + 0x5D].screenY - 4;
 frames->frame.palette = 6;
 frames->frame.priority = 0xF0;
 frames->frame.frameAndGroup = 0x4800;
 frames->frame.scaleX = 0x40;
 frames->frame.scaleY = 0x40;
 frames->frame.angle = 0;
 frames->frame.unknown2C[1] = 0;
 sub_08074DE0(0x4C);
 work[0xAA]++;
}

void sub_08025378(void) {
    struct ContinuedPartnerFrames25378 *frames;
    u8 *work;
    sub_08037424(0x21);
    frames=(struct ContinuedPartnerFrames25378 *)gFrameObjects;
    frames->second.flags=0xC604;
    frames->second.selector=0;
    work=gState0TransferWork.bytes;
    frames->second.x=(u16)gFrameObjects[work[0x88]*4+0x5D].screenX;
    frames->second.y=(u16)gFrameObjects[work[0x88]*4+0x5D].screenY-4;
    frames->second.scaleX=1;
    frames->second.scaleY=1;
    frames->second.palette=7;
    frames->second.priority=0xE0;
    frames->second.group=0x5001;
    frames->second.savedX=(u16)gFrameObjects[work[0x87]*4+0x5D].screenX;
    frames->second.savedY=(u16)gFrameObjects[work[0x87]*4+0x5D].screenY-4;
    frames->second.kind=3;
    frames->first.savedX=(u16)gFrameObjects[work[0x87]*4+0x5D].screenX;
    frames->first.savedY=(u16)gFrameObjects[work[0x87]*4+0x5D].screenY-4;
    frames->first.kind=3;
    sub_08074DE0(0x6F);
    work[0xAA]++;
}

void sub_08025974(void) {
 struct Continued25974Frame34 *frames;
 u8 *work;
 u32 zero;
 sub_08040D0C(0x21, 1);
 frames = (struct Continued25974Frame34 *)&gFrameObjects;
 frames->frame.flags = (zero = 0, 0xC404);
 frames->frame.tableSelector = zero;
 work = gState0TransferWork.bytes;
 frames->frame.screenX = (u16)gFrameObjects[work[0x88] * 4 + 0x5D].screenX;
 frames->frame.screenY = (u16)gFrameObjects[work[0x88] * 4 + 0x5D].screenY - 4;
 frames->frame.palette = 7;
 frames->frame.priority = 0xE0;
 frames->frame.unknown23[0] = zero;
 frames->frame.frameAndGroup = 0x5201;
 sub_08074DE0(0x6A);
 work[0xAA]++;
}
