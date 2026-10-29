/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct LeanCounterBonus { u8 unknown00[0x16C]; u16 bonus16C; };
struct LeanSetupSide { u8 bytes[0x100]; };

extern struct LeanCounterBonus gCounter6ED08_03001800;

void sub_0801264C(void);

void sub_0801264C(void) {

    u32 enemyTotal = 0;
    u32 allyTotal = 0;
    u32 i;
    u32 enemyCount;
    u32 allyCount;

    {
        struct LeanSetupSide *sides;
        i = 0;
        enemyCount = 0;
        sides = (struct LeanSetupSide *)gSetupBuffer_03000590;
        for (; i <= 2; i++) {
            if (sides[i + 3].bytes[0xBA]) {
                enemyTotal += sides[i + 3].bytes[5];
                enemyCount++;
            }
        }
    }
    enemyTotal = sub_0807CEC8(enemyTotal, enemyCount);
    {
        struct LeanSetupSide *sides;
        i = 0;
        allyCount = 0;
        sides = (struct LeanSetupSide *)gSetupBuffer_03000590;
        for (; i <= 2; i++) {
            if (sides[i].bytes[0xBA]) {
                allyTotal += sides[i].bytes[5];
                allyCount++;
            }
        }
    }
    allyTotal = sub_0807CEC8(allyTotal, allyCount);
    if (allyTotal < enemyTotal)
        gCounter6ED08_03001800.bonus16C += (enemyTotal - allyTotal) * (enemyCount << 4);
}
