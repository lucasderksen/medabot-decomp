/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "record_helpers.h"
#include "state0_work.h"

struct SoundRoot75028 { u8 pad[0x730]; u16 references; };
struct SoundRoot751E4 { u8 pad[0x72C]; u8 flags,first,second,pad72F; u16 references; };

extern struct SoundRoot75028 *gSoundRoot75028;
extern struct SoundRoot751E4 *gSoundRoot751E4;
extern void sub_08074FFC(void *, s32, s32);

void sub_08075028(void *work, s32 value, s32 duration);
void sub_080751E4(u32 first,u32 second);

void sub_08075028(void *work, s32 value, s32 duration) {

 u16 count;
 u32 after;
 count = (*(struct SoundRoot75028**)0x03007014)->references;
 if ((u32)count <= 0xFFFEU) {
  (*(struct SoundRoot75028**)0x03007014)->references = count + 1;
 }
 sub_08074FFC(work,value,duration);
 after = (*(struct SoundRoot75028**)0x03007014)->references;
 if (after != 0) {
  (*(struct SoundRoot75028**)0x03007014)->references = after - 1;
 }
}

void sub_080751E4(u32 first,u32 second) {

 u16 count;
 u32 after;
 count=(*(struct SoundRoot751E4**)0x03007014)->references;
 if((u32)count<=0xFFFEU)(*(struct SoundRoot751E4**)0x03007014)->references=count+1;
 (*(struct SoundRoot751E4**)0x03007014)->first=first;
 (*(struct SoundRoot751E4**)0x03007014)->second=second;
 (*(struct SoundRoot751E4**)0x03007014)->flags=1|(*(struct SoundRoot751E4**)0x03007014)->flags;
 after=(*(struct SoundRoot751E4**)0x03007014)->references;
 if(after!=0)(*(struct SoundRoot751E4**)0x03007014)->references=after-1;
}
