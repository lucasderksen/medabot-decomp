#ifndef GUARD_STATE0_CALLBACKS_H
#define GUARD_STATE0_CALLBACKS_H

#include "global.h"
#include "main_callbacks.h"
#include "frame_objects.h"
#include "object_helpers.h"
#include "utility_helpers.h"

/* Provisional RAM names and observed call interfaces; see docs/STATE0.md. */
extern u8 gUnknown_03000440[];
extern u8 gUnknown_03002B70[];
extern u32 gNestedCallbackIndex;
extern const void *const gUnknownPointers_083B5578[];
extern const MainCallback gMainState0Callbacks[64];
extern const MainCallback gUnknownCallbacks_083AC3C8[15];
extern const MainCallback gUnknownCallbacks_083AC404[20];
extern const MainCallback gUnknownCallbacks_083AC4A0[64];
extern u32 StepPortraitAnimation(u32, u32, u32, u32, u32, u32);
extern u32 RunDialogue(const void *);
extern void RestartDialogueText(void);
extern u32 gMainSubstate;
extern void InitDialogue(u32, u32, u32);
extern void PlayMusic(u32);
extern const void *const gUnknownPointers_083B4C60[];
extern void CopyTilemapRect(u32, u32, u32, u32, const void *, u32, u32);
extern void sub_08041164(void *, u32);
extern void InitFourRowCursor(void);
extern const void *const gUnknownPointers_083B6100[];
extern void PlaySoundEffect(u32);
extern void FadeOutMusic(u32);
extern void FillTilemapRect(u32, u32, u32, u32, u32, u32);
extern u8 gUnknown_03000588;
extern u32 gMainState;
extern void BlendBgPaletteBanksNow(u32, u32, u32);
extern void BlendObjPaletteBanksNow(u32, u32, u32);
extern void sub_0804765C(u32);
extern void sub_080480E4(void);
extern void sub_08048830(void);
extern void sub_080497E0(u8 control, u16 targets, u8 type, u8 frames, u8 frames2, u8 frames3, u8 first, u8 second, u8 third);
extern u32 sub_08049A6C(void);
extern const MainCallback gUnknownCallbacks_083AC454[19];
extern void LoadSelectedOptionTiles(void);
extern void ScrollBg3DecXIncY(void);
extern void InitThreeOptionCursor(void);
extern u32 StepBlendFade(void);
extern void FillBytes(void *, u32, u32);

void HandleBg1ScrollAndButtons(void);
void AnimatePortraitUntilDone(void);
void WriteTextBufferAndRunDialogue(void);
void RunDialogueThenStartChoiceBox(void);
void WaitChoiceBoxThenRestartDialogue(void);
void RunChoiceResultDialogue(void);
void DispatchMainState0Substate1(void);
void LoadFourRowSelectionGraphics(void);
void AnimateFourRowsIn(void);
void HandleFourRowSelectionInput(void);
void AnimateFourRowsOut(void);
void ClearUnselectedRows(void);
void MoveSelectedRowToTop(void);
void SlideSelectedRowLeft(void);
void SwitchStateForSelectedRow(void);
void sub_08002F70(void);
void SlideSelectedRowRight(void);
void LowerSelectedRowAndRedrawRows(void);
void InitFourRowCursor(void);
void DispatchMainState0Substate2(void);
void LoadThreeOptionGraphics(void);
void FadeInThenInitThreeOptionCursor(void);
void HandleThreeOptionInput(void);
void BeginThreeOptionFadeOut(void);
void StepThreeOptionFadeOut(void);
void ReturnToFourRowSelection(void);
void WaitThreeOptionBlendFade(void);
void sub_080036F4(void);

void RestoreThreeOptionGraphics(void);

void WaitFadeThenInitThreeOptionCursor(void);

void ResumeThreeOptionInput(void);

#endif
