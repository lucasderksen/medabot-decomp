#include "effect_work.h"
#include "interrupts.h"

const IntrFunc gUnknownCallbacks_083B291C[9] =
{
    BeginDialogueFadeToColor,
    StepDialogueFadeToColor,
    BeginDialogueBoxOpen,
    StepDialogueBoxOpen,
    BeginDialogueText,
    RunDialogueCommands,
    DispatchDialogueEndMode,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const IntrFunc gUnknownCallbacks_083B2940[5] =
{
    RunDialogueEndMode0,
    RunDialogueEndMode1,
    RunDialogueEndMode2,
    RunDialogueEndMode3,
    RunDialogueEndMode4,
};

const IntrFunc gUnknownCallbacks_083B2954[6] =
{
    RemoveDialoguePortrait,
    BeginDialogueBoxClose,
    StepDialogueBoxClose,
    BeginDialogueFadeFromColor,
    StepDialogueFadeFromColor,
    sub_08040B50,
};

const IntrFunc gUnknownCallbacks_083B296C[6] =
{
    RemoveDialoguePortrait,
    BeginDialogueBoxClose,
    StepDialogueBoxClose,
    BeginDialogueFadeFromColor,
    StepDialogueFadeFromColor,
    sub_08040B50,
};

const IntrFunc gUnknownCallbacks_083B2984[1] =
{
    sub_08040B50,
};

const IntrFunc gUnknownCallbacks_083B2988[2] =
{
    sub_08040B5C,
    sub_08040B50,
};

const IntrFunc gUnknownCallbacks_083B2990[1] =
{
    sub_08040B50,
};
