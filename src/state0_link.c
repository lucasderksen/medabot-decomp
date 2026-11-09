#include "state0_next_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "graphics.h"
#include "render_work.h"
#include "serial.h"

extern void ScrollBg3Diagonally2(void);
extern void PlaceNineRecordObjectGroups(void);
extern void sub_080054C0(void);
extern void sub_08007480(void);
extern void CopyPartMetadataSlot(u32, u32, void *);
extern u32 sub_0803E79C(void);
extern const void *const gUnknownPointers_083CF530[];


#define ENTRY_LINK_WORK() do { \
    ScrollBg3Diagonally2(); \
    sub_080054C0(); \
    sub_08007480(); \
} while (0)

void HideMarkersAndResetDelay(void)
{
    ScrollBg3Diagonally2();
    PlaceNineRecordObjectGroups();
    sub_080054C0();
    HideFrameObjects(0, 4);
    gState0TypedWork.widths.word5C = 0;
    gNestedCallbackIndex++;
}

void sub_08004798(void)
{
    ENTRY_LINK_WORK();
    if (gState0TypedWork.widths.word5C > 60)
    {
        if (gState0TypedWork.bytes[0x50] == 1)
            gNestedCallbackIndex = 48;
        else
        {
            SnapshotPalettes();
            gState0TypedWork.bytes[0x84] = 0;
            gNestedCallbackIndex++;
        }
    }
}

void sub_080047EC(void)
{
    ENTRY_LINK_WORK();
    if (gState0TypedWork.bytes[0x84] <= 32)
    {
        BlendBgPaletteBanksNow(0, gState0TypedWork.bytes[0x84], 0xFFFF);
        BlendObjPaletteBanksNow(0, gState0TypedWork.bytes[0x84], 0xFFFF);
        gState0TypedWork.bytes[0x84]++;
    }
    else
        gNestedCallbackIndex++;
}

void ExitToSubstate7(void)
{
    ClearFrameObjects(0, 128);
    gState0TypedWork.bytes[0x96] = 0;
    gRenderMode = 0;
    gMainSubstate = 7;
    gNestedCallbackIndex = 0;
}

void DelayThenStartExitFade(void)
{
    ENTRY_LINK_WORK();
    if (gState0TypedWork.widths.word5C > 60)
    {
        FadeOutMusic(8);
        StartBlendFade(6, 63, 8);
        gNestedCallbackIndex++;
    }
}

void sub_080048B0(void)
{
    ENTRY_LINK_WORK();
    if (StepBlendFade())
        gNestedCallbackIndex++;
}

void CopySelectedRecordsAndEnterState3(void)
{
    s32 i;
    ClearFrameObjects(0, 128);
    gState0TypedWork.bytes[0x96] = 0;
    gRenderMode = 0;
    for (i = 0; i <= 2; i++)
    {
        CopyPartMetadataSlot(gUnknownRecords_030017A0[gState0TransferWork.indexed.selected[i] & 15].byte6, 3, &gState0TypedWork.bytes[0xEE]);
        gState0TransferWork.indexed.results[i] = gState0TypedWork.bytes[0xEF] - 100;
        gState0TransferWork.indexed.records[i].byte0 = gUnknownRecords_030017A0[gState0TransferWork.indexed.selected[i] & 15].byte3;
        gState0TransferWork.indexed.records[i].byte1 = gUnknownRecords_030017A0[gState0TransferWork.indexed.selected[i] & 15].byte4;
        gState0TransferWork.indexed.records[i].byte2 = gUnknownRecords_030017A0[gState0TransferWork.indexed.selected[i] & 15].byte5;
        gState0TransferWork.indexed.records[i].byte3 = gUnknownRecords_030017A0[gState0TransferWork.indexed.selected[i] & 15].byte6;
    }
    gMainState = 3;
    gMainSubstate = 4;
    gNestedCallbackIndex = 5;
}

void InitDialogueBeforeTransfer(void)
{
    ScrollBg3Diagonally2();
    sub_080054C0();
    InitDialogue(1, 0, 0);
    gNestedCallbackIndex++;
}

void sub_080049EC(void)
{
    ScrollBg3Diagonally2();
    sub_080054C0();
    if (RunDialogue(gUnknownPointers_083CF530[11]))
        gNestedCallbackIndex++;
}

void PrepareSerialSendBuffer(void)
{
    ScrollBg3Diagonally2();
    sub_080054C0();
    sub_08014E7C();
    sub_08014E94();
    sub_08014EC8();
    gNestedCallbackIndex++;
}

void WaitSerialSyncAndClearOutput(void)
{
    ScrollBg3Diagonally2();
    sub_080054C0();
    if (sub_0803E79C())
    {
        gMainSerialOutgoingWork.word06 = 0;
        gState0TypedWork.widths.word86 = 0;
        gNestedCallbackIndex++;
    }
}

void DelayThenInitSerialTransfer(void)
{
    ScrollBg3Diagonally2();
    sub_080054C0();
    if (gState0TypedWork.widths.word86 == 24)
    {
        gState0TransferWork.bytes[0x51] = 0;
        gState0TransferWork.bytes[0x52] = 0;
        gState0TransferWork.bytes[0x53] = 0;
        gState0TransferWork.bytes[0x54] = 0;
        gState0TransferWork.widths.words1A6[0] = 0;
        gState0TransferWork.widths.words1A6[1] = 0;
        gState0TransferWork.widths.words1A6[2] = 0;
        gState0TransferWork.widths.words1A6[3] = 0;
        gState0TransferWork.bytes[0x1AF] = 0;
        gState0TransferWork.bytes[0x1B0] = 1;
        gState0TypedWork.widths.word86 = 0;
        gNestedCallbackIndex++;
    }
    else
        (gState0TypedWork.widths.word86)++;
}
