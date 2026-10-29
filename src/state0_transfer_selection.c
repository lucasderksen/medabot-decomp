#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "display_helpers.h"
#include "frame.h"
#include "main.h"

u32 sub_08007440(u32 index);
void sub_0800712C(void);
void sub_08014F90(u32,u32);
extern u8 gUnknown_03000590[];
extern u8 gTransferSelectedSlots[3];
extern const u8 gState0NextRow_083AC5E8[];

void sub_0800725C(void)
{
    u8 *slot;
    switch (gState0TypedWork.bytes[0x50]) {
    case 1: case 2: case 3: {
        s32 i=2;
        do {
            slot=&gTransferSelectedSlots[i];
            if (*slot) goto deselect;
            i--;
        } while (i>=0);
        goto done;
    }
    default:
        if (gState0TypedWork.bytes[0x52]&0x80) {
            sub_08074DE0(2); gState0TypedWork.bytes[0x52]=0; sub_08005798();
            goto done;
        }
        if (sub_080440B4()) {
            sub_08074DE0(5); gUnknown_0300137C++;
            goto done;
        }
        break;
    }
    goto failed;
deselect:
    *slot=0;
    sub_0800712C(); sub_08074DE0(5);
    goto done;
failed:
    sub_08074DE0(6); gUnknown_0300137C=11;
done:
    return;
}

void sub_08007408(void)
{
    switch (gState0TypedWork.bytes[0x50]) {
    case 1: case 2: {
        if (gState0TransferWork.bytes[0x41]) {
            sub_08074DE0(4); gUnknown_0300137C=32;
        }
        break;
    }
    }
}

void sub_0800750C(void)
{
    if (gState0TypedWork.bytes[0x50])
        sub_0803EF8C(16,4,13,16,*(volatile u16 *)0x0400000C,0);
}

void sub_08007540(void)
{
    u32 i=0;
    u8 *transfer=gState0TransferWork.bytes;
    u8 *base=gUnknown_03000590;
    u8 *count=transfer+0x5B;
    u8 *source=base+0x340;
    do {
        if (*source) (*count)++;
        source+=256;
        i++;
    } while (i<=2);
    sub_08014F90(3,transfer[0x5B]);
}

void sub_080072EC(void)
{
    switch (gState0TypedWork.bytes[0x50]) {
    case 1: case 2: case 3: {
        u32 i;
        for(i=0;i<=2;i++) {
            u8 *transfer=gState0TransferWork.bytes;
            u8 *slot;
            transfer+=0x41;
            slot=transfer+i;
            if (!*slot) {
                struct State0Record8 *base;
                u8 *work;
                if (!sub_08007440(i)) goto failed;
                base=gUnknownRecords_030017A0;
                work=gState0TypedWork.bytes;
                if (base[work[0x51]].unknown00[0]!=3) goto failed;
                sub_08074DE0(4);
                *slot=work[0x51]+16;
                sub_0800712C();
                if(i==2) {
                    switch(work[0x50]) {
                    case 1: case 2: goto confirmed;
                    default: gUnknown_0300137C=40; goto done;
                    }
                }
                if(sub_080440B4()==i+1) goto confirmed;
                work[0x51]=gState0NextRow_083AC5E8[work[0x51]];
                sub_08004EF8(0); sub_08004EF8(1); sub_08004EF8(2); sub_08004EF8(3);
                sub_08005118(); sub_0800519C(); sub_0800522C(); sub_080053C8();
                sub_08005000(); sub_08005948();
                goto done;
failed:
                sub_08074DE0(6);
                goto done;
            }
            sub_08074DE0(6);
        }
        break;
    }
    default:
        if(gUnknownRecords_030017A0[gState0TypedWork.bytes[0x51]].unknown00[0]) {
            sub_08074DE0(4); gUnknown_0300137C=8;
        } else goto defaultFailed;
        break;
    }
    goto done;
confirmed:
    gUnknown_0300137C=32;
    goto done;
defaultFailed:
    sub_08074DE0(6);
done:
    return;
}
