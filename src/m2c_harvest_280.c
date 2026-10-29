/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_blend_work.h"
#include "continued_scene_records.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "record_helpers.h"
#include "state0_display.h"
#include "state0_work.h"

struct Dma68864 {u32 source,destination,control;};
struct Link749B8 {struct Link749B8 *next,*prev;};
struct Work749B8 {u8 prefix[0x5E4];struct Link749B8 *head;};

extern const void *gUnknown_0300002C;
extern u8 gUnknown_0202F800[512];
extern void *gUnknown_03007014;

void sub_08019184(u32 bank,u32 increment);
void sub_0805AC64(void);
u32 sub_08068864(void);
void sub_080749B8(struct Link749B8 *node);

void sub_08019184(u32 bank,u32 increment) {

 u32 value=increment;
 u8 *root=gSetupBuffer_03000590;
 u8 *setup=(u8 *)((bank<<8)+(u32)root);
 value+=setup[0xBB];
 if(value>255)value=255;
 setup[0xBB]=value;
}

void sub_0805AC64(void) {

 CpuFastSet((const void*)0x05000200,gUnknown_0202F800,0x80);
 CpuFastSet((const void*)0x05000000,gEquipmentPaletteShadow,0x80);
}

u32 sub_08068864(void) {

 volatile struct Dma68864 *dma=(void*)0x040000D4;
 dma->source=(u32)gUnknown_0300002C;
 dma->destination=0x05000000;
 dma->control=0x80000200;
 return dma->control;
}

void sub_080749B8(struct Link749B8 *node) {

 struct Link749B8 *previous=node->prev;
 if(previous!=0 || node->next!=0){
  struct Work749B8 *work=(struct Work749B8*)gUnknown_03007014;
  struct Link749B8 *head=work->head;
  if(head->prev==head){work->head=0;}
  else {
   node->next->prev=previous;
   node->prev->next=node->next;
   if(work->head==node)work->head=node->prev;
  }
  node->prev=0;
  node->next=0;
 }
}
