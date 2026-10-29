/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_late_graphics.h"
#include "continued_numeric.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "encounter_choices.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "gba.h"
#include "main_callbacks.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sound_tables.h"
#include "sound_voice.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct Point66D8C {
    s16 w;
    s16 x;
    s16 y;
    s16 z;
    u8 pad08[8];
};
struct Ctx66D8C {
    u8 pad00[0x3C];
    u16 counter3C;
    u8 pad3E[0xA];
    u8 timer48;
    u8 half49;
    u8 pad4A[0x34];
    u8 mode7E;
    u8 pad7F;
    s16 target80[3];
    s8 velocity86[3];
    u8 pad89;
    s16 chain8A[3][4];
    u8 bytesA2[5];
    u8 bytesA7[5];
    u8 padAC[0x24];
    struct Point66D8C points[18];
    s32 matrix[4][4];
};
struct DmaRegs68A84 { u32 source, destination, control; };

extern const s16 gAffineSineTable_080AE8F4[];
extern const u8 gUnknownBytes_083B83FC[];
extern s32 gTransferStep03000000;
extern s32 gUnknown_03006F80;
extern s32 sub_0807CD2C(s32, s32);
extern s32 sub_0807CDF8(s32, s32);
extern struct Ctx66D8C *gCtx66D8C asm("gMainContextPointer_03006F74");
extern u16 *gUnknown_0300002C;
extern u16 gUnknown_0202FC00[];
extern u16 gUnknown_03000028;
extern u16 gUnknown_03000030[];
extern u16 gUnknown_03000170[];
extern u16 gUnknown_030002B0[];
extern u16 gUnknown_030003F0;
extern u8 gTransferDivisor03000005;
extern u8 gUnknown_03006FA0[3][4][3];
extern u8 gUnknown_03006FD0[3][3];
extern u8 gUnknown_03006FDC;
extern void sub_080668D4(u32);
extern void sub_08066A14(void);
extern void sub_08066B4C(u32, u32, u32);
extern void sub_08068460(u8, u8, u16);
extern void sub_08069320(void);
extern void sub_0806938C(void);
extern void sub_08069910(void);
extern void sub_08069A08(void);

void sub_08066D8C(void);
s32 sub_08068A84(void);
void sub_08068F50(void);
void sub_0806D4A4(void);
void sub_08072910(struct SoundChannelState *channel, u8 note);

void sub_08066D8C(void) {

    s32 i, k;
    u32 angle;
    u16 c;

    sub_080424B8();
    if (gCtx66D8C->timer48 == 0) {
        gCtx66D8C->timer48 = sub_080424B8();
        if (gCtx66D8C->timer48 == 0)
            gCtx66D8C->timer48++;
        gCtx66D8C->half49 = gCtx66D8C->timer48 >> 1;
    } else {
        gCtx66D8C->timer48--;
        if (gCtx66D8C->timer48 < gCtx66D8C->half49)
            sub_080668D4((u8)(gCtx66D8C->timer48 >> 2) + 0x14);
        else
            {
            s32 a = (u8)(gCtx66D8C->half49 >> 1);
            s32 d = (u8)(gCtx66D8C->timer48 >> 2) - 0x14;
            sub_080668D4(a - d);
        }
    }
    gCtx66D8C->chain8A[0][0] = (gCtx66D8C->target80[0] - gCtx66D8C->chain8A[0][0]) / 16 + gCtx66D8C->chain8A[0][0];
    gCtx66D8C->chain8A[1][0] = (gCtx66D8C->target80[1] - gCtx66D8C->chain8A[1][0]) / 16 + gCtx66D8C->chain8A[1][0];
    gCtx66D8C->chain8A[2][0] = (gCtx66D8C->target80[2] - gCtx66D8C->chain8A[2][0]) / 16 + gCtx66D8C->chain8A[2][0];
    gCtx66D8C->chain8A[0][1] = (gCtx66D8C->chain8A[0][0] - gCtx66D8C->chain8A[0][1]) / 16 + gCtx66D8C->chain8A[0][1];
    gCtx66D8C->chain8A[1][1] = (gCtx66D8C->chain8A[1][0] - gCtx66D8C->chain8A[1][1]) / 16 + gCtx66D8C->chain8A[1][1];
    gCtx66D8C->chain8A[2][1] = (gCtx66D8C->chain8A[2][0] - gCtx66D8C->chain8A[2][1]) / 16 + gCtx66D8C->chain8A[2][1];
    gCtx66D8C->chain8A[0][2] = (gCtx66D8C->chain8A[0][1] - gCtx66D8C->chain8A[0][2]) / 16 + gCtx66D8C->chain8A[0][2];
    gCtx66D8C->chain8A[1][2] = (gCtx66D8C->chain8A[1][1] - gCtx66D8C->chain8A[1][2]) / 16 + gCtx66D8C->chain8A[1][2];
    gCtx66D8C->chain8A[2][2] = (gCtx66D8C->chain8A[2][1] - gCtx66D8C->chain8A[2][2]) / 16 + gCtx66D8C->chain8A[2][2];
    gCtx66D8C->chain8A[0][3] = (gCtx66D8C->chain8A[0][2] - gCtx66D8C->chain8A[0][3]) / 16 + gCtx66D8C->chain8A[0][3];
    gCtx66D8C->chain8A[1][3] = (gCtx66D8C->chain8A[1][2] - gCtx66D8C->chain8A[1][3]) / 16 + gCtx66D8C->chain8A[1][3];
    gCtx66D8C->chain8A[2][3] = (gCtx66D8C->chain8A[2][2] - gCtx66D8C->chain8A[2][3]) / 16 + gCtx66D8C->chain8A[2][3];
    gCtx66D8C->bytesA2[4] = sub_080669AC(gCtx66D8C->bytesA2[3], gCtx66D8C->bytesA2[4], 0x7F);
    gCtx66D8C->bytesA2[3] = sub_080669AC(gCtx66D8C->bytesA2[2], gCtx66D8C->bytesA2[3], 0x7F);
    gCtx66D8C->bytesA2[2] = sub_080669AC(gCtx66D8C->bytesA2[1], gCtx66D8C->bytesA2[2], 0x7F);
    gCtx66D8C->bytesA2[1] = sub_080669AC(gCtx66D8C->bytesA2[0], gCtx66D8C->bytesA2[1], 0x7F);
    gCtx66D8C->bytesA7[4] = sub_080669AC(gCtx66D8C->bytesA7[3], gCtx66D8C->bytesA7[4], 0x7F);
    gCtx66D8C->bytesA7[3] = sub_080669AC(gCtx66D8C->bytesA7[2], gCtx66D8C->bytesA7[3], 0x7F);
    gCtx66D8C->bytesA7[2] = sub_080669AC(gCtx66D8C->bytesA7[1], gCtx66D8C->bytesA7[2], 0x7F);
    gCtx66D8C->bytesA7[1] = sub_080669AC(gCtx66D8C->bytesA7[0], gCtx66D8C->bytesA7[1], 0x7F);
    sub_08066A14();
    gCtx66D8C->counter3C = c = gCtx66D8C->counter3C + 1;
    if ((c & 0xFF) == 0) {
        angle = sub_080424B8() & 0xFF;
        gCtx66D8C->bytesA2[0] = (gAffineSineTable_080AE8F4[angle] * 5) >> 5;
        gCtx66D8C->bytesA7[0] = (gAffineSineTable_080AE8F4[angle + 0x40] * 5) >> 5;
        gCtx66D8C->bytesA2[0] += 0x78;
        gCtx66D8C->bytesA7[0] += 0x50;
    }
    if (!(0x3F & gCtx66D8C->counter3C))
        gCtx66D8C->mode7E = sub_080424B8() & 3;
    switch (3 & gCtx66D8C->mode7E) {
    case 0:
        gCtx66D8C->velocity86[0] += 2;
        gCtx66D8C->velocity86[1] += 1;
        break;
    case 1:
        gCtx66D8C->velocity86[0] -= 2;
        gCtx66D8C->velocity86[1] += 2;
        gCtx66D8C->velocity86[2] += 3;
        break;
    case 2:
        gCtx66D8C->velocity86[0] += 1;
        gCtx66D8C->velocity86[2] += 2;
        break;
    case 3:
        gCtx66D8C->velocity86[0] += 5;
        gCtx66D8C->velocity86[1] += 1;
        gCtx66D8C->velocity86[2] -= 2;
        break;
    }
    if (gCtx66D8C->velocity86[0] < -0x10)
        gCtx66D8C->velocity86[0] = -0x10;
    if (gCtx66D8C->velocity86[1] < -0x10)
        gCtx66D8C->velocity86[1] = -0x10;
    if (gCtx66D8C->velocity86[2] < -0x10)
        gCtx66D8C->velocity86[2] = -0x10;
    if (gCtx66D8C->velocity86[0] > 0x10)
        gCtx66D8C->velocity86[0] = 0x10;
    if (gCtx66D8C->velocity86[1] > 0x10)
        gCtx66D8C->velocity86[1] = 0x10;
    if (gCtx66D8C->velocity86[2] > 0x10)
        gCtx66D8C->velocity86[2] = 0x10;
    gCtx66D8C->target80[0] += gCtx66D8C->velocity86[0];
    gCtx66D8C->target80[1] += gCtx66D8C->velocity86[1];
    gCtx66D8C->target80[2] += gCtx66D8C->velocity86[2];
    for (i = 0; i <= 0x47; i = k) {
        s32 j, q, x, y;
        u32 root;
        s32 px, py, pz;
        struct Ctx66D8C *ctx;
        struct FrameObject *object;

        j = sub_0807CDF8(i, 0x12);
        if (j == 0) {
            struct Ctx66D8C *c;
            s32 d;
            sub_08066A14();
            c = gCtx66D8C;
            d = sub_0807CD2C(i, 0x12);
            sub_08066B4C((c->chain8A[0][d] >> 4) & 0xFF, (c->chain8A[1][d] >> 4) & 0xFF, (c->chain8A[2][d] >> 4) & 0xFF);
        }
        ctx = gCtx66D8C;
        px = ctx->points[j].x;
        py = ctx->points[j].y;
        pz = ctx->points[j].z;
        x = px * ctx->matrix[0][0] + py * ctx->matrix[1][0] + pz * ctx->matrix[2][0] + ctx->matrix[3][0];
        y = px * ctx->matrix[0][2] + py * ctx->matrix[1][2] + pz * ctx->matrix[2][2] + ctx->matrix[3][2];
        x >>= 8;
        y >>= 8;
        root = (u32)gFrameObjects;
        k = i + 1;
        object = (struct FrameObject *)(root + (k << 6));
        q = sub_0807CD2C(i, 0x12) + 1;
        object->screenX = ctx->bytesA2[q] + x;
        object->screenY = ctx->bytesA7[q] + y;
    }
}

s32 sub_08068A84(void) {

    s32 w, i;
    u16 **source;
    u32 inv;
    s32 step;
    u8 div;
    if (gTransferStep03000000 == gTransferDivisor03000005 << 5)
        return 1;
    step = gTransferStep03000000;
    div = gTransferDivisor03000005;
    if (sub_0807CDF8(step, div) == 0) {
        w = sub_0807CD2C(step, div);
        inv = 0x20 - w;
        source = &gUnknown_0300002C;
        for (i = 0; i <= 0x1FF; i++) {
            gUnknown_0202FC00[i] = (((0x1F & (*source)[i]) * w + (0x1F & gUnknown_03000028) * (s32)inv) >> 5)
                + ((((0x3E0 & (*source)[i]) * w + (0x3E0 & gUnknown_03000028) * (s32)inv) >> 5) & 0x3E0)
                + ((((0x7C00 & (*source)[i]) * w + (0x7C00 & gUnknown_03000028) * (s32)inv) >> 5) & 0x7C00);
        }
        {
            volatile struct DmaRegs68A84 *dma = (void *)0x040000D4;
            dma->source = (u32)gUnknown_0202FC00;
            dma->destination = 0x05000000;
            dma->control = 0x84000100;
            (void)dma->control;
        }
    }
    return 0;
}

void sub_08068F50(void) {

    s32 i;
    const u8 *record;

    sub_08069320();
    sub_08069A08();
    sub_0806938C();
    sub_08069910();
    sub_08074B88(0);
    for (i = 0; i <= 2; i++) {
        gUnknown_03006FD0[0][i] = gCounter6ED08_03001800.pad8C[i];
        gUnknown_03006FA0[0][0][i] = ((u8 (*)[4])&gCounter6ED08_03001800.pad8C[3])[i][0];
        gUnknown_03006FA0[0][1][i] = ((u8 (*)[4])&gCounter6ED08_03001800.pad8C[3])[i][1];
        gUnknown_03006FA0[0][2][i] = ((u8 (*)[4])&gCounter6ED08_03001800.pad8C[3])[i][2];
        gUnknown_03006FA0[0][3][i] = ((u8 (*)[4])&gCounter6ED08_03001800.pad8C[3])[i][3];
        sub_08042D94(gUnknown_03006FA0[0][0][i], gUnknown_03006FA0[0][1][i], gUnknown_03006FA0[0][2][i],
                     gUnknown_03006FA0[0][3][i], 2 - i);
    }
    record = gState0EncounterRecords_083C1B80[gChoiceRecords6A024[gUnknown_03006FDC].firstRecord];
    record += 4;
    for (i = 0; i <= 2; i++) {
        gUnknown_03006FA0[1][0][i] = *record++;
        gUnknown_03006FA0[1][1][i] = *record++;
        gUnknown_03006FA0[1][2][i] = *record++;
        gUnknown_03006FA0[1][3][i] = *record;
        record += 9;
        gUnknown_03006FD0[1][i] = gUnknownBytes_083B83FC[(gUnknown_03006FA0[1][3][i] << 6) + 0x31] - 0x64;
        sub_08042D94(gUnknown_03006FA0[1][0][i], gUnknown_03006FA0[1][1][i], gUnknown_03006FA0[1][2][i],
                     gUnknown_03006FA0[1][3][i], 5 - i);
    }
    record = gState0EncounterRecords_083C1B80[gChoiceRecords6A024[gUnknown_03006FDC].secondRecord];
    record += 4;
    for (i = 0; i <= 2; i++) {
        gUnknown_03006FA0[2][0][i] = *record++;
        gUnknown_03006FA0[2][1][i] = *record++;
        gUnknown_03006FA0[2][2][i] = *record++;
        gUnknown_03006FA0[2][3][i] = *record;
        record += 9;
        gUnknown_03006FD0[2][i] = gUnknownBytes_083B83FC[(gUnknown_03006FA0[2][3][i] << 6) + 0x31] - 0x64;
        sub_08042D94(gUnknown_03006FA0[2][0][i], gUnknown_03006FA0[2][1][i], gUnknown_03006FA0[2][2][i],
                     gUnknown_03006FA0[2][3][i], 8 - i);
    }
    sub_08074B88(0x13);
    sub_08068460(2, 2, 0);
    *(volatile u16 *)0x04000000 |= 0x1E00;
    gUnknown_03006F80 = 6;
    gUnknown_0300137C = 1;
}

void sub_0806D4A4(void) {

    s32 i;
    s32 v;
    s32 t;

    gUnknown_030003F0 += 0x80;
    for (i = 0; i <= 0x1F; i++) {
        t = gUnknown_030003F0;
        t = 0x7800 - t;
        v = gUnknown_03000030[i] * 15;
        v *= 8;
        v = t - v;
        do {
            gUnknown_03000170[i] = v;
            gUnknown_030002B0[i] = v >> 16;
        } while (0);
    }
    for (; i <= 0x7F; i++) {
        gUnknown_03000170[i] = 0;
        gUnknown_030002B0[i] = 0;
    }
    for (; i <= 0x9F; i++) {
        t = gUnknown_030003F0;
        t += 0x7800;
        v = gUnknown_03000030[i] * 15;
        v *= 8;
        v = t - v;
        do {
            gUnknown_03000170[i] = v;
            gUnknown_030002B0[i] = v >> 16;
        } while (0);
    }
    *(volatile u16 *)0x04000020 = gUnknown_03000030[0];
    *(volatile u16 *)0x04000028 = gUnknown_03000170[0];
    *(volatile u16 *)0x0400002A = gUnknown_030002B0[0];
}

void sub_08072910(struct SoundChannelState *channel, u8 note) {

    s32 key;
    s32 sum;

    channel->byte66 = channel->byte65;
    switch (channel->byte63) {
    case 0:
        channel->words18[4] = (channel->byte6E << 8) + *(u8 *)channel->track + 1;
        channel->track = (u8 *)channel->track + 1;
        channel->byte6E = 0;
        switch (channel->type) {
        case 0:
        case 1:
        case 2:
        {
            sum = note + (s8)channel->byte6A;
            key = sum - 0x24;
            if (key < 0)
                key = 0;
            else if (key > 0x47)
                key = 0x47;
            channel->half48 = key;
            channel->lastNote = 0xFF;
            channel->unknown46 = sub_080732B8(channel->half48);
            channel->flags |= 0x53;
            sub_080726D4(channel);
            sub_0807258C(channel);
            break;
        }
        case 3:
            sub_080728A0(channel, note);
            break;
        case 4:
        case 5:
            channel->half48 = note;
            channel->flags |= 0x50;
            break;
        }
        break;
    case 1:
        channel->words18[4] = channel->words18[5];
        channel->lastNote = 0xFF;
        switch (channel->type) {
        case 0:
        case 1:
        case 2:
        {
            u8 *p;
            u32 high;
            channel->half48 = 0;
            high = note << 8;
            p = channel->track;
            channel->unknown46 = *p | high;
            channel->track = p + 1;
        }
            channel->flags |= 0x53;
            break;
        case 4:
        case 5:
        {
            u32 high = note << 8;
            u8 *p = channel->track;
            channel->half48 = *p | high;
            channel->track = p + 1;
        }
            channel->unknown46 = 0;
            channel->flags |= 0x50;
            break;
        }
        break;
    case 2:
        channel->words18[4] = (channel->byte6E << 8) + *(u8 *)channel->track + 1;
        channel->track = (u8 *)channel->track + 1;
        channel->byte6E = 0;
        switch (channel->type) {
        case 3:
            sub_080728A0(channel, note);
            break;
        case 4:
        case 5:
        {
            const struct SoundAuxBank *aux = gFamilySoundRoot74028->aux;
            key = note - aux->base;
            if (key < 0)
                key = 0;
            else if (aux->count - 1 < key)
                key = aux->count - 1;
            channel->half48 = key;
            channel->flags |= 0x50;
            break;
        }
        }
        break;
    }
}
