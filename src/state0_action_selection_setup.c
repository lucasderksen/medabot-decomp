#include "state0_next_helpers.h"
#include "state0_work.h"
#include "global.h"
#include "state0_next_helpers.h"
struct ObservedSetupE0 { u8 unknown00[0xE0]; u8 byteE0; u8 unknownE1[0x1F]; };

void sub_080346C4(void)
{
    u8 *work = gState0TransferWork.bytes;
    u8 *selected = work + 0x87;
    u32 next;
    struct ObservedSetupE0 *base, *record;
    work[0x60] = sub_08032FB8(*selected);
    next = sub_08033090(work[0x60]);
    base = (void *)gSetupBuffer_03000590;
    record = &base[*selected];
    record->byteE0 = next + 1;
    sub_08035528(*selected);
    sub_080355C4(*selected);
    sub_08034F08();
}
