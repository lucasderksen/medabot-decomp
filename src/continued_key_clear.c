#include "input.h"
#include "later_graphics.h"

void sub_08050B9C(void)
{
    ClearBytes(&gNewKeys, 4);
    ClearBytes(&gRepeatedKeys, 4);
    ClearBytes(&gHeldKeys, 4);
}
