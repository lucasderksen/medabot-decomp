/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "continued_commands.h"
#include "continued_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "interrupts.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "render_work.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_work.h"
#include "tile_text.h"

struct BlendWorkA6C {
    u8 control;
    u8 type;
    u8 active;
    u8 byte3;
    u8 byte4;
    u8 byte5;
    u8 first;
    u8 second;
    u8 third;
    u8 currentFirst;
    u8 currentSecond;
    float valueFirst;
    float valueSecond;
    float elapsed;
    float stepFirst;
    float stepSecond;
    float stepElapsed;
};
struct Work2284 {
    u8 unknown000[0xC88];
    u8 active;
    u8 byteC89;
    u16 halfC8A;
    u8 unknownC8C[2];
    u16 valueC8E;
    u16 valueC90;
};
struct ContextF58 { u8 unknown00[0x36]; u16 tileBase; };

extern const u8 gUnknown_083D2A83[];
extern s8 gUnknown_03006494;
extern struct BlendWorkA6C gBlendSetupWork_03006F40;
extern struct Work2284 gWork2284 asm("gContinuedWork_030057E0");
extern u16 sub_0807CEC8(u16 value, s32 divisor);
extern u16 sub_0807CF40(u16 value, s32 divisor);
extern void DummyInterruptHandler(void);

u32 sub_08049A6C(void);
u32 sub_08052284(void);
void sub_08059F58(u32 numberArg, u32 widthArg, u32 xArg, u32 yArg, u32 paletteArg, u32 blockArg);

u32 sub_08049A6C(void) {

    u32 done;

    done = 0;
    if (gBlendSetupWork_03006F40.active == 2) {
        done = 1;
        gUnknownCallback_030017F0 = DummyInterruptHandler;
    } else if (gBlendSetupWork_03006F40.active == 1) {
        switch (gBlendSetupWork_03006F40.control) {
        case 0:
        case 0x40:
            break;
        case 0x80:
        case 0xC0:
            if (gBlendSetupWork_03006F40.elapsed < 256.0f)
                gBlendSetupWork_03006F40.elapsed += gBlendSetupWork_03006F40.stepElapsed;
            else
                gBlendSetupWork_03006F40.elapsed = 256.0f;
            if (gBlendSetupWork_03006F40.elapsed >= 256.0f)
                done = 1;
            break;
        }
        switch (gBlendSetupWork_03006F40.type) {
        case 0:
        case 2:
            gBlendSetupWork_03006F40.byte3 = gBlendSetupWork_03006F40.valueFirst * 0.0625f;
            gBlendSetupWork_03006F40.byte4 = gBlendSetupWork_03006F40.valueSecond * 0.0625f;
            gBlendSetupWork_03006F40.byte5 = gBlendSetupWork_03006F40.elapsed * 0.0625f;
            break;
        case 1:
        case 3:
            gBlendSetupWork_03006F40.byte3 = 16.0f - gBlendSetupWork_03006F40.valueFirst * 0.0625f;
            gBlendSetupWork_03006F40.byte4 = 16.0f - gBlendSetupWork_03006F40.valueSecond * 0.0625f;
            gBlendSetupWork_03006F40.byte5 = 16.0f - gBlendSetupWork_03006F40.elapsed * 0.0625f;
            break;
        case 4:
            gBlendSetupWork_03006F40.valueFirst += gBlendSetupWork_03006F40.stepFirst;
            gBlendSetupWork_03006F40.byte3 = (u8)gBlendSetupWork_03006F40.valueFirst + gBlendSetupWork_03006F40.first;
            if (gBlendSetupWork_03006F40.byte3 > 15) {
                gBlendSetupWork_03006F40.byte3 = 16;
                done = 1;
            }
            gBlendSetupWork_03006F40.valueSecond += gBlendSetupWork_03006F40.stepSecond;
            gBlendSetupWork_03006F40.byte4 = (u8)gBlendSetupWork_03006F40.valueSecond + gBlendSetupWork_03006F40.second;
            if (gBlendSetupWork_03006F40.byte4 > 15) {
                gBlendSetupWork_03006F40.byte4 = 16;
                done = 1;
            }
            break;
        case 5:
            gBlendSetupWork_03006F40.valueFirst += gBlendSetupWork_03006F40.stepFirst;
            gBlendSetupWork_03006F40.byte3 = 16 - (u8)gBlendSetupWork_03006F40.valueFirst;
            if (gBlendSetupWork_03006F40.byte3 <= gBlendSetupWork_03006F40.first) {
                gBlendSetupWork_03006F40.byte3 = gBlendSetupWork_03006F40.first;
                done = 1;
            }
            gBlendSetupWork_03006F40.valueSecond += gBlendSetupWork_03006F40.stepSecond;
            gBlendSetupWork_03006F40.byte4 = 16 - (u8)gBlendSetupWork_03006F40.valueSecond;
            if (gBlendSetupWork_03006F40.byte4 <= gBlendSetupWork_03006F40.second) {
                gBlendSetupWork_03006F40.byte4 = gBlendSetupWork_03006F40.second;
                done = 1;
            }
            break;
        case 6:
            gBlendSetupWork_03006F40.valueFirst += gBlendSetupWork_03006F40.stepFirst;
            gBlendSetupWork_03006F40.byte3 = gBlendSetupWork_03006F40.currentFirst - (u8)gBlendSetupWork_03006F40.valueFirst;
            if (gBlendSetupWork_03006F40.first != gBlendSetupWork_03006F40.currentFirst) {
                if (gBlendSetupWork_03006F40.byte3 >= gBlendSetupWork_03006F40.first) {
                    gBlendSetupWork_03006F40.byte3 = gBlendSetupWork_03006F40.first;
                    done = 1;
                }
            } else if (gBlendSetupWork_03006F40.byte3 <= gBlendSetupWork_03006F40.first) {
                gBlendSetupWork_03006F40.byte3 = gBlendSetupWork_03006F40.first;
                done = 1;
            }
            gBlendSetupWork_03006F40.valueSecond += gBlendSetupWork_03006F40.stepSecond;
            gBlendSetupWork_03006F40.byte4 = gBlendSetupWork_03006F40.currentSecond - (u8)gBlendSetupWork_03006F40.valueSecond;
            if (gBlendSetupWork_03006F40.second != gBlendSetupWork_03006F40.currentSecond) {
                if (gBlendSetupWork_03006F40.byte4 >= gBlendSetupWork_03006F40.second) {
                    gBlendSetupWork_03006F40.byte4 = gBlendSetupWork_03006F40.second;
                    done = 1;
                }
            } else if (gBlendSetupWork_03006F40.byte4 <= gBlendSetupWork_03006F40.second) {
                gBlendSetupWork_03006F40.byte4 = gBlendSetupWork_03006F40.second;
                done = 1;
            }
            break;
        }
    }
    gUnknownCallback_030017F0 = sub_08049CC8;
    if (done) {
        done = 0;
        gBlendSetupWork_03006F40.active = 2;
    }
    return done;
}

u32 sub_08052284(void) {

    struct SelectionRecord *record;
    s32 blocked;
    u32 x;
    u32 y;
    struct Work2284 *work;
    u32 found;
    s32 i;
    u16 value;
    u8 *later;

    record = gSelectionRecords_03005DBC;
    blocked = 0;
    x = ((u8 *)gSelectionRecords_03005DBC)[0x67A];
    y = ((u8 *)gSelectionRecords_03005DBC)[0x67B];
    switch (gFrameObjects[0x2F].commandDelay) {
    case 0:
        if ((u8)y != 0)
            y--;
        else
            blocked = 1;
        break;
    case 1:
        if (y != (*(u16 *)((u8 *)gSelectionRecords_03005DBC + 0x226) >> 1) - 1)
            y++;
        else
            blocked = 1;
        break;
    case 2:
        if ((u8)x != 0)
            x--;
        else
            blocked = 1;
        break;
    case 3:
        if (x == (*(u16 *)((u8 *)gSelectionRecords_03005DBC + 0x224) >> 1) - 1)
            blocked = 1;
        else
            x++;
        break;
    }
    if (blocked == 1)
        return 0;
    found = 0;
    for (i = 0, work = &gWork2284; i <= 0x3F; i++) {
        if (record->x == x && record->y == y) {
            switch ((record->attributes & 0xF000) >> 12) {
            case 0:
            case 4:
            case 6:
                work->active = 1;
                work->valueC90 = work->valueC8E = record->attributes & 0xFFF;
                work->byteC89 = 0;
                work->halfC8A = 0;
                gUnknown_03006494 = i;
                gFrameObjects[0x2F].unknown23[2] = 1;
                found = 1;
                break;
            }
            if ((record->attributes & 0xF000) == 0) {
                later = gLaterBuffer_03003810;
                sub_0805218C((u8)(record->flags.bits.index + 0x31), gUnknown_083D2A83[later[0]], record);
            }
        }
        record++;
        if (found == 1)
            break;
    }
    return found;
}

void sub_08059F58(u32 numberArg, u32 widthArg, u32 xArg, u32 yArg, u32 paletteArg, u32 blockArg) {

    u16 number = numberArg;
    s8 width = widthArg;
    u8 x = xArg;
    u8 y = yArg;
    u8 palette = paletteArg;
    u8 block = blockArg;
    u16 digits[5];
    u16 tile;
    u16 *dst;
    s32 i;

    tile = ((struct ContextF58 *)gMainContextPointer_03006F74)->tileBase + 0x16;
    if (width != 0) {
        if (width > 0) {
            dst = ((u16 *)((block << 11) + 0x06000000) + (x + width - 1)) + (y << 5);
            for (i = 0; i < width; i++) {
                if (i != 0 && number == 0) {
                    *dst = palette << 12;
                    dst--;
                } else {
                    *dst = (sub_0807CF40(number, 10) + tile) | (palette << 12);
                    dst--;
                    number = sub_0807CEC8(number, 10);
                }
            }
        } else {
            s8 count = -width;
            dst = ((u16 *)((block << 11) + 0x06000000) + (x + count - 1)) + (y << 5);
            for (i = 0; i < count; i++) {
                if (i != 0 && number == 0) {
                    *dst = tile | (palette << 12);
                    dst--;
                } else {
                    *dst = (sub_0807CF40(number, 10) + tile) | (palette << 12);
                    dst--;
                    number = sub_0807CEC8(number, 10);
                }
            }
        }
    } else {
        dst = ((u16 *)((block << 11) + 0x06000000) + x) + (y << 5);
        for (i = 0; i <= 4; i++) {
            digits[i] = sub_0807CF40(number, 10);
            if (number == 0 && i != 0)
                break;
            number = sub_0807CEC8(number, 10);
        }
        for (i--; i >= 0; i--)
            *dst++ = (digits[i] + tile) | (palette << 12);
    }
}
