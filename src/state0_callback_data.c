#include "state0_callback_data.h"

extern void DummyInterruptHandler(void);
extern void sub_080102C0(void);
extern void sub_0801030C(void);
extern void sub_08010328(void);
extern void sub_08010358(void);
extern void sub_08010374(void);
extern void sub_080103A4(void);
extern void sub_080103F4(void);
extern void sub_08010478(void);
extern void sub_0801053C(void);
extern void sub_0801058C(void);
extern void sub_08010794(void);
extern void sub_080107F0(void);
extern void sub_08010814(void);
extern void sub_08010860(void);
extern void sub_080108D0(void);
extern void sub_080108FC(void);
extern void sub_08010930(void);
extern void sub_08010968(void);
extern void sub_080109A0(void);
extern void sub_080109CC(void);
extern void sub_08010A20(void);
extern void sub_08010A7C(void);
extern void sub_08010AC8(void);
extern void sub_08010B24(void);
extern void sub_08010B54(void);
extern void sub_08010BA0(void);
extern void sub_08010BD0(void);
extern void sub_08010C28(void);
extern void sub_08010C50(void);
extern void sub_08010CE8(void);
extern void sub_08010D58(void);
extern void sub_08010DAC(void);
extern void sub_08010E50(void);
extern void sub_08010E7C(void);
extern void sub_08010F08(void);
extern void sub_08010F6C(void);
extern void sub_08010FA4(void);
extern void sub_08010FDC(void);
extern void sub_08011018(void);
extern void sub_08011048(void);
extern void sub_08011078(void);
extern void sub_080110FC(void);
extern void sub_0801112C(void);
extern void sub_08011158(void);
extern void sub_0801120C(void);
extern void sub_0801123C(void);
extern void sub_08011268(void);
extern void sub_080112C4(void);
extern void sub_080112F0(void);
extern void sub_08011344(void);
extern void sub_08011490(void);
extern void sub_080114E0(void);
extern void sub_08011500(void);
extern void sub_080115B4(void);
extern void sub_080115E8(void);
extern void sub_08011644(void);
extern void sub_080116C4(void);
extern void sub_08011764(void);
extern void sub_08011A58(void);
extern void sub_08011ABC(void);
extern void sub_08011ADC(void);
extern void sub_08011B18(void);
extern void sub_08011B5C(void);
extern void sub_08011BB8(void);
extern void sub_08011C88(void);
extern void sub_08011CFC(void);
extern void sub_08011D50(void);
extern void sub_08011D80(void);
extern void sub_080129C8(void);
extern void sub_08012A20(void);
extern void sub_08012B40(void);
extern void sub_08012B94(void);
extern void sub_08012BC0(void);
extern void sub_08012BE4(void);
extern void sub_08012C0C(void);
extern void sub_08012C64(void);
extern void sub_08012D98(void);
extern void sub_08012DF4(void);
extern void sub_08012E40(void);
extern void sub_08012EA8(void);
extern void sub_08012F00(void);
extern void sub_08012FF8(void);
extern void sub_0801303C(void);
extern void sub_080130D8(void);
extern void sub_08013164(void);
extern void sub_08013228(void);
extern void sub_08013288(void);
extern void sub_08013330(void);
extern void sub_080133B8(void);
extern void sub_08013438(void);
extern void sub_08013508(void);
extern void sub_08013568(void);
extern void sub_08013614(void);
extern void sub_08013650(void);
extern void sub_080136B0(void);
extern void sub_080136E8(void);
extern void sub_0801372C(void);
extern void sub_08013798(void);
extern void sub_08013824(void);
extern void sub_0801387C(void);
extern void sub_08013A74(void);
extern void sub_08013AE4(void);
extern void sub_08013B8C(void);
extern void sub_08013DE4(void);
extern void sub_08013E30(void);
extern void sub_08013FA8(void);
extern void sub_08014050(void);
extern void sub_080140B0(void);
extern void sub_0801425C(void);
extern void sub_0801427C(void);
extern void sub_08014314(void);
extern void sub_080143A0(void);
extern void sub_08014404(void);
extern void sub_08014548(void);
extern void sub_080145BC(void);
extern void sub_08014634(void);
extern void sub_080146DC(void);
extern void sub_08014754(void);
extern void sub_080147FC(void);
extern void sub_08014870(void);
extern void sub_08014920(void);
extern void sub_08014994(void);
extern void sub_08014A44(void);
extern void sub_08014A60(void);
extern void sub_08014A84(void);
extern void sub_08014AB4(void);
extern void sub_08014ADC(void);
extern void sub_08014B34(void);
extern void sub_08014C30(void);
extern void sub_08014C84(void);
extern void sub_08014CC8(void);
extern void sub_08014CE4(void);
extern void sub_08014CF0(void);
extern void sub_08014D84(void);
extern void sub_08014D94(void);
extern void sub_08014DC8(void);
extern void sub_08014E08(void);
extern void sub_08014E20(void);
extern void sub_08014E54(void);
extern void sub_0801C524(void);
extern void sub_0801C660(void);
extern void sub_0801C6C4(void);
extern void sub_0801C774(void);
extern void sub_0801C988(void);
extern void sub_0801C9C8(void);
extern void sub_0801CA2C(void);
extern void sub_0801CA60(void);
extern void sub_0801CAA8(void);
extern void sub_0801CB24(void);
extern void sub_0801CB74(void);
extern void sub_0801CBA4(void);
extern void sub_0801CBE4(void);
extern void sub_0801CC24(void);
extern void sub_0801CC58(void);
extern void sub_0801CCB8(void);
extern void sub_0801CD08(void);
extern void sub_0801CD28(void);
extern void sub_0801CD40(void);
extern void sub_0801CD50(void);
extern void sub_0801CDB4(void);
extern void sub_0801CDD4(void);
extern void sub_0801CE94(void);
extern void sub_0801CF78(void);
extern void sub_0801CFFC(void);
extern void sub_0801D06C(void);
extern void sub_0801D174(void);
extern void sub_0801D1AC(void);
extern void sub_0801D244(void);
extern void sub_0801D264(void);
extern void sub_0801D2AC(void);
extern void sub_0801D2C4(void);
extern void sub_0801D2D8(void);
extern void sub_0801D318(void);
extern void sub_0801D36C(void);
extern void sub_0801D3A8(void);
extern void sub_0801D3F8(void);
extern void sub_0801D434(void);
extern void sub_0801D45C(void);
extern void sub_0801D524(void);
extern void sub_0801D544(void);
extern void sub_0801D5A8(void);
extern void sub_0801D6A4(void);
extern void sub_0801D738(void);
extern void sub_0801D878(void);
extern void sub_0801D95C(void);
extern void sub_0801D9DC(void);
extern void sub_0801DAEC(void);
extern void sub_0801DC74(void);
extern void sub_0801DD30(void);
extern void sub_0801DD74(void);
extern void sub_0801DDDC(void);
extern void sub_0801DE44(void);
extern void sub_0801DED4(void);
extern void sub_0801DF0C(void);
extern void sub_0801DF60(void);
extern void sub_0801DFE0(void);
extern void sub_0801E09C(void);
extern void sub_0801E200(void);
extern void sub_0801E248(void);
extern void sub_0801E2B8(void);
extern void sub_0801E300(void);
extern void sub_0801E3C0(void);
extern void sub_0801E43C(void);
extern void sub_0801E474(void);
extern void sub_0801E54C(void);
extern void sub_0801E578(void);
extern void sub_0801E5DC(void);
extern void sub_0801E830(void);
extern void sub_0801E864(void);
extern void sub_0801E8DC(void);
extern void sub_0801E918(void);
extern void sub_0801E9B0(void);
extern void sub_0801E9E0(void);
extern void sub_0801E9FC(void);
extern void sub_0801EA5C(void);
extern void sub_0801EA94(void);
extern void sub_0801EAC4(void);
extern void sub_0801EAD4(void);
extern void sub_0801EB5C(void);
extern void sub_0801EBB8(void);
extern void sub_0801EBD4(void);
extern void sub_0801EBF8(void);
extern void sub_0801EC3C(void);
extern void sub_0801ECC0(void);
extern void sub_0801ED50(void);
extern void sub_0801EED4(void);
extern void sub_0801EEE4(void);
extern void sub_0801EFC8(void);
extern void sub_0801F018(void);
extern void sub_0801F0F0(void);
extern void sub_0801F1C8(void);
extern void sub_0801F214(void);
extern void sub_0801F290(void);
extern void sub_0801F2DC(void);
extern void sub_0801F374(void);
extern void sub_0801F390(void);
extern void sub_0801F3F0(void);
extern void sub_0801F474(void);
extern void sub_0801F4AC(void);
extern void sub_0801F5AC(void);
extern void sub_0801F5BC(void);
extern void sub_0801F780(void);
extern void sub_0801F800(void);
extern void sub_0801F9B0(void);
extern void sub_0801F9EC(void);
extern void sub_0801FA68(void);
extern void sub_0801FADC(void);
extern void sub_0801FBC4(void);
extern void sub_0801FD88(void);
extern void sub_0801FE14(void);
extern void sub_0801FE64(void);
extern void sub_0801FEC8(void);
extern void sub_0801FEE8(void);
extern void sub_0801FF9C(void);
extern void sub_08020004(void);
extern void sub_08020040(void);
extern void sub_08020078(void);
extern void sub_080200A8(void);
extern void sub_080201DC(void);
extern void sub_08020248(void);
extern void sub_08020288(void);
extern void sub_080202E0(void);
extern void sub_08020340(void);
extern void sub_0802036C(void);
extern void sub_08020428(void);
extern void sub_08020474(void);
extern void sub_08020530(void);
extern void sub_080205A4(void);
extern void sub_08020608(void);
extern void sub_08020628(void);
extern void sub_080206E8(void);
extern void sub_08020728(void);
extern void sub_08020768(void);
extern void sub_080207CC(void);
extern void sub_08020844(void);
extern void sub_080208E8(void);
extern void sub_08020928(void);
extern void sub_080209A0(void);
extern void sub_080209D8(void);
extern void sub_08020A90(void);
extern void sub_08020AD0(void);
extern void sub_08020B4C(void);
extern void sub_08020CEC(void);
extern void sub_08020D24(void);
extern void sub_08020DF8(void);
extern void sub_08020EDC(void);
extern void sub_08020FB8(void);
extern void sub_08021000(void);
extern void sub_08021038(void);
extern void sub_080211C8(void);
extern void sub_0802121C(void);
extern void sub_080212A0(void);
extern void sub_08021300(void);
extern void sub_08021370(void);
extern void sub_080213E4(void);
extern void sub_08021418(void);
extern void sub_08021564(void);
extern void sub_080215C8(void);
extern void sub_08021608(void);
extern void sub_08021638(void);
extern void sub_0802167C(void);
extern void sub_08021734(void);
extern void sub_08021774(void);
extern void sub_080217D8(void);
extern void sub_0802186C(void);
extern void sub_080218E4(void);
extern void sub_08021950(void);
extern void sub_080219C0(void);
extern void sub_08021A14(void);
extern void sub_08021A6C(void);
extern void sub_08021AFC(void);
extern void sub_08021B78(void);
extern void sub_08021BD8(void);
extern void sub_08021C94(void);
extern void sub_08021DAC(void);
extern void sub_08021DEC(void);
extern void sub_08021E2C(void);
extern void sub_08021EA0(void);
extern void sub_08021F90(void);
extern void sub_08022010(void);
extern void sub_080220A0(void);
extern void sub_0802213C(void);
extern void sub_0802217C(void);
extern void sub_080221C8(void);
extern void sub_080222A8(void);
extern void sub_08022380(void);
extern void sub_080223E4(void);
extern void sub_08022480(void);
extern void sub_08022648(void);
extern void sub_08022708(void);
extern void sub_08022748(void);
extern void sub_080227C0(void);
extern void sub_08022800(void);
extern void sub_08022870(void);
extern void sub_08022938(void);
extern void sub_08022990(void);
extern void sub_080229C0(void);
extern void sub_08022A04(void);
extern void sub_08022B40(void);
extern void sub_08022C28(void);
extern void sub_08022C90(void);
extern void sub_08022CD0(void);
extern void sub_08022D4C(void);
extern void sub_08022E14(void);
extern void sub_08022F50(void);
extern void sub_08022FB4(void);
extern void sub_08023018(void);
extern void sub_0802306C(void);
extern void sub_080230A4(void);
extern void sub_080230C8(void);
extern void sub_08023118(void);
extern void sub_080231D4(void);
extern void sub_08023224(void);
extern void sub_08023274(void);
extern void sub_08023328(void);
extern void sub_08023384(void);
extern void sub_080233E0(void);
extern void sub_08023414(void);
extern void sub_08023454(void);
extern void sub_080234A8(void);
extern void sub_08023564(void);
extern void sub_080235AC(void);
extern void sub_080235E8(void);
extern void sub_08023658(void);
extern void sub_080236E0(void);
extern void sub_08023718(void);
extern void sub_08023758(void);
extern void sub_080237C8(void);
extern void sub_080238A0(void);
extern void sub_08023900(void);
extern void sub_08023988(void);
extern void sub_080239C0(void);
extern void sub_08023A04(void);
extern void sub_08023A48(void);
extern void sub_08023AB0(void);
extern void sub_08023AF0(void);
extern void sub_08023B44(void);
extern void sub_08023C18(void);
extern void sub_08023C50(void);
extern void sub_08023C78(void);
extern void sub_08023CB8(void);
extern void sub_08023D44(void);
extern void sub_08023E18(void);
extern void sub_08023E50(void);
extern void sub_08023E94(void);
extern void sub_08023F48(void);
extern void sub_08023F80(void);
extern void sub_08023FB8(void);
extern void sub_08024078(void);
extern void sub_080240B8(void);
extern void sub_0802410C(void);
extern void sub_080241F0(void);
extern void sub_08024210(void);
extern void sub_080242F8(void);
extern void sub_08024488(void);
extern void sub_08024538(void);
extern void sub_0802463C(void);
extern void sub_080246C0(void);
extern void sub_0802473C(void);
extern void sub_08024790(void);
extern void sub_080247C8(void);
extern void sub_080247F4(void);
extern void sub_0802480C(void);
extern void sub_08024870(void);
extern void sub_08024890(void);
extern void sub_0802494C(void);
extern void sub_080249C0(void);
extern void sub_08024A30(void);
extern void sub_08024AF4(void);
extern void sub_08024BCC(void);
extern void sub_08024BF8(void);
extern void sub_08024C44(void);
extern void sub_08024C94(void);
extern void sub_08024D18(void);
extern void sub_08024DA8(void);
extern void sub_08024E2C(void);
extern void sub_08024E9C(void);
extern void sub_08024F90(void);
extern void sub_08024FC4(void);
extern void sub_0802503C(void);
extern void sub_08025104(void);
extern void sub_08025174(void);
extern void sub_080251B4(void);
extern void sub_08025230(void);
extern void sub_08025308(void);
extern void sub_08025354(void);
extern void sub_08025378(void);
extern void sub_0802549C(void);
extern void sub_08025500(void);
extern void sub_08025570(void);
extern void sub_080255F8(void);
extern void sub_08025674(void);
extern void sub_080256EC(void);
extern void sub_08025790(void);
extern void sub_080257E8(void);
extern void sub_08025858(void);
extern void sub_08025974(void);
extern void sub_08025A18(void);
extern void sub_08025AAC(void);
extern void sub_08025B20(void);
extern void sub_08025B9C(void);
extern void sub_08025C84(void);
extern void sub_08025D2C(void);
extern void sub_08025D4C(void);
extern void sub_08025D6C(void);
extern void sub_08025DD4(void);
extern void sub_08025E88(void);
extern void sub_08025F14(void);
extern void sub_08025F54(void);
extern void sub_08025FC8(void);
extern void sub_08026080(void);
extern void sub_080260EC(void);
extern void sub_08026130(void);
extern void sub_08026184(void);
extern void sub_08026284(void);
extern void sub_080262FC(void);
extern void sub_08026340(void);
extern void sub_08026378(void);
extern void sub_080263BC(void);
extern void sub_08026444(void);
extern void sub_08026484(void);
extern void sub_080264E4(void);
extern void sub_08026628(void);
extern void sub_08026678(void);
extern void sub_08026810(void);
extern void sub_080268AC(void);
extern void sub_080268D4(void);
extern void sub_08026924(void);
extern void sub_08026A24(void);
extern void sub_08026A74(void);
extern void sub_08026AF4(void);
extern void sub_08026BF8(void);
extern void sub_08026CBC(void);
extern void sub_08026D1C(void);
extern void sub_08026D44(void);
extern void sub_08026D98(void);
extern void sub_08026EC0(void);
extern void sub_08026EF8(void);
extern void sub_08026F34(void);
extern void sub_08026F6C(void);
extern void sub_08026FC0(void);
extern void sub_08026FF8(void);
extern void sub_080270BC(void);
extern void sub_080271C4(void);
extern void sub_0802724C(void);
extern void sub_080272EC(void);
extern void sub_0802733C(void);
extern void sub_08027378(void);
extern void sub_080273DC(void);
extern void sub_08027444(void);
extern void sub_0802747C(void);
extern void sub_08027494(void);
extern void sub_08027544(void);
extern void sub_0802761C(void);
extern void sub_080276E8(void);
extern void sub_08027798(void);
extern void sub_080277DC(void);
extern void sub_080278B8(void);
extern void sub_08027964(void);
extern void sub_080279E4(void);
extern void sub_08027BA0(void);
extern void sub_08027BEC(void);
extern void sub_08027CB0(void);
extern void sub_08027D24(void);
extern void sub_08027D98(void);
extern void sub_08027E1C(void);
extern void sub_08027EDC(void);
extern void sub_08027F84(void);
extern void sub_08028034(void);
extern void sub_08028078(void);
extern void sub_080280D4(void);
extern void sub_08028130(void);
extern void sub_08028230(void);
extern void sub_08028270(void);
extern void sub_080282E0(void);
extern void sub_08028350(void);
extern void sub_080283C0(void);
extern void sub_080283EC(void);
extern void sub_0802842C(void);
extern void sub_08028504(void);
extern void sub_080287C0(void);
extern void sub_080287DC(void);
extern void sub_08028A00(void);
extern void sub_08028A38(void);
extern void sub_08028B58(void);
extern void sub_08028BA8(void);
extern void sub_08028C68(void);
extern void sub_08028CC8(void);
extern void sub_08028E84(void);
extern void sub_08028F4C(void);
extern void sub_08029004(void);
extern void sub_08029178(void);
extern void sub_080291E0(void);
extern void sub_080292D4(void);
extern void sub_08029354(void);
extern void sub_08029464(void);
extern void sub_080294DC(void);
extern void sub_08029600(void);
extern void sub_08029680(void);
extern void sub_0802976C(void);
extern void sub_080297EC(void);
extern void sub_08029828(void);
extern void sub_08029868(void);
extern void sub_08029984(void);
extern void sub_08029A14(void);
extern void sub_08029B04(void);
extern void sub_08029B84(void);
extern void sub_08029C64(void);
extern void sub_08029D28(void);
extern void sub_08029DF4(void);
extern void sub_08029E34(void);
extern void sub_08029F50(void);
extern void sub_08029FE0(void);
extern void sub_0802A0D0(void);
extern void sub_0802A110(void);
extern void sub_0802A274(void);
extern void sub_0802A2D4(void);
extern void sub_0802A31C(void);
extern void sub_0802A360(void);
extern void sub_0802A440(void);
extern void sub_0802A4C4(void);
extern void sub_0802A534(void);
extern void sub_0802A5C0(void);
extern void sub_0802A694(void);
extern void sub_0802A6D4(void);
extern void sub_0802A7E0(void);
extern void sub_0802A824(void);
extern void sub_0802A9B8(void);
extern void sub_0802AAB8(void);
extern void sub_0802AAF8(void);
extern void sub_0802AC7C(void);
extern void sub_0802ACB4(void);
extern void sub_0802ACF4(void);
extern void sub_0802AE88(void);
extern void sub_0802AECC(void);
extern void sub_0802AF6C(void);
extern void sub_0802AFB0(void);
extern void sub_0802AFE8(void);
extern void sub_0802B028(void);
extern void sub_0802B184(void);
extern void sub_0802B258(void);
extern void sub_0802B388(void);
extern void sub_0802B3CC(void);
extern void sub_0802B460(void);
extern void sub_0802B4D8(void);
extern void sub_0802B5AC(void);
extern void sub_0802B7AC(void);
extern void sub_0802B810(void);
extern void sub_0802B8BC(void);
extern void sub_0802B980(void);
extern void sub_0802BA2C(void);
extern void sub_0802BAAC(void);
extern void sub_0802BB24(void);
extern void sub_0802BBA8(void);
extern void sub_0802BC1C(void);
extern void sub_0802BC60(void);
extern void sub_0802BD1C(void);
extern void sub_0802BD94(void);
extern void sub_0802BE44(void);
extern void sub_0802BEEC(void);
extern void sub_0802BF9C(void);
extern void sub_0802C0DC(void);
extern void sub_0802C1A4(void);
extern void sub_0802C24C(void);
extern void sub_0802C294(void);
extern void sub_0802C2D4(void);
extern void sub_0802C440(void);
extern void sub_0802C4F8(void);
extern void sub_0802C588(void);
extern void sub_0802C62C(void);
extern void sub_0802C66C(void);
extern void sub_0802C714(void);
extern void sub_0802C758(void);
extern void sub_0802C790(void);
extern void sub_0802C820(void);
extern void sub_0802C864(void);
extern void sub_0802C960(void);
extern void sub_0802CA5C(void);
extern void sub_0802CAD4(void);
extern void sub_0802CB34(void);
extern void sub_0802CBD0(void);
extern void sub_0802CC10(void);
extern void sub_0802CC74(void);
extern void sub_0802CD48(void);
extern void sub_0802CE08(void);
extern void sub_0802CE4C(void);
extern void sub_0802CFAC(void);
extern void sub_0802D198(void);
extern void sub_0802D270(void);
extern void sub_0802D3D4(void);
extern void sub_0802D4D8(void);
extern void sub_0802D5BC(void);
extern void sub_0802D670(void);
extern void sub_0802D6B0(void);
extern void sub_0802D758(void);
extern void sub_0802D7EC(void);
extern void sub_0802D8D0(void);
extern void sub_0802DA0C(void);
extern void sub_0802DA60(void);
extern void sub_0802DAD0(void);
extern void sub_0802DB3C(void);
extern void sub_0802DBD8(void);
extern void sub_0802DC9C(void);
extern void sub_0802DCDC(void);
extern void sub_0802DD98(void);
extern void sub_0802DE1C(void);
extern void sub_0802DF18(void);
extern void sub_0802DF48(void);
extern void sub_0802DF98(void);
extern void sub_0802DFE8(void);
extern void sub_0802E010(void);
extern void sub_0802E098(void);
extern void sub_0802E140(void);
extern void sub_0802E1A4(void);
extern void sub_0802E1C8(void);
extern void sub_0802E294(void);
extern void sub_0802E358(void);
extern void sub_0802E44C(void);
extern void sub_0802E4C8(void);
extern void sub_0802E5D4(void);
extern void sub_0802E638(void);
extern void sub_0802E70C(void);
extern void sub_0802E7A0(void);
extern void sub_0802E820(void);
extern void sub_0802E8D4(void);
extern void sub_0802E948(void);
extern void sub_0802EAA4(void);
extern void sub_0802EAC0(void);
extern void sub_0802EAD8(void);
extern void sub_0802EBE8(void);
extern void sub_0802EC4C(void);
extern void sub_0802ED34(void);
extern void sub_0802ED90(void);
extern void sub_0802EE14(void);
extern void sub_0802EF0C(void);
extern void sub_0802EF5C(void);
extern void sub_0802EFD0(void);
extern void sub_0802F018(void);
extern void sub_0802F058(void);
extern void sub_0802F13C(void);
extern void sub_0802F214(void);
extern void sub_0802F2F4(void);
extern void sub_0802F3FC(void);
extern void sub_0802F468(void);
extern void sub_0802F48C(void);
extern void sub_0802F4D0(void);
extern void sub_0802F594(void);
extern void sub_0802F5D8(void);
extern void sub_0802F610(void);
extern void sub_0802F650(void);
extern void sub_0802F6CC(void);
extern void sub_0802F7B8(void);
extern void sub_0802F864(void);
extern void sub_0802F880(void);
extern void sub_0802F89C(void);
extern void sub_0802F8E4(void);
extern void sub_0802F9B8(void);
extern void sub_0802FB74(void);
extern void sub_0802FBF4(void);
extern void sub_0802FC3C(void);
extern void sub_0802FD08(void);
extern void sub_0802FD4C(void);
extern void sub_0802FD84(void);
extern void sub_0802FDC8(void);
extern void sub_0802FE0C(void);
extern void sub_0802FE38(void);
extern void sub_0802FE78(void);
extern void sub_08030180(void);
extern void sub_08030238(void);
extern void sub_0803029C(void);
extern void sub_08030354(void);
extern void sub_080303A4(void);
extern void sub_08030494(void);
extern void sub_0803059C(void);
extern void sub_080305C8(void);
extern void sub_080305E0(void);
extern void sub_08030608(void);
extern void sub_08030624(void);
extern void sub_08030674(void);
extern void sub_080306B8(void);
extern void sub_08030780(void);
extern void sub_0803080C(void);
extern void sub_0803081C(void);

const State0StoredCallback gState0MapCallbacks_083ACE24[144] = {
    sub_080102C0,
    sub_0801030C,
    sub_08010328,
    sub_08010358,
    sub_08010374,
    sub_080103A4,
    sub_080103F4,
    sub_08010478,
    sub_0801053C,
    sub_0801058C,
    sub_08010794,
    sub_080107F0,
    sub_08010814,
    sub_08010860,
    sub_080108D0,
    sub_080108FC,
    sub_08010930,
    sub_08010968,
    sub_080109A0,
    sub_080109CC,
    sub_08010A20,
    sub_08010A7C,
    sub_08010AC8,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_080109A0,
    sub_080109CC,
    sub_08010A20,
    sub_08010B24,
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
    sub_0801058C,
    sub_08010B54,
    sub_08010794,
    sub_080107F0,
    sub_08010BA0,
    sub_08010BD0,
    sub_08010C28,
    sub_08010C50,
    sub_08010CE8,
    sub_08010D58,
    sub_08010DAC,
    sub_08010E50,
    sub_08010E7C,
    sub_08010F08,
    sub_08010F6C,
    sub_08010FA4,
    sub_08010FDC,
    sub_08011018,
    sub_08011048,
    sub_08011078,
    sub_080110FC,
    sub_0801112C,
    DummyInterruptHandler,
    sub_08011158,
    sub_0801120C,
    sub_0801123C,
    DummyInterruptHandler,
    sub_08011268,
    sub_080112C4,
    sub_080112F0,
    sub_08011344,
    DummyInterruptHandler,
    sub_08011490,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_080114E0,
    sub_080112C4,
    sub_080112F0,
    sub_08011500,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_080115B4,
    sub_080115E8,
    sub_08011644,
    sub_080116C4,
    DummyInterruptHandler,
    sub_08011764,
    sub_08011A58,
    sub_08011ABC,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08011ADC,
    sub_08011B18,
    sub_080114E0,
    sub_080112C4,
    sub_08011B5C,
    sub_08011BB8,
    DummyInterruptHandler,
    sub_08011C88,
    sub_08010CE8,
    sub_08011CFC,
    sub_08011D50,
    sub_08011D80,
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
};

const State0StoredCallback gState0MapPhaseCallbacks_083AD080[192] = {
    sub_080129C8,
    sub_08012A20,
    sub_08012B40,
    sub_08012B94,
    sub_08012BC0,
    sub_08012BE4,
    sub_08012C0C,
    sub_08012C64,
    sub_08012D98,
    sub_08012DF4,
    DummyInterruptHandler,
    sub_08012E40,
    sub_08012EA8,
    sub_08012F00,
    sub_08012FF8,
    DummyInterruptHandler,
    sub_0801303C,
    sub_080130D8,
    sub_08013164,
    sub_08013228,
    DummyInterruptHandler,
    sub_08013288,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08013330,
    sub_080133B8,
    sub_08013438,
    sub_08013508,
    DummyInterruptHandler,
    sub_08013568,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_080136E8,
    sub_0801372C,
    sub_08013798,
    sub_08013B8C,
    sub_08013DE4,
    sub_08013E30,
    sub_08013FA8,
    DummyInterruptHandler,
    sub_08013614,
    sub_08013650,
    sub_080136B0,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_080136E8,
    sub_0801372C,
    sub_08013798,
    sub_08013824,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08013AE4,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0801387C,
    sub_08013A74,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08014050,
    sub_080140B0,
    sub_0801425C,
    DummyInterruptHandler,
    sub_0801427C,
    sub_08014314,
    sub_080143A0,
    sub_08014404,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08014548,
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
    sub_080145BC,
    sub_08014634,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_080146DC,
    sub_08014754,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_080147FC,
    sub_08014870,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08014920,
    sub_08014994,
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
    sub_08014A44,
    sub_08014A60,
    sub_08014A84,
    sub_08014AB4,
    sub_08014ADC,
    sub_08014B34,
    sub_08014C30,
    sub_08014C84,
    sub_08014CC8,
    sub_08014CE4,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08014A44,
    sub_08014A60,
    sub_08014A84,
    sub_08014AB4,
    sub_08014ADC,
    sub_08014CF0,
    sub_08014AB4,
    sub_08014A84,
    sub_08014AB4,
    sub_08014D84,
    sub_08014D94,
    sub_08014DC8,
    sub_08014CC8,
    sub_08014E20,
    sub_08014E54,
    sub_08014E08,
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
};

const State0StoredCallback gActionDispatchCallbacks_083AD5CC[48] = {
    sub_0801C524,
    sub_080305E0,
    sub_0801C660,
    sub_0801C6C4,
    sub_0801C774,
    sub_0801C988,
    sub_0801C9C8,
    sub_0801CA2C,
    sub_0801CA60,
    sub_0801CAA8,
    sub_0801CB24,
    sub_080305E0,
    sub_0801CB74,
    sub_0801CBA4,
    sub_080305E0,
    sub_0801CBE4,
    sub_0801CC24,
    sub_0801CC58,
    sub_0801CCB8,
    sub_0801CA2C,
    sub_0801CD08,
    sub_0801CD28,
    sub_080305E0,
    sub_0801CD40,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0801CD50,
    sub_0801CDB4,
    sub_0801CDD4,
    sub_0801CE94,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0801CF78,
    sub_0801CFFC,
    sub_0801D06C,
    sub_0801C988,
    sub_0801D174,
    sub_0801D1AC,
    sub_0801D264,
    sub_080305E0,
    sub_0801D244,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0801D2AC,
    sub_0801D2C4,
    sub_0801D2D8,
};

const State0StoredCallback gActionDispatchCallbacks_083AD68C[9] = {
    sub_0801D318,
    sub_08030608,
    sub_080305E0,
    sub_0801D36C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AD6B0[8] = {
    sub_0801D3A8,
    sub_08030608,
    sub_080305E0,
    sub_0801D3F8,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AD6D0[8] = {
    sub_0801D434,
    sub_0801D45C,
    sub_0801D524,
    sub_0801D544,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AD6F0[16] = {
    sub_0801D5A8,
    sub_0801D6A4,
    sub_0801D738,
    sub_0801D878,
    sub_0801D95C,
    sub_0801D9DC,
    sub_0801DAEC,
    sub_0801DC74,
    sub_0801DD30,
    sub_0801DD74,
    sub_080305E0,
    sub_0801DDDC,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AD730[8] = {
    sub_0801DE44,
    sub_080305E0,
    sub_0801DED4,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AD750[16] = {
    sub_0801DF0C,
    sub_0801DF60,
    sub_0801DFE0,
    sub_0801E09C,
    sub_0801E200,
    sub_0801E248,
    sub_0801E2B8,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AD790[80] = {
    sub_0801E300,
    sub_0801E3C0,
    sub_0801E43C,
    sub_0801E474,
    sub_0801E54C,
    sub_08030624,
    sub_0801E578,
    sub_0801E5DC,
    sub_0801E830,
    sub_08030624,
    sub_0801E864,
    sub_0801E8DC,
    sub_08030624,
    sub_0801E918,
    sub_0801E9B0,
    sub_080306B8,
    sub_0801E9E0,
    sub_0801E9FC,
    sub_08030624,
    sub_0801EA5C,
    sub_0801EA94,
    sub_0801EAC4,
    sub_0801EAD4,
    sub_0801EB5C,
    sub_0801EBB8,
    sub_08030624,
    sub_0801EBF8,
    sub_0801EA94,
    sub_0801EAC4,
    sub_0801EC3C,
    sub_0801EA94,
    sub_0801EAC4,
    sub_0801ECC0,
    sub_0801ED50,
    sub_0801E830,
    sub_08030624,
    sub_0801EED4,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0801EEE4,
    sub_0801EFC8,
    sub_08030624,
    sub_0801EA94,
    sub_0801EAC4,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0801F018,
    sub_0801E54C,
    sub_08030624,
    sub_0801EA94,
    sub_0801EAC4,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0801F0F0,
    sub_0801E54C,
    sub_08030624,
    sub_0801F1C8,
    sub_0801EA94,
    sub_0801EAC4,
    sub_0801F214,
    sub_0801F290,
    sub_08030624,
    sub_0801F2DC,
    sub_0801E9B0,
    sub_080306B8,
    sub_0801F374,
    sub_0801F390,
    sub_08030624,
    sub_0801F3F0,
    sub_0801EA94,
    sub_0801EAC4,
    sub_0801ED50,
    sub_0801E830,
    sub_08030624,
    sub_0801F474,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AD8D0[17] = {
    sub_0801F4AC,
    sub_0801F5AC,
    sub_0801F5BC,
    sub_0801F780,
    sub_0801F800,
    sub_0801F9B0,
    sub_080306B8,
    sub_0801F9EC,
    sub_0801F5AC,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AD914[16] = {
    sub_0801FA68,
    sub_0801FADC,
    sub_0801FBC4,
    sub_0801FD88,
    sub_0803080C,
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
};

const State0StoredCallback gActionDispatchCallbacks_083AD954[16] = {
    sub_0801FE14,
    sub_0803080C,
    sub_0801FE64,
    sub_0801FEC8,
    sub_0801FEE8,
    sub_0801FF9C,
    sub_08020004,
    sub_080305E0,
    sub_08020040,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AD994[25] = {
    sub_08020078,
    sub_0803080C,
    sub_080200A8,
    sub_080201DC,
    sub_08020248,
    sub_0803080C,
    sub_08020288,
    sub_080202E0,
    sub_08030624,
    sub_08020340,
    sub_0803080C,
    sub_0802036C,
    sub_08020428,
    sub_08030624,
    sub_0803080C,
    sub_08020474,
    sub_08020530,
    sub_08030624,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AD9F8[8] = {
    sub_080205A4,
    sub_08020608,
    sub_08020628,
    sub_080206E8,
    sub_08020728,
    sub_08020768,
    sub_080305E0,
    sub_0803080C,
};

const State0StoredCallback gActionDispatchCallbacks_083ADA18[8] = {
    sub_080207CC,
    sub_0803080C,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083ADA38[8] = {
    sub_08020844,
    sub_0803080C,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083ADA58[25] = {
    sub_0801E300,
    sub_080208E8,
    sub_0801F214,
    sub_0801F290,
    sub_08030624,
    sub_0801F2DC,
    sub_0801E9B0,
    sub_080306B8,
    sub_0801F374,
    sub_0801F390,
    sub_08030624,
    sub_08020928,
    sub_0801EA94,
    sub_0803080C,
    sub_0801ED50,
    sub_0801E830,
    sub_08030624,
    sub_080209A0,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083ADABC[8] = {
    sub_080209D8,
    sub_0803080C,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083ADADC[25] = {
    sub_0801E300,
    sub_08020A90,
    sub_0801F214,
    sub_0801F290,
    sub_08030624,
    sub_0801F2DC,
    sub_0801E9B0,
    sub_080306B8,
    sub_08020B4C,
    sub_0801F374,
    sub_0801F390,
    sub_08030624,
    sub_08020AD0,
    sub_0801EA94,
    sub_0803080C,
    sub_0801ED50,
    sub_0801E830,
    sub_08030624,
    sub_08020CEC,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083ADB40[43] = {
    sub_08020D24,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_08021038,
    sub_080211C8,
    sub_0802121C,
    sub_080212A0,
    sub_08021300,
    sub_08021370,
    sub_080213E4,
    sub_08021418,
    sub_08021564,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    sub_080215C8,
    sub_08021608,
    sub_08021418,
    sub_08021564,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08021638,
    sub_0802167C,
    sub_08021734,
    sub_08021774,
    sub_080217D8,
    sub_0802186C,
    sub_08021418,
    sub_08021564,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083ADBEC[32] = {
    sub_080218E4,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_08021950,
    sub_080219C0,
    sub_08021A14,
    sub_08021A6C,
    sub_08021AFC,
    sub_08021B78,
    sub_08030674,
    sub_08021BD8,
    sub_08021C94,
    sub_08021DAC,
    sub_08021DEC,
    sub_080305E0,
    sub_0803080C,
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
};

const State0StoredCallback gActionDispatchCallbacks_083ADC6C[16] = {
    sub_08021E2C,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_08021EA0,
    sub_08030674,
    sub_08021F90,
    sub_08022010,
    sub_080220A0,
    sub_0802213C,
    sub_080305E0,
    sub_0803080C,
};

const State0StoredCallback gActionDispatchCallbacks_083ADCAC[16] = {
    sub_0802217C,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_080221C8,
    sub_080222A8,
    sub_08022380,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083ADCEC[16] = {
    sub_080223E4,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08022480,
    sub_08022648,
    sub_08022708,
    sub_08022748,
    sub_080227C0,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083ADD2C[24] = {
    sub_08022800,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_08022870,
    sub_08022938,
    sub_08022990,
    sub_080229C0,
    sub_08022A04,
    sub_08022B40,
    sub_08022C28,
    sub_08022C90,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083ADD8C[24] = {
    sub_08022CD0,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_08022D4C,
    sub_08022938,
    sub_08022990,
    sub_080229C0,
    sub_08022E14,
    sub_08022B40,
    sub_08022F50,
    sub_08022FB4,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083ADDEC[21] = {
    sub_08023018,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_0802306C,
    sub_080230A4,
    sub_080230C8,
    sub_08023118,
    sub_080231D4,
    sub_08023224,
    sub_08023274,
    sub_08023328,
    sub_08030674,
    sub_08023384,
    sub_080233E0,
    sub_08023414,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083ADE40[24] = {
    sub_08023454,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_080234A8,
    sub_08023564,
    sub_08030674,
    sub_080235AC,
    sub_080235E8,
    sub_08023658,
    sub_080236E0,
    sub_08023718,
    sub_080305E0,
    sub_0803080C,
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
};

const State0StoredCallback gActionDispatchCallbacks_083ADEA0[24] = {
    sub_08023758,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_080237C8,
    sub_080238A0,
    sub_08023900,
    sub_08023988,
    sub_080239C0,
    sub_08023A04,
    sub_08023A48,
    sub_08023AB0,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083ADF00[24] = {
    sub_08023AF0,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_08023B44,
    sub_080238A0,
    sub_08023900,
    sub_08023C18,
    sub_080239C0,
    sub_08023A04,
    sub_08023C50,
    sub_08023C78,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083ADF60[32] = {
    sub_08023CB8,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_08023D44,
    sub_080238A0,
    sub_08023900,
    sub_08023E18,
    sub_080239C0,
    sub_08023E50,
    sub_08023E94,
    sub_08023F48,
    sub_080238A0,
    sub_08023900,
    sub_08023F80,
    sub_080239C0,
    sub_08023A04,
    sub_08023FB8,
    sub_08024078,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083ADFE0[32] = {
    sub_080240B8,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_0802410C,
    sub_08030674,
    sub_080241F0,
    sub_08024210,
    sub_080242F8,
    sub_08024488,
    sub_08024538,
    sub_0802463C,
    sub_080246C0,
    sub_0802473C,
    sub_0803080C,
    sub_08024790,
    sub_0803080C,
    sub_080247C8,
    sub_080247F4,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    sub_0802480C,
    sub_08024870,
    sub_08024890,
    sub_0802494C,
    sub_0803080C,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE064[24] = {
    sub_080249C0,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_08024A30,
    sub_08030674,
    sub_08021F90,
    sub_08024AF4,
    sub_08024BCC,
    sub_08030674,
    sub_08024BF8,
    sub_08024C44,
    sub_08024C94,
    sub_08024D18,
    sub_08024DA8,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE0C4[24] = {
    sub_08024E2C,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_08024E9C,
    sub_08030780,
    sub_08021F90,
    sub_08024F90,
    sub_08024FC4,
    sub_0802503C,
    sub_0803081C,
    sub_08025104,
    sub_08025174,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE124[24] = {
    sub_080251B4,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_08025230,
    sub_08025308,
    sub_08025354,
    sub_08025378,
    sub_0802549C,
    sub_08025500,
    sub_08025570,
    sub_080255F8,
    sub_08025674,
    sub_080256EC,
    sub_08025790,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE184[24] = {
    sub_080257E8,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_08025858,
    sub_08030674,
    sub_08021F90,
    sub_08025974,
    sub_08024BCC,
    sub_08030674,
    sub_08024BF8,
    sub_08024C44,
    sub_08024C94,
    sub_08025A18,
    sub_08025AAC,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE1E4[32] = {
    sub_08025B20,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_08025B9C,
    sub_08030674,
    sub_08021F90,
    sub_08025C84,
    sub_08025D2C,
    sub_08025D4C,
    sub_08025D6C,
    sub_08025DD4,
    sub_08021F90,
    sub_08025D2C,
    sub_08025D4C,
    sub_08025E88,
    sub_08025F14,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE264[7] = {
    sub_08025F54,
    sub_0803080C,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE280[6] = {
    sub_08025FC8,
    sub_08026080,
    sub_08030674,
    sub_080260EC,
    sub_0803080C,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE298[21] = {
    sub_08026130,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_08026184,
    sub_08026284,
    sub_080262FC,
    sub_08026340,
    sub_08026378,
    sub_08030674,
    sub_080263BC,
    sub_08026444,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE2EC[21] = {
    sub_08026484,
    sub_08030608,
    sub_080305E0,
    sub_0803080C,
    sub_080264E4,
    sub_08026628,
    sub_08026678,
    sub_08026810,
    sub_080305E0,
    sub_0803080C,
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
};

const State0StoredCallback gActionDispatchCallbacks_083AE340[32] = {
    sub_0801E300,
    sub_080268AC,
    sub_080268D4,
    sub_08026924,
    sub_08026A24,
    sub_080306B8,
    sub_0801E9E0,
    sub_08026A74,
    sub_08030624,
    sub_08026AF4,
    sub_0801EA94,
    sub_0801EAC4,
    DummyInterruptHandler,
    sub_08026BF8,
    sub_0801EBD4,
    sub_08030624,
    sub_08026CBC,
    sub_0801EA94,
    sub_0801EAC4,
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
};

const State0StoredCallback gActionDispatchCallbacks_083AE3C0[48] = {
    sub_0801E300,
    sub_08026D1C,
    sub_0801E864,
    sub_0801E8DC,
    sub_08030624,
    sub_0801E918,
    sub_0801E9B0,
    sub_080306B8,
    sub_0801E9E0,
    sub_0801E9FC,
    sub_08030624,
    sub_0801EA5C,
    sub_0801EA94,
    sub_0801EAC4,
    sub_0801EAD4,
    sub_0801EB5C,
    sub_0801EBD4,
    sub_08030624,
    sub_0801EBF8,
    sub_0801EA94,
    sub_0801EAC4,
    sub_08026D44,
    sub_0801EA94,
    sub_0801EAC4,
    sub_08026D98,
    sub_0801E830,
    sub_08030624,
    sub_08026EC0,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0801F018,
    sub_0801E54C,
    sub_08030624,
    sub_0801EA94,
    sub_0801EAC4,
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
};

const State0StoredCallback gActionDispatchCallbacks_083AE480[32] = {
    sub_08026EF8,
    sub_0803080C,
    sub_08026F34,
    sub_0801E300,
    sub_0801F214,
    sub_0801F290,
    sub_08030624,
    sub_0801F2DC,
    sub_0801E9B0,
    sub_080306B8,
    sub_0801F374,
    sub_0801F390,
    sub_08030624,
    sub_08026F6C,
    sub_0801EA94,
    sub_0803080C,
    sub_08026D98,
    sub_0801E830,
    sub_08030624,
    sub_08026FC0,
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
};

const State0StoredCallback gActionDispatchCallbacks_083AE500[32] = {
    sub_08026FF8,
    sub_080270BC,
    sub_080271C4,
    sub_08030674,
    sub_0802724C,
    sub_080272EC,
    sub_0802733C,
    sub_08027378,
    sub_080273DC,
    sub_08027444,
    sub_0802747C,
    sub_080305E0,
    sub_08027544,
    sub_0802761C,
    sub_08027494,
    sub_080276E8,
    sub_0803080C,
    DummyInterruptHandler,
    sub_08027798,
    sub_080277DC,
    sub_080278B8,
    sub_0803080C,
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
};

const State0StoredCallback gActionDispatchCallbacks_083AE580[16] = {
    sub_08027964,
    sub_080279E4,
    sub_08027BA0,
    sub_08027BEC,
    sub_08027CB0,
    sub_08027D24,
    sub_08027D98,
    sub_08027E1C,
    sub_08027EDC,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE5C0[16] = {
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_08027F84,
    sub_08028034,
    sub_080212A0,
    sub_08028078,
    sub_080280D4,
    sub_080215C8,
    sub_08021608,
    sub_08028130,
    sub_08028230,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE600[16] = {
    sub_08020DF8,
    sub_08020EDC,
    sub_08020FB8,
    sub_08021000,
    sub_08028270,
    sub_08030674,
    sub_080282E0,
    sub_08028350,
    sub_080283C0,
    sub_080283EC,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE640[16] = {
    sub_0802842C,
    sub_08028504,
    sub_080287C0,
    sub_080287DC,
    sub_08028A00,
    sub_0803080C,
    sub_08028A38,
    sub_08028B58,
    sub_08030674,
    sub_08028BA8,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE680[16] = {
    sub_08028C68,
    sub_08028CC8,
    sub_08028E84,
    sub_08028F4C,
    sub_08029004,
    sub_08029178,
    sub_08030674,
    sub_080291E0,
    sub_080292D4,
    sub_08029354,
    sub_08029464,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE6C0[16] = {
    sub_080294DC,
    sub_080287C0,
    sub_08029600,
    sub_0803080C,
    sub_08029680,
    sub_0802976C,
    sub_080297EC,
    sub_08029828,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE700[16] = {
    sub_08029868,
    sub_080287C0,
    sub_08029984,
    sub_0803080C,
    sub_08029A14,
    sub_08029B04,
    sub_08029B84,
    sub_08029C64,
    sub_08029D28,
    sub_08029DF4,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE740[16] = {
    sub_08029E34,
    sub_080287C0,
    sub_08029F50,
    sub_0803080C,
    sub_08029A14,
    sub_08029B04,
    sub_08029FE0,
    sub_08029C64,
    sub_08029D28,
    sub_0802A0D0,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE780[16] = {
    sub_0802A110,
    sub_0802A274,
    sub_08030674,
    sub_0802A2D4,
    sub_0802A31C,
    sub_0802A360,
    sub_0802A440,
    sub_0802A4C4,
    sub_0802A534,
    sub_0802A5C0,
    sub_08029D28,
    sub_0802A694,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE7C0[16] = {
    sub_0802A6D4,
    sub_0802A7E0,
    sub_08030674,
    sub_0802A824,
    sub_0802A9B8,
    sub_0802AAB8,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE800[16] = {
    sub_0802AAF8,
    sub_08022648,
    sub_08022708,
    sub_0802AC7C,
    sub_0802ACB4,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE840[16] = {
    sub_0802ACF4,
    sub_08022648,
    sub_0802AE88,
    sub_0802AECC,
    sub_0802AF6C,
    sub_0802AFB0,
    sub_0802AFE8,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE880[20] = {
    sub_080230A4,
    sub_080230C8,
    sub_0802B028,
    sub_080231D4,
    sub_08023224,
    sub_0802B184,
    sub_0803080C,
    sub_0802B258,
    sub_0802B388,
    sub_0802B3CC,
    sub_0802B460,
    sub_0802B4D8,
    sub_08028B58,
    sub_08030674,
    sub_0802B5AC,
    sub_0802B7AC,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE8D0[16] = {
    sub_0802B810,
    sub_0802B8BC,
    sub_0802B980,
    sub_0802BA2C,
    sub_0802BAAC,
    sub_0802BB24,
    sub_0802BBA8,
    sub_08030674,
    sub_0802BC1C,
    sub_0802A5C0,
    sub_08029D28,
    sub_0802BC60,
    sub_0802BD1C,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE910[16] = {
    sub_0802306C,
    sub_080230A4,
    sub_080230C8,
    sub_0802BD94,
    sub_0802BE44,
    sub_08023224,
    sub_0802BEEC,
    sub_0802BF9C,
    sub_0802C0DC,
    sub_08030674,
    sub_0802C1A4,
    sub_0802C24C,
    sub_0802C294,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE954[16] = {
    sub_0802BEEC,
    sub_0802C2D4,
    sub_0802C440,
    sub_0802C4F8,
    sub_0802C588,
    sub_0802C62C,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE994[16] = {
    sub_0802C66C,
    sub_0802C714,
    sub_08030674,
    sub_0802C758,
    sub_0802C790,
    sub_0802C820,
    sub_0803080C,
    sub_0802C864,
    sub_0802C960,
    sub_0802CA5C,
    sub_0802CAD4,
    sub_0802CB34,
    sub_0802CBD0,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AE9D4[23] = {
    sub_0802CC10,
    sub_0802CC74,
    sub_0802CD48,
    sub_08030674,
    sub_0802CE08,
    sub_0802CE4C,
    sub_0802CFAC,
    sub_0802D198,
    sub_0802D270,
    sub_0802D3D4,
    sub_0802D4D8,
    sub_0802D5BC,
    sub_0802D670,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    sub_080276E8,
    sub_0803080C,
    DummyInterruptHandler,
    sub_08027798,
    sub_080277DC,
    sub_080278B8,
    sub_0803080C,
};

const State0StoredCallback gActionDispatchCallbacks_083AEA30[22] = {
    sub_0802D6B0,
    sub_0802C714,
    sub_08030674,
    sub_0802C758,
    sub_0802D758,
    sub_0802C820,
    sub_0803080C,
    sub_0802D7EC,
    sub_0802D8D0,
    sub_0802DA0C,
    sub_08030674,
    sub_0802DA60,
    sub_0802DAD0,
    sub_0802DB3C,
    sub_0802DBD8,
    sub_0802DC9C,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AEA88[32] = {
    sub_0802DCDC,
    sub_080230A4,
    sub_080230C8,
    sub_0802DD98,
    sub_0802DE1C,
    sub_0802DF18,
    sub_0802DF48,
    sub_0802DF98,
    sub_0802DFE8,
    DummyInterruptHandler,
    sub_08023224,
    sub_0802E010,
    sub_0803080C,
    sub_0802E098,
    sub_0802E140,
    sub_08030674,
    sub_0802E1A4,
    sub_080305E0,
    sub_0802E1C8,
    sub_0802E294,
    sub_0802E358,
    sub_080276E8,
    sub_0803080C,
    DummyInterruptHandler,
    sub_08027798,
    sub_080277DC,
    sub_080278B8,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AEB1C[27] = {
    sub_0802E44C,
    sub_0802E4C8,
    sub_0802E5D4,
    sub_08030674,
    sub_0802E638,
    sub_0802E70C,
    sub_0802A5C0,
    sub_08029D28,
    sub_0802E7A0,
    sub_0802E820,
    sub_0802E8D4,
    sub_0802E948,
    sub_0802EAA4,
    sub_0802EAC0,
    sub_080305E0,
    sub_0802EAD8,
    sub_08027544,
    sub_0802761C,
    sub_080276E8,
    sub_0803080C,
    DummyInterruptHandler,
    sub_08027798,
    sub_080277DC,
    sub_080278B8,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AEB88[15] = {
    sub_0802EBE8,
    sub_0802EC4C,
    sub_0802ED34,
    sub_0802ED90,
    sub_0802EE14,
    sub_0802EF0C,
    sub_08030674,
    sub_0802EF5C,
    sub_0802EFD0,
    sub_0802F018,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AEBC4[16] = {
    sub_0802F058,
    sub_0802F13C,
    sub_0802F214,
    sub_0802F2F4,
    sub_0802F3FC,
    sub_0802F468,
    sub_0802F48C,
    sub_0802F4D0,
    sub_0802F594,
    sub_0802F5D8,
    sub_0802F610,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AEC04[21] = {
    sub_0802F650,
    sub_0802F6CC,
    sub_0802F7B8,
    sub_08030674,
    sub_0802F864,
    sub_0802F880,
    sub_0802F89C,
    sub_0803080C,
    sub_0802F8E4,
    sub_08027544,
    sub_0802761C,
    sub_080276E8,
    sub_0803080C,
    DummyInterruptHandler,
    sub_08027798,
    sub_080277DC,
    sub_080278B8,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AEC58[16] = {
    sub_0802F9B8,
    sub_0802FB74,
    sub_0802FBF4,
    sub_0802FC3C,
    sub_0802FD08,
    sub_0802FD4C,
    sub_0802FD84,
    sub_08030674,
    sub_0802FDC8,
    sub_0802FE0C,
    sub_0802FE38,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const State0StoredCallback gActionDispatchCallbacks_083AEC98[16] = {
    sub_0802FE78,
    sub_08030180,
    sub_08030238,
    sub_0803029C,
    sub_08030354,
    sub_080303A4,
    sub_08030494,
    sub_0803059C,
    sub_080305C8,
    sub_080305E0,
    sub_0803080C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};
