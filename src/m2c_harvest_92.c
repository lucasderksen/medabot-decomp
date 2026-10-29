/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "sound_work.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "state0_callbacks.h"

struct NestedContext { u8 prefix[0x730]; u16 counter; };

extern void sub_08074118(void *);

void sub_08074090(void);
void sub_08074B88(u32 value);

void sub_08074090(void) {
    {
        struct NestedContext *work = *(struct NestedContext **) 0x03007014;
        u32 old = work->counter;
        if (old <= 0xFFFE)
            work->counter = old + 1;
    }
    sub_08074118((u8 *) (*(struct NestedContext **) 0x03007014) + 0x690);
    {
        struct NestedContext *work = *(struct NestedContext **) 0x03007014;
        u32 old = work->counter;
        if (old != 0)
            work->counter = old - 1;
    }
}

void sub_08074B88(u32 value) {
    {
        struct NestedContext *work = *(struct NestedContext **) 0x03007014;
        u32 old = work->counter;
        if (old <= 0xFFFE)
            work->counter = old + 1;
    }
    sub_08074A8C(value, 0);
    {
        struct NestedContext *work = *(struct NestedContext **) 0x03007014;
        u32 old = work->counter;
        if (old != 0)
            work->counter = old - 1;
    }
}
