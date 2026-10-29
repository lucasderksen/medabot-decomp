/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "link_menu.h"
#include "main.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Lanes6BB64
{
    u8 unknown00[0xC];
    s8 laneCount;
    s8 offset;
    s8 count;
    s8 lanes[0x35];
};

extern const u8 gRandomBytes_083F7D80[];
extern struct Lanes6BB64 gLanes6BB64 asm("gCounter6ED08_03001800");

void sub_0806BB64(void);

void sub_0806BB64(void) {

    s32 i;

    gLanes6BB64.lanes[0] = gRandomBytes_083F7D80[(gFrameCounter + i) & 0xFF] % 3u;
    for (i = 1; i < gLanes6BB64.laneCount; i++) {
        switch ((u8)(gRandomBytes_083F7D80[(gFrameCounter + i) & 0xFF] % 7u)) {
        case 0:
            gLanes6BB64.lanes[i] = gLanes6BB64.lanes[i - 1];
            break;
        case 1:
        case 2:
        case 3:
            gLanes6BB64.lanes[i] = gLanes6BB64.lanes[i - 1] != 0 ? gLanes6BB64.lanes[i - 1] - 1 : 1;
            break;
        case 4:
        case 5:
        case 6:
            gLanes6BB64.lanes[i] = gLanes6BB64.lanes[i - 1] != 2 ? gLanes6BB64.lanes[i - 1] + 1 : 1;
            break;
        }
    }
    gUnknown_0300137C++;
}
