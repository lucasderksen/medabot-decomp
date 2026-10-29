#include "global.h"
#include "gba.h"
#include "eeprom.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_inventory.h"
#include "object_helpers.h"
#include "continued_late_graphics.h"
#include "rom_libc.h"

/* Observed aligned copy units, not complete save/RAM allocation types. */

s32 sub_0805E248(void *buffer, u32 modeWord)
{
    u16 *source = buffer;
    s32 blockCount = 920;
    u16 block[4];
    s32 count;
    if ((u8)modeWord)
    {
        count = 0;
        do
        {
            block[0] = *source++;
            block[1] = *source++;
            block[2] = *source++;
            block[3] = *source++;
            ProgramEepromDwordEx(count, block);
            count++;
        } while (count < blockCount);
    }
    else
    {
        count = 0;
        do
        {
            u16 changed = ReadEepromDword(count, block);
            u32 index;
            for (index = 0; index <= 3; index++)
            {
                if (block[index] != *source)
                {
                    block[index] = *source;
                    changed = 1;
                }
                source++;
            }
            if (changed)
                ProgramEepromDwordEx(count, block);
            count++;
        } while (count < blockCount);
    }
    return 0;
}
