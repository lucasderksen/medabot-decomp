#include "main_callbacks.h"
#include "global.h"

extern u32 gMainSubstate;
extern const MainCallback gMainState0Callbacks[];
extern const MainCallback gMainState1Callbacks[];
extern const MainCallback gMainState3Callbacks[];
extern u32 gUnknown_0300137C;
extern const MainCallback gUnknownCallbacks_083AC3C8[];

/* These descriptive table names identify their index in gMainCallbacks.
 * Gameplay roles and some table lengths remain provisional.
 */
void sub_08002534(void)
{
    gMainState0Callbacks[gMainSubstate]();
}

void sub_08002554(void)
{
    gUnknownCallbacks_083AC3C8[gUnknown_0300137C]();
}

void sub_0804763C(void)
{
    gMainState1Callbacks[gMainSubstate]();
}

void sub_08068440(void)
{
    gMainState3Callbacks[gMainSubstate]();
}
