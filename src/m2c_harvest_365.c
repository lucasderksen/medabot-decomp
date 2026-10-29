/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct MedalDisplayWork { /* Observed fields plus the received 64-byte packet. */
    u8 before36[0x36];
    u16 tile;
    u8 before3C[4];
    s16 timer;
    u8 before40[2];
    u16 savedTiles[4];
    u8 before7A[0x32];
    s8 mode;
    u8 before230[0x1B5];
    struct InventoryRecord received;
};

extern const u8 *const gDebugMedalMetadata_083B6590[];
extern u32 sub_0807CEC8(u32, u32);
extern u32 sub_0807CF40(u32, u32);
extern void sub_08062D60(void);

void sub_0806412C(void);

void sub_0806412C(void) {

  volatile u16 *tensCursor;
  volatile u16 *onesCursor;
  s16 timer;
  s32 characterIndex;
  u32 tensTile;
  u32 onesTile;
  u32 baseTile;
  u8 percent;
  void *tensWork;
  void *onesWork;
  struct MedalDisplayWork *entryWork;
  u32 textRoot;
  u32 metadataRoot;
  u8 *destination;
  u32 entryRoot;
  sub_08062D60();
  entryWork = gMainContextPointer_03006F74;
  timer = ++entryWork->timer;
  if (((s32) timer) > 0xF)
  {
    gUnknown_0300137C += 1;
    if (entryWork->mode == 0)
    {
      gFrameObjects->flags &= 0xBFFF;
      return;
    }
    gFrameObjects->flags |= 0x4000;
    percent = ((struct MedalDisplayWork *) entryWork)->received.byte5;
    sub_08040DB8(entryWork->received.unknown06 + 4, 0x20U, 4, 4, 0xAU, 2U, 0U, 1U);
    characterIndex = 0;
    textRoot = (u32) gDebugMenuTextBuffer;
    metadataRoot = (u32) gDebugMedalMetadata_083B6590;
    do
    {
      destination = (u8 *) (characterIndex + textRoot);
      entryRoot = (u32) (*((const u8 * const *) ((((u32) ((struct MedalDisplayWork *) gMainContextPointer_03006F74)->received.byte1) << 2) + metadataRoot)));
      *destination = *((const u8 *) (entryRoot + characterIndex));
      characterIndex += 1;
    }
    while (characterIndex <= 9);
    sub_08040DB8(gDebugMenuTextBuffer, 0x10U, 5, 8, 0xAU, 1U, 1U, 1U);
    *((volatile u16 *) (0x06000218 + (((((u16) (*((volatile u16 *) 0x0400000C))) >> 8) & 0x1F) << 0xB))) = (u16) ((struct MedalDisplayWork *) gMainContextPointer_03006F74)->savedTiles[0];
    *((volatile u16 *) (0x0600021A + (((((u16) (*((volatile u16 *) 0x0400000C))) >> 8) & 0x1F) << 0xB))) = (u16) ((struct MedalDisplayWork *) gMainContextPointer_03006F74)->savedTiles[1];
    *((volatile u16 *) (0x06000258 + (((((u16) (*((volatile u16 *) 0x0400000C))) >> 8) & 0x1F) << 0xB))) = (u16) ((struct MedalDisplayWork *) gMainContextPointer_03006F74)->savedTiles[2];
    *((volatile u16 *) (0x0600025A + (((((u16) (*((volatile u16 *) 0x0400000C))) >> 8) & 0x1F) << 0xB))) = (u16) ((struct MedalDisplayWork *) gMainContextPointer_03006F74)->savedTiles[3];
    if (percent == 0x64)
    {
      *((volatile u16 *) (0x0600021A + (((((u16) (*((volatile u16 *) 0x0400000A))) >> 8) & 0x1F) << 0xB))) = (s16) ((((struct MedalDisplayWork *) gMainContextPointer_03006F74)->tile + 0x14) | 0x7000);
      *((volatile u16 *) (0x0600025A + (((((u16) (*((volatile u16 *) 0x0400000A))) >> 8) & 0x1F) << 0xB))) = (s16) ((((struct MedalDisplayWork *) gMainContextPointer_03006F74)->tile + 0x15) | 0x7000);
      *((volatile u16 *) (0x0600021C + (((((u16) (*((volatile u16 *) 0x0400000A))) >> 8) & 0x1F) << 0xB))) = (s16) ((((struct MedalDisplayWork *) gMainContextPointer_03006F74)->tile + 0x16) | 0x7000);
      *((volatile u16 *) (0x0600025C + (((((u16) (*((volatile u16 *) 0x0400000A))) >> 8) & 0x1F) << 0xB))) = (s16) ((((struct MedalDisplayWork *) gMainContextPointer_03006F74)->tile + 0x17) | 0x7000);
    }
    else
    {
      tensCursor = (volatile u16 *) ((((((u16) (*((volatile u16 *) 0x0400000A))) >> 8) & 0x1F) << 0xB) + 0x0600021A);
      tensWork = gMainContextPointer_03006F74;
      tensTile = (((u32) sub_0807CEC8(percent, 0xA)) << 0x18) >> 0x17;
      *tensCursor = (((struct MedalDisplayWork *) tensWork)->tile + tensTile) | 0x7000;
      *((volatile u16 *) (0x0600025A + (((((u16) (*((volatile u16 *) 0x0400000A))) >> 8) & 0x1F) << 0xB))) = (s16) (((((struct MedalDisplayWork *) gMainContextPointer_03006F74)->tile + tensTile) + 1) | 0x7000);
      onesCursor = (volatile u16 *) ((((((u16) (*((volatile u16 *) 0x0400000A))) >> 8) & 0x1F) << 0xB) + 0x0600021C);
      onesWork = gMainContextPointer_03006F74;
      onesTile = (((u32) sub_0807CF40(percent, 0xA)) << 0x18) >> 0x17;
      *onesCursor = (((struct MedalDisplayWork *) onesWork)->tile + onesTile) | 0x7000;
      *((volatile u16 *) (0x0600025C + (((((u16) (*((volatile u16 *) 0x0400000A))) >> 8) & 0x1F) << 0xB))) = (s16) (((((struct MedalDisplayWork *) gMainContextPointer_03006F74)->tile + onesTile) + 1) | 0x7000);
    }
    CpuFastSet((((struct MedalDisplayWork *) gMainContextPointer_03006F74)->received.byte1 << 7) + gUnknownBytes_084C29D8, (void *) ((((struct MedalDisplayWork *) gMainContextPointer_03006F74)->tile << 5) + 0x06003F80), 0x20U);
    {
      u32 shiftedTile = ((u32) (((struct MedalDisplayWork *) gMainContextPointer_03006F74)->tile - 4)) << 16;
      baseTile = 0x60000000;
      baseTile |= shiftedTile;
      baseTile >>= 16;
    }
    {
      u32 screenWord = (((*((volatile u16 *) 0x0400000A)) >> 8) & 31) << 11;
      u32 vram = screenWord;
      vram += 0x06000206;
      *((volatile u16 *) vram) = baseTile;
      vram += 2;
      *((volatile u16 *) vram) = baseTile + 1;
      vram += 0x3E;
      *((volatile u16 *) vram) = baseTile + 2;
      vram += 2;
      *((volatile u16 *) vram) = baseTile + 3;
    }
  }
  else
  {
    if (((s32) timer) <= 7)
    {
      gFrameObjects->scaleX = 0x40 - (entryWork->timer * 8);
    }
    else
    {
      gFrameObjects->scaleX = 1;
    }
    if (((s32) ((s16) ((struct MedalDisplayWork *) gMainContextPointer_03006F74)->timer)) > 1)
    {
      gFrameObjects->scaleY = (((s16) ((struct MedalDisplayWork *) gMainContextPointer_03006F74)->timer) * 4) + 0x38;
      gFrameObjects->screenY = 0x38 - ((((s16) ((struct MedalDisplayWork *) gMainContextPointer_03006F74)->timer) - 2) * 8);
    }
  }
}
