/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Continued07480Frames { u8 prefix[0x100];struct FrameObject frames[3]; };
struct Continued31120Work {u8 prefix[0x57];u8 flag57;u8 gap[0x10D];u8 flag165;};
struct Continued31458Frame {u8 prefix[0x880];struct FrameObject frame;};

extern const u8 gUnknown_083AEE98[];
extern u8 gTransferSelectedSlots[3];
extern void sub_0801B53C(void);
extern void sub_08074B88(u32);
extern void sub_08074DE0(u32);

void sub_08007480(void);
void sub_08031120(void);
void sub_08031458(void);

void sub_08007480(void) {
    struct FrameObject *var_r1;
    struct FrameObject *var_r3;
    u32 var_r2;

    if (4 & gState0TypedWork.widths.word5C) {
        u8 *selected;
        u32 mask;
        struct Continued07480Frames *all;
        var_r2 = 0;
        selected=gTransferSelectedSlots;
        all=(void *)gFrameObjects;
        mask=0xBFFF;
        var_r3=all->frames;
        do {
            if (*(u8 *)(var_r2+(u32)selected) != 0) {
                var_r3->flags &= mask;
            }
            var_r3 += 1;
            var_r2 += 1;
        } while (var_r2 <= 2U);
    } else {
        u8 *selected;
        var_r2 = 0;
        selected=gTransferSelectedSlots;
        {struct Continued07480Frames *all=(void *)gFrameObjects;var_r1 = all->frames;}
        do {
            if (*(u8 *)(var_r2+(u32)selected) != 0) {
                var_r1->flags |= 0x4000;
            }
            var_r1 += 1;
            var_r2 += 1;
        } while (var_r2 <= 2U);
    }
    gState0TypedWork.widths.word5C += 1;
}

void sub_08031120(void){
 struct Continued31120Work *work=(void *)gState0TransferWork.bytes;
 if(work->flag57){if(work->flag165)gUnknown_0300137C=0x60;else gUnknown_0300137C=0x4F;}
 else {sub_0801B53C();sub_08074B88(0x11);gUnknown_0300137C++;}
}

void sub_08031458(void){
 struct Continued31458Frame *frames;
 u8 *work;u32 zero;
 
 frames=(void *)gFrameObjects;zero=0;
 frames->frame.flags=0xC404;frames->frame.tableSelector=zero;
 work=gState0TransferWork.bytes;
 frames->frame.screenX=(u16)gFrameObjects[work[0x87]*4+0x5D].screenX-16;
 frames->frame.screenY=(u16)gFrameObjects[work[0x87]*4+0x5D].screenY+4;
 frames->frame.palette=gUnknown_083AEE98[work[0x166]];frames->frame.priority=0x80;
 frames->frame.frameAndGroup=0x5801+work[0x166];frames->frame.unknown23[0]=zero;
 sub_08074DE0(0x2A);gUnknown_0300137C++;
}
