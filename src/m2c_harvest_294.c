/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct NativeScaleCommandFrame53 {
    u16 flags;
    u8 pad02[6];
    u8 scaleX, scaleY;
    u8 pad0A[24];
    u8 stopped;
    u8 pad23[29];
};


void sub_08016554(void);

void sub_08016554(void) {

    u32 frameRoot=(u32)gFrameObjects;
    u32 workRoot=(u32)gState0TransferWork.bytes;
    u8 *selected=(void *)(workRoot+0x81);
    struct NativeScaleCommandFrame53 *flagsFrame,*scaleFrame,*xFrame;
    u8 *command;
    u32 scale;
    flagsFrame=(void *)(((u32)*selected<<6)+frameRoot);
    flagsFrame->flags|=0x20;
    command=(void *)(((u32)*selected<<6)+frameRoot+0x22);
    (*command)++;
    scaleFrame=(void *)(((u32)*selected<<6)+frameRoot);
    if(scaleFrame->stopped&4){scale=0x60;scaleFrame->scaleY=scale;}
    else{scale=0x40;scaleFrame->scaleY=scale;}
    xFrame=(void *)(((u32)*selected<<6)+frameRoot);
    xFrame->scaleX=scale;
}
