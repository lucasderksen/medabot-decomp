/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "graphics.h"
#include "state0_work.h"

struct ContinueClearWork {u8 pad[0xD2];u8 bytes[3];u8 padD5;s16 halves[3];};

extern struct ContinueClearWork gUnknown_03001800;

void sub_0803836C(void);

void sub_0803836C(void) {
u32 index=0;struct ContinueClearWork *root=&gUnknown_03001800;u8 *bytes=&root->bytes[0];u32 zero=0;s16 *out=&root->halves[0];do{*(u8 *)(index+(u32)bytes)=zero;*out=zero;out++;index++;}while(index<=2);}
