/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "serial.h"
#include "state0_work.h"

struct ContinuedPhase32 {u8 before[0xAA];u8 phase;};

extern const u8 *const gState0NextCommands_083B6100[];
extern u8 gUnknown_030004C4;
extern u8 gUnknown_030018D2[3];

void sub_0802ED90(void);

void sub_0802ED90(void) {

    u32 found=0,i=0;
    u8 *selected=gUnknown_030018D2;
    const u8 *const *commands=gState0NextCommands_083B6100;
    u8 *choice=&gUnknown_030004C4;
    do{
        if(*(u8 *)(i+(u32)selected)){
            const u8 *command=commands[*choice];
            u32 index=i+0x21;
            struct FrameObject *frames;
            sub_08040BD8(command,index);
            frames=gFrameObjects;
            if(((struct FrameObject *)((index<<6)+(u32)frames))->commandStopped==0xFF)found=1;
        }
        i++;
    }while(i<=2);
    if(found){gState0TypedWork.widths.word86=0x20;((struct ContinuedPhase32 *)&gState0TransferWork)->phase++;}
}
