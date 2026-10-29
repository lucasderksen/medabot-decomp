#include "state0_next_helpers.h"
#include "state0_work.h"


u32 sub_08033074(void)
{
    return gState0ChoiceWeights_083AF080[sub_080424B8() & 15];
}

u32 sub_08033318(u32 first, u32 second)
{
    u8 *work = gState0TransferWork.bytes;
    u8 *result = work;
    u8 *field = work;
    u32 kind;
    result += 0x51;
    *result = 0;
    field += 0x5C;
    *field = first;
    second--;
    field++;
    *field = second;
    {
        const u32 *callbacks = gState0ActionCallbackWords_083AF090;
        u8 *records = gSetupBuffer_03000590;
        u32 offset = second * 24 + first * 256;
        u8 *entry = records + offset;
        entry += 0x49;
        kind = *entry;
        ((void (*)(void))callbacks[kind])();
    }
    return *result;
}
