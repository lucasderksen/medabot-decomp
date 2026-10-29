#ifndef GUARD_ENCOUNTER_CHOICES_H
#define GUARD_ENCOUNTER_CHOICES_H

#include "global.h"

/* Twelve-byte records at 08485C00, shared by the encounter scene callbacks. */
struct EncounterChoiceRecord
{
    u8 fixed;
    u8 value;
    s16 firstRecord;
    u8 unknown04[2];
    s16 secondRecord;
    u8 unknown08;
    u8 command;
    u8 unknown0A[2];
};

extern const struct EncounterChoiceRecord gChoiceRecords6A024[];

#endif
