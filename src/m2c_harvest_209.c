/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Root122F4 {u8 prefix[0x168];u8 choice,result;u8 gap16A[0x1D];u8 selected;};
struct Dma595DC {u32 source,destination,control;};
struct DigitWork595DC {u8 pad0[0x13];u8 slot;};

extern const u8 gUnknown_083AD070[16];
extern s32 sub_0807CD2C(s32,s32);
extern u32 sub_0807CEC8(u32,u32);

void sub_080122F4(u32 value);
void sub_080595DC(const u8 *arg0, u32 arg1, u32 arg2);

void sub_080122F4(u32 value) {
 const u8 *choices=gUnknown_083AD070;
 u32 candidate=choices[sub_080424B8()&15];
 u32 direction=sub_080424B8()&1;
 u32 attempt=0;
 u8 *setup=gSetupBuffer_03000590;
 struct Root122F4 *work=(struct Root122F4 *)gState0TransferWork.bytes;
 u8 *selected=&work->selected;
 do {
  u32 bank=value+candidate;
  u32 bankOffset=bank<<8;
  if(((u8 *)(bankOffset+(u32)setup))[0xBA]) {
   work->choice=sub_080424B8()&3;
   work->result=((u8 *)(work->choice*24+bankOffset+(u32)setup))[0x5F];
   *selected=bank;
   return;
  }
  if(direction) {
   candidate++;
   if(candidate>2)candidate=0;
  } else if(candidate==0)candidate=2;
  else candidate--;
  attempt++;
 } while(attempt<=2);
}

void sub_080595DC(const u8 *arg0, u32 arg1, u32 arg2) {
    volatile struct Dma595DC *dma;
    struct DigitWork595DC *work;
    struct FrameObject *frames;
    u32 hundred;
    s32 temp_r6_2;
    u8 temp_r4;
    u8 temp_r5;
    u8 temp_r6;
    u8 temp_r6_3;

    temp_r6 = *arg0;
    hundred=100;
    temp_r4 = sub_0807CEC8(temp_r6, hundred);
    temp_r6_2 = temp_r6 - (hundred * temp_r4);
    temp_r5 = sub_0807CD2C(temp_r6_2, 0xA);
    temp_r6_3 = temp_r6_2 - (temp_r5 * 0xA);
    dma=(volatile struct Dma595DC *)0x040000D4;
    dma->source = (u32) (((temp_r4 + 0x30) << 5) + gNumericTiles_080ACCF4);
    work=(struct DigitWork595DC *)gContinuedOtherWork_030057A0;
    dma->destination = (s32) ((work->slot << 5) + 0x06017A00);
    dma->control = 0x84000008;
    (void)dma->control;
    sub_08048864((u32) work->slot, 0xC004U, work->slot + 0x99, 0xEU, 1U);
    frames=gFrameObjects;
    frames[work->slot].screenX = arg1;
    frames[work->slot].screenY = arg2;
    work->slot = (u8) (work->slot + 1);
    dma->source = (u32) (((temp_r5 + 0x30) << 5) + gNumericTiles_080ACCF4);
    dma->destination = (s32) ((work->slot << 5) + 0x06017A00);
    dma->control = 0x84000008;
    (void)dma->control;
    sub_08048864((u32) work->slot, 0xC004U, work->slot + 0x99, 0xEU, 1U);
    frames[work->slot].screenX = arg1 + 8;
    frames[work->slot].screenY = arg2;
    work->slot = (u8) (work->slot + 1);
    dma->source = (u32) (((temp_r6_3 + 0x30) << 5) + gNumericTiles_080ACCF4);
    dma->destination = (s32) ((work->slot << 5) + 0x06017A00);
    dma->control = 0x84000008;
    (void)dma->control;
    sub_08048864((u32) work->slot, 0xC004U, work->slot + 0x99, 0xEU, 1U);
    frames[work->slot].screenX = arg1 + 0x10;
    frames[work->slot].screenY = arg2;
    work->slot = (u8) (work->slot + 1);
}
