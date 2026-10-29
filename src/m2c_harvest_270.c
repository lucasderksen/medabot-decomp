/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"

struct SoundRecord_08073C84 {u8 before3A[0x3A];u8 channel;};

extern const u16 gUnknown_083ABC2E[];
extern void sub_08073B2C(s32);
extern volatile u32 *const gUnknown_08486E5C[];

void sub_08073C84(void *arg0);

void sub_08073C84(void *arg0) {

 u32 root=(u32)gUnknown_08486E5C;
 struct SoundRecord_08073C84 *record=arg0;
 u32 channel=record->channel;
 if(**(volatile u32 *const *)(root+((channel-1)<<2))&0x800000) {
  sub_08073B2C(channel);
  **(volatile u32 *const *)(root+(((u32)record->channel-1)<<2))=0;
  *(volatile u16 *)0x04000082&=~gUnknown_083ABC2E[record->channel-1];
 }
}
