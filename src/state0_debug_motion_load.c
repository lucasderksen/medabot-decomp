

#include "state0_debug_menu.h"
#include "state0_work.h"
#include "state0_callbacks.h"
#include "frame_objects.h"
#include "object_helpers.h"
#include "display_helpers.h"
#include "input.h"
#include "main.h"
#include "utility_helpers.h"

extern u8 gDebugMenuTextBuffer[];
extern u8 gDebugProcessStateByte;
extern u8 gUnknown_030057E0[];
extern const void *const gDebugTinpetLabels_083ACC40[];
extern const void *const gDebugRandomLabels_083ACCA0[];
void sub_08042238(u8 value);

void sub_0800D6A8(void)
{
    sub_080445F4();
    sub_080446B4(0, gState0TypedWork.bytes[0x39], gState0TypedWork.bytes[0x39],
                  gState0TypedWork.bytes[0x39], gState0TypedWork.bytes[0x39],
                  56, 104, 0, 4, 0, 0, 0);
    sub_080446B4(1, gState0TypedWork.bytes[0x39], gState0TypedWork.bytes[0x39],
                  gState0TypedWork.bytes[0x39], gState0TypedWork.bytes[0x39],
                  184, 48, 0, 8, 1, 0, 1);
    gState0TypedWork.bytes[0x33]++;
}
