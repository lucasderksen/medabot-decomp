/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "frame_objects.h"
#include "state0_callbacks.h"

extern const u8 *const gUnknown_083B61F0;
extern struct Counter6ED08 gCounter6ED08_03001800;
extern u8 gUnknown_030018D2[];

void sub_080280D4(void);
void sub_0802976C(void);

void sub_080280D4(void)
{
  u32 value;
  u32 address;
  u32 frameRoot;
  u32 comparisonLeft;
  u32 comparisonRight;
  u32 difference;
  address = (u32) (&gFrameObjects);
  frameRoot = 0x867U;
  value = address + frameRoot;
  difference = value;
  value = (u32) (*((const u8 *) value));
  frameRoot = address + 0x0U;
  difference = frameRoot;
  /* The address temporary supplies a genuine zero comparison input. */
  address = 0;
  comparisonLeft = value;
  comparisonRight = 0x10U;
  difference = comparisonLeft - comparisonRight;
  if (address != difference)
  {
    goto L80280FC;
  }
  L80280E4:
  ;

  value = 0x3eU;
  difference = value;
  sub_08074DE0((u32) value);
  address = (u32) (&gCounter6ED08_03001800);
  address = address + 0xaaU;
  difference = address;
  goto L802811E;
  L80280FC:
  ;

  comparisonLeft = value;
  ;
  difference = comparisonLeft - comparisonRight;
  if (comparisonLeft > 0x7U)
  {
    goto L8028110;
  }
  L8028100:
  ;

  value = 0x848U;
  address = frameRoot + value;
  difference = address;
  value = (u32) (*((const u8 *) address));
  value = value + 0x8U;
  difference = value;
  goto L8028118;
  L8028110:
  ;

  value = 0x848U;
  address = frameRoot + value;
  difference = address;
  value = (u32) (*((const u8 *) address));
  value = value - 0x8U;
  difference = value;
  L8028118:
  ;

  *((u8 *) address) = (u8) value;
  value = 0x867U;
  address = frameRoot + value;
  difference = address;
  L802811E:
  ;

  value = (u32) (*((const u8 *) address));
  value = value + 0x1U;
  difference = value;
  *((u8 *) address) = (u8) value;
  return;
}



void sub_0802976C(void)
{
  /* Three selected slots share the pointer word at 083B61F0. */
  u32 value;
  u32 address;
  u32 entry;
  u32 packedIndex;
  u32 frameOffset;
  u32 finished;
  u32 commandTableAddress;
  u32 selectionAddress;
  u32 comparisonLeft;
  u32 comparisonRight;
  u32 difference;
  finished = 0x0U;
  difference = finished;
  entry = 0x0U;
  difference = entry;
  value = (u32) (&gUnknown_030018D2);
  selectionAddress = value;
  frameOffset = 0x84U;
  difference = frameOffset;
  frameOffset = frameOffset << 0x4U;
  difference = frameOffset;
  packedIndex = 0x84U;
  difference = packedIndex;
  packedIndex = packedIndex << 0x16U;
  difference = packedIndex;
  address = (u32) (&gUnknown_083B61F0);
  commandTableAddress = address;
  L8029788:
  ;

  address = selectionAddress;
  value = entry + address;
  difference = value;
  value = (u32) (*((const u8 *) value));
  comparisonLeft = value;
  comparisonRight = 0x0U;
  difference = comparisonLeft - comparisonRight;
  if (difference == 0)
    goto L80297AA;
  L8029792:
  ;

  address = commandTableAddress;
  value = (u32) (*((const u8 * const *) address));
  address = packedIndex >> 0x18U;
  difference = address;
  sub_08040BD8((const u8 *) value, (u8) address);
  value = (u32) (&gFrameObjects);
  value = frameOffset + value;
  difference = value;
  value = value + 0x22U;
  difference = value;
  value = (u32) (*((const u8 *) value));
  comparisonLeft = value;
  comparisonRight = 0xffU;
  difference = comparisonLeft - comparisonRight;
  if (difference != 0)
    goto L80297AA;
  L80297A8:
  ;

  finished = 0x1U;
  difference = finished;
  L80297AA:
  ;

  frameOffset = frameOffset + 0x40U;
  difference = frameOffset;
  value = 0x80U;
  difference = value;
  value = value << 0x11U;
  difference = value;
  packedIndex = packedIndex + value;
  difference = packedIndex;
  entry = entry + 0x1U;
  difference = entry;
  comparisonLeft = entry;
  comparisonRight = 0x2U;
  difference = comparisonLeft - comparisonRight;
  if (comparisonLeft <= comparisonRight)
    goto L8029788;
  L80297B8:
  ;

  comparisonLeft = finished;
  comparisonRight = 0x0U;
  difference = comparisonLeft - comparisonRight;
  if (difference == 0)
    goto L80297CE;
  L80297BC:
  ;

  value = 0x21U;
  difference = value;
  address = 0x3U;
  difference = address;
  sub_08040CD0((u8) value, (u8) address);
  address = (u32) (&gCounter6ED08_03001800);
  address = address + 0xaaU;
  difference = address;
  value = (u32) (*((const u8 *) address));
  value = value + 0x1U;
  difference = value;
  *((u8 *) address) = (u8) value;
  L80297CE:
  ;

  return;
}


