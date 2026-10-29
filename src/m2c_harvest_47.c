/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"

extern s8 gUnknown_0300056F;
extern void (*gUnknown_083AF860[])(void);
extern void (*gUnknown_083AF8A0[])(void);

s32 sub_080385F8(void);
s32 sub_0803884C(void);

s32 sub_080385F8(void) {
    s32 offset;
    s32 idle;
    u32 i;
    s8 *current;
    void (**handlers)(void);
    u8 *object;
    idle = 1;
    i = 0;
    current = &gUnknown_0300056F;
    offset = 0x840;
    handlers = gUnknown_083AF860;
    do {
        *current = i + 0x21;
        object = offset + (u8 *) gFrameObjects;
        if (object[0x29] != 0) {
            idle = 0;
        }
        handlers[object[0x29]]();
        offset += 0x40;
        i += 1;
    } while (i <= 0x1AU);
    return idle;
}

s32 sub_0803884C(void) {
    s32 offset;
    s32 idle;
    u32 i;
    s8 *current;
    void (**handlers)(void);
    u8 *object;
    idle = 1;
    i = 0;
    current = &gUnknown_0300056F;
    offset = 0x840;
    handlers = gUnknown_083AF8A0;
    do {
        *current = i + 0x21;
        object = offset + (u8 *) gFrameObjects;
        if (object[0x29] != 0) {
            idle = 0;
        }
        handlers[object[0x29]]();
        offset += 0x40;
        i += 1;
    } while (i <= 0x1AU);
    return idle;
}
