/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "composite_graphics.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "encounter_parts.h"
#include "fallback_map_assets.h"
#include "frame.h"
#include "graphics.h"
#include "inventory_kind_data.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "map_metadata.h"
#include "native_le_streams.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Main2PartContext
{
    u8 unknown00[5];
    u8 byte05;
    u8 unknown06[0x13];
    u8 selection19;
    u8 row1A;
    u8 unknown1B;
    u32 total1C;
    s8 count20;
};
struct Main2PartRecord
{
    u16 identifier;
    u8 byte2;
    u8 byte3;
    u32 value;
};

extern u8 gUnknown_03002420;
extern void sub_0805B0D8(void);
extern void sub_0805B188(s32 index, s32 part, s32 slot);

void sub_080619B0(void);

void sub_080619B0(void) {

  s8 i;
  struct Main2PartContext **rootp;
  const u8 *part;
  struct Main2PartRecord *record;
  struct Main2PartRecord *records;
  u32 *values;
  const u8 *table;
  *((volatile u16 *) 0x04000000) |= 0x200;
  ((volatile u16 *) 0x0400000A)[0] = 0x1B05;
  ((volatile u16 *) 0x0400000A)[1] = 0x1A06;
  LeDecompress(gNativeLeStream_08785FB4, (void *) 0x06010000);
  gFrameObjects[8].flags = 0x8400;
  gFrameObjects[8].tableSelector = 2;
  gFrameObjects[8].palette = 2;
  gFrameObjects[8].frameAndGroup = 6;
  for (i = 0; i <= 1; i++)
  {
    gFrameObjects[i + 11].flags = 0x8000;
    gFrameObjects[i + 11].tableSelector = 2;
    gFrameObjects[i + 11].palette = 2;
    gFrameObjects[i + 11].frameAndGroup = 5;
    gFrameObjects[i + 11].screenX = (i * 24) + 0xD0;
    gFrameObjects[i + 11].screenY = (((struct Main2PartContext *) gMainContextPointer_03006F74)->row1A * 16) + 0x54;
  }

  gFrameObjects[11].flags |= 0x1000;
  for (i = 0; i <= 1; i++)
  {
    gFrameObjects[i + 0x68].flags = 0x8400;
    gFrameObjects[i + 0x68].tableSelector = 2;
    gFrameObjects[i + 0x68].palette = 2;
    gFrameObjects[i + 0x68].frameAndGroup = 8;
    gFrameObjects[i + 0x68].screenX = 0x1C;
    gFrameObjects[i + 0x68].screenY = (i != 0) ? (0x95) : (0x44);
  }

  gFrameObjects[0x69].flags |= 0x2000;
  for (i = 0; i <= 3; i++)
  {
    gFrameObjects[i + 0x6A].flags = 0x8400;
    gFrameObjects[i + 0x6A].tableSelector = 2;
    gFrameObjects[i + 0x6A].palette = 3;
    gFrameObjects[i + 0x6A].screenX = 0x78;
    gFrameObjects[i + 0x6A].screenY = (i * 16) + 0x50;
  }

  for (i = 0; i <= 3; i++)
  {
    gFrameObjects[i + 0x6E].flags = 0x8400;
    gFrameObjects[i + 0x6E].tableSelector = 2;
    gFrameObjects[i + 0x6E].palette = 3;
    gFrameObjects[i + 0x6E].frameAndGroup = i + 0x1D;
    gFrameObjects[i + 0x6E].screenX = 0x90;
    gFrameObjects[i + 0x6E].screenY = (i * 16) + 0x50;
  }

  *((volatile u16 *) 0x04000052) = 0x10;
  LeDecompress(gNativeLeStream_084C8034, (void *) 0x06017400);
  gFrameObjects[8].screenX = 8;
  gFrameObjects[8].screenY = (((struct Main2PartContext *) gMainContextPointer_03006F74)->row1A * 16) + 0x54;
  if ((*((struct Main2PartContext **) (&gMainContextPointer_03006F74)))->byte05 == 1)
  {
    sub_0805B0D8();
  }
  else
  {
    for (i = 0, records = (struct Main2PartRecord *) 0x02040000, values = (u32 *) 0x02040004; i <= 3; i++)
    {
      /* Constant address: the symbol form is PRE-hoisted by gcse into a register, unlike the reference. */
      table = (const u8 *)0x084838E4;
      part = &table[(gUnknown_03002420 * 4) + i];
      if ((*part) == 0xFF)
      {
        goto partsDone;
      }
      if (((*part) == 0x20) && ((*((struct Main2PartContext **) (&gMainContextPointer_03006F74)))->selection19 != 3))
      {
        goto partsDone;
      }
      record = (struct Main2PartRecord *)(i * 8 + (u32)records);
      record->identifier = *part;
      record->byte2 = gObjectHalfwordBytes[(record->identifier * 2) + ((*((struct Main2PartContext **) (&gMainContextPointer_03006F74)))->selection19 * 0xF0)];
      sub_08042B58(record->identifier, (*((struct Main2PartContext **) (&gMainContextPointer_03006F74)))->selection19, gUnknown_0300052E);
      record->byte3 = gUnknown_0300052E[3];
      values[i * 2] = gUnknown_0300052E[0xB] * 100;
    }

    partsDone:
    ((struct Main2PartRecord *) 0x02040000)[i].byte2 = 0;
    ((struct Main2PartContext *) gMainContextPointer_03006F74)->count20 = i;
  }
  for (i = 0; i <= 3; i++)
  {
    if (((u8) ((struct Main2PartContext *) gMainContextPointer_03006F74)->count20) <= i)
    {
      goto callsDone;
    }
    sub_0805B188(((struct Main2PartRecord *) 0x02040000)[i].identifier, ((struct Main2PartContext *) gMainContextPointer_03006F74)->selection19, i);
  }
  callsDone:
  ((struct Main2PartContext *) gMainContextPointer_03006F74)->total1C = 0;
  for (i = 0; i < ((u8) ((struct Main2PartContext *) gMainContextPointer_03006F74)->count20); i++)
  {
    ((struct Main2PartContext *) gMainContextPointer_03006F74)->total1C += ((u8 *) gObjectSortEntries)[i] * (*((u32 *) ((i * 8) + 0x02040004)));
  }

  if (((struct Main2PartContext *) gMainContextPointer_03006F74)->byte05 != 0)
  {
    ((struct Main2PartContext *) gMainContextPointer_03006F74)->total1C >>= 1;
  }
  if (((struct Main2PartContext *) gMainContextPointer_03006F74)->total1C > 99999)
  {
    ((struct Main2PartContext *) gMainContextPointer_03006F74)->total1C = 99999;
  }
  gUnknown_0300137C++;
}
