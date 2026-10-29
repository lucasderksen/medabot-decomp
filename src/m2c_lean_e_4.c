/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "composite_graphics.h"
#include "compression.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_command_data.h"
#include "frame_objects.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_work.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct SetupContext67F64 { u8 pad00[5]; u8 cursor05; u8 pad06[0x30]; u16 tileBase36; u8 pad38[2]; u16 timer3A; u8 pad3C[0xC]; u8 flags48[4]; };

extern const u8 *const gDebugMedalMetadata_083B6590[];
extern const void *const gGraphicsTable62C28[];
extern struct SetupContext67F64 *gSetupContext67F64 asm("gMainContextPointer_03006F74");
extern u8 gDebugMedalWork_03000BEA[];

void sub_08067F64(void);

void sub_08067F64(void) {

    s32 i;
    u8 c;

    {
        u32 kind = gInventoryRecords[gQuantityResult_030017EC].byte1;
        s32 level = gInventoryRecords[gQuantityResult_030017EC].unknown06[2] - 1;
        LeDecompress(gGraphicsTable62C28[kind * 5 + level], (void *)0x06010000);
    }
    gFrameObjects[0].flags = 0xCA04;
    gFrameObjects[0].screenX = 0x78;
    gFrameObjects[0].screenY = 0x28;
    gFrameObjects[0].frameAndGroup = 0x200;
    gFrameObjects[0].palette = 0;
    gFrameObjects[0].tableSelector = 0;
    gFrameObjects[0].priority = 0x40;
    gFrameObjects[0].scaleX = 0x40;
    gFrameObjects[0].scaleY = 0x40;
    for (i = 0; i <= 0xF; i++) {
        gDebugMenuTextBuffer[i] = gDebugMedalMetadata_083B6590[gInventoryRecords[gQuantityResult_030017EC].byte1][i];
        if (gDebugMenuTextBuffer[i] == 0xFE)
            break;
    }
    sub_08040DB8(gDebugMenuTextBuffer, 0x14, 5, 0xA, 0xA, 1, 1, 0);
    if (gInventoryRecords[gQuantityResult_030017EC].byte5 == 0x64) {
        *(volatile u16 *)((((*(volatile u16 *)0x04000008 >> 8) & 0x1F) << 11) + 0x0600029A) = (gSetupContext67F64->tileBase36 + 0x14) | 0x7000;
        *(volatile u16 *)((((*(volatile u16 *)0x04000008 >> 8) & 0x1F) << 11) + 0x060002DA) = (gSetupContext67F64->tileBase36 + 0x15) | 0x7000;
        *(volatile u16 *)((((*(volatile u16 *)0x04000008 >> 8) & 0x1F) << 11) + 0x0600029C) = (gSetupContext67F64->tileBase36 + 0x16) | 0x7000;
        *(volatile u16 *)((((*(volatile u16 *)0x04000008 >> 8) & 0x1F) << 11) + 0x060002DC) = (gSetupContext67F64->tileBase36 + 0x17) | 0x7000;
    } else {
        {
            volatile u16 *dst = (volatile u16 *)((((*(volatile u16 *)0x04000008 >> 8) & 0x1F) << 11) + 0x0600029A);
            struct SetupContext67F64 *ctx = gSetupContext67F64;
            *dst = ((u8)(gInventoryRecords[gQuantityResult_030017EC].byte5) / 10u * 2 + ctx->tileBase36) | 0x7000;
        }
        {
            volatile u16 *dst = (volatile u16 *)((((*(volatile u16 *)0x04000008 >> 8) & 0x1F) << 11) + 0x060002DA);
            struct SetupContext67F64 *ctx = gSetupContext67F64;
            *dst = ((u8)(gInventoryRecords[gQuantityResult_030017EC].byte5) / 10u * 2 + ctx->tileBase36 + 1) | 0x7000;
        }
        {
            volatile u16 *dst = (volatile u16 *)((((*(volatile u16 *)0x04000008 >> 8) & 0x1F) << 11) + 0x0600029C);
            struct SetupContext67F64 *ctx = gSetupContext67F64;
            *dst = ((u8)(gInventoryRecords[gQuantityResult_030017EC].byte5) % 10u * 2 + ctx->tileBase36) | 0x7000;
        }
        {
            volatile u16 *dst = (volatile u16 *)((((*(volatile u16 *)0x04000008 >> 8) & 0x1F) << 11) + 0x060002DC);
            struct SetupContext67F64 *ctx = gSetupContext67F64;
            *dst = ((u8)(gInventoryRecords[gQuantityResult_030017EC].byte5) % 10u * 2 + ctx->tileBase36 + 1) | 0x7000;
        }
    }
    sub_08040DB8(gDebugMedalWork_03000BEA + (gQuantityResult_030017EC << 6), 0x1E, 0x11, 0xA, 0xA, 2, 0, 0);
    *(volatile u16 *)0x04000000 |= 0x200;
    *(volatile u16 *)0x04000000 |= 0x400;
    *(volatile u16 *)0x04000000 |= 0x800;
    *(volatile u16 *)0x04000000 |= 0x1000;
    gSetupContext67F64->timer3A = 0;
    gSetupContext67F64->flags48[0] = 0;
    gSetupContext67F64->flags48[1] = 0;
    gSetupContext67F64->flags48[2] = 0;
    gSetupContext67F64->flags48[3] = 0;
    gSetupContext67F64->cursor05 = 0;
    gUnknown_0300137C++;
    gState0TypedWork.bytes[0x84] = 0;
}
