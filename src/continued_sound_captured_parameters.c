/* Byte-exact paired GNU nested functions; field roles and allocation extent remain provisional. */
#include "global.h"
struct SoundRecord74EA0 { u8 pad0[0x14];u32 active;u8 pad18[0x36];u16 id;u8 flags,pad51[0x1F],value; };
struct SoundRoot74EA0 {u8 pad[0x1D0];struct SoundRecord74EA0 records[8];};
extern struct SoundRoot74EA0 *gSoundRoot74EA0;
void sub_08074EA0(s32 arg0,s32 arg1) {
 struct SoundRoot74EA0 *root;
 void sub_08074E64(struct SoundRecord74EA0 *record) {
  if(record->id==arg0 && record->active!=0) {
   record->value=arg1;
   record->flags|=0x40;
  }
 }
 root=gSoundRoot74EA0;
 sub_08074E64(&root->records[0]);
 sub_08074E64(&root->records[1]);
 sub_08074E64(&root->records[2]);
 sub_08074E64(&root->records[3]);
 sub_08074E64(&root->records[6]);
 sub_08074E64(&root->records[7]);
}
