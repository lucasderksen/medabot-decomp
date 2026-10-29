/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ObservedActionFrameBacking
{
    u8 unknown000[0x840];
    u16 flags840;
    u16 screenX842;
    u16 screenY844;
    u8 unknown846[4];
    u8 palette84A;
    u8 priority84B;
    u8 unknown84C[0x10];
    u8 table85C;
    u8 unknown85D[5];
    u8 commandStopped862;
};

extern s8 sub_08036E54(s16);
extern u8 *gUnknown_083B6298;
extern u8 gUnknown_030018D2[];

void sub_08020628(void);
void sub_08023A48(void);

void sub_08020628(void) {
    struct ObservedActionFrameBacking *objects;
    u8 *work;
    u8 *row;
    u8 *selected;
    LeDecompress(gActionMotionAsset_084CDF48, (void *)0x06014800);
    CpuFastSet(gActionMotionPalette_0850F8D8, (void *)0x050002E0, 8);
    objects = (void *)gFrameObjects;
    objects->flags840 = 0xC004;
    objects->table85C = 0;
    work = gState0TransferWork.bytes;
    row = &work[0x87];
    {
        u32 index = *row * 4;
        u32 subindex;
        selected = &work[0xA7];
        subindex = *selected;
        subindex += 90;
        index += subindex;
        objects->screenX842 = gFrameObjects[index].screenX;
    }
    {
        u32 index = *row * 4;
        u32 subindex;
        subindex = *selected;
        subindex += 90;
        index += subindex;
        objects->screenY844 = gFrameObjects[index].screenY;
    }
    objects->palette84A = 7;
    objects->priority84B = 240;
    sub_08040B90(gUnknownPointers_083B6100[34], 33);
    work[0xAA]++;
}

void sub_08023A48(void) {
    u8 *setup = gSetupBuffer_03000590;
    u8 *work = gState0TransferWork.bytes;
    u8 *slot = &work[0x88];
    s32 zero;
    setup[(*slot << 8) + 0xC4] = (zero = 0, 0x26);
    setup[(*slot << 8) + 0xC5] = zero;
    setup[(*slot << 8) + 0xC6] = sub_08036E54(*(s16 *) &work[0xE8]);
    setup[(*slot << 8) + 0xC7] = sub_08036E54(*(s16 *) &work[0xEC]);
    work[0xAA]++;
}
