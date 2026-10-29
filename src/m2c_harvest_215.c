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
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ContinuedPhaseWork27 {u8 before[0xAA];u8 phase;};

extern void sub_0803836C(void);

void sub_0802C790(void);

void sub_0802C790(void) {
 s32 found=0;
 u8 *work;
 u8 *setup;
 u8 *flags;
 u32 i;
 do {
 sub_0803836C();
 work=gState0TransferWork.bytes;
 work[0x60]=sub_08032FC4(work[0x87]);
 } while(0);
 i=0;setup=gSetupBuffer_03000590;flags=work+0xD2;
 do {
  u32 slot=work[0x60]+i;
  u32 address=(slot<<8)+(u32)setup;
  if(*(u8 *)(address+0x40) && *(u8 *)(address+0x59) && sub_080331F8(slot)) {
   *(u8 *)(i+(u32)flags)=1;found=1;
  }
  i++;
 } while(i<=2);
 if(!found) ((struct ContinuedPhaseWork27 *)&gState0TransferWork)->phase++;
 else ((struct ContinuedPhaseWork27 *)&gState0TransferWork)->phase+=3;
}
