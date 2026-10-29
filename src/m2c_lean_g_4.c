/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "action_aux_data.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "graphics.h"
#include "later_graphics.h"
#include "link_menu.h"
#include "map_metadata.h"
#include "map_object_spawns.h"
#include "packed_fields.h"
#include "pose_channels.h"
#include "post_dispatch.h"
#include "record_helpers.h"
#include "scene_setup_data.h"
#include "scene_view.h"
#include "serial.h"
#include "sound_samples.h"
#include "sound_voice.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

struct CommandSlots
{
    u8 unknown00[2];
    u8 timer[8];
    u8 state[8];
    u8 cmds[8][2][4];
    u8 count;
    u8 unknown53;
    u8 value[8];
    u8 phase[8];
};

extern u8 gFreshWork_03006D38[];

void sub_0804FE9C(void);

void sub_0804FE9C(void) {

    s32 finished = 0;
    s32 i;
    struct SelectionRecord *rec;

    for (i = 0; i < ((struct CommandSlots *)gContinuedCommandWork_030064A0)->count; i++) {
        switch (((struct CommandSlots *)gContinuedCommandWork_030064A0)->cmds[i][0][0]) {
        case 0:
            finished = 1;
            break;
        case 1:
            if (++((struct CommandSlots *)gContinuedCommandWork_030064A0)->timer[i] > 5) {
                rec = sub_0804D938(((struct CommandSlots *)gContinuedCommandWork_030064A0)->cmds[i][0][1] << 8 | ((struct CommandSlots *)gContinuedCommandWork_030064A0)->cmds[i][0][2]);
                if (rec != NULL && rec->flags.bits.auxiliary) {
                    sub_0805218C((u8)(rec->flags.bits.index + 0x31), ((struct CommandSlots *)gContinuedCommandWork_030064A0)->state[i], rec);
                    if (((struct CommandSlots *)gContinuedCommandWork_030064A0)->state[i] == 0
                        && ((struct CommandSlots *)gContinuedCommandWork_030064A0)->cmds[i][0][3] == 1
                        && sub_08052C68(rec->x, rec->y) != 0 && gFreshWork_03006D38[3] != 0)
                        sub_08047BA8(gSetupByteLookup_083D2B66[gFreshWork_03006D38[3]]);
                }
                ((struct CommandSlots *)gContinuedCommandWork_030064A0)->state[i]++;
                ((struct CommandSlots *)gContinuedCommandWork_030064A0)->timer[i] = 0;
                if (((struct CommandSlots *)gContinuedCommandWork_030064A0)->state[i] > 3) {
                    gFrameObjects[rec->flags.bits.index + 0x31].unknown23[1] = 0xFF;
                    finished = 1;
                }
            }
            break;
        case 2:
            if (++((struct CommandSlots *)gContinuedCommandWork_030064A0)->timer[i] > 5) {
                rec = sub_0804D938(((struct CommandSlots *)gContinuedCommandWork_030064A0)->cmds[i][0][1] << 8 | ((struct CommandSlots *)gContinuedCommandWork_030064A0)->cmds[i][0][2]);
                if (rec != NULL && rec->flags.bits.auxiliary)
                    sub_0805218C((u8)(rec->flags.bits.index + 0x31), (u8)(3 - ((struct CommandSlots *)gContinuedCommandWork_030064A0)->state[i]), rec);
                ((struct CommandSlots *)gContinuedCommandWork_030064A0)->state[i]++;
                ((struct CommandSlots *)gContinuedCommandWork_030064A0)->timer[i] = 0;
                if (((struct CommandSlots *)gContinuedCommandWork_030064A0)->state[i] > 3) {
                    gFrameObjects[rec->flags.bits.index + 0x31].unknown23[1] = 0xFF;
                    gFrameObjects[rec->flags.bits.index + 0x31].commandDelay = 0;
                    sub_08049420((u8)(rec->flags.bits.index + 0x31), sub_08050300(rec->flags.bits.index + 0x31, gFrameObjects[rec->flags.bits.index + 0x31].commandDelay));
                    finished = 1;
                }
            }
            break;
        default:
            finished = 1;
            break;
        }
    }
    if (finished) {
        ((struct CommandSlots *)gContinuedCommandWork_030064A0)->count = 0;
        sub_08049714(((struct CommandSlots *)gContinuedCommandWork_030064A0)->cmds, 0x40);
        sub_08050290();
    }
}
