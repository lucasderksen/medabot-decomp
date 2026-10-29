/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "gba.h"
#include "input.h"
#include "interrupts.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "render_work.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ContinuedSetup1B700 {u8 prefix[0x40];u8 active;u8 tail[0xBF];};
struct ContinuedFADCText { const void *entries[0x6A]; };
struct ContinuedFADCWork { u8 pad00[0xAA]; u8 phaseAA; u8 padAB[0xB4]; u8 first15F; u8 second160; };
struct ContinuedFADCControl { u8 pad00[0x84]; u8 counter84; };
struct ContinuedSetup22F50 {u8 prefix[0x40];u8 active;u8 gap41[0x18];u8 equipped;u8 gap5A[0x60];u8 status;u8 tail[0x45];};
struct ContinuedDD4Work { u8 pad00[0x51]; u8 byte51; u8 byte52; u8 pad53[0x11]; u8 byte64; u8 pad65[0x22]; u8 byte87; u8 pad88[0x22]; u8 phaseAA; };
struct ContinuedDD4FrameView { u8 pad00[0x840]; union { struct FrameObject frame; struct { u8 pad00[0x30]; u16 sourceX30; s16 sourceY32; } source; } object; };
struct ContinuedSetup29600 {u8 prefix[0x40];u8 active;u8 gap41[0x18];u8 equipped;u8 gap5A[0x6F];u8 mode;u8 tail[0x36];};
struct ContinuedSetup32DA0 {u8 prefix[6];u8 type;u8 unknown07[0x39];u8 active;u8 gap41[0x79];u8 mode;u8 tail[0x45];};
struct Graphics6BD70 {u8 pad00[8];s32 transferCount;s8 first;s8 second;u8 progress;u8 pad0F[0x35];s32 total;};


extern const u8 gUnknown_083AD553[32];
extern const u8 gUnknown_083AD573[6];
extern const u8 gUnknown_084CA064[];
extern const u8 gUnknown_084E4598[32];
extern const void *const gState0NextText_083B4C60[0x6A];
extern struct Graphics6BD70 gGraphicsCounter6BD7003001800;
extern u32 sub_08032FD0(u32, u32);
extern u32 sub_08032FFC(void);
extern u32 sub_0803301C(void);
extern u32 sub_080330E8(u32);
extern u8 gUnknown_030004C9;
extern void sub_0801B5FC(u32);
extern void sub_0801BB7C(void);
extern void sub_08033154(u32, u32);
extern void sub_08036CCC(u32,u32,s32);
extern void sub_0803836C(void);
extern void sub_0806B718(u8);

u32 sub_0801B700(s32 excluded);
void sub_0801FADC(void);
void sub_08022F50(void);
void sub_08025DD4(void);
void sub_08029600(void);
void sub_08030890(void);
void sub_08032640(void);
s32 sub_0806B3D8(u32 inputIndex);
s32 sub_0806BD70(void);

u32 sub_0801B700(s32 excluded) {
    s32 index=sub_080424B8()&0x1F;
    u32 attempts=0;
    u8 selected;
    u8 mode=gUnknown_030004C9;
    struct ContinuedSetup1B700 *setup=(struct ContinuedSetup1B700 *)gSetupBuffer_03000590;
    do {
        selected=gUnknown_083AD553[index];
        if(mode==1 && gUnknown_03000B90!=0)selected=gUnknown_083AD573[selected];
        if(setup[selected].active!=0 && excluded!=selected)return selected;
        index=(index+1)&0x1F;
        attempts++;
    } while(attempts<=5);
    return 0;
}

void sub_0801FADC(void) {
 struct ContinuedFADCWork *work;
 struct ContinuedFADCControl *control;
 const void *const *text;
 const struct ContinuedFADCText *table;
 u8 *counter;
 u32 first;
 u32 firstLine;
 u32 zero;
 sub_08035DE8();
 first = sub_080361C4();
 work = (struct ContinuedFADCWork *)&gState0TransferWork;
 work->first15F = first;
 zero = 0;
 work->second160 = sub_08036218();
 control = (struct ContinuedFADCControl *)&gState0TypedWork;
 counter = &control->counter84;
 firstLine = *counter;
 table = (const struct ContinuedFADCText *)gState0NextText_083B4C60;
 text = &table->entries[0x69];
 sub_0803F15C(0x1E, 1, 0, firstLine, *text, *(volatile u16 *)0x04000008, zero);
 sub_0803F15C(0x1E, 1, 0, 0x13 - *counter, *text, *(volatile u16 *)0x04000008, zero);
 if (*counter == 9) {
  u32 clear = 0x200;
  CpuFastSet(&clear, gRenderWork->objects, 0x01000100u);
  gRenderWork->byte1094 = zero;
  gRenderWork->byte1095 = zero;
  gUnknownCallback_030017F0 = DummyInterruptHandler;
  work->phaseAA++;
 } else {
  (*counter)++;
 }
}

void sub_08022F50(void) {
    struct ContinuedSetup22F50 *setup=(struct ContinuedSetup22F50 *)gSetupBuffer_03000590;
    u8 *work=gState0TransferWork.bytes;
    u8 *bank=work+0x88;
    setup[*bank].active=3;
    sub_08036CCC(*bank,0,*(s16 *)(work+0xEC));
    setup[*bank].equipped=*(u16 *)(work+0xC8);
    setup[*bank].status=1;
    sub_080158F8();
    sub_0801A0D0();
    work[0xAA]++;
}

void sub_08025DD4(void) {
 struct ContinuedDD4Work *work;
 u8 *bank;
 u32 incoming;
 struct ContinuedDD4FrameView *frames;
 u16 halfZero;
 u32 zero;
 work = (struct ContinuedDD4Work *)&gState0TransferWork;
 incoming = work->byte64;
 bank = &work->byte87;
 *bank = (halfZero = 0, incoming);
 work->byte51 = work->byte52;
 frames = (struct ContinuedDD4FrameView *)&gFrameObjects;
 frames->object.frame.flags |= 0x220;
 zero = 0;
 frames->object.frame.scaleX = 0x40;
 frames->object.frame.scaleY = 0x40;
 frames->object.frame.angle = halfZero;
 frames->object.frame.palette = 7;
 frames->object.source.sourceX30 = (u16)gFrameObjects[*bank * 4 + 0x5D].screenX;
 frames->object.source.sourceY32 = (u16)gFrameObjects[*bank * 4 + 0x5D].screenY - 4;
 frames->object.frame.unknown23[1] = 6;
 frames->object.frame.unknown23[0] = zero;
 work->phaseAA++;
}

void sub_08029600(void) {
    s32 found=0;
    struct ContinuedSetup29600 *setup;
    struct ContinuedSetup29600 *row;
    u32 i;
    sub_0803836C();
    gState0TransferWork.bytes[0x60]=sub_08032FC4(gState0TransferWork.bytes[0x87]);
    i=0;
    setup=(struct ContinuedSetup29600 *)gSetupBuffer_03000590;
    do {
        row=(struct ContinuedSetup29600 *)(((gState0TransferWork.bytes[0x60]+i)<<8)+(u32)setup);
        if(row->active && row->equipped && row->mode) {
            found=1;
            *(i+(gState0TransferWork.bytes+0xD2))=1;
        }
        i++;
    } while(i<=2);
    if(found==0)gState0TransferWork.bytes[0xAA]++;
    else gState0TransferWork.bytes[0xAA]+=2;
}

void sub_08030890(void) {
    switch(gState0TypedWork.bytes[0x139]) {
    case 0:
        sub_0801B5FC(gState0TransferWork.bytes[0x87]);
        sub_0801BB7C();
        gState0TypedWork.bytes[0x139]++;
        break;
    case 1:
        LeDecompress(gUnknown_084CA064,(void *)0x06014E00);
        gState0TypedWork.bytes[0x139]++;
        break;
    case 2:
        CpuFastSet(gUnknown_084E4598,(void *)0x050002C0,8);
        gUnknown_0300137C++;
        gState0TypedWork.bytes[0x139]=0;
        break;
    default:break;
    }
}

void sub_08032640(void) {
    struct ContinuedSetup32DA0 *setup;
    struct ContinuedSetup32DA0 *secondSetup;
    struct ContinuedSetup32DA0 *finalSetup;
    u32 var_r6,finalScanValue;

    gState0TransferWork.bytes[0x60] = (u8) sub_08032FC4((u32) gState0TransferWork.bytes[0x5C]);
    var_r6 = 0;
    setup=(struct ContinuedSetup32DA0 *)gSetupBuffer_03000590;
    do {
        if ((setup[gState0TransferWork.bytes[0x60]].mode == 2) && (sub_08032FD0(gState0TransferWork.bytes[0x60], setup[gState0TransferWork.bytes[0x5C]].type) != 0)) {
            *(var_r6 + (gState0TransferWork.bytes + 0x61)) = gState0TransferWork.bytes[0x60] + 1;
        }
        gState0TransferWork.bytes[0x60] = (u8) (gState0TransferWork.bytes[0x60] + 1);
        var_r6 += 1;
    } while (var_r6 <= 2U);
    if (sub_08032FFC() != 0) {
        gState0TransferWork.bytes[0x5E]=sub_0803301C()+1;
    } else {
        gState0TransferWork.bytes[0x60] = (u8) sub_08032FC4((u32) gState0TransferWork.bytes[0x5C]);
        var_r6 = 0;
    secondSetup=(struct ContinuedSetup32DA0 *)gSetupBuffer_03000590;
        do {
            if ((secondSetup[gState0TransferWork.bytes[0x60]].mode == 2)) {
                *(var_r6 + (gState0TransferWork.bytes + 0x61)) = gState0TransferWork.bytes[0x60] + 1;
            }
            gState0TransferWork.bytes[0x60] = (u8) (gState0TransferWork.bytes[0x60] + 1);
            var_r6 += 1;
        } while (var_r6 <= 2U);
        if (sub_08032FFC() != 0) {
            gState0TransferWork.bytes[0x5E]=sub_0803301C()+1;
        } else {
            gState0TransferWork.bytes[0x60] = (u8) sub_08032FC4((u32) gState0TransferWork.bytes[0x5C]);
            var_r6 = 0;
            do {
                finalScanValue=gState0TransferWork.bytes[0x60];
                finalSetup=(struct ContinuedSetup32DA0 *)gSetupBuffer_03000590;
                if ((sub_08032FD0(finalScanValue, finalSetup[gState0TransferWork.bytes[0x5C]].type) != 0)) {
                    *(var_r6 + (gState0TransferWork.bytes + 0x61)) = gState0TransferWork.bytes[0x60] + 1;
                }
                gState0TransferWork.bytes[0x60] = (u8) (gState0TransferWork.bytes[0x60] + 1);
                var_r6 += 1;
            } while (var_r6 <= 2U);
            if (sub_08032FFC() != 0) {
                gState0TransferWork.bytes[0x5E]=sub_0803301C()+1;
            } else {
                gState0TransferWork.bytes[0x60] = (u8) sub_08032FC4((u32) gState0TransferWork.bytes[0x5C]);
                gState0TransferWork.bytes[0x5E]=sub_08033090(gState0TransferWork.bytes[0x60])+1;
            }
        }
    }
    sub_08033154(gState0TransferWork.bytes[0x5C], *((gState0TransferWork.bytes + 0x5F) - 2));
}

s32 sub_0806B3D8(u32 inputIndex) {
    u8 slot = (u8)inputIndex;
    struct FrameObject *base = gFrameObjects;
    struct FrameObject *frame = base + slot;
    u16 count = frame->unknown1A;
    u32 phase = (count + 16) & 63;
    u32 initialY = (u16)frame->screenY;
    if (frame->screenY > 96) {
        frame->screenY = 200;
        return 0;
    }
    if (count & 1)
        frame->screenY = initialY + 1;
    if (phase & 16) {
        if (frame->unknown1A & 1) {
            if (!(slot & 1))
                frame->screenX = (u16)frame->screenX - 1;
            else
                frame->screenX = (u16)frame->screenX + 1;
        }
    } else if (frame->unknown1A & 1) {
        if (slot & 1)
            frame->screenX = (u16)frame->screenX - 1;
        else
            frame->screenX = (u16)frame->screenX + 1;
    }
    frame = &gFrameObjects[slot];
    if (frame->unknown1A & 8)
        frame->flags |= 0x1000;
    else
        frame->flags &= 0xEFFF;
    return 1;
}

s32 sub_0806BD70(void) {
    u32 next;
    u16 elapsed;
    switch ((u32)gFrameObjects[0].commandDelay) {
    case 0:
        sub_08048864(0, 0xCA00, 0x2E, 10, 3);
        gFrameObjects[0].screenX = 120;
        gFrameObjects[0].screenY = 80;
        gFrameObjects[0].unknown1A = 0;
        gFrameObjects[0].scaleX = 4;
        gFrameObjects[0].scaleY = 4;
        gFrameObjects[0].commandDelay++;
        break;
    case 1:
        elapsed = gFrameObjects[0].unknown1A;
        if (elapsed > 23) {
            next = elapsed + 1;
            gFrameObjects[0].unknown1A = next;
            if ((u16)next > 180 || (*(u8 *)&gNewKeys & 9)) {
                gFrameObjects[0].unknown1A = 0;
                gFrameObjects[0].commandDelay++;
            }
        } else {
            gFrameObjects[0].unknown1A++;
        }
        break;
    case 2:
        if (gFrameObjects[0].unknown1A <= 23) {
            gFrameObjects[0].unknown1A++;
        } else {
            gFrameObjects[0].unknown1A = 0;
            gFrameObjects[0].screenY = 200;
            gFrameObjects[0].commandDelay++;
        }
        break;
    case 3:
        if (gGraphicsCounter6BD7003001800.first == (s8)gGraphicsCounter6BD7003001800.progress) {
            sub_08048864(0,0xCA08,0x2F,11,3);
            gFrameObjects[0].screenX = 120;
            gFrameObjects[0].screenY = 80;
            gFrameObjects[0].scaleX = 0;
            gFrameObjects[0].scaleY = 96;
            gFrameObjects[0].unknown1A = 0;
            gFrameObjects[0].commandDelay++;
            *(volatile u16 *)0x04000050 = 0x840;
            *(volatile u16 *)0x04000052 = 0x10;
        } else {
            gGraphicsCounter6BD7003001800.progress++;
        }
        break;
    case 4:
    case 5:
    case 6:
        if (gFrameObjects[0].unknown1A == 0)
            sub_08074DE0(24);
        next = gFrameObjects[0].unknown1A + 1;
        gFrameObjects[0].unknown1A = next;
        if ((u16)next > 60) {
            gFrameObjects[0].frameAndGroup++;
            gFrameObjects[0].unknown1A = 0;
            gFrameObjects[0].commandDelay++;
        }
        break;
    case 7:
        if (gFrameObjects[0].unknown1A == 0)
            sub_08074DE0(7);
        next = gFrameObjects[0].unknown1A + 1;
        gFrameObjects[0].unknown1A = next;
        if ((u16)next > 30) {
            sub_0806B718(0);
            gGraphicsCounter6BD7003001800.transferCount = 0;
            gGraphicsCounter6BD7003001800.total = gGraphicsCounter6BD7003001800.first + gGraphicsCounter6BD7003001800.second;
            *(volatile u16 *)0x04000050 = 0x840;
            *(volatile u16 *)0x04000052 = 0x808;
            return 1;
        }
        break;
    }
    return 0;
}
