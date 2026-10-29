/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "main_callbacks.h"
#include "serial.h"

struct ContinuePhaseWork {u8 pad[0x102];s16 phase,slot;};

extern struct ContinuePhaseWork gUnknown_03001800;extern const void *const gUnknown_083CEDF4[];
extern void sub_0803D450(void);extern void sub_0803D4AC(void);extern void sub_0801BF78(const void *,u32,u32);

void sub_0803B328(void);

void sub_0803B328(void) {
struct FrameObject *frames;struct ContinuePhaseWork *work;sub_0803D450();frames=gFrameObjects;work=&gUnknown_03001800;frames[work->slot].unknown2C[2]=work->phase;sub_0801BF78(gUnknown_083CEDF4[work->phase],0,0);sub_0803D4AC();}
