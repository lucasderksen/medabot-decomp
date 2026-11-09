#include "continued_late_graphics.h"
#include "continued_graphics.h"
#include "object_numeric_helpers.h"
#include "post_dispatch.h"


void sub_08057AD0(void)
{
    if (StepPaletteFadeToColor(0))
    {
        InitFrameObject(127, 0xC004, 0x307, 12, 0);
        sub_08057FD4();
        gNestedCallbackIndex = 2;
    }
}

void sub_08057D04(void)
{
    sub_08047C00();
    sub_0804A210();
}

void sub_08057D14(void)
{
    if (InitAndRunDialogue(1, 1, 0, gStateScripts_084144B4[129]))
        gNestedCallbackIndex = 2;
}

void sub_08057D40(void)
{
    sub_08047C00();
    sub_0804A210();
}

void sub_08057D50(void)
{
    if (InitAndRunDialogue(1, 1, 0, gStateScripts_084144B4[128]))
        gNestedCallbackIndex = 2;
}
