/*
 * Record display setup wrappers (siblings of sub_08044934). Defined here with
 * their narrow parameter types; include/utility_helpers.h keeps the u32
 * prototypes the callers were matched against.
 */

#include "global.h"
#include "gba.h"
#include "render_work.h"
#include "state0_display.h"

void sub_080446B4(u32 index, u8 first, u8 second, u8 third, u8 fourth, u16 width, u16 height, u32 mode, u8 size, u8 doubled, u8 clear, u8 last) {
    s16 h;
    u32 extra;
    u32 data;
    s32 fill;

    switch (mode) {
    case 0:
        /* data is set only in case 0 and read uninitialised for other modes, as in the reference:
           no effect on the generated code; only steers literal rematerialisation. */
        data = (u32)gRecordDisplayData;
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
    sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork, first, second, third, fourth, h, (s16) width, mode, size, doubled | extra, last);
    if (clear == 2) {
        fill = 0x200;
        CpuFastSet(&fill, gRenderWork->objects, 0x01000100);
        gRenderWork->byte1094 = 0;
        gRenderWork->byte1095 = 0;
    }
}

void sub_080447EC(u32 index, u8 first, u8 second, u8 third, u8 fourth, u16 width, u16 height, u32 mode, u8 size, u8 doubled, u8 clear, u8 last, u8 offset) {
    s16 h;
    u32 extra;
    u32 data;
    s32 fill;

    switch (mode) {
    case 0:
        /* data is set only in case 0 and read uninitialised for other modes, as in the reference:
           no effect on the generated code; only steers literal rematerialisation. */
        data = (u32)gRecordDisplayData;
        mode = offset + 100;
        break;
    case 1:
        mode = offset + 200;
        break;
    case 2:
        mode = offset + 300;
        break;
    case 3:
        mode = offset + 400;
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
    sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork, first, second, third, fourth, h, (s16) width, mode, size, doubled | extra, last);
    if (clear == 2) {
        fill = 0x200;
        CpuFastSet(&fill, gRenderWork->objects, 0x01000100);
        gRenderWork->byte1094 = 0;
        gRenderWork->byte1095 = 0;
    }
}
