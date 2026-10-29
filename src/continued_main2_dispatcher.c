#include "global.h"
#include "input.h"
#include "main.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "main_callbacks.h"

struct Main2OutgoingView
{
    u32 unknown00;
    u16 word04,word06;
    u8 unknown08[0x14];
    u32 word1C;
};

void sub_0805BBE0(void)
{
    struct Main2OutgoingView *work=(struct Main2OutgoingView *)&gMainSerialOutgoingWork;
    u16 held=gHeldKeys;
    u32 zero=0;
    work->word04=held;
    work->word06=zero;
    gMainContextPointer_03006F74=&gState0TransferWork;
    if(gMainFlag_03005030!=0 && (work->word1C&0x00FFFF00)!=0)
    {
        gMainState=zero;
        gMainSubstate=10;
        gUnknown_0300137C=16;
    }
    else
        gMain2Callbacks_08483594[gMainSubstate]();
}
