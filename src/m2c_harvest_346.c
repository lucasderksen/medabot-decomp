/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "serial.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ContinuedAmountWork30 {u8 before[0xC8];u16 amount;u8 middle[7];u8 mode;u8 selected[3];u8 unusedD5;u16 amounts[3];u8 gap[0x10];s16 input;};
struct ContinuedPhaseWork30 {u8 before[0xAA];u8 phase;};

extern u32 sub_0803556C(u32);

void sub_08026FF8(void);

void sub_08026FF8(void) {

  u32 i = 0;
  u8 *work;
  {
    u8 *initial = gState0TransferWork.bytes;
    u8 *selected = initial + 0xD2;
    u32 zero = 0;
    u16 *amounts = (u16 *) (initial + 0xD6);
    do
    {
      *((u8 *) (i + ((u32) selected))) = zero;
      *amounts = zero;
      amounts++;
      i++;
    }
    while (i <= 2);
  }
  work = gState0TransferWork.bytes;
  work[0x60] = sub_08032FB8(work[0x87]);
  i = 0;
  {
    u8 *setup = gSetupBuffer_03000590;
    struct ContinuedAmountWork30 *base = (struct ContinuedAmountWork30 *) work;
    u8 *first = work + 0x60;
    u16 *amount = (u16 *) (work + 0xC8);
    do
    {
      u32 bank = (*first) + i;
      u8 *record = (u8 *) ((bank << 8) + ((u32) setup));
      if (record[0x40] && record[0x59])
      {
        u32 choiceValue = sub_0803556C(bank);
        u8 *choice = base->selected;
        choice = (u8 *)(i - (0U - (u32)choice));
        *choice = choiceValue;
        sub_08034F68((*first) + i, *choice, base->input);
        *choice |= base->mode << 7;
        {
          u32 offset = i << 1;
          u8 *amountRoot = ((u8 *) base) + 0xD6;
          u16 *destination = (u16 *) (offset + ((u32) amountRoot));
          *destination = *amount;
        }
      }
      i++;
    }
    while (i <= 2);
  }
  ((struct ContinuedPhaseWork30 *) (&gState0TransferWork))->phase++;
}
