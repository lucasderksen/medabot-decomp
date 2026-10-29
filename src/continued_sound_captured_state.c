/* Byte-exact GNU nested functions; observed record prefix is not a full allocation extent. */
#include "global.h"
struct FamilySoundRecord750AC {u8 pad0[0x14];u32 active;u8 pad18[0x5C];};
struct FamilySoundRoot750AC {struct FamilySoundRecord750AC records[10];};
extern struct FamilySoundRoot750AC *gFamilySoundRoot750AC;
extern void sub_08075028(void *,s32,s32);
void sub_080750AC(s32 value) {
 void sub_0807506C(u32 slot) {
  struct FamilySoundRoot750AC *root=gFamilySoundRoot750AC;
  if(root->records[slot].active != 0) sub_08075028(&root->records[slot],0,value);
 }
 sub_0807506C(0);sub_0807506C(1);sub_0807506C(2);sub_0807506C(3);
 sub_0807506C(8);sub_0807506C(9);
}
