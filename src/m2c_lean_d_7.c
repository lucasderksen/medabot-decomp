/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "battle_work.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "dialogue_messages.h"
#include "display_effects.h"
#include "effect_work.h"
#include "frame.h"
#include "frame_command_data.h"
#include "input.h"
#include "main.h"
#include "main_callbacks.h"
#include "map_metadata.h"
#include "object_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct MenuContext65208 {
    u8 pad00[0x2E];
    u8 cursor2E;
    u8 scroll2F;
    u8 count30;
    u8 pad31[0x1B];
    u8 flag4C;
};

extern struct MenuContext65208 *gMenuContext65208 asm("gMainContextPointer_03006F74");
extern u8 gFamilyKeyBytes49558_0300058C;
extern void sub_08064C6C(u8);

void sub_08065208(void);

void sub_08065208(void) {

    s32 done;
    u8 up;
    s32 sound;

    done = 1;
    if (gMenuContext65208->flag4C != 0) {
        if (sub_08041CA4() != 0) {
            gMenuContext65208->flag4C = 0;
            sub_0803FAA0(1, 0, 0);
        }
    } else if (sub_0803FB3C(gMain2ScriptSlots_0848521C[13]) != 0) {
        done = 0;
    }
    if (done != 0)
        return;
    sub_08041C14(8, gFrameCounter, 0xC);
    gFrameObjects[8].flags |= 0x4000;
    sound = 0;
    if (gMenuContext65208->count30 > 4) {
        if (gMenuContext65208->scroll2F != 0) {
            if ((gFrameCounter & 0xF) <= 9)
                gFrameObjects[10].flags |= 0x4000;
            else
                gFrameObjects[10].flags &= 0xBFFF;
        } else {
            gFrameObjects[10].flags &= 0xBFFF;
        }
        if (!(gMenuContext65208->scroll2F + 4 < gMenuContext65208->count30))
            gFrameObjects[11].flags = 0xBFFF & gFrameObjects[11].flags;
        else if ((gFrameCounter & 0xF) <= 9)
            gFrameObjects[11].flags = 0x4000 | gFrameObjects[11].flags;
        else
            gFrameObjects[11].flags = 0xBFFF & gFrameObjects[11].flags;
    }
    if ((up = 0x40 & (u8)gRepeatedKeys) != 0) {
        sound = 2;
        if (gMenuContext65208->cursor2E != 0)
            gMenuContext65208->cursor2E--;
        else if (gMenuContext65208->scroll2F != 0)
            gMenuContext65208->scroll2F--;
        else if (gMenuContext65208->count30 <= 3)
            gMenuContext65208->cursor2E = gMenuContext65208->count30 - 1;
        else
            goto upRefresh;
        if (sound != 0)
            sub_08074DE0(sound);
    upRefresh:
        sub_08064C6C(gMenuContext65208->scroll2F);
    } else if (0x80 & (u8)gRepeatedKeys) {
        sound = 2;
        if (gMenuContext65208->count30 <= 3) {
            if (gMenuContext65208->cursor2E == gMenuContext65208->count30 - 1)
                gMenuContext65208->cursor2E = up;
            else
                gMenuContext65208->cursor2E++;
        } else if (gMenuContext65208->cursor2E == 3) {
            if (gMenuContext65208->scroll2F != gMenuContext65208->count30 - 4)
                gMenuContext65208->scroll2F++;
            else
                goto downRefresh;
        } else {
            gMenuContext65208->cursor2E++;
        }
        if (sound != 0)
            sub_08074DE0(sound);
    downRefresh:
        sub_08064C6C(gMenuContext65208->scroll2F);
    } else {
        if (1 & gFamilyKeyBytes49558_0300058C) {
            sub_08074DE0(4);
            gFrameObjects[10].flags &= 0xBFFF;
            gFrameObjects[11].flags &= 0xBFFF;
            gFrameObjects[8].screenX = 0xC;
            gMenuContext65208->flag4C = 1;
            gState0TypedWork.bytes[0x1B] = 0;
            gUnknown_0300137C = 9;
            sub_080415E8(1, 0x16, 7);
            return;
        }
        if (2 & gFamilyKeyBytes49558_0300058C) {
            sub_08074DE0(5);
            gFrameObjects[8].flags &= 0xBFFF;
            gState0TypedWork.bytes[0x1B] = 0;
            gState0TypedWork.bytes[0x84] = 0;
            gUnknown_0300137C = 7;
        }
        return;
    }
    gFrameObjects[8].screenX = 0xC;
    gFrameObjects[8].screenY = gMenuContext65208->cursor2E * 16 + 0x1C;
}
