#include "input.h"

#define REG_KEYINPUT (*(volatile u16 *)0x04000130)
#define KEY_MASK 0x03FF

/* Names are descriptive; the original function and variable names are unknown. */
void ReadKeys(void)
{
    gPreviousKeys = gHeldKeys;
    gHeldKeys = REG_KEYINPUT ^ KEY_MASK;
    gNewKeys = gHeldKeys & ~gPreviousKeys;
    gReleasedKeys = gPreviousKeys & ~gHeldKeys;
    gRepeatedKeys = 0;

    if (gNewKeys != 0)
    {
        gRepeatedKeys = gNewKeys;
        gKeyRepeatCounter = 16;
    }

    if (gHeldKeys != 0)
    {
        if (gKeyRepeatCounter == 0)
        {
            gRepeatedKeys = gNewKeys | gHeldKeys;
            gKeyRepeatCounter = 3;
        }
        else
        {
            gKeyRepeatCounter--;
        }
    }
}
