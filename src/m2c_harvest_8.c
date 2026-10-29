/*
 * Functions translated by m2c (tools/m2c_candidate.py --harvest) that matched
 * exactly without edits. Names, types and boundaries are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "display_effects.h"
#include "display_helpers.h"
#include "effect_work.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "initialization.h"
#include "later_helpers.h"
#include "main.h"
#include "main_callbacks.h"
#include "object_helpers.h"
#include "object_numeric_helpers.h"
#include "post_dispatch.h"
#include "record_helpers.h"
#include "render_work.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_inventory.h"
#include "state0_inventory_numbers.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"
#include "utility_helpers.h"

extern s32 gUnknown_020264E0;
extern s32 gUnknown_0202F880;
extern s32 gUnknown_0202F8A0;
extern s32 gUnknown_0202F8C0;
extern s32 gUnknown_0202F8E0;
extern s32 gUnknown_0202F900;
extern s32 gUnknown_0202F920;
extern s32 gUnknown_0202F940;
extern s32 gUnknown_0202F960;
extern s32 gUnknown_03006F80;
extern s32 gUnknown_03006F88;
extern s32 gUnknown_03006F8C;
extern s32 gUnknown_03006F94;
extern s32 gUnknown_08484FC0;
extern s32 gUnknown_084E4498;
extern s32 gUnknown_084E44B8;
extern s32 gUnknown_084F4F40;
extern s32 gUnknown_0850F718;
extern s32 gUnknown_08510418;
extern s32 gUnknown_08510438;
extern s32 gUnknown_085104F8;
extern struct RenderWork gUnknown_02024000;
extern u16 gState0FrameBackup;
extern u16 gUnknown_02021000;
extern u8 gFreshWork_03006D38;
extern u8 gUnknown_020268F0;
extern u8 gUnknown_03001864;
extern u8 gUnknown_0300198A;
extern u8 gUnknown_03006FDC;
extern u8 gUnknown_084C7C54;
extern u8 gUnknown_084C7E7C;
extern u8 gUnknown_084CB9C8;
extern u8 gUnknown_084D819C;
extern u8 gUnknown_084E1584;
extern u8 gUnknown_084E1900;
extern u8 gUnknown_084E3698;
extern u8 gUnknown_084EF490;
extern u8 gUnknown_084F0C08;
extern u8 gUnknown_084F1734;
extern u8 gUnknown_084F233C;
extern u8 gUnknown_084F3788;
extern void *gUnknown_03007014;
s32 sub_08017A14(s32, s32);
s32 sub_08018CBC();
s32 sub_0801A418(u8 *, u8, s32);
s32 sub_0801AC24(u8);
s32 sub_0801AC6C();
s32 sub_0801AC98(u8);
s32 sub_0801AD10(u8);
s32 sub_0801AD48(u8);
s32 sub_0801ADE8(u8);
s32 sub_0801AE70(u8);
s32 sub_0801C0BC(u8);
s32 sub_0801C154();
s32 sub_0801C2F0(s32);
s32 sub_08031A70();
s32 sub_08031ABC();
s32 sub_0803572C(void *, s16);
s32 sub_08035740(void *, s16, s32);
s32 sub_08035C70();
s32 sub_08035F20();
s32 sub_08036120(s32);
s32 sub_080361A8();
s32 sub_080366DC(s32, u8);
s32 sub_0803684C(s32);
s32 sub_08036CCC(u8, u8, s16);
s32 sub_08036DE8(s32, s32);
s32 sub_080372D4(u8, u8, s16);
s32 sub_08037424(s32);
s32 sub_08037728(s32 slot, s32 part, u32 limit);
s32 sub_080378A8();
s32 sub_08037B9C();
s32 sub_080385F8();
s32 sub_0803884C();
s32 sub_080393EC();
s32 sub_0803B8C8();
s32 sub_0803D450();
s32 sub_0803D4AC();
s32 sub_0803E79C();
s32 sub_0803E894();
s32 sub_0803E8B8();
s32 sub_0803E8EC();
s32 sub_0803E934();
s32 sub_0803E978();
s32 sub_0803E9BC();
s32 sub_0803EB30();
s32 sub_0803EB5C();
s32 sub_0803EC04();
s32 sub_0803EC98();
s32 sub_0803ECF0();
s32 sub_0803ED10();
s32 sub_0803ED28();
s32 sub_0803ED6C();
s32 sub_0803EE10();
s32 sub_0805A3A4(s32, s32, s32);
s32 sub_0805B984();
s32 sub_080605A0();
s32 sub_08060620();
s32 sub_08060D28(void *, s32 *);
s32 sub_08062B48(u8, u8, s32);
s32 sub_08062DFC();
s32 sub_08067C04();
s32 sub_08068460(s32, s32, s32);
s32 sub_08068888();
s32 sub_08069320();
s32 sub_0806938C();
s32 sub_08069490();
s32 sub_08069530();
s32 sub_080696A8();
s32 sub_08069910();
s32 sub_08069A08();
s32 sub_08069CC0();
s32 sub_0806A024();
s32 sub_0806A08C();
s32 sub_0806A114();
s32 sub_0806A3C4();
s32 sub_0806A654();
s32 sub_0806A718();
s32 sub_0806A748();
s32 sub_0806A860();
s32 sub_0806AA10();
s32 sub_0806AAA4();
s32 sub_0806ADB0();
s32 sub_0806B01C();
s32 sub_0806B0D4();
s32 sub_0806B4C8();
s32 sub_0806B718(s32);
s32 sub_0806BD70();
s32 sub_0806BF18();
s32 sub_0806BFEC();
s32 sub_0806C084();
s32 sub_0806C218();
s32 sub_0806C3A0();
s32 sub_0806C660();
s32 sub_0806C694();
s32 sub_0806CB28();
s32 sub_0806CC80();
s32 sub_0806CD68();
s32 sub_0806CEDC();
s32 sub_0806CF7C();
s32 sub_0806D398();
s32 sub_0806F9D8();
s32 sub_0806FB5C();
s32 sub_08071898(s32, s32, s32);
s32 sub_080718D4(s32, s32);
void sub_08071DB8(u32,u32,u32);
s32 sub_080727D0();
s32 sub_08072818(s32);
s32 sub_08072880();
s32 sub_08072D68(void *);
s32 sub_080732C8(void *, s32);
s32 sub_080732F0(void *, s32, s32);
s32 sub_0807334C(void *, s32);
s32 sub_08073404(void *, s32);
void sub_08073480(void *, volatile u16 *);
s32 sub_08073524(void *, s32, s32);
void sub_08073604(void *);
void sub_080737E8(void *);
s32 sub_08073A88();
s32 sub_08073C84();
s32 sub_08073D70(void *, s32);
s32 sub_08073DB8(s32, s32, s32, s32, s32, s32, s32, s32);
s32 sub_08073E1C(void *);
void sub_0807462C(s32);
s32 sub_0807495C(void *);
s32 sub_08074A04();
s32 sub_0807CD2C(s32, s32);
s32 sub_0807CF40(u8, s32);
u8 sub_0807CEC8(u8, s32);

void sub_0800AFF8(void);
void sub_0800F218(void);
void sub_080158D0(u32 arg0);
void sub_08016614(void);
void sub_08016660(void);
void sub_080166F0(void);
void sub_0801672C(void);
void sub_08016E90(void);
void sub_08016EDC(void);
void sub_08016F28(void);
void sub_08016F64(void);
void sub_08017048(void);
void sub_08017084(void);
void sub_08017948(void);
void sub_08018098(void);
void sub_08018180(void);
void sub_08018218(void);
void sub_080187A8(void);
void sub_08018C38(void);
void sub_0801ABF8(void);
void sub_0801AEF4(void);
void sub_0801C110(void);
void sub_0801C138(void);
void sub_0801C32C(void);
void sub_0801C360(void);
void sub_0801C388(void);
void sub_0801C3F8(void);
void sub_0801C40C(void);
void sub_0801C444(void);
void sub_0801C470(void);
void sub_0801C4A4(void);
void sub_0801C4E0(void);
void sub_0801E200(void);
void sub_0801E248(void);
void sub_0801E2B8(void);
void sub_0801E54C(void);
void sub_0801E830(void);
void sub_0801E8DC(void);
void sub_0801E9E0(void);
void sub_0801EBD4(void);
void sub_0801F374(void);
void sub_0801F9B0(void);
void sub_0801FA68(void);
void sub_0801FD88(void);
void sub_0801FEC8(void);
void sub_08020288(void);
void sub_08020608(void);
void sub_08020728(void);
void sub_08020768(void);
void sub_080208E8(void);
void sub_08020A90(void);
void sub_080215C8(void);
void sub_08021608(void);
void sub_08021734(void);
void sub_080231D4(void);
void sub_080233E0(void);
void sub_080241F0(void);
void sub_08024870(void);
void sub_08024BCC(void);
void sub_08024BF8(void);
void sub_08024F90(void);
void sub_08025354(void);
void sub_08025500(void);
void sub_08025674(void);
void sub_08025790(void);
void sub_08025D2C(void);
void sub_08025D4C(void);
void sub_080260EC(void);
void sub_08026810(void);
void sub_080268AC(void);
void sub_080268D4(void);
void sub_08026F34(void);
void sub_0802733C(void);
void sub_08027378(void);
void sub_080273DC(void);
void sub_08027444(void);
void sub_080287C0(void);
void sub_0802A2D4(void);
void sub_0802C24C(void);
void sub_0802C66C(void);
void sub_0802D6B0(void);
void sub_0802DF18(void);
void sub_0802E1A4(void);
void sub_0802EAA4(void);
void sub_0802F468(void);
void sub_0802F864(void);
void sub_0802F880(void);
void sub_080305E0(void);
void sub_08030608(void);
void sub_08030D3C(void);
void sub_08030D74(void);
void sub_08030E54(void);
void sub_080312F0(void);
void sub_08031438(void);
void sub_08031518(void);
void sub_08031978(void);
void sub_080319B8(void);
void sub_08031A08(void);
void sub_08031A24(void);
void sub_08031A3C(u32 selected);
u32 sub_080361C4(void);
u32 sub_08036218(void);
void sub_080362C4(s32 arg0);
void sub_08036BF4(s32 arg0);
void sub_0803809C(void);
void sub_080393BC(void);
void sub_0803A0B8(void);
void sub_0803A264(void);
void sub_0803A2E8(void);
void sub_0803A444(void);
void sub_0803A6FC(void);
void sub_0803A920(void);
void sub_0803AB9C(void);
void sub_0803B6D8(void);
void sub_0803B700(void);
void sub_0803D5E0(void);
void sub_0803D928(void);
void sub_0803D980(void);
void sub_0803D9C8(void);
void sub_0803D9F0(void);
void sub_0803DA40(void);
void sub_0803DA90(void);
void sub_0803DB1C(void);
void sub_0803DB94(void);
void sub_0803DBE0(void);
void sub_0803DC0C(void);
void sub_0803DC3C(void);
void sub_0803DC8C(void);
void sub_0803DCDC(void);
void sub_0803DE70(void);
void sub_0803DE90(void);
void sub_0803E018(void);
void sub_0803E098(void);
void sub_0803E0C0(void);
void sub_0803E0F0(void);
void sub_0803E170(void);
void sub_0803E234(void);
void sub_0803E270(void);
void sub_0803E2AC(void);
void sub_0803E2DC(void);
void sub_0803E314(void);
void sub_0803E374(void);
void sub_0803E48C(void);
void sub_0803E4B4(void);
void sub_0803E4D8(void);
void sub_0803E618(void);
void sub_0803E7C0(void);
void sub_0803E7F0(void);
void sub_0803EAD8(void);
void sub_0805B0B0(struct FrameObject *object);
void sub_0805B558(void);
void sub_0805B594(void);
void sub_0805FA00(void);
void sub_080602BC(void);
void sub_08060AF4(void);
void sub_080612E8(void);
void sub_08061440(void);
void sub_08061998(void);
void sub_08061E98(void);
void sub_08062970(void);
void sub_08062A10(u32 arg0);
void sub_0806379C(void);
void sub_08064610(void);
void sub_08065198(void);
void sub_080654C0(void);
void sub_0806552C(void);
void sub_08065A80(void);
void sub_08065C98(void);
void sub_08065CFC(void);
void sub_08066240(void);
void sub_08066534(void);
void sub_0806668C(void);
void sub_080666F4(void);
void sub_08068238(void);
void sub_080683C8(void);
void sub_08068E00(void);
void sub_08068F08(void);
void sub_08068F34(void);
void sub_08069168(void);
void sub_08069194(void);
void sub_080691E0(void);
void sub_0806920C(void);
void sub_08069258(void);
void sub_080692A8(void);
void sub_08069DF0(void);
void sub_0806BB24(void);
void sub_0806BB44(void);
void sub_0806BC48(void);
void sub_0806BD3C(void);
void sub_0806E150(void);
void sub_0806E3F8(void);
void sub_0806EAC0(void);
void sub_0806EAF4(void);
void sub_08071030(void);
void sub_0807105C(void);
void sub_080710AC(void);
void sub_080710F4(void);
void sub_08071138(void);
s32 sub_08071E8C(void);
s32 sub_08071EFC(void);
s32 sub_08071F74(void);
void sub_080723AC(void *arg0);
void sub_08072C10(void *arg0);
void sub_08072C20(void *arg0);
void sub_08073044(s32 arg0);
void sub_08073058(void *arg0);
void sub_080736A0(void *arg0);
void sub_08073718(void *arg0);
void sub_08073784(void *arg0);
void sub_08073DF4(s32 arg0);
void sub_08073F6C(void *arg0);
void sub_08074728(void);
void sub_08074834(void);
void sub_0807485C(void);
void sub_08074890(void);
void sub_080748B8(void);
void sub_080748E8(void);

void sub_0800AFF8(void) {
    sub_08042838((u32) gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x1A], 0xBU, 9U, 3U, (u32) *(u16 *)0x0400000A, 0xC3C4U);
    sub_08042838((u32) gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x1B], 0xBU, 0xCU, 3U, (u32) *(u16 *)0x0400000A, 0xC3C4U);
    sub_08042838((u32) gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x1C], 0x19U, 9U, 3U, (u32) *(u16 *)0x0400000A, 0xC3C4U);
    sub_08042838((u32) gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x1D], 0x19U, 0xCU, 3U, (u32) *(u16 *)0x0400000A, 0xC3C4U);
    sub_08042838((u32) gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x1E], 0xBU, 0xFU, 3U, (u32) *(u16 *)0x0400000A, 0xC3C4U);
    sub_08042838((u32) gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x1F], 0xBU, 0x12U, 3U, (u32) *(u16 *)0x0400000A, 0xC3C4U);
    sub_08042838((u32) gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x20], 0x19U, 0xFU, 3U, (u32) *(u16 *)0x0400000A, 0xC3C4U);
    sub_08042838((u32) gInventoryRecords[gState0TypedWork.bytes[0x3D]].unknown06[0x21], 0x19U, 0x12U, 3U, (u32) *(u16 *)0x0400000A, 0xC3C4U);
}

void sub_0800F218(void) {
    s32 sp14;

    gState0TypedWork.bytes[0x3D] = (gState0TypedWork.bytes[0x3F] * 4) + gState0TypedWork.bytes[0x40];
    sub_0803F624(&gRecordDisplayWork, 0xD0U, 0U);
    sub_0803F624(gRecordDisplayData, 0x800U, 0U);
    sub_0803F624(gRecordDisplayExtra, 0x60U, 0U);
    gRenderMode = 2;
    gRenderWork = &gUnknown_02024000;
    sp14 = 0;
    CpuFastSet(&sp14, &gUnknown_02024000, 0x01000426U);
    gRecordDisplayExtraPointer = gRecordDisplayExtra;
    sub_08047414(&gRecordDisplayWork, gRenderWork, gUnknownBytes_083D1D78, gRecordDisplayData);
    gRecordDisplayWork.data = gRecordDisplayData;
    sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, (s32) gState0TypedWork.bytes[0x3D], (s32) gState0TypedWork.bytes[0x3E], 0x3C, 0x28, 0x1C2U, 8U, 1U);
}

void sub_080158D0(u32 arg0) {
    sub_08015838(arg0, &gUnknown_03001864);
    sub_08042D94((u32) (*(u8 *)((u8 *)(&gUnknown_03001864) + 0)), (u32) (*(u8 *)((u8 *)(&gUnknown_03001864) + 1)), (u32) (*(u8 *)((u8 *)(&gUnknown_03001864) + 2)), (u32) (*(u8 *)((u8 *)(&gUnknown_03001864) + 3)), arg0);
}

void sub_08016614(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 9U) {
        sub_08044118(0xBU, 4U, 0x13U, 0x10U, (u32) *(u16 *)0x0400000A, &gState0FrameBackup);
        sub_08044160(0xBU, 4U, 0x14U, 0x10U, (u32) *(u16 *)0x0400000A, &gState0FrameBackup);
    }
}

void sub_08016660(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 4U) {
        sub_08044118(6U, 6U, 0xCU, 0xEU, (u32) *(u16 *)0x0400000A, &gState0FrameBackup);
        sub_08044160(6U, 6U, 0xCU, 0xFU, (u32) *(u16 *)0x0400000A, &gState0FrameBackup);
    }
}

void sub_080166F0(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 3U) {
        sub_08044160(0xCU, 4U, 9U, 0x13 - gState0TypedWork.bytes[0x84], (u32) *(u16 *)0x04000008, &gState0FrameBackup);
    }
}

void sub_0801672C(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 0xBU) {
        sub_08044118(gState0TypedWork.bytes[0x84] + 1, 7U, 0x12U, 0x15U, (u32) *(u16 *)0x0400000A, &gUnknown_02021000);
        sub_08044160(gState0TypedWork.bytes[0x84] + 1, 7U, 0x1D - gState0TypedWork.bytes[0x84], 0xDU, (u32) *(u16 *)0x0400000A, &gUnknown_02021000);
    }
}

void sub_08016E90(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 0xBU) {
        sub_08044118(0xDU, 7U, 0x11U, 0xDU, (u32) *(u16 *)0x0400000A, &gUnknown_02021000);
        sub_08044160(0xDU, 7U, 0x12U, 0xDU, (u32) *(u16 *)0x0400000A, &gUnknown_02021000);
    }
}

void sub_08016EDC(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 3U) {
        sub_08044118(0xCU, 5U, 9U, 0xFU, (u32) *(u16 *)0x04000008, &gState0FrameBackup);
        sub_08044160(0xCU, 5U, 9U, 0x10U, (u32) *(u16 *)0x04000008, &gState0FrameBackup);
    }
}

void sub_08016F28(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 4U) {
        sub_08044160(6U, 5U, 0xCU, 0x13 - gState0TypedWork.bytes[0x84], (u32) *(u16 *)0x0400000A, &gState0FrameBackup);
    }
}

void sub_08016F64(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 9U) {
        sub_08044118(gState0TypedWork.bytes[0x84] + 1, 4U, 0x14U, 0x15U, (u32) *(u16 *)0x0400000A, &gUnknown_02021000);
        sub_08044160(gState0TypedWork.bytes[0x84] + 1, 4U, 0x1D - gState0TypedWork.bytes[0x84], 0x10U, (u32) *(u16 *)0x0400000A, &gUnknown_02021000);
    }
}

void sub_08017048(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 3U) {
        sub_08044160(0xCU, 4U, 9U, 0x13 - gState0TypedWork.bytes[0x84], (u32) *(u16 *)0x04000008, &gState0FrameBackup);
    }
}

void sub_08017084(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 0xBU) {
        sub_08044118(gState0TypedWork.bytes[0x84] + 1, 4U, 0x12U, 0x15U, (u32) *(u16 *)0x0400000A, &gUnknown_02021000);
        sub_08044160(gState0TypedWork.bytes[0x84] + 1, 4U, 0x1D - gState0TypedWork.bytes[0x84], 0xDU, (u32) *(u16 *)0x0400000A, &gUnknown_02021000);
    }
}

void sub_08017948(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 0xBU) {
        sub_08044118(0xDU, 4U, 0x11U, 0xDU, (u32) *(u16 *)0x0400000A, &gUnknown_02021000);
        sub_08044160(0xDU, 4U, 0x12U, 0xDU, (u32) *(u16 *)0x0400000A, &gUnknown_02021000);
    }
}

void sub_08018098(void) {
    s32 sp20;

    sub_0803F624(&gRecordDisplayWork, 0xD0U, 0U);
    sub_0803F624(gRecordDisplayData, 0x800U, 0U);
    sub_0803F624(gRecordDisplayExtra, 0x60U, 0U);
    gState0TypedWork.bytes[0x96] = 1;
    gRenderMode = 2;
    gRenderWork = &gUnknown_02024000;
    sp20 = 0;
    CpuFastSet(&sp20, &gUnknown_02024000, 0x01000426U);
    gRecordDisplayExtraPointer = gRecordDisplayExtra;
    sub_08047414(&gRecordDisplayWork, gRenderWork, gUnknownBytes_083D1D78, gRecordDisplayData);
    gRecordDisplayWork.data = gRecordDisplayData;
    sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork, (u32) gState0TypedWork.bytes[0x98], (u32) gState0TypedWork.bytes[0x99], (u32) (*(u8 *)((u8 *)((&gState0TypedWork.bytes[0x98] + 1)) + 1)), (u32) gState0TypedWork.bytes[0x9B], 0x28U, 0x28U, 0x1C2U, 8U, 1U, 0U);
}

void sub_08018180(void) {
    s32 sp20;

    gRecordDisplayWork.data = gRecordDisplayData;
    sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork, (u32) gState0TypedWork.bytes[0x98], (u32) gState0TypedWork.bytes[0x99], (u32) gState0TypedWork.bytes[0x9A], (u32) gState0TypedWork.bytes[0x9B], 0x28U, 0x28U, 0x1C2U, 8U, 1U, 0U);
    sp20 = 0x200;
    CpuFastSet(&sp20, gRenderWork->objects, 0x01000100U);
    gRenderWork->byte1094 = 0;
    gRenderWork->byte1095 = 0;
}

void sub_08018218(void) {
    sub_08046D1C(gRenderWork->objects, &gRecordDisplayWork, (u32) gState0TypedWork.bytes[0x98], (u32) gState0TypedWork.bytes[0x99], (u32) gState0TypedWork.bytes[0x9A], (u32) gState0TypedWork.bytes[0x9B], 0x44U, 0x2AU, 0x1C2U, 8U, 5U, 0U);
}

void sub_080187A8(void) {
    gState0TypedWork.bytes[0x3D] = 0;
    gState0TypedWork.bytes[0x3C] ^= 1;
    sub_08017A14(gState0TypedWork.bytes[0x3C] * 3, 1);
}

void sub_08018C38(void) {
    u8 temp_r0;

    temp_r0 = (gState0TransferWork.bytes[0x56] + 1) & 0x1F;
    gState0TransferWork.bytes[0x56] = temp_r0;
    if ((temp_r0 == 0) && (gState0TransferWork.bytes[0x57] != 0)) {
        gState0TransferWork.bytes[0x57] -= 1;
        gState0TransferWork.bytes[0x16B] += 1;
        sub_08018CBC();
    }
}

void sub_0801ABF8(void) {
    if ((gMainByte_03001360 == 0) || (gState0TypedWork.bytes[0x89] == 1)) {
        sub_0803FAA0(1U, 2U, 0U);
    }
}

void sub_0801AEF4(void) {
    sub_0803EF8C(0xCU, 7U, 0U, 0xDU, (u32) *(u16 *)0x0400000A, 0U);
    sub_0803EF8C(0xCU, 7U, 0x12U, 0xDU, (u32) *(u16 *)0x0400000A, 0U);
    sub_0803EF8C(0xCU, 7U, 0U, 0xDU, (u32) *(u16 *)0x04000008, 0U);
    sub_0803EF8C(0xCU, 7U, 0x12U, 0xDU, (u32) *(u16 *)0x04000008, 0U);
    sub_08040CD0(0x3CU, 0xAU);
    sub_08040CD0(0x78U, 8U);
    sub_08040CD0(0xAU, 0x17U);
}

void sub_0801C110(void) {
    if (sub_0801AC24(gState0TransferWork.bytes[0xA2]) != 0) {
        gState0TransferWork.bytes[0xA1] += 1;
    }
}

void sub_0801C138(void) {
    if (sub_0801AC6C() != 0) {
        gState0TransferWork.bytes[0xA1] += 1;
    }
}

void sub_0801C32C(void) {
    CpuFastSet(&gUnknown_084E4498, (void *)0x05000300, 8U);
    sub_08016370((u32) gState0TransferWork.bytes[0x87]);
    gState0TransferWork.bytes[0x9C] += 1;
}

void sub_0801C360(void) {
    if (sub_08016438((u32) gState0TransferWork.bytes[0x87]) != 0) {
        gState0TransferWork.bytes[0x9C] += 1;
    }
}

void sub_0801C388(void) {
    sub_080164F4((u32) gState0TransferWork.bytes[0x87]);
    sub_0801AC98(gState0TransferWork.bytes[0x87]);
    gState0TransferWork.bytes[0x9C] += 1;
}

void sub_0801C3F8(void) {
    sub_080164F4((u32) gState0TransferWork.bytes[0x87]);
}

void sub_0801C40C(void) {
    CpuFastSet(&gUnknown_084E44B8, (void *)0x05000320, 8U);
    sub_080164F4((u32) gState0TransferWork.bytes[0x87]);
    sub_0801AD48(gState0TransferWork.bytes[0x87]);
    gState0TransferWork.bytes[0x9C] += 1;
}

void sub_0801C444(void) {
    sub_080164F4((u32) gState0TransferWork.bytes[0x87]);
    if (sub_0801ADE8(gState0TransferWork.bytes[0x87]) != 0) {
        gState0TransferWork.bytes[0x9C] += 1;
    }
}

void sub_0801C470(void) {
    sub_080164F4((u32) gState0TransferWork.bytes[0x87]);
    sub_0801AE70(gState0TransferWork.bytes[0x87]);
    sub_0801AC98(gState0TransferWork.bytes[0x88]);
    gState0TransferWork.bytes[0x9C] += 1;
}

void sub_0801C4A4(void) {
    u8 *temp_r1;

    sub_080164F4((u32) gState0TransferWork.bytes[0x87]);
    sub_0801AE70(gState0TransferWork.bytes[0x87]);
    sub_08015B3C((u32) gState0TransferWork.bytes[0x88]);
    sub_0801AD10(gState0TransferWork.bytes[0x88]);
    gState0TransferWork.bytes[0x9E] = 1;
    temp_r1 = &gState0TransferWork.bytes[0x9E] - 2;
    *temp_r1 += 1;
}

void sub_0801C4E0(void) {
    sub_080164F4((u32) gState0TransferWork.bytes[0x87]);
    sub_0801AE70(gState0TransferWork.bytes[0x87]);
}

void sub_0801E200(void) {
    s32 sp0;

    sp0 = 0;
    CpuFastSet(&sp0, gFrameObjects, 0x01000800U);
    sub_08035C70();
    sub_08035DE8();
    sub_080361A8();
    gState0TypedWork.bytes[0x84] = 0;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0801E248(void) {
    sub_08035DE8();
    sub_080361C4();
    sub_08036218();
    sub_0803EF8C(0x1EU, 1U, 0U, 9 - gState0TypedWork.bytes[0x84], (u32) *(u16 *)0x04000008, 0U);
    sub_0803EF8C(0x1EU, 1U, 0U, gState0TypedWork.bytes[0x84] + 0xA, (u32) *(u16 *)0x04000008, 0U);
    if (gState0TypedWork.bytes[0x84] == 9) {
        gState0TransferWork.bytes[0xAA] += 1;
        return;
    }
    gState0TypedWork.bytes[0x84] += 1;
}

void sub_0801E2B8(void) {
    sub_08035DE8();
    sub_080361C4();
    sub_08036218();
    gState0TransferWork.bytes[0xB5] = 1;
}

void sub_0801E54C(void) {
    if (sub_080353CC(0xAU) != 0) {
        gState0TypedWork.widths.word86 = 0x3C;
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_0801E830(void) {
    if (sub_080366DC(0xA, gState0TransferWork.bytes[0x8B]) != 0) {
        gState0TypedWork.widths.word86 = 0x3C;
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_0801E8DC(void) {
    CpuFastSet(gActionMotionPalette_0850F8D8, (void *)0x050003C0, 8U);
    if (sub_0803684C(0xA) != 0) {
        gState0TypedWork.widths.word86 = 0xA;
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_0801E9E0(void) {
    sub_08074DE0(0x2FU);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0801EBD4(void) {
    sub_08035F20();
    gState0TypedWork.widths.word86 = 0x3C;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0801F374(void) {
    sub_08074DE0(0x2EU);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0801F9B0(void) {
    sub_08036DE8(0xA, 0);
    if (sub_08036DE8(0xB, 1) != 0) {
        sub_08074DE0(0x2AU);
        gState0TypedWork.widths.word86 = 0x5A;
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_0801FA68(void) {
    s32 sp0;
    s32 sp4;

    sub_08035DE8();
    gState0TransferWork.bytes[0x15F] = (u8) sub_080361C4();
    gState0TransferWork.bytes[0x160] = (u8) sub_08036218();
    gState0TypedWork.bytes[0x84] = 0;
    sp0 = 0;
    CpuFastSet(&sp0, (void *)0x05000120, 0x01000008U);
    sp4 = 0x11111111;
    CpuFastSet(&sp4, (void *)0x06004120, 0x01000008U);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0801FD88(void) {
    sub_0803EF8C(0x1EU, 1U, 0U, 9 - gState0TypedWork.bytes[0x84], (u32) *(u16 *)0x04000008, 0U);
    sub_0803EF8C(0x1EU, 1U, 0U, gState0TypedWork.bytes[0x84] + 0xA, (u32) *(u16 *)0x04000008, 0U);
    if (gState0TypedWork.bytes[0x84] == 9) {
        gState0TransferWork.bytes[0xAA] += 1;
        return;
    }
    gState0TypedWork.bytes[0x84] += 1;
}

void sub_0801FEC8(void) {
    if (sub_080370AC(0x21U, 8U) != 0) {
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08020288(void) {
    LeDecompress(&gUnknown_084CB9C8, (void *)0x06010000);
    CpuFastSet(&gUnknown_0850F718, (void *)0x050003C0, 8U);
    gFrameObjects[0xA].byte2B = 0;
    gFrameObjects[0xA].unknown2C[0] = 0;
    sub_08074DE0(0x2FU);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08020608(void) {
    if (sub_080370AC(0x21U, 4U) != 0) {
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08020728(void) {
    sub_08035164((u32) gState0TransferWork.bytes[0x87], (u32) gState0TransferWork.bytes[0xA7], 0xFF);
    sub_080158F8();
    sub_0801A0D0();
    if (gState0TransferWork.bytes[0xA7] == 0) {
        sub_08035234((u32) gState0TransferWork.bytes[0x87]);
    }
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08020768(void) {
    sub_0803F63C(gState0PartMessages_083C6F68[gState0TransferWork.bytes[0xA7]], gDebugMenuTextBuffer, 0xEU);
    gState0TransferWork.bytes[0xA6] = 0x18;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_080208E8(void) {
    sub_08040CD0(0U, 0x80U);
    gState0TransferWork.bytes[0xD0] = gState0TransferWork.bytes[0x8B];
    sub_08036CCC(gState0TransferWork.bytes[0x88], gState0TransferWork.bytes[0xD0], (*(s16 *)((u8 *)(&gState0TransferWork) + 0xEC)));
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08020A90(void) {
    sub_08040CD0(0U, 0x80U);
    gState0TransferWork.bytes[0xD0] = gState0TransferWork.bytes[0x8B];
    sub_080372D4(gState0TransferWork.bytes[0x88], gState0TransferWork.bytes[0xD0], (*(s16 *)((u8 *)(&gState0TransferWork) + 0xEC)));
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_080215C8(void) {
    gFrameObjects[0x21].unknown23[1] = 4;
    gFrameObjects[0x21].unknown23[2] = 0;
    (*(s16 *)((u8 *)(gFrameObjects) + 0x870)) = 0;
    sub_08074DE0(0x40U);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08021608(void) {
    if (sub_080352EC(0x21U, -0x40, -0x30) != 0) {
        sub_08040CD0(0x21U, 1U);
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08021734(void) {
    u32 temp_r0;
    u32 var_r4;

    temp_r0 = sub_080355F0(0x21U);
    var_r4 = (u32) ((0 - temp_r0) | temp_r0) >> 0x1F;
    if (sub_080355F0(0x22U) != 0) {
        var_r4 += 1;
    }
    if (sub_080355F0(0x23U) != 0) {
        var_r4 += 1;
    }
    if (var_r4 == 3) {
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_080231D4(void) {
    if (gFrameObjects[0x21].unknown2C[1] == 0x40) {
        sub_08040CD0(0x21U, 2U);
        gState0TransferWork.bytes[0xAA] += 1;
        return;
    }
    gFrameObjects[0x21].unknown2C[1] += 1;
    gFrameObjects[0x21].angle = (gFrameObjects[0x21].angle + 0x10) & 0x3FF;
}

void sub_080233E0(void) {
    sub_08035740((gState0TransferWork.bytes[0x89] * 8) + &gState0TransferWork.bytes[0x28], (*(s16 *)((u8 *)(&gState0TransferWork) + 0xEC)), 0xA0);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_080241F0(void) {
    if (sub_080355F0(0x21U) != 0) {
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08024870(void) {
    if (sub_080370AC(0x21U, 4U) != 0) {
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08024BCC(void) {
    if (sub_08036AC4(0x22U, 0U) != 0) {
        gState0TypedWork.widths.word86 = 0x3C;
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08024BF8(void) {
    sub_08040D44(0x21U, 1U);
    gFrameObjects[0x21].flags |= 0x220;
    gFrameObjects[0x21].scaleX = 0x80;
    gFrameObjects[0x21].scaleY = 0x80;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08024F90(void) {
    sub_08074DE0(0x33U);
    gFrameObjects[0x21].flags |= 0x220;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08025354(void) {
    if (sub_080355F0(0x21U) != 0) {
        gState0TransferWork.bytes[0xAA] += 1;
    }
    sub_08037424(0x21);
}

void sub_08025500(void) {
    if (sub_080355F0(0x21U) != 0) {
        gFrameObjects[0x22].screenX = (s16) (u16) gFrameObjects[0x21].screenX;
        gFrameObjects[0x22].screenY = (s16) (u16) gFrameObjects[0x21].screenY;
        sub_08074DE0(0x2BU);
        gState0TransferWork.bytes[0xAA] += 1;
    }
    sub_08037424(0x21);
    gFrameObjects[0x22].screenX = (s16) (u16) gFrameObjects[0x21].screenX;
    gFrameObjects[0x22].screenY = (s16) (u16) gFrameObjects[0x21].screenY;
}

void sub_08025674(void) {
    u8 *temp_r5;

    LeDecompress(&gUnknown_084D819C, (void *)0x06017E00);
    sub_0801A28C(gUnknown_0300052E, (u32) gState0TransferWork.bytes[0x51], 1U);
    sub_0801A418(gUnknown_0300052E, gState0TransferWork.bytes[0x88], 0x21);
    temp_r5 = gUnknown_0300052E + 0x20;
    sub_0801A28C(temp_r5, (u32) gState0TransferWork.bytes[0x52], 0U);
    sub_0801A418(temp_r5, gState0TransferWork.bytes[0x87], 0x21);
    sub_08074DE0(0x5BU);
    *(gUnknown_0300052E - 0x6A) = 0;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08025790(void) {
    sub_08041490(gDebugMenuTextBuffer, (u32) gState0TransferWork.bytes[0x51], 0x35U);
    gState0TransferWork.bytes[0xA6] = 0x35;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08025D2C(void) {
    if (sub_0801C2F0(0) != 0) {
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08025D4C(void) {
    sub_0801C2F0(0);
    sub_08074DE0(0x51U);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_080260EC(void) {
    sub_08040CD0(0x21U, 3U);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08026810(void) {
    sub_08040CD0(0x21U, 2U);
    sub_08041D04((u8 *) gPartTextPointers_083BBB4C[(gState0TransferWork.bytes[0x133] * 4) + gState0TransferWork.bytes[0xA7]], gDebugMenuTextBuffer, 0xFU);
    sub_08041D04((u8 *) gPartTextPointers_083BBB4C[(gState0TransferWork.bytes[0x11A] * 4) + gState0TransferWork.bytes[0xA7]], gDebugMenuTextBuffer + 0x14, 0xFU);
    gState0TransferWork.bytes[0xA6] = 0x2F;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_080268AC(void) {
    sub_0803769C((u32) gState0TransferWork.bytes[0x87]);
    sub_080376F4((u32) gState0TransferWork.bytes[0x87]);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_080268D4(void) {
    sub_08037728(gState0TransferWork.bytes[0x88], 0, (*(s16 *)((u8 *)(&gState0TransferWork) + 0xEC)));
    sub_08037728(gState0TransferWork.bytes[0x88], 1, (*(s16 *)((u8 *)(&gState0TransferWork) + 0xEC)));
    sub_08037728(gState0TransferWork.bytes[0x88], 2, (*(s16 *)((u8 *)(&gState0TransferWork) + 0xEC)));
    sub_08037728(gState0TransferWork.bytes[0x88], 3, (*(s16 *)((u8 *)(&gState0TransferWork) + 0xEC)));
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08026F34(void) {
    sub_08040CD0(0U, 0x80U);
    sub_08036CCC(gState0TransferWork.bytes[0x87], gState0TransferWork.bytes[0xD0], (*(s16 *)((u8 *)(&gState0TransferWork) + 0xEC)));
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802733C(void) {
    gState0TypedWork.widths.word86 += 1;
    sub_080378A8();
    if (gState0TypedWork.widths.word86 == 0x10) {
        SnapshotPalettes();
        gState0TypedWork.bytes[0x84] = 0;
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08027378(void) {
    gState0TypedWork.widths.word86 += 1;
    sub_080378A8();
    if ((u32) gState0TypedWork.bytes[0x84] <= 4U) {
        sub_0803F684(0x7FFFU, gState0TypedWork.bytes[0x84] * 8, 0xFFFFU);
        sub_0803F998(0x7FFFU, gState0TypedWork.bytes[0x84] * 8, 0xFFFFU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    gState0TypedWork.bytes[0x84] = 0;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_080273DC(void) {
    gState0TypedWork.widths.word86 += 1;
    sub_080378A8();
    if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
        sub_0803F684(0x7FFFU, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0xFFFFU);
        sub_0803F998(0x7FFFU, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0xFFFFU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_08027444(void) {
    gState0TypedWork.widths.word86 += 1;
    sub_080378A8();
    if ((u32) gState0TypedWork.widths.word86 > 0x23U) {
        sub_08040CD0(0x21U, 1U);
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_080287C0(void) {
    if (sub_08037B9C() != 0) {
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_0802A2D4(void) {
    if (gFrameObjects[0x21].screenY == 0x20) {
        sub_08074DE0(0x42U);
        gState0TransferWork.bytes[0xAA] += 1;
        return;
    }
    gFrameObjects[0x21].screenY = (u16) gFrameObjects[0x21].screenY - 1;
    gFrameObjects[0x22].screenY = (u16) gFrameObjects[0x22].screenY - 1;
}

void sub_0802C24C(void) {
    sub_08035740((gState0TransferWork.bytes[0x89] * 8) + &gState0TransferWork.bytes[0x28], (*(s16 *)((u8 *)(&gState0TransferWork) + 0xEC)), 0xA0);
    sub_0803572C((gState0TransferWork.bytes[0x8A] * 8) + &gState0TransferWork.bytes[0x28], (*(s16 *)((u8 *)(&gState0TransferWork) + 0xEC)));
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802C66C(void) {
    LeDecompress(&gUnknown_084E1584, (void *)0x06014800);
    CpuFastSet(&gUnknown_08510418, (void *)0x050002E0, 8U);
    gFrameObjects[0x21].flags = 0xC604;
    gFrameObjects[0x21].tableSelector = 0;
    gFrameObjects[0x21].screenX = 0x78;
    gFrameObjects[0x21].screenY = 0x40;
    gFrameObjects[0x21].scaleX = 4;
    gFrameObjects[0x21].scaleY = 4;
    gFrameObjects[0x21].palette = 7;
    gFrameObjects[0x21].priority = 0xF0;
    gFrameObjects[0x21].frameAndGroup = 0x7D00;
    sub_08074DE0(0x6EU);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802D6B0(void) {
    LeDecompress(&gUnknown_084E1900, (void *)0x06014800);
    CpuFastSet(&gUnknown_08510438, (void *)0x050002E0, 8U);
    gFrameObjects[0x21].flags = 0xC604;
    gFrameObjects[0x21].tableSelector = 0;
    gFrameObjects[0x21].screenX = 0x78;
    gFrameObjects[0x21].screenY = 0x40;
    gFrameObjects[0x21].scaleX = 4;
    gFrameObjects[0x21].scaleY = 4;
    gFrameObjects[0x21].palette = 7;
    gFrameObjects[0x21].priority = 0xF0;
    gFrameObjects[0x21].frameAndGroup = 0x7E00;
    sub_08074DE0(0x6EU);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802DF18(void) {
    gFrameObjects[0x21].frameAndGroup = 0x7F02;
    sub_08074DE0(0x38U);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802E1A4(void) {
    sub_08040CD0(0x21U, 3U);
    gState0TransferWork.bytes[0xA6] = 0x43;
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802EAA4(void) {
    if (sub_080385F8() != 0) {
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_0802F468(void) {
    if (sub_080355F0(0x21U) != 0) {
        sub_08074DE0(0x2BU);
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_0802F864(void) {
    sub_08074DE0(0x22U);
    gState0TransferWork.bytes[0xAA] += 1;
}

void sub_0802F880(void) {
    if (sub_0803884C() != 0) {
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_080305E0(void) {
    if (sub_0801C0BC(gState0TransferWork.bytes[0xA6]) != 0) {
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08030608(void) {
    if (sub_0801C154() != 0) {
        gState0TransferWork.bytes[0xAA] += 1;
    }
}

void sub_08030D3C(void) {
    if (sub_0801C154() != 0) {
        gUnknown_0300137C += 1;
    }
}

void sub_08030D74(void) {
    if (sub_0801C2F0(0) != 0) {
        gUnknown_0300137C += 1;
    }
}

void sub_08030E54(void) {
    if (sub_0801C0BC(gState0TransferWork.bytes[0xA6]) != 0) {
        gUnknown_0300137C += 1;
    }
}

void sub_080312F0(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
        sub_0803F684(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
        sub_0803F998(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    gUnknown_0300137C += 1;
}

void sub_08031438(void) {
    if (sub_08036AC4(0x21U, 0U) != 0) {
        gUnknown_0300137C += 1;
    }
}

void sub_08031518(void) {
    if (sub_08036DE8(0x22, 0) != 0) {
        gUnknown_0300137C += 1;
    }
}

void sub_08031978(void) {
    sub_0803FAA0(1U, 0U, 0U);
    gUnknown_0300137C += 1;
}

void sub_080319B8(void) {
    if (sub_0803E79C() != 0) {
        gState0TypedWork.widths.word86 = 0;
        gUnknown_0300137C += 1;
    }
}

void sub_08031A08(void) {
    if (sub_08041CA4() != 0) {
        gUnknown_0300137C += 1;
    }
}

void sub_08031A24(void) {
    sub_080750F0(8U);
    gUnknown_0300137C = 0x51;
}

void sub_08031A3C(u32 selected) {
    u32 var_r4;

    gState0TransferWork.bytes[0x5C] = (u8) selected;
    gState0TransferWork.bytes[0x5D] = 0;
    var_r4 = 0;
    do {
        sub_08031A70();
        sub_08031ABC();
        gState0TransferWork.bytes[0x5D] += 1;
        var_r4 += 1;
    } while (var_r4 <= 2U);
}

u32 sub_080361C4(void) {
    u32 temp_r0;

    if (!(0x80 & gState0TransferWork.bytes[0x112]) && !(1 & gState0TransferWork.bytes[0xFF])) {
        sub_08036120(0);
        temp_r0 = sub_08044A3C(0U, (u32) gState0TransferWork.bytes[0x112], (u32) gState0TransferWork.bytes[0x67]);
        if (temp_r0 != 0) {
            gState0TransferWork.bytes[0x112] |= 0x80;
        }
        return temp_r0;
    }
    return 1U;
}

u32 sub_08036218(void) {
    u32 temp_r0;

    if (!(0x80 & gState0TransferWork.bytes[0x113]) && !(2 & gState0TransferWork.bytes[0xFF])) {
        sub_08036120(1);
        temp_r0 = sub_08044A3C(1U, (u32) gState0TransferWork.bytes[0x113], (u32) gState0TransferWork.bytes[0x67]);
        if (temp_r0 != 0) {
            gState0TransferWork.bytes[0x113] |= 0x80;
        }
        return temp_r0;
    }
    return 1U;
}

void sub_080362C4(s32 arg0) {
    u32 var_r5;

    var_r5 = 2;
    if (arg0 == 0) {
        var_r5 = 0x10;
    }
    sub_08042698(2U, 2U, var_r5, 1U, (u32) *(u16 *)0x0400000A, 0xB340U);
    sub_08042698(2U, 2U, var_r5, 4U, (u32) *(u16 *)0x0400000A, 0xB344U);
    sub_08042698(2U, 2U, var_r5, 7U, (u32) *(u16 *)0x0400000A, 0xB348U);
    sub_08042698(2U, 2U, var_r5, 0xAU, (u32) *(u16 *)0x0400000A, 0xB34CU);
}

void sub_08036BF4(s32 arg0) {
    u32 var_r2;

    var_r2 = 2;
    if (arg0 == 0) {
        var_r2 = 0x10;
    }
    sub_0803EF8C(0xCU, 0xDU, var_r2, 0U, (u32) *(u16 *)0x0400000A, 0U);
}

void sub_0803809C(void) {
    sub_08040CD0(gState0TypedWork.bytes[0x12F], 1U);
}

void sub_080393BC(void) {
    if (gFrameObjects->unknown23[7] == 0) {
        do {
            sub_080393EC();
        } while (gFrameObjects->unknown23[7] == 0);
    }
    sub_0803B8C8();
    gFrameObjects->unknown23[7] = 0;
}

void sub_0803A0B8(void) {
    if (gFrameObjects[0x1E].unknown23[6] == 0) {
        sub_0803D4AC();
    }
    gFrameObjects->unknown23[7] = 1;
}

void sub_0803A264(void) {
    sub_0803D450();
    if (!(2 & gState0TransferWork.bytes[0xF8])) {
        if ((s32) gFrameObjects[(*(s16 *)((u8 *)(&gState0TransferWork) + 0x104))].screenX >= (s32) (*(s16 *)((u8 *)(&gState0TransferWork) + 0x102))) {
            sub_0803D4AC();
        }
    } else if ((s32) gFrameObjects[(*(s16 *)((u8 *)(&gState0TransferWork) + 0x104))].screenX <= (s32) (0xF0 - (*(s16 *)((u8 *)(&gState0TransferWork) + 0x102)))) {
        sub_0803D4AC();
    }
    gFrameObjects->unknown23[7] = 1;
}

void sub_0803A2E8(void) {
    sub_0803D450();
    sub_08040CD0(gState0TransferWork.bytes[0x102], gState0TransferWork.bytes[0x104]);
    sub_0803D4AC();
}

void sub_0803A444(void) {
    *(u16 *)0x04000008 = 0x4500;
    sub_0803EFD8(0x40U, 0x20U, 0U, 0U, (u32) *(u16 *)0x04000008, 0U);
    sub_0803D4AC();
}

void sub_0803A6FC(void) {
    sub_0803EFD8(0x20U, 0x20U, 0U, 0U, (u32) *(u16 *)0x04000008, 0U);
    sub_0803EFD8(0x20U, 0x20U, 0x20U, 0U, (u32) *(u16 *)0x04000008, 0U);
    *(u16 *)0x04000008 = 0x500;
    gBgScroll0.x = 0;
    gBgScroll1.x = 0;
    sub_08040CD0(4U, 1U);
    sub_08040CD0(0x23U, 1U);
    sub_0803D4AC();
}

void sub_0803A920(void) {
    gFrameObjects[0x23].unknown23[4] = 1;
    sub_0803D4AC();
}

void sub_0803AB9C(void) {
    if (!(2 & gState0TransferWork.bytes[0xF8])) {
        CpuFastSet((void *)0x05000300, &gUnknown_0202F900, 8U);
        CpuFastSet((void *)0x05000320, &gUnknown_0202F920, 8U);
        CpuFastSet((void *)0x05000340, &gUnknown_0202F940, 8U);
        CpuFastSet((void *)0x05000360, &gUnknown_0202F960, 8U);
    } else {
        CpuFastSet((void *)0x05000280, &gUnknown_0202F880, 8U);
        CpuFastSet((void *)0x050002A0, &gUnknown_0202F8A0, 8U);
        CpuFastSet((void *)0x050002C0, &gUnknown_0202F8C0, 8U);
        CpuFastSet((void *)0x050002E0, &gUnknown_0202F8E0, 8U);
    }
    sub_0803D4AC();
}

void sub_0803B6D8(void) {
    if (gFrameObjects[9].unknown23[6] == 0) {
        sub_0803D4AC();
    }
    gFrameObjects->unknown23[7] = 1;
}

void sub_0803B700(void) {
    sub_0803EF8C(0x20U, 0x20U, 0U, 0U, (u32) *(u16 *)0x04000008, 0U);
    sub_0803EF8C(0x20U, 0x20U, 0U, 0U, (u32) *(u16 *)0x0400000A, 0U);
    sub_08040CD0(4U, 1U);
    sub_08040CD0(0x23U, 1U);
    sub_0803D4AC();
}

void sub_0803D5E0(void) {
    if (sub_0803E79C() != 0) {
        gState0TypedWork.widths.word86 = 0;
        gUnknown_0300137C += 1;
    }
}

void sub_0803D928(void) {
    sub_08043CD4();
    if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
        sub_0803F684(0U, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0xFFFFU);
        sub_0803F998(0U, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0xFFFFU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    gUnknown_0300137C += 1;
}

void sub_0803D980(void) {
    sub_08043CD4();
    sub_0803FAA0(1U, 0U, 0U);
    gUnknown_0300137C += 1;
}

void sub_0803D9C8(void) {
    sub_08043CD4();
    SnapshotPalettes();
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C += 1;
}

void sub_0803D9F0(void) {
    sub_08043CD4();
    if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
        sub_0803F684(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
        sub_0803F998(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    gUnknown_0300137C += 1;
}

void sub_0803DA40(void) {
    sub_08043CD4();
    if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
        sub_0803F684(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
        sub_0803F998(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    gUnknown_0300137C += 1;
}

void sub_0803DA90(void) {
    sub_0804253C(0U, 0U, 0U);
    sub_0803EF8C(0x20U, 0x20U, 0U, 0U, (u32) *(u16 *)0x04000008, 0U);
    sub_0803EF8C(0x20U, 0x20U, 0U, 0U, (u32) *(u16 *)0x0400000A, 0U);
    sub_08040CD0(0U, 0x80U);
    gUnknown_0300137C += 1;
}

void sub_0803DB1C(void) {
    if (gState0TypedWork.bytes[0x9C] == 1) {
        sub_08074B88(0xEU);
    } else {
        sub_08074B88(0xFU);
    }
    gUnknown_0300137C += 1;
}

void sub_0803DB94(void) {
    sub_08043CD4();
    if (sub_08041CD4() != 0) {
        sub_0803FB0C();
        gUnknown_0300137C += 1;
    }
}

void sub_0803DBE0(void) {
    sub_08043CD4();
    if (sub_0803E79C() != 0) {
        gState0TypedWork.widths.word86 = 0;
        gUnknown_0300137C += 1;
    }
}

void sub_0803DC0C(void) {
    sub_08043CD4();
    if (gState0TypedWork.widths.word86 == 8) {
        gState0TypedWork.widths.word86 = 0;
        gUnknown_0300137C += 1;
        return;
    }
    gState0TypedWork.widths.word86 += 1;
}

void sub_0803DC3C(void) {
    sub_08043CD4();
    sub_080750F0(8U);
    gUnknown_0300137C += 1;
}

void sub_0803DC8C(void) {
    s32 sp0;
    s32 sp4;

    sub_08040CD0(0U, 0x80U);
    sub_08043CA8();
    sp0 = 0;
    CpuFastSet(&sp0, (void *)0x05000200, 0x01000080U);
    sp4 = 0;
    CpuFastSet(&sp4, (void *)0x05000000, 0x01000080U);
    sub_0804253C(5U, 0x3FU, 0x20U);
    sub_08044CDC(3U);
}

void sub_0803DCDC(void) {
    s32 sp4;

    sub_08043CA8();
    sub_0804253C(5U, 0x3FU, 0x20U);
    *(u16 *)0x04000000 &= 0xE0FF;
    *(u16 *)0x04000008 = 0x500;
    *(u16 *)0x0400000A = 0x1801;
    *(u16 *)0x0400000C = 0x1902;
    *(u16 *)0x0400000E = 0x1B03;
    LeDecompress(&gUnknown_084EF490, (void *)0x06004000);
    LeDecompress(&gUnknown_084C7C54, (void *)0x06007000);
    LeDecompress(&gUnknown_084C7E7C, (void *)0x06007A00);
    LeDecompress(gMain2SharedObjectTiles_084C8034, (void *)0x06017400);
    LeDecompress(&gUnknown_084E3698, (void *)0x06010000);
    LoadLeTilemap(0U, 0U, &gUnknown_084F0C08, (u32) *(u16 *)0x04000008, 0x200U);
    LoadLeTilemap(0U, 0U, &gUnknown_084F1734, (u32) *(u16 *)0x0400000A, 0x200U);
    LoadLeTilemap(0U, 0U, &gUnknown_084F233C, (u32) *(u16 *)0x0400000C, 0x200U);
    LoadLeTilemap(0U, 0U, &gUnknown_084F3788, (u32) *(u16 *)0x0400000E, 0x200U);
    CpuFastSet(&gUnknown_084F4F40, (void *)0x05000000, 0x60U);
    CpuFastSet(&gUnknown_085104F8, (void *)0x05000200, 0x10U);
    sp4 = 0;
    CpuFastSet(&sp4, gFrameObjects, 0x01000800U);
    *(u16 *)0x04000000 |= 0x1F60;
    sub_0803E8B8();
    sub_0803E8EC();
    sub_0803E934();
    sub_0803E978();
    sub_0803E9BC();
    gState0TransferWork.bytes[0x1A0] = 0;
    sub_08074B88(0x14U);
    gUnknown_0300137C += 1;
}

void sub_0803DE70(void) {
    sub_0803E894();
    if (sub_080425DC() != 0) {
        gUnknown_0300137C += 1;
    }
}

void sub_0803DE90(void) {
    sub_0803E894();
    sub_0803FAA0(1U, 0U, 0U);
    gUnknown_0300137C += 1;
}

void sub_0803E018(void) {
    sub_0803E894();
    sub_0803EB30();
    sub_0803EB5C();
    sub_0803EC04();
    gUnknown_0300137C += 1;
}

void sub_0803E098(void) {
    sub_0803E894();
    if (sub_0803EC98() != 0) {
        sub_0803ECF0();
        sub_0803ED10();
        gUnknown_0300137C += 1;
    }
}

void sub_0803E0C0(void) {
    sub_0803E894();
    if (sub_0803ED28() != 0) {
        sub_08074DE0(0x2AU);
        gState0TypedWork.widths.word86 = 0;
        gUnknown_0300137C += 1;
    }
}

void sub_0803E0F0(void) {
    sub_0803E894();
    sub_0803ED6C();
    if (gState0TypedWork.widths.word86 == 0x78) {
        gUnknown_0300137C += 1;
        return;
    }
    gState0TypedWork.widths.word86 += 1;
}

void sub_0803E170(void) {
    sub_0803E894();
    sub_0803ED6C();
    gState0TypedWork.widths.word86 += 1;
    sub_0803FAA0(1U, 0U, 0U);
    gUnknown_0300137C += 1;
}

void sub_0803E234(void) {
    sub_0803E894();
    sub_0803ED6C();
    gState0TypedWork.widths.word86 += 1;
    if (sub_0803E79C() != 0) {
        gState0TypedWork.bytes[0x84] = 0;
        gUnknown_0300137C += 1;
    }
}

void sub_0803E270(void) {
    sub_0803E894();
    sub_0803ED6C();
    gState0TypedWork.widths.word86 += 1;
    if (gState0TypedWork.bytes[0x84] == 4) {
        gState0TypedWork.bytes[0x84] = 0;
        gUnknown_0300137C += 1;
        return;
    }
    gState0TypedWork.bytes[0x84] += 1;
}

void sub_0803E2AC(void) {
    sub_0803E894();
    sub_0803ED6C();
    gState0TypedWork.widths.word86 += 1;
    sub_080750F0(8U);
    gUnknown_0300137C += 1;
}

void sub_0803E2DC(void) {
    sub_0803E894();
    sub_0803ED6C();
    gState0TypedWork.widths.word86 += 1;
    SnapshotPalettes();
    gState0TypedWork.bytes[0x84] = 0;
    gUnknown_0300137C += 1;
}

void sub_0803E314(void) {
    sub_0803E894();
    sub_0803ED6C();
    gState0TypedWork.widths.word86 += 1;
    if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
        sub_0803F684(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
        sub_0803F998(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    gUnknown_0300137C += 1;
}

void sub_0803E374(void) {
    sub_0803E894();
    sub_0803ED6C();
    gState0TypedWork.widths.word86 += 1;
    sub_0803EE10();
    if (gState0TypedWork.bytes[0x9C] == 1) {
        sub_0804213C(gState0TransferWork.bytes[0x1A5], (&gState0TransferWork.bytes[0x19A])[gState0TransferWork.bytes[0x1A2]], 1U);
    } else {
        sub_080421B4((u32) gState0TransferWork.bytes[0x1A4], (u32) (&gState0TransferWork.bytes[0x19A])[gState0TransferWork.bytes[0x1A2]]);
    }
    sub_08041D04((u8 *) gPartTextPointers_083BBB4C[(gState0TransferWork.bytes[0x1A5] * 4) + (&gState0TransferWork.bytes[0x19A])[gState0TransferWork.bytes[0x1A2]]], gDebugMenuTextBuffer, 0xFU);
    gUnknown_0300137C += 1;
}

void sub_0803E48C(void) {
    sub_0803E894();
    sub_0803ED6C();
    gState0TypedWork.widths.word86 += 1;
    gUnknown_0300137C = 0x3E;
}

void sub_0803E4B4(void) {
    sub_080750F0(8U);
    sub_0804253C(6U, 0x3FU, 0x20U);
    gUnknown_0300137C += 1;
}

void sub_0803E4D8(void) {
    if (sub_080425DC() != 0) {
        gUnknown_0300137C += 1;
    }
}

void sub_0803E618(void) {
    sub_0803FAA0(1U, 0U, 0U);
    gUnknown_0300137C += 1;
}

void sub_0803E7C0(void) {
    sub_08040EE4(&gUnknown_0300198A, 0xAU, 0x12, 3, 0xAU, 0xDU, 0U, 1U, 0, -4);
}

void sub_0803E7F0(void) {
    sub_0803F63C(gState0MapPartLabels_083BEB68[gState0TransferWork.bytes[0x38]], gDebugMenuTextBuffer, 0xBU);
    sub_08040DB8(gDebugMenuTextBuffer, 0x1EU, 1, 3, 8U, 0xCU, 0U, 1U);
}

void sub_0803EAD8(void) {
    u32 var_r4;

    var_r4 = 0;
    do {
        sub_08042698(1U, 1U, var_r4 + 7, 0x12U, (u32) *(u16 *)0x0400000A, 0x53D0U);
        var_r4 += 1;
    } while (var_r4 <= 0xBU);
}

void sub_0805B0B0(struct FrameObject *object) {
    object->screenX = 0x54;
    object->screenY = ((u32) (sub_0807CF40((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0xC)), 5) << 0x18) >> 0x14) + 0x1C;
}

void sub_0805B558(void) {
    sub_0805A3A4(sub_0807CEC8((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0xC)), 5) + 1, 2, 3);
    sub_0805A3A4(sub_0807CD2C((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x10)) - 1, 5) + 1, 5, 3);
}

void sub_0805B594(void) {
    sub_0803F65C(gObjectCountPairs[(*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x13))], gObjectCountPairs[(*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0xC))], 2U);
}

void sub_0805FA00(void) {
    if (sub_08041CA4() != 0) {
        gUnknown_0300137C = 4;
    }
}

void sub_080602BC(void) {
    s32 sp0;

    sp0 = 0;
    CpuFastSet(&sp0, (void *)0x06000000, 0x01006000U);
    sub_080415BC();
    sub_08040CD0(0U, 0x80U);
    (*(s16 *)((u8 *)((void *)0x04000000) + 0)) = 0x60;
    (*(s16 *)((u8 *)((void *)0x04000000) + 0x50)) = 0x2FF;
    (*(s16 *)((u8 *)(((void *)0x04000000 + 0x50)) + 4)) = 0x10;
    gUnknown_0300137C += 1;
}

void sub_08060AF4(void) {
    sub_080605A0();
    sub_08060620();
    if (sub_08041CA4() != 0) {
        SnapshotPalettes();
        gState0TypedWork.bytes[0x84] = 0;
        gUnknown_0300137C += 1;
    }
}

void sub_080612E8(void) {
    void *temp_r4;

    temp_r4 = gMainContextPointer_03006F74 + 0x270;
    sub_08060D28(temp_r4, &gUnknown_08484FC0);
    if (sub_0803FB3C(temp_r4) != 0) {
        gFrameObjects[8].flags |= 0x4000;
        gUnknown_0300137C += 1;
    }
}

void sub_08061440(void) {
    if (sub_08041CA4() != 0) {
        gState0TypedWork.bytes[0x84] = 0;
        gUnknown_0300137C += 1;
    }
}

void sub_08061998(void) {
    sub_080415BC();
    gUnknown_0300137C += 1;
}

void sub_08061E98(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
        sub_0803F684(0U, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0xFFFEU);
        sub_0803F998(0U, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0x7FFDU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    sub_0805B984();
    (*(s16 *)((u8 *)(gMainContextPointer_03006F74) + 2)) = 0;
    gUnknown_0300137C += 1;
}

void sub_08062970(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
        sub_0803F684(0U, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0xFFFFU);
        sub_0803F998(0U, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0xFFFFU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    sub_0805B984();
    (*(s16 *)((u8 *)(gMainContextPointer_03006F74) + 2)) = 0;
    gMainSubstate = 0xC;
    gUnknown_0300137C = 4;
}

void sub_08062A10(u32 arg0) {
    u32 sp14;

    if (arg0 == 0) {
        sub_0803F624(&gRecordDisplayWork, 0xD0U, 0U);
        sub_0803F624(gRecordDisplayData, 0x820U, 0U);
        sub_0803F624(&gUnknown_020264E0, 0x820U, 0U);
        sub_0803F624(&gUnknown_020268F0, 0x60U, 0U);
        gRenderMode = 2;
        gRenderWork = &gUnknown_02024000;
        sp14 = arg0;
        CpuFastSet(&sp14, &gUnknown_02024000, 0x01000426U);
        gRecordDisplayExtraPointer = &gUnknown_020268F0;
        sub_08047414(&gRecordDisplayWork, gRenderWork, gUnknownBytes_083D1D78, gRecordDisplayData);
        gRecordDisplayWork.data = gRecordDisplayData;
        sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, (s32) (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x31)), (s32) (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x33)), 0x3C, 0x28, 0x12BU, arg0, 1U);
        return;
    }
    sub_08047414(&gRecordDisplayWork, gRenderWork, gUnknownBytes_083D1D78, &gUnknown_020264E0);
    gRecordDisplayWork.data = &gUnknown_020264E0;
    sub_08046A60(gRenderWork->objects, &gRecordDisplayWork, (s32) (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x32)), (s32) (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x34)), 0x3C, 0x28, 0x12BU, 4U, 2U);
}

void sub_0806379C(void) {
    sub_08062B48((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x31)), (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x33)), 0);
    sub_08062B48((*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x32)), (*(u8 *)((u8 *)(gMainContextPointer_03006F74) + 0x34)), 1);
    sub_08062DFC();
    if ((*(s16 *)((u8 *)(gMainContextPointer_03006F74) + 0x3A)) == 0) {
        gFrameObjects[0x21].flags = 0xC000;
        gFrameObjects[0x21].tableSelector = 2;
        gFrameObjects[0x21].screenX = 0x28;
        gFrameObjects[0x21].screenY = 0x40;
        gFrameObjects[0x21].palette = 8;
        gFrameObjects[0x21].frameAndGroup = 0x2A;
        sub_0803FAA0(1U, 0U, 1U);
        gUnknown_0300137C += 1;
    }
}

void sub_08064610(void) {
    if (sub_08065710(gMainContextPointer_03006F74 + 0x50) != 0) {
        gMainSubstate = 0x14;
        gUnknown_0300137C = 0;
    }
}

void sub_08065198(void) {
    if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
        sub_0803F684(0U, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0xFFFFU);
        sub_0803F998(0U, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0xFFFFU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    (*(s8 *)((u8 *)(gMainContextPointer_03006F74) + 0x4C)) = 0;
    sub_0803FAA0(1U, 0U, 0U);
    (*(s8 *)((u8 *)(gMainContextPointer_03006F74) + 6)) = 0;
    gUnknown_0300137C += 1;
}

void sub_080654C0(void) {
    if (sub_08041CA4() != 0) {
        if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
            sub_0803F684(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
            sub_0803F998(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
            gState0TypedWork.bytes[0x84] += 1;
            return;
        }
        *(u16 *)0x04000000 &= 0xFDFF;
        gMainSubstate = 6;
        gUnknown_0300137C = 0;
    }
}

void sub_0806552C(void) {
    if (sub_08041CA4() != 0) {
        if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
            sub_0803F684(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
            sub_0803F998(0U, gState0TypedWork.bytes[0x84] * 4, 0xFFFFU);
            gState0TypedWork.bytes[0x84] += 1;
            return;
        }
        *(u16 *)0x04000000 &= 0xFDFF;
        sub_08040CD0(0U, 0x80U);
        sub_080476E8(2U);
    }
}

void sub_08065A80(void) {
    if (sub_08041CA4() != 0) {
        sub_080476E8(8U);
    }
}

void sub_08065C98(void) {
    u32 var_r0;

    if ((u32) gUnknown_03000B90 > 1U) {
        sub_0803FB0C();
        (*(s32 *)((u8 *)(gMainContextPointer_03006F74) + 8)) = 1;
        goto block_5;
    }
    if (gMainSerialOutgoingWork.polledBits & (1 << gUnknown_03000B90)) {
        var_r0 = gUnknown_0300137C + 1;
    } else {
        sub_0803FB0C();
        (*(s32 *)((u8 *)(gMainContextPointer_03006F74) + 8)) = 1;
block_5:
        var_r0 = gUnknown_0300137C - 2;
    }
    gUnknown_0300137C = var_r0;
}

void sub_08065CFC(void) {
    if (sub_08041CA4() != 0) {
        sub_080476E8(7U);
    }
}

void sub_08066240(void) {
    if (sub_08065710(gMainContextPointer_03006F74 + 0x50) != 0) {
        gUnknown_0300137C += 1;
        sub_0803FAA0(1U, 0U, 1U);
        gFrameObjects->flags |= 0x4000;
    }
}

void sub_08066534(void) {
    if ((sub_08065710(gMainContextPointer_03006F74 + 0x50) != 0) && (sub_08074FA4(4U) == 0)) {
        sub_08074B88(0U);
        sub_08074DE0(0U);
        Unknown_0805DEB0();
        gUnknown_0300137C += 2;
    }
}

void sub_0806668C(void) {
    if (sub_08041674() != 0) {
        if (gState0TypedWork.bytes[0x2A] == 0) {
            gUnknown_0300137C += 1;
            sub_0803FB0C();
            return;
        }
        gUnknown_0300137C += 3;
    }
}

void sub_080666F4(void) {
    if (sub_08041674() != 0) {
        gUnknown_0300137C += 1;
        sub_0803FB0C();
    }
}

void sub_08068238(void) {
    sub_08067C04();
    if ((u32) gState0TypedWork.bytes[0x84] <= 8U) {
        sub_0803F684(0U, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0xFFFFU);
        sub_0803F998(0U, 0x20 - (gState0TypedWork.bytes[0x84] * 4), 0xFFFFU);
        gState0TypedWork.bytes[0x84] += 1;
        return;
    }
    sub_0803FAA0(1U, 2U, 0U);
    gUnknown_0300137C += 1;
}

void sub_080683C8(void) {
    if (sub_08065710(gMainContextPointer_03006F74 + 0x50) != 0) {
        gMainState = 0;
        gMainSubstate = 6;
        gUnknown_0300137C = 0x50;
    }
}

void sub_08068E00(void) {
    sub_08069320();
    sub_08074B88(0U);
    gUnknown_03006FDC = gFreshWork_03006D38;
    sub_0806A024();
    sub_08069A08();
    sub_08069910();
    sub_08069490();
    sub_08074B88(0x13U);
    sub_08068460(4, 1, 0);
    *(u16 *)0x04000000 |= 0x1E00;
    gUnknown_03006F88 = 0;
    (*(s8 *)((u8 *)(&gUnknown_03006F94) + 0)) = 0;
    (*(s8 *)((u8 *)(&gUnknown_03006F94) + 1)) = 0;
    (*(s8 *)((u8 *)(&gUnknown_03006F94) + 2)) = 0;
    (*(s8 *)((u8 *)(&gUnknown_03006F8C) + 0)) = 0;
    (*(s8 *)((u8 *)(&gUnknown_03006F8C) + 1)) = 0;
    (*(s8 *)((u8 *)(&gUnknown_03006F8C) + 2)) = 0;
    gUnknown_03006F80 = 3;
    gUnknown_0300137C = 1;
}

void sub_08068F08(void) {
    if (sub_0806A08C() != 0) {
        gUnknown_03006F88 = 0;
        gUnknown_03006F80 = 4;
        gUnknown_0300137C = 2;
    }
}

void sub_08068F34(void) {
    (*(s16 *)((u8 *)((void *)0x04000050) + 0)) = 0xFF;
    (*(s16 *)((u8 *)((void *)0x04000050) + 4)) = 0xF;
    sub_080441B8();
}

void sub_08069168(void) {
    if (sub_0806A114() != 0) {
        gUnknown_03006F88 = 0;
        gUnknown_03006F80 = 7;
        gUnknown_0300137C = 2;
    }
}

void sub_08069194(void) {
    sub_08069530();
    sub_08069CC0();
    sub_080696A8();
    sub_08074B88(0U);
    sub_08068460(4, 1, 0);
    sub_08074B88(0x17U);
    *(u16 *)0x04000000 |= 0x1E00;
    gUnknown_03006F80 = 8;
    gUnknown_0300137C = 1;
}

void sub_080691E0(void) {
    sub_0806B0D4();
    sub_0806B4C8();
    if (sub_0806A654() != 0) {
        gUnknown_03006F88 = 0;
        gUnknown_0300137C = 9;
    }
}

void sub_0806920C(void) {
    sub_0806A860();
    sub_0806AA10();
    sub_0806AAA4();
    sub_0806ADB0();
    sub_0806B01C();
    sub_0806A748();
    sub_0806B0D4();
    sub_0806B4C8();
    if (sub_0806A718() != 0) {
        gUnknown_03006F88 = 0;
        gUnknown_03006F80 = 0xA;
        gUnknown_0300137C = 2;
    }
}

void sub_08069258(void) {
    sub_08069320();
    sub_08069A08();
    sub_0806938C();
    sub_08069910();
    sub_08074B88(0U);
    sub_08068460(2, 2, 0);
    sub_08074B88(0x13U);
    *(u16 *)0x04000000 |= 0x1A00;
    gUnknown_03006F80 = 0xB;
    gUnknown_0300137C = 1;
}

void sub_080692A8(void) {
    if (sub_0806A3C4() != 0) {
        *(s16 *)0x04000054 = 0;
        *(s16 *)0x04000050 = 0xFF;
        gUnknown_03006F88 = 0;
        sub_080750F0(0x20U);
        gUnknown_03006F80 = 0xC;
        gUnknown_0300137C = 2;
    }
}

void sub_08069DF0(void) {
    sub_08048864(0U, 0xC004U, 0x33U, 0U, 1U);
    gFrameObjects->screenX = -0x10;
}

void sub_0806BB24(void) {
    if (sub_08068888() != 0) {
        sub_08074B88(0x14U);
        gUnknown_0300137C += 1;
    }
}

void sub_0806BB44(void) {
    if (sub_0806BD70() != 0) {
        gUnknown_0300137C += 1;
    }
    sub_0806CB28();
}

void sub_0806BC48(void) {
    if (gFrameObjects[0x1E].commandOffset == 0) {
        sub_0806BFEC();
        sub_0806C218();
        sub_0806BF18();
    } else {
        sub_0806C694();
    }
    sub_0806C084();
    sub_0806C3A0();
    sub_0806C660();
    sub_0806D398();
    sub_0806CF7C();
    sub_0806CD68();
    sub_0806CEDC();
    sub_0806CC80();
}

void sub_0806BD3C(void) {
    (*(s16 *)((u8 *)((void *)0x04000050) + 0)) = 0xFF;
    (*(s16 *)((u8 *)((void *)0x04000050) + 4)) = 0x10;
    *(u16 *)0x04000000 &= 0x80FF;
    sub_08074B88(0U);
    sub_08047850(1);
}

void sub_0806E150(void) {
    if (sub_08068888() != 0) {
        gMainState = (u32) (*(u16 *)((u8 *)(&gState0TransferWork) + 0));
        gMainSubstate = (u32) (*(u16 *)((u8 *)(&gState0TransferWork) + 2));
        gUnknown_0300137C = (u32) (*(u16 *)((u8 *)(&gState0TransferWork) + 4));
    }
}

void sub_0806E3F8(void) {
    sub_08047850(2);
}

void sub_0806EAC0(void) {
    if (sub_0806F9D8() != 0) {
        gMainState = (u32) (*(u16 *)((u8 *)(&gState0TransferWork) + 0));
        gMainSubstate = (u32) (*(u16 *)((u8 *)(&gState0TransferWork) + 2));
        gUnknown_0300137C = (u32) (*(u16 *)((u8 *)(&gState0TransferWork) + 4));
    }
}

void sub_0806EAF4(void) {
    if (sub_0806FB5C() != 0) {
        gMainState = (u32) (*(u16 *)((u8 *)(&gState0TransferWork) + 0));
        gMainSubstate = (u32) (*(u16 *)((u8 *)(&gState0TransferWork) + 2));
        gUnknown_0300137C = (u32) (*(u16 *)((u8 *)(&gState0TransferWork) + 4));
    }
}

void sub_08071030(void) {
    sub_08074B88(4U);
    sub_08071DB8(1, 0, 0);
    sub_08071DB8(2, 0xB, 0);
    gUnknown_0300137C += 1;
}

void sub_0807105C(void) {
    if (gFrameObjects[0xA].commandStopped == 0) {
        sub_08071898(0x16, 0x2D, 8);
        sub_08071898(0x17, 0x36, 8);
        sub_08071DB8(5, 0x16, 0x48);
        sub_08071DB8(6, 0x17, 0x48);
        gUnknown_0300137C += 1;
    }
}

void sub_080710AC(void) {
    if (gFrameObjects[0x16].commandDelay == 0) {
        sub_080718D4(0x16, 0x27);
        sub_080718D4(0x17, 0x33);
        sub_08071898(0x18, 0x45, 8);
        sub_08071DB8(7, 0x18, 0x60);
        gUnknown_0300137C += 1;
    }
}

void sub_080710F4(void) {
    if (gFrameObjects[0x18].commandDelay == 0) {
        sub_08071898(0x18, 0x3F, 0xC);
        sub_08071898(0x19, 0x4E, 8);
        sub_08071DB8(6, 0x19, 0x60);
        gUnknown_0300137C += 1;
    }
}

void sub_08071138(void) {
    if (gFrameObjects[0x19].commandDelay == 0) {
        sub_080718D4(0x19, 0x4B);
        gUnknown_0300137C += 1;
    }
}

s32 sub_08071E8C(void) {
    if ((s32) gFrameObjects[3].screenY <= 0x35) {
        gFrameObjects[3].screenY = (u16) gFrameObjects[3].screenY + 2;
        goto block_9;
    }
    if ((s32) gFrameObjects[3].screenY <= 0x39) {
        gFrameObjects[3].screenY = (u16) gFrameObjects[3].screenY + 1;
        goto block_9;
    }
    if ((u32) gFrameObjects[3].unknown1A <= 0x1FU) {
        gFrameObjects[3].unknown1A += 1;
        goto block_9;
    }
    if ((s32) gFrameObjects[3].screenX > 0x37) {
        sub_0806B718(7);
        sub_08074DE0(0x54U);
        gFrameObjects[3].unknown1A = 0;
        gState0TransferWork.bytes[0x10] += 1;
        return 1;
    }
    gFrameObjects[3].screenX = (u16) gFrameObjects[3].screenX + 4;
block_9:
    return 0;
}

s32 sub_08071EFC(void) {
    if ((s32) gFrameObjects[4].screenY <= 0x35) {
        gFrameObjects[4].screenY = (u16) gFrameObjects[4].screenY + 2;
        goto block_9;
    }
    if ((s32) gFrameObjects[4].screenY <= 0x39) {
        gFrameObjects[4].screenY = (u16) gFrameObjects[4].screenY + 1;
        goto block_9;
    }
    if ((u32) gFrameObjects[4].unknown1A <= 0x1FU) {
        gFrameObjects[4].unknown1A += 1;
        goto block_9;
    }
    if ((s32) gFrameObjects[4].screenX <= 0x44) {
        sub_0806B718(8);
        sub_08074DE0(0x54U);
        gFrameObjects[4].unknown1A = 0;
        gState0TransferWork.bytes[0x10] += 1;
        return 1;
    }
    gFrameObjects[4].screenX = (u16) gFrameObjects[4].screenX - 4;
block_9:
    return 0;
}

s32 sub_08071F74(void) {
    if ((s32) gFrameObjects[5].screenY <= 0x3D) {
        gFrameObjects[5].screenY = (u16) gFrameObjects[5].screenY + 2;
        goto block_9;
    }
    if ((s32) gFrameObjects[5].screenY <= 0x41) {
        gFrameObjects[5].screenY = (u16) gFrameObjects[5].screenY + 1;
        goto block_9;
    }
    if ((u32) gFrameObjects[5].unknown1A <= 0x1FU) {
        gFrameObjects[5].unknown1A += 1;
        goto block_9;
    }
    if ((s32) gFrameObjects[5].screenX <= 0x40) {
        sub_0806B718(9);
        sub_08074DE0(0x54U);
        gFrameObjects[5].priority = 0x21;
        gFrameObjects[5].unknown1A = 0;
        gState0TransferWork.bytes[0x10] += 1;
        return 1;
    }
    gFrameObjects[5].screenX = (u16) gFrameObjects[5].screenX - 4;
block_9:
    return 0;
}

void sub_080723AC(void *arg0) {
    s32 sp0;

    gUnknown_03007014 = arg0;
    sp0 = 0;
    CpuSet(&sp0, arg0, 0x050001CDU);
    sub_08074A04();
    (*(s8 *)((u8 *)(gUnknown_03007014) + 0x6CA)) = 1;
    (*(s8 *)((u8 *)(gUnknown_03007014) + 0x712)) = 2;
    sub_08073A88();
}

void sub_08072C10(void *arg0) {
    (*(s32 *)((u8 *)(arg0) + 0x14)) = sub_08072880();
}

void sub_08072C20(void *arg0) {
    s32 temp_r0;

    temp_r0 = sub_08072880();
    (*(s32 *)((u8 *)(arg0) + 0x20)) = (s32) (*(s32 *)((u8 *)(arg0) + 0x14));
    (*(s32 *)((u8 *)(arg0) + 0x14)) = temp_r0;
}

void sub_08073044(s32 arg0) {
    sub_080727D0();
    sub_08072818(arg0);
}

void sub_08073058(void *arg0) {
    s32 temp_r0;

    if ((*(s32 *)((u8 *)(arg0) + 0x14)) != 0) {
        (*(s8 *)((u8 *)(arg0) + 0x6E)) = 0;
        temp_r0 = (*(s32 *)((u8 *)(arg0) + 0x28));
        if (temp_r0 != 0) {
            (*(s32 *)((u8 *)(arg0) + 0x28)) = (s32) (temp_r0 - 1);
        }
loop_3:
        if ((*(s32 *)((u8 *)(arg0) + 0x28)) == 0) {
            sub_08072D68(arg0);
            if ((*(s32 *)((u8 *)(arg0) + 0x14)) != 0) {
                goto loop_3;
            }
        }
        (*(s32 (**)(void *))((u8 *)(arg0) + 0x10))(arg0);
    }
}

void sub_080736A0(void *arg0) {
    if (((*(s32 *)((u8 *)(arg0) + 8)) != 0) && ((*(u8 *)((u8 *)(arg0) + 0x6B)) != 0) && ((*(u8 *)((u8 *)(arg0) + 0x66)) == 0) && !(0x10 & (*(u8 *)((u8 *)(arg0) + 0x50)))) {
        sub_08073524(arg0, 0x04000062, 0x04000064);
        return;
    }
    sub_080732C8(arg0, 0x04000060);
    sub_080732F0(arg0, 0x04000062, 0x04000065);
    sub_08073404(arg0, 0x04000064);
    sub_08073604(arg0);
}

void sub_08073718(void *arg0) {
    if (((*(s32 *)((u8 *)(arg0) + 8)) != 0) && ((*(u8 *)((u8 *)(arg0) + 0x6B)) != 0) && ((*(u8 *)((u8 *)(arg0) + 0x66)) == 0) && !(0x10 & (*(u8 *)((u8 *)(arg0) + 0x50)))) {
        sub_08073524(arg0, 0x04000068, 0x0400006C);
        return;
    }
    sub_080732F0(arg0, 0x04000068, 0x0400006D);
    sub_08073404(arg0, 0x0400006C);
    sub_08073604(arg0);
}

void sub_08073784(void *arg0) {
    if (((*(s32 *)((u8 *)(arg0) + 8)) != 0) && ((*(u8 *)((u8 *)(arg0) + 0x6B)) != 0) && ((*(u8 *)((u8 *)(arg0) + 0x66)) == 0) && !(0x10 & (*(u8 *)((u8 *)(arg0) + 0x50)))) {
        sub_08073524(arg0, 0x04000072, 0x04000074);
        return;
    }
    sub_0807334C(arg0, 0x04000072);
    sub_08073480(arg0, (volatile u16 *)0x04000074);
    sub_08073604(arg0);
}

void sub_08073DF4(s32 arg0) {
    sub_08073C84();
    sub_08073DB8(arg0, 0, 0, 0, 0, 0, 0, 0);
}

void sub_08073F6C(void *arg0) {
    s32 temp_r1;

    temp_r1 = (*(s32 *)((u8 *)(arg0) + 0xC));
    if (1 & temp_r1) {
        (*(s32 *)((u8 *)(arg0) + 0xC)) = (s32) (temp_r1 & ~1);
        sub_08073D70(arg0, (*(s32 *)((u8 *)(arg0) + 8)) - 0x20);
    }
}

void sub_08074728(void) {
    if ((*(s32 *)((u8 *)(gUnknown_03007014) + 0x340)) == 0) {
        sub_080737E8(gUnknown_03007014 + 0x15C);
    }
}

void sub_08074834(void) {
    if ((*(s32 *)((u8 *)(gUnknown_03007014) + 0x49C)) == 0) {
        sub_08073E1C(gUnknown_03007014 + 0x690);
    }
}

void sub_0807485C(void) {
    if ((*(s32 *)((u8 *)(gUnknown_03007014) + 0x510)) == 0) {
        sub_08073E1C(gUnknown_03007014 + 0x6D8);
    }
    sub_0807495C(gUnknown_03007014 + 0x570);
}

void sub_08074890(void) {
    sub_08073E1C(gUnknown_03007014 + 0x690);
    (*(s8 *)((u8 *)(gUnknown_03007014) + 0x4D8)) = 0;
}

void sub_080748B8(void) {
    sub_08073E1C(gUnknown_03007014 + 0x6D8);
    (*(s8 *)((u8 *)(gUnknown_03007014) + 0x54C)) = 0;
    sub_0807462C(0xC);
}

void sub_080748E8(void) {
    if ((*(s32 *)((u8 *)(gUnknown_03007014) + 0x340)) == 0) {
        sub_080737E8(gUnknown_03007014 + 0x570);
    }
}
