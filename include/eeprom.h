#ifndef GUARD_EEPROM_H
#define GUARD_EEPROM_H

#include "gba.h"

struct EepromConfig
{
    u32 sizeBytes;
    u16 blockCount;
    u16 waitcnt;
    u8 addressBits;
    u8 padding[3];
};

extern const char gEepromLibraryVersion[12];
extern const struct EepromConfig gEepromConfig4K;
extern const struct EepromConfig gEepromConfig64K;
extern const u16 gEepromTimeoutParams[4];
extern const struct EepromConfig *gEepromConfig;
/* Matching -O1 access patterns use ordinary shared RAM declarations here.
 * The hardware registers reached through gEepromTimerRegs remain volatile.
 */
extern u8 gEepromTimerNumber;
extern u16 gEepromCountdown;
extern u8 gEepromTimedOut;
extern volatile u16 *gEepromTimerRegs;
extern u16 gEepromSavedIme;

/* ABI name retained while initialization still refers to this entrypoint. */
u16 Unknown_0807C8B0(u16 sizeKbits);
void EepromTimerIntr(void);
u16 SetEepromTimerIntr(u8 timerNumber, IntrFunc *handler);
void StartEepromTimer(const u16 *parameters);
void StopEepromTimer(void);
void EepromDma3Transmit(const void *source, void *destination, u16 count);
u16 ReadEepromDword(u16 block, u16 *destination);
u16 ProgramEepromDword(u16 block, const u16 *source);
u16 VerifyEepromDword(u16 block, const u16 *source);
u16 ProgramEepromDwordEx(u16 block, const u16 *source);

#endif
