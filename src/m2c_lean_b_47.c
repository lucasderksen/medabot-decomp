/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "later_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "render_work.h"
#include "scene_view.h"
#include "serial.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "state0_inventory_view.h"
#include "state0_work.h"
#include "tile_text.h"

struct LaterTemplate { u32 words[4]; u8 count; u8 pad[7]; };
struct LaterBytes { u8 b0, b1, b2, b3; };
struct LaterCmd { u8 count:6; u8 b6:2; u8 b8:7; u8 flag:1; u8 b2; u8 b3; };

extern const struct LaterCmd gLaterCmdF610[][4] asm("gLaterCommands_0807F610");
extern const struct LaterCmd gLaterCmdFDB0[][4] asm("gLaterCommands_0807FDB0");
extern const struct LaterTemplate gLaterTemplate_0807EE10;
extern const struct LaterTemplate gLaterTemplate_0807EE28;
extern const struct LaterTemplate gLaterTemplate_0807EE40;
extern const struct LaterTemplate gLaterTemplate_0807EE58;
extern struct LaterTemplate gUnknown_03005290;
extern struct LaterTemplate gUnknown_030052B0;
extern struct LaterTemplate gUnknown_030052D0;
extern struct LaterTemplate gUnknown_030052F0;
extern void sub_080465B8(struct RecordDisplayWork *work, const u32 *commands, u32 selector, s32 y, s32 x, s32 priority, u32 visible, u32 slot);

u8 sub_080460B0(struct RenderWork *render, void *names, s32 mode, void *objects, s16 tileBase, const u8 *parts, u8 palette, u8 y, u8 x, u32 slot);

u8 sub_080460B0(struct RenderWork *render, void *names, s32 mode, void *objects, s16 tileBase, const u8 *parts, u8 palette, u8 y, u8 x, u32 slot) {

    u32 list[32];
    u8 data[0x820];
    struct RecordDisplayWork work;
    volatile u32 fill;
    s32 i0, i1, i2, i3;
    s32 o1, o2;
    const u32 *c0;
    const u32 *c1;
    const u32 *c2;
    const u32 *c3;
    const u32 *src;
    u32 *dst;
    s32 k;
    u16 base;
    s16 priority = 0x32;
    u32 zero;

    zero = 0;
    i0 = parts[0];
    i1 = parts[1];
    i2 = parts[2];
    i3 = parts[3];
    memset(list, 0, sizeof(list));
    memset(data, 0, sizeof(data));
    memset(&work, 0, sizeof(work));
    fill = zero;
    CpuFastSet((void *)&fill, render, 0x01000426);
    gRenderWork = render;
    sub_08047414(&work, render, gUnknownBytes_083D1D78, data);
    gRenderWork->byte1094 = zero;
    gRenderWork->byte1095 = mode;
    ((u8 *)gRenderWork)[0x1097] = zero;
    gUnknown_030052D0 = gLaterTemplate_0807EE10;
    gUnknown_030052B0 = gLaterTemplate_0807EE28;
    base = 0x160;
    gUnknown_03005290 = gLaterTemplate_0807EE40;
    gUnknown_030052F0 = gLaterTemplate_0807EE58;
    c0 = gLaterCommands_0807EE70[i0];
    gUnknown_030052D0.count = c0[0] << 26 >> 26;
    o1 = i1 << 4;
    c1 = ((const u32 (*)[4])gLaterCmdF610)[i1];
    gUnknown_03005290.count = c1[0] << 26 >> 26;
    o2 = i2 << 4;
    c2 = ((const u32 (*)[4])gLaterCmdFDB0)[i2];
    gUnknown_030052B0.count = c2[0] << 26 >> 26;
    c3 = gLaterCommands_08080550[i3];
    gUnknown_030052F0.count = c3[0] << 26 >> 26;
    tileBase = base + 0x140;
    sub_08045E6C(work.source, c0, c0[0] << 26 >> 26, palette, work.data, &tileBase, slot);
    tileBase = base + 0x1A0;
    sub_08045E6C(work.source, c1, c1[0] << 26 >> 26, palette, work.data, &tileBase, slot);
    tileBase = base + 0x1E0;
    sub_08045E6C(work.source, c2, c2[0] << 26 >> 26, palette, work.data, &tileBase, slot);
    tileBase = base + 0x220;
    sub_08045E6C(work.source, c3, c3[0] << 26 >> 26, palette, work.data, &tileBase, slot);
    if (slot) {
        if (((const u8 *)c1)[0] << 26) {
            for (k = 0; ((const u8 *)((const u32 (*)[4])gLaterCmdF610)[i1])[k] << 26; k += 4) {
                if (!(((const struct LaterBytes *)((const u8 *)((const u32 (*)[4])gLaterCmdF610)[i1] + k))->b1 >> 7))
                    sub_08046034(work.source, work.data, ((const u32 (*)[4])gLaterCmdFDB0)[i1],
                        ((u32)((((const u8 *)((const u32 (*)[4])gLaterCmdFDB0)[i1])[k]) << 26) >> 26),
                        ((u32)((((const u8 *)((const u32 (*)[4])gLaterCmdF610)[i1])[k]) << 26) >> 26));
            }
        }
        do {
        for (k = 0; gLaterCmdFDB0[i2][k].count; k++) {
            if (!gLaterCmdFDB0[i2][k].flag) {
                sub_08046034(work.source, work.data, (const u32 *)gLaterCmdF610[i2], gLaterCmdF610[i2][k].count, gLaterCmdFDB0[i2][k].count);
            }
        }
        } while (0);
        sub_08046CC8(i0, i1, i2, i3);
    }
    dst = list;
    if (gUnknown_030052D0.count) {
        src = gLaterCommands_0807EE70[i0];
        while (*(const u8 *)src & 0x3F)
            *dst++ = *src++;
    }
    if (gUnknown_03005290.count) {
        src = ((const u32 (*)[4])gLaterCmdF610)[i1];
        while (*(const u8 *)src & 0x3F)
            *dst++ = *src++;
    }
    if (gUnknown_030052B0.count) {
        src = ((const u32 (*)[4])gLaterCmdFDB0)[i2];
        while (*(const u8 *)src & 0x3F)
            *dst++ = *src++;
    }
    if (gUnknown_030052F0.count) {
        src = gLaterCommands_08080550[i3];
        while (*(const u8 *)src & 0x3F)
            *dst++ = *src++;
    }
    sub_080465B8(&work, list, 1, y << 8, x << 8, priority, 0, (u8)slot);
    CpuSet(work.render->objects, objects, gRenderWork->byte1094 * 4);
    CpuSet(work.render->unknownF8C, names, 0x80);
    return gRenderWork->byte1094;
}
