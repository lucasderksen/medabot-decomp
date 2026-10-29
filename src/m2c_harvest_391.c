/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "frame.h"
#include "serial.h"
#include "state0_work.h"

struct SoundDispatchNode73094 {
    /* Observed sound-node stride: 0x74 bytes. */
    void *prev;
    struct SoundDispatchNode73094 *next;
    u8 pad08[12];
    s32 active14;
    u8 pad18[0x38];
    u8 byte50, kind51;
    u8 pad52[0x11];
    u8 mode63;
    u8 pad64[0x10];
};
struct SoundDispatchWork73094 {
    /* 080723AC clears 0x1CD words in this caller-owned work object. */
    struct SoundDispatchNode73094 nodes[13];
    struct SoundDispatchNode73094 *head5E4;
    u8 pad5E8[0x144];
    u8 flags72C;
    u8 pad72D[7];
};
struct Buffer7424C { u8 bytes[48]; u8 cursor; };
struct Work7424C {
    u8 pad00[8];
    struct Buffer7424C *buffer;
    u8 pad0C[0x3C];
    u16 value48;
    u8 pad4A[0x1C];
    u8 flag66;
};
typedef char SoundNodeSize73094[sizeof(struct SoundDispatchNode73094)==0x74?1:-1];
typedef char SoundWorkSize73094[sizeof(struct SoundDispatchWork73094)==0x734?1:-1];

extern s32 sub_08074540(void);
extern struct SoundDispatchWork73094 *gSoundDispatchRoot73094;
extern void sub_08073058(void *);
extern void sub_080736A0(void *);
extern void sub_08073718(void *);
extern void sub_08073784(void *);
extern void sub_080737E8(void *);
extern void sub_080739C4(s32);
extern void sub_080739DC(s32);
extern void sub_080739F4(void);
extern void sub_0807424C(struct Work7424C *);

void sub_08073094(void);

void sub_08073094(void) {

    u8 kind;
    void *firstChannel;
    void *secondChannel;
    void *thirdChannel;
    void *fifthChannel;
    void *sixthChannel;
    u8 *nextNode;
    void *fourthChannel;
    u8 *cursor;

    cursor = (u8 *)gSoundDispatchRoot73094->head5E4;
    if (cursor != 0) {
        do {
            nextNode = (u8 *)((struct SoundDispatchNode73094 *)cursor)->next;
            if (2 & gSoundDispatchRoot73094->flags72C) {
                kind = ((struct SoundDispatchNode73094 *)cursor)->kind51;
                switch (kind) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 8:
                case 9:
                case 12:
                    break;
                default:
                case 4:
                case 5:
                case 6:
                case 7:
                case 10:
                case 11:
                    sub_08073058(cursor);
                    break;
                }
            } else {
                sub_08073058(cursor);
            }
            cursor = nextNode;
        } while (cursor != (u8 *)gSoundDispatchRoot73094->head5E4);
    }
    /* Reuse the traversal cursor for the captured work root. */
    cursor = (u8 *)gSoundDispatchRoot73094;
    firstChannel = cursor + 0x1D0;
    if (((struct SoundDispatchNode73094 *)firstChannel)->active14 != 0) {
        sub_080736A0(firstChannel);
    } else if (sub_08074540() == 0) {
        sub_080736A0(cursor);
    }
    secondChannel = cursor + 0x244;
    if (((struct SoundDispatchNode73094 *)secondChannel)->active14 != 0) {
        sub_08073718(secondChannel);
    } else if (sub_08074540() == 0) {
        sub_08073718(cursor + 0x74);
    }
    thirdChannel = cursor + 0x2B8;
    if (((struct SoundDispatchNode73094 *)thirdChannel)->active14 != 0) {
        sub_08073784(thirdChannel);
    } else if (sub_08074540() == 0) {
        sub_08073784(cursor + 0xE8);
    }
    fourthChannel = cursor + 0x32C;
    if (((struct SoundDispatchNode73094 *)fourthChannel)->active14 != 0) goto dispatchFourth;
    if (sub_08074540() != 0) goto afterFourth;
    fourthChannel = cursor + 0x570;
    if (((struct SoundDispatchNode73094 *)fourthChannel)->active14 == 0) goto fallbackFourth;
    if (((struct SoundDispatchNode73094 *)(cursor + 0x414))->active14 == 0) goto fallbackFourth;
    if (((struct SoundDispatchNode73094 *)(cursor + 0x414))->mode63 != 2) goto fallbackFourth;
    if (((struct SoundDispatchNode73094 *)(cursor + 0x4FC))->active14 == 0) goto fallbackFourth;
dispatchFourth:
    sub_080737E8(fourthChannel);
    goto afterFourth;
fallbackFourth:
    sub_080737E8(cursor + 0x15C);
afterFourth:;
    fifthChannel = cursor + 0x488;
    if (((struct SoundDispatchNode73094 *)fifthChannel)->active14 != 0) {
        sub_080739C4((s32)(u32)(fifthChannel));
    } else if (sub_08074540() == 0) {
        sub_080739C4((s32)(u32)(cursor + 0x3A0));
    }
    sixthChannel = cursor + 0x4FC;
    if (((struct SoundDispatchNode73094 *)sixthChannel)->active14 != 0) {
        sub_080739DC((s32)(u32)(sixthChannel));
    } else if (sub_08074540() == 0) {
        sub_080739DC((s32)(u32)(cursor + 0x414));
    }
    if (sub_08074540() == 0) {
        sub_0807424C((void *)cursor);
        sub_0807424C((void *)cursor + 0x74);
        sub_0807424C((void *)cursor + 0xE8);
    }
    sub_080739F4();
}
