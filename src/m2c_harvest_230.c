/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "serial.h"

struct ContinueFrameCommand {u8 pad[0x102];u16 timer,status;s16 slot;u16 phase,palette;};

extern struct ContinueFrameCommand gUnknown_03001800;
extern void sub_0803D450(void);extern void sub_0803D4AC(void);

void sub_0803A310(void);

void sub_0803A310(void) {
struct ContinueFrameCommand *work;struct FrameObject *frame;sub_0803D450();work=&gUnknown_03001800;{s32 slot=work->slot;struct FrameObject *frames=gFrameObjects;frame=&frames[slot];};frame->palette=work->palette;frame->unknown2C[1]=work->status;frame->byte2B=work->timer;frame->unknown23[6]=0x20;frame->unknown2C[2]=work->phase;sub_0803D4AC();}
