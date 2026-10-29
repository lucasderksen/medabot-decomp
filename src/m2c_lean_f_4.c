/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sprite_layouts.h"
#include "state0_work.h"


void sub_080423A0(u8 count);
void sub_0804242C(u8 count);

void sub_080423A0(u8 count) {

    u32 j;
    u16 key, tie, word4, word6;

    if (count > 1)
    {
        for (count--; count != 0; count--)
        {
            for (j = 0; j < count; j++)
            {
                if (OBJECT_SORT_ENTRIES[j].key > OBJECT_SORT_ENTRIES[j + 1].key)
                {
                    key = OBJECT_SORT_ENTRIES[j].key;
                    tie = OBJECT_SORT_ENTRIES[j].tie;
                    word4 = OBJECT_SORT_ENTRIES[j].word4;
                    word6 = OBJECT_SORT_ENTRIES[j].word6;
                    OBJECT_SORT_ENTRIES[j].key = OBJECT_SORT_ENTRIES[j + 1].key;
                    OBJECT_SORT_ENTRIES[j].tie = OBJECT_SORT_ENTRIES[j + 1].tie;
                    OBJECT_SORT_ENTRIES[j].word4 = OBJECT_SORT_ENTRIES[j + 1].word4;
                    OBJECT_SORT_ENTRIES[j].word6 = OBJECT_SORT_ENTRIES[j + 1].word6;
                    OBJECT_SORT_ENTRIES[j + 1].key = key;
                    OBJECT_SORT_ENTRIES[j + 1].tie = tie;
                    OBJECT_SORT_ENTRIES[j + 1].word4 = word4;
                    OBJECT_SORT_ENTRIES[j + 1].word6 = word6;
                }
                else if (OBJECT_SORT_ENTRIES[j].key == OBJECT_SORT_ENTRIES[j + 1].key && OBJECT_SORT_ENTRIES[j].tie > OBJECT_SORT_ENTRIES[j + 1].tie)
                {
                    key = OBJECT_SORT_ENTRIES[j].key;
                    tie = OBJECT_SORT_ENTRIES[j].tie;
                    word4 = OBJECT_SORT_ENTRIES[j].word4;
                    word6 = OBJECT_SORT_ENTRIES[j].word6;
                    OBJECT_SORT_ENTRIES[j].key = OBJECT_SORT_ENTRIES[j + 1].key;
                    OBJECT_SORT_ENTRIES[j].tie = OBJECT_SORT_ENTRIES[j + 1].tie;
                    OBJECT_SORT_ENTRIES[j].word4 = OBJECT_SORT_ENTRIES[j + 1].word4;
                    OBJECT_SORT_ENTRIES[j].word6 = OBJECT_SORT_ENTRIES[j + 1].word6;
                    OBJECT_SORT_ENTRIES[j + 1].key = key;
                    OBJECT_SORT_ENTRIES[j + 1].tie = tie;
                    OBJECT_SORT_ENTRIES[j + 1].word4 = word4;
                    OBJECT_SORT_ENTRIES[j + 1].word6 = word6;
                }
            }
        }
    }
}

void sub_0804242C(u8 count) {

    u32 j;
    u16 key, tie, word4, word6;

    if (count > 1)
    {
        for (count--; count != 0; count--)
        {
            for (j = 0; j < count; j++)
            {
                if (OBJECT_SORT_ENTRIES[j].key < OBJECT_SORT_ENTRIES[j + 1].key)
                {
                    key = OBJECT_SORT_ENTRIES[j].key;
                    tie = OBJECT_SORT_ENTRIES[j].tie;
                    word4 = OBJECT_SORT_ENTRIES[j].word4;
                    word6 = OBJECT_SORT_ENTRIES[j].word6;
                    OBJECT_SORT_ENTRIES[j].key = OBJECT_SORT_ENTRIES[j + 1].key;
                    OBJECT_SORT_ENTRIES[j].tie = OBJECT_SORT_ENTRIES[j + 1].tie;
                    OBJECT_SORT_ENTRIES[j].word4 = OBJECT_SORT_ENTRIES[j + 1].word4;
                    OBJECT_SORT_ENTRIES[j].word6 = OBJECT_SORT_ENTRIES[j + 1].word6;
                    OBJECT_SORT_ENTRIES[j + 1].key = key;
                    OBJECT_SORT_ENTRIES[j + 1].tie = tie;
                    OBJECT_SORT_ENTRIES[j + 1].word4 = word4;
                    OBJECT_SORT_ENTRIES[j + 1].word6 = word6;
                }
                else if (OBJECT_SORT_ENTRIES[j].key == OBJECT_SORT_ENTRIES[j + 1].key && OBJECT_SORT_ENTRIES[j].tie < OBJECT_SORT_ENTRIES[j + 1].tie)
                {
                    key = OBJECT_SORT_ENTRIES[j].key;
                    tie = OBJECT_SORT_ENTRIES[j].tie;
                    word4 = OBJECT_SORT_ENTRIES[j].word4;
                    word6 = OBJECT_SORT_ENTRIES[j].word6;
                    OBJECT_SORT_ENTRIES[j].key = OBJECT_SORT_ENTRIES[j + 1].key;
                    OBJECT_SORT_ENTRIES[j].tie = OBJECT_SORT_ENTRIES[j + 1].tie;
                    OBJECT_SORT_ENTRIES[j].word4 = OBJECT_SORT_ENTRIES[j + 1].word4;
                    OBJECT_SORT_ENTRIES[j].word6 = OBJECT_SORT_ENTRIES[j + 1].word6;
                    OBJECT_SORT_ENTRIES[j + 1].key = key;
                    OBJECT_SORT_ENTRIES[j + 1].tie = tie;
                    OBJECT_SORT_ENTRIES[j + 1].word4 = word4;
                    OBJECT_SORT_ENTRIES[j + 1].word6 = word6;
                }
            }
        }
    }
}
