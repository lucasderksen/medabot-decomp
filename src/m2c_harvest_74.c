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
#include "frame_objects.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct FrameInitBacking {
    u8 padding[0x80];
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

extern __typeof__(sub_08036AC4) sub_08036DE8;
extern s32 sub_08036D24(void *, u32, u32);
extern u8 gUnknown_030018C8[];
extern u8 gUnknown_030018D2[];
extern void sub_08036370(s32, u32);
extern void sub_080364A8(s32, u32);

void sub_0801F390(void);
void sub_0802CE08(void);
void sub_0802EF0C(void);
void sub_0803E934(void);

void sub_0801F390(void) {
    u8 *base = gUnknown_030018C8;
    u8 *selected = base - 0x40;
    s32 result = sub_08036D24(base, *selected, *(base - 0x3D));
    s32 mode;
    u32 bits = base[0x30] & 2;
    mode = 0;
    if (bits == 0)
        mode = 1;
    sub_08036370(mode, *selected);
    sub_080364A8(mode, *selected);
    if (result != 0) {
        gState0TypedWork.widths.word86 = 0x3C;
        (*(base - 0x1E))++;
    }
}

void sub_0802CE08(void) {
    s32 finished = 0;
    s32 active = 0;
    u32 i = 0;
    u8 *flags = gUnknown_030018D2;
    do {
        if (*(u8 *) (i + (u32) flags) != 0) {
            active++;
            if (sub_080355F0(i + 0x21) != 0)
                finished++;
        }
        i++;
    } while (i <= 2);
    if (finished == active)
        gState0TransferWork.bytes[0xAA]++;
}

void sub_0802EF0C(void) {
    s32 found = 0;
    u32 i = 0;
    u8 *flags = gUnknown_030018D2;
    do {
        if (*(u8 *) (i + (u32) flags) != 0 && sub_08036DE8(i + 0x24, 0) != 0)
            found = 1;
        i++;
    } while (i <= 2);
    if (found != 0) {
        gState0TypedWork.widths.word86 = 0x3C;
        gState0TransferWork.bytes[0xAA]++;
    }
}

void sub_0803E934(void) {
    struct FrameInitBacking *objects;
    s16 *coordinate;
    u8 *parameter;
    u32 zero;
    sub_08040CD0(2, 1);
    objects = (void *) gFrameObjects;
    objects->flags = (zero = 0, 0xC400);
    coordinate = &objects->x;
    *coordinate = 0x68;
    coordinate++;
    *coordinate = 0x78;
    objects->frame = 0x8506;
    objects->table = zero;
    parameter = (u8 *) coordinate + 7;
    *parameter = 0x82;
}
