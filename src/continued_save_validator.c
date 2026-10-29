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
/* Access coverage of observed fields only; no allocated save extent. */
struct SaveHeaderAccess {
    u8 signature00[16];
    u32 word10;
    u8 name14[16];
    u16 half24, half26;
    u32 word28;
};

s32 sub_0805E138(void *buffer)
{
    u8 *base = buffer;
    s32 blockCount = 920;
    u16 *destination = buffer;
    u16 block[4];
    s32 count;
    s32 empty;
    u16 checksum;
    u8 *scan;
    count = 0;
    do
    {
        ReadEepromDword(count, block);
        *destination++ = block[0];
        *destination++ = block[1];
        *destination++ = block[2];
        *destination++ = block[3];
        count++;
    } while (count < blockCount);
    for (count = 0; count <= 12; count++)
    {
        if (gMain2SerializerSignature_084836B4[count] != base[count])
            return 1;
    }
    empty = 1;
    for (count = 0; count <= 15; count++)
    {
        if (((struct SaveHeaderAccess *)base)->name14[count] == 0xFE)
            break;
        if (((struct SaveHeaderAccess *)base)->name14[count] != 0)
        {
            empty = 0;
            break;
        }
    }
    if (empty)
        return -1;
    if (*(u32 *)(base + 0x10) > 99999)
        return -1;
    if (*(u16 *)(base + 0x24) > 9999)
        return -1;
    if (*(u16 *)(base + 0x24) < *(u16 *)(base + 0x26))
        return -1;
    if (*(u32 *)(base + 0x28) > 21599999)
        return -1;
    if ((base[0x1CB8] & 3) > 2 || ((base[0x1CB8] >> 3) & 3) > 2)
        return -1;
    empty = *(u16 *)(base + 0xFF4);
    *(u16 *)(base + 0xFF4) = 0;
    checksum = 0;
    scan = base;
    count = 0;
    do
    {
        checksum += *scan++;
        count++;
    } while (count <= 0x1CBBu);
    if (checksum != empty)
        return -1;
    return 0;
}
