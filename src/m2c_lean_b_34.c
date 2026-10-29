/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "encounter_choices.h"
#include "frame.h"
#include "frame_command_handlers.h"
#include "graphics.h"
#include "link_menu.h"
#include "main.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "serial.h"
#include "sound_voice.h"
#include "sound_work.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_work.h"

struct View6AAA4
{
    u8 unknown00[2];
    s16 screenX;
    u8 unknown04[7];
    u8 priority;
    u8 unknown0C[0xE];
    u16 timer;
    u8 unknown1C[0xE];
    u8 state;
    u8 unknown2B[0xF];
    u16 previous;
    u8 unknown3C[4];
};

extern const u8 gRandomBytes_083F7D80[];
extern struct View6AAA4 gView6AAA4[] asm("gFrameObjects");
extern u8 gEncounterFrameSlotsView[3][3] asm("gEncounterFrameSlots");
extern u8 gSelectionOrder03006F94[3];
extern u8 gUnknown_03006F8C[3];
extern u8 gUnknown_03006FEC[3];
extern u8 gUnknown_03006FF0[3];
extern void sub_08069B38(u8 slot, u8 mode);

void sub_0806AAA4(void);

void sub_0806AAA4(void) {

    s32 i;
    s32 k;

    for (i = 0; i <= 2; i++) {
        if (gUnknown_03006F8C[i] <= 2) {
            if (gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].timer > 0x2AF) {
                sub_08043240(gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]] - 3, 4);
                gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].state = 1;
                if (++gUnknown_03006F8C[i] > 2) {
                    sub_0806B530(i + 1, 0, 0, 0);
                    if (gSelectionOrder03006F94[0] == 0) {
                        gSelectionOrder03006F94[0] = i + 1;
                        for (k = 0; k <= 15; k++) {
                            u8 frame = gRandomBytes_083F7D80[(gFrameCounter + k) & 0xFF];
                            frame &= 3;
                            sub_08048864(k + 4, 0xC400, frame + 0x10C, 0xB, 3);
                            gView6AAA4[k + 4].priority = 0x64;
                            sub_0806B530(k + 4, 8, frame, (k * 16) & 0x7F);
                        }
                    } else if (gSelectionOrder03006F94[1] == 0) {
                        gSelectionOrder03006F94[1] = i + 1;
                    } else if (gSelectionOrder03006F94[2] == 0) {
                        gSelectionOrder03006F94[2] = i + 1;
                    }
                    sub_08074DE0(0x43);
                    continue;
                }
                sub_08074DE0(0x44);
                gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].timer = 0;
                gUnknown_03006FEC[i] = 0x20;
                gUnknown_03006FF0[i] = 0;
            }
            if (gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].previous <= 0x157 && gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].timer > 0x157) {
                sub_08069B38(i * 3 + gUnknown_03006F8C[i], 1);
                gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]] - 3].priority -= 4;
                gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]] - 2].priority -= 4;
                gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]] - 1].priority -= 4;
                gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].priority -= 4;
                if (gUnknown_03006F8C[i] <= 1)
                    gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1]].state = 2;
            }
            if (gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].timer > 0x158) {
                gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].screenX = 0xD8 - ((gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].timer - 0x158) >> 1);
            } else {
                gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].screenX = (gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].timer >> 1) + 0x2C;
                if (gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].previous <= 0x97 && gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].timer > 0x97 && gUnknown_03006F8C[i] <= 1) {
                    gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1]].state = 1;
                    sub_08043240(gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1] - 3, 4);
                }
            }
            gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].previous = gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].timer;
            gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].timer++;
            sub_080432A0(gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]] - 3, i * 3 + 2 - gUnknown_03006F8C[i], 0);
            gView6AAA4[0x14 + i * 3 + gUnknown_03006F8C[i]].screenX = gView6AAA4[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i]]].screenX;
        }
    }
}
