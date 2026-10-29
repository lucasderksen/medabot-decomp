/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "eeprom.h"
#include "frame.h"
#include "later_graphics.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct SelectionBacking
{
  u8 prefix[0x5C];
  u8 owner;
  u8 other;
  u8 selected;
  u8 found;
  u8 cursor;
  u8 slots[3];
};
struct FrameInitBacking {
    u8 padding[0xC0];
    u16 flags;
    s16 x;
    s16 y;
    u16 frame;
    u8 scales[2];
    u8 palette;
    u8 priority;
    u8 gap[0x10];
    u8 table;
};
struct FrameCounterBacking {
    u8 prefix[0x14];
    s32 current;
    s32 extra;
    s32 saved;
    u8 gap[0x53 - 0x20];
    u8 count;
};

extern __typeof__(sub_08032FC4) sub_08032FB8;
extern s32 sub_08032FD0(u32, u32);
extern s32 sub_08032FFC(void);
extern s32 sub_0803301C(void);
extern s32 sub_080330E8(s32);
extern s32 sub_08033154(u32, u32);
extern u32 sub_08033184(u32);
extern u32 sub_08033224(u32);
extern u32 sub_08033240(u32);
extern u32 sub_0803325C(u32);
extern void sub_0803836C(void);
extern void sub_0807258C(void *);

void sub_0802BD1C(void);
void sub_0802CC10(void);

void sub_0802BD1C(void) {
    u8 *work = gState0TransferWork.bytes;
    switch (work[0x51]) {
    case 0:
        work[0xA6] = 0x3D;
        break;
    case 1:
        work[0xA6] = 0x3E;
        break;
    case 2:
        work[0xA6] = 0x40;
        break;
    case 3:
        work[0xA6] = 0x41;
        break;
    }
    work[0xAA]++;
}

void sub_0802CC10(void) {
    u8 *work;
    u8 *setup;
    u8 *flags;
    u8 *cursor;
    u32 root;
    u32 i;
    sub_0803836C();
    work = gState0TransferWork.bytes;
    work[0x60] = sub_08032FB8(work[0x87]);
    i = 0;
    setup = gSetupBuffer_03000590;
    root = (u32) work;
    flags = (u8 *) ((u32) root + 0xD2);
    cursor = (u8 *) ((u32) root + 0x60);
    do {
        u32 address = ((*cursor + i) << 8) + (u32) setup;
        if (*(u8 *) (address + 0x40) != 0 && *(u8 *) (address + 0x59) != 0)
            *(u8 *) (i + (u32) flags) = 1;
        i++;
    } while (i <= 2);
    (*(u8 *) ((u32) root + 0xAA))++;
}
