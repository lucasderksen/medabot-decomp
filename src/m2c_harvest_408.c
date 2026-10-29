/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "state0_work.h"

extern struct SoundDispatchWork73094 *gSoundDispatchRoot73094;
extern void sub_08073094(void);

void sub_08073274(void);

void sub_08073274(void) {

  u32 value;
  u32 workOrDepth;
  u32 depthAddress;
  struct SoundDispatchWork73094 **rootSlot;

  /* The caller-owned audio work allocation is at least 0x734 bytes. */
  rootSlot = &gSoundDispatchRoot73094;
  workOrDepth = (u32)*rootSlot;
  depthAddress = 0xe6U;
  depthAddress = depthAddress << 0x3U;
  value = workOrDepth + depthAddress;
  value = (u32)*(const u16 *)(value);
  if (value != 0) goto L80732AA;
  L8073286:;
  depthAddress = workOrDepth + depthAddress;
  workOrDepth = (u32)*(const u16 *)(depthAddress);
  value = 0xfffeU;
  if (workOrDepth > value) goto L8073294;
  L8073290:;
  value = workOrDepth + 0x1U;
  *(u16 *)(depthAddress) = (u16)value;
  L8073294:;
  sub_08073094();
  /* The callback may replace the root; reload before balancing its depth. */
  value = (u32)*rootSlot;
  depthAddress = 0xe6U;
  depthAddress = depthAddress << 0x3U;
  workOrDepth = value + depthAddress;
  value = (u32)*(const u16 *)(workOrDepth);
  if (value == 0) goto L80732AA;
  L80732A6:;
  value = value - 0x1U;
  *(u16 *)(workOrDepth) = (u16)value;
  L80732AA:;


  return;
}
