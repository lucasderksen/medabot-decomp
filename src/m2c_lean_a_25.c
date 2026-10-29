/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"

struct Work175FC { u8 pad[0x82]; u8 selection82; };

extern struct Work175FC gWork175FC asm("gCounter6ED08_03001800");
extern u8 gFamilyKeyBytes49558_0300058C;
extern void sub_08074DE0(u32);

void sub_080175FC(void);

void sub_080175FC(void) {

    u8 previous;

    previous = gWork175FC.selection82;
    if (gFamilyKeyBytes49558_0300058C & 0x40)
        gWork175FC.selection82 = 1;
    if (gFamilyKeyBytes49558_0300058C & 0x80)
        gWork175FC.selection82 = 0;
    if (gFamilyKeyBytes49558_0300058C & 0x20)
        gWork175FC.selection82 = 2;
    if (gFamilyKeyBytes49558_0300058C & 0x10)
        gWork175FC.selection82 = 3;
    if (gWork175FC.selection82 != previous) {
        sub_08074DE0(2);
        sub_08017178(1);
        sub_080171C0(1);
        sub_08017208(1);
        sub_08017130(1);
        sub_08017268();
        sub_080173B4(0);
    }
}
