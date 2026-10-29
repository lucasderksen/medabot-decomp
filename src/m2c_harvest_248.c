/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "main_callbacks.h"
#include "state0_work.h"

extern s8 gUnknown_0300056F;
extern void (*const gUnknown_083AFAEC[])(void);

void sub_0803B8C8(void);

void sub_0803B8C8(void) {

 u32 counter=0;
 s8 *selection=&gUnknown_0300056F;
 void (*const *callbacks)(void)=gUnknown_083AFAEC;
 struct FrameObject *frames=gFrameObjects;
 do {counter++;*selection=counter;callbacks[frames[counter].unknown23[6]]();} while(counter<=38u);
}
