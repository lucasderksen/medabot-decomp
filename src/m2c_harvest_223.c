/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "main_menu_data.h"
#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "main.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedSetupFlag29 {u8 before[0xBD];u8 flags;};
struct ContinuedKindWork29 {u8 before[0x51];u8 kind;};
struct ContinuedPhaseWork29 {u8 before[0xAA];u8 phase;};
struct ContinuedCoordinates29 {u8 before[2];s16 x;u16 y;u8 after[58];};
struct ContinuedSetupMode29 {u8 before[0xC9];u8 mode,zero,first,second;u8 tail[0x33];};
struct ContinueStatusFlags {u8 pad[0xCF];u8 flags;u8 tail[0x30];};
struct ContinueCounterTriplet {u8 pad[0xC8];s16 values[3];};
struct AnimationWork60620 {u8 pad0[0x3A];u16 phase;};
struct Scratch60620 {u8 bytes[2400];};
struct TileWork62ED8 {u8 pad0[0x3A];s16 phase;};
struct ChoiceRecord6A024 {u8 fixed,value;u8 pad2[10];};

extern const struct ChoiceRecord6A024 gChoiceRecords6A024[];
extern const u8 gRandomBytes_083F7D80[256];
extern s32 sub_0807CD2C(s32,s32);
extern s32 sub_0807CDF8(s32,s32);
extern struct ContinueCounterTriplet gUnknown_03001800;
extern struct ContinueStatusFlags gUnknown_03000590[];
extern struct Scratch60620 gScratch60620;
extern u16 gUnknown_030018E8;
extern u32 sub_08036E54(u32);
extern u32 sub_0807CF40(u32,u32);
extern u8 gUnknown_030018D2[3];
extern u8 gUnknown_03006F84,gUnknown_03006FDC;

s32 sub_08015924(u32 bank);
void sub_0801FE64(void);
void sub_08025104(void);
void sub_0802EF5C(void);
void sub_0803536C(u32 index,u32 phase,u32 x);
void sub_080358F0(u32 bank);
s32 sub_08036D64(u32 bank,u32 kind);
void sub_080372D4(u32 bank,u32 part,s32 cap);
void sub_08060620(void);
void sub_08062ED8(void);
void sub_0806A024(void);

s32 sub_08015924(u32 bank) {

    if(bank<=2){
        u8 *setup=gSetupBuffer_03000590;
        u32 offset=bank<<8;
        struct ContinuedSetupFlag29 *record=(struct ContinuedSetupFlag29 *)(offset+(u32)setup);
        if(4&record->flags)return 1;
        return 0;
    }else{
        u8 *setup=gSetupBuffer_03000590;
        u32 offset=bank<<8;
        struct ContinuedSetupFlag29 *record=(struct ContinuedSetupFlag29 *)(offset+(u32)setup);
        if(4&record->flags)return 0;
        return 1;
    }
}

void sub_0801FE64(void) {

    struct FrameObject *frames;
    union State0TransferWork *work;
    u32 offset;
    struct ContinuedCoordinates29 *record;
    LeDecompress(gActionMotionAsset_084CF178, (void *)0x06014800);
    CpuFastSet(gActionMotionPalette_0850F918, (void *)0x050002E0, 8U);
    frames=gFrameObjects;
    work=&gState0TransferWork;
    offset=(((struct ContinuedKindWork29 *)work)->kind<<8)+0x1740;
    record=(struct ContinuedCoordinates29 *)(offset+(u32)frames);
    sub_08036FF8(0x21U,(u32)record->x,(u32)(s16)(record->y-4),8U);
    ((struct ContinuedPhaseWork29 *)work)->phase++;
}

void sub_08025104(void) {

    struct ContinuedSetupMode29 *setup;
    u8 *work,*bank;
    u32 zero;
    sub_08040CD0(0x21,1);
    setup=(struct ContinuedSetupMode29 *)gSetupBuffer_03000590;
    work=gState0TransferWork.bytes;
    bank=work+0x88;
    {u8 *mode=&setup[*bank].mode;zero=0;*mode=0x2C;}
    setup[*bank].zero=zero;
    setup[*bank].first=sub_08036E54(*(s16 *)(work+0xE8));
    setup[*bank].second=sub_08036E54(*(s16 *)(work+0xEC));
    work[0xAA]++;
}

void sub_0802EF5C(void) {

    s32 finished=0;
    u32 i=0;
    const u8 *selected=gUnknown_030018D2;
    u32 second=0x900,first=0x840;
    do{
        if(*(u8 *)(i+(u32)selected)){
            struct FrameObject *frames=gFrameObjects;
            struct FrameObject *one=(struct FrameObject *)(first+(u32)frames);
            u32 scale=one->scaleX;
            if(scale==4)finished=1;
            else{
                struct FrameObject *two;
                one->scaleX=scale-4;
                one->scaleY=one->scaleY-4;
                two=(struct FrameObject *)(second+(u32)frames);
                two->scaleX=two->scaleX-4;
                two->scaleY=two->scaleY-4;
            }
        }
        second+=64;first+=64;i++;
    }while(i<=2);
    if(finished){
        struct ContinuedPhaseWork29 *work;
        sub_08040CD0(0x21,6);
        work=(struct ContinuedPhaseWork29 *)&gState0TransferWork;
        work->phase++;
    }
}

void sub_0803536C(u32 index,u32 phase,u32 x) {
switch((phase&6)>>1){case 1:gFrameObjects[index].screenX=x+1;break;case 3:gFrameObjects[index].screenX=x-1;break;default:gFrameObjects[index].screenX=x;break;}}

void sub_080358F0(u32 bank) {

 u32 index=0;u8 *setup=gSetupBuffer_03000590;u16 *total=&gUnknown_030018E8;
 u32 shift=bank<<8;u8 *record;setup+=0x49;record=(u8 *)(shift+(u32)setup);
 do{if(record[0x10]!=0&&record[0]==0x35)*total+=record[4];record+=0x18;index++;}while(index<=2);
}

s32 sub_08036D64(u32 bank,u32 kind) {

 if(kind-0xD<=1){if(gUnknown_03000590[bank].flags&1)return 1;return 0;}
 if(kind-0xF<=1){if(gUnknown_03000590[bank].flags&8)return 1;return 0;}
 if(kind-0x11<=1){if(gUnknown_03000590[bank].flags&2)return 1;return 0;}
 if(kind-0x13<=1){if(gUnknown_03000590[bank].flags&4)return 1;return 0;}
 return 0;
}

void sub_080372D4(u32 bank,u32 part,s32 cap) {

 u8 *setup=gSetupBuffer_03000590;u8 *record=(u8 *)(part*24+(bank<<8)+(u32)setup);u32 first=record[0x4C];
 if((s32)first>=cap){s16 *out;u32 zero;gUnknown_03001800.values[0]=cap;out=&gUnknown_03001800.values[2];zero=0;*out=cap;out--;*out=zero;}
 else{s16 *out;u32 second;struct ContinueCounterTriplet *root=&gUnknown_03001800;root->values[0]=first;out=&root->values[0];second=record[0x4C];out+=2;*out=second;root->values[1]=(u32)cap-(u32)record[0x4C];}
}

void sub_08060620(void) {

    s16 temp_r5;
    s32 temp_r0;

    temp_r0 = ((struct AnimationWork60620 *)gMainContextPointer_03006F74)->phase + 1;
    ((struct AnimationWork60620 *)gMainContextPointer_03006F74)->phase = temp_r0;
    if ((u16) temp_r0 > 0x6DU) {
        ((struct AnimationWork60620 *)gMainContextPointer_03006F74)->phase = 0U;
    }
    temp_r5 = (s16) ((struct AnimationWork60620 *)gMainContextPointer_03006F74)->phase;
    if (((u32)sub_0807CDF8(temp_r5, 0xA) << 0x10) == 0) {
        const u8 *blocks=gAnimationBlocks60620;
        s16 selected=(s16)sub_0807CD2C(temp_r5,10);
        CpuSet(gScratch60620.bytes+((blocks[selected]+1)*0x1E0),(void *)0x06004020,0xF0U);
    }
}

void sub_08062ED8(void) {

    s32 temp_r0_2;
    s32 var_r1;
    s32 temp_r0;
    s32 var_r1_2;
    s32 var_r5;
    u32 var_r4;
    u32 var_r6;

    var_r1 = ((struct TileWork62ED8 *)gMainContextPointer_03006F74)->phase;
    if ((s32) var_r1 < 0) {
        var_r1 += 0x7F;
    }
    temp_r0 = var_r1 >> 7;
    switch (temp_r0) {
    case 0:
    case 1:
        var_r1_2 = (s32) ((u32)(u16) ((struct TileWork62ED8 *)gMainContextPointer_03006F74)->phase << 0x10) >> 0x15;
        break;
    case 2:
        var_r1_2 = (s32) ((u32)(u16) ((struct TileWork62ED8 *)gMainContextPointer_03006F74)->phase << 0x10) >> 0x14;
        break;
    case 3:
        var_r1_2 = (s32) ((u32)(u16) ((struct TileWork62ED8 *)gMainContextPointer_03006F74)->phase << 0x10) >> 0x13;
        break;
    case 4:
        var_r1_2 = (s32) ((u32)(u16) ((struct TileWork62ED8 *)gMainContextPointer_03006F74)->phase << 0x10) >> 0x12;
        break;
    default:
        var_r1_2 = (s32) ((u32)(u16) ((struct TileWork62ED8 *)gMainContextPointer_03006F74)->phase << 0x10) >> 0x11;
        break;
    }
    var_r1_2 &= 3;
    temp_r0_2 = (u16) ((struct TileWork62ED8 *)gMainContextPointer_03006F74)->phase - 1;
    ((struct TileWork62ED8 *)gMainContextPointer_03006F74)->phase = temp_r0_2;
    if ((s32) ((u32)temp_r0_2 << 0x10) < 0) {
        ((struct TileWork62ED8 *)gMainContextPointer_03006F74)->phase = 0x3F;
    }
    var_r6 = 0x0600E9E2;
    var_r1_2 <<= 9;
    var_r4=var_r1_2+0x0600D800;
    var_r5 = 7;
    do {
        CpuSet((const void *)var_r4, (void *)var_r6, 0xCU);
        var_r6 += 0x40;
        var_r4 += 0x40;
        var_r5 -= 1;
    } while (var_r5 >= 0);
}

void sub_0806A024(void) {

 const struct ChoiceRecord6A024 *records=gChoiceRecords6A024;
 const struct ChoiceRecord6A024 *selected=&records[gUnknown_03006FDC];
 if(selected->fixed) {gUnknown_03006F84=selected->value;return;}
 gUnknown_03006F84=sub_0807CF40(gRandomBytes_083F7D80[*(u8 *)&gFrameCounter],11);
}
