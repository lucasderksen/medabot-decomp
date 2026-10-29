

#include "state0_debug_menu.h"
#include "state0_work.h"
#include "main.h"

extern const MainCallback gDebugPartCallbacks_083ACAD8[];
extern const MainCallback gDebugTinpetCallbacks_083ACAE4[];
extern const MainCallback gDebugItemCallbacks_083ACAF0[];
extern const MainCallback gDebugFaceCallbacks_083ACAFC[];
extern const MainCallback gDebugMedalImageCallbacks_083ACB08[];
extern const MainCallback gDebugRandomCallbacks_083ACB14[];
extern const MainCallback gDebugBattleCallbacks_083ACB20[];
extern const MainCallback gDebugSoundCallbacks_083ACB2C[];
extern const MainCallback gDebugMotionCallbacks_083ACB38[];

void sub_0800C29C(void)
{
    gDebugPartCallbacks_083ACAD8[gState0TypedWork.bytes[0x33]]();
}

void sub_0800C6D8(void)
{
    gDebugTinpetCallbacks_083ACAE4[gState0TypedWork.bytes[0x33]]();
}

void sub_0800C7E4(void)
{
    gDebugItemCallbacks_083ACAF0[gState0TypedWork.bytes[0x33]]();
}

void sub_0800CBA8(void)
{
    gDebugFaceCallbacks_083ACAFC[gState0TypedWork.bytes[0x33]]();
}

void sub_0800CE70(void)
{
    gDebugMedalImageCallbacks_083ACB08[gState0TypedWork.bytes[0x33]]();
}

void sub_0800D168(void)
{
    gDebugRandomCallbacks_083ACB14[gState0TypedWork.bytes[0x33]]();
}

void sub_0800D25C(void)
{
    gDebugBattleCallbacks_083ACB20[gState0TypedWork.bytes[0x33]]();
}

void sub_0800D3C4(void)
{
    gDebugSoundCallbacks_083ACB2C[gState0TypedWork.bytes[0x33]]();
}

void sub_0800D664(void)
{
    gDebugMotionCallbacks_083ACB38[gState0TypedWork.bytes[0x33]]();
}
