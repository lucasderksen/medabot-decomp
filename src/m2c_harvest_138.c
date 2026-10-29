/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_work.h"

struct ContinuedFrame21 {u8 prefix[0x840];struct FrameObject frame;};

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gUnknown_084DD484[];
extern const u8 gUnknown_084DD6A0[];
extern const u8 gUnknown_084DDAE4[];
extern const u8 gUnknown_084DDD70[];
extern const u8 gUnknown_084DE728[];
extern const u8 gUnknown_084E4658[32];
extern const u8 gUnknown_08510178[32];
extern const u8 gUnknown_08510198[32];
extern const u8 gUnknown_085101B8[32];
extern const u8 gUnknown_085101D8[32];
extern const u8 gUnknown_08510218[32];

void sub_08028504(void);

void sub_08028504(void) {
    struct ContinuedFrame21 *frames;u8 *setup=gSetupBuffer_03000590;
    u32 selector;

    selector = (setup+(gState0TransferWork.bytes[0x87]<<8))[0xA8] - 0xC;
    switch(selector) {
    case 0:
        LeDecompress(gUnknown_084DD484,(void *)0x06014800);
        CpuFastSet(gUnknown_08510178,(void *)0x050002E0,8);
        gFrameObjects[0x21].unknown23[5]=0;
        gFrameObjects[0x21].unknown2C[2]=0x5B;
        break;
    case 2:
        LeDecompress(gUnknown_084DD6A0,(void *)0x06014800);
        CpuFastSet(gUnknown_08510198,(void *)0x050002E0,8);
        gFrameObjects[0x21].unknown23[5]=1;
        gFrameObjects[0x21].unknown2C[2]=0x5B;
        break;
    case 4:
        LeDecompress(gUnknown_084DDAE4,(void *)0x06014800);
        CpuFastSet(gUnknown_085101B8,(void *)0x050002E0,8);
        gFrameObjects[0x21].unknown23[5]=2;
        gFrameObjects[0x21].unknown2C[2]=0x5B;
        break;
    case 6:
        LeDecompress(gUnknown_084DDD70,(void *)0x06014800);
        CpuFastSet(gUnknown_085101D8,(void *)0x050002E0,8);
        gFrameObjects[0x21].unknown23[5]=3;
        gFrameObjects[0x21].unknown2C[2]=0x5C;
        break;
    case 28:
        LeDecompress(gUnknown_084DE728,(void *)0x06014800);
        CpuFastSet(gUnknown_08510218,(void *)0x050002E0,8);
        gFrameObjects[0x21].unknown23[5]=4;
        gFrameObjects[0x21].unknown2C[2]=0x5B;
        break;
    }
    CpuFastSet(gUnknown_084E4658, (void *)0x050002C0, 8U);
    frames=(struct ContinuedFrame21 *)gFrameObjects;
    frames->frame.flags = 0xC604;
    frames->frame.tableSelector = 0;
    frames->frame.screenY = 0xE0;
    frames->frame.palette = 7;
    frames->frame.scaleX = 0x40;
    frames->frame.scaleY = 0x40;
    frames->frame.angle = 0;
    frames->frame.priority = 0xF0;
    frames->frame.unknown23[6] = 1;
    frames->frame.byte2B = 0x20;
    frames->frame.unknown2C[0] = 0xC0;
    frames->frame.unknown2C[1] = 0;
    sub_08040B90(gState0NextCommands_083B6100[frames->frame.unknown2C[2]], 0x21U);
    if (!(1 & gState0TransferWork.bytes[0xF8])) {
        frames->frame.screenX = 0xB8;
    } else {
        frames->frame.flags |= 0x1000;
        frames->frame.screenX = 0x38;
    }
    gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
}
