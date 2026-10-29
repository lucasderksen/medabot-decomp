/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "serial.h"

struct SoundWork73EC8 {u8 pad00[0x10];s32 phase;u8 pad14[4];s32 word18; s32 word1C;s32 word20;u8 pad24[4];s32 word28;s32 word2C;u8 byte30;u8 byte31;};

extern const u8 gUnknown_083AF630[];
extern s32 sub_0807CEC8(s32,s32);
extern u32 sub_08073C18(void *,s32);
extern void sub_08072734(s32);
extern void sub_08073D70(void *,s32);
extern void sub_08073DB8(void *,s32,s32,s32,s32,s32,s32,s32);
extern void sub_08073DF4(void *);

s32 sub_08036DE8(s32 index,s32 direction);
void sub_08073EC8(struct SoundWork73EC8 *work);

s32 sub_08036DE8(s32 index,s32 direction) {
 struct FrameObject *frames=gFrameObjects;
 struct FrameObject *frame=&frames[index];
 if (!(frame->flags & 0x8000) || frame->unknown23[0]==16) return 1;
 if (direction==0) frame->screenX=(u16)frame->screenX+gUnknown_083AF630[frame->unknown23[0]];
 else frame->screenX=(u16)frame->screenX-gUnknown_083AF630[frame->unknown23[0]];
 gFrameObjects[index].unknown23[0]++;
 return 0;
}

void sub_08073EC8(struct SoundWork73EC8 *work) {
 s32 denominator;
 sub_08073DF4(work);
 sub_08073DB8(work,work->word1C,0x20,0,work->word28,work->word2C,work->byte30,work->byte31);
 denominator=sub_08073C18(work,work->word20);
 work->phase=(0x10000-sub_0807CEC8(0x01000000,denominator))|0x800000;
 sub_08073D70(work,0);
 sub_08072734(work->word18);
}
