/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "state0_work.h"

extern const s16 *const gUnknown_083CE164[];extern u8 gUnknown_03001800[];extern void sub_0803D450(void);extern void sub_0803D4AC(void);

void sub_08039448(void);
void sub_080394C4(void);

void sub_08039448(void) {
u8 done;u8 *initial=&done;*initial=0;sub_0803D450();sub_0803D4AC();if(done==0){const s16 *const *tables=gUnknown_083CE164;u8 *work=gUnknown_03001800;s16 *expected=(s16 *)(work+0x102);u16 *cursor=(u16 *)(work+0x100); u8 *flag=&done;do{const s16 *selected=tables[work[0xF9]]; u16 index=*cursor;s16 current=*expected;s16 reference=selected[index];if(current==reference){sub_0803D4AC();*flag=1;}else{sub_0803D4AC();}}while(*flag==0);}}

void sub_080394C4(void) {
u8 done;u8 *initial=&done;*initial=0;sub_0803D450();sub_0803D4AC();if(done==0){const s16 *const *tables=gUnknown_083CE164;u8 *work=gUnknown_03001800;u16 *cursor=(u16 *)(work+0x100); u8 *flag=&done;do{const s16 *selected=tables[work[0xF9]];u32 slot=(u32)work[0xFD]*2;u8 *values=work+0x102;s16 *expected=(s16 *)(slot+(u32)values); u16 index=*cursor;s16 current=*expected;s16 reference=selected[index];if(current==reference){sub_0803D4AC();*flag=1;}else{sub_0803D4AC();}}while(*flag==0);}}
