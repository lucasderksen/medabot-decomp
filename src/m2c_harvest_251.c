/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "main_callbacks.h"

extern void *memset(void *, s32, unsigned long);
extern void sub_080669EC(s32 *,const s32 *);

void sub_08066A14(void);

void sub_08066A14(void) {

 s32 matrix[16];
 memset(matrix,0,sizeof(matrix));
 matrix[0]=0x100;matrix[5]=0x100;matrix[10]=0x100;matrix[15]=0x100;
 sub_080669EC((s32 *)((u32)gMainContextPointer_03006F74+0x1F0),matrix);
}
