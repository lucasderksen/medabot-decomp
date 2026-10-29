/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "interrupts.h"
#include "main.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "serial.h"
#include "sound_samples.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

extern u16 gEquipmentScanlineA[];
extern u16 gEquipmentScanlineB[];

void sub_08043960(s32 phase, s32 amplitude, u32 count);

void sub_08043960(s32 phase, s32 amplitude, u32 count) {

    u16 *dst;
    u16 *buffer;
    s32 i;

    if (!(gFrameCounter & 1))
        buffer = gEquipmentScanlineB;
    else
        buffer = gEquipmentScanlineA;
    for (i = 0; i <= 0x9F; i++) {
        dst = buffer + i * 8;
        if (i < count) {
            if (!(3 & i)) {
                u32 index = (i + phase) & 0xFF;
                gState0TypedWork.widths.word86 = (float)gScrollOscillationSines_083D6A2C[index]
                    * ((float)amplitude * 0.001953125f);
            }
            dst[0] = gState0TypedWork.widths.word86 + (gBgScroll0.x + gBgScrollBase.x);
            dst[1] = gBgScroll0.y + gBgScrollBase.y;
            dst[2] = gState0TypedWork.widths.word86 + (gBgScroll1.x + gBgScrollBase.x);
            dst[3] = gBgScroll1.y + gBgScrollBase.y;
            dst[4] = gState0TypedWork.widths.word86 + (gBgScroll2.x + gBgScrollBase.x);
            dst[5] = gBgScroll2.y + gBgScrollBase.y;
            dst[6] = gState0TypedWork.widths.word86 + (gBgScroll3.x + gBgScrollBase.x);
            dst[7] = gBgScroll3.y + gBgScrollBase.y;
        } else {
            dst[0] = gBgScroll0.x + gBgScrollBase.x;
            dst[1] = gBgScroll0.y + gBgScrollBase.y;
            dst[2] = gBgScroll1.x + gBgScrollBase.x;
            dst[3] = gBgScroll1.y + gBgScrollBase.y;
            dst[4] = gBgScroll2.x + gBgScrollBase.x;
            dst[5] = gBgScroll2.y + gBgScrollBase.y;
            dst[6] = gBgScroll3.x + gBgScrollBase.x;
            dst[7] = gBgScroll3.y + gBgScrollBase.y;
        }
    }
    gUnknownCallback_03000B98 = sub_08043AE0;
}
