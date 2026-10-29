/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_commands.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "fresh_helpers.h"
#include "palette_transfer_helpers.h"
#include "record_helpers.h"
#include "state0_display.h"
#include "state0_work.h"

struct PaletteRouteWork4E370 {u8 unknown00[0xC28];u8 first;u8 unknownC29[0x33];u8 current;u8 unknownC5D[12];u8 previous;u8 unknownC6A[0x2A];u8 mode;};
struct PaletteRouteMode4E370 {u8 unknown00;u8 mode;};
struct PaletteRouteDma4E370 {const void *source;void *destination;u32 control;};

extern const u8 gUnknown_083D2B18[];
extern struct PaletteRouteMode4E370 gUnknown_03006F40;
extern struct PaletteRouteWork4E370 gContinuedWork_030057E0;
extern u8 gUnknown_0202F800[];
extern void sub_08048288(void);
extern void sub_08050290(void);
extern void sub_0805330C(void);

void sub_0804E370(void);

void sub_0804E370(void) {

  struct PaletteRouteWork4E370 *root = &gContinuedWork_030057E0;
  const u8 *modeByteSource;
  const u8 *table = gUnknown_083D2B18;
  u8 first = *((const u8 *) (((u32) table) + ((u32) root->mode)));
  u32 direct;
  s32 index;
  void *destination;
  u32 paletteBase;
  volatile struct PaletteRouteDma4E370 *dma;
  volatile struct PaletteRouteDma4E370 *directDma;
  root->previous = (root->current = first);
  modeByteSource = (const u8 *) (((u32) table) + ((u32) root->mode));
  root->first = *modeByteSource;
  sub_0805330C();
  sub_08048288();
  directDma = (volatile struct PaletteRouteDma4E370 *) 0x040000D4;
  switch (gUnknown_03006F40.mode)
  {
    case 1:

    case 3:

    case 5:

    case 6:
      direct = 1;
      break;

    default:
      direct = 0;
      break;

  }

  index = sub_08048684(0);
  paletteBase = (u32) gPaletteSourcePointers_083F83C0;
  if (0 == (*((const void * const *) ((((u32) index) << 2) + paletteBase))))
  {
    index = 1;
  }
  if (direct)
  {
    dma = directDma;
    dma->source = *((const void * const *) (((u32) gPaletteSourcePointers_083F83C0) + (((u32)index)<<2)));
    destination = (void *) 0x05000200;
  }
  else
  {
    dma = (volatile struct PaletteRouteDma4E370 *) 0x040000D4;
    dma->source = *((const void * const *) (((u32) gPaletteSourcePointers_083F83C0) + (((u32) index) << 2)));
    destination = gUnknown_0202F800;
  }
  dma->destination = destination;
  dma->control = 0x84000008;
  (void) dma->control;
  sub_08050290();
}
