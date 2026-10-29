/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "scene_animation_data.h"
#include "compression.h"
#include "continued_commands.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "post_dispatch.h"
#include "record_helpers.h"
#include "state0_display.h"

#include "scene_graphics_loads.h"

void sub_08049440(u32 indexWord);

void sub_08049440(u32 indexWord) {

    u8 index = indexWord;
    const u16 *list;
    const u16 *command;
    u16 op, argument, duration, frame;

    list = gUnknown_083F7B80[gFrameObjects[index].unknown23[1]];
    /* Native prefetch includes adjacent words after short terminals/empty roots. */
    command = (const u16 *)((u32)gFrameObjects[index].commandStopped * 8 + (u32)list);
    op = command[0];
    argument = command[1];
    duration = command[2];
    frame = command[3];
    switch (op) {
    case 0xFFFD:
        gFrameObjects[index].commandStopped++;
        sub_08047BA8(argument);
        sub_08049440(index);
        break;
    case 0xFFFE:
        gFrameObjects[index].commandStopped = argument;
        gFrameObjects[index].unknown23[0] = 0;
        sub_08049440(index);
        break;
    case 0xFFFF:
        break;
    case 0xFFFA:
        if (gFrameObjects[index].unknown23[0] < duration) {
            gFrameObjects[index].frameAndGroup = frame + gFrameObjects[index].unknown2C[3];
            gFrameObjects[index].unknown23[0]++;
            if (gFrameObjects[index].unknown23[0] >= duration) {
                gFrameObjects[index].unknown23[0] = 0;
                gFrameObjects[index].commandStopped++;
            }
        }
        break;
    case 0xFFFC:
        if (gFrameObjects[index].unknown23[0] == 0) {
            const struct GraphicsLoad *load = &gUnknown_080AEB74[argument];
            if (load->loaded == 0)
                LZ77UnCompVram(load->source, load->destination);
        }
    default:
        if (gFrameObjects[index].unknown23[0] < duration) {
            gFrameObjects[index].frameAndGroup = frame;
            gFrameObjects[index].unknown23[0]++;
            if (gFrameObjects[index].unknown23[0] >= duration) {
                gFrameObjects[index].unknown23[0] = 0;
                gFrameObjects[index].commandStopped++;
            }
        }
        break;
    }
}
