/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_display.h"
#include "state0_work.h"

struct SoundDmaRegisters {u32 source,destination,control;};
struct AudioQueueF4 {u8 bytes[48];u8 cursor;};
struct AudioOwnerF4 {u8 before8[8];struct AudioQueueF4 *queue;};
struct Buffer7424C {u8 bytes[48];u8 cursor;};
struct Work7424C {u8 pad0[8];struct Buffer7424C *buffer;u8 padC[0x3C];u16 value48;u8 pad4A[0x1C];u8 flag66;};

extern const u32 gUnknown_08486E54[];

void sub_08073AB8(u32 channel,const void *source);
void sub_080741F4(void *record);
void sub_0807424C(struct Work7424C *work);

void sub_08073AB8(u32 channel,const void *source) {

 volatile struct SoundDmaRegisters *dma=(volatile struct SoundDmaRegisters *)(0x040000B0U+channel*12U);
 u32 destinations;
 dma->source=(u32)source;
 destinations=(u32)gUnknown_08486E54;
 dma->destination=*(const u32 *)(destinations+((channel-1U)<<2));
 dma->control=0xF6400004;
}

void sub_080741F4(void *record) {

 s32 fill;
 struct AudioOwnerF4 *owner=record;
 struct AudioQueueF4 *queue=owner->queue;
 if(queue){
  fill=-1;
  CpuSet(&fill,queue,0x0500000C);
  owner->queue->cursor=0;
 }
}

void sub_0807424C(struct Work7424C *work) {

 struct Buffer7424C *buffer;u8 *cursor;u8 flag;u32 next;
 buffer=work->buffer;if(buffer!=0){flag=work->flag66;cursor=&buffer->cursor;
 if(flag!=0){buffer->bytes[*cursor]=work->value48;}else{buffer->bytes[*cursor]=0xFF;}
 next=*cursor+1;*cursor=next;if((u8)next>0x2F)*cursor=0;}}
