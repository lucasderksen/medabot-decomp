/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

struct Part19B40 { u8 unknown00[0x11]; u8 byte11; u8 unknown12[6]; };
struct SetupParts19B40 { u8 unknown00[0x48]; struct Part19B40 parts[4]; u8 unknownA8[0x58]; };
struct Setup19B40 { u8 unknown00[0xDF]; u8 kindDF; u8 unknownE0[0x20]; };

extern const u8 *gState0NextCommands_083B6100[];
extern const u8 gUnknown_083C4DF8[];
extern const u8 gUnknown_083C4DFC[];
extern const u8 gUnknown_083C4E00[];
extern const u8 gUnknown_083C4E04[];
extern const u8 gUnknown_083C4E20[];
extern struct Setup19B40 gSetup19B40[] asm("gSetupBuffer_03000590");
extern struct SetupParts19B40 gSetupParts19B40[] asm("gSetupBuffer_03000590");
extern u16 gUnknown_083AF600[];
extern u16 gUnknown_083AF610[];
extern void sub_08019D9C(u32 index, u32 slot, u32 mode, u32 priority);

void sub_08019B40(u32 arg0);
void sub_08036784(s32 start, s32 path, u16 x, u16 y);

void sub_08019B40(u32 arg0) {

    u32 sbase = (u32)gSetupParts19B40;
    u8 *record = (u8 *)(sbase + (arg0 << 8));
    u32 root;
    u32 slot;
    struct FrameObject *object;

    if (8 & record[0xBD]) {
        do {
        if (gSetupParts19B40[arg0].parts[record[0xDE] - 1].byte11 == 0) {
            sub_08040D0C(arg0 * 3 + 0x48, 1);
            return;
        }
        } while (0);
        root = (u32)gFrameObjects;
        slot = arg0 * 3 + 0x48;
        object = (struct FrameObject *)(root + (slot << 6));
        if (object->flags != 0 && object->unknown23[0] == record[0xDF]) {
            switch (record[0xDF]) {
            case 0x1B:
                sub_08040BD8(gState0NextCommands_083B6100[12], slot);
                break;
            case 0x1C:
                sub_08040BD8(gState0NextCommands_083B6100[13], slot);
                break;
            case 0x1D:
                sub_08040BD8(gState0NextCommands_083B6100[14], slot);
                break;
            default:
                sub_08040BD8(gState0NextCommands_083B6100[11], arg0 * 3 + 0x48);
                break;
            }
        } else {
            switch (gSetup19B40[arg0].kindDF) {
            case 0x1B:
                do {
                sub_08040B90(gState0NextCommands_083B6100[12], arg0 * 3 + 0x48);
                break;
            case 0x1D:
                sub_08040B90(gState0NextCommands_083B6100[14], arg0 * 3 + 0x48);
                break;
            case 0x1C:
                sub_08040B90(gState0NextCommands_083B6100[13], arg0 * 3 + 0x48);
                } while (0);
                break;
            default:
                sub_08040B90(gState0NextCommands_083B6100[11], arg0 * 3 + 0x48);
                break;
            }
        }
        switch (gSetup19B40[arg0].kindDF) {
        case 0x1B:
            sub_08041D04(gUnknown_083C4DFC, gUnknown_0300052E, 4);
            break;
        case 0x1C:
            sub_08041D04(gUnknown_083C4E00, gUnknown_0300052E, 4);
            break;
        case 0x1D:
            sub_08041D04(gUnknown_083C4E04, gUnknown_0300052E, 4);
            break;
        default:
            sub_08041D04(gUnknown_083C4DF8, gUnknown_0300052E, 4);
            break;
        }
        sub_08019D9C(arg0, 2, 2, gFrameObjects[0x5D + arg0 * 4].priority + 4);
    } else if (0x10 & record[0xBD]) {
        do {
        if (gSetupParts19B40[arg0].parts[record[0xDE] - 1].byte11 == 0) {
            sub_08040D0C(arg0 * 3 + 0x48, 1);
            return;
        }
        } while (0);
        root = (u32)gFrameObjects;
        slot = arg0 * 3 + 0x48;
        object = (struct FrameObject *)(root + (slot << 6));
        if (object->flags != 0 && object->unknown23[0] == record[0xDF])
            sub_08040BD8(gState0NextCommands_083B6100[20], slot);
        else
            sub_08040B90(gState0NextCommands_083B6100[20], arg0 * 3 + 0x48);
        sub_08041D04(gUnknown_083C4E20, gUnknown_0300052E, 4);
        sub_08019D9C(arg0, 2, 2, gFrameObjects[0x5D + arg0 * 4].priority + 4);
    }
}

void sub_08036784(s32 start, s32 path, u16 x, u16 y) {

    u32 i;
    u32 k;

    sub_08040CD0(start, 4);
    for (i = 0; i <= 3; i++) {
        gFrameObjects[start + i].flags = 0x4404;
        gFrameObjects[start + i].tableSelector = 0;
        gFrameObjects[start + i].palette = 0xE;
        gFrameObjects[start + i].priority = 0x80;
        gFrameObjects[start + i].unknown2C[0] = i * 8;
        { s32 t = gUnknown_083AF600[k = path * 2]; t += (s16)x; gFrameObjects[start + i].screenX = (gUnknown_083AF610[i * 2] + t) & 0x1FF; }
        { s32 t = (s16)y; t += gUnknown_083AF600[k + 1]; gFrameObjects[start + i].screenY = (gUnknown_083AF610[i * 2 + 1] + t) & 0xFF; }
        sub_08040B90(gState0NextCommands_083B6100[29], start + i);
    }
}
