/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ContinuedActionRecordD8 { u8 pad00[0x4D]; u8 stat4D; u8 stat4E; u8 pad4F; u8 stat50; u8 stat51; u8 pad52[0xAE]; };

extern struct ContinuedActionRecordD8 gUnknown_030005D8[];
extern void sub_080351E8(u32);
extern void sub_08035740(u8 *, s32, u32);

void sub_0802BC60(void);

void sub_0802BC60(void) {
 u32 slot;
 u8 *work;
 u8 *bank;
 struct ContinuedActionRecordD8 *records;
 s16 *amount;
 slot = 0;
 work = gState0TransferWork.bytes;
 bank = work + 0x60;
 records = gUnknown_030005D8;
 amount = (s16 *)(work + 0xEC);
 do {
  u8 *selected = work + 0xD2;
  if (*(u8 *)(slot + (u32)selected) != 0) {
   switch (work[0x51]) {
   case 0: sub_08035740(&records[*bank + slot].stat4D, *amount, 0xFF); break;
   case 1: sub_08035740(&records[*bank + slot].stat4E, *amount, 0xFF); break;
   case 2: sub_08035740(&records[*bank + slot].stat50, *amount, 0xFF); break;
   case 3: sub_08035740(&records[*bank + slot].stat51, *amount, 0xFF); break;
   }
   sub_08035194(*bank + slot);
   sub_080351E8(*bank + slot);
  }
  slot++;
 } while (slot <= 2u);
 gState0TransferWork.bytes[0xAA]++;
}
