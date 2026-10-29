#ifndef GUARD_INPUT_H
#define GUARD_INPUT_H

#include "global.h"

enum
{
    KEY_A      = 1 << 0,
    KEY_B      = 1 << 1,
    KEY_SELECT = 1 << 2,
    KEY_START  = 1 << 3,
    KEY_RIGHT  = 1 << 4,
    KEY_LEFT   = 1 << 5,
    KEY_UP     = 1 << 6,
    KEY_DOWN   = 1 << 7,
    KEY_R      = 1 << 8,
    KEY_L      = 1 << 9,
};

extern u16 gHeldKeys;
extern u16 gPreviousKeys;
extern u16 gNewKeys;
extern u16 gReleasedKeys;
extern u16 gRepeatedKeys;
extern u8 gKeyRepeatCounter;

void ReadKeys(void);

#endif
