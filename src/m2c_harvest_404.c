/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_work.h"

extern struct Counter6ED08 gCounter6ED08_03001800;

void sub_0803B900(void);

void sub_0803B900(void) {
    /* Use integer cursors to retain the full byte-index address domain. */
    u32 value, scratch;
    u32 activeAddress, indexAddress, frameRoot, workRoot, offset;

    frameRoot=(u32)gFrameObjects;
    workRoot=(u32)&gState0TypedWork;
    offset=0x12F;
    indexAddress=workRoot+offset;
    scratch=*(u8 *)indexAddress;
    value=scratch<<6;
    value+=frameRoot;
    activeAddress=value+0x2B;
    value=*(u8 *)activeAddress;
    if(value==0)goto done;

    if(scratch!=1)goto other;

    value=(u32)&gCounter6ED08_03001800;
    scratch=0x15F;
    value+=scratch;
    value=*(u8 *)value;
    if(value==0)goto done;

    value=0;
    *(u8 *)activeAddress=value;
    value=*(u8 *)indexAddress;
    value<<=6;
    scratch=value+frameRoot;
    value=scratch+0x2D;
    value=*(u8 *)value;
    if(value!=0)goto twice;
    goto once;

other:value=(u32)&gCounter6ED08_03001800;
    scratch=0x160;
    value+=scratch;
    value=*(u8 *)value;
    if(value==0)goto done;

    value=0;
    *(u8 *)activeAddress=value;
    value=*(u8 *)indexAddress;
    value<<=6;
    scratch=value+frameRoot;
    value=scratch+0x2D;
    value=*(u8 *)value;
    if(value==0)goto once;

twice:scratch+=0x29;
    value=*(u8 *)scratch;
    value++;
    *(u8 *)scratch=value;
    value=*(u8 *)indexAddress;
    value<<=6;
    value+=frameRoot;
    value+=0x29;
    scratch=*(u8 *)value;
    scratch++;
    *(u8 *)value=scratch;
    goto done;

once:scratch+=0x29;
    value=*(u8 *)scratch;
    value++;
    *(u8 *)scratch=value;

done:
    return;
}
