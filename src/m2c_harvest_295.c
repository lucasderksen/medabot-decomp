/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_float_progress.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_work.h"
#include "tile_text.h"

struct NativeFrame2FE78 {u16 flags;s16 x,y;u16 group;u8 scaleX,scaleY,palette,priority;u8 pad0C[16];u8 command;u8 pad1D[35];};
struct WholeFrames2FE78 {u8 prefix[0x840];struct NativeFrame2FE78 first,second,third,fourth;};
struct NativeTransfer2FE78 {u8 pad00[0x87];u8 selection;u8 pad88[0x22];u8 phase;u8 padAB[0x4D];u8 directions;};

extern const u8 gUnknown_084E3444[];
extern const u8 gUnknown_084E4658[32];
extern const u8 gUnknown_085104B8[32];
extern struct NativeTransfer2FE78 gTransferPrefix2FE78;
extern struct WholeFrames2FE78 gFramesPrefix2FE78;

void sub_0802FE78(void);

void sub_0802FE78(void) {

 LeDecompress(gUnknown_084E3444,(void*)0x06014800);
 CpuFastSet(gUnknown_085104B8,(void*)0x050002C0,8);
 CpuFastSet(gUnknown_084E4658,(void*)0x050002E0,8);
 {
 struct WholeFrames2FE78 *view=&gFramesPrefix2FE78;
 struct NativeTransfer2FE78 *work;
 const u8 *selected;
 u32 frameRoot,sourceAddress,y;
 struct NativeFrame2FE78 *source;
 view->first.flags=0xC404;
 view->first.command=0;
 work=&gTransferPrefix2FE78;
 selected=&work->selection;
 frameRoot=(u32)view;
 sourceAddress=(u32)*selected<<8;
 sourceAddress+=0x1740;
 sourceAddress+=frameRoot;
 source=(struct NativeFrame2FE78*)sourceAddress;
 y=(u16)source->y;
 view->first.y=y-0x1C;
 view->first.palette=6;
 view->first.priority=0xF0;
 view->first.group=0x8400;
 if(!(1&work->directions)) {
 sourceAddress=(u32)*selected<<8;
 sourceAddress+=0x1740;
 sourceAddress+=frameRoot;
 source=(struct NativeFrame2FE78*)sourceAddress;
 view->first.x=(u16)source->x- 0x18;
 } else {
 sourceAddress=(u32)*selected<<8;
 sourceAddress+=0x1740;
 sourceAddress+=frameRoot;
 source=(struct NativeFrame2FE78*)sourceAddress;
 view->first.x=(u16)source->x+ 0x18;
 }
 }
 {
 struct WholeFrames2FE78 *view=&gFramesPrefix2FE78;
 struct NativeTransfer2FE78 *work;
 const u8 *selected;
 u32 frameRoot,sourceAddress,y;
 struct NativeFrame2FE78 *source;
 view->second.flags=0xC404;
 view->second.command=0;
 work=&gTransferPrefix2FE78;
 selected=&work->selection;
 frameRoot=(u32)view;
 sourceAddress=(u32)*selected<<8;
 sourceAddress+=0x1740;
 sourceAddress+=frameRoot;
 source=(struct NativeFrame2FE78*)sourceAddress;
 y=(u16)source->y;
 view->second.y=y-0x1C;
 view->second.palette=6;
 view->second.priority=0xF0;
 view->second.group=0x8401;
 if(!(1&work->directions)) {
 sourceAddress=(u32)*selected<<8;
 sourceAddress+=0x1740;
 sourceAddress+=frameRoot;
 source=(struct NativeFrame2FE78*)sourceAddress;
 view->second.x=(u16)source->x- 0x18;
 } else {
 sourceAddress=(u32)*selected<<8;
 sourceAddress+=0x1740;
 sourceAddress+=frameRoot;
 source=(struct NativeFrame2FE78*)sourceAddress;
 view->second.x=(u16)source->x+ 0x18;
 }
 }
 {
 struct WholeFrames2FE78 *view=&gFramesPrefix2FE78;
 struct NativeTransfer2FE78 *work;
 const u8 *selected;
 u32 frameRoot,sourceAddress,y;
 struct NativeFrame2FE78 *source;
 view->third.flags=0xC404;
 view->third.command=0;
 work=&gTransferPrefix2FE78;
 selected=&work->selection;
 frameRoot=(u32)view;
 sourceAddress=(u32)*selected<<8;
 sourceAddress+=0x1740;
 sourceAddress+=frameRoot;
 source=(struct NativeFrame2FE78*)sourceAddress;
 y=(u16)source->y;
 view->third.y=y-0x1C;
 view->third.palette=7;
 view->third.priority=0xF1;
 view->third.group=0x8402;
 if(!(1&work->directions)) {
 sourceAddress=(u32)*selected<<8;
 sourceAddress+=0x1740;
 sourceAddress+=frameRoot;
 source=(struct NativeFrame2FE78*)sourceAddress;
 view->third.x=(u16)source->x+ 0x18;
 } else {
 sourceAddress=(u32)*selected<<8;
 sourceAddress+=0x1740;
 sourceAddress+=frameRoot;
 source=(struct NativeFrame2FE78*)sourceAddress;
 view->third.x=(u16)source->x- 0x18;
 view->third.flags|=0x1000;
 }
 }
 {
 struct WholeFrames2FE78 *view=&gFramesPrefix2FE78;
 struct NativeTransfer2FE78 *work;
 const u8 *selected;
 u32 frameRoot,sourceAddress,y;
 struct NativeFrame2FE78 *source;
 view->fourth.flags=0xC404;
 view->fourth.command=0;
 work=&gTransferPrefix2FE78;
 selected=&work->selection;
 frameRoot=(u32)view;
 sourceAddress=(u32)*selected<<8;
 sourceAddress+=0x1740;
 sourceAddress+=frameRoot;
 source=(struct NativeFrame2FE78*)sourceAddress;
 y=(u16)source->y;
 view->fourth.y=y-0x1C;
 view->fourth.palette=7;
 view->fourth.priority=0xF1;
 view->fourth.group=0x8403;
 if(!(1&work->directions)) {
 sourceAddress=(u32)*selected<<8;
 sourceAddress+=0x1740;
 sourceAddress+=frameRoot;
 source=(struct NativeFrame2FE78*)sourceAddress;
 view->fourth.x=(u16)source->x+ 0x18;
 } else {
 sourceAddress=(u32)*selected<<8;
 sourceAddress+=0x1740;
 sourceAddress+=frameRoot;
 source=(struct NativeFrame2FE78*)sourceAddress;
 view->fourth.x=(u16)source->x- 0x18;
 view->fourth.flags|=0x1000;
 }
 }
 gState0TypedWork.widths.word86=0;
 sub_08074DE0(0x2B);
 gTransferPrefix2FE78.phase++;
}
