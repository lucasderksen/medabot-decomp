/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_float_progress.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedPaletteFrame {struct FrameObject preceding[0x21];u16 flags;u8 gap42[6];u8 scaleX,scaleY,palette;u8 gap4B[0x19];u8 kind;u8 gap65[11];u16 destinationX;s16 destinationY;};

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gUnknown_083AD524[];
extern const u8 gUnknown_084D6E00[];
extern const u8 gUnknown_084D70A8[];
extern const u8 gUnknown_0850FC98[64];
extern const u8 gUnknown_0850FCD8[64];
extern void sub_08017994(u32, u32, u32);
extern void sub_08040D0C(u8, u8);
extern void sub_080432A0(u32, u32, u32);

void sub_0801830C(void);
void sub_08022870(void);
void sub_08022D4C(void);
void sub_0802842C(void);

void sub_0801830C(void) {
    u8 *setup;
    u8 *work;
    u8 *active;
    u8 *finalWork;
    u8 *finalActive;
    const u8 *coordinates;
    u32 x;
    u32 y;
    s32 temp_r0;
    s32 temp_r3;
    u32 var_r4;

    sub_08040D0C(4U, 1U);
    sub_08040D0C(5U, 1U);
    sub_08040D0C(6U, 1U);
    sub_08040D0C(7U, 1U);
    var_r4 = 0;
    setup = gSetupBuffer_03000590;
    work = gState0TypedWork.bytes;
    active = work + 0x3D;
    coordinates = gUnknown_083AD524;
    do {
        temp_r3 = (work[0x3C] * 3) + var_r4;
        if ((setup[(temp_r3 << 8) + 0x40] != 0) && (var_r4 != *active)) {
            temp_r0 = temp_r3 * 2;
            x = *(const u8 *)(temp_r0 + (u32)coordinates);
            temp_r0 += 1;
            y = *(const u8 *)(temp_r0 + (u32)coordinates);
            sub_08017994(temp_r3, x, y);
        }
        var_r4 += 1;
    } while (var_r4 <= 2U);
    finalWork = gState0TypedWork.bytes;
    finalActive = finalWork + 0x3D;
    sub_080432A0(0U, (finalWork[0x3C] * 3) + *finalActive, (u32)finalWork[0x3C]);
}

void sub_08022870(void) {
    u8 *frames;
    u8 *work;
    u8 *typed;
    struct ContinuedPaletteFrame *view;
    struct FrameObject *source;
    const u8 *const *commands;
    u32 index;
    LeDecompress(gUnknown_084D6E00,(void *)0x06014800);
    CpuFastSet(gUnknown_0850FC98,(void *)0x050002C0,0x10);
    frames=(u8 *)gFrameObjects;
    view=(struct ContinuedPaletteFrame *)frames;
    view->flags|=0x200;
    view->scaleX=0x40;
    view->scaleY=0x40;
    view->palette=6;
    work=gState0TransferWork.bytes;
    index=work[0x88]*4+0x5D;
    source=&((struct FrameObject *)frames)[index];
    view->destinationX=source->screenX;
    index=work[0x88]*4+0x5D;
    source=&((struct FrameObject *)frames)[index];
    view->destinationY=source->screenY-4;
    view->kind=6;
    commands=gState0NextCommands_083B6100;
    sub_08040B90(commands[0x3E],0x21);
    typed=gState0TypedWork.bytes;
    *(u16 *)(typed+0x86)=0x3C;
    work[0xAA]++;
}

void sub_08022D4C(void) {
    u8 *frames;
    u8 *work;
    u8 *typed;
    struct ContinuedPaletteFrame *view;
    struct FrameObject *source;
    const u8 *const *commands;
    u32 index;
    LeDecompress(gUnknown_084D70A8,(void *)0x06014800);
    CpuFastSet(gUnknown_0850FCD8,(void *)0x050002C0,0x10);
    frames=(u8 *)gFrameObjects;
    view=(struct ContinuedPaletteFrame *)frames;
    view->flags|=0x200;
    view->scaleX=0x40;
    view->scaleY=0x40;
    view->palette=6;
    work=gState0TransferWork.bytes;
    index=work[0x88]*4+0x5D;
    source=&((struct FrameObject *)frames)[index];
    view->destinationX=source->screenX;
    index=work[0x88]*4+0x5D;
    source=&((struct FrameObject *)frames)[index];
    view->destinationY=source->screenY-4;
    view->kind=6;
    commands=gState0NextCommands_083B6100;
    sub_08040B90(commands[0x3E],0x21);
    typed=gState0TypedWork.bytes;
    *(u16 *)(typed+0x86)=0x3C;
    work[0xAA]++;
}

void sub_0802842C(void) {
 u8 *setup=gSetupBuffer_03000590;
 u32 selector=(setup+(gState0TransferWork.bytes[0x87]<<8))[0xA8]-0xC;
 switch(selector) {
 case 0:gState0TransferWork.bytes[0x51]=0;break;
 case 2:gState0TransferWork.bytes[0x51]=1;break;
 case 4:gState0TransferWork.bytes[0x51]=2;break;
 case 6:gState0TransferWork.bytes[0x51]=3;break;
 case 28:gState0TransferWork.bytes[0x51]=4;break;
 }
 gState0TransferWork.bytes[0xAA]++;
}
