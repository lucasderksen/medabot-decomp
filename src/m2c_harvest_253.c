/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "action_scene_data.h"
#include "continued_scene_records.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "graphics.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern const u8 gUnknown_083CEE88[128];
extern const u8 gUnknown_083CEF08[128];
extern const u8 gUnknown_083CEF88[128];
extern const u8 gUnknown_083CF008[64];
extern const u8 gUnknown_083CF048[64];
extern const u8 gUnknown_083CF088[64];
extern const u8 gUnknown_083CF0C8[64];
extern const u8 gUnknown_083CF108[64];
extern const u8 gUnknown_083CF148[64];
extern const u8 gUnknown_083CF188[64];
extern const u8 gUnknown_083CF1C8[64];
extern const u8 gUnknown_083CF208[64];
extern const u8 gUnknown_083CF248[64];
extern const u8 gUnknown_083CF288[64];
extern const u8 gUnknown_083CF2C8[64];
extern u8 gContinuedWork_030057E0[];

void sub_08018A18(void);
u32 sub_08037578(u32 kind,u32 selection);

void sub_08018A18(void)
{
    u8 *shared=gContinuedWork_030057E0;
    u8 *value=(u8 *)(0xC2E + (u32)shared);
    if((*value&0xF0)==0x20){
        u32 i=0;
        u8 *setup=gSetupBuffer_03000590;
        u32 value=0x50;
        u32 out=0x3C1+(u32)setup;
        do{*(u8 *)out=value;out+=0x100;i++;}while(i<=2);
    }
}

u32 sub_08037578(u32 kind,u32 selection) {
u32 value=0;sub_080424B8();switch(kind){
case 0:switch(selection){
case 0:value=gUnknown_083CEE88[gState0TypedWork.bytes[0x8C]&127u];break;
case 1:value=gUnknown_083CEF08[gState0TypedWork.bytes[0x8C]&127u];break;
case 2:value=gUnknown_083CEF88[gState0TypedWork.bytes[0x8C]&127u];break;
}break;
case 1:switch(selection){
case 0:value=gUnknown_083CF008[gState0TypedWork.bytes[0x8C]&63u];break;
case 1:value=gUnknown_083CF048[gState0TypedWork.bytes[0x8C]&63u];break;
case 2:value=gUnknown_083CF088[gState0TypedWork.bytes[0x8C]&63u];break;
}break;
case 2:switch(selection){
case 0:value=gUnknown_083CF0C8[gState0TypedWork.bytes[0x8C]&63u];break;
case 1:value=gUnknown_083CF108[gState0TypedWork.bytes[0x8C]&63u];break;
case 2:value=gUnknown_083CF148[gState0TypedWork.bytes[0x8C]&63u];break;
}break;
case 3:switch(selection){
case 0:value=gUnknown_083CF188[gState0TypedWork.bytes[0x8C]&63u];break;
case 1:value=gUnknown_083CF1C8[gState0TypedWork.bytes[0x8C]&63u];break;
case 2:value=gUnknown_083CF208[gState0TypedWork.bytes[0x8C]&63u];break;
}break;
default:switch(selection){
case 0:value=gUnknown_083CF248[gState0TypedWork.bytes[0x8C]&63u];break;
case 1:value=gUnknown_083CF288[gState0TypedWork.bytes[0x8C]&63u];break;
case 2:value=gUnknown_083CF2C8[gState0TypedWork.bytes[0x8C]&63u];break;
}break;
}return value;}
