/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_effects.h"
#include "effect_work.h"
#include "frame.h"
#include "frame_objects.h"
#include "initialization.h"
#include "input.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ContinuedScaleFrame21 {
 u8 prefix[0x840];u16 flags;s16 screenX,screenY;u16 frameAndGroup;u8 scaleX,scaleY,palette,priority;
 u8 gapC[0xC];u16 angle,unknown1A;u8 tableSelector,affineIndex;u8 gap1E[6];u8 kind;u8 gap25[0xB];u16 savedX;s16 savedY;u8 gap34[0xC];
};
struct LocalScriptMenuContext { u8 pad00[2]; u16 timer; u8 pad04[4]; u32 phase; u8 pad0C[0x73]; u8 mode; };
struct ContinuedSceneRecord {u8 pad00[2];s16 firstRecord;u8 pad04[2];s16 secondRecord;u8 pad08;u8 command;u8 pad0A[2];};

extern const struct ContinuedSceneRecord gUnknown_08485C00[];
extern const u8 *const gState0NextCommands_083B6100[]; /* Observed index0x1C. */
extern const u8 *const gUnknown_08485F88[];
extern const u8 gUnknown_080AFC80[];
extern const u8 gUnknown_080AFC83[];
extern s32 gUnknown_03006F88;
extern s32 sub_0806B0D4(void);
extern s32 sub_0806B4C8(void);
extern u8 gUnknown_03006FDC;
extern void sub_0806941C(u8);
extern void sub_08069DF0(void);
extern void sub_08069E1C(void);
extern void sub_0806A078(u8 *,u8 *);
extern void sub_0806B530(u8,u8,u8,u8);

void sub_0801DC74(void);
void sub_080657C4(void);
s32 sub_0806A114(void);

void sub_0801DC74(void) {
    struct ContinuedScaleFrame21 *frames;
    u8 *work;
    u32 zero;
    if(gState0TypedWork.bytes[0x84]!=0x1E) {
        gState0TypedWork.bytes[0x84]++;
        return;
    }
    sub_08040CD0(0x21,1);
    frames=(struct ContinuedScaleFrame21 *)gFrameObjects;
    frames->flags=(zero=0,0xC624);
    frames->tableSelector=zero;
    work=gState0TransferWork.bytes;
    frames->screenX=(u16)gFrameObjects[work[0xDE]*4+0x59].screenX;
    frames->screenY=(u16)gFrameObjects[work[0xDE]*4+0x59].screenY-4;
    frames->palette=6;
    frames->scaleX=0x80;
    frames->scaleY=0x80;
    frames->priority=0xF0;
    sub_08040B90(gState0NextCommands_083B6100[0x1C],0x21);
    work[0xAA]++;
}

void sub_080657C4(void) {
    s32 temp_r4;
    struct LocalScriptMenuContext *context;
    u32 var_r0;
    u16 temp_r0;
    u8 elapsed;
    u16 var_r5;
    u32 temp_r0_2;
    u32 temp_r0_3;
    u32 temp_r0_4;
    u32 temp_r0_5;

    context = gMainContextPointer_03006F74;
    temp_r0 = context->timer;
    (*(u16 *)((u8 *)(gMainContextPointer_03006F74) + 2)) = temp_r0 + 1;
    elapsed = temp_r0;
    var_r5 = 0;
    if (!(2 & (*(u8 *)((u8 *)(&gMainFlagsWord_03001784) + 0)))) {
        {
            u32 slots = (u32)gMain2ScriptSlots_08485678;
            u32 base = (u32)gUnknown_080AFC80;
            u32 offset = context->phase;
            u32 index = *(const u8 *)(base + offset);
            if (sub_0803FB3C(*(const void *const *)(slots + (index << 2))) == 0)
                return;
        }
        if (!(1 & (u8)gNewKeys)) {
            return;
        }
        sub_08074DE0(0xDU);
        temp_r0_2 = (*(u32 *)((u8 *)(gMainContextPointer_03006F74) + 8)) + 1;
        (*(u32 *)((u8 *)(gMainContextPointer_03006F74) + 8)) = temp_r0_2;
        if (temp_r0_2 <= 2U) {
            goto block_28;
        }
        gState0TypedWork.bytes[0x84] = 0;
        gState0TypedWork.bytes[0x1B] = 0;
        gUnknown_0300137C += 1;
        (*(u8 *)((u8 *)(&gMainFlagsWord_03001784) + 0)) |= 2;
        return;
    }
    temp_r0_3 = context->phase;
    switch (temp_r0_3) {                            /* irregular */
    case 0:
        if (sub_0803FB3C(gMain2ScriptSlots_08485678[gUnknown_080AFC83[(*(u32 *)((u8 *)(gMainContextPointer_03006F74) + 8))]]) == 0) {
            return;
        }
        if (!(1 & (u8)gNewKeys)) {
            return;
        }
        sub_08074DE0(0xDU);
        (*(u32 *)((u8 *)(gMainContextPointer_03006F74) + 8)) = (u32) ((*(u32 *)((u8 *)(gMainContextPointer_03006F74) + 8)) + 1);
        sub_0803FB0C();
        sub_080415E8(1U, 0U, 7U);
        return;
    case 1:
    case 2:
    case 3:
        if (sub_0803FB3C(gMain2ScriptSlots_08485678[gUnknown_080AFC83[(*(u32 *)((u8 *)(gMainContextPointer_03006F74) + 8))]]) == 0) {
            return;
        }
        if (sub_08041674() == 0) {
            return;
        }
        if (gState0TypedWork.bytes[0x2A] == 0) {
            if (1 & (*(u8 *)((u8 *)(&gMainFlagsWord_03001784) + 0))) {
                temp_r0_4 = (*(u32 *)((u8 *)(gMainContextPointer_03006F74) + 8)) + 1;
                (*(u32 *)((u8 *)(gMainContextPointer_03006F74) + 8)) = temp_r0_4;
                if (temp_r0_4 > 3U) goto block_28;
                goto block_25;
            } else {
                struct LocalScriptMenuContext *phaseContext = gMainContextPointer_03006F74;
                temp_r0_5 = phaseContext->phase + 1;
                phaseContext->phase = temp_r0_5;
                if (temp_r0_5 <= 2U) {
block_25:
                    sub_080415E8(1U, 0U, 7U);
                } else {
                    phaseContext->phase = temp_r0_5 + 1;
                }
            }
        } else {
            (*(u32 *)((u8 *)(gMainContextPointer_03006F74) + 8)) = 0U;
            gUnknown_0300137C += 2;
        }
block_28:
        sub_0803FB0C();
        return;
    case 4:
        if (sub_0803FB3C(gMain2ScriptSlots_08485678[gUnknown_080AFC83[(*(u32 *)((u8 *)(gMainContextPointer_03006F74) + 8))]]) != 0) {
            sub_08074B88(0U);
            sub_08074DE0(0U);
            Unknown_0805DEB0();
            {
            struct LocalScriptMenuContext *resetContext = gMainContextPointer_03006F74;
            resetContext->timer = 0;
            resetContext->phase += 1;
            }
            return;
        }
        return;
    case 5:
        if (((u32) elapsed > 0x1DU) && (sub_08074FA4(4U) == 0)) {
            for (var_r0 = 0; (temp_r4 = (s8)var_r0) <= 3; var_r0 = (u8)(temp_r4 + 1)) {
                var_r5 = (u16)sub_0805DDEC(0);
                if (var_r5 == 0) break;
            }
            sub_08074B88((u32) (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x7F)));
            (*(u32 *)((u8 *)(gMainContextPointer_03006F74) + 8)) = (u32) var_r5;
            gUnknown_0300137C += 3;
            sub_0803FB0C();
            sub_080020C8();
        }
        break;
    }
}

s32 sub_0806A114(void) {
    switch ((u32)gUnknown_03006F88) {
    case 0:
        sub_0803FAA0(1,2,0);
        sub_08069DF0();
        sub_0806B530(0,1,0x18,0x58);
        *(volatile u16 *)0x04000000 |= 0x400;
        gUnknown_03006F88++;
        return 0;
    case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13:
        sub_0806941C((u8)(gUnknown_03006F88-6));
    case 1: case 2: case 3: case 4: case 5:
        sub_0803FB3C(gUnknown_08485F88[1]);
        gUnknown_03006F88++;
        break;

    case 14:
        if (sub_0803FB3C(gUnknown_08485F88[1])) {
            sub_0803FB0C();
            sub_08069E1C();
            sub_0806B530(1,4,0,0);
            gUnknown_03006F88++;
        }
        break;
    case 15:
        if (sub_0803FB3C(gUnknown_08485F88[2])) {
            sub_0803FB0C();
            gUnknown_03006F88++;
        }
        break;
    case 16:
        if (gFrameObjects[0].commandDelay==0) gUnknown_03006F88++;
        break;
    case 17:
        if (sub_0803FB3C(gUnknown_08485F88[5])) {
            const u8 *record;
            sub_0803FB0C();
            record=gState0EncounterRecords_083C1B80[gUnknown_08485C00[gUnknown_03006FDC].firstRecord];
            sub_0806A078(gDebugMenuTextBuffer,(u8 *)gState0EncounterLabels_083C40B8[*record]);
            sub_0806B530(0,2,0x40,0);
            gFrameObjects[1].screenX=0x68;
            gUnknown_03006F88++;
        }
        break;
    case 18:
        if (sub_0803FB3C(gUnknown_08485F88[3]) && gFrameObjects[0].commandDelay==0) {
            sub_0803FB0C();
            gUnknown_03006F88++;
        }
        break;
    case 19:
        if (sub_0803FB3C(gUnknown_08485F88[gUnknown_08485C00[gUnknown_03006FDC].command])) {
            const u8 *record;
            sub_0803FB0C();
            record=gState0EncounterRecords_083C1B80[gUnknown_08485C00[gUnknown_03006FDC].secondRecord];
            sub_0806A078(gDebugMenuTextBuffer,(u8 *)gState0EncounterLabels_083C40B8[*record]);
            sub_0806B530(0,2,0x40,0);
            gFrameObjects[1].screenX=0xA8;
            gUnknown_03006F88++;
        }
        break;
    case 20:
        if (sub_0803FB3C(gUnknown_08485F88[4]) && gFrameObjects[0].commandDelay==0) {
            sub_0803FB0C();
            gUnknown_03006F88++;
        }
        break;
    case 21:
        if (sub_0803FB3C(gUnknown_08485F88[gUnknown_08485C00[gUnknown_03006FDC].command+1])) {
            sub_0803FB0C();
            gUnknown_03006F88++;
        }
        break;
    case 22:
        if (sub_0803FB3C(gUnknown_08485F88[6])) return 1;
        break;
    }
    sub_0806B0D4();
    sub_0806B4C8();
    return 0;
}
