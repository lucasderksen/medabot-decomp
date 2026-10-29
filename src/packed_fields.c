#include "continued_commands.h"
#include "packed_fields.h"
#include "bitfields.h"
#include "frame.h"


/* 0x080502C8: three bytes per subentry, four subentries per high nibble. */
u8 sub_080502C8(u8 value)
{
    u32 high = ExtractHighNibble(value);
    u32 low = ExtractLowTwoBits(value);
    return (u8)high * 12 + (u8)low * 3;
}

/* 0x08050300: derive an index from the observed record byte. */
u8 sub_08050300(u8 index, u8 value)
{
    return gFrameObjects[index].byte2B * 4 + value;
}

/* 0x08050320: the mapper's result is biased by 79 record strides. */
u8 sub_08050320(u8 index, u8 value)
{
    return gFrameObjects[sub_0804DBF0(index) + 0x4F].byte2B * 12 + value * 3;
}
