#include "eeprom.h"

/* Reconstructed from the ROM and matched with agbcc 2.9-arm-000512,
 * -O1 -fprologue-bugfix. The resulting .rodata pointer constants are also
 * part of the matching library data. No inline assembly is used.
 */

#define REG_WAITCNT (*(volatile u16 *)0x04000204)
#define REG_DMA3SAD (*(volatile u32 *)0x040000D4)
#define REG_DMA3DAD (*(volatile u32 *)0x040000D8)
#define REG_DMA3CNT (*(volatile u32 *)0x040000DC)
#define REG_DMA3CNT_H (*(volatile u16 *)0x040000DE)
#define EEPROM_PORT ((volatile u16 *)0x0D000000)

/* 0x0807C8B0; size values are in kilobits. */
u16 Unknown_0807C8B0(u16 sizeKbits)
{
    u16 result = 0;
    if (sizeKbits == 4)
        gEepromConfig = &gEepromConfig4K;
    else if (sizeKbits == 64)
        gEepromConfig = &gEepromConfig64K;
    else
    {
        gEepromConfig = &gEepromConfig4K;
        result = 1;
    }
    return result;
}

/* 0x0807C8F4; installed by SetEepromTimerIntr. */
void EepromTimerIntr(void)
{
    if (gEepromCountdown != 0)
    {
        if (--gEepromCountdown == 0)
            gEepromTimedOut = 1;
    }
}

/* 0x0807C918. */
u16 SetEepromTimerIntr(u8 timerNumber, IntrFunc *handler)
{
    if (timerNumber > 3)
        return 1;
    gEepromTimerNumber = timerNumber;
    gEepromTimerRegs = (volatile u16 *)(0x04000100 + gEepromTimerNumber * 4);
    *handler = EepromTimerIntr;
    return 0;
}

/* 0x0807C950. */
void StartEepromTimer(const u16 *parameters)
{
    gEepromSavedIme = REG_IME;
    REG_IME = 0;
    gEepromTimerRegs[1] = 0;
    REG_IF = IRQ_TIMER0 << gEepromTimerNumber;
    REG_IE |= IRQ_TIMER0 << gEepromTimerNumber;
    gEepromTimedOut = 0;
    gEepromCountdown = *parameters++;
    *gEepromTimerRegs++ = *parameters++;
    *gEepromTimerRegs-- = *parameters;
    REG_IME = 1;
}

/* 0x0807C9D8. */
void StopEepromTimer(void)
{
    REG_IME = 0;
    *gEepromTimerRegs++ = 0;
    *gEepromTimerRegs-- = 0;
    REG_IE &= ~(IRQ_TIMER0 << gEepromTimerNumber);
    REG_IME = gEepromSavedIme;
}

/* 0x0807CA1C; immediate 16-bit DMA, incrementing source and destination. */
void EepromDma3Transmit(const void *source, void *destination, u16 count)
{
    u16 savedIme = REG_IME;
    REG_IME = 0;
    REG_WAITCNT = (REG_WAITCNT & 0xF8FF) | gEepromConfig->waitcnt;
    REG_DMA3SAD = (u32)source;
    REG_DMA3DAD = (u32)destination;
    REG_DMA3CNT = 0x80000000 | count;
    while ((REG_DMA3CNT_H & 0x8000) != 0)
        ;
    REG_IME = savedIme;
}

/* 0x0807CA9C; one EEPROM doubleword contains four host halfwords. */
u16 ReadEepromDword(u16 block, u16 *destination)
{
    u16 buffer[68];
    u16 *cursor;
    u8 i;
    u8 bit;
    u32 addressOffset;
    u16 value;

    if (block >= gEepromConfig->blockCount)
        return 0x80FF;
    addressOffset = gEepromConfig->addressBits * 2;
    cursor = (u16 *)(addressOffset + (u32)buffer + 2);
    for (i = 0; i < gEepromConfig->addressBits; i++)
    {
        *cursor-- = block;
        block >>= 1;
    }
    *cursor-- = 1;
    *cursor = 1;
    /* The original does not initialize buffer[addressBits + 2], the final
     * halfword of this outgoing read request.
     */
    EepromDma3Transmit(buffer, (void *)EEPROM_PORT, gEepromConfig->addressBits + 3);
    EepromDma3Transmit((const void *)EEPROM_PORT, buffer, 68);
    cursor = &buffer[4];
    destination += 3;
    for (i = 0; i < 4; i++)
    {
        value = 0;
        for (bit = 0; bit < 16; bit++)
        {
            value <<= 1;
            value |= *cursor++ & 1;
        }
        *destination-- = value;
    }
    return 0;
}

/* 0x0807CB4C. */
u16 ProgramEepromDword(u16 block, const u16 *source)
{
    u16 buffer[82];
    u16 *cursor;
    u16 value;
    u16 result;
    u8 i;
    u8 bit;
    u32 addressOffset;

    if (block >= gEepromConfig->blockCount)
        return 0x80FF;
    addressOffset = gEepromConfig->addressBits * 2;
    cursor = (u16 *)(addressOffset + (u32)buffer + 132);
    *cursor-- = 0;
    for (i = 0; i < 4; i++)
    {
        value = *source++;
        for (bit = 0; bit < 16; bit++)
        {
            *cursor-- = value;
            value >>= 1;
        }
    }
    for (i = 0; i < gEepromConfig->addressBits; i++)
    {
        *cursor-- = block;
        block >>= 1;
    }
    *cursor-- = 0;
    *cursor = 1;
    EepromDma3Transmit(buffer, (void *)EEPROM_PORT, gEepromConfig->addressBits + 67);
    StartEepromTimer(gEepromTimeoutParams);
    result = 0;
    while ((*EEPROM_PORT & 1) == 0)
    {
        if (gEepromTimedOut != 0)
        {
            /* Preserve the original narrow expression in the final poll. */
            if (((u8)*EEPROM_PORT & 1) == 0)
                result = 0xC001;
            break;
        }
    }
    StopEepromTimer();
    return result;
}

/* 0x0807CC28; return the first mismatch as 0x8000. */
u16 VerifyEepromDword(u16 block, const u16 *source)
{
    u16 buffer[4];
    u16 *cursor;
    u16 result = 0;
    u8 i;

    if (block >= gEepromConfig->blockCount)
        return 0x80FF;
    ReadEepromDword(block, buffer);
    cursor = buffer;
    for (i = 0; i < 4; i++)
    {
        if (*source++ != *cursor++)
        {
            result = 0x8000;
            break;
        }
    }
    return result;
}

/* 0x0807CC80; at most three program-and-verify attempts. */
u16 ProgramEepromDwordEx(u16 block, const u16 *source)
{
    u8 i;
    u16 result;

    for (i = 0; i < 3; i++)
    {
        result = ProgramEepromDword(block, source);
        if (result == 0)
        {
            result = VerifyEepromDword(block, source);
            if (result == 0)
                break;
        }
    }
    return result;
}
