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
#include "display_helpers.h"
#include "effect_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "input.h"
#include "main.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedWork279E4 {u8 prefix[0x51];u8 variant;u8 gap52[0x35];u8 selection;u8 gap88[0x22];u8 phase;};
struct ContinuedWorkSelect87 {u8 prefix[0x87];u8 selection;};
struct ContinuedWholeFrame21 {u8 prefix[0x840];struct FrameObject frame;};
struct ContinuedSetupA8 {u8 prefix[0xA8];u8 kind;u8 tail[0x57];};
struct ContinuedWork51A6 { u8 pad00[0x51]; u8 selection51; u8 pad52[0x54]; u8 commandA6; u8 padA7[3]; u8 phaseAA; };
struct Work63354 { u8 pad00[0x31]; u8 firstX; u8 secondX; u8 firstY; u8 secondY; u8 pad35[7]; u16 timer; };
struct Phase63354 { u8 pad00[0x84]; u8 phase; };
struct Row6938C { u8 pad00[4]; u8 firstTiles; u8 pad05[3]; u8 secondTiles; u8 pad09[3]; };
struct Work6D41C { u8 pad00[4]; u16 status; };

extern const struct Row6938C gUnknown_08485C00[];
extern const u8 gUnknown_084DD0C8[];
extern const u8 gUnknown_084DD24C[];
extern const u8 gUnknown_084DD2AC[];
extern const u8 gUnknown_084DD300[];
extern const u8 gUnknown_084E4658[32];
extern const u8 gUnknown_085100F8[32];
extern const u8 gUnknown_08510118[32];
extern const u8 gUnknown_08510138[32];
extern s32 sub_08062C98(void);
extern s8 gUnknown_03006F90;
extern struct ContinuedWork51A6 gUnknown_03001800;
extern struct Work6D41C gGraphicsTransferCounter;
extern u8 gContinuedByte_03002B64;
extern u8 gUnknown_0202F800[1024];
extern u8 gUnknown_03006FDC;
extern void sub_08040CD0(u8, u8);
extern void sub_08062B48(u8, u8, u32);

void sub_080279E4(void);
void sub_08028BA8(void);
void sub_08063354(void);
void sub_0806938C(void);
void sub_0806D41C(void);

void sub_080279E4(void) {
    struct ContinuedWork279E4 *work;
    struct ContinuedWholeFrame21 *frames;
    struct ContinuedSetupA8 *setup;
    u8 *selection;
    u32 temp_r0;

    LeDecompress(gUnknown_084DD0C8, (void *)0x06014800);
    CpuFastSet(gUnknown_084E4658, (void *)0x050002C0, 8U);
    setup=(struct ContinuedSetupA8 *)gSetupBuffer_03000590;
    temp_r0=setup[((struct ContinuedWorkSelect87 *)gState0TransferWork.bytes)->selection].kind-4;
    switch (temp_r0) {
    case 0:
    case 1:
        LeDecompress(gUnknown_084DD24C, (void *)0x06014C00);
        CpuFastSet(gUnknown_085100F8, (void *)0x050002E0, 8U);
        sub_08074DE0(0x27U);
        break;
    case 2:
    case 3:
        LeDecompress(gUnknown_084DD2AC, (void *)0x06014C00);
        CpuFastSet(gUnknown_08510118, (void *)0x050002E0, 8U);
        sub_08074DE0(0x45U);
        break;
    case 4:
    default:
        LeDecompress(gUnknown_084DD300, (void *)0x06014C00);
        CpuFastSet(gUnknown_08510138, (void *)0x050002E0, 8U);
        sub_08074DE0(0x33U);
        break;
    }
    frames=(struct ContinuedWholeFrame21 *)gFrameObjects;
    frames->frame.flags = 0xC604;
    frames->frame.tableSelector = 0;
    work=(struct ContinuedWork279E4 *)gState0TransferWork.bytes;
    selection=&work->selection;
    frames->frame.screenX = (s16) (u16)gFrameObjects[*selection*4+0x5D].screenX;
    frames->frame.screenY = (u16)gFrameObjects[*selection*4+0x5D].screenY - 4;
    frames->frame.scaleX = 0x40;
    frames->frame.scaleY = 0x40;
    frames->frame.angle = 0;
    frames->frame.palette = 6;
    frames->frame.priority = 0xF0;
    if (1 & work->variant) {
        frames->frame.frameAndGroup = 0x6601;
    } else {
        frames->frame.frameAndGroup = 0x6600;
    }
    gState0TypedWork.widths.word86 = 0;
    gState0TransferWork.bytes[0xAA]++;
}

void sub_08028BA8(void) {
 sub_08040CD0(0x21, 3);
 switch (gUnknown_03001800.selection51) {
 case 0: gUnknown_03001800.commandA6 = 0x46; break;
 case 1: gUnknown_03001800.commandA6 = 0x49; break;
 case 2: gUnknown_03001800.commandA6 = 0x47; break;
 case 3: gUnknown_03001800.commandA6 = 0x48; break;
 case 4: gUnknown_03001800.commandA6 = 0x5D; break;
 case 5: gUnknown_03001800.commandA6 = 0x5E; break;
 }
 gUnknown_03001800.phaseAA++;
}

void sub_08063354(void) {
    u32 temp_r0;
    struct Work63354 *work;

    sub_0803FB3C(gMain2ScriptSlots_08485678[19]);
    sub_08062C98();
    sub_08062B48(((struct Work63354 *)gMainContextPointer_03006F74)->firstX, ((struct Work63354 *)gMainContextPointer_03006F74)->firstY, 0);
    sub_08062B48(((struct Work63354 *)gMainContextPointer_03006F74)->secondX, ((struct Work63354 *)gMainContextPointer_03006F74)->secondY, 1);
    work = gMainContextPointer_03006F74;
    temp_r0 = work->timer - 1;
    work->timer = temp_r0;
    if ((s32) (temp_r0 << 0x10) < 0) {
        ((struct Phase63354 *)&gState0TypedWork)->phase = 0;
        gUnknown_0300137C += 1;
        sub_08042170(((struct Work63354 *)gMainContextPointer_03006F74)->firstX, ((struct Work63354 *)gMainContextPointer_03006F74)->firstY, 1U);
        sub_0804213C(((struct Work63354 *)gMainContextPointer_03006F74)->secondX, ((struct Work63354 *)gMainContextPointer_03006F74)->secondY, 1U);
        CpuFastSet((void *)0x05000200, gUnknown_0202F800, 0x100U);
        sub_08074DE0(0x4BU);
    }
}

void sub_0806938C(void) {
    gUnknown_03006F90 = 0;
    sub_0803F41C(0U, 0U, (void *)0x06004000, 9U, 0U);
    sub_0803F41C((u32) gUnknown_08485C00[gUnknown_03006FDC].firstTiles, 0U, (void *)0x06004800, 0xAU, 0U);
    sub_0803F41C((u32) gUnknown_08485C00[gUnknown_03006FDC].secondTiles, 0U, (void *)0x06005000, 0xBU, 0U);
    *(volatile u16 *)0x0400000C = 0x1E02;
    gBgScroll2.x = 0xFFE8;
    gBgScroll2.y = 0xFFA0;
}

void sub_0806D41C(void) {

    if ((gGraphicsTransferCounter.status == 5) && ((8 & gContinuedByte_03002B64) || (gMain2Byte_03007008 != 0))) {
        gMain2Byte_03007008 = 0;
        gMainState = 3;
        gMainSubstate = 2;
        gUnknown_0300137C = 0xA;
        return;
    }
    if ((4 & gContinuedByte_03002B64) && (8 & *(u8 *)&gNewKeys)) {
        gMainState = 2;
        gMainSubstate = 7;
        gUnknown_0300137C = 0;
    }
}
