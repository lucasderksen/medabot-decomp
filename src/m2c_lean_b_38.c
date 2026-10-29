/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "main.h"
#include "record_helpers.h"
#include "sound_voice.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Limits6C694 { s32 value[3]; };
struct BattleView6C694 { u8 pad00[8]; s32 word08; s8 byte0C; u8 byte0D; u8 byte0E; u8 pad0F[0x32]; u8 byte41; };
struct DmaRegs6C694 { u32 source, destination, control; };

extern const struct Limits6C694 gUnknown_080B00AC;
extern const u8 gRandomBytes_083F7D80[];
extern struct BattleView6C694 gBattleView6C694 asm("gCounter6ED08_03001800");
extern void sub_0806D3EC(void);

void sub_0806C694(void);

void sub_0806C694(void) {

    struct Limits6C694 limits = gUnknown_080B00AC;
    s32 i;
    volatile u16 fill;

    if (gFrameObjects[0x1E].unknown1A <= 0x4F) {
        if (gFrameObjects[0x1E].unknown1A <= limits.value[gFrameObjects[0x1E].commandDelay - 1]
            && !(gFrameObjects[0x1E].unknown1A & 7)) {
            for (i = 0; i <= 7; i++) {
                if (gFrameObjects[0x28 + i].commandDelay == 0) {
                    gFrameObjects[0x28 + i].commandDelay = 3;
                    gFrameObjects[0x28 + i].screenX = (0x3F & gRandomBytes_083F7D80[(gFrameCounter + i) & 0xFF]) + 0x58;
                    gFrameObjects[0x28 + i].screenY = 0x90;
                    gFrameObjects[0x28 + i].unknown1A = 0;
                    if (gFrameObjects[0x1E].unknown1A % 16 == 0)
                        sub_08074DE0(0x3B);
                    break;
                }
            }
        }
        if (gFrameObjects[0x1E].commandStopped != 0)
            gFrameObjects[0x1E].screenX += 2;
        else
            gFrameObjects[0x1E].screenX -= 2;
        gFrameObjects[0x1E].screenY -= 2;
        gFrameObjects[0x1E].unknown1A++;
        return;
    }
    gFrameObjects[0x1E].commandDelay--;
    sub_0806D3EC();
    if (gFrameObjects[0x1E].commandDelay != 0) {
        gUnknown_0300137C = 3;
        gFrameObjects[0].commandDelay = 3;
        gFrameObjects[0x1E].commandOffset = 0;
        gFrameObjects[0x1E].frameAndGroup = 0;
        gFrameObjects[0x1E].angle = 0;
        gFrameObjects[0x1E].screenX = 0x78;
        gFrameObjects[0x1E].screenY = 0x80;
        gFrameObjects[0x1E].scaleX = 0x40;
        gFrameObjects[0x1E].scaleY = 0x40;
        gFrameObjects[0x1E].commandStopped = 0;
        gBattleView6C694.byte41 = 0;
        gFrameObjects[0x20].frameAndGroup = 7;
        gFrameObjects[0x20].screenX = 0x78;
        gFrameObjects[0x20].screenY = 0x10;
        gFrameObjects[0x20].unknown1A = 0;
        fill = 0;
        {
            volatile struct DmaRegs6C694 *dma = (void *)0x040000D4;
            dma->source = (u32)&fill;
            dma->destination = (u32)&gFrameObjects[0x20].commandDelay;
            dma->control = 0x81000008;
            (void)dma->control;
        }
        gBattleView6C694.byte0C = gBattleView6C694.byte0E + 10;
        if (gBattleView6C694.byte0C > 0x32)
            gBattleView6C694.byte0C = 0x32;
        gBattleView6C694.byte0D += 4;
        gBattleView6C694.word08 = 0;
        return;
    }
    sub_08074B88(0);
    sub_08074B88(0xF);
    gUnknown_0300137C = 7;
    gBattleView6C694.word08 = 0;
}
