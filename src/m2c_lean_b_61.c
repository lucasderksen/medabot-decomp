/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bios_lz77.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "encounter_choices.h"
#include "encounter_parts.h"
#include "frame.h"
#include "frame_objects.h"
#include "graphics.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "main_menu_data.h"
#include "map_metadata.h"
#include "record_helpers.h"
#include "scene_view.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_inventory_view.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "text_glyphs.h"

struct PairAED0 { u16 name; u16 value; };
struct CtxAED0 { u8 unknown00[0x11]; u8 first; };

extern const void *const gFreshPointers_08483ED8[];
extern u32 sub_0805B5FC(u32 index);
extern void sub_0805A444(s32 value, s32 x, s32 y);
extern void sub_0805B530(u32 a, u32 b, u32 c);
extern void sub_0805B558(void);

void sub_0805AED0(void);

void sub_0805AED0(void) {

    u32 saved0, saved1;
    s32 count = 5;
    u8 names[count];
    u8 values[count];
    s8 i;
    struct PairAED0 *pairs;
    u16 *p;

    for (i = 0, pairs = (struct PairAED0 *)0x02040000; i < count; i++) {
        names[i] = pairs[((struct CtxAED0 *)gMainContextPointer_03006F74)->first + i].name;
        values[i] = pairs[((struct CtxAED0 *)gMainContextPointer_03006F74)->first + i].value;
    }
    for (i = 0; i < count; i++) {
        sub_08040D0C(i << 4, 0x10);
        sub_0805B530(0x18, i * 2 + 3, 3);
        sub_0805B530(0x18, i * 2 + 4, 3);
    }
    saved0 = *(u16 *)0x0600F0EE;
    saved1 = *(u16 *)0x0600F12E;
    for (i = 0; i < count; i++) {
        if (values[i] != 0) {
            sub_0803F63C(gFreshPointers_08483ED8[names[i]], gDebugMenuTextBuffer, 0x11);
            sub_08040DB8(gDebugMenuTextBuffer, (u8)(i * 15), 0xC, i * 2 + 3, 7, 8, 1, 2);
            sub_0805A444(values[i], 0x18, i * 2 + 3);
            *(u16 *)(((i * 2 + 3) << 6) + 0x0600F02E) = saved0;
            *(u16 *)(((i * 2 + 4) << 6) + 0x0600F02E) = saved1;
            gFrameObjects[i + 0x55].flags |= 0x4000;
            gFrameObjects[i + 0x55].frameAndGroup = sub_0805B5FC(names[i]) ? 0x21 : 0x22;
        } else {
            p = (u16 *)(((i * 2 + 3) << 6) + 0x0600F02E);
            *p = 0;
            p = (u16 *)(((i * 2 + 3) << 6) + 0x0600F030);
            *p = 0;
            p = (u16 *)(((i * 2 + 3) << 6) + 0x0600F032);
            *p = 0;
            p = (u16 *)(((i * 2 + 4) << 6) + 0x0600F02E);
            *p = 0;
            do {
                p = (u16 *)(((i * 2 + 4) << 6) + 0x0600F030);
                *p = 0;
                p = (u16 *)(((i * 2 + 4) << 6) + 0x0600F032);
                *p = 0;
            } while (0);
            gFrameObjects[i + 0x55].flags &= 0xBFFF;
        }
    }
    sub_0805B558();
}
