#ifndef GUARD_LINK_MENU_H
#define GUARD_LINK_MENU_H

#include "global.h"

/* Partial view of the context used by the link-menu swap callbacks. */
struct LinkSwapContext
{
    u8 unknown00[0x31];
    u8 firstX;
    u8 secondX;
    u8 firstY;
    u8 secondY;
    u8 unknown35[7];
    u16 timer;                 /* 3C */
};

/* Reverse-copy up to twenty ASCII glyphs into the selected BG screen row. */
void sub_080674BC(u8 *str, u8 row);

#endif
