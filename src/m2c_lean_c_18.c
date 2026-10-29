/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "banked_commands.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "blend_setup_helpers.h"
#include "continued_commands.h"
#include "continued_graphics.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "initialization.h"
#include "later_graphics.h"
#include "link_menu.h"
#include "object_helpers.h"
#include "object_numeric_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "render_work.h"
#include "sound_voice.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "state0_work.h"
#include "tile_text.h"

struct SetupDma2F0 { u32 source, destination, control; };
struct ContinuedWork2F0 {
    u8 unknown000[0x7FC];
    u8 byte7FC;
    u8 byte7FD;
    u8 byte7FE;
    u8 unknown7FF[0xC34 - 0x7FF];
    u8 byteC34;
    u8 unknownC35[0xC4A - 0xC35];
    u16 halfC4A;
    u8 unknownC4C[0xC52 - 0xC4C];
    u16 halfC52;
    u16 halfC54;
    u8 byteC56;
    u8 byteC57;
    u8 unknownC58[3];
    u8 byteC5B;
    u8 byteC5C;
    u8 unknownC5D[0xC67 - 0xC5D];
    u8 byteC67;
    u8 unknownC68[0xC6E - 0xC68];
    s16 halfC6E;
    s16 halfC70;
    u8 unknownC72[4];
    u8 byteC76;
    u8 unknownC77[0xC83 - 0xC77];
    u8 byteC83;
    u8 byteC84;
    u8 unknownC85[0xCBA - 0xC85];
    u8 byteCBA;
    u8 unknownCBB;
    u8 byteCBC;
    u8 byteCBD;
    u8 unknownCBE[2];
};

extern const void *gLaterBuffer_03005590;
extern struct ContinuedWork2F0 gContinuedWork_030057E0;
extern u16 gSetupCoordinate_03006428;
extern u32 gPostDispatchWord_03002B70;
extern void *gFreshPointer_030057DC;
extern void *gLaterBuffer_030057D8;
extern void *gLaterBuffer_03006D14;
extern void *gLaterBuffer_03006D30;

void sub_0804A2F0(void);

void sub_0804A2F0(void) {

    u32 fill;
    u32 zero;
    u32 control;
    volatile struct SetupDma2F0 *dma;

    do {
        sub_08049714(&gPostDispatchWord_03002B70, 0x1C);
        sub_08049714(gInventoryRecords, 0x780);
        sub_08049714(gObjectHalfwordBytes, 0x3C0);
        sub_08049714(gUnknownRecords_030017A0, 0x48);
        sub_08049714(gObjectCountPairs, 0x80);
        sub_08049714(&gContinuedWork_030057E0, 0xCC0);
    } while (0);
    sub_08049714(&gState0TypedWork, 0x13C);
    sub_08049714(gSetupBuffer_03000590, 0x600);
    ResetSpritesAndVram();
    sub_08049714(gFrameObjects, 0x2000);
    sub_08049714(gLaterBuffer_030055A0, 0x200);
    zero = 0;
    fill = zero;
    dma = (volatile struct SetupDma2F0 *)0x040000D4;
    dma->source = (u32)&fill;
    dma->destination = 0x07000000;
    control = 0x85000100;
    dma->control = control;
    dma->control;
    sub_08041D28();
    sub_080421A0();
    gContinuedWork_030057E0.byteCBC = 0x10;
    gContinuedWork_030057E0.byteCBD = 0x10;
    *(volatile u16 *)0x0400000A = 0xC609;
    *(volatile u16 *)0x0400000C = 0xEA0A;
    *(volatile u16 *)0x0400000E = 0xEE0B;
    *(volatile u16 *)0x04000000 = 0x1E40;
    gLaterBuffer_03005590 = gSetupData_08765EC0;
    gLaterBuffer_030057D8 = &gContinuedWork_030057E0;
    gLaterBuffer_03006D30 = (void *)0x02039000;
    gLaterBuffer_03006D14 = (void *)0x02030000;
    gFreshPointer_030057DC = (void *)0x02038000;
    sub_08049714(gFrameObjects, 0x2000);
    sub_08049714(gLaterBuffer_030055A0, 0x200);
    fill = zero;
    dma->source = (u32)&fill;
    dma->destination = 0x07000000;
    dma->control = control;
    dma->control;
    sub_08049318();
    sub_08048BB8();
    gBackgroundState_03005310.unknown1C = zero;
    gBackgroundState_03005310.unknown24 = zero;
    gBackgroundState_03005310.scrollX[0] = zero;
    gBackgroundState_03005310.scrollY[0] = zero;
    gBackgroundState_03005310.scrollX[1] = zero;
    gBackgroundState_03005310.scrollY[1] = zero;
    gBackgroundState_03005310.scrollX[2] = zero;
    gBackgroundState_03005310.scrollY[2] = zero;
    gBgScroll0.x = zero;
    gBgScroll0.y = zero;
    gBgScroll1.x = zero;
    gBgScroll1.y = zero;
    gBgScroll2.x = zero;
    gBgScroll2.y = zero;
    gBgScroll3.x = zero;
    gBgScroll3.y = zero;
    sub_08049714(&gContinuedWork_030057E0.byte7FC, 0x454);
    gContinuedWork_030057E0.byteCBA = 0;
    gContinuedWork_030057E0.byte7FE = 0x17;
    gContinuedWork_030057E0.byte7FC = 0xE;
    gContinuedWork_030057E0.byte7FD = 7;
    gContinuedWork_030057E0.halfC52 = 0x120 + gSetupCoordinate_03006428;
    gContinuedWork_030057E0.halfC54 = gContinuedWork_030057E0.halfC4A + 0xD0;
    gContinuedWork_030057E0.byteC67 = 0;
    gContinuedWork_030057E0.byteC34 = 1;
    gContinuedWork_030057E0.byteC56 = sub_0805273C(gContinuedWork_030057E0.halfC52);
    gContinuedWork_030057E0.byteC57 = sub_08052760(gContinuedWork_030057E0.halfC54);
    gContinuedWork_030057E0.byteC5C = 0;
    gContinuedWork_030057E0.byteC5B = 1;
    sub_08048864(0x2F, 0xC804, 3, 0, 1);
    sub_08052B70();
    if (gContinuedWork_030057E0.byteC76 != 0) {
        sub_08048864(0x30, 0xC804, gContinuedWork_030057E0.byteC84 * 12 + gContinuedWork_030057E0.byteC83, gContinuedWork_030057E0.byteC84, 1);
        gContinuedWork_030057E0.halfC6E = 0x50 - gSetupCoordinate_03006428;
        gContinuedWork_030057E0.halfC70 = 0x60 - gContinuedWork_030057E0.halfC4A;
    }
    gBackgroundState_03005310.unknown00[1] = 0;
    *(volatile u16 *)0x04000050 = zero;
    *(volatile u16 *)0x04000054 = zero;
    sub_08048830();
    sub_08049D18(0x7FFF, 32.0f, 0.0f, 8.0f);
    sub_0804A210();
}
