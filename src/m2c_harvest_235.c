/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "state0_work.h"

struct ContinueDivideWork {u8 pad[0xE8];u16 input;u16 gap;s16 value;};

extern struct ContinueDivideWork gUnknown_03001800;extern s32 sub_0807CD2C(s32,s32);

void sub_08037280(u32 bank,u32 part);

void sub_08037280(u32 bank,u32 part) {
struct ContinueDivideWork *root=&gUnknown_03001800;s32 quarter=(s16)root->input>>2;u8 *setup;u8 *record;s32 result;root->value=quarter;setup=gSetupBuffer_03000590;record=(u8 *)(part*0x18+(bank<<8)+(u32)setup);quarter+=record[0x4E];root->value=quarter;result=sub_0807CD2C(root->value,record[0x54]);root->value=result;if((s16)result==0)root->value=1;}
