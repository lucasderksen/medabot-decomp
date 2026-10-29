#include "global.h"

/* The RAM object and this callback's gameplay role still need identifying.
 * Seven entries in the table near 0x083B2968 point to this function.
 */
extern u8 gUnknown_03000440[];

/* 0x08040B50; descriptive name is provisional. */
void SetUnknownState8(void)
{
    gUnknown_03000440[4] = 8;
}
