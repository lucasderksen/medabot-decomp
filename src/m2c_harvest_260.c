/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_effects.h"
#include "effect_work.h"
#include "frame.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "utility_helpers.h"

struct FamilyWork38F84 {u8 pad[0x87];u8 first,second;u8 gap89[0x1E];u8 part;u8 gapA8[0x40];u16 remaining;u8 gapEA[4];u16 sum;u8 gapF0[2];u16 copy;};

extern s32 sub_08038E9C(void);
extern s32 sub_0807CD2C(s32, s32);
extern struct FamilyWork38F84 gUnknown_03001800;
extern u8 gUnknown_02023078;
extern void sub_08035844(u32 index);

s32 sub_08038F84(void);
void sub_080617E0(void);
void sub_080627A0(void);
void sub_08067314(s32 arg0, s32 arg1);

s32 sub_08038F84(void) {

 struct FamilyWork38F84 *work=&gUnknown_03001800;
 u16 *sum=&work->sum;
 u8 *setup;
 u8 *bank;
 u8 flags;
 *sum=0;setup=gSetupBuffer_03000590;bank=&work->second;
 flags=setup[((u32)*bank<<8)+0xBC];
 {u32 mask=4;mask&=flags;
 if(!mask) {
  sub_08035844(*bank);
  *sum=*sum+setup[((u32)*bank<<8)+0xA3];
  if(!(setup[((u32)*bank<<8)+0xBC]&8u))sub_08035754((s16*)sum,8);
  if(sub_08038E9C()!=0)return 1;
  sub_08035754((s16*)&work->remaining,(s16)*sum);
  { u32 remaining=work->remaining;work->copy=remaining;
  {
  remaining<<=16;
  if(remaining==0) {
   u32 part=work->part*24u;
   u32 offset=(u32)work->first<<8;
   u32 kind=setup[part+offset+0x49];
   if(kind==6)return 0;
   else if(kind==7)return 0;
   else if(!(setup[offset+0xD6]&2u)) {
    u8 *record=setup+((u32)*bank<<8);u8 oldFlags=record[0xBC];u32 newFlags=16;newFlags|=oldFlags;record[0xBC]=newFlags;return 1;
   }
  }
  }
  }
 }
 }
 return 0;
}

void sub_080617E0(void) {

    u16 temp_r0;
    u8 temp_r3;

    temp_r0 = (*(u16 *)((u8 *)(gMainContextPointer_03006F74) + 2));
    (*(u16 *)((u8 *)(gMainContextPointer_03006F74) + 2)) = (u16) (temp_r0 + 0xFFFF);
    temp_r3 = (u8) temp_r0;
    if ((u32) gFrameObjects[8].scaleX <= 0x3FU) {
        gFrameObjects[8].scaleX += 4;
        gFrameObjects[8].scaleY += 4;
    } else {
        gFrameObjects[8].scaleY=0x40;
    }
    if (temp_r3 != 0) {
        *(volatile u16 *)0x04000052 = (temp_r3 << 8) | (0x10 - temp_r3);
        return;
    }
    *(volatile u16 *)0x04000052 = 0x10;
    sub_0803FB0C();
    gUnknown_0300137C = 4;
}

void sub_080627A0(void) {

 u32 inventoryRoot;
    if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
        sub_0803F684(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
        sub_0803F998(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    sub_08044BA8((u32) (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x19)), (u32)(inventoryRoot=0x02040000U, *(u16 *)(inventoryRoot + (((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x1A)) + gUnknown_02023078) * 8))));
    gMainState = 0;
}

void sub_08067314(s32 arg0, s32 arg1) {

    u16 sp0[32];
    s32 sp40;
    s32 temp_r0;
    s32 var_r4;
    u16 *var_r1;
    u16 temp_r7;

    sp40 = 0;
    CpuFastSet(&sp40, &sp0[0], 0x01000010U);
    if (arg1 <= 0xD) {
        temp_r7 = *(u16 *)0x0600DD3E;
        var_r4 = 0;
        if (var_r4 < arg0) {
            temp_r0 = sub_0807CD2C(arg1 * 0x1D, 0xD);
            var_r1=(u16 *)(((u32)temp_r0<<1)+(u32)sp0);
            do {
                if ((s32) (temp_r0 - var_r4) >= 0) {
                    *var_r1 = temp_r7;
                }
                var_r1=(u16 *)((u32)var_r1-2U);
                var_r4 += 1;
            } while (var_r4 < arg0);
        }
    }
    if (sp0[0] == 0) {
        sp0[0]=*(u16*)0x0600D8C0;
    } else {
        sp0[0]=*(u16*)0x0600D940;
    }
    CpuFastSet(&sp0[0], (void *)(((((u16) *(volatile u16 *)0x04000008 >> 8) & 0x1F) << 0xB) + 0x06000400), 0x10U);
}
