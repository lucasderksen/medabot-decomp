/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "encoded_label_catalog.h"
#include "encoded_labels.h"
#include "encounter_choices.h"
#include "frame.h"
#include "frame_command_data.h"
#include "graphics.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "part_label_banks.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Setup19D9C { u8 unknown00[0xC4]; u8 byteC4; u8 unknownC5[4]; u8 kindC9; u8 unknownCA[0x15]; u8 byteDF; u8 unknownE0[0x20]; };

extern struct Setup19D9C gSetup19D9C[] asm("gSetupBuffer_03000590");
extern u32 sub_08015924(u32 index);

void sub_08018900(u32 value);
void sub_08019D9C(u32 index, u32 slot, u32 mode, u32 priority);

void sub_08018900(u32 value) {

  u32 slot;
  u8 kind;
  u8 *text;
  u8 *root;
  u32 off;
  if (value > 2)
  {
    return;
  }
  root = gSetupBuffer_03000590;
  off = value << 8;
  if (root[off + 0xDD] == 0)
  {
    return;
  }
  if (root[off + 0xDD] <= 3)
  {
    {
      u32 p = root[off + 0xDD] - 1;
      slot = root[((p * 0x18) + off) + 0x4A];
    }
  }
  else
  {
    switch (root[off + 0xDD] - 4)
    {
      case 0:
        if (root[off + 5] <= 9)
      {
        return;
      }
        sub_08041D04(&gUnknownBytes_083B7F8C[root[off + 1] * 3], text = &gState0TypedWork.bytes[0xEE], 3);
        kind = text[0];
        break;

      case 1:
        if (root[off + 5] <= 0x1D)
      {
        return;
      }
        sub_08041D04(&gUnknownBytes_083B7F8C[root[off + 1] * 3], text = &gState0TypedWork.bytes[0xEE], 3);
        kind = text[1];
        break;

      case 2:
        if (root[off + 5] <= 0x3B)
      {
        return;
      }
        sub_08041D04(&gUnknownBytes_083B7F8C[root[off + 1] * 3], text = &gState0TypedWork.bytes[0xEE], 3);
        kind = text[2];
        break;

      default:
        return;

    }

    sub_08041D04(&gUnknownBytes_083B7E54[kind * 6], text + 0x20, 6);
    text += 0x21;
    slot = *text;
  }
  slot += off;
  { u32 q = (u32)root + 0xB0; slot += q; (*(u8 *)slot)++; }
}

void sub_08019D9C(u32 index, u32 slot, u32 mode, u32 priority) {

    struct FrameObject *object;
    u32 flags;
    u16 offset;

    {
        u32 root = (u32)gFrameObjects;
        { u32 s; object = (struct FrameObject *)(((index * 3 + (s = slot + 0x46)) << 6) + root); }
        object->flags = ((gCounter6ED08_03001800.byte3C + 2) << 10) | 0xC004;
        object->tableSelector = 0;
        object->palette = gState0TypedWork.bytes[0xF0] + 0xB;
        object->priority = priority;
        object->screenY = ((struct FrameObject *)(((index * 4 + 0x5D) << 6) + root))->screenY + 0xFFFC + gState0TypedWork.bytes[0xEF];
        object->flags &= 0xEFFF;
    }
    switch (mode) {
    case 0:
        object->unknown23[0] = gSetup19D9C[index].byteC4;
        break;
    case 1:
        object->unknown23[0] = gSetup19D9C[index].kindC9;
        break;
    case 2:
        object->unknown23[0] = gSetup19D9C[index].byteDF;
        break;
    }
    { u8 b; offset = gState0TypedWork.bytes[0xEE]; b = offset; if (0x80 & b) offset = (u16)(b - 0x100); }
    if (sub_08015924(index) != 0) {
        u32 root = (u32)gFrameObjects; u32 s; struct FrameObject *obj2;
        obj2 = (struct FrameObject *)(((index * 3 + (s = slot + 0x46)) << 6) + root);
        obj2->screenX = ((struct FrameObject *)(((index * 4 + 0x5D) << 6) + root))->screenX - offset;
        if (gState0TypedWork.bytes[0xF1] != 0)
            obj2->flags |= 0x1000;
    } else {
        u32 root = (u32)gFrameObjects; u32 s;
        { struct FrameObject *o = (struct FrameObject *)(((index * 3 + (s = slot + 0x46)) << 6) + root); struct FrameObject *a = (struct FrameObject *)(((index * 4 + 0x5D) << 6) + root); s32 t = (s16)offset; o->screenX = t + (u16)a->screenX; }
    }
}
