/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_work.h"


s32 sub_080437E0(void);

s32 sub_080437E0(void) {

    u8 *work = gState0TypedWork.bytes;

    if (!(work[0x98] == work[0x99]))
        return 0;
    if (!(work[0x98] == work[0x9A]))
        return 0;
    if (!(work[0x98] == work[0x9B]))
        return 0;
    return 1;
}
