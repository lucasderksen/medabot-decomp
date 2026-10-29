/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_command_data.h"
#include "link_menu.h"
#include "native_le_streams.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_work.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Setup15390 { u8 unknown00[0x18]; u8 types18[0x27]; u8 cursor3F; u8 unknown40[0xC0]; };
struct Setup155A8 { u8 unknown00[5]; u8 level05; u8 unknown06[0xBB]; u8 kindC1; u8 unknownC2[0x3E]; };

extern struct Setup15390 gSetup15390[] asm("gSetupBuffer_03000590");
extern struct Setup155A8 gSetup155A8[] asm("gSetupBuffer_03000590");
extern u8 gFamilyKeyBytes49558_0300058C;

u32 sub_08006F34(void);
u32 sub_08015390(u32 slot);
u32 sub_080155A8(u32 slot, u32 level, u32 adjust);
u32 sub_0801A6EC(u32 kind);

u32 sub_08006F34(void) {

    if (1 & gFamilyKeyBytes49558_0300058C) {
        switch (gState0TypedWork.bytes[0x5A]) {
        case 0:
            if (gState0TypedWork.bytes[0x97] == 0x1E)
                return 2;
            return 1;
        case 1:
            if (gState0TypedWork.bytes[0x98] > 0x77)
                return 2;
            return 1;
        case 2:
            if (gState0TypedWork.bytes[0x99] > 0x77)
                return 2;
            return 1;
        case 3:
            if (gState0TypedWork.bytes[0x9A] > 0x77)
                return 2;
            return 1;
        case 4:
            if (gState0TypedWork.bytes[0x9B] > 0x77)
                return 2;
            return 1;
        }
    }
    /* Falls off the end like the reference (flag clear or selector > 4): r0 is the caller's; the only caller, sub_0800442C, calls with r0 = 0 (after a zero key test), so it takes neither choice 1 nor 2. */
}

u32 sub_08015390(u32 slot) {

    u8 type = gSetup15390[slot].types18[gSetup15390[slot].cursor3F];

    switch (type) {
    case 0:
        return 1;
    case 1:
    case 2:
    case 3:
        if (sub_080156F8(slot, type) != 0)
            return 1;
        sub_08015564(slot, type);
        return 0;
    case 4:
        sub_08015564(slot, 0);
        return 0;
    case 5:
    case 6:
    case 7:
        if (sub_080155A8(slot, type - 5, 0) != 0)
            return 1;
        return 0;
    }
    /* Falls off the end like the reference (type > 7): r0 still holds slot; callers sub_0801531C and sub_08015358 test it != 0, i.e. slot != 0. */
}

u32 sub_080155A8(u32 slot, u32 level, u32 adjust) {

    u32 i;

    if (sub_08015648(slot) != 0 || gCounter6ED08_03001800.pad56[2] != 0)
        goto fail;
    if (gSetup155A8[slot].kindC1 == 0x50)
        goto search;
    goto fail;
raise0:
    sub_08015668(slot, 0);
    return 0;
raise1:
    sub_08015668(slot, 1);
    return 0;
raise2:
    sub_08015668(slot, 2);
    return 0;
fail:
    return 1;
search:
    if (adjust != 0)
        level = sub_08033074();
    for (i = 0; i <= 2; i++) {
        if (level == 0) {
            if (gSetup155A8[slot].level05 > 9)
                goto raise0;
            if (adjust == 0)
                goto fail;
        }
        if (level == 1) {
            if (gSetup155A8[slot].level05 > 0x1D)
                goto raise1;
            if (adjust == 0)
                goto fail;
        }
        if (level == 2) {
            if (gSetup155A8[slot].level05 > 0x3B)
                goto raise2;
            if (adjust == 0)
                goto fail;
        }
        if (level == 0)
            goto fail;
        level--;
    }
    /* Falls off the end like the reference, returning r0 = sub_08033074() (>= 3, only with adjust != 0): caller sub_08015464 tests it != 0; caller sub_08015390 passes levels 0..2 with adjust == 0 and never gets here. */
}

u32 sub_0801A6EC(u32 kind) {

    if (kind <= 2) {
        switch (kind) {
        case 0:
            if (1 & gCounter6ED08_03001800.pad3D[7])
                return 1;
            return 0;
        case 1:
            if (2 & gCounter6ED08_03001800.pad3D[7])
                return 1;
            return 0;
        case 2:
            if (4 & gCounter6ED08_03001800.pad3D[7])
                return 1;
            return 0;
        }
    }
    /* Falls off the end like the reference (kind > 2): r0 still holds kind; the only caller, sub_08014404, tests it != 0 and so sees it as true. */
}
