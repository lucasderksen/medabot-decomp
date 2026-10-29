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
struct SaveCopy28 { u32 words[7]; };
struct SaveCopy8 { u32 words[2]; };

/* Private view of observed flag accesses; original field declarations unknown. */
struct FlagsBitAccess { u32 bit0:1; u32 bit1:1; u32 remaining:30; };
#define FLAGS_BITS ((struct FlagsBitAccess *)&gMainFlagsWord_03001784)


void sub_0805DF18(void *buffer)
{
    u8 *base = buffer;
    u8 *source;
    u8 *destination;
    s32 count;
    u16 *halfwords;
    struct SaveCopy8 *recordSource;
    u32 packed;
    s32 maximum;
    void *pairs;
    u8 *bytes;
    *(struct SaveCopy28 *)gUnknown_03002B70 = *(struct SaveCopy28 *)(base + 0x10);
    source = base + 0x2C;
    destination = (u8 *)gInventoryRecords;
    count = 29;
    do
    {
        memcpy(destination, source, 64);
        source += 64;
        destination += 64;
        count--;
    } while (count >= 0);
    count = 0;
    maximum = 959;
    pairs = gObjectCountPairs;
    bytes = gObjectHalfwordBytes;
    halfwords = (u16 *)(base + 0x7AC);
    do
    {
        *(u8 *)(count + (u32)bytes) = *halfwords++;
        count++;
    } while (count <= maximum);
    recordSource = (struct SaveCopy8 *)(base + 0xF2C);
    for (count = 0; count <= 8; count++)
        ((struct SaveCopy8 *)gUnknownRecords_030017A0)[count] = recordSource[count];
    CpuSet(base + 0xF74, pairs, 64);
    CpuSet(base + 0xFF8, gUnknown_030057E0, 1632);
    { u8 *state = &gMainByte_03001788;
    packed = base[0x1CB8];
    *state = packed;
    *state &= 3;
    gMainByte_03001360 = ((u8)packed >> 2) & 1;
    gMainByte_03000B94 = ((u8)packed >> 3) & 3;
    FLAGS_BITS->bit1 = ((u8)packed >> 5) & 1;
    }
}
