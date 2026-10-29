#include "encounter_choices.h"

typedef char EncounterChoiceRecordSize[(sizeof(struct EncounterChoiceRecord) == 12) ? 1 : -1];

/* The next object at 08485C78 is the first scene-text stream. */
const struct EncounterChoiceRecord gChoiceRecords6A024[10] = {
    { 0, 0, 101, { 2, 0 }, 226, 81, 10, { 0, 0 } },
    { 1, 5, 102, { 2, 0 }, 226, 81, 12, { 0, 0 } },
    { 0, 0, 103, { 2, 0 }, 71, 54, 14, { 0, 0 } },
    { 0, 0, 130, { 7, 0 }, 135, 8, 16, { 0, 0 } },
    { 0, 0, 127, { 6, 0 }, 131, 7, 18, { 0, 0 } },
    { 1, 3, 51, { 40, 0 }, 57, 52, 20, { 0, 0 } },
    { 0, 0, 103, { 2, 0 }, 224, 75, 22, { 0, 0 } },
    { 0, 0, 103, { 2, 0 }, 222, 74, 24, { 0, 0 } },
    { 0, 0, 116, { 4, 0 }, 227, 78, 26, { 0, 0 } },
    { 1, 10, 226, { 81, 0 }, 87, 62, 28, { 0, 0 } },
};
