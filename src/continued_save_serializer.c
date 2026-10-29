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
#define FLAGS_PHYSICAL_WORD (*(u32 *)&gMainFlagsWord_03001784)

void sub_0805E010(void *buffer)
{
    u8 *base = buffer;
    s32 count = 0;
    struct SaveCopy28 *header = (struct SaveCopy28 *)gUnknown_03002B70;
    const u8 *signature = gMain2SerializerSignature_084836B4;
    u8 *destination;
    u16 *halfwords;
    struct SaveCopy8 *recordDestination;
    u32 packed;
    s32 maximum;
    void *pairs;
    u8 *bytes;
    u16 checksum;
    u8 *scan;
    do
    {
        base[count] = *(const u8 *)(count + (u32)signature);
        count++;
    } while (count <= 15);
    *(struct SaveCopy28 *)(base + 0x10) = *header;
    destination = base + 0x2C;
    for (count = 0; count <= 29; count++)
    {
        memcpy(destination, &gInventoryRecords[count], 64);
        destination += 64;
    }
    count = 0;
    maximum = 959;
    pairs = gObjectCountPairs;
    bytes = gObjectHalfwordBytes;
    halfwords = (u16 *)(base + 0x7AC);
    do
    {
        *halfwords++ = *(u8 *)(count + (u32)bytes);
        count++;
    } while (count <= maximum);
    recordDestination = (struct SaveCopy8 *)(base + 0xF2C);
    for (count = 0; count <= 8; count++)
        recordDestination[count] = ((struct SaveCopy8 *)gUnknownRecords_030017A0)[count];
    CpuSet(pairs, base + 0xF74, 64);
    CpuSet(gUnknown_030057E0, base + 0xFF8, 1632);
    { u8 *state = &gMainByte_03001788;
    packed = gMainByte_03001360 << 2;
    packed |= *state;
    packed |= gMainByte_03000B94 << 3;
    packed |= ((FLAGS_PHYSICAL_WORD << 30) >> 31) << 5;
    {
        u8 *packedDestination = base + 0x1CB8;
        checksum = 0;
        *packedDestination = packed;
    }
    }
    *(u16 *)(base + 0xFF4) = checksum;
    scan = base;
    count = 0;
    do
    {
        checksum += *scan++;
        count++;
    } while (count <= 0x1CBBu);
    *(u16 *)(base + 0xFF4) = checksum;
}
