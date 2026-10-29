/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "main_menu_data.h"
#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "effect_work.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "graphics.h"
#include "input.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct SingleFrameBacking {
 u8 prefix[0x782];s16 x,y;
 u8 gap[0x7A4-0x786];u8 tileY,tileX;
 u8 gap2[3];u8 kind;u8 gap3;u8 active;
 u8 gap4[4];u16 savedX;
};
struct MaskContextBacking { u8 prefix[0x31]; u8 first; u8 gap; u8 second; };

extern const u8 *gState0NextCommands_083B6100[];
extern u32 gUnknownMask_03002B68;
extern u8 gUnknown_03007010;
s32 sub_0807CD2C(s32, s32);
void sub_08067C04(void);

void sub_08039FE4(void);
void sub_0803A370(void);
void sub_0803DB4C(void);
void sub_0803EC04(void);
s32 sub_0805B5FC(s32 arg0);
void sub_08062F88(void);
void sub_08066870(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3);
void sub_08068374(void);
void sub_08071898(u8 slot, u16 group, u8 value);
void sub_080718D4(u8 slot, u16 group);

void sub_08039FE4(void) {
 struct SingleFrameBacking *frames;
 u8 *work;
 sub_0803D450();sub_08040CD0(0x1E,1);
 frames=(void*)gFrameObjects;work=gState0TransferWork.bytes;
 frames->active=*(u16*)(work+0x102);
 frames->y=*(u16*)(work+0x106);
 frames->tileY=*(u16*)(work+0x10A);
 frames->kind=0xA;
 if((work[0xF8]&2)==0) {
  frames->x=*(u16*)(work+0x104);
  frames->tileX=*(u16*)(work+0x108);
 }else {
  frames->x=0xF0-*(u16*)(work+0x104);
  frames->tileX=(0x20-work[0x108])&0x1F;
 }
 ((struct SingleFrameBacking*)gFrameObjects)->savedX=gFrameObjects[0x1E].screenX;
 sub_0803D4AC();
}

void sub_0803A370(void) {
 struct SingleFrameBacking *frames;
 u8 *work;
 sub_0803D450();sub_08040CD0(0x1E,1);
 frames=(void*)gFrameObjects;work=gState0TransferWork.bytes;
 frames->active=*(u16*)(work+0x102);
 frames->y=*(u16*)(work+0x106);
 frames->tileY=*(u16*)(work+0x10A);
 frames->kind=0xC;
 if((work[0xF8]&2)==0) {
  frames->x=*(u16*)(work+0x104);
  frames->tileX=*(u16*)(work+0x108);
 }else {
  frames->x=0xF0-*(u16*)(work+0x104);
  frames->tileX=(0x20-work[0x108])&0x1F;
 }
 ((struct SingleFrameBacking*)gFrameObjects)->savedX=gFrameObjects[0x1E].screenX;
 sub_0803D4AC();
}

void sub_0803DB4C(void) {
    __typeof__(&gState0TypedWork.bytes[0]) member0;
    const void *const *table;
    sub_08043CD4();
    table = gState0MessagePointers_083C3B04;
    if ((sub_0803FB3C(table[1]) != 0) && (3 & (*(u8 *)&gNewKeys))) {
        member0 = gState0TypedWork.bytes;
        member0[0x1B] = 0;
        sub_08074DE0(0xDU);
        gUnknown_0300137C += 1;
    }
}

void sub_0803EC04(void) {
    struct FrameObject *objects = gFrameObjects;
    u8 *work = gState0TransferWork.bytes;
    const u8 **commands;
    objects[2].unknown23[1] = (work[0x1A0] >> 2) + 4;
    objects[2].unknown23[2] = 0;
    commands = gState0NextCommands_083B6100;
    sub_08040B90(commands[0x75 - work[0x1A2]], 4);
}

s32 sub_0805B5FC(s32 arg0) {
    s32 var_r2;

    var_r2 = 0;
    if (gUnknown_08483554[arg0] == 1) {
        var_r2 = 1;
    }
    return var_r2;
}

void sub_08062F88(void) {
    struct MaskContextBacking *context;
    context = gMainContextPointer_03006F74;
    context->first = gUnknownMask_03002B68;
    context = gMainContextPointer_03006F74;
    context->second = *((u16 *)&gUnknownMask_03002B68 + 1);
    gUnknown_0300137C++;
}

void sub_08066870(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s32 temp_r4;
    s32 temp_r5;
    s32 target;

    target = arg1[0];
    temp_r4 = arg0[0];
    arg2[0] = (s32) (sub_0807CD2C(target - temp_r4, 3) + temp_r4);
    target = arg1[1];
    temp_r5 = arg0[1];
    arg2[1] = (s32) (sub_0807CD2C(target - temp_r5, 3) + temp_r5);
    arg3[0] = (s32) (sub_0807CD2C((arg1[0] - temp_r4) * 2, 3) + temp_r4);
    arg3[1] = (s32) (sub_0807CD2C((arg1[1] - temp_r5) * 2, 3) + temp_r5);
}

void sub_08068374(void) {
    u8 *offset0;
    const void *const *table;
    sub_08067C04();
    table = gMain2ScriptSlots_0848521C;
    if ((sub_0803FB3C(table[18]) != 0) && (1 & (*(u8 *)&gNewKeys))) {
        offset0 = gMainContextPointer_03006F74;
        sub_080656DC(offset0 + 0x50, 0U, 0U, 1U, 0xC0U);
        gUnknown_0300137C += 1;
    }
}

void sub_08071898(u8 slot, u16 group, u8 value) {
    u32 mask;
    u8 *active;
    struct FrameObject *objects;
    struct FrameObject *frame;
    mask = (u32)(0x01000000 << (slot - 0x16)) >> 24;
    active = &gUnknown_03007010;
    *active |= mask;
    objects = gFrameObjects;
    frame = &objects[slot];
    frame->unknown23[0] = value;
    *(u16 *)((u8 *)frame + 0x30) = group;
    frame->frameAndGroup = group;
}

void sub_080718D4(u8 slot, u16 group) {
    u32 mask;
    u8 *active;
    struct FrameObject *objects;
    struct FrameObject *frame;
    mask = (u32)(0x01000000 << (slot - 0x16)) >> 24;
    active = &gUnknown_03007010;
    *active &= ~ mask;
    objects = gFrameObjects;
    frame = &objects[slot];
    frame->unknown23[0] = 0;
    frame->frameAndGroup = group;
}
