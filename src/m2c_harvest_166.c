/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "interrupts.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "render_work.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedFrame3GroupInit { u8 prefix[0xC0]; struct FrameObject frame; };
struct ContinuedBackupPhase139 { u8 pad00[0x139]; u8 phase139; };
struct ContinuedFrame21BlinkInit { u8 prefix[0x840]; struct FrameObject frame; };
struct ContinuedSetupB028 {u8 prefix[0xA8];u8 kind;u8 tail[0x57];};
struct ContinuedWorkB028 {u8 prefix[0x87];u8 selection;};
struct ContinuedFramePairNext {u8 prefix[0x840];struct FrameObject first,second;};
struct ContinuedWorkB5AC {u8 prefix[0x60];u8 bank;u8 gap61[0x71];u8 results[3];u8 gapD5;u16 values[3];u8 gapDC[0xC];s16 x,gapEA,y;};
struct ContinuedSetupB5AC {u8 prefix[0xC9];u8 kind,variant,first,second;u8 tailCD[0x33];};
struct ContinuedFrame3ScriptInit { u8 prefix[0xC0]; struct FrameObject frame; };
struct LocalInitializationWork71460 { u8 pad00[4]; s16 phase4; };

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gUnknown_084E1028[];
extern const u8 gUnknown_08510358[64];
extern struct LocalInitializationWork71460 gGraphicsTransferCounter;
extern u32 sub_08036E54(u32);
extern u8 gState0FrameBackup[0x800];
extern u8 gUnknown_02021000[0x800];
extern u8 gUnknown_02021800[0x800];
extern u8 gUnknown_02022000[0x800];
extern u8 gUnknown_02028000[0x2000];
extern u8 gUnknown_03007010;
extern void sub_08036E64(s32,s32,s16,s16);
extern void sub_08040CD0(u8,u8);
extern void sub_08071898(u8,u16,u8);
extern void sub_08074DE0(u32);

void sub_0801C1C0(void);
void sub_0801DFE0(void);
void sub_0802724C(void);
void sub_0802B028(void);
void sub_0802B5AC(void);
void sub_08030910(void);
void sub_08071460(void);

void sub_0801C1C0(void) {
    struct ContinuedFrame3GroupInit *frames;
    u8 *work;
    frames = (struct ContinuedFrame3GroupInit *)gFrameObjects;
    frames->frame.flags = 0xC004;
    frames->frame.tableSelector = 0;
    work = gState0TransferWork.bytes;
    frames->frame.screenX = (u16)gFrameObjects[work[0x87]*4+0x5D].screenX;
    frames->frame.screenY = (u16)gFrameObjects[work[0x87]*4+0x5D].screenY - 0xC;
    frames->frame.palette = 6;
    frames->frame.frameAndGroup = 0xA11;
    frames->frame.priority = 0x81;
    sub_08074DE0(0x2Fu);
    work[0x9C] += 1;
}

void sub_0801DFE0(void) {
    struct ContinuedBackupPhase139 *work;
    u8 *phase;
    work = (struct ContinuedBackupPhase139 *)&gState0TypedWork;
    phase = &work->phase139;
    switch (*phase) {
    case 0:
        CpuFastSet((const void *)0x06002800,gState0FrameBackup,0x200u);
        CpuFastSet((const void *)0x0600C800,gUnknown_02021000,0x200u);
        CpuFastSet((const void *)0x0600D000,gUnknown_02021800,0x200u);
        CpuFastSet((const void *)0x0600D800,gUnknown_02022000,0x200u);
        *phase += 1;
        return;
    case 1:
        CpuFastSet(gFrameObjects,gUnknown_02028000,0x800u);
        *phase += 1;
        return;
    case 2:
        gUnknownCallback_030017F0 = DummyInterruptHandler;
        sub_08040CD0(0,0x80u);
        *phase = 0;
        gState0TransferWork.bytes[0xAA] += 1;
        return;
    }
}

void sub_0802724C(void) {
    struct ContinuedFrame21BlinkInit *frames;
    u8 *work;
    sub_08040CD0(0x21u,2u);
    frames = (struct ContinuedFrame21BlinkInit *)gFrameObjects;
    frames->frame.flags = 0xC404;
    work = gState0TransferWork.bytes;
    if (work[0xF8] & 2u) frames->frame.flags |= 0x1000;
    frames->frame.tableSelector = 0;
    frames->frame.screenX = 0x78;
    frames->frame.screenY = 0x40;
    frames->frame.palette = 7;
    frames->frame.priority = 0xF0;
    sub_08040B90(gState0NextCommands_083B6100[0x5A],0x21u);
    work[0xAA] += 1;
}

void sub_0802B028(void) {
    struct ContinuedFramePairNext *frames;
    struct ContinuedWorkB028 *transfer;
    struct ContinuedSetupB028 *setup;

    LeDecompress(gUnknown_084E1028, (void *)0x06014800);
    CpuFastSet(gUnknown_08510358, (void *)0x050002C0, 0x10U);
    frames=(struct ContinuedFramePairNext *)gFrameObjects;
    frames->first.flags = 0xC604;
    frames->first.tableSelector = 0;
    transfer=(struct ContinuedWorkB028 *)gState0TransferWork.bytes;

    frames->first.screenX = (s16) (u16)gFrameObjects[transfer->selection*4+0x5D].screenX;
    frames->first.screenY = (u16)gFrameObjects[transfer->selection*4+0x5D].screenY - 4;
    frames->first.palette = 6;
    frames->first.priority = 0xF0;
    frames->first.scaleX = 0x40;
    frames->first.scaleY = 0x40;
    frames->first.frameAndGroup = 0x7A00;
    frames->second.flags = 0xC404;
    frames->second.tableSelector = 0;
    frames->second.screenX = (s16) (u16)gFrameObjects[transfer->selection*4+0x5D].screenX;
    frames->second.screenY = (u16)gFrameObjects[transfer->selection*4+0x5D].screenY - 4;
    frames->second.palette = 7;
    frames->second.priority = 0xE0;
    frames->second.unknown2C[1] = 0;
    setup=(struct ContinuedSetupB028 *)gSetupBuffer_03000590;
    if (setup[transfer->selection].kind == 0x1E) {
        frames->second.frameAndGroup = 0x7A01;
    } else {
        frames->second.frameAndGroup = 0x7A02;
    }
    sub_08074DE0(0x4CU);
    gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
}

void sub_0802B5AC(void) {
    u32 i;
    sub_08040CD0(0x21,3);
    for(i=0;i<3;i++) {
        struct ContinuedWorkB5AC *work=(struct ContinuedWorkB5AC *)gState0TransferWork.bytes;
        if(work->results[i]==0)continue;
        switch(work->values[i]) {
        case 0: {
            struct ContinuedWorkB5AC *caseWork=(struct ContinuedWorkB5AC *)gState0TransferWork.bytes;
            sub_08036E64(caseWork->bank+i,13,caseWork->x,caseWork->y);
            break;
        }
        case 1: {
            struct ContinuedWorkB5AC *caseWork=(struct ContinuedWorkB5AC *)gState0TransferWork.bytes;
            sub_08036E64(caseWork->bank+i,17,caseWork->x,caseWork->y);
            break;
        }
        case 2: {
            struct ContinuedWorkB5AC *caseWork=(struct ContinuedWorkB5AC *)gState0TransferWork.bytes;
            sub_08036E64(caseWork->bank+i,19,caseWork->x,caseWork->y);
            break;
        }
        case 3: {
            struct ContinuedWorkB5AC *caseWork=(struct ContinuedWorkB5AC *)gState0TransferWork.bytes;
            sub_08036E64(caseWork->bank+i,16,caseWork->x,caseWork->y);
            break;
        }
        case 4: {
            struct ContinuedSetupB5AC *setup=(struct ContinuedSetupB5AC *)gSetupBuffer_03000590;
            u8 *caseWork=gState0TransferWork.bytes;
            u8 *bank=caseWork+0x60;
            setup[*bank+i].kind=0x2B;
            setup[*bank+i].first=sub_08036E54(*(s16 *)(caseWork+0xE8));
            setup[*bank+i].second=sub_08036E54(*(s16 *)(caseWork+0xEC));
            setup[*bank+i].variant=1;
            break;
        }
        case 5: {
            struct ContinuedSetupB5AC *setup=(struct ContinuedSetupB5AC *)gSetupBuffer_03000590;
            u8 *caseWork=gState0TransferWork.bytes;
            u8 *bank=caseWork+0x60;
            setup[*bank+i].kind=0x2C;
            setup[*bank+i].variant=0;
            setup[*bank+i].first=sub_08036E54(*(s16 *)(caseWork+0xE8));
            setup[*bank+i].second=sub_08036E54(*(s16 *)(caseWork+0xEC));
            break;
        }
        case 6: {
            struct ContinuedSetupB5AC *setup=(struct ContinuedSetupB5AC *)gSetupBuffer_03000590;
            u8 *caseWork=gState0TransferWork.bytes;
            u8 *bank=caseWork+0x60;
            setup[*bank+i].kind=0x2E;
            setup[*bank+i].variant=0;
            setup[*bank+i].first=sub_08036E54(*(s16 *)(caseWork+0xE8));
            setup[*bank+i].second=sub_08036E54(*(s16 *)(caseWork+0xEC));
            break;
        }
        case 7: {
            struct ContinuedSetupB5AC *setup=(struct ContinuedSetupB5AC *)gSetupBuffer_03000590;
            u8 *caseWork=gState0TransferWork.bytes;
            u8 *bank=caseWork+0x60;
            setup[*bank+i].kind=0x2F;
            setup[*bank+i].variant=0;
            setup[*bank+i].first=sub_08036E54(*(s16 *)(caseWork+0xE8));
            setup[*bank+i].second=sub_08036E54(*(s16 *)(caseWork+0xEC));
            break;
        }
        }
    }
    gState0TransferWork.bytes[0xAA]++;
}

void sub_08030910(void) {
    struct ContinuedFrame3ScriptInit *frames;
    u8 *work;
    frames = (struct ContinuedFrame3ScriptInit *)gFrameObjects;
    frames->frame.flags = 0xC004;
    frames->frame.tableSelector = 0;
    work = gState0TransferWork.bytes;
    frames->frame.screenX = (u16)gFrameObjects[work[0x87]*4+0x5D].screenX;
    frames->frame.screenY = (u16)gFrameObjects[work[0x87]*4+0x5D].screenY - 4;
    frames->frame.palette = 6;
    frames->frame.priority = 0x81;
    sub_08040B90(gState0NextCommands_083B6100[0x15],3u);
    sub_08074DE0(7u);
    gUnknown_0300137C += 1;
}

void sub_08071460(void) {
    s32 sp4;
    u32 renderZero;
    volatile u32 *dma;
    u8 *var_r5_2;
    s32 var_r7;
    struct FrameObject *var_r7_2;
    s32 var_r4;

    sp4 = 0;
    dma=(volatile u32 *)0x040000D4;
    dma[0]=(u32)&sp4;
    dma[1]=(u32)gFrameObjects;
    dma[2]=0x85000800;
    (void)dma[2];
    sub_08048864(0U, 0xCC00U, 0x50EU, 4U, 3U);
    gFrameObjects->screenX = 0xD4;
    gFrameObjects->screenY = 0;
    gFrameObjects->priority = 0x4A;
    gFrameObjects[0xA].commandStopped = 0xFF;
    sub_08048864(0xBU, 0xCC00U, 0x50EU, 4U, 3U);
    gFrameObjects[0xB].screenX = 0x14;
    gFrameObjects[0xB].screenY = 0;
    gFrameObjects[0xB].priority = 0x4A;
    gFrameObjects[0x15].commandStopped = (u8)-1U;
    var_r4=0;
    var_r7=0x580;
    do {
        sub_08048864((u8)(var_r4+0x16),0xCC00U,(u16)(var_r4*12+0x27),(u8)var_r4,1U);
        ((struct FrameObject *)((u8 *)gFrameObjects+var_r7))->screenY=0x48;
        var_r7+=0x40;
        ++var_r4;
    } while (var_r4<=3);
    gFrameObjects[0x16].screenX = 0x58;
    gFrameObjects[0x16].priority = 8;
    gFrameObjects[0x17].screenX = 0x88;
    gFrameObjects[0x17].priority = 8;
    gFrameObjects[0x18].screenX = 0x70;
    gFrameObjects[0x18].priority = 0xC;
    gFrameObjects[0x18].screenY = 0x24;
    gFrameObjects[0x19].screenX = 0x70;
    gFrameObjects[0x19].priority = 4;
    var_r4=0;
    var_r5_2=(u8 *)gFrameObjects+0x682;
    var_r7_2=&gFrameObjects[0x16];
    do {
        sub_08048864((u8)(var_r4+0x1A),0xCC08U,0x513U,0xEU,3U);
        *(s16 *)var_r5_2=(u16)var_r7_2->screenX;
        *(s16 *)(var_r5_2+2)=0x48;
        var_r5_2+=0x40;
        ++var_r7_2;
        ++var_r4;
    } while (var_r4<=3);
    renderZero=0;
    gFrameObjects[0x1C].screenY = 0x38;
    gUnknown_03007010 = 0;
    sub_08071898(0x18, 0x3F, 0xC);
    gRenderMode = renderZero;
    gGraphicsTransferCounter.phase4 = 0xF;
    gUnknown_0300137C = 4;
}
