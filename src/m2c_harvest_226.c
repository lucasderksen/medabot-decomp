/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"

struct ContinueToggleWork {u8 pad[0x102];s16 slot,xflag,yflag;};

extern struct ContinueToggleWork gUnknown_03001800;
extern void sub_0803D450(void);extern void sub_0803D4AC(void);

void sub_0803AA90(void);

void sub_0803AA90(void) {
sub_0803D450();if(gUnknown_03001800.xflag!=0)gFrameObjects[gUnknown_03001800.slot].flags^=0x1000;if(gUnknown_03001800.yflag!=0)gFrameObjects[gUnknown_03001800.slot].flags^=0x2000;sub_0803D4AC();}
