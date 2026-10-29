/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "record_helpers.h"

struct FrameCounterBacking {
    u8 prefix[0x14];
    s32 current;
    s32 saved;
    u8 gap[0x52 - 0x1C];
    u8 count;
};

extern void sub_0807258C(void *);

void sub_08072BCC(struct FrameCounterBacking *work);
void sub_08072D04(u8 *work);

void sub_08072BCC(struct FrameCounterBacking *work) {
    work->count--;
    if (work->count != 0)
        work->current = work->saved;
}

void sub_08072D04(u8 *work) {
    work[0x62] = 1;
    switch (work[0x64]) {
    case 0:
    case 1:
    case 2:
        sub_0807258C(work);
        break;
    }
}
