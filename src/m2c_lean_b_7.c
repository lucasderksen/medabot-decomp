/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "audio.h"
#include "frame.h"
#include "frame_objects.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "utility_helpers.h"


void sub_0803C044(void);

void sub_0803C044(void) {

    u8 count;

    count = gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown2C[1];
    if (count != 0) {
        gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown2C[1] = count - 1;
        sub_0804422C(gState0TypedWork.bytes[0x12F]);
        if (gFrameObjects[3].unknown2C[0] == 0) {
            gCounter6ED08_03001800.pos154[0] = gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX;
            gCounter6ED08_03001800.pos154[1] = gFrameObjects[gState0TypedWork.bytes[0x12F]].screenY;
        } else {
            gCounter6ED08_03001800.pos154[2] = gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX;
            gCounter6ED08_03001800.pos154[3] = gFrameObjects[gState0TypedWork.bytes[0x12F]].screenY;
        }
    } else {
        sub_08040CD0(gState0TypedWork.bytes[0x12F], 1);
    }
}
