/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "frame.h"
#include "frame_objects.h"
#include "input.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Work256EC { u8 pad[0x87]; u8 setup87; u8 setup88; u8 pad89[0x21]; u8 counterAA; };

extern struct Work256EC gWork256EC asm("gCounter6ED08_03001800");

void sub_080256EC(void);

void sub_080256EC(void) {

    u32 count;

    sub_0801A574(&gState0TypedWork.bytes[0xEE], gWork256EC.setup88, 0x21);
    sub_0801A574(&gState0TypedWork.bytes[0x10E], gWork256EC.setup87, 0x21);
    gState0TypedWork.bytes[0x84] = count = gState0TypedWork.bytes[0x84] + 1;
    if (gState0TypedWork.bytes[0x89] == 0 && (*(u8 *)&gRepeatedKeys & 1) && (u8)count > 0x32)
        gState0TypedWork.bytes[0x84] = 0x78;
    if (gState0TypedWork.bytes[0x84] == 0x78) {
        sub_08040CD0(gWork256EC.setup88 * 4 + 0x21, 4);
        sub_08040CD0(gWork256EC.setup87 * 4 + 0x21, 4);
        gWork256EC.counterAA++;
    }
}
