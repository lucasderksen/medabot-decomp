/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "bios_lz77.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_command_data.h"
#include "gba.h"
#include "graphics.h"
#include "later_helpers.h"
#include "link_menu.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "render_work.h"
#include "scene_view.h"
#include "serial.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "state0_work.h"
#include "tile_text.h"

struct LaterTemplate { u32 words[4]; u8 count; u8 pad[7]; };
struct LaterCmd { u8 count:6; u8 b6:2; u8 b8:7; u8 flag:1; u8 b2; u8 b3; };
struct LaterExtra { u8 unknown00[4]; s32 first; u32 second; u32 third; u32 fourth; u8 unknown14[0x14]; u32 slot; u32 flags; };
struct LaterSaved { struct LaterTemplate parts[4]; };
struct LaterDisplayWork { struct RenderWork *render; const void *source; void *data; struct LaterSaved saved[2]; };

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

void sub_08046D1C(void *unused, struct RecordDisplayWork *work, u32 first, u32 second, u32 third, u32 fourth, u32 y, u32 x, u32 priority, u32 palette, u32 flags, u32 slot);

void sub_08046D1C(void *unused, struct RecordDisplayWork *work, u32 first, u32 second, u32 third, u32 fourth, u32 y, u32 x, u32 priority, u32 palette, u32 flags, u32 slot) {

  u32 index = slot;
  u16 tileBase;
  u32 bits;
  u32 visible;
  u16 base;
  const u32 *c0;
  const u32 *c1;
  const u32 *c2;
  const u32 *c3;
  const u32 *src;
  u32 *dst;
  s32 k;
  if (!(flags & 4))
  {
    if (gState0TypedWork.bytes[0x130])
    {
      gState0TypedWork.bytes[0x131] = 1;
    }
    ((struct LaterExtra *) gRecordDisplayExtraPointer)[slot].flags = (((struct LaterExtra *) gRecordDisplayExtraPointer)[slot].flags | 1) & (~8);
    ((struct LaterExtra *) gRecordDisplayExtraPointer)[slot].first = first;
    ((struct LaterExtra *) gRecordDisplayExtraPointer)[slot].second = second;
    ((struct LaterExtra *) gRecordDisplayExtraPointer)[slot].third = third;
    ((struct LaterExtra *) gRecordDisplayExtraPointer)[slot].fourth = fourth;
    ((struct LaterExtra *) gRecordDisplayExtraPointer)[slot].slot = slot;
    return;
  }
  bits = ((struct LaterExtra *) gRecordDisplayExtraPointer)[slot].flags;
  visible = bits & 2;
  if (visible)
  {
    base = 0;
    if (flags & 2)
      base = 0x160;
    gUnknown_030052D0 = gLaterTemplate_0807EE10;
    gUnknown_030052B0 = gLaterTemplate_0807EE28;
    gUnknown_03005290 = gLaterTemplate_0807EE40;
    gUnknown_030052F0 = gLaterTemplate_0807EE58;
    first = ((struct LaterExtra *) gRecordDisplayExtraPointer)[index].first;
    second = ((struct LaterExtra *) gRecordDisplayExtraPointer)[index].second;
    third = ((struct LaterExtra *) gRecordDisplayExtraPointer)[index].third;
    fourth = ((struct LaterExtra *) gRecordDisplayExtraPointer)[index].fourth;
    slot = ((struct LaterExtra *) gRecordDisplayExtraPointer)[index].slot;
    if (((s32) first) < 0)
    {
      gUnknown_030052D0.count = 0;
      gUnknown_03005290.count = 0;
      gUnknown_030052B0.count = 0;
    }
    else
    {
      c0 = gLaterCommands_0807EE70[first];
      gUnknown_030052D0.count = (c0[0] << 26) >> 26;
      c1 = ((const u32 (*)[4])gLaterCmdF610)[second];
      gUnknown_03005290.count = (c1[0] << 26) >> 26;
      c2 = ((const u32 (*)[4])gLaterCmdFDB0)[third];
      gUnknown_030052B0.count = (c2[0] << 26) >> 26;
      c3 = gLaterCommands_08080550[fourth];
      gUnknown_030052F0.count = (c3[0] << 26) >> 26;
      tileBase = base + 0x140;
      sub_08045E6C(work->source, c0, (c0[0] << 26) >> 26, palette, work->data, &tileBase, slot);
      tileBase = base + 0x1A0;
      sub_08045E6C(work->source, c1, (c1[0] << 26) >> 26, palette, work->data, &tileBase, slot);
      tileBase = base + 0x1E0;
      sub_08045E6C(work->source, c2, (c2[0] << 26) >> 26, palette, work->data, &tileBase, slot);
      tileBase = base + 0x220;
      sub_08045E6C(work->source, c3, (c3[0] << 26) >> 26, palette, work->data, &tileBase, slot);
      if (index)
      {
        for (k = 0; gLaterCmdF610[second][k].count; k++)
        {
          if (!gLaterCmdF610[second][k].flag)
            sub_08046034(work->source, work->data, (const u32 *)gLaterCmdFDB0[second], gLaterCmdFDB0[second][k].count, gLaterCmdF610[second][k].count);
        }
        for (k = 0; gLaterCmdFDB0[third][k].count; k++)
        {
          if (!gLaterCmdFDB0[third][k].flag)
            sub_08046034(work->source, work->data, (const u32 *)gLaterCmdF610[third], gLaterCmdF610[third][k].count, gLaterCmdFDB0[third][k].count);
        }
        sub_08046CC8(first, second, third, fourth);
      }
    }
    ((struct LaterDisplayWork *)work)->saved[index].parts[0] = gUnknown_030052D0;
    ((struct LaterDisplayWork *)work)->saved[index].parts[1] = gUnknown_03005290;
    ((struct LaterDisplayWork *)work)->saved[index].parts[2] = gUnknown_030052B0;
    ((struct LaterDisplayWork *)work)->saved[index].parts[3] = gUnknown_030052F0;
    {
      u32 f = ((struct LaterExtra *) gRecordDisplayExtraPointer)[index].flags;
      f &= ~2;
      f |= 4;
      f |= 8;
      ((struct LaterExtra *) gRecordDisplayExtraPointer)[index].flags = f;
    }
    return;
  }
  if (bits & 8)
  {
    u32 list[32];
    memset(list, 0, sizeof(list));
    gState0TypedWork.bytes[0x131] = visible;
    first = ((struct LaterExtra *) gRecordDisplayExtraPointer)[index].first;
    second = ((struct LaterExtra *) gRecordDisplayExtraPointer)[index].second;
    third = ((struct LaterExtra *) gRecordDisplayExtraPointer)[index].third;
    fourth = ((struct LaterExtra *) gRecordDisplayExtraPointer)[index].fourth;
    gUnknown_030052D0 = ((struct LaterDisplayWork *)work)->saved[index].parts[0];
    gUnknown_03005290 = ((struct LaterDisplayWork *)work)->saved[index].parts[1];
    gUnknown_030052B0 = ((struct LaterDisplayWork *)work)->saved[index].parts[2];
    gUnknown_030052F0 = ((struct LaterDisplayWork *)work)->saved[index].parts[3];
    dst = list;
    if (gUnknown_030052D0.count)
    {
      src = gLaterCommands_0807EE70[first];
      while ((*((const u8 *) src)) & 0x3F)
      {
        *(dst++) = *(src++);
      }

    }
    if (gUnknown_03005290.count)
    {
      src = ((const u32 (*)[4])gLaterCmdF610)[second];
      while ((*((const u8 *) src)) & 0x3F)
      {
        *(dst++) = *(src++);
      }

    }
    if (gUnknown_030052B0.count)
    {
      src = ((const u32 (*)[4])gLaterCmdFDB0)[third];
      while ((*((const u8 *) src)) & 0x3F)
      {
        *(dst++) = *(src++);
      }

    }
    if (gUnknown_030052F0.count)
    {
      src = gLaterCommands_08080550[fourth];
      while ((*((const u8 *) src)) & 0x3F)
      {
        *(dst++) = *(src++);
      }

    }
    sub_080465B8(work, list, 1, y << 8, x << 8, (s16) priority, 0, (u8) slot);
  }
}
