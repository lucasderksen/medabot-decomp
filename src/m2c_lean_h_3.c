/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bios_lz77.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "graphics.h"
#include "later_graphics.h"
#include "link_menu.h"
#include "record_helpers.h"
#include "scene_view.h"
#include "serial.h"
#include "sound_samples.h"
#include "sprite_layouts.h"
#include "state0_work.h"

/* The setup clears 0x874 bytes; overlapping views retain unchecked ROM indices. */
union CommandSlots {
    struct { u8 pad[0x0A]; u8 state[0x86A]; } s;
    struct { u8 pad[0x12]; u8 cmds[0x862]; } c;
    struct { u8 pad[0x52]; u8 count; } n;
    struct { u8 pad[0x54]; u8 value[0x820]; } v;
    struct { u8 pad[0x5C]; u8 phase[0x818]; } p;
};

void sub_0804FD10(void);

void sub_0804FD10(void) {

    s32 done = 0;
    s32 i;
    u32 mode;

    for (i = 0; i < ((union CommandSlots *)gContinuedCommandWork_030064A0)->n.count; i++) {
        if (((union CommandSlots *)gContinuedCommandWork_030064A0)->s.state[i] > 1) {
            done++;
            continue;
        }
        {
            switch (((union CommandSlots *)gContinuedCommandWork_030064A0)->c.cmds[((union CommandSlots *)gContinuedCommandWork_030064A0)->s.state[i] * 4 + i * 8]) {
            case 1: {
                /* Argument byte offsets as locals: the reference adds them to i * 8 before state * 4. */
                s32 first = 1, second = 2;
                sub_0805076C(((union CommandSlots *)gContinuedCommandWork_030064A0)->c.cmds[((union CommandSlots *)gContinuedCommandWork_030064A0)->s.state[i] * 4 + (i * 8 + first)], ((union CommandSlots *)gContinuedCommandWork_030064A0)->c.cmds[((union CommandSlots *)gContinuedCommandWork_030064A0)->s.state[i] * 4 + (i * 8 + second)]);
                ((union CommandSlots *)gContinuedCommandWork_030064A0)->s.state[i]++;
                break;
            }
            case 2: {
                s32 first = 1;
                ((union CommandSlots *)gContinuedCommandWork_030064A0)->v.value[i] = ((union CommandSlots *)gContinuedCommandWork_030064A0)->c.cmds[((union CommandSlots *)gContinuedCommandWork_030064A0)->s.state[i] * 4 + (i * 8 + first)];
                sub_08050554(((union CommandSlots *)gContinuedCommandWork_030064A0)->v.value[i]);
                ((union CommandSlots *)gContinuedCommandWork_030064A0)->s.state[i]++;
                break;
            }
            case 3:
            case 4:
                switch (((union CommandSlots *)gContinuedCommandWork_030064A0)->c.cmds[((union CommandSlots *)gContinuedCommandWork_030064A0)->s.state[i] * 4 + i * 8]) {
                case 3:
                default:
                    mode = 0;
                    break;
                case 4:
                    mode = 1;
                    break;
                }
                switch (((union CommandSlots *)gContinuedCommandWork_030064A0)->p.phase[i]) {
                case 0: {
                    s32 first = 1, second = 2;
                    ((union CommandSlots *)gContinuedCommandWork_030064A0)->v.value[i] = sub_0804DBF0(((union CommandSlots *)gContinuedCommandWork_030064A0)->c.cmds[((union CommandSlots *)gContinuedCommandWork_030064A0)->s.state[i] * 4 + (i * 8 + first)]) + 0x4F;
                    sub_080500BC(((union CommandSlots *)gContinuedCommandWork_030064A0)->v.value[i], ((union CommandSlots *)gContinuedCommandWork_030064A0)->c.cmds[((union CommandSlots *)gContinuedCommandWork_030064A0)->s.state[i] * 4 + (i * 8 + second)], mode);
                    ((union CommandSlots *)gContinuedCommandWork_030064A0)->p.phase[i]++;
                    break;
                }
                case 1:
                    if (sub_0805018C(((union CommandSlots *)gContinuedCommandWork_030064A0)->v.value[i], 1))
                        ((union CommandSlots *)gContinuedCommandWork_030064A0)->p.phase[i]++;
                    break;
                case 2:
                    ((union CommandSlots *)gContinuedCommandWork_030064A0)->p.phase[i] = 0;
                    ((union CommandSlots *)gContinuedCommandWork_030064A0)->s.state[i]++;
                    break;
                }
                break;
            case 0xFF:
                done++;
                break;
            default:
                done++;
                break;
            }
            if (((union CommandSlots *)gContinuedCommandWork_030064A0)->s.state[i] > 1)
                done++;
        }
    }
    if (done == ((union CommandSlots *)gContinuedCommandWork_030064A0)->n.count) {
        ((union CommandSlots *)gContinuedCommandWork_030064A0)->n.count = 0;
        sub_08049714(((union CommandSlots *)gContinuedCommandWork_030064A0)->c.cmds, 0x40);
        sub_08050290();
    }
}
