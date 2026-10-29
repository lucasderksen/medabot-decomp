#include "serial.h"
#include "gba.h"

#define REG_SIOCNT (*(volatile u16 *)0x04000128)
#define REG_SIOCNT_WORD (*(volatile u32 *)0x04000128)
#define REG_SIOCNT_HI (*(volatile u8 *)0x04000129)
#define REG_SIOMLT_SEND (*(volatile u16 *)0x0400012A)
#define REG_RCNT (*(volatile u16 *)0x04000134)
#define REG_TM3 (*(volatile u32 *)0x0400010C)
#define REG_TM3CNT_H (*(volatile u16 *)0x0400010E)
#define BIOS_IF (*(volatile u16 *)0x03007FF8)

/* 0x08002190: request a transfer only when the master byte is nonzero. */
void sub_08002190(void)
{
    if (gSerialState.masterFlag != 0)
        gSerialState.requestFlag = 1;
}

/* 0x080021A4: reset serial/timer control and clear the request flag. */
void sub_080021A4(void)
{
    REG_IME = 0;
    REG_IE &= 0xFF3F;
    REG_IME = 1;
    REG_SIOCNT = 0x2003;
    REG_TM3 = 0x63F7;
    REG_IF = 0xC0;
    gSerialState.requestFlag = 0;
}

/* 0x080022DC: prepare an eight-byte header/payload packet and its checksum. */
void sub_080022DC(const void *payload)
{
    u32 sum = 0;
    u32 i;

    gSerialState.pendingSend->sequence = gSerialState.sequence;
    gSerialState.pendingSend->linkBits = gSerialState.rememberedBits ^ gSerialState.validBits;
    gSerialState.pendingSend->checksum = 0;
    CpuSet(payload, &gSerialState.pendingSend->payload, CPU_SET_32BIT | 1);

    for (i = 0; i < 4; i++)
        sum += ((u16 *)gSerialState.pendingSend)[i];

    gSerialState.pendingSend->checksum = ~sum;
    gSerialState.sendReady = 1;
}

/* 0x080020C8: configure multiplayer serial I/O and initialize buffer pointers. */
extern u8 SwapSerialBuffers(void);
extern u32 gSerialIrqCode[0x48];

void sub_080020C8(void)
{
    u32 zero;

    REG_IME = 0;
    REG_IE &= 0xFF3F;
    REG_IME = 1;
    REG_RCNT = 0;
    REG_SIOCNT = 0x2000;
    REG_SIOCNT |= 0x4003;
    zero = 0;
    CpuSet(&zero, &gSerialState, CPU_SET_FILL | CPU_SET_32BIT | (sizeof(gSerialState) / 4));
    CpuSet((const void *)SwapSerialBuffers, (void *)0x03005250, CPU_SET_32BIT | 0x10);
    CpuSet((const void *)sub_08002438, gSerialIrqCode, CPU_SET_32BIT | 0x48);
    gSerialState.sendPosition = 6;
    gSerialState.receivePosition = 6;
    gSerialState.pendingSend = &gSerialState.sendPackets[0];
    gSerialState.activeSend = &gSerialState.sendPackets[1];
    gSerialState.activeReceive = gSerialState.receivePackets[0];
    gSerialState.pendingReceive = gSerialState.receivePackets[1];
    gSerialState.completedReceive = gSerialState.receivePackets[2];
    REG_IME = 0;
    REG_IE |= 0x80;
    REG_IME = 1;
}

struct SioBitfields { u32 control:16; u32 send:16; };

/* 0x080023D8: rotate buffers and start a requested multiplayer transfer. */
void sub_080023D8(void)
{
    struct SerialPacket *temporary;
    volatile u16 *sio;

    if (gSerialState.phase != 0 && gSerialState.requestFlag != 0)
    {
        gSerialState.receivePosition = -1;
        temporary = gSerialState.pendingReceive;
        gSerialState.pendingReceive = gSerialState.activeReceive;
        gSerialState.activeReceive = temporary;

        if (gSerialState.sendReady != 0)
        {
            temporary = gSerialState.activeSend;
            gSerialState.activeSend = gSerialState.pendingSend;
            gSerialState.pendingSend = temporary;
            gSerialState.sendReady = 0;
            gSerialState.sendPosition = 0;
        }

        sio = (volatile u16 *)0x04000128;
        gSerialState.errorBit = (*(volatile u32 *)sio << 25) >> 31;
        ((struct SioBitfields *)sio)->send = 0xFEFE;
        *sio |= 0x80;
        REG_TM3CNT_H = 0xC0;
    }
}

/* 0x080021F4: poll serial state and return packed status bits. */
u32 sub_080021F4(u16 words[4][2])
{
    volatile u32 *sio = (volatile u32 *)0x04000128;
    u32 serialControl = *sio;
    u32 validBits;
    u32 rememberedBits;
    u16 baseStatus;
    u32 status;
    u32 result;

    switch (gSerialState.phase)
    {
    case 0:
        if ((u8)serialControl & 0x30)
            goto receive;
        if (((u8)serialControl & 0x88) != 8)
            break;
        if ((u8)(serialControl & 4) == 0 && gSerialState.sendPosition == 6)
        {
            REG_IME = 0;
            REG_IE &= 0xFF7F;
            REG_IE |= 0x40;
            REG_IME = 1;
            *((volatile s8 *)sio + 1) &= ~0x40;
            REG_TM3 = 0x63F7;
            REG_IF = 0xC0;
            gSerialState.masterFlag = 8;
        }
        gSerialState.phase = 1;
        /* Fall through to the receive poll after entering phase one. */
    case 1:
    receive:
        sub_08002328(words);
        break;
    }

    gSerialState.sequence++;
    validBits = gSerialState.validBits;
    rememberedBits = gSerialState.rememberedBits << 8;
    if (gSerialState.masterFlag == 8)
        baseStatus = (u16)(0x80 | rememberedBits) | validBits;
    else
        baseStatus = validBits | rememberedBits;

    status = baseStatus;
    if (gSerialState.errorBit != 0)
        status |= 0x1000;
    result = status;
    if (((u32)serialControl << 26 >> 30) > 3)
        result |= 0x2000;
    return result;
}

/* 0x08002328: consume packets whose four-halfword checksum is 0xFFFF. */
u8 sub_08002328(u16 words[4][2])
{
    u8 (*swapBuffers)(void) = (u8 (*)(void))0x03005250;
    u32 scratch[2];
    u8 ready;
    s32 i;

    scratch[0] = 0;
    ready = swapBuffers();
    gSerialState.validBits = 0;
    if (ready != 0)
    {
        struct SerialContext *state;
        s32 validChecksum;
        u32 *zeroPayload;
        i = 0;
        zeroPayload = &scratch[1];
        state = &gSerialState;
        validChecksum = -1;
        for (; i < 4; i++)
        {
            struct SerialPacket *packet = &state->completedReceive[i];
            u32 sum = 0;
            u32 j;

            for (j = 0; j < 4; j++)
                sum += ((u16 *)packet)[j];
            if ((s16)sum == validChecksum)
            {
                CpuSet(&packet->payload, words[i], CPU_SET_32BIT | 1);
                state->validBits |= 1 << i;
            }
            scratch[1] = 0;
            CpuSet(zeroPayload, &packet->payload, CPU_SET_FILL | CPU_SET_32BIT | 1);
        }
    }

    gSerialState.rememberedBits |= gSerialState.validBits;
    return gSerialState.validBits;
}


union SerialMultiReceive { u16 words[4]; u32 aligned[2]; };

/* 0x08002438: exchange one serial halfword for each of four players. */
void sub_08002438(void)
{
    union SerialMultiReceive received = *(volatile union SerialMultiReceive *)0x04000120;
    struct SerialPacket *temporary;

    gSerialState.errorBit = (REG_SIOCNT_WORD << 25) >> 31;
    if (received.words[0] == 0xFEFE && gSerialState.receivePosition > 3)
    {
        gSerialState.receivePosition = -1;
        temporary = gSerialState.pendingReceive;
        gSerialState.pendingReceive = gSerialState.activeReceive;
        gSerialState.activeReceive = temporary;
        if (gSerialState.sendReady != 0)
        {
            temporary = gSerialState.activeSend;
            gSerialState.activeSend = gSerialState.pendingSend;
            gSerialState.pendingSend = temporary;
            gSerialState.sendReady = 0;
            gSerialState.sendPosition = 0;
        }
        REG_IME = 0;
        BIOS_IF |= 0x80;
        REG_IME = 1;
    }

    if (gSerialState.sendPosition <= 3)
        ((struct SioBitfields *)0x04000128)->send = ((u16 *)gSerialState.activeSend)[gSerialState.sendPosition];
    if (gSerialState.sendPosition <= 4)
        gSerialState.sendPosition++;

    if (gSerialState.receivePosition >= 0)
    {
        u16 *destination = (u16 *)gSerialState.activeReceive;
        u16 *source = received.words;
        s32 i;
        destination += gSerialState.receivePosition;
        i = 3;
        do
        {
            *destination = *source++;
            destination += sizeof(struct SerialPacket) / 2;
            i--;
        } while (i >= 0);
        if (gSerialState.receivePosition == 3)
            gSerialState.receiveReady = 1;
    }
    if (gSerialState.receivePosition <= 4)
        gSerialState.receivePosition++;
    if (gSerialState.masterFlag != 0)
        REG_TM3CNT_H = 0;
    if (gSerialState.sendPosition <= 4 && gSerialState.masterFlag != 0)
    {
        REG_SIOCNT |= 0x80;
        REG_TM3CNT_H = 0xC0;
    }
}




