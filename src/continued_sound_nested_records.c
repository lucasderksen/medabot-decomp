/* Byte-exact GNU lexical helper; observed root/records are partial views. */
#include "global.h"
struct FamilySoundRecord74028 {
 u32 active;u8 pad4[8];u32 control;u8 pad10[0x28];u16 ticks;u8 pad3A[0xE];
};
struct FamilySoundRoot74028 {u8 pad0[0x690];struct FamilySoundRecord74028 records[2];};
struct CommandWork73FC0;
extern struct FamilySoundRoot74028 *gFamilySoundRoot74028;
extern void sub_08073FC0(struct CommandWork73FC0 *);
void sub_08074070(void) {
 void sub_08074028(u32 slot) {
  struct FamilySoundRecord74028 *record=&gFamilySoundRoot74028->records[slot];
  if(record->active !=0 && !(record->control & 1)) record->ticks++;
  sub_08073FC0((struct CommandWork73FC0 *)record);
 }
 sub_08074028(0);sub_08074028(1);
}
