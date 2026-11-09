/*
 * sub_0804842C: not matching yet. The build assembles asm/non_matching/sub_0804842C.inc
 * in its place; the C below is the closest attempt (600 B, 5 rows: the reference
 * compares a copy of the case-3 byte, `adds r1, r2, #0; cmp r1, #0xff`, and the
 * path-1 0xC31 reload then uses r2 instead of r6).
 */

#include "global.h"
#include "fresh_helpers.h"
#include "post_dispatch.h"
#include "scene_setup_data.h"

extern u8 gFreshWork_03006D38[];
extern u8 gContinuedWork_030057E0[];

NONMATCH("asm/non_matching/sub_0804842C.inc", u32 sub_0804842C(u32 first, u32 second))
{
    /* Falls off the end like the reference (r0 keeps first or the last call result); no caller uses it: sub_0804A6A0, sub_0804A6F8, sub_0804A764, sub_0804A944, sub_0804AA74, sub_0804AB60, sub_0804ABCC, sub_0804ACD4, sub_0804AE80, sub_0804C960, sub_0804C984, sub_0804C9A0, sub_0804C9C4, sub_08050CCC, sub_0805424C */
    u32 v;
    u32 value;

    switch (first) {
    case 0:
    case 10:
    case 12: {
        u8 *work = gContinuedWork_030057E0;
        if (work[0xC30] == 0xFF)
            break;
        value = sub_080483F8();
        if (work[0xC30] == value)
            break;
        work[0xC30] = value;
        sub_08047BB4(value);
        break;
    }
    case 1: {
        u8 *work = gContinuedWork_030057E0;
        work[0xC30] = second;
        sub_08047BB4(second);
        break;
    }
    case 2: {
        u8 *work = gContinuedWork_030057E0;
        work[0xC30] = 0;
        sub_08047BB4(0);
        break;
    }
    case 3: {
        u8 *work = gContinuedWork_030057E0;
        u8 *p = &work[0xC30];
        value = *p;
        if (value != 0xFF) {
            if (!(0x80 & second)) {
                FORCE_REGISTER(u32 c, r1) = 0x7F; /* FAKE MATCH: the reference reloads 0x7F into r1 instead of tying it to the result */
                FORCE_REGISTER(u32 m, r0) = second; /* FAKE MATCH: masked copy of second in r0 */
                m &= c;
                work[0xC31] = m;
                sub_08047BB4(second);
                *p = 0xFF;
                break;
            }
        } else if (!(0x80 & second))
            break;
        {
            FORCE_REGISTER(u32 c, r1) = 0x7F; /* FAKE MATCH: 0x7F reloaded into r1 as in the reference */
            second &= c;
        }
        work[0xC31] = second;
        {
            FORCE_REGISTER(u32 x, r1) = 0xFF; /* FAKE MATCH: keeps the reference's 0xFF | old (combine folds it to 0xFF otherwise) */
            x |= value;
            *p = x;
        }
        break;
    }
    case 4: {
        u8 *work = gContinuedWork_030057E0;
        u8 old = work[0xC30];
        work[0xC30] = 0;
        value = sub_080483F8();
        if (old != value) {
            work[0xC30] = value;
            sub_08047BB4(value);
        } else
            work[0xC30] = value;
        break;
    }
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 19:
    case 28: {
        u8 *work;
        value = sub_080483F8();
        work = gContinuedWork_030057E0;
        work[0xC30] = value;
        sub_08047BB4(value);
        break;
    }
    case 11:
    case 13:
    case 14:
    case 15:
    case 21:
    case 22:
    case 26: {
        u8 *work = gContinuedWork_030057E0;
        if (work[0xC30] != 0xFF) {
            value = sub_080483F8();
            work[0xC30] = value;
            sub_08047BB4(value);
        } else
            sub_08047BB4(work[0xC31]);
        break;
    }
    case 23:
        if (gSceneTransitionChoices_083D2B36[gFreshWork_03006D38[1] * 4] != 0)
            sub_08047BC0(0x1E);
        break;
    case 24:
        if (gSceneTransitionChoices_083D2B36[gFreshWork_03006D38[1] * 4] != 0) {
            u8 *work;
            v = gSceneTransitionChoices_083D2B36[gFreshWork_03006D38[1] * 4 + 1];
            work = gContinuedWork_030057E0;
            work[0xC30] = v;
            sub_08047BB4(v);
        }
        break;
    case 25:
        switch (gSceneTransitionChoices_083D2B36[gFreshWork_03006D38[1] * 4 + 2]) {
        case 1: {
            u8 *work;
            v = gSceneTransitionChoices_083D2B36[gFreshWork_03006D38[1] * 4 + 3];
            work = gContinuedWork_030057E0;
            work[0xC30] = v;
            sub_08047BB4(v);
            break;
        }
        case 2: {
            u8 *work;
            v = sub_080483F8();
            work = gContinuedWork_030057E0;
            work[0xC30] = v;
            sub_08047BB4(v);
            break;
        }
        }
        break;
    }
}
END_NONMATCH
