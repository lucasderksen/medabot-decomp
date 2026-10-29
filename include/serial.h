#ifndef GUARD_SERIAL_H
#define GUARD_SERIAL_H

#include "global.h"

/* Names describe byte-level observations, rather than recovered game symbols. */
struct SerialPacket
{
    u8 sequence;               /* 00 */
    u8 linkBits;               /* 01 */
    u16 checksum;              /* 02 */
    u32 payload;               /* 04 */
    u32 unknown08;             /* 08; not sent by the observed four-word transfer */
};

struct SerialContext
{
    u8 masterFlag;             /* 00; tested against 8 */
    u8 phase;                  /* 01 */
    u8 rememberedBits;         /* 02 */
    u8 validBits;              /* 03 */
    u8 sendReady;              /* 04 */
    u8 receiveReady;           /* 05 */
    u8 requestFlag;            /* 06 */
    u8 errorBit;               /* 07 */
    u8 unknown08[3];           /* 08 */
    u8 sequence;               /* 0B */
    u8 unknown0C[8];           /* 0C */
    s32 sendPosition;          /* 14 */
    s32 receivePosition;       /* 18 */
    struct SerialPacket *pendingSend;      /* 1C */
    struct SerialPacket *activeSend;       /* 20 */
    struct SerialPacket *activeReceive;    /* 24; four packets */
    struct SerialPacket *pendingReceive;   /* 28; four packets */
    struct SerialPacket *completedReceive; /* 2C; four packets */
    struct SerialPacket sendPackets[2];    /* 30 */
    struct SerialPacket receivePackets[3][4]; /* 48..D7 */
};

struct MainSerialWork
{
    u32 polledBits;             /* 00 */
    u8 unknown04[4];            /* 04; passed as an outgoing payload */
    u16 words[4][2];            /* 08; four received four-byte payloads */
    u8 unknown18;              /* 18 */
    u8 missingPolls[4];         /* 19; compared as signed bytes */
    u8 appeared;               /* 1D */
    u8 disappeared;            /* 1E */
};

extern struct SerialContext gSerialState;
extern struct MainSerialWork gMainSerialWork;

void sub_080020C8(void);
void sub_08002190(void);
void sub_080021A4(void);
u32 sub_080021F4(u16 words[4][2]);
void sub_080022DC(const void *payload);
u8 sub_08002328(u16 words[4][2]);
void sub_080023D8(void);
void sub_08002438(void);

#endif
