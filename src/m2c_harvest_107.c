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
#include "graphics.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Frame4Backing {
 u8 prefix[0x102];s16 x,y;
 u8 gap[0x129-0x106];u8 kind;u8 gap2;u8 active;
 u8 tileX,clear,field2,field3;u16 delay;
};

extern const u8 *gState0NextCommands_083B6100[];
extern const u8 *gUnknown_083C47EC[];
#include "action_scene_data.h"
extern void sub_0801AEB4();
extern void sub_0801AEF4();
extern void sub_0801BCE4(u32, s32, s32);
extern void sub_0801BD1C(const void *, s32, s32);
extern void sub_0801C2F0(s32);
s32 sub_0801AFB8(u8);

void sub_08015F24(void);
void sub_08025D6C(void);
void sub_0803A5CC(void);
void sub_0803ADFC(void);
void sub_0803D3C0(void);

void sub_08015F24(void) {
    const u8 **table;
    sub_08040D0C(0x1EU, 0xBU);
    table=gUnknown_083C47EC;
    sub_08041D04(table[gState0TransferWork.bytes[0x81]], gDebugMenuTextBuffer, 0xCU);
    sub_08040DB8(gDebugMenuTextBuffer, 0x1EU, 0x15, 0x11, 8U, 0xEU, 0U, 1U);
}

void sub_08025D6C(void) {
    const u8 **table;
    s32 var_r4;

    sub_0801C2F0(0);
    var_r4 = sub_0801AFB8(gState0TransferWork.bytes[0x87]);
    table=gState0NextCommands_083B6100;
    sub_08040BD8(table[gState0TypedWork.bytes[0x84]], 0x21U);
    if (gFrameObjects[0x21].commandStopped == 0xFF) {
        var_r4 += 1;
    }
    if (var_r4 == 2) {
        sub_0801AEF4();
        sub_0801AEB4();
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_0803A5CC(void) {
 u8 *setup,*work,*initialWork;struct Frame4Backing *frames;
 s32 offset;u32 value;void *record;
 sub_0803D450();
 setup=gSetupBuffer_03000590;initialWork=gState0TransferWork.bytes;
 offset=initialWork[0x87]<<8;record=setup+offset;
 if(*(u8*)(record+0xDD)<=3U)
  value=setup[initialWork[0xA7]*0x18+offset+0x49];
 else value=*(u8*)(record+0xA8)+0x50;
 sub_0801BCE4(value,*(s16*)((work=gState0TransferWork.bytes)+0x10A),9);
 frames=(void*)gFrameObjects;
 frames->field2=*(u16*)(work+0x102);
 frames->field3=*(u16*)(work+0x104);
 frames->active=*(u16*)(work+0x10E);
 frames->delay=*(u16*)(work+0x10C);
 frames->kind=0x12;
 sub_0801BD1C(gUnknown_083CEDF4[frames->active],0,0);
 frames->y=4;
 if(!(2&work[0xF8])) {
  frames->x=*(u16*)(work+0x106);
  frames->tileX=*(u16*)(work+0x110);
 }else {
  frames->x=*(u16*)(work+0x108);
  frames->tileX=work[0x110]+2;
 }
 ((struct Frame4Backing*)gFrameObjects)->clear=0;
 sub_0803D4AC();
}

void sub_0803ADFC(void) {
 u8 *setup,*work,*initialWork;struct Frame4Backing *frames;
 s32 offset;u32 value;void *record;
 sub_0803D450();
 setup=gSetupBuffer_03000590;initialWork=gState0TransferWork.bytes;
 offset=initialWork[0x87]<<8;record=setup+offset;
 if(*(u8*)(record+0xDD)<=3U)
  value=setup[initialWork[0xA7]*0x18+offset+0x49];
 else value=*(u8*)(record+0xA8)+0x50;
 sub_0801BCE4(value,*(s16*)((work=gState0TransferWork.bytes)+0x10A),9);
 frames=(void*)gFrameObjects;
 frames->field2=*(u16*)(work+0x102);
 frames->field3=*(u16*)(work+0x104);
 frames->active=*(u16*)(work+0x10E);
 frames->delay=*(u16*)(work+0x10C);
 frames->kind=0x13;
 sub_0801BD1C(gUnknown_083CEDF4[frames->active],0,0);
 frames->y=4;
 if(!(2&work[0xF8])) {
  frames->x=*(u16*)(work+0x106);
  frames->tileX=*(u16*)(work+0x110);
 }else {
  frames->x=*(u16*)(work+0x108);
  frames->tileX=work[0x110]+2;
 }
 ((struct Frame4Backing*)gFrameObjects)->clear=0;
 sub_0803D4AC();
}

void sub_0803D3C0(void) {
    const u8 **table;
    struct FrameObject *temp_r1;

    table=gState0NextCommands_083B6100;
    sub_08040BD8(table[gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[3]], gState0TypedWork.bytes[0x12F]);
    if (sub_080353CC((u32) gState0TypedWork.bytes[0x12F]) != 0) {
        temp_r1 = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
        temp_r1->frameAndGroup = temp_r1->unknown23[5] + 0x6307;
        gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown23[6] = 0;
    }
}
