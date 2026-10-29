/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_commands.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "serial.h"
#include "state0_work.h"

struct ContinueTripletWork {u8 pad[0xC8];s16 first,middle,last;u8 gap[3];u8 flag;};
struct ContinueModeCopyWork {u8 pad[0xC34];u8 saved;u8 gap;u8 state;u8 gap2[0x5D];u8 mode;};

extern s32 sub_08036BB8(u8 *,s32,s32);
extern struct ContinueModeCopyWork gContinuedWork_030057E0;extern void sub_08050290(void);
extern struct ContinueTripletWork gUnknown_03001800;
extern u32 __fixunssfsi(float);
extern void sub_08036370(s32,s32);
extern void sub_080364A8(s32,u32);

u32 sub_08015DD0(u32 first,u32 second,u32 third);
void sub_08026A74(void);
void sub_08036B84(u32 bank,u32 part);
void sub_0804FE6C(void);

u32 sub_08015DD0(u32 first,u32 second,u32 third) {

    float ratio=(float)first/(float)second;
    u32 whole=__fixunssfsi(ratio*(float)third);
    u32 packed=((whole>>3)<<16)|(whole&7);
    if(third!=0 && packed==0)packed=1;
    return packed;
}

void sub_08026A74(void) {

    u8 *base=gState0TransferWork.bytes+0xD6;
    u8 *bank=(u8 *)((u32)base-0x4E);
    s32 total=sub_08036BB8(base,*bank,0);
    s32 mode;
    u32 bits;
    total+=sub_08036BB8(base+2,*bank,1);
    total+=sub_08036BB8(base+4,*bank,2);
    total+=sub_08036BB8(base+6,*bank,3);
    bits=base[0x22]&2;
    mode=0;
    if(!bits)mode=1;
    sub_08036370(mode,*bank);
    sub_080364A8(mode,*bank);
    if(total==4){
        u8 *phase;
        gState0TypedWork.widths.word86=0x3C;
        phase=(u8 *)((u32)base-0x2C);
        (*phase)++;
    }
}

void sub_08036B84(u32 bank,u32 part) {
struct ContinueTripletWork *root=&gUnknown_03001800;u8 *setup=gSetupBuffer_03000590;u8 *record=(u8 *)(part*24+(bank<<8)+(u32)setup);record+=0x59;root->first=*record;root->last=*record;root->flag=1;}

void sub_0804FE6C(void) {
struct ContinueModeCopyWork *root=&gContinuedWork_030057E0;if(root->state==0){root->saved=root->mode;sub_08050290();}}
