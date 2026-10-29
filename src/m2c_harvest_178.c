/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "bg_scroll.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedSetup32DA0 {u8 prefix[6];u8 type;u8 unknown07[0x39];u8 active;u8 gap41[0x88];u8 mode;u8 tail[0x36];};
struct Continued35478Backing { struct FrameObject frames[128]; };


extern u32 sub_08032FD0(u32, u32);
extern u32 sub_08032FFC(void);
extern u32 sub_0803301C(void);
extern u32 sub_080330E8(u32);
extern void sub_08033154(u32, u32);

void sub_08031F2C(void);
void sub_08035478(u32 selected);

void sub_08031F2C(void) {
    struct ContinuedSetup32DA0 *setup;
    u32 var_r6;

    gState0TransferWork.bytes[0x60] = (u8) sub_08032FC4((u32) gState0TransferWork.bytes[0x5C]);
    var_r6 = 0;
    setup=(struct ContinuedSetup32DA0 *)gSetupBuffer_03000590;
    do {
        if ((setup[gState0TransferWork.bytes[0x60]].active != 0) && (sub_080331F8((u32) gState0TransferWork.bytes[0x60]) != 0) && (setup[gState0TransferWork.bytes[0x60]].mode != 0) && (sub_08032FD0(gState0TransferWork.bytes[0x60], setup[gState0TransferWork.bytes[0x5C]].type) != 0)) {
            *(var_r6 + (gState0TransferWork.bytes + 0x61)) = gState0TransferWork.bytes[0x60] + 1;
        }
        gState0TransferWork.bytes[0x60] = (u8) (gState0TransferWork.bytes[0x60] + 1);
        var_r6 += 1;
    } while (var_r6 <= 2U);
    if (sub_08032FFC() != 0) {
        gState0TransferWork.bytes[0x5E]=sub_0803301C()+1;
    } else {
        gState0TransferWork.bytes[0x60] = (u8) sub_08032FC4((u32) gState0TransferWork.bytes[0x5C]);
        var_r6 = 0;
    setup=(struct ContinuedSetup32DA0 *)gSetupBuffer_03000590;
        do {
            if ((setup[gState0TransferWork.bytes[0x60]].active != 0) && (sub_080331F8((u32) gState0TransferWork.bytes[0x60]) != 0) && (setup[gState0TransferWork.bytes[0x60]].mode != 0)) {
                *(var_r6 + (gState0TransferWork.bytes + 0x61)) = gState0TransferWork.bytes[0x60] + 1;
            }
            gState0TransferWork.bytes[0x60] = (u8) (gState0TransferWork.bytes[0x60] + 1);
            var_r6 += 1;
        } while (var_r6 <= 2U);
        if (sub_08032FFC() != 0) {
            gState0TransferWork.bytes[0x5E]=sub_0803301C()+1;
        } else {
            gState0TransferWork.bytes[0x60] = (u8) sub_08032FC4((u32) gState0TransferWork.bytes[0x5C]);
            var_r6 = 0;
    setup=(struct ContinuedSetup32DA0 *)gSetupBuffer_03000590;
            do {
                if ((setup[gState0TransferWork.bytes[0x60]].active != 0) && (sub_080331F8(gState0TransferWork.bytes[0x60])!=0) && (sub_08032FD0(gState0TransferWork.bytes[0x60], setup[gState0TransferWork.bytes[0x5C]].type) != 0)) {
                    *(var_r6 + (gState0TransferWork.bytes + 0x61)) = gState0TransferWork.bytes[0x60] + 1;
                }
                gState0TransferWork.bytes[0x60] = (u8) (gState0TransferWork.bytes[0x60] + 1);
                var_r6 += 1;
            } while (var_r6 <= 2U);
            if (sub_08032FFC() != 0) {
                gState0TransferWork.bytes[0x5E]=sub_0803301C()+1;
            } else {
                gState0TransferWork.bytes[0x60] = (u8) sub_08032FC4((u32) gState0TransferWork.bytes[0x5C]);
                gState0TransferWork.bytes[0x5E]=sub_08033090(gState0TransferWork.bytes[0x60])+1;
            }
        }
    }
    gState0TransferWork.bytes[0x5F] = (s8) (sub_080330E8(gState0TransferWork.bytes[0x5E] - 1) + 1);
    sub_08033154(gState0TransferWork.bytes[0x5C], *((gState0TransferWork.bytes + 0x5F) - 2));
}

void sub_08035478(u32 selected) {
 u32 best;
 s32 index;
 s32 chosen;
 u32 selectedOffset;
 struct Continued35478Backing *backing;
 struct FrameObject *frame;
 u8 *setup;
 u32 recordAddress;
 if (selected <= 2u) {
  best = 0xFF;
  index = 5;
  chosen = 5;
  setup = gSetupBuffer_03000590;
  selectedOffset = selected << 8;
  backing = (struct Continued35478Backing *)&gFrameObjects;
  frame = &backing->frames[0x71];
  recordAddress = (u32)setup + 0x540;
  do {
   if (*(u8 *)recordAddress != 0) {
    s16 x = frame->screenX;
    if ((u32)x < best) {
     best = (u32)x;
     chosen = index;
    }
   }
   frame -= 4;
   recordAddress -= 0x100;
   index--;
  } while (index > 2);
 } else {
  best = 0;
  index = 2;
  chosen = 2;
  setup = gSetupBuffer_03000590;
  selectedOffset = selected << 8;
  backing = (struct Continued35478Backing *)&gFrameObjects;
  frame = &backing->frames[0x65];
  recordAddress = (u32)setup + 0x240;
  do {
   if (*(u8 *)recordAddress != 0) {
    s16 x = frame->screenX;
    if ((u32)x > best) {
     best = (u32)x;
     chosen = index;
    }
   }
   frame -= 4;
   recordAddress -= 0x100;
   index--;
  } while (index >= 0);
 }
 {
  u8 *destination = (u8 *)(selectedOffset + (u32)setup);
  u32 value = chosen + 1;
  destination[0xE0] = value;
 }
}
