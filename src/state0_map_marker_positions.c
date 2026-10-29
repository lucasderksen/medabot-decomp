#include "state0_next_helpers.h"
#include "state0_work.h"
#include "frame.h"

struct ObservedSetupEntry { u8 unknown00[0x40]; u8 enabled; u8 unknown41[0xBF]; };
void sub_0801A0D0(void)
{
    u32 index = 0;
    struct ObservedSetupEntry *setup = (void *)gSetupBuffer_03000590;
    struct FrameObject *objects = gFrameObjects;
    do
    {
        if (setup[index].enabled != 0)
            sub_08015A00(index, objects[index * 4 + 93].screenX,
                        objects[index * 4 + 93].screenY - 4);
        index++;
    } while (index <= 5);
}
