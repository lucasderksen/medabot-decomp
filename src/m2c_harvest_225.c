/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_blend_work.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "serial.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"
#include "utility_helpers.h"

struct ContinuedSelectorWork29 {u8 before[0x81];u8 choice;u8 unknown;u8 mode;};
struct ContinueFrameUpdate {u8 pad[0x29];u8 action;u8 unknown2A,timer,enable,status,phase,unknown2F;u16 counter;u8 tail[0xE];};
struct ContinueFrameInput {u8 pad[0x102];s16 slot;u16 counter,timer,status,phase;};
struct TileWork62D60 {u8 pad0[0x3A];s16 phase;};
struct Dma6E9E0 {u32 source,destination,control;};
struct SoundRoot72734 {u8 pad0[0x690];u8 tables[2][0x48];};
struct SoundWork72734 {u8 pad0[0x34];u32 increment,position;u8 pad3C[12];u16 pitch;u8 pad4A[12];u8 initialOffset,duration,amount,offset,halfDuration;u8 pad5B[9];u8 kind;};

extern struct ContinueFrameInput gUnknown_03001800;
extern struct ContinueFrameUpdate gUnknown_03002C30[128];
extern struct SoundRoot72734 *gSoundRoot72734;
extern u32 sub_08073C3C(const void *,s32);
extern u32 sub_0807CEC8(u32,u32);
extern u8 gUnknown_0300049E;
extern u8 gUnknown_0300199A[6];
extern void sub_0803D450(void);extern void sub_0803D4AC(void);

void sub_08005000(void);
void sub_0801630C(void);
void sub_08039A2C(void);
void sub_0803E8EC(void);
void sub_08062D60(void);
void sub_0806E9E0(void);
void sub_08072734(struct SoundWork72734 *work);

void sub_08005000(void) {

    struct State0Record8 *temp_r3;
    u32 var_r5;
    u32 var_r7;
    u32 var_r8;
    const u8 *var_r6;
    const u8 *kind;

    var_r5 = 0;
    var_r8 = 0x0A000000;
    var_r7 = 0xA;
    var_r6 = gUnknownBytes_083AC5BB;
    kind=&gUnknown_0300049E;
    do {
        struct State0Record8 *records=gUnknownRecords_030017A0;
        temp_r3 = (struct State0Record8 *)((var_r5<<3)+(u32)records);
        if (temp_r3->unknown00[0] != 0) {
            sub_08042E58((u32) temp_r3->byte3, (u32) temp_r3->byte4, (u32) temp_r3->byte5, (u32) temp_r3->byte6, var_r5, var_r7, (u32) *var_r6, (u32) var_r6[1], (u32) *kind, 1U, (u32) gUnknownBytes_083AC5B2[var_r5]);
        } else {
            sub_08040D0C((u8) (var_r8 >> 0x18), 4U);
        }
        var_r8 += 0x04000000;
        var_r7 += 4;
        var_r6 += 2;
        var_r5 += 1;
    } while (var_r5 <= 8U);
}

void sub_0801630C(void) {

    struct ContinuedSelectorWork29 *work=(struct ContinuedSelectorWork29 *)&gState0TransferWork;
    if(work->mode==0){
        struct FrameObject *frames=gFrameObjects;
        u8 *choice=&work->choice;
        struct FrameObject *initial=&frames[*choice];
        struct FrameObject *frame;
        
        
        initial->flags|=0x20;
        frames[*choice].commandStopped++;
        frame=&frames[*choice];
        if(8&frame->commandStopped){frame->scaleY=0x50;frames[*choice].scaleX=0x50;}
        else{frame->scaleY=0x40;frames[*choice].scaleX=0x40;}
    }
}

void sub_08039A2C(void) {

 struct ContinueFrameUpdate *frames;struct ContinueFrameInput *work;sub_0803D450();frames=gUnknown_03002C30;work=&gUnknown_03001800;
 ((struct ContinueFrameUpdate *)(((u32)((s32)work->slot+5)<<6)+(u32)frames))[0].counter=work->counter;((struct ContinueFrameUpdate *)(((u32)((s32)work->slot+5)<<6)+(u32)frames))[0].timer=work->timer;((struct ContinueFrameUpdate *)(((u32)((s32)work->slot+5)<<6)+(u32)frames))[0].enable=0;
 ((struct ContinueFrameUpdate *)(((u32)((s32)work->slot+5)<<6)+(u32)frames))[0].status=work->status;((struct ContinueFrameUpdate *)(((u32)((s32)work->slot+5)<<6)+(u32)frames))[0].phase=work->phase;((struct ContinueFrameUpdate *)(((u32)((s32)work->slot+5)<<6)+(u32)frames))[0].action=0x18;sub_0803D4AC();}

void sub_0803E8EC(void) {
u32 index=0;u8 *choices=gUnknown_0300199A;u32 position=2;do{
 sub_08042698(7,2,4,position,*(volatile u16 *)0x0400000A,((u32)*(u8 *)(index+(u32)choices)*0xE0000u+0x33800000u)>>16);
 position+=2;index++;}while(index<=5);}

void sub_08062D60(void) {

    s32 temp_r0_2;
    s32 var_r1;
    s32 temp_r0;
    s32 var_r1_2;
    s32 var_r5;
    u32 var_r4;
    u32 var_r6;

    var_r1 = ((struct TileWork62D60 *)gMainContextPointer_03006F74)->phase;
    if ((s32) var_r1 < 0) {
        var_r1 += 0x7F;
    }
    temp_r0 = var_r1 >> 7;
    switch (temp_r0) {                              /* irregular */
    case 0:
        var_r1_2 = (s32) ((u32)(u16) ((struct TileWork62D60 *)gMainContextPointer_03006F74)->phase << 0x10) >> 0x11;
        break;
    case 1:
        var_r1_2 = (s32) ((u32)(u16) ((struct TileWork62D60 *)gMainContextPointer_03006F74)->phase << 0x10) >> 0x12;
        break;
    case 2:
        var_r1_2 = (s32) ((u32)(u16) ((struct TileWork62D60 *)gMainContextPointer_03006F74)->phase << 0x10) >> 0x13;
        break;
    case 3:
        var_r1_2 = (s32) ((u32)(u16) ((struct TileWork62D60 *)gMainContextPointer_03006F74)->phase << 0x10) >> 0x14;
        break;
    default:
        var_r1_2 = (s32) ((u32)(u16) ((struct TileWork62D60 *)gMainContextPointer_03006F74)->phase << 0x10) >> 0x15;
        break;
    }
    var_r1_2 &= 3;
    temp_r0_2 = (u16) ((struct TileWork62D60 *)gMainContextPointer_03006F74)->phase - 1;
    ((struct TileWork62D60 *)gMainContextPointer_03006F74)->phase = temp_r0_2;
    if ((s32) ((u32)temp_r0_2 << 0x10) < 0) {
        ((struct TileWork62D60 *)gMainContextPointer_03006F74)->phase = 0x3F;
    }
    var_r6 = 0x0600E9E2;
    var_r1_2 <<=9;
    var_r4 = var_r1_2 + 0x0600D800;
    var_r5 = 7;
    do {
        CpuSet((const void *)var_r4, (void *)var_r6, 0xCU);
        var_r6 += 0x40;
        var_r4 += 0x40;
        var_r5 -= 1;
    } while (var_r5 >= 0);
}

void sub_0806E9E0(void) {

    u32 sp20;
    u32 mode;
    volatile struct Dma6E9E0 *dma;

    mode=gRenderMode;
    if (mode == 2) {
        sp20 = 0x200;
        dma=(volatile struct Dma6E9E0 *)0x040000D4;
        dma->source=(u32)&sp20;
        dma->destination=(u32)gRenderWork->objects;
        dma->control=0x85000100;
        (void)dma->control;
        sub_080446B4(0U, 0x2BU, 0x2BU, 0x2BU, 0x2BU, 0x70U, 0x50U, mode, 0xCU, 0U, 1U, 0U);
        sub_08044A3C(0U, 0x2CU, 0x2BU);
    }
}

void sub_08072734(struct SoundWork72734 *work) {

 const void *table;
 u32 high,low;
 u8 var_r0,initial;
 u32 zero;
 u8 *amount=&work->amount,*offset,*duration;
 var_r0=*amount;
 offset=&work->offset;
 duration=&work->halfDuration;
 if (var_r0==0) {*offset=var_r0;*duration=var_r0;work->increment=var_r0;work->position=var_r0;}
 else {
  table=gSoundRoot72734->tables[0];
  if(work->kind!=4)table=gSoundRoot72734->tables[1];
  initial=work->initialOffset;
  zero=0;
  *offset=initial;
  *duration=work->duration>>1;
  high=sub_08073C3C(table,work->pitch+2);
  low=sub_08073C3C(table,work->pitch);
  work->increment=sub_0807CEC8((high-low)* *amount,*duration);
  work->position=zero;
 }
}
