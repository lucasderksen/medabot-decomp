#ifndef GUARD_BG_SCROLL_H
#define GUARD_BG_SCROLL_H

#include "global.h"

struct BgScroll
{
    u16 x;
    u16 y;
};

extern struct BgScroll gBgScrollBase;
extern struct BgScroll gBgScroll0;
extern struct BgScroll gBgScroll1;
extern struct BgScroll gBgScroll2;
extern struct BgScroll gBgScroll3;

#endif
