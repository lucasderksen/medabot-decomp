/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "link_menu.h"
#include "record_helpers.h"
#include "scene_view.h"
#include "sound_samples.h"
#include "sound_voice.h"
#include "state0_callbacks.h"
#include "state0_work.h"

struct AnimRecBD58 {
    u8 timer;
    u8 pos;
    u8 state;
    u8 tile;
    u16 base;
    u16 width;
};
struct AnimViewBD58 { u8 pad[0x64]; struct AnimRecBD58 recs[8]; };


void sub_0801BD58(const u16 *script, u32 index);

void sub_0801BD58(const u16 *script, u32 index) {


    u32 running;

    if (((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].state == 0xFF)
        return;
    running = 1;
    do {
        if (((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].timer != 0) {
            ((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].timer--;
            return;
        }
        switch (*(const u8 *)&script[((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].pos]) {
        case 0xFD:
            sub_08074DE0(script[((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].pos + 1]);
            ((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].pos += 2;
            break;
        case 0xFE:
            ((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].pos = script[((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].pos + 1] * 2;
            break;
        case 0xFF:
            ((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].state = 0xFF;
            return;
        default:
            ((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].timer = script[((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].pos];
            CpuSet((u8 *)(((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].base << 5) + (((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].width * (script[((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].pos + 1] << 5) + 0x02000000),
                (void *)(((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].tile * 0x1200 + 0x06004000), (((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].width << 3) | 0x04000000);
            ((struct AnimViewBD58 *)&gState0TypedWork)->recs[index].pos += 2;
            break;
        }
    } while (running);
}
