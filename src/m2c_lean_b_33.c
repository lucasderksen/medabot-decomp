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
#include "continued_blend_work.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "encounter_parts.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_command_handlers.h"
#include "link_menu.h"
#include "main.h"
#include "main_callbacks.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "rom_libc.h"
#include "sound_samples.h"
#include "sound_voice.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

struct Spark67C04
{
    u16 flags;
    s16 screenX;
    s16 screenY;
    u16 frame;
    u8 scaleX;
    u8 scaleY;
    u8 palette;
    u8 priority;
    s32 velocityX:8;
    s32 x:24;
    s32 velocityY:8;
    s32 y:24;
    u8 unknown14[6];
    u16 timer;
    u8 unknown1C[0x24];
};

extern const u8 gUnknown_0848576D[];
extern s32 gUnknown_03006FF8[2];
extern s32 gUnknown_03007000[2];
extern u32 sub_0807CEC8(u32 value, u32 divisor);
extern u32 sub_0807CF40(u32 value, u32 divisor);
extern u8 gEncounterFrameSlotsView[3][3] asm("gEncounterFrameSlots");
extern u8 gFamilyKeyBytes49558_0300058C;
extern u8 gSelectionOrder03006F94[3];
extern u8 gUnknown_03006F84;
extern u8 gUnknown_03006F8C[3];
extern u8 gUnknown_03006FA0[3][4][3];
extern u8 gUnknown_03006FEC[3];
extern u8 gUnknown_03006FF0[3];
extern void *memcpy(void *, const void *, unsigned long);
extern void sub_080697B4(u8, u8, u8);

void sub_08067C04(void);
void sub_08069B38(u8 slot, u8 mode);
void sub_08069BFC(u8 slot, u16 x, u16 y, u8 mode, u8 increment);
void sub_0806A748(void);
void sub_0806A860(void);
void sub_0806ADB0(void);
void sub_0806B01C(void);

void sub_08067C04(void) {

  s32 i;
  for (i = 0; i <= 15; i++)
  {
    u32 root = (u32) gFrameObjects;
    struct Spark67C04 *object;
    object = (struct Spark67C04 *) (root + ((i + 1) << 6));
    if (object->timer == 0)
    {
      object->screenX = 0x78;
      object->screenY = 0x28;
      object->x = object->screenX << 8;
      object->y = object->screenY << 8;
      object->velocityX = sub_080424B8();
      object->velocityY = sub_080424B8();
      object->timer = 0x3F;
      object->scaleX = 0;
      object->scaleY = 0;
      object->flags &= ~8;
    }
    else
    {
      object->timer--;
      if (object->timer <= 0xF)
      {
        object->flags |= 8;
      }
      object->x += object->velocityX * 4;
      object->y += object->velocityY * 4;
      object->screenX = object->x >> 8;
      object->screenY = object->y >> 8;
      {
        s32 scale = 0x40 - ((u8) object->timer);
        object->scaleX = scale;
        object->scaleY = scale;
      }
    }
  }
  *((volatile u16 *) 0x04000050) = 0xC40;
  *((volatile u16 *) 0x04000052) = (0xF & ((*(((u8 *) gMainContextPointer_03006F74) + 0x48))--)) | 0x1000;
  *((volatile u16 *) 0x04000054) = 8;
}

void sub_08069B38(u8 slot, u8 mode) {

    s32 three = 3;
    u8 row = sub_0807CEC8(slot, 3);
    u8 column = sub_0807CF40(slot, 3);
    u8 rowY[3];

    memcpy(rowY, gEncounterRowY, 3);
    sub_0804305C(gUnknown_03006FA0[row][0][column], gUnknown_03006FA0[row][1][column], gUnknown_03006FA0[row][2][column],
                 gUnknown_03006FA0[row][3][column], row * 3 + 2 - column, gEncounterFrameSlotsView[row][column] - 3,
                 gFrameObjects[gEncounterFrameSlotsView[row][column]].screenX, rowY[row], mode, three, 5);
}

void sub_08069BFC(u8 slot, u16 x, u16 y, u8 mode, u8 increment) {

    u8 row = sub_0807CEC8(slot, 3);
    u8 column = sub_0807CF40(slot, 3);

    sub_08042E58(gUnknown_03006FA0[row][0][column], gUnknown_03006FA0[row][1][column], gUnknown_03006FA0[row][2][column],
                 gUnknown_03006FA0[row][3][column], row * 3 + 2 - column, gEncounterFrameSlotsView[row][column] - 3,
                 (s16)x, (s16)y, mode, 3, 5);
    sub_08043240(gEncounterFrameSlotsView[row][column] - 3, increment);
}

void sub_0806A748(void) {

    s32 i, j;
    s32 rank;

    for (i = 0; i <= 2; i++) {
        if (gUnknown_03006F8C[i] > 2) {
            if (gSelectionOrder03006F94[0] == i + 1)
                sub_080697B4(5, i * 10 + 5, 0xF);
            else if (gSelectionOrder03006F94[1] == i + 1)
                sub_080697B4(6, i * 10 + 5, 0xF);
            else if (gSelectionOrder03006F94[2] == i + 1)
                sub_080697B4(7, i * 10 + 5, 0xF);
        } else {
            for (j = 0, rank = 5; j <= 2; j++) {
                if (i != j) {
                    if (gUnknown_03006F8C[i] < gUnknown_03006F8C[j]) {
                        rank++;
                    } else if (gUnknown_03006F8C[i] == gUnknown_03006F8C[j]) {
                        if (gFrameObjects[gEncounterFrameSlots[i][gUnknown_03006F8C[i]]].unknown1A == gFrameObjects[gEncounterFrameSlots[j][gUnknown_03006F8C[j]]].unknown1A) {
                            if (j < i)
                                rank++;
                        } else if (gFrameObjects[gEncounterFrameSlots[i][gUnknown_03006F8C[i]]].unknown1A < gFrameObjects[gEncounterFrameSlots[j][gUnknown_03006F8C[j]]].unknown1A) {
                            rank++;
                        }
                    }
                }
            }
            sub_080697B4(rank, i * 10 + 5, 0xF);
        }
    }
}

void sub_0806A860(void) {

    s32 i;

    if (gUnknown_03006F8C[0] <= 2 && (1 & gFamilyKeyBytes49558_0300058C)) {
        gUnknown_03006FEC[0] -= 4;
        if (gUnknown_03006FEC[0] <= 3)
            gUnknown_03006FEC[0] = 4;
        gFrameObjects[gEncounterFrameSlots[0][gUnknown_03006F8C[0]]].unknown1A += 3;
    }
    for (i = 1; i <= 2; i++) {
        if (gUnknown_03006F8C[i] <= 2) {
            if (((gScrollOscillationSines_083D6A2C[(gUnknown_0848576D[gUnknown_03006F84 + (i - 1) * 11] + gUnknown_03007000[i - 1]) & 0xFF] >> 5) & 7) + 6
                <= ++gUnknown_03006FF8[i - 1]) {
                if ((u8)(gUnknown_03006FEC[i] -= 4) <= 3)
                    gUnknown_03006FEC[i] = 4;
                gFrameObjects[gEncounterFrameSlots[i][gUnknown_03006F8C[i]]].unknown1A += 3;
                gUnknown_03006FF8[i - 1] = 0;
                gUnknown_03007000[i - 1]++;
            }
        }
    }
    for (i = 0; i <= 2; i++) {
        if (gUnknown_03006F8C[i] <= 2) {
            if (gUnknown_03006FEC[i] == 0x20) {
                sub_0806B530(i + 1, 10, i, 0);
                gUnknown_03006FF0[i] = 0;
            } else if (gUnknown_03006FEC[i] <= gUnknown_03006FF0[i]) {
                gFrameObjects[i + 1].unknown23[4] += 2;
                gUnknown_03006FF0[i] = 0;
            } else {
                gUnknown_03006FF0[i]++;
            }
        }
    }
    if (!(gFrameCounter & 7)) {
        for (i = 0; i < 3; i++) {
            if ((u8)(gUnknown_03006FEC[i] += 2) > 0x20)
                gUnknown_03006FEC[i] = 0x20;
        }
    }
}

void sub_0806ADB0(void) {

    s32 i;

    for (i = 0; i <= 2; i++) {
        if (gUnknown_03006F8C[i] <= 1) {
            if (gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1]].unknown23[7] == 1) {
                sub_080432A0(gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1] - 3, i * 3 + 1 - gUnknown_03006F8C[i], 0);
                gFrameObjects[gUnknown_03006F8C[i] + i * 3 + 0x15].screenX = gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1]].screenX;
                if (gFrameCounter & 1) {
                    if (++gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1]].screenX == 0x18) {
                        gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1]].unknown23[7] = 0;
                        sub_08042E58(gUnknown_03006FA0[i][0][gUnknown_03006F8C[i] + 1], gUnknown_03006FA0[i][1][gUnknown_03006F8C[i] + 1], gUnknown_03006FA0[i][2][gUnknown_03006F8C[i] + 1], gUnknown_03006FA0[i][3][gUnknown_03006F8C[i] + 1],
                                     i * 3 + 1 - gUnknown_03006F8C[i], gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1] - 3,
                                     gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1] - 3].screenX, gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1] - 3].screenY + 3, 0, 3, 5);
                        sub_08043240(gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1] - 3, 8);
                    }
                }
            } else
            if (gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1]].unknown23[7] == 2) {
                sub_080432A0(gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1] - 3, i * 3 + 1 - gUnknown_03006F8C[i], 0);
                gFrameObjects[gUnknown_03006F8C[i] + i * 3 + 0x15].screenX = gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1]].screenX;
                if (gFrameCounter & 1) {
                    if (++gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1]].screenX == 0x2C) {
                        gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1]].unknown23[7] = 0;
                        sub_08042E58(gUnknown_03006FA0[i][0][gUnknown_03006F8C[i] + 1], gUnknown_03006FA0[i][1][gUnknown_03006F8C[i] + 1], gUnknown_03006FA0[i][2][gUnknown_03006F8C[i] + 1], gUnknown_03006FA0[i][3][gUnknown_03006F8C[i] + 1],
                                     i * 3 + 1 - gUnknown_03006F8C[i], gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1] - 3,
                                     gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1] - 3].screenX, gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1] - 3].screenY + 3, 0, 3, 5);
                        sub_08043240(gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] + 1] - 3, 0xC);
                    }
                }
            }
        }
    }
}

void sub_0806B01C(void) {

    s32 i;

    for (i = 0; i <= 2; i++) {
        if (gUnknown_03006F8C[i] != 0) {
            if (gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] - 1]].unknown23[7] == 1) {
                if (--gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] - 1]].screenX <= -0x10)
                    gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] - 1]].unknown23[7] = 0;
                sub_080432A0(gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] - 1] - 3, i * 3 + 3 - gUnknown_03006F8C[i], 0);
                gFrameObjects[gUnknown_03006F8C[i] + i * 3 + 0x13].screenX = gFrameObjects[gEncounterFrameSlotsView[i][gUnknown_03006F8C[i] - 1]].screenX;
            }
        }
    }
}
