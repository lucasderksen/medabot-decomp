/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"

struct SceneSetupKind1E5DC {u8 prefix[0x49];u8 kind;};

extern const u8 gUnknown_084CCEF0[];
extern const u8 gUnknown_084CD1B0[];
extern const u8 gUnknown_084CD4A4[];
extern const u8 gUnknown_084CD73C[];
extern const u8 gUnknown_084CDD68[];
extern const u8 gUnknown_0850F7F8[32];
extern const u8 gUnknown_0850F818[32];
extern const u8 gUnknown_0850F838[32];
extern const u8 gUnknown_0850F858[32];
extern const u8 gUnknown_0850F8B8[32];
extern void sub_08036B84(u32, u32);

void sub_0801E5DC(void);

void sub_0801E5DC(void) {

  u32 workValue;
  u32 partOffset;
  u32 bankOffset;
  struct SceneSetupKind1E5DC *setup = (struct SceneSetupKind1E5DC *) gSetupBuffer_03000590;
  u8 *work = gState0TransferWork.bytes;
  partOffset = work[0xA7] * 0x18;
  bankOffset = work[0x87] << 8;
  if (0x30 == ((struct SceneSetupKind1E5DC *) ((partOffset + bankOffset) + ((u32) setup)))->kind)
  {
    sub_08036B84(gState0TransferWork.bytes[0x88], gState0TransferWork.bytes[0x8B]);
    LeDecompress(gUnknown_084CDD68, (void *) 0x06010000);
    CpuFastSet(gUnknown_0850F8B8, (void *) 0x050003C0, 8U);
    gFrameObjects[10].frameAndGroup = 0x2100;
    sub_08074DE0(0x54U);
  }
  else
  {
    switch (gState0TransferWork.bytes[0x8B])
    {
      case 0:
        LeDecompress(gUnknown_084CCEF0, (void *) 0x06010000);
        CpuFastSet(gUnknown_0850F7F8, (void *) 0x050003C0, 8U);
        gFrameObjects[10].frameAndGroup = 0x1B00;
        break;

      case 1:
        LeDecompress(gUnknown_084CD1B0, (void *) 0x06010000);
        CpuFastSet(gUnknown_0850F818, (void *) 0x050003C0, 8U);
        gFrameObjects[10].frameAndGroup = 0x1C00;
        break;

      case 2:
        LeDecompress(gUnknown_084CD4A4, (void *) 0x06010000);
        CpuFastSet(gUnknown_0850F838, (void *) 0x050003C0, 8U);
        gFrameObjects[10].frameAndGroup = 0x1D00;
        break;

      case 3:
        LeDecompress(gUnknown_084CD73C, (void *) 0x06010000);
        CpuFastSet(gUnknown_0850F858, (void *) 0x050003C0, 8U);
        gFrameObjects[10].frameAndGroup = 0x1E00;
        break;

    }

    sub_08074DE0(6U);
  }
  gFrameObjects[10].flags = 0xC404;
  gFrameObjects[10].tableSelector = 0;
  gFrameObjects[10].palette = 0xE;
  gFrameObjects[10].priority = 0x80;
  gFrameObjects[10].unknown23[0] = 0;
  workValue = gState0TransferWork.bytes[0xF8];
  if (!(2 & workValue))
  {
    if (gState0TransferWork.bytes[0x8B] == 2)
    {
      gFrameObjects[10].screenX = (*((u16 *) (gState0TransferWork.bytes + 0x158))) - 0x10;
    }
    else
    {
      gFrameObjects[10].screenX = (s16) (*((u16 *) (gState0TransferWork.bytes + 0x158)));
    }
    workValue = 0x15A;
  }
  else
  {
    if (gState0TransferWork.bytes[0x8B] == 1)
    {
      gFrameObjects[10].screenX = (*((u16 *) (gState0TransferWork.bytes + 0x154))) + 0x10;
    }
    else
    {
      gFrameObjects[10].screenX = (s16) (*((u16 *) (gState0TransferWork.bytes + 0x154)));
    }
    workValue = 0x156;
  }
  gFrameObjects[10].screenY = *((u16 *) ((u32)gState0TransferWork.bytes - (0U-workValue)));
  gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
}
