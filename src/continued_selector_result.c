#include "global.h"
#include "continued_late_graphics.h"
#include "continued_commands.h"
#include "object_numeric_helpers.h"
#include "fresh_helpers.h"
#include "background_state.h"

struct NumericOtherFields
{
    u8 unknown00[0x10];
    u8 byte10,byte11,byte12,byte13,byte14,byte15;
    u8 modes[8];
};
struct NumericDma {u32 source,destination,control;};
#define OTHER (*(struct NumericOtherFields *)gContinuedOtherWork_030057A0)

u32 sub_080594C8(void)
{
    struct NumericOtherFields *work=(struct NumericOtherFields *)gContinuedOtherWork_030057A0;
    switch((s32)work->byte14)
    {
    case 0:
    case 1:
    case 2:
    case 4:
        return 1;
    case 3:
        if(sub_0805424C()==4)
        {
            u8 *base=gUnknown_030057E0;
            u8 *selected=base+0xC5C;
            *selected=0;
            if(work->byte12==14||work->byte12==18)
            {
                volatile struct NumericDma *dma;
                const void *const *sources;
                const u8 *lookup;
                sub_08048288();
                dma=(void *)0x040000D4;
                sources=gPaletteSourcePointers_083F83C0;
                lookup=gFreshBytes_083D2B26;
                dma->source=(u32)sources[lookup[*selected]];
                dma->destination=0x05000200;
                dma->control=0x84000008;
                dma->control;
                {
                    u32 value=*selected;
                    u8 *destination=base+0xC28;
                    *destination=value;
                }
                sub_0805330C();
            }
            sub_08050C94();
            return 1;
        }
        return 0;
    }
    /* No R0 assignment is observed on the remaining selector paths. */
}

