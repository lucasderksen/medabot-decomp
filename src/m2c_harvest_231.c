/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_blend_work.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinueMotionFrame {u8 pad0[4];s16 y;u8 pad1[0x1E];u8 increment,fraction;u8 pad2[0xA];u16 accumulator;u8 tail[0xE];};
struct ContinueAssetWork {u8 pad[0x102];s16 index;};

extern const u8 gUnknown_083AD524[];
extern struct ContinueAssetWork gUnknown_03001800;extern const u8 *const gUnknown_083AFA0C[];
extern struct ContinueMotionFrame gUnknown_03002C30[128];extern const u8 gUnknown_083AF390[];
extern void sub_08017994(u32, u32, u32);
extern void sub_0803D450(void);extern void sub_0803D4AC(void);

void sub_08017A14(u32 arg0, s32 arg1);
u32 sub_0803526C(u32 index,s32 low,s32 high);
void sub_0803A0E0(void);

void sub_08017A14(u32 arg0, s32 arg1) {

    u32 var_r4,bankOffset;
    u32 var_r8;
    u8 *var_r6;
    u32 var_r1,y;
    u32 var_r5;
    u8 *setup;
    const u8 *coordinates;

    var_r8 = 0;
    setup=gSetupBuffer_03000590;
    coordinates=gUnknown_083AD524;
    var_r5 = (arg0 * 2)+(u32)coordinates;
    bankOffset=arg0<<8;
    setup+=0x40;
    var_r6 = (u8 *)(bankOffset+(u32)setup);
    var_r4 = arg0;
    do {
        if (*var_r6 != 0) {
            var_r1 = *(const u8 *)var_r5;
            y=*(const u8 *)(var_r5 + 1);
            if (var_r4 <= 2U) {
                if (arg1 != 0) {
                    var_r1 -= 0x68;
                }
            } else if (arg1 != 0) {
                var_r1 += 0x68;
            }
            sub_08017994(var_r4, (u32) var_r1, y);
        }
        var_r5 += 2;
        var_r6 += 0x100;
        var_r4 += 1;
        var_r8 += 1;
    } while (var_r8 <= 2U);
}

u32 sub_0803526C(u32 index,s32 low,s32 high) {
s16 lower=low,upper=high;struct ContinueMotionFrame *frame;u8 fraction;u32 next,sum;{u32 selected=index;struct ContinueMotionFrame *frames=gUnknown_03002C30;frame=&frames[selected];}frame->fraction+=gUnknown_083AF390[frame->accumulator];fraction=frame->fraction;frame->fraction=fraction&3;next=((fraction>>2)+(u16)frame->y)&0xFF;frame->y=next;if((s32)next>=lower&&(s32)next<=upper){frame->y=lower;return 1;}{struct ContinueMotionFrame *tail=&gUnknown_03002C30[index];u32 add=tail->increment;sum=tail->accumulator+add;tail->accumulator=sum;sum=(u16)sum;if(sum>0xFF)tail->accumulator=0xFF;}return 0;}

void sub_0803A0E0(void) {
const u8 *const *table;struct ContinueAssetWork *work;sub_0803D450();table=gUnknown_083AFA0C;work=&gUnknown_03001800;LeDecompress(table[work->index*2],(void *)0x06010000);CpuFastSet(*(const u8 *const *)((((u32)((s32)work->index*2)+1)<<2)+(u32)table),(void *)0x050003C0,8);sub_0803D4AC();}
