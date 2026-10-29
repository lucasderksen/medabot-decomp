/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "main.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"

struct WaitWork6D6AC {u16 main,sub,previous,limit;s32 counter;};

extern struct WaitWork6D6AC gWaitWork6D6AC;

void sub_0806D6AC(void);

void sub_0806D6AC(void) {

 struct WaitWork6D6AC *work=&gWaitWork6D6AC;
 s32 limit=work->limit;
 s32 count=(s32)((u32)work->counter+1);
 work->counter=count;
 if(limit<count) {
  work->counter=0;
  gMainState=work->main;
  gMainSubstate=work->sub;
  gUnknown_0300137C=work->previous;
 }
}
