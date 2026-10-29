/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "composite_graphics.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_debug_menu.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"
#include "utility_helpers.h"

struct ContinuedFlag33 {u8 before[0x44];u8 flags;};
struct ContinuedRecord33 {u8 before[0x2A];u8 active,kind;};
struct ContinuedWork33 {u8 before[0x8A];u8 index;u8 gap[0x1B];u8 kind;u8 gap2[3];u8 phase,delay;};
struct ContinuedPhase33 {u8 before[0xAA];u8 phase;};
struct WaitWork6F934 {u8 pad[4];u16 previous;u8 pad6[2];s32 counter;};

extern const s16 *const gUnknown_083CE164[];
#include "action_scene_data.h"
extern const u8 *const gContinuedPalettePointers_083B2704[];
extern const u8 *gUnknown_083B6188;
extern const u8 *gUnknown_083B61E0;
extern const u8 gUnknown_083CE374[];
extern s8 gUnknown_0300056F;
extern struct WaitWork6F934 gWaitWork6F934;
extern u32 sub_0803E780(void);
extern u32 sub_0807CEC8(u32,u32);
extern u8 gUnknown_02016000[0x4000];
extern u8 gUnknown_03001800[];
extern u8 gUnknown_030018D2[3];
extern void (*const gUnknown_083AECD8[])(void);
extern void (*const gUnknown_083AEEA0[])(void);
extern void (*const gUnknown_083AEF90[])(void);
extern void (*const gUnknown_083AF810[])(void);
extern void (*const gUnknown_083AFC78[])(void);
extern void sub_08032F64(void);
extern void sub_08068460(u8,u8,u16);
extern void sub_08068684(u8,u8,u16);
extern void sub_08070464(void);
void sub_08071DB8(u32,u32,u32);

void sub_0801A0A4(u32 selected,u32 kind);
void sub_0801A744(u32 value);
void sub_0801BCA0(void);
void sub_0801BCE4(u32 group,s32 entry,s32 palette);
void sub_08025F54(void);
void sub_08026080(void);
void sub_080278B8(void);
void sub_0802A440(void);
void sub_08030860(void);
void sub_08031A70(void);
void sub_08031ABC(void);
void sub_080383E8(void);
void sub_0803D450(void);
void sub_0803D538(void);
void sub_0806F934(void);
s32 sub_08071C68(u32 index);
s32 sub_08071CBC(u32 index);
s32 sub_08071D10(u32 arg0);

void sub_0801A0A4(u32 selected,u32 kind) {

    u32 i=0;
    u8 *work=gState0TransferWork.bytes;
    u32 identifier=selected+1;
    u8 *slot=work+0x45;
    do{
        if(!slot[0]){slot[0]=identifier;slot[1]=kind;break;}
        slot+=2;i++;
    }while(i<=5);
}

void sub_0801A744(u32 value) {

    if(value>2)return;
    switch(value){
    case 0:((struct ContinuedFlag33 *)&gState0TransferWork)->flags&=0xFE;break;
    case 1:((struct ContinuedFlag33 *)&gState0TransferWork)->flags&=0xFD;break;
    case 2:((struct ContinuedFlag33 *)&gState0TransferWork)->flags&=0xFB;break;
    }
}

void sub_0801BCA0(void) {

    const struct ActionGraphicPiece *initial=gUnknown_083CE600[60];
    u8 *destination=gUnknown_02016000;
    if(initial->units){
        const struct CompositeGraphicAsset *assets=gUnknown_083B2704;
        const struct ActionGraphicPiece *piece=initial;
        do{
            sub_08044B28(assets[piece->asset].data,destination);
            destination+=piece->units<<5;
            piece++;
        }while(piece->units);
    }
}

void sub_0801BCE4(u32 group,s32 entry,s32 palette) {

    const struct ActionGraphicPiece *pieces=gUnknown_083CE600[group];
    const u8 *const *assets=gContinuedPalettePointers_083B2704;
    const struct ActionGraphicPiece *piece=(const struct ActionGraphicPiece *)(((u32)entry<<2)+(u32)pieces);
    u32 tableIndex=(piece->asset*2)+1;
    const u8 *source=*(const u8 *const *)((tableIndex<<2)+(u32)assets);
    CpuFastSet(source,(void *)(((u32)palette<<5)+0x05000000u),8);
}

void sub_08025F54(void) {

    struct ContinuedWork33 *work=(struct ContinuedWork33 *)&gState0TransferWork;
    struct ContinuedRecord33 *record=(struct ContinuedRecord33 *)(work->index*8+(u32)work);
    if(record->active && record->kind==0x33){work->delay=0;work->phase++;}
    else {work->kind=0x22;work->delay=1;work->phase=2;}
}

void sub_08026080(void) {

    u32 found=0,i=0;
    const u8 **commands=&gUnknown_083B61E0;
    u32 offset=0x840;
    do{
        struct FrameObject *frames;
        sub_08040BD8(*commands,(u8)(i+0x21));frames=gFrameObjects;
        if(((struct FrameObject *)(offset+(u32)frames))->commandStopped==0xFF)found=1;
        offset+=0x40;i++;
    }while(i<=2);
    if(found){gState0TypedWork.widths.word86=0x3C;((struct ContinuedPhase33 *)&gState0TransferWork)->phase++;}
}

void sub_080278B8(void) {

    u32 found=0,i=0;
    u8 *selected=gUnknown_030018D2;
    const u8 **commands=&gUnknown_083B6188;
    do{
        if(*(u8 *)(i+(u32)selected)&0x80){
            const u8 *command=*commands;
            u32 index=i+0x21;
            u8 shortIndex=index;
            struct FrameObject *frames;
            sub_08040BD8(command,shortIndex);frames=gFrameObjects;
            if(((struct FrameObject *)((index<<6)+(u32)frames))->commandStopped==0xFF){sub_08040CD0(shortIndex,1);found=1;}
        }
        i++;
    }while(i<=2);
    if(found){sub_080158F8();sub_0801A0D0();((struct ContinuedPhase33 *)&gState0TransferWork)->phase++;}
}

void sub_0802A440(void) {

    u32 completed=0,selectedCount=0,i=0;
    u8 *selected=gUnknown_030018D2;
    u32 offset=0x8C0;
    struct FrameObject *frames=gFrameObjects;
    do{
        if(*(u8 *)(i+(u32)selected)){
            u32 index;
            struct FrameObject *frame;
            selectedCount++;index=i+0x23;frame=(struct FrameObject *)(offset+(u32)frames);frame->angle=(frame->angle+0x20)&0x3FF;
            if(sub_080355F0(index))completed++;
        }
        offset+=0x40;i++;
    }while(i<=2);
    if(selectedCount==completed){sub_08074DE0(0x2B);((struct ContinuedPhase33 *)&gState0TransferWork)->phase++;}
}

void sub_08030860(void) {

 if(sub_0803EED8()==0) {sub_0803E780();sub_080195C0();gUnknown_083AECD8[gUnknown_0300137C]();}
}

void sub_08031A70(void) {

 u8 *commands;
 void (*const *callbacks)(void);
 u8 *setup;u32 part,bank;
 sub_08032F64();commands=&gState0TransferWork.bytes[0x61];
 sub_0803F624(commands,3,0);
 callbacks=gUnknown_083AEEA0;setup=gSetupBuffer_03000590;
 part=commands[-4]*24u;bank=commands[-5];
 callbacks[setup[part+(bank<<8)+0x49]]();
}

void sub_08031ABC(void) {

 void (*const *callbacks)(void)=gUnknown_083AEF90;
 u8 *setup=gSetupBuffer_03000590;
 u8 *work=gUnknown_03001800;
 u32 part=work[0x5D]*24u;
 u32 bank=work[0x5C];
 callbacks[setup[part+(bank<<8)+0x49]]();
}

void sub_080383E8(void) {

 u32 counter=10;
 s8 *selection=&gUnknown_0300056F;
 void (*const *callbacks)(void)=gUnknown_083AF810;
 u32 offset=0xAC0;
 do {
  struct FrameObject *frame;
  *selection=counter+33;
  frame=(struct FrameObject*)((u32)gFrameObjects+offset);
  callbacks[frame->unknown23[6]]();offset+=64;counter++;
 } while(counter<=26u);
}

void sub_0803D450(void) {

 const s16 *const *tables=gUnknown_083CE164;
 u8 *work=gUnknown_03001800;
 const s16 *table=tables[work[0xF9]];
 const u8 *lengths=gUnknown_083CE374;
 u16 *cursor=(u16*)(work+0x100);
 s32 opcode=table[*cursor];
 u32 count=*(const u8*)((u32)lengths+opcode);
 u32 i=0;
 if(i<count) {
  u16 *destination=(u16*)(work+0x102);
  do {*destination=(u16)table[*cursor+i+1];destination++;i++;} while(i<count);
 }
}

void sub_0803D538(void) {

 u32 fill;
 if ((u32)(gUnknown_0300137C-16u)<=15u || sub_0803EED8()==0) {
  if (gRenderMode==2) {fill=0x200;CpuFastSet(&fill,gRenderWork->objects,0x01000100u);}
  sub_0803E780();gUnknown_083AFC78[gUnknown_0300137C]();
 }
}

void sub_0806F934(void) {

 s32 threshold=60;
 struct WaitWork6F934 *work=&gWaitWork6F934;
 volatile u16 *brightness;
 if(threshold==work->counter) {
  *(volatile u16 *)0x04000050=0xBF;
  brightness=(volatile u16 *)0x04000054;
  *brightness=0x10;
  sub_08070464();
  sub_08068460(4,4,0x7FFF);
  *brightness=0;
  work->previous=(u16)gUnknown_0300137C;
  gUnknown_0300137C=1;
 } else if(threshold<work->counter) {
  work->counter=0;
  work->previous=0x12;
  sub_08068684(4,4,0);
  gUnknown_0300137C=2;
  return;
 }
 gWaitWork6F934.counter=(s32)((u32)gWaitWork6F934.counter+1);
}

s32 sub_08071C68(u32 index) {
 u8 slot=(u8)index;

 struct FrameObject *frames=gFrameObjects;
 struct FrameObject *frame;
 s32 x;
 u32 quotient,tile;
 frame=(struct FrameObject *)((u32)frames+((u32)slot<<6));
 x=(u16)frame->screenX + 1;
 frame->screenX=x;
 ((struct FrameObject *)((u32)frames+(((u32)slot+4)<<6)))->screenX=x;
 if((*(u16 *)((u8 *)(frame) + 0x34)) <= frame->unknown1A) {
  quotient=sub_0807CEC8(frame->frameAndGroup,12);
  tile=(u16)((u16)quotient*12)+3;
  (*(u16 *)((u8 *)(frame) + 0x30))=tile;
  frame->frameAndGroup=tile;
  sub_08071DB8(8,slot,0);
 }
 return 1;
}

s32 sub_08071CBC(u32 index) {
 u8 slot=(u8)index;

 struct FrameObject *frames=gFrameObjects;
 struct FrameObject *frame;
 s32 x;
 u32 quotient,tile;
 frame=(struct FrameObject *)((u32)frames+((u32)slot<<6));
 x=(u16)frame->screenX - 1;
 frame->screenX=x;
 ((struct FrameObject *)((u32)frames+(((u32)slot+4)<<6)))->screenX=x;
 if((*(u16 *)((u8 *)(frame) + 0x34)) <= frame->unknown1A) {
  quotient=sub_0807CEC8(frame->frameAndGroup,12);
  tile=(u16)((u16)quotient*12)+3;
  (*(u16 *)((u8 *)(frame) + 0x30))=tile;
  frame->frameAndGroup=tile;
  sub_08071DB8(8,slot,0);
 }
 return 1;
}

s32 sub_08071D10(u32 arg0) {

    s32 temp_r1;
    u32 active;
    struct FrameObject *temp_r3;
 struct FrameObject *frames;
    u8 temp_r0;

    temp_r0 = (u8)arg0;
    frames=gFrameObjects;
    temp_r3 = (struct FrameObject *)((u32)frames+((u32)temp_r0<<6));
    temp_r1 = (u16) temp_r3->screenX + 1;
    temp_r3->screenX = temp_r1;
    ((struct FrameObject *)((u32)frames+(((u32)temp_r0+4)<<6)))->screenX = temp_r1;
    temp_r3->screenY = 0x32 - ((s32) ((u16) gAffineSineTable_080AE8F4[(u16) temp_r3->unknown1A >> 1] << 0x10) >> 0x14);
    if (temp_r3->screenX == 0x20) {
        temp_r3->flags = (0xF3FF & temp_r3->flags) | 0x800;
    }
    if ((u32) (*(u16 *)((u8 *)(temp_r3) + 0x34)) > (u32) temp_r3->unknown1A) {
        active=1;
        goto done;
    }
    temp_r3->flags = (0xF7FF & temp_r3->flags) | 0xC00;
    active=0;
done:
    return active;
}
