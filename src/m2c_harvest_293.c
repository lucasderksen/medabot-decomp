/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_work.h"

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gUnknown_083C4E08[4],gUnknown_083C4E0C[4];
extern void sub_08019D9C(u32,u32,u32,u32);

void sub_08019600(u32 bank);

void sub_08019600(u32 bank) {

    u8 *setup=gSetupBuffer_03000590;
    u8 *record=(u8 *)((bank<<8)+(u32)setup);
    u32 kind=record[0xC4];
    if(kind==0)return;
    if(kind==0x1F){
        struct FrameObject *frames=gFrameObjects;
        u32 priorityRoot,priorityAddress;
        u32 index=bank*3+0x46;
        struct FrameObject *frame=(struct FrameObject *)((index<<6)+(u32)frames);
        if(frame->flags && frame->unknown23[0]==0x1F)sub_08040BD8(gState0NextCommands_083B6100[15],(u8)index);
        else sub_08040B90(gState0NextCommands_083B6100[15],(u8)(bank*3+0x46));
        sub_08041D04(gUnknown_083C4E08,gUnknown_0300052E,4);
        priorityRoot=(u32)gFrameObjects;priorityAddress=bank<<8;
        priorityAddress+=0x1740;priorityAddress+=priorityRoot;
        sub_08019D9C(bank,0,0,*(u8 *)(priorityAddress+0xB)+4);
    }else if(kind==0x26 || kind==0x29){
        struct FrameObject *frames=gFrameObjects;
        u32 priorityRoot,priorityAddress;
        u32 index=bank*3+0x46;
        struct FrameObject *frame=(struct FrameObject *)((index<<6)+(u32)frames);
        if(frame->flags && frame->unknown23[0]==kind)sub_08040BD8(gState0NextCommands_083B6100[8],(u8)index);
        else sub_08040B90(gState0NextCommands_083B6100[8],(u8)(bank*3+0x46));
        sub_08041D04(gUnknown_083C4E0C,gUnknown_0300052E,4);
        priorityRoot=(u32)gFrameObjects;priorityAddress=bank<<8;
        priorityAddress+=0x1740;priorityAddress+=priorityRoot;
        sub_08019D9C(bank,0,0,*(u8 *)(priorityAddress+0xB)+4);
    }
}
