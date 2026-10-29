/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "frame_objects.h"
#include "object_helpers.h"
#include "state0_work.h"

extern const u8 *const gState0NextCommands_083B6100[];

void sub_0803D0BC(void);

void sub_0803D0BC(void) {

  u8 *cursor;
  u32 word0;
  u32 word1;
  u32 word2;
  u32 word3;
  u32 word4;
  u32 word6;
  word2 = (u32) gState0NextCommands_083B6100;
  word6 = (u32) gFrameObjects;
  word0 = (u32) (&gState0TypedWork);
  word1 = (u32) (*((u8 *) (word0 + 0x12FU)));
  word0 = word1 << 6;
  word0 += word6;
  word0 += 0x2D;
  word0 = (u32) (*((u8 *) word0));
  word0 *= 4;
  word0 += word2;
  word0 = (u32)*((const u8 *const *)word0);
  sub_08040BD8((const u8 *) word0, (u8) word1);
  word4 = (u32) (*((u8 *) (((u32) (&gState0TypedWork)) + 0x12FU)));
  word0 = word4 << 6;
  word1 = word0 + word6;
  cursor=(u8 *)word1;
  cursor+=0x23;
  word0=(u32)cursor;
  word0=*(u8 *)word0;
  if (word0 == 0)
  {
    word2 = word1;
    word2 += 0x26;
    word3 = (u32) (*((u8 *) (word1 + 0x8U)));
    word0 = (u32) (*((u8 *) word2));
    if (word3 <= word0)
    {
      word0 = word4;
      word1 = 1;
      sub_08040D0C((u8) word0, 1U);
      return;
    }
    word0 = word3 - word0;
    *((u8 *) (word1 + 0x8U)) = (u8) word0;
    word0 = (u32) (*((u8 *) (((u32) (&gState0TypedWork)) + 0x12FU)));
    word0 <<= 6;
    word0 += (u32) gFrameObjects;
    word2 = word0;
    word2 += 0x26;
    word1 = (u32) (*((u8 *) (word0 + 0x9U)));
    word2 = (u32) (*((u8 *) word2));
    word1 -= word2;
    goto block_7;
  }
  word2 = (u32) (*((u8 *) (word1 + 0x8U)));
  if (word2 == 0x40)
  {
    word1 += 0x29;
    word0 = 0;
    *((u8 *) word1) = 0;
    return;
  }
  word0 = word1;
  word0 += 0x26;
  word0 = (u32) (*((u8 *) word0));
  *((u8 *)(word1+8U))=(u8)(word2+word0);
  word0 = (u32) (*((u8 *) (((u32) (&gState0TypedWork)) + 0x12FU)));
  word0 <<= 6;
  word2 = (u32)gFrameObjects;
  word0 = word2 + word0;
  word1 = word0;
  word1 += 0x26;
  word1 = (u32) (*((u8 *) word1));
  word2 = (u32) (*((u8 *) (word0 + 0x9U)));
  word1 += word2;
  block_7:
  *((u8 *) (word0 + 0x9U)) = (u8) word1;

}
