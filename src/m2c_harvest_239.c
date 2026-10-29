/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "display_helpers.h"
#include "frame.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "tile_text.h"


void sub_08017C50(s32 mode);

void sub_08017C50(s32 mode) {

    if(mode==0){
        if(gState0TypedWork.bytes[0x3C]==0){
            sub_08042698(2,2,26,17,*(volatile u16 *)0x04000008,0x8304);
        }else{
            sub_08042698(2,2,2,17,*(volatile u16 *)0x04000008,0x8300);
        }
        return;
    }
    {
    u32 selected=gState0TypedWork.bytes[0x3C];
    if(selected==0){
        sub_0803EF8C(2,2,26,17,*(volatile u16 *)0x04000008,selected);
    }else{
        sub_0803EF8C(2,2,2,17,*(volatile u16 *)0x04000008,0);
    }
    }
}
