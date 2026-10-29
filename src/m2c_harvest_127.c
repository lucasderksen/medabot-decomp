/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "frame.h"
#include "gba.h"
#include "state0_work.h"

extern s32 gGraphicsTransferCounter;
extern const u8 gUnknown_084885C0[32];
extern const u8 gUnknown_084C7FF4[32];
extern const u8 gUnknown_084E4638[32];
extern s32 sub_080362C4(s32);
extern s32 sub_08036340(s32);
extern s32 sub_08036370(s32, u8);
extern s32 sub_080364A8(s32, u8);
extern const u8 gUnknown_08487D90[];
extern const u8 gUnknown_084C3E64[];
extern const u8 gUnknown_084C571C[];
extern const u8 gUnknown_084C7B64[];

void sub_0801E300(void);

void sub_0801E300(void) {
    s32 var_r5;u32 mask;
    u8 *work;u8 *selection;

    LeDecompress(gUnknown_084C571C, (void *)0x06006400);
    LeDecompress(gUnknown_08487D90, (void *)0x06006520);
    LeDecompress(gUnknown_084C3E64, (void *)0x06006600);
    LeDecompress(gUnknown_084C7B64, (void *)0x06006800);
    CpuFastSet(gUnknown_084885C0, (void *)0x05000140, 8U);
    CpuFastSet(gUnknown_084E4638, (void *)0x05000100, 8U);
    CpuFastSet(gUnknown_084C7FF4, (void *)0x05000160, 8U);
    work=gState0TransferWork.bytes;
    mask=2 & work[0xF8];
    var_r5=0;
    if(!mask) {
        var_r5 = 1;
    }
    sub_080362C4(var_r5);
    sub_08036340(var_r5);
    sub_08036370(var_r5, work[0x88]);
    sub_080364A8(var_r5, work[0x88]);
    work[0xAA] = (u8) (work[0xAA] + 1);
}
