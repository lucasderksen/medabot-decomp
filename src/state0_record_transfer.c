#include "object_helpers.h"
#include "state0_work.h"
#include "state0_next_helpers.h"
#include "state0_next_helpers.h"

void sub_08015668(u32 first, u32 second)
{
    u8 *base = gSetupBuffer_03000590;
    u32 offset = first * 256;
    const u8 *source = gUnknownBytes_083B7F8C + *(u8 *)(offset + (u32)base + 1) * 3;
    u8 *scratch = gUnknown_0300052E;
    sub_08041D04(source, scratch, 3);
    source = gUnknownBytes_083B7E54 + scratch[second] * 6;
    base += 0xA8;
    offset += (u32)base;
    sub_08041D04(source, (u8 *)offset, 6);
    sub_08015564(first, second + 4);
}
