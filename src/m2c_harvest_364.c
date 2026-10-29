/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "gba.h"
#include "state0_work.h"

extern const u8 gCompressedGraphics_084CE3E8[];
extern const u8 gPaletteBytes_0850F8F8[32];
extern void sub_08036C20(u32,u32,s32,s32,u32);

void sub_0801EAD4(void);

void sub_0801EAD4(void) {

  u8 *cursor;
  u32 word0;
  u32 word1;
  u32 word2;
  u32 word3;
  u32 word4;
  word0 = (u32) gCompressedGraphics_084CE3E8;
  LeDecompress((u8 *) word0, (void *) 0x06010800);
  word0 = (u32) gPaletteBytes_0850F8F8;
  CpuFastSet((void *) word0, (void *) 0x050003C0, 8U);
  word3 = (u32) (&gState0TransferWork);
  cursor=(u8 *)word3;
  cursor+=0xF8;
  word0=(u32)cursor;
  word1=*(u8 *)word0;
  word0 = 2;
  word0 &= word1;
  if (word0 == 0)
  {
    word1 = 0xAC;
    word1 <<= 1;
  }
  else
  {
    word1 = 0xAA;
    word1 <<= 1;
  }
  word0 = word3 + word1;
  word2 = (u32) (*((u16 *) word0));
  word1 += 2;
  word0 = word3 + word1;
  word3 = (u32) (*((u16 *) word0));
  word0 = (u32)&gState0TypedWork;
  word0 += 0x86;
  word1=0;
  *(u16 *)word0=(u16)word1;
  word4 = (u32) (&gState0TransferWork);
  cursor=(u8 *)word4;
  cursor+=0x8B;
  word0=(u32)cursor;
  word1=*(u8 *)word0;
  word2 <<= 0x10;
  word2 = (u32) (((s32) word2) >> 0x10);
  word3 <<= 0x10;
  word3 = (u32) (((s32) word3) >> 0x10);
  sub_08036C20(0xAU, word1, (s32) word2, (s32) word3, 0x1EU);
  word4 += 0xAA;
  word0 = (u32) (*((u8 *)word4));
  word0 += 1;
  *((u8 *)word4) = (u8) word0;
}
