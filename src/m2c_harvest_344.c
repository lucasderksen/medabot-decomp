/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_work.h"

struct ContinuedSetupBank31 {
    u8 before[0xBD];
    u8 flags;
    u8 middle[0x1A];
    u16 amount;
    u8 padDA[5];
    u8 kind;
    u8 tail[0x20];
};
struct ContinuedPhase31 {u8 before[0xAA];u8 phase;};

extern void sub_08035740(u8 *,s32,u32);

void sub_08022748(void);

void sub_08022748(void) {

  struct ContinuedSetupBank31 *setup = (struct ContinuedSetupBank31 *) gSetupBuffer_03000590;
  u8 *work = gState0TransferWork.bytes;
  u8 *bank = work + 0x87;
  u32 old = setup[*bank].flags;
  u32 mask = 8;
  u32 zero = 0;
  u32 offset;
  struct ContinuedSetupBank31 *record;
  u8 kind;
  mask |= old; setup[*bank].flags = mask;
  offset = (*bank) << 8;
  record = (struct ContinuedSetupBank31 *) (offset + ((u32) setup));
  kind = *((u8 *) ((((work[0xA7] * 24) + offset) + ((u32) setup)) + 0x49));
  record->kind = kind;
  setup[*bank].amount = zero;
  sub_08035740((u8 *)((u32)setup - (0U - (*bank << 8)) + 0xD8), *((s16 *) (work + 0xEC)), 0xFF);
  ((struct ContinuedPhase31 *) work)->phase++;
}
