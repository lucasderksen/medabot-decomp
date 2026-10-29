/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "sound_work.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_callbacks.h"
#include "state0_debug_menu.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"
#include "utility_helpers.h"

struct InitCounterWork {u32 prefix[2];s32 counter;};

extern const s8 gUnknown_080AFCBD[3];
extern const u16 gUnknown_083AF660[];
extern const u8 *gState0NextCommands_083B6100[];
extern const u8 gUnknown_083AD51A[];
extern void sub_0801AEB4();
extern void sub_0803E894();
extern void sub_0806E10C(s32, s32);

void sub_080165B0(void);
void sub_0801F780(void);
void sub_08025C84(void);
void sub_08026BF8(void);
void sub_08031298(void);
void sub_08037424(s32 arg0);
void sub_0803E03C(void);
void sub_08064880(void);
void sub_080665B0(void);
void sub_0806D9A8(void);
s32 sub_08074F4C(s32 index);

void sub_080165B0(void) {
    u32 *output=&gUnknown_0300137C;
    const u8 *table=gUnknown_083AD51A;
    u8 *work=gState0TransferWork.bytes;
    *output=table[work[0x81]];
    }

void sub_0801F780(void) {
    const u8 **table;
    u32 scaled;
    u8 temp_r0;

    if (gFrameObjects[0xA].commandDelay == 0) {
        scaled=gFrameObjects[0xA].scaleY+4;
        gFrameObjects[0xA].scaleY=scaled;
        temp_r0=scaled;
        if (temp_r0 == 0x80) {
            gFrameObjects[0xA].commandDelay = 1;
        }
    } else if (gFrameObjects[0xA].scaleY != 0x40) {
        gFrameObjects[0xA].scaleY -= 4;
    }
    table=gState0NextCommands_083B6100;
    sub_08040BD8(table[33], 0xBU);
    if (gFrameObjects[0xB].commandStopped == 0xFF) {
        sub_08040CD0(0xAU, 2U);
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08025C84(void) {
    void *temp_r2;
    u8 *setup;

    setup=gSetupBuffer_03000590;
    sub_080374E0((*(u8 *)((u8 *)(((gState0TransferWork.bytes[0x88] << 8) + setup)) + 0xC1)), (*(s16 *)((u8 *)(&gState0TransferWork) + 0xEC)));
    gState0TransferWork.bytes[0x51] = (u8) (*(u16 *)((u8 *)(&gState0TransferWork) + 0xC8));
    temp_r2 = (gState0TransferWork.bytes[0x87] << 8) + setup;
    if (8 & (*(u8 *)((u8 *)(temp_r2) + 0xC0))) {
        sub_0803752C((*(u8 *)((u8 *)(temp_r2) + 0xC1)), 0x50, gState0TransferWork.bytes[0x51] * 2);
    } else {
        sub_0803752C((*(u8 *)((u8 *)(temp_r2) + 0xC1)), 0x50, gState0TransferWork.bytes[0x51]);
    }
    gState0TransferWork.bytes[0x52] = (u8) (*(u16 *)((u8 *)(&gState0TransferWork) + 0xC8));
    gState0TransferWork.bytes[0x64] = gState0TransferWork.bytes[0x87];
    gState0TransferWork.bytes[0x87] = gState0TransferWork.bytes[0x88];
    sub_0801AEB4();
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08026BF8(void) {
    const u8 **table;
    s32 var_r4;

    var_r4 = 0;
    if (gState0TransferWork.bytes[0xD2] != 0) {
        table=gState0NextCommands_083B6100;
        sub_08040BD8(table[30], 0xAU);
        if (gFrameObjects[0xA].commandStopped == 0xFF) {
            var_r4 = 1;
        }
    }
    if (gState0TransferWork.bytes[0xD3] != 0) {
        table=gState0NextCommands_083B6100;
        sub_08040BD8(table[30], 0xBU);
        if (gFrameObjects[0xB].commandStopped == 0xFF) {
            var_r4 = 1;
        }
    }
    if (gState0TransferWork.bytes[0xD4] != 0) {
        table=gState0NextCommands_083B6100;
        sub_08040BD8(table[30], 0xCU);
        if (gFrameObjects[0xC].commandStopped == 0xFF) {
            var_r4 = 1;
        }
    }
    if (gState0TransferWork.bytes[0xD5] != 0) {
        table=gState0NextCommands_083B6100;
        sub_08040BD8(table[30], 0xDU);
        if (gFrameObjects[0xD].commandStopped == 0xFF) {
            var_r4 = 1;
        }
    }
    if (var_r4 != 0) {
        sub_08040CD0(0xAU, 4U);
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08031298(void) {
 u32 *counter;
 if(gState0TypedWork.bytes[0x89]!=1) {
  sub_080750F0(8U);
  counter=&gUnknown_0300137C;
  *counter+=1;
 }else {
  counter=&gUnknown_0300137C;
  *counter=0x58;
 }
}

void sub_08037424(s32 arg0) {
    struct FrameObject *temp_r0,*objects;
    const u16 *table;
    u32 delta;

    objects=gFrameObjects;
    temp_r0=&objects[arg0];
    table=gUnknown_083AF660;
    delta=table[temp_r0->unknown23[0]];
    delta+=(u16)temp_r0->screenY;
    temp_r0->screenY=delta&0xFF;
    temp_r0->unknown23[0] = (temp_r0->unknown23[0] + 1) & 0x1F;
}

void sub_0803E03C(void) {
    const u8 **table;
    sub_0803E894();
    table=gState0NextCommands_083B6100;
    sub_08040BD8(table[0x75-gState0TransferWork.bytes[0x1A2]], 4U);
    if (gFrameObjects[4].commandStopped == 0xFF) {
        gFrameObjects[3].frameAndGroup = 0x8505;
        sub_08074DE0(0x54U);
        gUnknown_0300137C += 1;
    }
}

void sub_08064880(void) {
    u16 mask;
    
    if (sub_08065710((u8*)gMainContextPointer_03006F74 + 0x50) != 0) {
        gUnknown_0300137C += 1;
    
    }
    gBgScroll2.y = (((*(s16*)((u8*)gMainContextPointer_03006F74+0x3A)) * 0x10) + 0x1B8) & (mask=0x1FF);
    
    gBgScroll2.x = ((s32) (0 - (s16) (0x20 & (u16) (*(s16*)((u8*)gMainContextPointer_03006F74+0x3A)))) >> 0x1F) & 0x100;
    
    (*(s16*)((u8*)gMainContextPointer_03006F74+0x3A)) = (s16) ((u16) (*(s16*)((u8*)gMainContextPointer_03006F74+0x3A)) + 1);
    
}

void sub_080665B0(void) {
    const s8 *table;
    if (sub_08065710(gMainContextPointer_03006F74 + 0x50) != 0) {
        if ((u32) (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 5)) <= 2U) {
            table=gUnknown_080AFCBD;
            sub_08044C38((u32)table[(*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 5))]);
            return;
        }
        gMainSubstate = 0x1B;
        gUnknown_0300137C = 0;
    }
}

void sub_0806D9A8(void) {
    u8 temp_r7;
    struct InitCounterWork *work;

    work=(void*)&gState0TransferWork;
    if (work->counter == 0) {
        sub_08074B88(0U);
        sub_08048864(1U, 0xC400U, 0x210U, 1U, 3U);
        gFrameObjects[1].screenX = 0x118;
        gFrameObjects[1].screenY = 0x55;
        gFrameObjects[1].priority = 0x20;
        sub_0806E10C(3, 1);
    }
    temp_r7 = gFrameObjects[1].commandDelay;
    if (temp_r7 == 0) {
        sub_08048864(3U, 0xC000U, 0x213U, 3U, 3U);
        gFrameObjects[3].screenX = 0x12C;
        gFrameObjects[3].screenY = 0x55;
        gFrameObjects[3].priority = 0x40;
        (*(s16 *)((u8 *)(gFrameObjects) + 0xF2)) = (s16) temp_r7;
        sub_0806E10C(7, 3);
        sub_08048864(4U, 0xC400U, 0x21CU, 5U, 3U);
        gFrameObjects[4].screenX = 0x12C;
        gFrameObjects[4].screenY = 0x3C;
        gFrameObjects[4].priority = 0x10;
        (*(s16 *)((u8 *)(gFrameObjects) + 0x132)) = (s16) temp_r7;
        sub_0806E10C(8, 4);
        work=(void*)&gState0TransferWork;
        work->counter = temp_r7;
        gUnknown_0300137C = 7;
        return;
    }
    work=(void*)&gState0TransferWork;
    work->counter += 1;
}

s32 sub_08074F4C(s32 index) {
    u8 *base=(u8 *)sub_08075244();
    u8 *entry=base+index*0x74;
    if(*(s32*)(entry+0x14)==0)return -1;
    return *(u16*)(entry+0x4E);
    }
