/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern u32 ProgramEepromDwordExWord0807CC80(u16,const u16*);
extern void (*const gUnknown_083AD580[4])(void);
extern void (*const gUnknown_083AD590[5])(void);
extern void (*const gUnknown_083AD5A4[])(void);

u32 sub_0801C0BC(u32 kind);
u32 sub_0801C154(void);
u32 sub_0801C2F0(u32 kind);
void sub_0806050C(void);

u32 sub_0801C0BC(u32 kind) {

    u8 *work=gState0TransferWork.bytes;
    u8 *kindField=work+0xA2;
    void (*const *callbacks)(void);
    u32 result;
    u8 *phase;
    *kindField=kind;
    callbacks=gUnknown_083AD580;
    phase=work+0xA1;
    callbacks[*phase]();
    if(*phase!=3)result=0;else{*phase=0;result=1;}return result;
}

u32 sub_0801C154(void) {

    void (*const *callbacks)(void)=gUnknown_083AD590;
    u8 *work=gState0TransferWork.bytes;
    u32 result;
    u8 *phase=work+0x9C;
    callbacks[*phase]();
    if(*phase!=4)result=0;else{*phase=0;result=1;}return result;
}

u32 sub_0801C2F0(u32 kind) {

    u8 *work=gState0TransferWork.bytes;
    work[0x9D]=kind;
    gUnknown_083AD5A4[work[0x9C]]();
    if(work[0x9E]!=0)return 1;return 0;
}

void sub_0806050C(void) {

    u16 sp0[4];
    u32 sp8;
    s32 var_r4;
    u16 temp_r5;
    u32 temp_r0;

    temp_r0 = sub_08074FA4(4U);
    if (temp_r0 == 0) {
        *(volatile u16 *)0x04000208 = (s16) temp_r0;
        temp_r5 = *(volatile u16 *)0x04000200;
        *(volatile u16 *)0x04000200 = 0x2020;
        *(volatile u16 *)0x04000208 = 1;
        sp8 = temp_r0;
        CpuSet(&sp8, sp0, 0x05000002U);
        for(var_r4=0;var_r4<=3;var_r4++){
            u32 result=ProgramEepromDwordExWord0807CC80(0U,sp0);
            if(result==0)break;
        }
        *(volatile u16 *)0x04000200 = (u16) (temp_r5 | *(volatile u16 *)0x04000200);
        gMainState = 3;
        gMainSubstate = 2;
        gUnknown_0300137C = 0;
        gMain2Byte_03007008 = 1;
    }
}
