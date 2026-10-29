#include "global.h"
#include "gba.h"
#include "initialization.h"
#include "eeprom.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "rom_libc.h"

u16 Unknown_0805DEB0(void)
{
    return SetEepromTimerIntr(2, &gIntrTable[11]);
}
