/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "graphics.h"
#include "input.h"
#include "state0_callbacks.h"
#include "state0_inventory_rows.h"
#include "state0_work.h"

struct ContinuedADE8Work { u8 prefix[0x46];u8 part; };


u32 sub_0800ADE8(void);

u32 sub_0800ADE8(void) {
 u32 pressed=(u8)(0x20&*(u8*)&gRepeatedKeys);
 u32 value;
 u8 *part;
 struct ContinuedADE8Work *work;
 if(pressed!=0) {
  sub_08074DE0(2);
  work=(void*)&gState0TypedWork;part=&work->part;
  value=*part;
  if(value==0)value=7;else value--;
  *part=value;
  sub_0800AC2C();
  return 1;
 }
 if(0x10&*(u8*)&gRepeatedKeys) {
  sub_08074DE0(2);
  work=(void*)&gState0TypedWork;part=&work->part;
  value=*part;
  if(value==7)*part=pressed;else *part=value+1;
  sub_0800AC2C();
  return 1;
 }
 return 0;
}
