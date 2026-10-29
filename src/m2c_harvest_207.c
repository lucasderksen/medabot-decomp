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
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Continued31614Work {u8 prefix[0x58];u8 busy;u8 gap59[0x2E];u8 bank;u8 gap88[0x1E];u8 action,part;};
struct Continued31614Record {u8 prefix[5];u8 level;u8 gap06[0xBB];u8 item;u8 tail[0x3E];};
struct Continued3B0C0Pair {u16 x;u8 y,pad;};
struct Continued3B0C0Work {u8 prefix[0xF8];u8 flags;u8 gapF9[9];u16 delay,mode,arg,command;};
struct FrameRoot6280C {u8 pad0[0x1C0];u16 flags;u16 x,y,frame;u8 pad1C8[2];u8 palette;u8 pad1CB[0x11];u8 table;};
struct Context6280C {u8 pad0[6];u8 state;u8 pad7[0x12];u8 selection;};
struct Phase6280C {u8 pad0[0x84];u8 byte84;u8 pad85[0x19];u8 text9E[40];};
struct ChoiceContext6355C {u8 pad0[0x31];u8 byte31,byte32,byte33,byte34;u8 pad35[7];u16 step;};
struct Dma6BCFC {u32 source,destination,control;};
struct Dma6D7A0 {u32 source,destination,control;};
struct Graphics6D7A0 {u16 state,substate,step;};

extern const struct Continued3B0C0Pair gUnknown_083AFACC[4];
extern const u16 gSetup6D7A0_palette0807C490[110];
extern const u32 gCopy6280C08488540[8],gCopy6280C08797910[128];
extern const u32 gSetup6D7A0_map087BAD60[144],gSetup6D7A0_palette087BAFA0[48],gSetup6D7A0_map087BB7E0[160];
extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gSetup6D7A0_tiles087B67B0[],gSetup6D7A0_tiles087BB060[],gSetup6D7A0_tiles087BB2A0[],gSetup6D7A0_tiles087AEFD0[];
extern s32 sub_080688E0(void);
extern u16 gSetup6D7A0_saved0300180C[14];
extern u32 gCopy6280C0202F800[8],gCopy6280C0202F9E0[8],gCopy6280C0202F9C0[8],gCopy6280C0202F820[8];
extern u32 gPostDispatchWord_03002B70;
extern u8 gSwap6355C0202F800[128],gSwap6355C0202F880[128];
extern void sub_0801AEB4(void);
extern void sub_0803D450(void);extern void sub_0803D4AC(void);
extern void sub_08060BE4(u32,u32);
extern void sub_08062BEC(u16,u8);
extern void sub_08062C98(void);
extern void sub_08068460(u8,u8,u16);

void sub_08021564(void);
void sub_08028C68(void);
void sub_08031614(void);
void sub_0803B0C0(void);
void sub_0806280C(void);
void sub_0806355C(void);
void sub_0806BCFC(void);
void sub_0806D7A0(void);

void sub_08021564(void) {
 u8 *destination;
 u8 value;
 switch(gState0TransferWork.bytes[0x51]) {
 case 0:destination=gState0TransferWork.bytes+0xA6;value=0x1E;goto store;
 case 1:destination=gState0TransferWork.bytes+0xA6;value=0x1F;goto store;
 case 2:destination=gState0TransferWork.bytes+0xA6;value=0x20;goto store;
 case 3:destination=gState0TransferWork.bytes+0xA6;value=0x21;
 store:*destination=value;break;
 }
 if(gState0TransferWork.bytes[0x53])gState0TransferWork.bytes[0xA6]=0x71;
 gState0TransferWork.bytes[0xAA]++;
}

void sub_08028C68(void) {
 u8 *setup=gSetupBuffer_03000590,*destination;
 u32 offset=gState0TransferWork.bytes[0x87]<<8;u8 value;
 s32 kind=((u8 *)(offset+(u32)setup))[0xA8];
 switch(kind) {
 case 13:destination=gState0TransferWork.bytes+0x51;value=0;goto store;
 case 15:destination=gState0TransferWork.bytes+0x51;value=1;goto store;
 case 17:destination=gState0TransferWork.bytes+0x51;value=2;goto store;
 case 19:destination=gState0TransferWork.bytes+0x51;value=3;
 store:*destination=value;break;
 }
 gState0TransferWork.bytes[0xAA]++;
}

void sub_08031614(void){

 struct Continued31614Record *records;
 sub_0801AEB4();
 if(((struct Continued31614Work*)gState0TransferWork.bytes)->busy){((struct Continued31614Work*)gState0TransferWork.bytes)->action=0x79;gUnknown_0300137C++;}
 else {u32 firstPart=((struct Continued31614Work*)gState0TransferWork.bytes)->part;records=(void*)gSetupBuffer_03000590;
 if(firstPart==0 && records[((struct Continued31614Work*)gState0TransferWork.bytes)->bank].level<=9){((struct Continued31614Work*)gState0TransferWork.bytes)->action=0x36;gUnknown_0300137C++;}
 else if(((struct Continued31614Work*)gState0TransferWork.bytes)->part==1 && records[((struct Continued31614Work*)gState0TransferWork.bytes)->bank].level<=0x1D){((struct Continued31614Work*)gState0TransferWork.bytes)->action=0x36;gUnknown_0300137C++;}
 else if(((struct Continued31614Work*)gState0TransferWork.bytes)->part==2 && records[((struct Continued31614Work*)gState0TransferWork.bytes)->bank].level<=0x3B){((struct Continued31614Work*)gState0TransferWork.bytes)->action=0x36;gUnknown_0300137C++;}
 else if(records[((struct Continued31614Work*)gState0TransferWork.bytes)->bank].item!=0x50){((struct Continued31614Work*)gState0TransferWork.bytes)->action=0x37;gUnknown_0300137C++;}
 else gUnknown_0300137C=0x34;
 }
}

void sub_0803B0C0(void){
 u32 i;struct Continued3B0C0Work *work;u8 *mirror;const struct Continued3B0C0Pair *pair;
 sub_0803D450();i=0;work=(void*)gState0TransferWork.bytes;mirror=&work->flags;pair=gUnknown_083AFACC;
 do{struct FrameObject *root=gFrameObjects;u32 current=i+10;struct FrameObject *frame=&root[current];u32 zero=0;
 frame->flags=0xC004;frame->tableSelector=zero;frame->screenY=pair->y;frame->palette=14;frame->priority=0x80;
 frame->unknown2C[0]=work->delay;frame->byte2B=work->delay;frame->unknown23[2]=work->mode;frame->unknown23[1]=work->arg;frame->unknown23[6]=11;frame->unknown2C[1]=work->command;
 sub_08040B90(gState0NextCommands_083B6100[frame->unknown2C[1]],(u8)current);
 if(!(*mirror&2))frame->screenX=pair->x;else frame->screenX=(0xF6-pair->x)&0x1FF;
 ++pair;++i;}while(i<=3);sub_0803D4AC();
}

void sub_0806280C(void) {
    s32 var_r3;
    struct FrameObject *var_r2;
    struct FrameObject *frames;
    struct FrameRoot6280C *root;
    struct Phase6280C *phase;
    u32 mask,zero;

    sub_08060BE4(((struct Context6280C *)gMainContextPointer_03006F74)->selection, 8);
    sub_08040CD0(0U, 0x80U);
    frames=gFrameObjects;
    mask=0xBFFF;
    var_r2 = (struct FrameObject *)((u32)frames+0x300);
    var_r3 = 3;
    do {
        var_r2->flags &= mask;
        var_r2++;
        var_r3 -= 1;
    } while (var_r3 >= 0);
    zero=0;
    CpuFastSet(gUnknownWords_084E43F8, gCopy6280C0202F800, 8U);
    CpuFastSet(gMain2NameTransfer_084E43D8, gCopy6280C0202F9E0, 8U);
    CpuFastSet(gUnknownWords_084E43F8, gCopy6280C0202F9C0, 8U);
    CpuFastSet(gCopy6280C08488540, gCopy6280C0202F820, 8U);
    CpuFastSet(gCopy6280C08797910, gEquipmentPaletteShadow, 0x80U);
    phase=(struct Phase6280C *)&gState0TypedWork;
    phase->byte84 = zero;
    ((struct Context6280C *)gMainContextPointer_03006F74)->state = 1;
    gUnknown_0300137C += 1;
    *(volatile u16 *)0x04000000 |= 0x100;
    *(volatile u16 *)0x04000000 |= 0x200;
    *(volatile u16 *)0x04000000 |= 0x400;
    *(volatile u16 *)0x04000000 |= 0x800;
    *(volatile u16 *)0x04000000 |= 0x1000;
    root=(struct FrameRoot6280C *)gFrameObjects;
    root->flags = 0xC000;
    root->table = 2;
    root->palette = 1;
    root->frame = 0x1A;
    root->x = 0x98;
    root->y = zero;
    sub_08041164(phase->text9E, gPostDispatchWord_03002B70);
    sub_08040DB8(phase->text9E, 0U, 0x15, 1, 7U, 0xFU, 1U, zero);
}

void sub_0806355C(void) {
    u32 sp10[8];
    u8 *var_r4;
    u8 *var_r5;
    s32 var_r6;

    var_r5 = gSwap6355C0202F880;
    var_r4 = gSwap6355C0202F800;
    var_r6 = 3;
    do {
        CpuFastSet(var_r4, sp10, 8U);
        CpuFastSet(var_r5, var_r4, 8U);
        CpuFastSet(sp10, var_r5, 8U);
        var_r5 += 0x20;
        var_r4 += 0x20;
        var_r6 -= 1;
    } while (var_r6 >= 0);
    gUnknown_0300137C += 1;
    ((struct ChoiceContext6355C *)gMainContextPointer_03006F74)->step = 1;
    sub_08040CD0(0U, 0x80U);
    sub_08062BEC((((struct ChoiceContext6355C *)gMainContextPointer_03006F74)->byte31 * 4) + ((struct ChoiceContext6355C *)gMainContextPointer_03006F74)->byte33, 0);
    sub_08062BEC((((struct ChoiceContext6355C *)gMainContextPointer_03006F74)->byte32 * 4) + ((struct ChoiceContext6355C *)gMainContextPointer_03006F74)->byte34, 1);
    sub_08041020(gDebugMenuTextBuffer, 0U, 0, 0xA, 0x10U, 0xDU, 0U, 1U);
    sub_08041020(gDebugMenuTextBuffer + 0x14, 0x10U, 0xE, 0xA, 0x10U, 0xDU, 0U, 1U);
    sub_08074DE0(0x2AU);
    sub_08062C98();
}

void sub_0806BCFC(void) {
 u32 fill;
 volatile struct Dma6BCFC *dma;
 if(sub_080688E0()) {
  fill=0;
  dma=(volatile struct Dma6BCFC *)0x040000D4;
  dma->source=(u32)&fill;dma->destination=(u32)gFrameObjects;dma->control=0x85000800;(void)dma->control;
  gUnknown_0300137C++;
 }
}

void sub_0806D7A0(void) {
 volatile struct Dma6D7A0 *dma;
 u16 *saved;
 LZ77UnCompVram(gSetup6D7A0_tiles087B67B0,(void *)0x06000000);
 dma=(volatile struct Dma6D7A0 *)0x040000D4;
 dma->source=(u32)gSetup6D7A0_map087BAD60;dma->destination=0x06008000;dma->control=0x84000090;(void)dma->control;
 dma->source=(u32)gSetup6D7A0_palette087BAFA0;dma->destination=0x05000000;dma->control=0x84000030;(void)dma->control;
 LZ77UnCompVram(gSetup6D7A0_tiles087BB060,(void *)0x06006800);
 LZ77UnCompVram(gSetup6D7A0_tiles087BB2A0,(void *)0x06007000);
 dma->source=(u32)gSetup6D7A0_map087BB7E0;dma->destination=0x06007800;dma->control=0x840000A0;(void)dma->control;
 *(volatile u16 *)0x04000008=0xD01;*(volatile u16 *)0x0400000A=0xE03;*(volatile u16 *)0x0400000C=0x6F8A;
 LZ77UnCompVram(gSetup6D7A0_tiles087AEFD0,(void *)0x06010000);
 dma->source=(u32)gSetup6D7A0_palette0807C490;dma->destination=0x05000200;dma->control=0x80000060;(void)dma->control;
 dma->source=(u32)(gSetup6D7A0_palette0807C490+96);
 saved=gSetup6D7A0_saved0300180C;dma->destination=(u32)saved;dma->control=0x8000000E;(void)dma->control;
 sub_08068460(2,1,0);
 ((struct Graphics6D7A0 *)((u32)saved-12))->step=5;
 gUnknown_0300137C=1;
}
