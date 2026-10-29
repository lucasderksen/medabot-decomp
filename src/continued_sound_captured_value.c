/* Byte-exact paired GNU nested functions; field roles and allocation extent remain provisional. */
#include "global.h"
struct Record74C30 {u8 pad0[0x50],flags,pad51[0x1F],value,pad71[3];};
struct Root74C30 {struct Record74C30 records[13];};
extern struct Root74C30 *gSoundRoot74C30;
void sub_08074C30(s32 value){
 struct Root74C30 *root;
 void sub_08074C0C(struct Record74C30 *record){record->value=value;record->flags|=0x40;}
 root=gSoundRoot74C30;
 sub_08074C0C(&root->records[0]);sub_08074C0C(&root->records[1]);
 sub_08074C0C(&root->records[2]);sub_08074C0C(&root->records[3]);
 sub_08074C0C(&root->records[8]);sub_08074C0C(&root->records[9]);sub_08074C0C(&root->records[12]);
}
