/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "bios_lz77.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "link_menu.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "scene_view.h"
#include "sound_samples.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

struct PoseChannel7428
{
    u8 unknown00[8];
    s16 x;
    s16 y;
    s16 angle;
    u8 unknown0E[2];
};
struct AngleChoice
{
    s32 diff;
    s32 abs;
};


s32 sub_08047428(struct PoseChannel7428 *channel, s16 *angles, s8 *offsets, u8 *frames, u32 unused4, u8 frame, u8 slot, s32 count, s32 stride);

s32 sub_08047428(struct PoseChannel7428 *channel, s16 *angles, s8 *offsets, u8 *frames, u32 unused4, u8 frame, u8 slot, s32 count, s32 stride) {

    s32 done = 0;
    u32 end;
    s32 n;

    /* The reference traverses beyond the 49 stored tracks into adjacent ROM. */
    angles = (s16 *)((u32)angles + ((u32)slot << 1));
    offsets = (s8 *)((u32)offsets + ((u32)slot << 1));
    if (frames != 0) {
        end = frames[slot];
        for (n = 1; n < count;
             n++, angles = (s16 *)((u32)angles + ((u32)stride << 1)),
             offsets = (s8 *)((u32)offsets + ((u32)stride << 1))) {
            if (frame < end) {
                struct AngleChoice c[3];
                s32 remaining = end - frame;
                s32 diff = *angles; /* target angle first, then the chosen difference */

                c[0].diff = diff - channel[n].angle;
                {
                    s32 a = channel[n].angle - 0x10000;
                    c[1].diff = diff - a;
                }
                {
                    s32 a = channel[n].angle + 0x10000;
                    c[2].diff = diff - a;
                }
                c[0].abs = c[0].diff;
                c[1].abs = c[1].diff;
                c[2].abs = c[2].diff;
                if (c[0].abs < 0)
                    c[0].abs = -c[0].abs;
                if (c[1].abs < 0)
                    c[1].abs = -c[1].abs;
                if (c[2].abs < 0)
                    c[2].abs = -c[2].abs;
                if (c[0].abs > c[1].abs) {
                    if (c[1].abs > c[2].abs)
                        diff = c[2].diff;
                    else
                        diff = c[1].diff;
                } else {
                    if (c[0].abs > c[2].abs)
                        diff = c[2].diff;
                    else
                        diff = c[0].diff;
                }
                channel[n].angle += Div(diff, remaining);
                if (offsets != 0) {
                    channel[n].x += Div((offsets[0] * 256) - channel[n].x, remaining);
                    channel[n].y += Div((offsets[1] * 256) - channel[n].y, remaining);
                }
            } else {
                channel[n].angle = *angles;
                if (offsets != 0) {
                    channel[n].x = offsets[0] * 256;
                    channel[n].y = offsets[1] * 256;
                }
                done++;
            }
        }
    }
    return done;
}
