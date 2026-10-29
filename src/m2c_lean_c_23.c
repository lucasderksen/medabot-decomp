/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "bios_lz77_streams.h"
#include "composite_graphics.h"
#include "compression.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "effect_work.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "scene_view.h"
#include "serial.h"
#include "sound_samples.h"
#include "sound_voice.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Main2CursorContext
{
    u8 unknown00[8];
    s32 word08;
    u8 unknown0C;
    u8 byte0D;
    u8 byte0E;
    u8 unknown0F[0x27];
    u16 halfword36;
};
struct MenuContext66460 { u8 pad00[5]; u8 cursor05; u8 pad06[0x4A]; u8 area50[0x2A]; s8 flag7A; };

extern const u8 gBiosLz77Stream_08796340[];
extern const u8 gBiosLz77Stream_0879660C[];
extern struct MenuContext66460 *gMenuContext66460 asm("gMainContextPointer_03006F74");
extern u8 gUnknown_03000584;

void sub_0805E478(void);
void sub_08066460(void);

void sub_0805E478(void) {

  volatile u16 *bg1 = (volatile u16 *) 0x0400000A;
  volatile u16 *bg2;
  volatile u16 *bg3;
  u32 length;
  u32 control;
  u8 index;
  u32 zero0;
  u32 zero1;
  u16 tile;
  u16 *map;
  u32 cellTopRight;
  u32 offset;
  u32 cellBottomRight;
  u32 cellBottomLeft;
  s32 x;
  control = 0x1F05;
  *bg1 = control;
  bg2 = (volatile u16 *) 0x0400000C;
  control = 0x1E06;
  *bg2 = control;
  bg3 = (volatile u16 *) 0x0400000E;
  control = 0x1D07;
  *bg3 = control;
  sub_0805BA34(gBiosLz77Stream_08796060, *bg1);
  sub_0805BA34(gBiosLz77Stream_08796340, *bg2);
  sub_0805BA34(gBiosLz77Stream_0879660C, *bg3);
  length = sub_08044D0C(gBiosLz77Stream_0879481C, (void *) 0x02030000);
  CpuSet((void *) 0x02030000, (void *) 0x06004000, (length << 10) >> 11);
  ((struct Main2CursorContext *) gMainContextPointer_03006F74)->halfword36 = (length >> 5) - 1;
  {
    const u8 *source = gUnknownBytes_084C29D8;
    u32 destination = 0x06000000;
    destination += length;
    destination += 0x4000;
    CpuSet(source, (void *) destination, 0x800);
  }
  zero0 = 0;
  CpuFastSet(&zero0, (void *) 0x05000000, 0x01000080);
  zero1 = 0;
  CpuFastSet(&zero1, (void *) 0x05000200, 0x01000080);
  LeDecompress(gMain2ObjectTiles_08785FB4, (void *) 0x06010000);
  LeDecompress(gMain2SharedObjectTiles_084C8034, (void *) 0x06017400);
  for (index = 0; index <= 1; index++)
  {
    gFrameObjects[index].flags = 0xC000;
    gFrameObjects[index].tableSelector = 2;
    gFrameObjects[index].palette = 14;
    gFrameObjects[index].frameAndGroup = 8;
  }

  gFrameObjects[0].flags |= 0x2000;
  cellTopRight = 0x060000C6;
  cellBottomRight = 0x06000106;
  cellBottomLeft = 0x06000104;
  gFrameObjects[20].flags = 0x8000;
  gFrameObjects[20].tableSelector = 2;
  gFrameObjects[20].screenX = 16;
  gFrameObjects[20].screenY = 16;
  gFrameObjects[20].palette = 0;
  gFrameObjects[20].frameAndGroup = 0x23;
  if (gUnknown_03000584 == 0)
  {
    gFrameObjects[20].flags |= 0x4000;
  }
  else
  {
    tile = ((struct Main2CursorContext *) gMainContextPointer_03006F74)->halfword36 + ((gInventoryRecords[gQuantityResult_030017EC].byte1 * 4) + 1);
    tile |= 0x6000;
    offset = (((*((volatile u16 *) 0x0400000A)) >> 8) & 0x1F) << 11;
    map = (u16 *) (offset + 0x060000C4);
    *map = tile;
    map = (u16 *) (offset + cellTopRight);
    *map = tile + 1;
    map = (u16 *) (offset + cellBottomLeft);
    *map = tile + 2;
    map = (u16 *) (offset + cellBottomRight);
    *map = tile + 3;
  }
  for (index = 0; index <= 1; index++)
  {
    gFrameObjects[index + 2].flags = 0x8000;
    gFrameObjects[index + 2].tableSelector = 2;
    gFrameObjects[index + 2].palette = 14;
    gFrameObjects[index + 2].frameAndGroup = 5;
  }

  gFrameObjects[3].flags |= 0x1000;
  ((struct Main2CursorContext *) gMainContextPointer_03006F74)->byte0D = 0;
  ((struct Main2CursorContext *) gMainContextPointer_03006F74)->byte0E = 0;
  ((struct Main2CursorContext *) gMainContextPointer_03006F74)->word08 = 0;
  x = (((struct Main2CursorContext *) gMainContextPointer_03006F74)->byte0D * 8) + 20;
  gFrameObjects[0].screenX = x;
  gFrameObjects[0].screenY = (((struct Main2CursorContext *) gMainContextPointer_03006F74)->byte0E * 16) + ((s16) ((((struct Main2CursorContext *) gMainContextPointer_03006F74)->word08 / 2) + 0x40));
  gFrameObjects[1].screenX = x;
  gFrameObjects[1].screenY = (((struct Main2CursorContext *) gMainContextPointer_03006F74)->byte0E * 16) - ((s16) ((((struct Main2CursorContext *) gMainContextPointer_03006F74)->word08 / 2) - 0x50));
  gFrameObjects[4].flags = 0xC000;
  gFrameObjects[4].tableSelector = 2;
  gFrameObjects[4].palette = 14;
  gFrameObjects[4].frameAndGroup = 0x26;
  gUnknown_0300137C++;
}

void sub_08066460(void) {


    if (gMenuContext66460->flag7A != 0) {
        gMainSerialOutgoingWork.word06 = 0xFE0F;
    } else if (gUnknown_03000B90 != 0) {
        if ((0xFF00 & gMainSerialOutgoingWork.words[gUnknown_03000B90 == 0][1]) == 0xEF00) {
            gMenuContext66460->cursor05 = gMainSerialOutgoingWork.words[gUnknown_03000B90 == 0][1];
            gMenuContext66460->flag7A = 1;
        } else if (gMainSerialOutgoingWork.words[gUnknown_03000B90 == 0][1] == 0xFE0F) {
            gMainSerialOutgoingWork.word06 = 0xFE0F;
        }
    } else {
        gMenuContext66460->flag7A = gUnknown_03000B90;
        gMainSerialOutgoingWork.word06 = gMenuContext66460->cursor05 | 0xEF00;
    }
    if (gMainSerialOutgoingWork.words[1][1] == 0xFE0F) {
        if (gMenuContext66460->cursor05 == 4) {
            gUnknown_0300137C = 8;
            sub_0803FB0C();
            return;
        }
        sub_080656DC(gMenuContext66460->area50, 0, 0, 1, 0xC0);
        gUnknown_0300137C += 2;
    }
}
