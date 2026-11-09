#include "main_callbacks.h"
#include "global.h"

extern u32 gMainSubstate;
extern const MainCallback gMainState0Callbacks[];
extern const MainCallback gMainState1Callbacks[];
extern const MainCallback gMainState3Callbacks[];
extern u32 gNestedCallbackIndex;
extern const MainCallback gUnknownCallbacks_083AC3C8[];

/* These descriptive table names identify their index in gMainCallbacks.
 * Gameplay roles and some table lengths remain provisional.
 */
void DispatchMainState0(void)
{
    gMainState0Callbacks[gMainSubstate]();
}

void DispatchMainState0Substate0(void)
{
    gUnknownCallbacks_083AC3C8[gNestedCallbackIndex]();
}

void DispatchMainState1(void)
{
    gMainState1Callbacks[gMainSubstate]();
}

void DispatchMainState3(void)
{
    gMainState3Callbacks[gMainSubstate]();
}
