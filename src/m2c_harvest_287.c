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
#include "frame.h"
#include "main.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "utility_helpers.h"

struct StatePrefix62484 {u8 unknown00[0x84];u8 step84;};
struct MainContext_08062484 {u8 pad19[0x19];u8 mode19,index1A;u8 pad1B[0x2D];u8 flag48;};


void sub_08062484(void);

void sub_08062484(void) {

    s8 temp_r1_2;
    s8 temp_r1_4;
    s8 temp_r1_6;
    s8 temp_r1_8;
    u32 var_r0_2;
    u32 var_r0_3;
    u32 var_r0_4;
    u32 var_r0_5;
    struct FrameObject *temp_r2;
    struct FrameObject *temp_r2_2;
    struct FrameObject *temp_r2_3;
    struct FrameObject *temp_r2_4;
    u32 *var_r1;
    u32 frameRoot;
    u32 secondRoot;
    u32 thirdRoot;
    u32 fourthRoot;
    u32 inventoryRoot;
    u32 callMode;
    u32 counterShift;
    u32 var_r0;
    u8 temp_r1;
    u8 temp_r1_3;
    u8 temp_r1_5;
    u8 temp_r1_7;

    if ((u32) ((struct StatePrefix62484 *)&gState0TypedWork)->step84 <= 8U) {
        sub_0803F684(0U, ((struct StatePrefix62484 *)&gState0TypedWork)->step84 * 4, 0xFFFEU);
        sub_0803F998(0U, ((struct StatePrefix62484 *)&gState0TypedWork)->step84 * 4, 0x7FFDU);
        ((struct StatePrefix62484 *)&gState0TypedWork)->step84 += 1;
        return;
    }
    if (((struct MainContext_08062484 *)gMainContextPointer_03006F74)->flag48 != 0) {
        callMode=((struct MainContext_08062484 *)gMainContextPointer_03006F74)->mode19;
        inventoryRoot=0x02040000U;
        sub_08044BA8(callMode, (u32) *(u16 *)(inventoryRoot + ((u32)((struct MainContext_08062484 *)gMainContextPointer_03006F74)->index1A * 8)));
        gMainState=0;
        return;
    } else {
        *(volatile u16 *)0x04000000 &= 0xFDFF;
        var_r0_2 = 0;
        do {
            counterShift=(u32)var_r0_2<<24;
            frameRoot=(u32)gFrameObjects;
            temp_r1_2=(s32)counterShift>>24;
            temp_r2 = (struct FrameObject *)(((u32)(temp_r1_2+0xB)<<6)+frameRoot);
            temp_r2->flags &= 0xBFFF;
            temp_r1 = temp_r1_2 + 1;
            var_r0_2 = (u8) temp_r1;
        } while ((s32) (s8) temp_r1 <= 1);
        var_r0_3 = 0;
        do {
            counterShift=(u32)var_r0_3<<24;
            secondRoot=(u32)gFrameObjects;
            temp_r1_4=(s32)counterShift>>24;
            temp_r2_2 = (struct FrameObject *)(((u32)(temp_r1_4+0x68)<<6)+secondRoot);
            temp_r2_2->flags &= 0xBFFF;
            temp_r1_3 = temp_r1_4 + 1;
            var_r0_3 = (u8) temp_r1_3;
        } while ((s32) (s8) temp_r1_3 <= 1);
        var_r0_4 = 0;
        do {
            counterShift=(u32)var_r0_4<<24;
            thirdRoot=(u32)gFrameObjects;
            temp_r1_6=(s32)counterShift>>24;
            temp_r2_3 = (struct FrameObject *)(((u32)(temp_r1_6+0x6A)<<6)+thirdRoot);
            temp_r2_3->flags &= 0xBFFF;
            temp_r1_5 = temp_r1_6 + 1;
            var_r0_4 = (u8) temp_r1_5;
        } while ((s32) (s8) temp_r1_5 <= 3);
        var_r0_5 = 0;
        do {
            counterShift=(u32)var_r0_5<<24;
            fourthRoot=(u32)gFrameObjects;
            temp_r1_8=(s32)counterShift>>24;
            temp_r2_4 = (struct FrameObject *)(((u32)(temp_r1_8+0x6E)<<6)+fourthRoot);
            temp_r2_4->flags &= 0xBFFF;
            temp_r1_7 = temp_r1_8 + 1;
            var_r0_5 = (u8) temp_r1_7;
        } while ((s32) (s8) temp_r1_7 <= 3);
        gFrameObjects[8].flags &= 0xBFFF;
        *(volatile u16 *)0x04000052 = 0x1000;
        *(volatile u16 *)0x0400000A = 0x1E05;
        *(volatile u16 *)0x0400000C = 0x1D06;
        gMainSubstate = 0xB;
        gUnknown_0300137C=1;
    }

}
