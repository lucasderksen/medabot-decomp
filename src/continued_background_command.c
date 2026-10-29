#include "continued_commands.h"
#include "frame.h"
#include "background_state.h"
#include "continued_blend_work.h"
#include "fresh_helpers.h"
#include "palette_transfer_helpers.h"
#include "post_dispatch.h"
#include "later_graphics.h"

extern u8 gUnknown_030057E0[];

/* Partial view: byte 39 is observed; total work size remains unknown. */
struct BackgroundCommandView
{
    struct BackgroundState known;
    u8 unknown38;
    u8 unknown39;
};

void sub_0804CB94(void)
{
    u8 *work = gUnknown_030057E0;
    u16 *current = (u16 *)(work + 0xC8A);
    u16 snapshot = *current;
    u16 *previous = (u16 *)(work + 0xC8C);
    *previous = snapshot;
    sub_0804D8CC(1);
    if (((struct BackgroundCommandView *)&gBackgroundState_03005310)->unknown39 == 2)
        *current = *previous + work[0xC94];
}
