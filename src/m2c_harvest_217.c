/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_commands.h"
#include "continued_scene_records.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "fresh_helpers.h"
#include "palette_transfer_helpers.h"
#include "record_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinueTravelWork { u8 pad[0xC35]; u8 first,second; u8 pad2[0x11]; u16 x,y; u8 pad3[6]; u16 resultX,resultY; u8 stepX,stepY; u8 pad4[15]; u8 kind; };

extern struct ContinueTravelWork gContinuedWork_030057E0;
extern void sub_0804B2B0(void);

void sub_0804DDCC(void);

void sub_0804DDCC(void) {
    sub_0804830C();
    sub_08048708();
    sub_0804B2B0();
    sub_0804387C();
    gContinuedWork_030057E0.first = 0;
    gContinuedWork_030057E0.second = 0;
    sub_08048174();
    sub_0805330C();
    gContinuedWork_030057E0.resultX = (s16) ((gContinuedWork_030057E0.stepX * 0x10) + gContinuedWork_030057E0.x);
    gContinuedWork_030057E0.resultY = (s16) ((gContinuedWork_030057E0.stepY * 0x10) + gContinuedWork_030057E0.y);
    sub_080517F0();
    sub_08052B70();
    gFrameObjects[0x2F].unknown23[2] = 1;
    sub_08052E0C((u32) gContinuedWork_030057E0.kind);
    sub_0805309C();
    sub_08048288();
    sub_08050290();
}
