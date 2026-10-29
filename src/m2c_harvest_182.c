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
#include "coordinate_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedPart1F3F0 {u8 prefix[7];u8 active;u8 tail[0x10];};
struct ContinuedSetup1F3F0 {u8 prefix[0x48];struct ContinuedPart1F3F0 parts[4];u8 gapA8[0x2E];u8 flags;u8 tail[0x29];};
struct ContinuedPartnerFrame25378 {u16 flags;s16 x,y;u16 group;u8 scaleX,scaleY,palette,priority;u8 gapC[0xC];u16 angle,unknown1A;u8 selector;u8 gap1D[6];u8 byte23,kind;u8 gap25[0xB];u16 savedX;s16 savedY;u8 gap34[0xC];};
struct ContinuedPartnerFrames25378 {u8 prefix[0x840];struct ContinuedPartnerFrame25378 first,second;};

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gUnknown_084D7638[];
extern const u8 gUnknown_0850FD78[32];
extern s32 gUnknown_03006F88;
extern s32 gUnknown_03006FE0[3];
extern s32 gUnknown_03006FF8[2];
extern s32 gUnknown_03007000[2];
extern u32 sub_08033184(u32);
extern u8 gUnknown_03006FEC[3];
extern u8 gUnknown_03006FF0[3];
extern void sub_08036CCC(u32,u32,s32);
extern void sub_08069E78(void);
extern void sub_0806B530(u8,u8,u8,u8);

void sub_0801F3F0(void);
void sub_080237C8(void);
void sub_08024AF4(void);
s32 sub_0806A654(void);

void sub_0801F3F0(void) {
    struct ContinuedSetup1F3F0 *setup=(struct ContinuedSetup1F3F0 *)gSetupBuffer_03000590;
    u8 *work=gState0TransferWork.bytes;
    u32 selected;
    u32 bankOffset=work[0x87]<<8;
    if(((((struct ContinuedSetup1F3F0 *)((u32)setup+bankOffset))->flags&2) || *(u8 *)(((work[0xA7]*0x18)+bankOffset)+(u32)setup+0x4F)!=0) && *(u16 *)(work+0xCA)!=0 && (selected=sub_08033184(work[0x88]))!=0) {
        selected-=1;
        work[0xD0]=selected;
        work[0x8B]=selected;
        sub_08036CCC(work[0x88],work[0xD0],*(u16 *)(work+0xCA));
        work[0xAA]=0x4A;
    } else work[0xAA]++;
}

void sub_080237C8(void) {
    struct ContinuedPartnerFrames25378 *frames;
    u8 *work;
    union State0TypedWork *typed;
    LeDecompress(gUnknown_084D7638,(void *)0x06014800);
    CpuFastSet(gUnknown_0850FD78,(void *)0x050002E0,8);
    frames=(struct ContinuedPartnerFrames25378 *)gFrameObjects;
    frames->first.flags|=0x220;
    frames->first.scaleX=0x40;
    frames->first.scaleY=0x40;
    frames->first.angle=0;
    work=gState0TransferWork.bytes;
    frames->first.savedX=(u16)gFrameObjects[work[0x88]*4+0x5D].screenX;
    frames->first.savedY=(u16)gFrameObjects[work[0x88]*4+0x5D].screenY-4;
    frames->first.kind=6;
    typed=&gState0TypedWork;
    typed->bytes[0x84]=0x42;
    sub_08040B90(gState0NextCommands_083B6100[0x42],0x21);
    typed->widths.word86=0x3C;
    work[0xAA]++;
}

void sub_08024AF4(void) {
    struct ContinuedPartnerFrames25378 *frames;
    u8 *work;
    sub_08040D0C(0x21,1);
    frames=(struct ContinuedPartnerFrames25378 *)gFrameObjects;
    frames->second.flags=0xC404;
    frames->second.selector=0;
    work=gState0TransferWork.bytes;
    frames->second.x=(u16)gFrameObjects[work[0x88]*4+0x5D].screenX;
    frames->second.y=(u16)gFrameObjects[work[0x88]*4+0x5D].screenY-4;
    frames->second.palette=7;
    frames->second.priority=0xE0;
    frames->second.byte23=0;
    switch(work[0x8B]) {
    case 1:frames->second.group=0x4E02;break;
    case 2:frames->second.group=0x4E03;break;
    default:frames->second.group=0x4E01;break;
    }
    sub_08074DE0(0x6A);
    gState0TransferWork.bytes[0xAA]++;
}

s32 sub_0806A654(void) {
    switch (gUnknown_03006F88) {
    case 0:
        sub_08069E78();
        sub_0806B530(0,5,0,0);
        gUnknown_03006F88++;
        break;
    case 1:
        if (gFrameObjects[0].unknown1A == 180) {
            sub_08074DE0(0x42);
            sub_08043240(0x26,12);
            sub_08043240(0x32,12);
            sub_08043240(0x3E,12);
            sub_0806B530(1,10,0,0);
            sub_0806B530(2,10,1,0);
            sub_0806B530(3,10,2,0);
            gUnknown_03006FF8[1] = 0;
            gUnknown_03006FF8[0] = 0;
            gUnknown_03007000[1] = 0;
            gUnknown_03007000[0] = 0;
            gUnknown_03006FE0[2] = 0;
            gUnknown_03006FE0[1] = 0;
            gUnknown_03006FE0[0] = 0;
            gUnknown_03006FEC[2] = 32;
            gUnknown_03006FEC[1] = 32;
            gUnknown_03006FEC[0] = 32;
            gUnknown_03006FF0[2] = 0;
            gUnknown_03006FF0[1] = 0;
            gUnknown_03006FF0[0] = 0;
            return 1;
        }
        break;
    }
    return 0;
}
