#include "eeprom.h"

const char gEepromLibraryVersion[12] = "EEPROM_V122";

const struct EepromConfig gEepromConfig4K =
{
    512, 64, 0x0300, 6, {0, 0, 0}
};

const struct EepromConfig gEepromConfig64K =
{
    8192, 1024, 0x0300, 14, {0, 0, 0}
};

/* Three used halfwords followed by the observed zero alignment halfword. */
const u16 gEepromTimeoutParams[4] = {10, 0xFFBD, 0x00C2, 0};
