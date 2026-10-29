/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "input.h"
#include "main.h"
#include "object_numeric_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"

/* Observed byte offsets within the actual 128-frame array. */
struct EffectFrameView {
    u8 pad00[2];
    s16 x0, y0;                 /* 002,004 */
    u8 pad06[0x14];
    u16 timer1A;
    u8 pad1C[4];
    u8 phase20, offset21;
    u8 pad22[0x7E0];
    s16 x32, y32;               /* 802,804 */
    u8 pad806[0x3C];
    s16 x33, y33;               /* 842,844 */
    u8 pad846[0x53E];
    s16 y54;                   /* D84 */
    u8 padD86[0x3E];
    s16 y55;                   /* DC4 */
    u8 padDC6[0x7C];
    s16 x57, y57;               /* E42,E44 */
};

extern const u8 gRandomBytes_083F7D80[];
extern void sub_0806B718(u8);

s32 sub_0806C958(void);

s32 sub_0806C958(void) {
  /* The private view uses observed offsets inside gFrameObjects[128]. */
  const u8 *random;
  struct EffectFrameView *timerWork;
  u32 cursor;
  s32 i;
  s32 x;
  u32 timer;
  u32 gateTimer;
  u32 quarterMask;
  s8 selection;
  u8 phase;
  u8 active;
  u32 updatedTimer;
  phase = (*((struct EffectFrameView *) gFrameObjects)).phase20;
  switch (phase)
  {
    case 0:
      sub_08048864(0U, 0xC000U, 0x34U, 0xDU, 3U);
      (*((struct EffectFrameView *) gFrameObjects)).x0 = 0x78;
      (*((struct EffectFrameView *) gFrameObjects)).y0 = -0x10;
      (*((struct EffectFrameView *) gFrameObjects)).timer1A = phase;
      (*((struct EffectFrameView *) gFrameObjects)).offset21 = 1;
      (*((struct EffectFrameView *) gFrameObjects)).phase20 += 1;
      selection = (s8) gState0TransferWork.bytes[0xE];
      if (selection > 0x23)
    {
      sub_08048864(0x2EU, 0xC800U, 0x10U, 2U, 3U);
      sub_08048864(0x36U, 0xCC08U, 0x12U, 2U, 3U);
      (*((struct EffectFrameView *) gFrameObjects)).y54 = 0x1E;
    }
    else
      if (selection > 0)
    {
      sub_08048864(0x21U, 0xCC08U, 0x12U, 2U, 3U);
      (*((struct EffectFrameView *) gFrameObjects)).x33 = (u16) (*((struct EffectFrameView *) gFrameObjects)).x32;
      (*((struct EffectFrameView *) gFrameObjects)).y33 = ((u16) (*((struct EffectFrameView *) gFrameObjects)).y32) + 8;
    }
      break;

    case 1:
      /* Capture the mask here to preserve the original temporary order. */
      if((*((struct EffectFrameView *)gFrameObjects)).timer1A<=144U && !((*((struct EffectFrameView *)gFrameObjects)).timer1A&(quarterMask=3)))
    {
      i = 0;
      random = gRandomBytes_083F7D80;
      cursor = ((u32) gFrameObjects) + 0xA02;
      for (; i <= 5; i++)
      {
        timerWork = (struct EffectFrameView *) gFrameObjects;
        active = *((u8 *) (cursor + 0x1E));
        if (active == 0)
        {
          *((u8 *) (cursor + 0x1E)) = 3;
          *((s16 *) (cursor + 0)) = (*(const u8 *)(((gFrameCounter+i)&0xFFU)+(u32)random) & 0x3F) + 0x58;
          do
          {
            *((s16 *) (cursor + 2)) = ((u16) (*((struct EffectFrameView *) gFrameObjects)).y57) - 0x10;
          }
          while (0);
          *((u16 *) (cursor + 0x18)) = active;
          gateTimer=timerWork->timer1A;
          if(!(gateTimer&15U))
          {
            sub_08074DE0(0x3DU);
          }
          break;
        }
        cursor += 64;
      }

      timer = 4 & (*((struct EffectFrameView *) gFrameObjects)).timer1A;
      x = 0x76;
      if (timer != 0)
      {
        x = 0x7A;
      }
      (*((struct EffectFrameView *) gFrameObjects)).x57 = x;
      (*((struct EffectFrameView *) gFrameObjects)).y57 = ((u16) (*((struct EffectFrameView *) gFrameObjects)).y57) + 1;
    }
      timer = (*((struct EffectFrameView *) gFrameObjects)).timer1A;
      if ((timer > 0xEBU) || (9 & ((u8) gNewKeys)))
    {
      sub_0806B718(0);
      sub_0806B718(0x39);
      return 1;
    }
      updatedTimer=timer+1;
      (*((struct EffectFrameView *) gFrameObjects)).timer1A=updatedTimer;
      if (((u16)updatedTimer)==0x20)
    {
      sub_08048864(0x2FU, 0xC800U, 0x10U, 2U, 3U);
      sub_08048864(0x37U, 0xCC08U, 0x12U, 2U, 3U);
      (*((struct EffectFrameView *) gFrameObjects)).y55 = 0x1E;
    }
      break;

    default:
      break;

  }

  return 0;
}
