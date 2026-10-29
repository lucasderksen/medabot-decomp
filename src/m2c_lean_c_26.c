/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_work.h"

struct SaveHeaderView { u32 money; u8 name[0x10]; u16 half14; u16 half16; s32 time18; };

extern struct SaveHeaderView gSaveHeaderView_03002B70 asm("gPostDispatchWord_03002B70");

s32 sub_0805DEC8(void);

s32 sub_0805DEC8(void) {

    s32 result;
    s32 i;
    s32 value;

    value = sub_08074FA4(4);
    if (value != 0)
        return value;
    sub_08074B88(0);
    sub_08074DE0(0);
    for (i = 0; i < 16; i++)
        gSaveHeaderView_03002B70.name[i] = value = 0xFE;
    for (i = 0; i <= 3; i++)
    {
        result = sub_0805DDEC(1);
        if (result == 0)
            break;
    }
    return result;
}
