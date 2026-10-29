/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "frame_objects.h"
#include "object_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

extern const u8 *const gUnknown_083BE868[];

void sub_08016D18(void);

void sub_08016D18(void) {

    u8 *work;
    const u8 *text;
    s32 choice;
    u32 recordAddress;
    u32 setupRoot;
    const u8 *const *labels;
    sub_08040D0C(0x14,0xB);
    work=gState0TransferWork.bytes;
    choice=work[0x82];
    switch(choice) {
    case 0:sub_08042678(gDebugMenuTextBuffer,0xA);break;
    case 1:case 2:case 3:
        labels=gUnknown_083BE868;
        setupRoot=(u32)gSetupBuffer_03000590;
        recordAddress=(u32)(choice-1)*0x18;
        recordAddress+=(u32)work[0x80]<<8;
        recordAddress+=setupRoot;
        text=labels[*(u8 *)(recordAddress+0x49)];
        sub_08041D04(text,gDebugMenuTextBuffer,0xC);
        break;
    default:break;
    }
    sub_08040DB8(gDebugMenuTextBuffer,0x14,0x15,0x11,8,0xE,0,0);
}
