#ifndef GUARD_EFFECT_WORK_H
#define GUARD_EFFECT_WORK_H

#include "gba.h"

extern const IntrFunc gUnknownCallbacks_083B291C[9];
extern const IntrFunc gUnknownCallbacks_083B2940[5];
extern const IntrFunc gUnknownCallbacks_083B2954[6];
extern const IntrFunc gUnknownCallbacks_083B296C[6];
extern const IntrFunc gUnknownCallbacks_083B2984[1];
extern const IntrFunc gUnknownCallbacks_083B2988[2];
extern const IntrFunc gUnknownCallbacks_083B2990[1];

/* Observed byte/halfword interfaces; field roles remain provisional. */
void RestartDialogueText(void);
u32 RunDialogue(const void *script);
void BeginDialogueFadeToColor(void);
void StepDialogueFadeToColor(void);
void BeginDialogueBoxOpen(void);
void StepDialogueBoxOpen(void);
void BeginDialogueText(void);
void RunDialogueCommands(void);
void AdvanceDialoguePosition(void);
void SetDialoguePortrait(void);
void DrawDialogueGlyph(void);
void DrawDialogueReplacementGlyph(void);
void BreakDialogueLine(void);
u32 WaitDialoguePageInput(void);
void WaitDialogueDelaySkippable(void);
void WaitDialogueDelay(void);
void EndDialogueText(void);
void DispatchDialogueEndMode(void);
void RunDialogueEndMode0(void);
void RunDialogueEndMode1(void);
void RunDialogueEndMode2(void);
void RunDialogueEndMode3(void);
void RunDialogueEndMode4(void);
void RemoveDialoguePortrait(void);
void BeginDialogueBoxClose(void);
void StepDialogueBoxClose(void);
void BeginDialogueFadeFromColor(void);
void StepDialogueFadeFromColor(void);
/* Subsequent routines are referenced as zero-argument table callbacks. */
void sub_08040B50(void);
void sub_08040B5C(void);

#endif
