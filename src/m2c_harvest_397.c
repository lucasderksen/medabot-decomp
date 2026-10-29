/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "frame.h"
#include "state0_work.h"


void sub_08070108(void);

void sub_08070108(void) {

  u16 *fillSource;
  u16 fill;
  volatile u32 *dma;
  fillSource = &fill;
  fill = 0;
  dma = (volatile u32 *) 0x040000D4;
  dma[0] = (u32) (&fill);
  dma[1] = 0x0600FB0A;
  dma[2] = 0x8100000A;
  (void) dma[2];
  fill = 0;
  dma[0] = (u32) fillSource;
  dma[1] = 0x0600FB4A;
  dma[2] = 0x8100000A;
  (void) dma[2];
  fill = 0;
  dma[0] = (u32) (&fill);
  dma[1] = 0x0600FB8A;
  dma[2] = 0x8100000A;
  (void) dma[2];
  fill = 0;
  dma[0] = (u32) (&fill);
  dma[1] = 0x0600FBCA;
  dma[2] = 0x8100000A;
  (void) dma[2];
  gState0TransferWork.bytes[0x2E] = fill;
}
