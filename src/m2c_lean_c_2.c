/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "state0_work.h"


void sub_08049EE8(u8 *values, s16 left, s16 right);
void sub_08049FD0(u16 *values, s16 left, s16 right);
void sub_0804A0F0(u16 *values, s16 left, s16 right);

void sub_08049EE8(u8 *values, s16 left, s16 right) {

    s32 i;
    s32 j;
    u8 swap;

    if (left < right) {
        i = left + 1;
        j = right;
        while (i <= j) {
            for (; i <= j && values[i] <= values[left]; i++);
            for (; i <= j && values[j] >= values[left]; j--);
            if (i >= j)
                break;
            swap = values[j];
            values[j] = values[i];
            values[i] = swap;
            i++;
            j--;
        }
        swap = values[j];
        values[j] = values[left];
        values[left] = swap;
        sub_08049EE8(values, left, j - 1);
        sub_08049EE8(values, j + 1, right);
    }
}

void sub_08049FD0(u16 *values, s16 left, s16 right) {

    s32 i;
    s32 j;
    u16 swap;

    if (left < right) {
        i = left + 1;
        j = right;
        while (i <= j) {
            for (; i <= j && (values[i] & 0xFF) < (values[left] & 0xFF); i++);
            for (; i <= j && (values[j] & 0xFF) > (values[left] & 0xFF); j--);
            if (i >= j)
                break;
            swap = values[j];
            values[j] = values[i];
            values[i] = swap;
            i++;
            j--;
        }
        swap = values[j];
        values[j] = values[left];
        values[left] = swap;
        sub_08049FD0(values, left, j - 1);
        sub_08049FD0(values, j + 1, right);
    }
}

void sub_0804A0F0(u16 *values, s16 left, s16 right) {

    s32 i;
    s32 j;
    u16 swap;

    if (left < right) {
        i = left + 1;
        j = right;
        while (i <= j) {
            for (; i <= j && (values[i] & 0xFF) > (values[left] & 0xFF); i++);
            for (; i <= j && (values[j] & 0xFF) < (values[left] & 0xFF); j--);
            if (i >= j)
                break;
            swap = values[j];
            values[j] = values[i];
            values[i] = swap;
            i++;
            j--;
        }
        swap = values[j];
        values[j] = values[left];
        values[left] = swap;
        sub_0804A0F0(values, left, j - 1);
        sub_0804A0F0(values, j + 1, right);
    }
}
