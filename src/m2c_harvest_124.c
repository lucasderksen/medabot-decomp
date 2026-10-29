/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern s32 sub_08036D64(s32,s32);
extern void sub_08036E64(s32,s32,s16,s16);
extern void sub_0803836C(void);

void sub_080287DC(void);

void sub_080287DC(void) {
  u32 i;
  u8 *initial;
  sub_0803836C();
  initial=gState0TransferWork.bytes;
  initial[0x60]=sub_08032FB8(initial[0x87]);
  for(i=0;i<3;i++) {
    u8 *setup=gSetupBuffer_03000590;
    u8 *work=gState0TransferWork.bytes;
    u32 slot=work[0x60]+i;
    u8 *record=setup+(slot<<8);
    u32 kind;
    if(record[0x40]==0) continue;
    if(record[0x59]==0) continue;
    if(sub_080331F8(slot)==0) continue;
    kind=setup[(work[0x87]<<8)+0xA8]-0xC;
    switch(kind) {
case 0: {
 u8 *results;u8 *caseWork=gState0TransferWork.bytes;
 u8 *count=caseWork+0x60;
 if(sub_08036D64(*count+i,13)==0) {
   results=caseWork+0xD2; results[i]=1;
   sub_08036E64(*count+i,13,*(s16 *)(caseWork+0xE8),*(s16 *)(caseWork+0xEC));
 }
 break;
}
case 2: {
 u8 *results;u8 *caseWork=gState0TransferWork.bytes;
 u8 *count=caseWork+0x60;
 if(sub_08036D64(*count+i,16)==0) {
   results=caseWork+0xD2; results[i]=1;
   sub_08036E64(*count+i,16,*(s16 *)(caseWork+0xE8),*(s16 *)(caseWork+0xEC));
 }
 break;
}
case 4: {
 u8 *results;u8 *caseWork=gState0TransferWork.bytes;
 u8 *count=caseWork+0x60;
 if(sub_08036D64(*count+i,18)==0) {
   results=caseWork+0xD2; results[i]=1;
   sub_08036E64(*count+i,18,*(s16 *)(caseWork+0xE8),*(s16 *)(caseWork+0xEC));
 }
 break;
}
case 6: {
 u8 *results;u8 *caseWork=gState0TransferWork.bytes;
 u8 *count=caseWork+0x60;
 if(sub_08036D64(*count+i,19)==0) {
   results=caseWork+0xD2; results[i]=1;
   sub_08036E64(*count+i,19,*(s16 *)(caseWork+0xE8),*(s16 *)(caseWork+0xEC));
 }
 break;
}
case 28: {
 u8 *results;u8 *caseWork=gState0TransferWork.bytes;
 results=caseWork+0xD2; results[i]=1;
 sub_08036E64(caseWork[0x60]+i,0x2C,*(s16 *)(caseWork+0xE8),*(s16 *)(caseWork+0xEC));
 break;
}
    }
  }
  gState0TransferWork.bytes[0xAA]++;
}
