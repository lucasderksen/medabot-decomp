#include "bitfields.h"

/* 0x080502B0: discard all but the low byte, then extract its high nibble.
 * The original signature is unknown; u32 preserves the observed truncation
 * for any caller. There is no inline assembly in this matching C function.
 */
u32 ExtractHighNibble(u32 value)
{
    return (u8)value >> 4;
}

/* 0x080502B8: agbcc's u8 argument truncation and bit mask reproduce all
 * fourteen instruction bytes; original names are unknown.
 */
u8 ExtractLowTwoBits(u8 value)
{
    return value & 3;
}
