/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"

struct ContinuedSetup24D18 {u8 prefix[0xC9];u8 mode,part,firstValue,secondValue;u8 tail[0x33];};
struct ContinuedAECCFrame33 { u8 pad00[0x840]; struct FrameObject frame; };

extern const u8 *const gState0NextCommands_083B6100[0x66];
extern u32 sub_08036E54(u32);

void sub_08024D18(void);
void sub_0802AECC(void);

void sub_08024D18(void) {
    struct ContinuedSetup24D18 *setup=(struct ContinuedSetup24D18 *)gSetupBuffer_03000590;
    u8 *work=gState0TransferWork.bytes;
    u8 *bank=work+0x88;
    setup[*bank].mode=0x2B;
    setup[*bank].firstValue=sub_08036E54(*(s16 *)(work+0xE8));
    setup[*bank].secondValue=sub_08036E54(*(s16 *)(work+0xEC));
    switch(work[0x8B]) {
    case 1:setup[*bank].part=2;break;
    case 2:setup[*bank].part=3;break;
    default:setup[*bank].part=1;break;
    }
    gState0TransferWork.bytes[0xAA]++;
}

void sub_0802AECC(void) {
 struct ContinuedAECCFrame33 *frames;
 u8 *work;
 u8 *bank;
 u32 zero;
 frames = (struct ContinuedAECCFrame33 *)&gFrameObjects;
 frames->frame.flags = (zero = 0, 0xCC04);
 frames->frame.tableSelector = zero;
 work = gState0TransferWork.bytes;
 bank = work + 0x87;
 frames->frame.screenX = (u16)gFrameObjects[*bank * 4 + 0x5D].screenX;
 frames->frame.screenY = (u16)gFrameObjects[*bank * 4 + 0x5D].screenY - 4;
 frames->frame.palette = 7;
 frames->frame.priority = zero;
 sub_08040B90(gState0NextCommands_083B6100[0x65], 0x21);
 sub_08074DE0(0x71);
 work[0xAA]++;
}
