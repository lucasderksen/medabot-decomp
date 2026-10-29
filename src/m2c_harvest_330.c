/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Context5FD10 { u16 unknown00; u16 state; u8 pad04[0x11]; u8 timer; u8 flag; u8 pad17[0x1F]; u16 tileLast; };

extern const u8 gUnknown_080AFA78[64];
extern const u8 gUnknown_08787144[];
extern const u8 gUnknown_08796790[512];
extern const u8 gUnknown_08796990[];
extern const u8 gUnknown_087974DC[];
extern const u8 gUnknown_08797668[];
extern const u8 gUnknown_0879778C[];
extern u8 gUnknown_02030000[0x4480];

void sub_0805FD10(void);

void sub_0805FD10(void) {

  u32 length;
  u16 control;
  struct Context5FD10 *context;
  u32 destination;
  const u8 *additionalTiles;
  u8 byteZero;
  u16 halfZero;
  u8 one;
  struct FrameObject (*frames)[128];
  u8 *cursor;
  volatile u16 *bg0;
  volatile u16 *bg1;
  volatile u16 *bg2;
  volatile u16 *bg3;
  bg0 = (volatile u16 *) 0x04000008;
  one = 1;
  control = 0x1F04;
  *bg0 = control;
  bg1 = (volatile u16 *) 0x0400000A;
  control -= 0xFF;
  *bg1 = control;
  bg2 = (volatile u16 *) 0x0400000C;
  control -= 0xFF;
  *bg2 = control;
  bg3 = (volatile u16 *) 0x0400000E;
  control = 0x3C07;
  *bg3 = control;
  sub_0805BA34(gUnknown_087974DC, *bg0);
  sub_0805BA34(gUnknown_08797668, *bg2);
  sub_0805BA34(gUnknown_0879778C, *bg3);
  length = sub_08044D0C(gUnknown_08796990, gUnknown_02030000);
  CpuSet(gUnknown_02030000, (void *) 0x06004000, (length << 10) >> 11);
  additionalTiles = gMain2AdditionalTiles_08785EC0;
  destination = 0x06000000;
  destination += length;
  destination += 0x4000;
  LeDecompress(additionalTiles, (void *) destination);
  context = (struct Context5FD10 *) gMainContextPointer_03006F74;
  context->tileLast = (length >> 5) - 1;
  byteZero = 0;
  halfZero = 0;
  CpuFastSet(gUnknown_08796790, (void *) 0x05000000, 0x80);
  CpuFastSet(gUnknown_080AFA78, (void *) 0x05000200, 0x10);
  LeDecompress(gUnknown_08787144, (void *) 0x06010000);
  frames = &gFrameObjects;
  (*frames)[0].flags = 0x8A20;
  (*frames)[0].tableSelector = 2;
  (*frames)[0].screenX = 0x78;
  (*frames)[0].screenY = -0x20;
  (*frames)[0].palette = byteZero;
  (*frames)[0].frameAndGroup = 0x108;
  (*frames)[0].scaleX = 0x80;
  (*frames)[0].scaleY = 0x80;
  (*frames)[0].angle = halfZero;
  (*frames)[1].flags = 0x8220;
  cursor = ((u8 *) frames) + 0x5C;
  *cursor = 2;
  cursor -= 0x1A;
  *((u16 *) cursor) = 0x78;
  (*frames)[1].screenY = -0x40;
  (*frames)[1].palette = one;
  (*frames)[1].frameAndGroup = 0x109;
  cursor = ((u8 *) frames) + 0x48;
  *cursor = 0x80;
  ++cursor;
  *cursor = 0x80;
  cursor += 0xF;
  *((u16 *) cursor) = halfZero;
  ((struct Context5FD10 *) gMainContextPointer_03006F74)->state = halfZero;
  ((struct Context5FD10 *) gMainContextPointer_03006F74)->timer = 0x3C;
  ((struct Context5FD10 *) gMainContextPointer_03006F74)->flag = byteZero;
  ++gUnknown_0300137C;
}
