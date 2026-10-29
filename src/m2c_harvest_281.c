/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "tile_text.h"

extern void *memset(void*,s32,unsigned long);
extern void sub_080669EC(s32*,const s32*);
extern void sub_08066A48(s32*,const s32*,const s32*);

void sub_08066AB4(s32 value);
void sub_08066AFC(s32 x,s32 y,s32 z);

void sub_08066AB4(s32 value) {

 struct {s32 input[16],output[16];} frame;
 s32 *existing;
 u32 outputRoot;
 memset(frame.input,0,64);
 frame.input[0]=value;frame.input[5]=value;frame.input[10]=value;frame.input[15]=0x100;
 outputRoot=(u32)frame.output;
 existing=(s32*)((u8*)gMainContextPointer_03006F74+0x1F0);
 sub_08066A48((s32*)outputRoot,frame.input,existing);
 sub_080669EC((s32*)((u8*)gMainContextPointer_03006F74+0x1F0),(s32*)outputRoot);
}

void sub_08066AFC(s32 x,s32 y,s32 z) {

 struct {s32 input[16],output[16];} frame;
 s32 *existing;
 u32 outputRoot;
 memset(frame.input,0,64);
 frame.input[0]=0x100;frame.input[5]=0x100;frame.input[10]=0x100;frame.input[12]=x;frame.input[13]=y;frame.input[14]=z;frame.input[15]=0x100;
 outputRoot=(u32)frame.output;
 existing=(s32*)((u8*)gMainContextPointer_03006F74+0x1F0);
 sub_08066A48((s32*)outputRoot,existing,frame.input);
 sub_080669EC((s32*)((u8*)gMainContextPointer_03006F74+0x1F0),(s32*)outputRoot);
}
