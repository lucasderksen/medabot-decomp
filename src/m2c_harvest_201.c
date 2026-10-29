/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "record_helpers.h"

struct EnvelopeWorkInitQ14 {u8 pad0[0x5B];u8 attack;u8 decay;u8 pad5D[2];u8 countdown;s8 step;u8 state;};

extern s32 sub_080724B0(void *);
extern void sub_0807250C(void *);

void sub_0807254C(struct EnvelopeWorkInitQ14 *work);

void sub_0807254C(struct EnvelopeWorkInitQ14 *work) {
 u32 count;
 if(sub_080724B0(work)==0) {
  count=work->attack>>4;
  work->countdown=count;
  if(count==0) {sub_0807250C(work);return;}
  work->step=(0xF & work->attack);
  work->state=2;
 }
}
