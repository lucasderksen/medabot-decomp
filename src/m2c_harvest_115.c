/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"

extern s32 sub_080724B0(void);
extern void sub_08072414(void *);

void sub_080724D8(u8 *object);

void sub_080724D8(u8 *object) {
    u32 value;
    if (sub_080724B0() == 0) {
        value = object[0x5D];
        /* The stored signed-byte result is tested through its high byte. */
        value=(*(s8*)(object+0x5F)=value);
        if ((value << 24) == 0) {
            sub_08072414(object);
            return;
        }
        object[0x61] = 4;
    }
}
