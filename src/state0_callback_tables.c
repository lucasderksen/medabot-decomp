#include "state0_next_helpers.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "interrupts.h"

/* Adjacent independently referenced table starts establish these intervals.
 * Names/slot roles remain provisional; see docs/STATE0.md. */
extern void DispatchMainState0Substate0(void);
extern void sub_08002574(void);
extern void HandleBg1ScrollAndButtons(void);
extern void AnimatePortraitUntilDone(void);
extern void WriteTextBufferAndRunDialogue(void);
extern void RunDialogueThenStartChoiceBox(void);
extern void WaitChoiceBoxThenRestartDialogue(void);
extern void RunChoiceResultDialogue(void);
extern void DispatchMainState0Substate1(void);
extern void LoadFourRowSelectionGraphics(void);
extern void AnimateFourRowsIn(void);
extern void HandleFourRowSelectionInput(void);
extern void AnimateFourRowsOut(void);
extern void ClearUnselectedRows(void);
extern void MoveSelectedRowToTop(void);
extern void SlideSelectedRowLeft(void);
extern void SwitchStateForSelectedRow(void);
extern void sub_08002F70(void);
extern void SlideSelectedRowRight(void);
extern void LowerSelectedRowAndRedrawRows(void);
extern void DispatchMainState0Substate2(void);
extern void LoadThreeOptionGraphics(void);
extern void FadeInThenInitThreeOptionCursor(void);
extern void HandleThreeOptionInput(void);
extern void BeginThreeOptionFadeOut(void);
extern void StepThreeOptionFadeOut(void);
extern void ReturnToFourRowSelection(void);
extern void WaitThreeOptionBlendFade(void);
extern void sub_080036F4(void);
extern void RestoreThreeOptionGraphics(void);
extern void WaitFadeThenInitThreeOptionCursor(void);
extern void ResumeThreeOptionInput(void);
extern void DispatchMainState0Substate3(void);
extern void DispatchInventoryCallbacks(void);
extern void DispatchDebugMenu(void);
extern void DispatchPartListCallbacks(void);
extern void sub_08012970(void);
extern void sub_08030860(void);
extern void sub_08033840(void);
extern void sub_0803D538(void);

const MainCallback gMainState0Callbacks[64] =
{
    DispatchMainState0Substate0,
    DispatchMainState0Substate1,
    DispatchMainState0Substate2,
    DispatchMainState0Substate3,
    DispatchInventoryCallbacks,
    DispatchPartListCallbacks,
    sub_08010264,
    sub_08012970,
    sub_08030860,
    sub_08033840,
    sub_0803D538,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DispatchDebugMenu,
};

const MainCallback gUnknownCallbacks_083AC3C8[15] =
{
    sub_08002574,
    HandleBg1ScrollAndButtons,
    AnimatePortraitUntilDone,
    WriteTextBufferAndRunDialogue,
    RunDialogueThenStartChoiceBox,
    WaitChoiceBoxThenRestartDialogue,
    RunChoiceResultDialogue,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const MainCallback gUnknownCallbacks_083AC404[20] =
{
    LoadFourRowSelectionGraphics,
    AnimateFourRowsIn,
    HandleFourRowSelectionInput,
    AnimateFourRowsOut,
    DummyInterruptHandler,
    DummyInterruptHandler,
    ClearUnselectedRows,
    MoveSelectedRowToTop,
    SlideSelectedRowLeft,
    SwitchStateForSelectedRow,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08002F70,
    SlideSelectedRowRight,
    LowerSelectedRowAndRedrawRows,
    DummyInterruptHandler,
};

const MainCallback gUnknownCallbacks_083AC454[19] =
{
    LoadThreeOptionGraphics,
    FadeInThenInitThreeOptionCursor,
    HandleThreeOptionInput,
    BeginThreeOptionFadeOut,
    StepThreeOptionFadeOut,
    ReturnToFourRowSelection,
    DummyInterruptHandler,
    DummyInterruptHandler,
    WaitThreeOptionBlendFade,
    sub_080036F4,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    RestoreThreeOptionGraphics,
    WaitFadeThenInitThreeOptionCursor,
    ResumeThreeOptionInput,
};


extern void sub_08003A38(void);
extern void FadeInRecordSelection(void);
extern void HandleRecordSelectionInput(void);
extern void StartRecordSelectionExitFade(void);
extern void sub_08003EA0(void);
extern void ReturnToThreeOptionSelection(void);
extern void SnapshotRecordSelectionPalettes(void);
extern void sub_08003F74(void);
extern void InitRecordSelectionDialogue(void);
extern void sub_08004028(void);
extern void sub_0800406C(void);
extern void FadeInInventoryDisplay(void);
extern void HandleInventoryDisplayInput(void);
extern void BeginInventoryReturnFade(void);
extern void sub_0800454C(void);
extern void CommitPartsAndReturnToRecords(void);
extern void StartInventoryExitFade(void);
extern void sub_08004610(void);
extern void sub_08004644(void);
extern void HideMarkersAndResetDelay(void);
extern void sub_08004798(void);
extern void sub_080047EC(void);
extern void ExitToSubstate7(void);
extern void DelayThenStartExitFade(void);
extern void sub_080048B0(void);
extern void CopySelectedRecordsAndEnterState3(void);
extern void InitDialogueBeforeTransfer(void);
extern void sub_080049EC(void);
extern void PrepareSerialSendBuffer(void);
extern void WaitSerialSyncAndClearOutput(void);
extern void DelayThenInitSerialTransfer(void);
extern void ExchangeTransferBuffersOverSerial(void);
extern void DelayThenResetTransferCounters(void);
extern void VerifyTransferChecksums(void);
extern void sub_08004DB4(void);
extern void FadeToBlackAfterTransfer(void);
extern void ExitToSubstate7AfterTransfer(void);

const MainCallback gUnknownCallbacks_083AC4A0[64] =
{
    sub_08003A38,
    FadeInRecordSelection,
    HandleRecordSelectionInput,
    StartRecordSelectionExitFade,
    sub_08003EA0,
    ReturnToThreeOptionSelection,
    DummyInterruptHandler,
    DummyInterruptHandler,
    SnapshotRecordSelectionPalettes,
    sub_08003F74,
    DummyInterruptHandler,
    InitRecordSelectionDialogue,
    sub_08004028,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0800406C,
    FadeInInventoryDisplay,
    HandleInventoryDisplayInput,
    BeginInventoryReturnFade,
    sub_0800454C,
    CommitPartsAndReturnToRecords,
    DummyInterruptHandler,
    DummyInterruptHandler,
    StartInventoryExitFade,
    sub_08004610,
    sub_08004644,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    HideMarkersAndResetDelay,
    sub_08004798,
    sub_080047EC,
    ExitToSubstate7,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    HideMarkersAndResetDelay,
    DelayThenStartExitFade,
    sub_080048B0,
    CopySelectedRecordsAndEnterState3,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    InitDialogueBeforeTransfer,
    sub_080049EC,
    PrepareSerialSendBuffer,
    WaitSerialSyncAndClearOutput,
    DelayThenInitSerialTransfer,
    ExchangeTransferBuffersOverSerial,
    DelayThenResetTransferCounters,
    WaitSerialSyncAndClearOutput,
    DelayThenResetTransferCounters,
    VerifyTransferChecksums,
    sub_08004DB4,
    FadeToBlackAfterTransfer,
    ExitToSubstate7AfterTransfer,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};
