/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_blend_work.h"
#include "continued_float_progress.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "serial.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern void sub_08070550(void);
s32 sub_0806FCCC(u8);
s32 sub_0806FDA4(s32);
s32 sub_0806FF2C(s32);
u32 sub_080700C8(void);
u32 sub_08070108(void);
void sub_0806FE44(void);
void sub_080701A8(void);
void sub_080707BC(u32, u8, u8);

void sub_0806F23C(void);
void sub_0806F5A0(void);

void sub_0806F23C(void) {

  s32 phaseDuration = 0xC4;
  struct SceneFrameWork *work = &gState0TransferWork.sceneFrame;
  s32 var_r0_2;
  s32 var_r0_3;
  s32 var_r4;
  struct FrameObject *var_r6;
  u32 hiddenY;
  u32 frames;
  u32 lateFrameRoot;
  u32 temp_r0;
  s32 phase;
  u32 countRoot;
  u32 var_r5;
  work->first = (u16) (work->first + 1);
  work->second = (u16) (work->second + 0x6F);
  phase = work->count;
  countRoot = (u32) work;
  if (phase < phaseDuration)
  {
    switch ((u32) phase)
    {
      case 0:
        sub_08048864(1, 0xCA00, 0x309, 3, 3);
        gFrameObjects[1].screenX = 0x50;
        gFrameObjects[1].screenY = 0x38;
        gFrameObjects[1].scaleX = 2;
        gFrameObjects[1].scaleY = 2;
        sub_080707BC(1, 1, 0);
        sub_080707BC(4, 9, 0);
        sub_080707BC(5, 10, 0);
        gState0TransferWork.sceneFrame.count = (s32) (((u32) gState0TransferWork.sceneFrame.count) + 1u);
        break;

      case 1:
        goto shared_first_frame_delay;

      case 2:
        sub_08048864(2, 0xC600, 0x306, 2, 3);
        gFrameObjects[2].screenX = 0xB8;
        gFrameObjects[2].screenY = 0x70;
        gFrameObjects[2].scaleX = 2;
        gFrameObjects[2].scaleY = 2;
        sub_080707BC(2, 2, 0);
        gState0TransferWork.sceneFrame.count = (s32) (((u32) gState0TransferWork.sceneFrame.count) + 1u);
        break;

      case 3:
        if (gFrameObjects[2].commandDelay == 0)
      {
        sub_080707BC(3, 3, 0x70);
        sub_080707BC(3, 4, 0x68);
        sub_080707BC(3, 5, 0x68);
        sub_080707BC(3, 6, 0x70);
        sub_080707BC(3, 7, 0x78);
        sub_080707BC(3, 8, 0x78);
        goto increment;
      }
        break;

      case 4:
        var_r0_2 = 0;
        goto test_ff;

      default:
        if (sub_0806FDA4(0) != 0)
      {
        var_r0_3 = 0;
        goto apply_fccc;
      }
        goto default_increment;

    }

  }
  else
    if (phase == phaseDuration)
  {
    sub_080700C8();
    sub_08070108();
    sub_080701A8();
    frames = (u32) gFrameObjects;
    hiddenY = (((struct FrameObject *) (frames + 0x40))->screenY = 0xC8);
    ((struct FrameObject *) (frames + 0x80))->screenY = hiddenY;
    /* Three complete frame-array elements; the compiler reverses traversal. */
    for(var_r4=0;var_r4<3;++var_r4) (*(struct FrameObject *)(frames+((11+var_r4)<<6))).screenY=hiddenY;
    var_r4 = 0;
    lateFrameRoot = (u32) gFrameObjects;
    var_r6 = (struct FrameObject *) (lateFrameRoot + 0xC0);
    var_r5 = 0x03000000;
    for (;;)
    {
      sub_080707BC(0, var_r5 >> 24, 0);
      var_r6->screenY = 0xC8;
      var_r6++;
      var_r5 += 0x01000000;
      var_r4++;
      if (var_r4 > 5)
      {
        break;
      }
    }

    goto increment;
  }
  else
  {
    temp_r0 = phase - (phaseDuration + 1);
    switch (temp_r0)
    {
      case 0:
        gFrameObjects[1].frameAndGroup = 0x30A;
        gFrameObjects[1].screenY = 0x38;
        gFrameObjects[1].scaleX = 2;
        gFrameObjects[1].scaleY = 2;
        sub_080707BC(1, 1, 0);
        gState0TransferWork.sceneFrame.count = (s32) (((u32) gState0TransferWork.sceneFrame.count) + 1u);
        break;

      case 1:
        shared_first_frame_delay:
      if (gFrameObjects[1].commandDelay == 0)
      {
        /* Corresponding unsigned view gives the original wrapping word add. */
        *((u32 *) (countRoot + 8)) = (*((u32 *) (countRoot + 8))) + 1u;
      }

        break;

      case 2:
        gFrameObjects[2].frameAndGroup = 0x307;
        gFrameObjects[2].screenY = 0x70;
        gFrameObjects[2].scaleX = 2;
        gFrameObjects[2].scaleY = 2;
        sub_080707BC(2, 2, 0);
        gState0TransferWork.sceneFrame.count = (s32) (((u32) gState0TransferWork.sceneFrame.count) + 1u);
        break;

      case 3:
        if (gFrameObjects[2].commandDelay == 0)
      {
        sub_080707BC(3, 3, 0x78);
        sub_080707BC(3, 4, 0x70);
        sub_080707BC(3, 5, 0x78);
        sub_080707BC(3, 6, 0x70);
        sub_080707BC(3, 7, 0x68);
        sub_080707BC(3, 8, 0x70);
        goto increment;
      }
        break;

      case 4:
        var_r0_2 = 1;
        test_ff:
      if (sub_0806FF2C(var_r0_2) != 0)
      {
        increment:
        gState0TransferWork.sceneFrame.count = (s32) (((u32) gState0TransferWork.sceneFrame.count) + 1u);

      }

        break;

      default:
        if (sub_0806FDA4(0x28) != 0)
      {
        var_r0_3 = 1;
        apply_fccc:
        sub_0806FCCC(var_r0_3);

      }
        default_increment:
      work->count = (s32) (((u32) work->count) + 1u);

        break;

    }

  }
  sub_0806FE44();
  sub_08070550();
  if ((phaseDuration * 2) <= gState0TransferWork.sceneFrame.count)
  {
    gState0TransferWork.sceneFrame.count = 0;
    gState0TransferWork.sceneFrame.state = 6;
    gState0TransferWork.sceneFrame.mode = 0xD;
    gUnknown_0300137C = 2;
  }
}

void sub_0806F5A0(void) {

  s32 phaseDuration = 0xC4;
  struct SceneFrameWork *work = &gState0TransferWork.sceneFrame;
  s32 var_r0_2;
  s32 var_r0_3;
  s32 var_r4;
  struct FrameObject *var_r6;
  u32 hiddenY;
  u32 frames;
  u32 lateFrameRoot;
  u32 temp_r0;
  s32 phase;
  u32 countRoot;
  u32 var_r5;
  work->first = (u16) (work->first + 1);
  work->second = (u16) (work->second + 0x6F);
  phase = work->count;
  countRoot = (u32) work;
  if (phase < phaseDuration)
  {
    switch ((u32) phase)
    {
      case 0:
        sub_08048864(1, 0xCA00, 0x30B, 3, 3);
        gFrameObjects[1].screenX = 0x50;
        gFrameObjects[1].screenY = 0x38;
        gFrameObjects[1].scaleX = 2;
        gFrameObjects[1].scaleY = 2;
        sub_080707BC(1, 1, 0);
        sub_080707BC(4, 9, 0);
        sub_080707BC(5, 10, 0);
        gState0TransferWork.sceneFrame.count = (s32) (((u32) gState0TransferWork.sceneFrame.count) + 1u);
        break;

      case 1:
        goto shared_first_frame_delay;

      case 2:
        sub_08048864(2, 0xC600, 0x306, 2, 3);
        gFrameObjects[2].screenX = 0xB8;
        gFrameObjects[2].screenY = 0x70;
        gFrameObjects[2].scaleX = 2;
        gFrameObjects[2].scaleY = 2;
        sub_080707BC(2, 2, 0);
        gState0TransferWork.sceneFrame.count = (s32) (((u32) gState0TransferWork.sceneFrame.count) + 1u);
        break;

      case 3:
        if (gFrameObjects[2].commandDelay == 0)
      {
        sub_080707BC(3, 3, 0x70);
        sub_080707BC(3, 4, 0x68);
        sub_080707BC(3, 5, 0x68);
        sub_080707BC(3, 6, 0x70);
        sub_080707BC(3, 7, 0x78);
        sub_080707BC(3, 8, 0x78);
        goto increment;
      }
        break;

      case 4:
        var_r0_2 = 2;
        goto test_ff;

      default:
        if (sub_0806FDA4(0x28) != 0)
      {
        var_r0_3 = 2;
        goto apply_fccc;
      }
        goto default_increment;

    }

  }
  else
    if (phase == phaseDuration)
  {
    sub_080700C8();
    sub_08070108();
    sub_080701A8();
    frames = (u32) gFrameObjects;
    hiddenY = (((struct FrameObject *) (frames + 0x40))->screenY = 0xC8);
    ((struct FrameObject *) (frames + 0x80))->screenY = hiddenY;
    /* Three complete frame-array elements; the compiler reverses traversal. */
    for(var_r4=0;var_r4<3;++var_r4) (*(struct FrameObject *)(frames+((11+var_r4)<<6))).screenY=hiddenY;
    var_r4 = 0;
    lateFrameRoot = (u32) gFrameObjects;
    var_r6 = (struct FrameObject *) (lateFrameRoot + 0xC0);
    var_r5 = 0x03000000;
    for (;;)
    {
      sub_080707BC(0, var_r5 >> 24, 0);
      var_r6->screenY = 0xC8;
      var_r6++;
      var_r5 += 0x01000000;
      var_r4++;
      if (var_r4 > 5)
      {
        break;
      }
    }

    goto increment;
  }
  else
  {
    temp_r0 = phase - (phaseDuration + 1);
    switch (temp_r0)
    {
      case 0:
        gFrameObjects[1].frameAndGroup = 0x30C;
        gFrameObjects[1].screenY = 0x38;
        gFrameObjects[1].scaleX = 2;
        gFrameObjects[1].scaleY = 2;
        sub_080707BC(1, 1, 0);
        gState0TransferWork.sceneFrame.count = (s32) (((u32) gState0TransferWork.sceneFrame.count) + 1u);
        break;

      case 1:
        shared_first_frame_delay:
      if (gFrameObjects[1].commandDelay == 0)
      {
        /* Corresponding unsigned view gives the original wrapping word add. */
        *((u32 *) (countRoot + 8)) = (*((u32 *) (countRoot + 8))) + 1u;
      }

        break;

      case 2:
        gFrameObjects[2].frameAndGroup = 0x307;
        gFrameObjects[2].screenY = 0x70;
        gFrameObjects[2].scaleX = 2;
        gFrameObjects[2].scaleY = 2;
        sub_080707BC(2, 2, 0);
        gState0TransferWork.sceneFrame.count = (s32) (((u32) gState0TransferWork.sceneFrame.count) + 1u);
        break;

      case 3:
        if (gFrameObjects[2].commandDelay == 0)
      {
        sub_080707BC(3, 3, 0x78);
        sub_080707BC(3, 4, 0x70);
        sub_080707BC(3, 5, 0x78);
        sub_080707BC(3, 6, 0x70);
        sub_080707BC(3, 7, 0x68);
        sub_080707BC(3, 8, 0x70);
        goto increment;
      }
        break;

      case 4:
        var_r0_2 = 3;
        test_ff:
      if (sub_0806FF2C(var_r0_2) != 0)
      {
        increment:
        gState0TransferWork.sceneFrame.count = (s32) (((u32) gState0TransferWork.sceneFrame.count) + 1u);

      }

        break;

      default:
        if (sub_0806FDA4(0) != 0)
      {
        var_r0_3 = 3;
        apply_fccc:
        sub_0806FCCC(var_r0_3);

      }
        default_increment:
      work->count = (s32) (((u32) work->count) + 1u);

        break;

    }

  }
  sub_0806FE44();
  sub_08070550();
  if ((phaseDuration * 2) <= gState0TransferWork.sceneFrame.count)
  {
    gState0TransferWork.sceneFrame.count = 0;
    gState0TransferWork.sceneFrame.state = 9;
    gUnknown_0300137C = 2;
  }
}
