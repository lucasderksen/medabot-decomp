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
#include "continued_commands.h"
#include "continued_graphics.h"
#include "continued_late_graphics.h"
#include "continued_map.h"
#include "continued_scene_records.h"
#include "link_menu.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "render_work.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedWorkB008 {
    u8 unknown000[0x7FE];
    u8 map;
    u8 unknown7FF[0x429];
    u8 byteC28;
    u8 unknownC29[0x1F];
    u16 halfC48;
    u16 halfC4A;
    u8 unknownC4C[6];
    u16 halfC52;
    u16 halfC54;
    u8 cellX;
    u8 cellY;
    u8 unknownC58[4];
    u8 byteC5C;
    u8 unknownC5D[0x5D];
    u8 byteCBA;
};
struct OtherWork14
{
    u8 unknown00[0x14];
    u8 byte14;
    u8 unknown15[0x11];
    u16 half26;
};

extern const void *gLaterBuffer_03005590;
extern struct ContinuedWorkB008 gContinuedWork_030057E0;

void sub_0804B008(void);

void sub_0804B008(void) {

    u32 x, y;

    if (sub_08049E08(0x7FFF) != 0) {
        gLaterBuffer_03005590 = gSetupData_08765EC0;
        if (((struct OtherWork14 *)gContinuedOtherWork_030057A0)->byte14 == 0)
            gContinuedWork_030057E0.map = ((struct OtherWork14 *)gContinuedOtherWork_030057A0)->half26;
        sub_080528F8(gContinuedWork_030057E0.map);
        x = ((u8 (*)(u32))sub_0805273C)(gContinuedWork_030057E0.halfC52);
        y = ((u8 (*)(u32))sub_08052760)(gContinuedWork_030057E0.halfC54);
        if (gContinuedWork_030057E0.cellX >= sub_080529AC(gContinuedWork_030057E0.map, 0) >> 1)
            x = (sub_080529AC(gContinuedWork_030057E0.map, 0) >> 1) - 1;
        if (gContinuedWork_030057E0.cellY >= sub_080529AC(gContinuedWork_030057E0.map, 1) >> 1)
            y = (sub_080529AC(gContinuedWork_030057E0.map, 1) >> 1) - 1;
        gContinuedWork_030057E0.halfC52 = x * 16 + gContinuedWork_030057E0.halfC48;
        gContinuedWork_030057E0.halfC54 = y * 16 + gContinuedWork_030057E0.halfC4A;
        gContinuedWork_030057E0.cellX = sub_0805273C(gContinuedWork_030057E0.halfC52);
        gContinuedWork_030057E0.cellY = sub_08052760(gContinuedWork_030057E0.halfC54);
        sub_08052AA4();
        gContinuedWork_030057E0.byteC28 = gContinuedWork_030057E0.byteC5C;
        sub_0805330C();
        *(volatile u16 *)0x04000000 = 0x1E40;
        sub_0804B248();
        gContinuedWork_030057E0.byteCBA = 0;
        gUnknown_0300137C = 1;
    }
}
