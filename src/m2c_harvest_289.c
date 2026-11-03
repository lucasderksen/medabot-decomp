/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "frame_objects.h"
#include "object_helpers.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern const u8 *const gUnknown_083C4B90[4];

void sub_08016A3C(void);

void sub_08016A3C(void) {

    u8 *work;
    s32 choice;
    u32 recordAddress,setupRoot,labelIndex;
    const void *const *labels;
    HideFrameObjects(0x1F,0xE);
    work=gState0TransferWork.bytes;
    choice=work[0x82];
    switch(choice) {
    case 0:CopyBytesU8Count(gUnknown_083C4B90[3],gDebugMenuTextBuffer,0xE);break;
    case 1:case 2:case 3:
        labels=gPartTextPointers_083BBB4C;
        setupRoot=(u32)gSetupBuffer_03000590;
        recordAddress=(u32)(choice-1)*0x18;
        recordAddress+=(u32)work[0x80]<<8;
        recordAddress+=setupRoot;
        labelIndex=*(u8 *)(recordAddress+0x5F)*4+choice-1;
        CopyBytesU8Count((const u8 *)labels[labelIndex],gDebugMenuTextBuffer,0xF);
        break;
    default:break;
    }
    PlaceAlignedTextObjects(gDebugMenuTextBuffer,0x1F,0xA,0x11,0xA,0xD,0,0);
}
