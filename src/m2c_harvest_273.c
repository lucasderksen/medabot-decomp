/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "main_menu_data.h"
#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "input.h"
#include "main.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Callbacks629DC{void (*fn[7])(void);};
struct LocalCallbackPair {MainCallback callbacks[2];};
struct Callbacks65D10{void (*fn[8])(void);};
struct Counter708D8 {u8 pad0[0xC];u8 scrollC,scrollD;};
struct AudioQueue24 {u8 bytes[48];u8 cursor;};
struct AudioOwner24 {u8 before8[8];struct AudioQueue24 *queue;u8 before6B[0x5F];u8 behind;};
struct Link74978 { struct Link74978 *next, *prev; };

extern const MainCallback gUnknown_08485730[];
extern const MainCallback gUnknown_08485964[];
extern const MainCallback gUnknown_08485A08[];
extern const struct Callbacks629DC gUnknown_080AFB98;
extern const struct Callbacks65D10 gUnknown_080AFC88;
extern const struct LocalCallbackPair gUnknown_080AFC58;
extern s32 (*const gUnknown_0848571C[5])(void);
extern s32 gUnknown_03000000;
extern struct Counter708D8 gCounter708D8;
extern u8 gUnknown_03000004;
extern u8 gUnknown_03006F90;
extern void (*const gUnknown_08485B68[8])(void);
extern void *gUnknown_03007014;
extern void sub_08060248(void);
extern void sub_0806B4A4(void);
extern void sub_0806D41C(void);
extern void sub_0806D4A4(void);
extern void sub_0806DE0C(void);
extern void sub_0806E9E0(void);
extern void sub_0806EA54(void);
extern void sub_08070804(void);
extern void sub_08070824(void);

void sub_0805FC58(void);
void sub_08060280(void);
void sub_0806045C(void);
void sub_0806048C(void);
void sub_080629DC(void);
void sub_08064B90(void);
void sub_08065D10(void);
s32 sub_080688E0(void);
void sub_08068DD0(void);
void sub_0806D588(void);
void sub_0806EA98(void);
void sub_080708D8(void);
u32 sub_08074224(const void *record);
void sub_08074978(struct Link74978 *node);

void sub_0805FC58(void) {
gUnknown_08483738[gUnknown_0300137C]();if(gFrameCounter&1)gBgScroll3.y += 1;}

void sub_08060280(void) {
gUnknown_08483758[gUnknown_0300137C]();if(gFrameCounter&1)gBgScroll3.y -= 1;}

void sub_0806045C(void) {
u8 *ctx=(u8 *)gMainContextPointer_03006F74;u8 old;u32 packed;
 old=*ctx;packed=(u32)old<<24;
 if(packed!=0){volatile u16 *brightness=(volatile u16 *)0x04000054;*ctx=old+0xFF;*brightness=packed>>25;return;}
 gUnknown_0300137C+=1;
 }

void sub_0806048C(void) {

 sub_08060248();
 if(1U & *(u8 *)&gNewKeys){sub_08074DE0(4U);*(u8 *)gMainContextPointer_03006F74=0;gUnknown_0300137C+=1;}
}

void sub_080629DC(void) {
struct Callbacks629DC callbacks=gUnknown_080AFB98;callbacks.fn[gUnknown_0300137C]();}

void sub_08064B90(void) {

 struct LocalCallbackPair local=gUnknown_080AFC58;
 local.callbacks[gUnknown_0300137C]();
}

void sub_08065D10(void) {
struct Callbacks65D10 callbacks=gUnknown_080AFC88;callbacks.fn[gUnknown_0300137C]();}

s32 sub_080688E0(void) {
if(gUnknown_0848571C[gUnknown_03000004]()!=0){gUnknown_03000000=0;return 1;}gUnknown_03000000+=1;return 0;}

void sub_08068DD0(void) {

 if(gUnknown_03006F90==0)sub_0806B4A4();
 gUnknown_08485730[gUnknown_0300137C]();
}

void sub_0806D588(void) {

 sub_0806D4A4();
 gUnknown_08485964[gUnknown_0300137C]();
 sub_0806DE0C();
 sub_0806D41C();
}

void sub_0806EA98(void) {

 sub_0806E9E0();
 gUnknown_08485A08[gUnknown_0300137C]();
 sub_0806EA54();
}

void sub_080708D8(void) {

 if(gCounter708D8.scrollC!=0)sub_08070804();
 if(gCounter708D8.scrollD!=0)sub_08070824();
 gUnknown_08485B68[gUnknown_0300137C]();
}

u32 sub_08074224(const void *record) {

 const struct AudioOwner24 *owner=record;
 const struct AudioQueue24 *queue=owner->queue;
 s32 offset;
 if(!queue)return 255;
 offset=(s32)queue->cursor-owner->behind;
 if(offset<0)offset+=48;
 return *(const u8 *)((u32)queue+(u32)offset);
}

void sub_08074978(struct Link74978 *node) {

 struct Link74978 *head,*next;
 struct Link74978 **slot;
 if(node->prev==0 && node->next==0){
  slot=(struct Link74978 **)((u8 *)gUnknown_03007014+0x5E4);
  head=*slot;
  if(head==0){node->prev=node;node->next=node;}
  else{next=head->next;node->next=next;node->prev=*slot;next->prev=node;node->prev->next=node;}
  *slot=node;
 }
}
