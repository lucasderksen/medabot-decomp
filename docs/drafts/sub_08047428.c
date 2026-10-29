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

s32 sub_08047428(struct PoseChannel7428 *channel, s16 *angles, s8 *offsets, u8 *frames, u32 unused4, u8 frame, u8 slot, s32 count, s32 stride)
{
    s32 done = 0;
    u32 end;
    s32 n;

    angles += slot;
    offsets += slot * 2;
    if (frames != 0) {
        end = frames[slot];
        for (n = 1; n < count; n++, angles += stride, offsets += stride * 2) {
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
                    channel[n].x += Div((offsets[0] << 8) - channel[n].x, remaining);
                    channel[n].y += Div((offsets[1] << 8) - channel[n].y, remaining);
                }
            } else {
                channel[n].angle = *angles;
                if (offsets != 0) {
                    channel[n].x = offsets[0] << 8;
                    channel[n].y = offsets[1] << 8;
                }
                done++;
            }
        }
    }
    return done;
}
