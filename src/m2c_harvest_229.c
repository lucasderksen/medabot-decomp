/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ContinuedPhaseWork30 {u8 before[0xAA];u8 phase;};
struct ContinuedFlagPhase30 {u8 before[0xAA];u8 phase,status;u8 middle[0x4A];u8 flags;};
struct ContinuedObservedRecord30 {u8 before[0x2A];u8 active,kind;};
struct ContinuedLookupWork30 {u8 before[0x52];u8 kind;u8 middle[0x37];u8 index;};
struct ContinueBankWork {u8 pad[0x87];u8 bank;};

extern struct ContinueBankWork gUnknown_03001800;
extern void sub_0801AEB4(void);
extern void sub_08036E64(u32,u32,s32,s32);

void sub_0801F9EC(void);
void sub_08020078(void);
void sub_08021774(void);
void sub_08030CFC(void);

void sub_0801F9EC(void) {

    u8 *work=gState0TransferWork.bytes;
    u32 target=work[0x88];
    u8 *setup=gSetupBuffer_03000590;
    u32 offset=work[0xA7]*24;
    u32 kind;
    offset+=work[0x87]<<8;
    kind=*(u8 *)(offset+(u32)setup+0x49);
    sub_08036E64(target,kind,*(s16 *)(work+0xE8),*(s16 *)(work+0xEC));
    ((struct ContinuedPhaseWork30 *)work)->phase++;
}

void sub_08020078(void) {

    struct ContinuedFlagPhase30 *work=(struct ContinuedFlagPhase30 *)&gState0TransferWork;
    u32 flags=work->flags&1;
    u8 *phase;
    u32 value;
    if(flags){phase=&work->phase;value=2;}
    else {work->status=flags;phase=&work->phase;value=work->phase+1;}
    *phase=value;
}

void sub_08021774(void) {

    struct ContinuedLookupWork30 *work=(struct ContinuedLookupWork30 *)&gState0TransferWork;
    struct ContinuedObservedRecord30 *record=(struct ContinuedObservedRecord30 *)(work->index*8+(u32)work);
    if(record->active && record->kind==work->kind){
        gFrameObjects[0x21].unknown23[4]=0;
        ((struct ContinuedPhaseWork30 *)work)->phase++;
    }else{
        struct ContinuedPhaseWork30 *phase;
        sub_08074DE0(0x3E);
        phase=(struct ContinuedPhaseWork30 *)&gState0TransferWork;
        phase->phase=0x25;
    }
}

void sub_08030CFC(void) {
u8 *setup=gSetupBuffer_03000590;if(*(u8 *)(((u32)gUnknown_03001800.bank<<8)+(u32)setup+0xC1)==0x50)gUnknown_0300137C++;else{sub_0801AEB4();gUnknown_0300137C=0x14;}}
