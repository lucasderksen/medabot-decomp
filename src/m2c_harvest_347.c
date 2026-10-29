/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinueChoiceWork {
    u8 pad[0x19A];
    u8 choices[6];
    u8 amount;
    u8 gap;
    u8 selected;
};

extern void sub_08042698(u32,u32,u32,u32,u32,u32);

void sub_0803ED6C(void);

void sub_0803ED6C(void)
{
  if (gState0TypedWork.widths.word86 & 4)
  {
    struct ContinueChoiceWork *work = (struct ContinueChoiceWork *)&gState0TransferWork;
    /* Preserve the original unchecked byte index through word addressing. */
    sub_08042698(7, 2, 4, (((u32) work->selected) * 2) + 2, *((volatile u16 *) 0x0400000A), ((u32)*(u8 *)(0U - (0U - (u32)work->choices) + work->selected) * 0xE0000u + 0x33800000u) >> 16);
    return;
  }
  {
    struct ContinueChoiceWork *work = (struct ContinueChoiceWork *)&gState0TransferWork;
    sub_08042698(7, 2, 4, (((u32) work->selected) * 2) + 2, *((volatile u16 *) 0x0400000A), ((u32)*(u8 *)(0U - (0U - (u32)work->choices) + work->selected) * 0xE0000u + 0x43800000u) >> 16);
  }
}
