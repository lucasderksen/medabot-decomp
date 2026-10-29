/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "graphics.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "state0_work.h"
#include "utility_helpers.h"


void sub_08024538(void);

void sub_08024538(void) {

    /* Four frame copies use the transfer bank byte and whole frame-array root. */
    u32 count = 0;
    do {
        sub_0804422C(count+0x26);
        count++;
    } while (count <= 3);
    if (gState0TypedWork.bytes[0x84] == 0x10) {
        u32 sourceAddress;
        u8 *work;
        sub_08040CD0(0x26,4);
        sourceAddress=(u32)gFrameObjects+0x880;
        work=gState0TransferWork.bytes;
        { u8 *source=(u8 *)(sourceAddress+0x0); u32 bankOffset=work[0x88]<<8; u8 *destination=(u8 *)(sourceAddress+0xE00); sub_0803F63C(source,(u8 *)(bankOffset+(u32)destination),0x40); }
        { u8 *source=(u8 *)(sourceAddress+0x40); u32 bankOffset=work[0x88]<<8; u8 *destination=(u8 *)(sourceAddress+0xE40); sub_0803F63C(source,(u8 *)(bankOffset+(u32)destination),0x40); }
        { u8 *source=(u8 *)(sourceAddress+0x80); u32 bankOffset=work[0x88]<<8; u8 *destination=(u8 *)(sourceAddress+0xE80); sub_0803F63C(source,(u8 *)(bankOffset+(u32)destination),0x40); }
        { u8 *source=(u8 *)(sourceAddress+0xC0); u32 bankOffset=work[0x88]<<8; u8 *destination=(u8 *)(sourceAddress+0xEC0); sub_0803F63C(source,(u8 *)(bankOffset+(u32)destination),0x40); }
        sourceAddress+=(u32)-0x880; /* Defined unsigned GBA address arithmetic returns to frame root. */
        { u32 flagOffset=(work[0x88]<<8)+0x1680; u16 *flags=(u16 *)(flagOffset+sourceAddress); *flags|=0x8000; }
        { u32 flagOffset=(work[0x88]<<8)+0x16C0; u16 *flags=(u16 *)(flagOffset+sourceAddress); *flags|=0x8000; }
        { u32 flagOffset=(work[0x88]<<8)+0x1700; u16 *flags=(u16 *)(flagOffset+sourceAddress); *flags|=0x8000; }
        { u32 flagOffset=(work[0x88]<<8)+0x1740; u16 *flags=(u16 *)(flagOffset+sourceAddress); u16 value=*flags; value|=0x8000; *flags=value; }
        sub_08040CD0(0x21,4);
        work[0xAA]++;
    } else gState0TypedWork.bytes[0x84]++;
}
