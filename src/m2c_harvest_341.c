/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_blend_work.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "graphics.h"
#include "record_helpers.h"
#include "state0_work.h"

struct ContinuedPart263BC {u8 unknown;u8 label;u8 gap2[4];u8 increment;u8 tail[0x11];};
struct ContinuedSetup263BC {u8 prefix[0x48];struct ContinuedPart263BC parts[4];u8 gapA8[0x15];u8 flags;u8 gapBE[0x1A];u16 value;u8 gapDA[5];u8 label;u8 tail[0x20];};

extern void sub_08035740(u8 *,s32,u32);

void sub_080263BC(void);

void sub_080263BC(void) {

    struct ContinuedSetup263BC *setup;
    u8 *work;
    u32 zero;
    u32 bankOffset,helperBankOffset;
    u32 flags,mask;
    u8 *flagCursor;
    sub_08040CD0(0x21,1);
    setup=(struct ContinuedSetup263BC *)gSetupBuffer_03000590;
    work=gState0TransferWork.bytes;
    flagCursor=(u8 *)&setup[work[0x87]].flags;
    flags = *flagCursor;
    mask = 0x10;
    zero = 0;
    mask |= flags;
    *flagCursor = mask;
    bankOffset=work[0x87]<<8;
    setup[work[0x87]].label=*(u8 *)((work[0xA7]*0x18)+bankOffset+(u32)setup+0x49);
    setup[work[0x87]].value=zero;
    /* Unsigned word subtraction preserves the original GBA address wrap. */
    helperBankOffset=work[0x87]<<8;
    sub_08035740((u8 *)((u32)setup-(0U-helperBankOffset)+0xD8),*(u8 *)((work[0xA7]*0x18)+helperBankOffset+(u32)setup+0x4E),0xFF);
    work[0xAA]++;
}
