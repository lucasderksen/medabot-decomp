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
#include "record_helpers.h"
#include "rom_libc.h"
#include "serial.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct FamilyFrame4Q26 {u8 prefix[0x102];s16 x,y;u8 gap[0x129-0x106];u8 kind,gap2,active,tileX,clear,field2,field3;u16 delay;};
struct Work72414{u8 pad0[0x5E],setting,delay,repeat,value61;};
struct Work72CB0{u8 pad0[0x14];const u8 *script;u8 pad18[0x43],first,second,third,fourth;u8 pad5F[3],active,pad63,mode;};
struct Work74FFC{u8 pad0[0x3C];s32 duration;u16 current,target; s16 step;};

extern const s16 *const gUnknown_083CE164[];
extern const u8 gUnknown_080AF864[4];
extern const void *const gUnknown_083CEDF4[];
extern s32 sub_0807CD2C(s32,s32);
extern void sub_0801BCE4(u32,s32,s32);
extern void sub_0801BD1C(const void*,s32,s32);
extern void sub_0803D450(void);
extern void sub_0803D4AC(void);
extern void sub_080723F8(void *);
extern void sub_0807258C(void *);

u32 sub_0801A6B0(void);
void sub_08028A00(void);
void sub_08039CF8(void);
s32 sub_0803D424(void);
void sub_0805BB0C(void);
void sub_0806B718(u8 slot);
void sub_08072414(struct Work72414 *work);
void sub_08072CB0(struct Work72CB0 *work);
void sub_08074FFC(struct Work74FFC *work,s32 target,s32 duration);

u32 sub_0801A6B0(void)
{
    u32 i=0;
    u8 *setup=gSetupBuffer_03000590;
    u32 second=0xBF+(u32)setup;
    u32 first=0x40+(u32)setup;
    do{if(*(u8 *)first && *(u8 *)second)return 1;second+=0x100;first+=0x100;i++;}while(i<=5);
    return 0;
}

void sub_08028A00(void) {

    u32 i=0;
    u8 *work=gState0TransferWork.bytes;
    u8 *selected=work+0xD2;
    u8 *phase=work+0xAA;
    do{if(*(u8 *)(i+(u32)selected)){*phase+=2;return;}i++;}while(i<=2);
    work[0xAA]++;
}

void sub_08039CF8(void) {

 u8 *work;struct FamilyFrame4Q26 *frames;
 sub_0803D450();work=gState0TransferWork.bytes;
 sub_0801BCE4(0x3C,*(s16*)(work+0x10A),9);
 frames=(void*)&gFrameObjects;
 frames->field2=*(u16*)(work+0x102);frames->field3=*(u16*)(work+0x104);
 frames->active=*(u16*)(work+0x10E);frames->delay=*(u16*)(work+0x10C);frames->kind=0x10;
 sub_0801BD1C(gUnknown_083CEDF4[frames->active],0,0);
 frames->y=*(u16*)(work+0x108);
 if(!(2&work[0xF8])) {frames->x=*(u16*)(work+0x106);frames->tileX=*(u16*)(work+0x110);}
 else {u32 half=(u8)frames->field2>>1;frames->x=(30-half)-(*(u16*)(work+0x106)+half);frames->tileX=*(u16*)(work+0x110)+2;}
 gFrameObjects[4].unknown2C[1]=0;sub_0803D4AC();
}

s32 sub_0803D424(void) {

 const s16 *const *tables=gUnknown_083CE164;
 u8 *work=gState0TransferWork.bytes;
 const s16 *table=tables[work[0xF9]];
 return table[*(u16*)(work+0x100)];
}

void sub_0805BB0C(void) {

 u8 local[4];
 memcpy(local,gUnknown_080AF864,4);
 gUnknown_03000B90=(*(volatile u32 *)0x04000128<<26)>>30;
}

void sub_0806B718(u8 slot) {

 u32 zero=0;
 volatile u32 *dma=(volatile u32 *)0x040000D4;
 dma[0]=(u32)&zero;
 dma[1]=((u32)slot<<6)+(u32)gFrameObjects;
 dma[2]=0x85000010;
 (void)dma[2];
}

void sub_08072414(struct Work72414 *work) {

 if((work->setting>>4)==0){sub_080723F8(work);return;}
 work->delay=1;work->repeat=work->setting&15;work->value61=5;
}

void sub_08072CB0(struct Work72CB0 *work) {

 work->first=*work->script++;work->second=*work->script++;
 work->third=*work->script++;work->fourth=*work->script++;
 work->active=1;
 switch(work->mode){case 0:case 1:case 2:sub_0807258C(work);break;}
}

void sub_08074FFC(struct Work74FFC *work,s32 target,s32 duration) {

 s32 step=sub_0807CD2C((s32)((u32)target-work->current),duration);
 if(step){work->target=target;work->step=step;work->duration=duration;}
}
