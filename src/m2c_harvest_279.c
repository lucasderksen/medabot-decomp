/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "serial.h"

struct ByteDispatch33 {u8 before10[0x10];u8 phase;};
typedef s32 (*ResultCallback33)(void);

extern const ResultCallback33 gUnknown_08485BD8[];
extern struct ByteDispatch33 gGraphicsTransferCounter;

s32 sub_08071DDC(void);

s32 sub_08071DDC(void) {

 return gUnknown_08485BD8[gGraphicsTransferCounter.phase]();
}
