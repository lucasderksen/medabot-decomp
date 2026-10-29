/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_display.h"
#include "state0_work.h"

extern const u8 gUnknown_087C9FF4[];
extern const u8 gUnknown_087CD9B0[];
extern const u8 gUnknown_087CDCE0[];
extern const u8 gUnknown_087D2074[];
extern const u8 gUnknown_087D5440[];
extern const u8 gUnknown_087D5758[];

void sub_0807028C(void);
void sub_08070464(void);

void sub_0807028C(void) {
 /* DMA consumes this fill word through its hardware source register. */
 u16 destination[640];
    u16 input[600];
    volatile u32 zero;
    
 volatile u32 *zeroPointer;
    
 s32 row, index, column, next, at30, at31, offset;
    u16 *source, *target, *pad30, *pad31, *inputRoot;
    volatile u32 *dma;
    const u8 *palette;
    
 LZ77UnCompVram(gUnknown_087C9FF4,(void*)0x06000000);
    
 LZ77UnCompVram(gUnknown_087CD9B0,input);
    
 *(zeroPointer=&zero)=0;
    
 {
        volatile u32 *first=(void*)0x040000D4;
    
 first[0]=(u32)zeroPointer;
    first[1]=0x06007800;
    first[2]=0x85000200;
    (void)first[2];
    }
 row=0;
    palette=gUnknown_087CDCE0;
    inputRoot=input;
    
 do {
  index=row<<5;
    offset=row<<4;
    next=row+1;
    offset-=row;
    source=(u16*)((u32)(offset<<2)+(u32)inputRoot);
    target=(u16*)((u32)(row*64)+(u32)destination);
    column=29;
    
copy:
  *target=*source;
    source++;
    target++;
    column--;
    
  if(column>=0)goto copy;
    
  at30=index+30;
    pad30=at30+destination;
    at31=index+31;
    pad31=at31+destination;
    *pad31=0;
    *pad30=0;
    
  row=next;
    
 }while(row<=19);
    
 dma=(void*)0x040000D4;
    
 dma[0]=(u32)destination;
    dma[1]=0x06007800;
    dma[2]=0x80000280;
    (void)dma[2];
    
 dma[0]=(u32)palette;
    dma[1]=0x05000000;
    dma[2]=0x80000100;
    (void)dma[2];
    
 *(volatile u16*)0x04000008=0xFC0;
    
 *(volatile u16*)0x04000000|=0x100;
    
}

void sub_08070464(void) {
 /* DMA consumes this fill word through its hardware source register. */
 u16 destination[640];
    u16 input[600];
    volatile u32 zero;
    
 volatile u32 *zeroPointer;
    
 s32 row, index, column, next, at30, at31, offset;
    u16 *source, *target, *pad30, *pad31, *inputRoot;
    volatile u32 *dma;
    const u8 *palette;
    
 LZ77UnCompVram(gUnknown_087D2074,(void*)0x06000000);
    
 LZ77UnCompVram(gUnknown_087D5440,input);
    
 *(zeroPointer=&zero)=0;
    
 {
        volatile u32 *first=(void*)0x040000D4;
    
 first[0]=(u32)zeroPointer;
    first[1]=0x06007800;
    first[2]=0x85000200;
    (void)first[2];
    }
 row=0;
    palette=gUnknown_087D5758;
    inputRoot=input;
    
 do {
  index=row<<5;
    offset=row<<4;
    next=row+1;
    offset-=row;
    source=(u16*)((u32)(offset<<2)+(u32)inputRoot);
    target=(u16*)((u32)(row*64)+(u32)destination);
    column=29;
    
copy:
  *target=*source;
    source++;
    target++;
    column--;
    
  if(column>=0)goto copy;
    
  at30=index+30;
    pad30=at30+destination;
    at31=index+31;
    pad31=at31+destination;
    *pad31=0;
    *pad30=0;
    
  row=next;
    
 }while(row<=19);
    
 dma=(void*)0x040000D4;
    
 dma[0]=(u32)destination;
    dma[1]=0x06007800;
    dma[2]=0x80000280;
    (void)dma[2];
    
 dma[0]=(u32)palette;
    dma[1]=0x05000000;
    dma[2]=0x80000100;
    (void)dma[2];
    
 *(volatile u16*)0x04000008=0xF80;
    
 *(volatile u16*)0x04000000|=0x100;
    
}
