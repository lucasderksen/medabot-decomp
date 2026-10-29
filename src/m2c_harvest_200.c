/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 sub_0807CD2C(s32,s32);

void sub_0801A640(void);

void sub_0801A640(void) {
 u8 *work=gState0TransferWork.bytes;
 s32 result;
 s32 selection;
 selection=work[0x45]-1;
 work[0x87]=selection;
 result=sub_0807CD2C(work[0x45]-1,3);
 work[0x89]=result;
 result=result^1;
 work[0x8A]=result;
}
