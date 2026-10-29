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
#include "record_helpers.h"
#include "serial.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedScaleFrameBlock31 {u8 before[0x848];u8 scales[0x17B8];};
struct ContinuedPhaseWork30 {u8 before[0xAA];u8 phase;};
struct ContinuedSetupFlags30 {u8 before[0xC0];u8 flags;};
struct ContinueBankPartWork {u8 pad[0x5C];u8 bank,part;};

extern const u8 *const gState0NextCommands_083B6100[];
extern struct ContinueBankPartWork gUnknown_03001800;
extern u8 gUnknown_030018D2[3];

void sub_0802CAD4(void);
void sub_0802DD98(void);
void sub_0802EFD0(void);
void sub_080332EC(void);

void sub_0802CAD4(void) {

    s32 finished=0;
    u32 i=0;
    u8 *selected=gUnknown_030018D2;
    struct ContinuedScaleFrameBlock31 *frames=(struct ContinuedScaleFrameBlock31 *)&gFrameObjects;
    u8 *cursor=frames->scales;
    do{
        if(*(u8 *)(i+(u32)selected)){
            u32 scale=cursor[0]-4;
            cursor[0]=scale;
            cursor[1]=cursor[1]-4;
            if((u8)scale==4)finished=1;
        }
        cursor+=64;i++;
    }while(i<=2);
    if(finished){
        struct ContinuedPhaseWork30 *phase;
        sub_08040CD0(0x21,3);
        phase=(struct ContinuedPhaseWork30 *)&gState0TransferWork;
        phase->phase++;
    }
}

void sub_0802DD98(void) {

    u8 *frames;
    s16 *y;
    u32 old;
    sub_08040BD8(gState0NextCommands_083B6100[105],0x21);
    frames=(u8 *)&gFrameObjects;
    y=(s16 *)(frames+0x844);
    old=*(u16 *)y;
    if(*y==0x40){
        union State0TypedWork *timer=&gState0TypedWork;
        timer->widths.word86=0;
        {
        u32 zero=0;
        frames[0x865]=0x14;
        frames[0x864]=zero;
        frames[0x868]=zero;
        frames[0x863]=zero;
        ((struct ContinuedPhaseWork30 *)&gState0TransferWork)->phase++;
        }
    }else{
        *y=(old+1)&0xFF;
    }
}

void sub_0802EFD0(void) {

    u32 i=0;
    u8 *work=gState0TransferWork.bytes;
    u8 *selected=work+0xD2;
    u8 *setup=gSetupBuffer_03000590;
    u8 *first=work+0x60;
    u32 mask=8;
    do{
        if(*(u8 *)(i+(u32)selected)){
            struct ContinuedSetupFlags30 *record=(struct ContinuedSetupFlags30 *)(((*first+i)<<8)+(u32)setup);
            u32 flags=record->flags;
            record->flags=flags|mask;
        }
        i++;
    }while(i<=2);
    work[0xAA]++;
}

void sub_080332EC(void) {
u8 *setup=gSetupBuffer_03000590;struct ContinueBankPartWork *root=&gUnknown_03001800;u32 offset=root->part*0x18;offset+=(u32)root->bank<<8;*(u8 *)(offset+(u32)setup+0x57)=0;}
