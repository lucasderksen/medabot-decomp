/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 sub_0803725C(void);
extern void sub_0803579C(u32,u32);
extern void sub_08035814(u32);
extern void sub_08037280(u32,u32);

void sub_08020D24(void);

void sub_08020D24(void) {

 u8 *work=gState0TransferWork.bytes;
 s32 ready;
 u8 *bank=&work[0x87];
 u32 firstBank=*bank;
 u8 *part=&work[0xA7];
 sub_0803579C(firstBank,*part);
 sub_08035814(*bank);
 ready=sub_0803725C();
 if(ready) {
  work[0xA6]=0x1A;
  work[0xAA]++;
 } else {
  u8 *setup;
  s32 kind;
 u32 partOffset,finalSetupRoot,finalRecordAddress;
  sub_08037280(*bank,*part);
  sub_08036270();
  setup=gSetupBuffer_03000590;
  partOffset=*part*24;
 kind=setup[partOffset+(*bank<<8)+0x49];
  switch(kind) {
  case 10:work[0x51]=ready;break;
  case 11:work[0x51]=1;break;
  case 12:work[0x51]=2;break;
  default:gState0TransferWork.bytes[0x51]=3;break;
  }
  finalSetupRoot=(u32)gSetupBuffer_03000590;
  finalRecordAddress=gState0TransferWork.bytes[0xA7]*24;
  finalRecordAddress+=gState0TransferWork.bytes[0x87]<<8;
  finalRecordAddress+=finalSetupRoot;
  gState0TransferWork.bytes[0x52]=*(u8 *)(finalRecordAddress+0x49);
  gState0TransferWork.bytes[0xAA]=4;
 }
}
