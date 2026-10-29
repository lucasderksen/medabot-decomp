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

void sub_08059560(void)
{
    s32 index;
    for(index=0;index<40;index++)sub_08048888((u8)index);
}

void sub_08059578(void)
{
    struct NumericOtherFields *work=(struct NumericOtherFields *)gContinuedOtherWork_030057A0;
    u32 zero;
    if(work->byte11==0)
    {
        work->byte10=0;
        sub_08059560();
    }
    zero=0;
    work->byte15=zero;
    switch((s32)work->byte14)
    {
    case 0:
    case 2:
        gBackgroundState_03005310.unknown00[1]=0;
        gUnknown_0300137C=51;
        break;
    case 1:
        gBackgroundState_03005310.unknown00[1]=zero;
        gUnknown_0300137C=51;
        break;
    default:
        gUnknown_0300137C=5;
        break;
    }
}
