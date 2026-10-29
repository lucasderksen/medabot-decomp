/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "display_effects.h"
#include "display_helpers.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedGraphics1A788 {u8 prefix[0x13A];u8 phase;};
struct Continued234A8Frame33 { u8 pad00[0x840]; struct FrameObject frame; };
struct ContinuedF7B8PhaseAA { u8 pad00[0xAA]; u8 phaseAA; };
struct ContinuedFrame398AC {
 u8 prefix[0x102];s16 x,y;
 u8 gap[0x129-0x106];u8 kind;u8 gap2;u8 active;
 u8 tileX,clear,field2,field3;u16 delay;
};
struct Phase636FC { u8 pad00[0x84]; s8 phase; };
struct Context636FC { u8 pad00[0x31]; u8 firstX; u8 secondX; u8 firstY; u8 secondY; u8 pad35[5]; u16 timer; };
struct Dma69F44 { const void *volatile source; void *volatile destination; volatile u32 control; };

extern const u8 *const gState0NextCommands_083B6100[0x41];
extern const u8 gUnknownPalette_0850F358[96];
extern const u8 gUnknown_0807C410[32];
extern const u8 gUnknown_080AFBC4[32];
extern const u8 gUnknown_0848748C[];
extern const u8 gUnknown_084874C0[];
extern const u8 gUnknown_0848761C[];
extern const u8 gUnknown_08487730[];
extern const u8 gUnknown_08487808[];
extern const u8 gUnknown_08487904[];
extern const u8 gUnknown_08487A00[];
extern const u8 gUnknown_08487AD8[];
extern const u8 gUnknown_08487BB0[];
extern const u8 gUnknown_08487C88[];
extern const u8 gUnknown_08488560[32];
extern const u8 gUnknown_08488580[32];
extern const u8 gUnknown_084885A0[32];
extern const u8 gUnknown_084C3E64[];
extern const u8 gUnknown_084C53C8[];
extern const u8 gUnknown_084C571C[];
extern const u8 gUnknown_084C57A8[];
extern const u8 gUnknown_084C5824[];
extern const u8 gUnknown_084C589C[];
extern const u8 gUnknown_084C7FB4[32];
extern const u8 gUnknown_084C7FD4[32];
extern const u8 gUnknown_084C8BD4[];
extern const u8 gUnknown_084C9560[];
extern const u8 gUnknown_084CA064[];
extern const u8 gUnknown_084CADEC[];
extern const u8 gUnknown_084D745C[];
extern const u8 gUnknown_084E3EF0[];
extern const u8 gUnknown_084E41B8[];
extern const u8 gUnknown_084E4498[32];
extern const u8 gUnknown_084E44B8[32];
extern const u8 gUnknown_0850F598[64];
extern const u8 gUnknown_0850F678[32];
extern const u8 gUnknown_0850FD58[0x20];
#include "action_scene_data.h"
extern s32 sub_08062C98(void);
extern u32 sub_0803526C(u32, s32, s32);
extern u8 gUnknown_0202F8A0[32];
extern u8 gUnknown_0202F900[32];
extern u8 gUnknown_0202F920[32];
extern u8 gUnknown_0202F940[32];
extern u8 gUnknown_0202F960[64];
extern u8 gUnknown_0202F9A0[32];
extern u8 gUnknown_0202F9C0[32];
extern u8 gUnknown_0202F9E0[32];
extern u8 gUnknown_0202FB00[32];
extern u8 gUnknown_0202FB40[32];
extern u8 gUnknown_0202FB60[32];
extern u8 gUnknown_0202FB80[32];
extern u8 gUnknown_0202FBA0[32];
extern u8 gUnknown_03001864[4];
extern void sub_0801BCE4(u32,s32,s32);
extern void sub_0801BD1C(const void *,s32,s32);
extern void sub_0803D450(void);
extern void sub_0803D4AC(void);
extern void sub_08062B48(u8, u8, u32);

void sub_08017A7C(u32 arg0, u32 arg1, u32 arg2);
u32 sub_0801A788(u32 value);
void sub_080234A8(void);
void sub_0802F7B8(void);
void sub_080398AC(void);
void sub_080636FC(void);
void sub_08069F44(void);

void sub_08017A7C(u32 arg0, u32 arg1, u32 arg2) {
    s32 var_r6;
    u32 var_r1;
    u32 var_sb;

    if (arg0 <= 2U) {
        var_r1 = arg0;
        var_sb = 0;
    } else {
        var_r1 = arg0 - 3;
        var_sb = 1;
    }
    if (var_r1 == gState0TypedWork.bytes[0x3D]) {
        var_r6 = 0;
        goto block_7;
    }
    if (var_r1 == gState0TypedWork.bytes[0x46]) {
        var_r6 = 1;
block_7:
        sub_08015838(arg0, gUnknown_03001864);
        sub_0804305C((u32) gUnknown_03001864[0], (u32) gUnknown_03001864[1], (u32) gUnknown_03001864[2], (u32) gUnknown_03001864[3], arg0, (var_r6 * 4), arg1, arg2, var_sb, 2U, (var_r6 * 4));
        gFrameObjects[var_r6 * 4 + 1].flags &= 0xFDFF;
        gFrameObjects[var_r6 * 4 + 2].flags &= 0xFDFF;
    }
}

u32 sub_0801A788(u32 value) {

    switch ((u32) ((struct ContinuedGraphics1A788 *)&gState0TypedWork)->phase) { /* irregular */
    case 0:
        LeDecompress(gUnknown_084C571C, (void *)0x06004000);
        LeDecompress(gUnknown_084C57A8, (void *)0x06004140);
        LeDecompress(gUnknown_0848748C, (void *)0x06004200);
        ((struct ContinuedGraphics1A788 *)&gState0TypedWork)->phase++;
        break;
    default:
        return 0U;
    case 1:
        LeDecompress(gUnknown_084C589C, (void *)0x06004300);
        LeDecompress(gUnknown_084C3E64, (void *)0x06004400);
        LeDecompress(gUnknown_084874C0, (void *)0x0600C000);
        LeDecompress(gUnknown_084C5824, (void *)0x0600C600);
        ((struct ContinuedGraphics1A788 *)&gState0TypedWork)->phase++;
        break;
    case 2:
        LeDecompress(gUnknown_08487904, (void *)0x06004E00);
        LeDecompress(gUnknown_08487A00, (void *)0x06005100);
        LeDecompress(gUnknown_08487AD8, (void *)0x06005400);
        LeDecompress(gUnknown_08487BB0, (void *)0x06005700);
        LeDecompress(gUnknown_08487C88, (void *)0x06005A00);
        ((struct ContinuedGraphics1A788 *)&gState0TypedWork)->phase++;
        break;
    case 3:
        LeDecompress(gUnknown_084C53C8, (void *)0x0600C280);
        LeDecompress(gUnknown_084C8BD4, (void *)0x06012000);
        LeDecompress(gUnknown_084CA064, (void *)0x06014E00);
        LeDecompress(gUnknown_084CADEC, (void *)0x06017F80);
        LeDecompress(gMain2SharedObjectTiles_084C8034, (void *)0x06017400);
        ((struct ContinuedGraphics1A788 *)&gState0TypedWork)->phase++;
        break;
    case 4:
        LeDecompress(gUnknown_0848761C, (void *)0x06004600);
        LeDecompress(gUnknown_08487730, (void *)0x06004800);
        LeDecompress(gUnknown_08487808, (void *)0x06004B00);
        ((struct ContinuedGraphics1A788 *)&gState0TypedWork)->phase++;
        break;
    case 5:
        ((struct ContinuedGraphics1A788 *)&gState0TypedWork)->phase++;
        break;
    case 6:
        LeDecompress(gUnknown_084C9560, (void *)0x06013000);
        LeDecompress(gUnknown_084E3EF0, (void *)0x06013C00);
        LeDecompress(gUnknown_084E41B8, (void *)0x06014200);
        ((struct ContinuedGraphics1A788 *)&gState0TypedWork)->phase++;
        break;
    case 7:
        sub_0803EF8C(0x20U, 0x20U, 0U, 0U, (u32) *(u16 *)0x0400000A, 0U);
        ((struct ContinuedGraphics1A788 *)&gState0TypedWork)->phase++;
        break;
    case 8:
        if (value == 0) {
            sub_0803EF8C(0x20U, 0x20U, 0U, 0U, (u32) *(u16 *)0x04000008, value);
            sub_08043C08((u32) gState0TransferWork.bytes[0x38], 1U);
            CpuFastSet(gUnknown_084C7FB4, gUnknown_0202FB00, 8U);
            CpuFastSet(gUnknown_08488560, gUnknown_0202FB40, 8U);
            CpuFastSet(gUnknown_084885A0, gUnknown_0202FB60, 8U);
            CpuFastSet(gUnknown_08488580, gUnknown_0202FB80, 8U);
            CpuFastSet(gUnknown_084C7FD4, gUnknown_0202FBA0, 8U);
            CpuFastSet(gUnknown_084E4498, gUnknown_0202F900, 8U);
            CpuFastSet(gUnknown_084E44B8, gUnknown_0202F920, 8U);
            CpuFastSet(gState0Palette_084E44D8, gUnknown_0202F940, 8U);
            CpuFastSet(gUnknown_0850F598, gUnknown_0202F960, 0x10U);
            CpuFastSet(gUnknownPalette_0850F358, gUnknown_0202F9A0, 8U);
            CpuFastSet(gUnknownPalette_0850F358 + 0x20, gUnknown_0202F9C0, 8U);
            CpuFastSet(gUnknownPalette_0850F358 + 0x40, gUnknown_0202F9E0, 8U);
            CpuFastSet(gUnknown_0850F678, gUnknown_0202F8A0, 8U);
        } else {
            sub_08043C08((u32) gState0TransferWork.bytes[0x38], 0U);
            CpuFastSet(gUnknown_084C7FB4, (void *)0x05000100, 8U);
            CpuFastSet(gUnknown_08488560, (void *)0x05000140, 8U);
            CpuFastSet(gUnknown_084885A0, (void *)0x05000160, 8U);
            CpuFastSet(gUnknown_08488580, (void *)0x05000180, 8U);
            CpuFastSet(gUnknown_084C7FD4, (void *)0x050001A0, 8U);
            CpuFastSet(gUnknown_084E4498, (void *)0x05000300, 8U);
            CpuFastSet(gUnknown_084E44B8, (void *)0x05000320, 8U);
            CpuFastSet(gState0Palette_084E44D8, (void *)0x05000340, 8U);
            CpuFastSet(gUnknown_0850F598, (void *)0x05000360, 0x10U);
            CpuFastSet(gUnknownPalette_0850F358, (void *)0x050003A0, 8U);
            CpuFastSet(gUnknownPalette_0850F358 + 0x20, (void *)0x050003C0, 8U);
            CpuFastSet(gUnknownPalette_0850F358 + 0x40, (void *)0x050003E0, 8U);
            CpuFastSet(gUnknown_0850F678, (void *)0x050002A0, 8U);
        }
        ((struct ContinuedGraphics1A788 *)&gState0TypedWork)->phase = 0U;
        return 1U;
    }
    return 0;
}

void sub_080234A8(void) {
 struct Continued234A8Frame33 *frames;
 u8 *work;
 u32 zero;
 LeDecompress(gUnknown_084D745C, (void *)0x06014800);
 CpuFastSet(gUnknown_0850FD58, (void *)0x050002E0, 8u);
 frames = (struct Continued234A8Frame33 *)&gFrameObjects;
 frames->frame.flags = (zero = 0, 0xC404);
 frames->frame.tableSelector = zero;
 work = gState0TransferWork.bytes;
 frames->frame.screenX = (u16)gFrameObjects[work[0x87] * 4 + 0x5D].screenX;
 frames->frame.screenY = (u16)gFrameObjects[work[0x87] * 4 + 0x5D].screenY - 4;
 frames->frame.palette = 7;
 frames->frame.priority = 0xF0;
 sub_08040B90(gState0NextCommands_083B6100[0x40], 0x21);
 sub_08074DE0(0x4D);
 work[0xAA]++;
}

void sub_0802F7B8(void) {
 s32 completed = 0;
 s32 selectedCount = 0;
 u32 slot = 0;
 u8 *work = gState0TransferWork.bytes;
 u8 *bank = work + 0x60;
 do {
  u8 *selected = work + 0xD2;
  if (*(u8 *)(slot + (u32)selected) != 0) {
   u32 index;
   struct FrameObject *frames;
   u16 y;
   selectedCount++;
   index = slot + 0x21;
   frames = gFrameObjects;
   y = (u16)gFrameObjects[(*bank + slot) * 4 + 0x5D].screenY;
   if (sub_0803526C(index, (s16)(y - 4), (s16)(y + 0x10)) != 0) {
    struct FrameObject *frame = &frames[index];
    frame->unknown23[4] = 0;
    frame->unknown23[5] = 0;
    frame->unknown23[6] = 1;
    completed++;
   }
  }
  slot++;
 } while (slot <= 2u);
 if (completed == selectedCount) {
  gState0TypedWork.widths.word86 = 0x3C;
  ((struct ContinuedF7B8PhaseAA *)&gState0TransferWork)->phaseAA++;
 }
}

void sub_080398AC(void) {
 u8 *setup,*work,*initialWork;struct ContinuedFrame398AC *frames;
 s32 offset;u32 value;u8 *record;
 sub_0803D450();
 setup=gSetupBuffer_03000590;initialWork=gState0TransferWork.bytes;
 offset=initialWork[0x87]<<8;record=setup+offset;
 if(*(u8*)(record+0xDD)<=3U)
  value=setup[initialWork[0xA7]*0x18+offset+0x49];
 else value=*(u8*)(record+0xA8)+0x50;
 sub_0801BCE4(value,*(s16*)((work=gState0TransferWork.bytes)+0x10A),9);
 frames=(void*)gFrameObjects;
 frames->field2=*(u16*)(work+0x102);
 frames->field3=*(u16*)(work+0x104);
 frames->active=*(u16*)(work+0x10E);
 frames->delay=*(u16*)(work+0x10C);
 frames->kind=0x10;
 sub_0801BD1C(gUnknown_083CEDF4[frames->active],0,0);
 frames->y=*(u16*)(work+0x108);
 if(!(2&work[0xF8])) {
  frames->x=*(u16*)(work+0x106);
  frames->tileX=*(u16*)(work+0x110);
 }else {
  u32 half=(u8)frames->field2>>1;
  frames->x=(0x1E - half)-(*(u16*)(work+0x106)+half);
  frames->tileX=work[0x110]+2;
 }
 ((struct ContinuedFrame398AC*)gFrameObjects)->clear=0;
 sub_0803D4AC();
}

void sub_080636FC(void) {
    if ((u32)(u8)((struct Phase636FC *)&gState0TypedWork)->phase <= 0x40) {
        sub_0803F998(0x7FFF, 0x20 - ((u8)((struct Phase636FC *)&gState0TypedWork)->phase >> 1), 0xFF);
        ++((struct Phase636FC *)&gState0TypedWork)->phase;
    } else {
        CpuFastSet(gUnknown_080AFBC4, (void *)0x05000300, 8);
        CpuFastSet(gUnknown_080AFBC4, gUnknown_0202F900, 8);
        ((struct Phase636FC *)&gState0TypedWork)->phase = 0;
        ++gUnknown_0300137C;
        ((struct Context636FC *)gMainContextPointer_03006F74)->timer = 0x280;
    }
    sub_08062B48(((struct Context636FC *)gMainContextPointer_03006F74)->firstX, ((struct Context636FC *)gMainContextPointer_03006F74)->firstY, 0);
    sub_08062B48(((struct Context636FC *)gMainContextPointer_03006F74)->secondX, ((struct Context636FC *)gMainContextPointer_03006F74)->secondY, 1);
    sub_08062C98();
}

void sub_08069F44(void) {
    struct FrameObject *frames;
    struct Dma69F44 *dma;
    u32 zero;
    s16 screenY;
    u8 *cursor;
    sub_08048864(2, 0xCB20, 0x108, 2, 3);
    frames = gFrameObjects;
    cursor = (u8 *)frames + 0x84;
    zero = 0;
    screenY = 0xC8;
    *(u16 *)cursor = screenY;
    cursor += 4;
    *cursor = 0x88;
    ++cursor;
    *cursor = 0x88;
    cursor += 0xF;
    *(u16 *)cursor = zero;
    cursor += 2;
    *(u16 *)cursor = zero;
    sub_08048864(3, 0xCB20, 0x109, 2, 3);
    cursor = (u8 *)frames + 0xC4;
    *(u16 *)cursor = screenY;
    cursor += 4;
    *cursor = 0x88;
    ++cursor;
    *cursor = 0x88;
    cursor += 0xF;
    *(u16 *)cursor = zero;
    cursor += 2;
    *(u16 *)cursor = zero;
    sub_08048864(4, 0xCB20, 0x10A, 2, 3);
    *(u16 *)((u8 *)frames + 0x104) = screenY;
    *((u8 *)frames + 0x108) = 0x88;
    *((u8 *)frames + 0x109) = 0x88;
    *(u16 *)((u8 *)frames + 0x118) = zero;
    *(u16 *)((u8 *)frames + 0x11A) = zero;
    dma = (struct Dma69F44 *)0x040000D4;
    dma->source = gUnknown_0807C410;
    dma->destination = (void *)0x05000240;
    dma->control = 0x84000008U;
    (void)dma->control;
}
