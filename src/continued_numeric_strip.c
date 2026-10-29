#include "global.h"
#include "continued_late_graphics.h"
#include "object_numeric_helpers.h"
#include "frame.h"

struct NumericStripOther
{
    u8 unknown00[0x13];
    u8 byte13;
};
struct NumericStripDma {u32 source,destination,control;};

void sub_080598C0(const void *source,u32 count,u32 x,u32 y)
{
    if((s32)count>0)
    {
        volatile struct NumericStripDma *dma=(void *)0x040000D4;
        struct NumericStripOther *work=(struct NumericStripOther *)gContinuedOtherWork_030057A0;
        struct FrameObject *objects=gFrameObjects;
        u32 remaining=count;
        do
        {
            dma->source=(u32)(gNumericTiles_080ACCF4+*(const u8 *)source*32);
            dma->destination=0x06017A00+work->byte13*32;
            dma->control=0x84000008;
            dma->control;
            sub_08048864(work->byte13,0xC004,work->byte13+0x99,14,1);
            objects[work->byte13].screenX=x;
            objects[work->byte13].screenY=y;
            x+=8;
            work->byte13++;
            source=(const u8 *)source+1;
            remaining--;
        }while(remaining);
    }
}
