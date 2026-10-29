/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_work.h"

extern const u8 gUnknown_080AF774[];
extern const u8 gUnknown_080AF7EC[];
extern u8 gContinuedWork_030057E0[];
extern u8 gFamilyKeyBytes49558_0300058C;

s32 sub_0805B8EC(void);

s32 sub_0805B8EC(void) {

    u8 **root = (u8 **)&gMainContextPointer_03006F74;
    u8 *context = *root;
    u8 previous = context[0x17];
    s32 offset = previous * 4 + gContinuedWork_030057E0[0xC32] * 40;
    const u8 *table;
    u8 flag;

    flag = context[0x18];
    table = gUnknown_080AF774;
    if (flag != 0)
        table = gUnknown_080AF7EC;
    if (gFamilyKeyBytes49558_0300058C & 0x20)
        context[0x17] = table[offset];
    else if (gFamilyKeyBytes49558_0300058C & 0x10)
        context[0x17] = table[offset + 1];
    else if (gFamilyKeyBytes49558_0300058C & 0x40)
        context[0x17] = table[offset + 2];
    else if (gFamilyKeyBytes49558_0300058C & 0x80)
        context[0x17] = table[offset + 3];
    else
        goto none;
    sub_08074DE0(previous != (*root)[0x17] ? 2 : 6);
    return 1;
none:
    return 0;
}
