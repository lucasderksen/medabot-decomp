/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "bios_lz77.h"
#include "composite_graphics.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "record_helpers.h"
#include "render_work.h"
#include "scene_view.h"
#include "state0_display.h"
#include "state0_work.h"
#include "utility_helpers.h"


void sub_08044934(u32 index, u8 first, u8 second, u16 width, u16 height, u32 mode, u8 size, u8 doubled, u8 clear);

void sub_08044934(u32 index, u8 first, u8 second, u16 width, u16 height, u32 mode, u8 size, u8 doubled, u8 clear) {

    s16 h;
    u32 extra;
    u32 data = (u32)gRecordDisplayData;
    s32 fill;

    switch (mode) {
    case 0:
        mode = 100;
        break;
    case 1:
        mode = 200;
        break;
    case 2:
        mode = 300;
        break;
    case 3:
        mode = 400;
        break;
    }
    if (doubled == 0)
        doubled = 1;
    else
        doubled = 2;
    extra = 0;
    if (clear == 1)
        extra = 4;
    h = height;
    gRecordDisplayWork.data = (u8 *)(index * 0x410 + data);
    sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, first, second, h, (s16)width, mode, size, doubled | extra);
    if (clear == 2) {
        fill = 0x200;
        CpuFastSet(&fill, gRenderWork->objects, 0x01000100);
        gRenderWork->byte1094 = 0;
        gRenderWork->byte1095 = 0;
    }
}
