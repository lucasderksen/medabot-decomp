#ifndef GUARD_STATE0_WORK_H
#define GUARD_STATE0_WORK_H

#include "global.h"

/* Partial observed RAM views. Their bounds are access coverage, not recovered
 * object sizes. The byte aliases in state0_callbacks.h refer to the same RAM. */
union State0TypedWork {
    u8 bytes[0x13A];
    struct { u8 unknown00[0x5C]; u16 word5C; u8 unknown5E[0x28]; u16 word86; } widths;
    struct { u8 unknown00[0x48]; u16 word48; } selection;
    struct { u8 unknown00[0x89]; u8 scripted; u16 seed; u8 value; u8 index; } random;
};
struct State0Bytes4 { u8 byte0, byte1, byte2, byte3; } __attribute__((packed));
struct EquipmentScrollControl {
    u8 selector;
    u8 directions;
    u8 quarterSpeed;
    u8 blendEnabled;
    u8 alphaHigh;
    u8 alphaLow;
    u8 fraction;
    u8 wholeStep;
} __attribute__((packed));
struct SceneFrameWork {
    u8 unknown00[4];
    s16 state;
    u8 unknown06[2];
    s32 count;
    s16 mode;
    u8 unknown0E[0xE2];
    u16 first;
    u16 second;
};
union State0TransferWork {
    u8 bytes[0x1B1];
    struct SceneFrameWork sceneFrame;
    struct { u8 unknown00[4]; u16 word04; u8 unknown06[6]; u16 word0C; u8 unknown0E[2]; u32 word10; } backgroundSetup;
    struct { u8 unknown00[0xC8]; s16 values[3]; u8 unknownCE[3]; u8 flag; } limits;
    struct { u8 unknown00[0x41]; u8 selected[3]; u8 unknown44[0x48]; u8 results[3]; struct State0Bytes4 records[3]; } indexed;
    struct { u8 unknown00[0x1A6]; u16 words1A6[4]; } widths;
    struct {
        u8 unknown00[0x39];
        struct EquipmentScrollControl first;
        u8 unknown41[0x33];
        struct EquipmentScrollControl second;
    } scroll;
};
struct MainSerialOutgoingWork { u32 polledBits; u16 word04; u16 word06; u16 words[4][2]; };
extern union State0TypedWork gState0TypedWork;
extern union State0TransferWork gState0TransferWork;
extern struct MainSerialOutgoingWork gMainSerialOutgoingWork;
struct State0Record8 { u8 unknown00[3]; u8 byte3; u8 byte4; u8 byte5; u8 byte6; u8 byte7; };
extern struct State0Record8 gUnknownRecords_030017A0[];

extern u8 gSetupBuffer_03000590[];
extern u8 gUnknown_0300052E[];
#endif
