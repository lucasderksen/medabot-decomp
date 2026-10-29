/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ContinuedSetupD3D4 {
    u8 prefix[0xBD];
    u8 flags;
    u8 tail[0x42];
};
struct ContinuedWorkD3D4 {
    u8 prefix[0x60];
    u8 bank;
    u8 gap61[0x67];
    u16 amount;
    u8 gapCA[8];
    u8 results[3];
    u8 gapD5;
    u16 values[3];
    u8 gapDC[0x10];
    s16 coordinate;
};

extern u8 gDebugMenuTextBuffer[0x53];
extern u8 gUnknown_030004F2[7];
extern u8 gUnknown_03000506[7];

void sub_0802D3D4(void);

void sub_0802D3D4(void) {

    u32 i=0;
    struct ContinuedWorkD3D4 *work=(struct ContinuedWorkD3D4 *)gState0TransferWork.bytes;
    u8 *bank=&work->bank;
    s16 *coordinate=&work->coordinate;
    u8 *firstText=gDebugMenuTextBuffer;
    u8 *text;

    do {
        /* i is 0..2; unsigned word arithmetic preserves the ROM ADD order. */
        if (*(u8 *)(i - (0U - (u32)work->results))) {
            struct ContinuedSetupD3D4 *setup=(struct ContinuedSetupD3D4 *)gSetupBuffer_03000590;
            u32 row=*bank+i;
            if(setup[row].flags&4)sub_08034F68(row,0,1);
            else sub_08034F68(row,0,*coordinate);
            ((struct ContinuedWorkD3D4 *)gState0TransferWork.bytes)->values[i]=((struct ContinuedWorkD3D4 *)gState0TransferWork.bytes)->amount;
            switch(i) {
            case 0:
                sub_0801A28C(firstText,((struct ContinuedWorkD3D4 *)gState0TransferWork.bytes)->amount,1);
                sub_0801A33C(firstText,*bank+i,0x21);
                break;
            case 1:
                text=gUnknown_030004F2;
                sub_0801A28C(text,((struct ContinuedWorkD3D4 *)gState0TransferWork.bytes)->amount,1);
                sub_0801A33C(text,*bank+1,0x21);
                break;
            case 2:
                text=gUnknown_03000506;
                sub_0801A28C(text,((struct ContinuedWorkD3D4 *)gState0TransferWork.bytes)->amount,1);
                sub_0801A33C(text,*bank+2,0x21);
                break;
            }
        }
        i++;
    }while(i<=2);
    sub_08074DE0(0x5B);
    gState0TypedWork.bytes[0x84]=0;
    gState0TransferWork.bytes[0xAA]++;
}
