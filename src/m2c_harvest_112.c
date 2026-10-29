/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "record_helpers.h"
#include "tile_text.h"


void sub_08075190(s32 *x, s32 *y);

void sub_08075190(s32 *x, s32 *y) {
 u16 after;
 u16 before;
 void **saved=(void**)0x03007014;
 u8 *root;
 before=*(u16*)((u8*)*saved+0x730);
 if((u32)before<=0xFFFE) {
  *(u16*)((u8*)*saved+0x730)=before+1;
 }
 root=*saved;
 *x=root[0x72D];
 *y=root[0x72E];
 after=*(u16*)((u8*)*saved+0x730);
 if(after!=0) {
  *(u16*)((u8*)*saved+0x730)=after-1;
 }
}
