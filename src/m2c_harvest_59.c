/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "eeprom.h"
#include "frame.h"
#include "gba.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "tile_text.h"

struct FrameBacking {
    u8 padding[0x280];
    u16 flags;
    s16 x;
    s16 y;
    u16 frame;
    u8 scales[2];
    u8 palette;
    u8 priority;
    u8 gap[0x10];
    u8 table;
    u8 gap2[6];
    u8 stopped;
};

extern s32 gUnknown_0850F898;
extern s32 gUnknown_0850FA38;
extern u8 gUnknown_084CDB98;
extern u8 gUnknown_084D2E8C;

void sub_0801F018(void);
void sub_0801F0F0(void);

void sub_0801F018(void) {
    struct FrameBacking *objects;
    u8 *work;

    LeDecompress(&gUnknown_084CDB98, (void *)0x06010000);
    CpuFastSet(&gUnknown_0850F898, (void *)0x050003C0, 8U);
    objects = (void *) gFrameObjects;
    objects->flags = 0xC404;
    objects->table = 0;
    objects->palette = 0xE;
    objects->priority = 0x80;
    objects->frame = 0x2000;
    objects->stopped = 0;
    work = gState0TransferWork.bytes;
    if (!(2 & work[0xF8])) {
        objects->x = (s16) *(u16 *) (work + 0x158);
        objects->y = *(s16 *) (work + 0x15A);
    } else {
        objects->x = (s16) *(u16 *) (work + 0x154);
        objects->y = *(s16 *) (work + 0x156);
    }
    sub_08074DE0(0x2A);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0801F0F0(void) {
    struct FrameBacking *objects;
    u8 *work;

    LeDecompress(&gUnknown_084D2E8C, (void *)0x06010000);
    CpuFastSet(&gUnknown_0850FA38, (void *)0x050003C0, 8U);
    objects = (void *) gFrameObjects;
    objects->flags = 0xC404;
    objects->table = 0;
    objects->palette = 0xE;
    objects->priority = 0x80;
    objects->frame = 0x2E00;
    objects->stopped = 0;
    work = gState0TransferWork.bytes;
    if (!(2 & work[0xF8])) {
        objects->x = (s16) *(u16 *) (work + 0x158);
        objects->y = *(s16 *) (work + 0x15A);
    } else {
        objects->x = (s16) *(u16 *) (work + 0x154);
        objects->y = *(s16 *) (work + 0x156);
    }
    sub_08074DE0(0x2A);
    gState0TransferWork.bytes[0xAA] += 1;
}
