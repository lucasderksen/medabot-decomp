/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "sound_work.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "record_helpers.h"

struct Counter74500{u8 prefix[0x730];u16 count;};
struct Counter74BCC{u8 prefix[0x730];u16 count;};
struct Counter74CA0{u8 prefix[0x730];u16 count;};
struct Counter74E24{u8 prefix[0x730];u16 count;};
struct Counter74F0C{u8 prefix[0x730];u16 count;};

extern void *gUnknown_03007014;
extern void sub_08074288(s32);
extern void sub_08074C30(s32);
extern void sub_08074EA0(s32,s32);

void sub_08074500(s32 value);
void sub_08074BCC(s32 value,s32 parameter);
void sub_08074CA0(s32 value);
void sub_08074E24(s32 value,s32 parameter);
void sub_08074F0C(s32 value,s32 parameter);

void sub_08074500(s32 value) {

 {struct Counter74500 *work=*(struct Counter74500**)0x03007014;u32 old=work->count;if(old<=0xFFFE)work->count=old+1;}
 sub_08074288(value);
 {struct Counter74500 *work=*(struct Counter74500**)0x03007014;u32 old=work->count;if(old!=0)work->count=old-1;}
}

void sub_08074BCC(s32 value,s32 parameter) {

 {struct Counter74BCC *work=*(struct Counter74BCC**)0x03007014;u32 old=work->count;if(old<=0xFFFE)work->count=old+1;}
 sub_08074A8C(value,parameter);
 {struct Counter74BCC *work=*(struct Counter74BCC**)0x03007014;u32 old=work->count;if(old!=0)work->count=old-1;}
}

void sub_08074CA0(s32 value) {

 {struct Counter74CA0 *work=*(struct Counter74CA0**)0x03007014;u32 old=work->count;if(old<=0xFFFE)work->count=old+1;}
 sub_08074C30(value);
 {struct Counter74CA0 *work=*(struct Counter74CA0**)0x03007014;u32 old=work->count;if(old!=0)work->count=old-1;}
}

void sub_08074E24(s32 value,s32 parameter) {

 {struct Counter74E24 *work=*(struct Counter74E24**)0x03007014;u32 old=work->count;if(old<=0xFFFE)work->count=old+1;}
 sub_08074D50(value,parameter);
 {struct Counter74E24 *work=*(struct Counter74E24**)0x03007014;u32 old=work->count;if(old!=0)work->count=old-1;}
}

void sub_08074F0C(s32 value,s32 parameter) {

 {struct Counter74F0C *work=*(struct Counter74F0C**)0x03007014;u32 old=work->count;if(old<=0xFFFE)work->count=old+1;}
 sub_08074EA0(value,parameter);
 {struct Counter74F0C *work=*(struct Counter74F0C**)0x03007014;u32 old=work->count;if(old!=0)work->count=old-1;}
}
