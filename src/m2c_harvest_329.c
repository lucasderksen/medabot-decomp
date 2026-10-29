/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_next_helpers.h"
#include "state0_work.h"


u32 sub_08018F48(u32 bank);
void sub_0801C660(void);

u32 sub_08018F48(u32 bank) {

 u32 index=0;
 u8 *root=gSetupBuffer_03000590;
 /* Unsigned word arithmetic retains wrapping bank offsets and operand order. */
 u8 *cursor=(u8 *)((u32)root-(0U-(bank<<8)));
 u32 result;
 cursor+=0xA1;
loop:
 if(*cursor!=0){result=index+1;goto done;}
 cursor-=0x18;
 index++;
 if(index<=3)goto loop;
 result=0;
done:
 return result;
}

void sub_0801C660(void) {

    s32 part=3;
    u8 *work=gState0TransferWork.bytes;
    u8 *cursor=gSetupBuffer_03000590;
    u8 *selection;
    /* The byte-derived signed offset preserves agbcc addition operand order. */
    cursor -= -((s32)work[0x87] << 8);
    cursor+=0xA1;
    selection=work+0xD0;
loop:
    if(*cursor!=0)*selection=part;
    else {
        cursor-=0x18;
        part--;
        if(part>=0)goto loop;
    }
    sub_08034F68(work[0x87],work[0xD0],work[work[0x89]*8+0x2D]);
    work[0xAA]++;
}
