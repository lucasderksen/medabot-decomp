#include "global.h"

typedef void (*StateCallback)(void);
extern void DummyInterruptHandler(void);
extern void sub_08030890(void);
extern void sub_08030910(void);
extern void sub_08030990(void);
extern void sub_080309C8(void);
extern void sub_08030A24(void);
extern void sub_08030C94(void);
extern void sub_08030CA0(void);
extern void sub_08030CAC(void);
extern void sub_08030CFC(void);
extern void sub_08030D3C(void);
extern void sub_08030D58(void);
extern void sub_08030D74(void);
extern void sub_08030D90(void);
extern void sub_08030DB4(void);
extern void sub_08030E14(void);
extern void sub_08030E54(void);
extern void sub_08030E78(void);
extern void sub_08030F10(void);
extern void sub_08030FB4(void);
extern void sub_08030FEC(void);
extern void sub_08031048(void);
extern void sub_080310A0(void);
extern void sub_08031120(void);
extern void sub_08031174(void);
extern void sub_08031218(void);
extern void sub_08031298(void);
extern void sub_080312CC(void);
extern void sub_080312F0(void);
extern void sub_0803133C(void);
extern void sub_08031390(void);
extern void sub_08031438(void);
extern void sub_08031458(void);
extern void sub_08031518(void);
extern void sub_08031538(void);
extern void sub_080315B0(void);
extern void sub_08031608(void);
extern void sub_08031614(void);
extern void sub_08031704(void);
extern void sub_0803185C(void);
extern void sub_080318CC(void);
extern void sub_08031918(void);
extern void sub_08031978(void);
extern void sub_08031994(void);
extern void sub_080319B8(void);
extern void sub_080319E0(void);
extern void sub_08031A08(void);
extern void sub_08031A24(void);
extern void sub_08031AFC(void);
extern void sub_08031BCC(void);
extern void sub_08031D7C(void);
extern void sub_08031F2C(void);
extern void sub_08032100(void);
extern void sub_080322C8(void);
extern void sub_08032478(void);
extern void sub_08032640(void);
extern void sub_0803279C(void);
extern void sub_080328B8(void);
extern void sub_08032A68(void);
extern void sub_08032C08(void);
extern void sub_08032DA0(void);
extern void sub_080332EC(void);
extern void sub_08033364(void);
extern void sub_08033394(void);
extern void sub_080333D4(void);
extern void sub_080333E4(void);
extern void sub_08033434(void);
extern void sub_08033490(void);
extern void sub_080334E0(void);
extern void sub_08033550(void);
extern void sub_080335A0(void);
extern void sub_080335E0(void);
extern void sub_08033618(void);
extern void sub_08033658(void);
extern void sub_08033698(void);
extern void sub_080336DC(void);
extern void sub_08033754(void);
extern void sub_080337CC(void);
extern void sub_080338DC(void);
extern void sub_080338F4(void);
extern void sub_08033974(void);
extern void sub_080339F4(void);
extern void sub_08033A10(void);
extern void sub_08033A2C(void);
extern void sub_08033A78(void);
extern void sub_08033A94(void);
extern void sub_08033AB0(void);
extern void sub_08033ACC(void);
extern void sub_08033B7C(void);
extern void sub_08033C00(void);
extern void sub_08033C10(void);
extern void sub_08033C20(void);
extern void sub_08033CD0(void);
extern void sub_08033CE0(void);
extern void sub_08033CF0(void);
extern void sub_08033D00(void);
extern void sub_08033D10(void);
extern void sub_08033D30(void);
extern void sub_08033F04(void);
extern void sub_08033F64(void);
extern void sub_08033F9C(void);
extern void sub_08034008(void);
extern void sub_0803402C(void);
extern void sub_08034048(void);
extern void sub_08034074(void);
extern void sub_08034120(void);
extern void sub_08034170(void);
extern void sub_080341C0(void);
extern void sub_08034200(void);
extern void sub_08034240(void);
extern void sub_0803426C(void);
extern void sub_08034288(void);
extern void sub_080342C8(void);
extern void sub_080342E4(void);
extern void sub_08034300(void);
extern void sub_0803431C(void);
extern void sub_0803435C(void);
extern void sub_08034378(void);
extern void sub_080343B8(void);
extern void sub_080343D4(void);
extern void sub_080343F0(void);
extern void sub_0803440C(void);
extern void sub_08034428(void);
extern void sub_08034444(void);
extern void sub_08034460(void);
extern void sub_0803447C(void);
extern void sub_08034498(void);
extern void sub_080344B4(void);
extern void sub_080344D0(void);
extern void sub_080344EC(void);
extern void sub_08034508(void);
extern void sub_08034524(void);
extern void sub_08034540(void);
extern void sub_0803455C(void);
extern void sub_08034578(void);
extern void sub_08034594(void);
extern void sub_080345B0(void);
extern void sub_080345CC(void);
extern void sub_080345E8(void);
extern void sub_08034628(void);
extern void sub_08034644(void);
extern void sub_08034684(void);
extern void sub_080346C4(void);
extern void sub_08034708(void);
extern void sub_08034728(void);
extern void sub_0803476C(void);
extern void sub_080347AC(void);
extern void sub_080347BC(void);
extern void sub_080347F8(void);
extern void sub_080348D0(void);
extern void sub_08034910(void);
extern void sub_0803496C(void);
extern void sub_080349D8(void);
extern void sub_08034A68(void);
extern void sub_08034AA0(void);
extern void sub_08034AF4(void);
extern void sub_08034B68(void);
extern void sub_08034BA0(void);
extern void sub_08034BBC(void);
extern void sub_08034BD8(void);
extern void sub_08034BF4(void);
extern void sub_08034C10(void);
extern void sub_08034C2C(void);
extern void sub_08034C48(void);
extern void sub_08034C64(void);
extern void sub_08034C80(void);
extern void sub_08034C9C(void);
extern void sub_08034CB8(void);
extern void sub_08034CD4(void);
extern void sub_08034CF0(void);
extern void sub_08034D0C(void);
extern void sub_08034D28(void);
extern void sub_08034D44(void);
extern void sub_08034D60(void);
extern void sub_08034D7C(void);
extern void sub_08034D98(void);
extern void sub_08034DB4(void);
extern void sub_08034DD0(void);
extern void sub_08034DEC(void);
extern void sub_08034E08(void);
extern void sub_08034E24(void);
extern void sub_08034E40(void);
extern void sub_08034E5C(void);
extern void sub_08034E78(void);
extern void sub_08037BF4(void);
extern void sub_08037C50(void);
extern void sub_08037E2C(void);
extern void sub_08037FE4(void);
extern void sub_08038024(void);
extern void sub_0803805C(void);
extern void sub_0803809C(void);
extern void sub_080380B8(void);
extern void sub_080380F0(void);
extern void sub_08038178(void);
extern void sub_080381E0(void);
extern void sub_08038258(void);
extern void sub_080382F4(void);
extern void sub_08038428(void);
extern void sub_0803858C(void);
extern void sub_08038650(void);
extern void sub_08038700(void);
extern void sub_08038804(void);
extern void sub_080388A4(void);
extern void sub_08038AC0(void);
extern void sub_08039430(void);
extern void sub_08039448(void);
extern void sub_080394C4(void);
extern void sub_08039540(void);
extern void sub_08039568(void);
extern void sub_08039598(void);
extern void sub_080395C0(void);
extern void sub_080395E8(void);
extern void sub_080396C4(void);
extern void sub_080396D4(void);
extern void sub_080397B0(void);
extern void sub_0803981C(void);
extern void sub_080398AC(void);
extern void sub_080399EC(void);
extern void sub_08039A2C(void);
extern void sub_08039AC8(void);
extern void sub_08039BFC(void);
extern void sub_08039CB4(void);
extern void sub_08039CF8(void);
extern void sub_08039E00(void);
extern void sub_08039FE4(void);
extern void sub_0803A0B8(void);
extern void sub_0803A0E0(void);
extern void sub_0803A130(void);
extern void sub_0803A264(void);
extern void sub_0803A2E8(void);
extern void sub_0803A310(void);
extern void sub_0803A370(void);
extern void sub_0803A444(void);
extern void sub_0803A474(void);
extern void sub_0803A5CC(void);
extern void sub_0803A6FC(void);
extern void sub_0803A760(void);
extern void sub_0803A840(void);
extern void sub_0803A920(void);
extern void sub_0803A93C(void);
extern void sub_0803AA00(void);
extern void sub_0803AA90(void);
extern void sub_0803AB00(void);
extern void sub_0803AB9C(void);
extern void sub_0803AC4C(void);
extern void sub_0803ACB4(void);
extern void sub_0803ADE8(void);
extern void sub_0803ADFC(void);
extern void sub_0803AF2C(void);
extern void sub_0803B0C0(void);
extern void sub_0803B19C(void);
extern void sub_0803B1EC(void);
extern void sub_0803B328(void);
extern void sub_0803B374(void);
extern void sub_0803B3C8(void);
extern void sub_0803B428(void);
extern void sub_0803B4F8(void);
extern void sub_0803B5DC(void);
extern void sub_0803B6D8(void);
extern void sub_0803B700(void);
extern void sub_0803B754(void);
extern void sub_0803B884(void);

const StateCallback gLateStateCallbacks_083AECD8[112] = {
    sub_08030890,
    sub_08030910,
    sub_08030990,
    sub_080309C8,
    sub_08030A24,
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
    sub_08030CFC,
    sub_08030D3C,
    sub_08030D58,
    sub_08030C94,
    sub_08030D74,
    sub_08030D90,
    sub_08030DB4,
    sub_08030E14,
    sub_08030C94,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08030D3C,
    sub_08030E54,
    sub_08030C94,
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
    sub_08031614,
    sub_08030D3C,
    sub_08030E54,
    sub_08030C94,
    sub_08030D74,
    sub_08031704,
    sub_0803185C,
    sub_080318CC,
    sub_08030E54,
    sub_08031918,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08030E78,
    sub_08030F10,
    sub_08030FB4,
    sub_08030FEC,
    sub_080310A0,
    sub_08030CA0,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08031120,
    sub_08031174,
    sub_08030FB4,
    sub_08031048,
    sub_08031218,
    sub_08030CA0,
    DummyInterruptHandler,
    sub_08030CAC,
    sub_08031298,
    sub_080312CC,
    sub_080312F0,
    sub_0803133C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08031978,
    sub_08031994,
    sub_080319B8,
    sub_080319E0,
    sub_08031A08,
    sub_08031A24,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08031390,
    sub_08031438,
    sub_08031458,
    sub_08031518,
    sub_08031538,
    sub_080315B0,
    sub_08031608,
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

const StateCallback gLateStateCallbacks_083AEEA0[60] = {
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08031AFC,
    sub_08031AFC,
    sub_08031AFC,
    sub_08031AFC,
    sub_08031AFC,
    sub_08031AFC,
    sub_08031AFC,
    sub_08031AFC,
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
    sub_08031F2C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08032100,
    sub_080322C8,
    sub_08032478,
    sub_08032640,
    sub_08031BCC,
    sub_08031D7C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_080322C8,
    sub_0803279C,
    DummyInterruptHandler,
    sub_080328B8,
    sub_08031AFC,
    sub_08032DA0,
    sub_080328B8,
    sub_08032A68,
    sub_080328B8,
    sub_080328B8,
    DummyInterruptHandler,
    sub_08031AFC,
    sub_08032C08,
    DummyInterruptHandler,
    sub_08031AFC,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const StateCallback gLateStateCallbacks_083AEF90[60] = {
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
    sub_080332EC,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_080332EC,
    DummyInterruptHandler,
    sub_080332EC,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_080332EC,
    sub_080332EC,
    DummyInterruptHandler,
    sub_080332EC,
    sub_080332EC,
    DummyInterruptHandler,
    sub_080332EC,
    DummyInterruptHandler,
    sub_080332EC,
    sub_080332EC,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_080332EC,
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

const StateCallback gLateStateCallbacks_083AF090[60] = {
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
    sub_080336DC,
    sub_08033754,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08033364,
    sub_08033394,
    DummyInterruptHandler,
    sub_080333D4,
    sub_080333D4,
    sub_080333D4,
    sub_080333E4,
    sub_080333E4,
    sub_080333E4,
    sub_08033434,
    sub_08033490,
    sub_08033550,
    sub_080335A0,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08033490,
    sub_080335E0,
    sub_080333D4,
    sub_080334E0,
    DummyInterruptHandler,
    sub_080334E0,
    sub_080334E0,
    sub_08033618,
    sub_080334E0,
    sub_080334E0,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08033658,
    sub_080337CC,
    sub_08033698,
    sub_080333D4,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const StateCallback gLateStateCallbacks_083AF180[128] = {
    DummyInterruptHandler,
    sub_080338DC,
    sub_080338F4,
    sub_08033974,
    sub_080339F4,
    sub_08033A10,
    sub_08033A2C,
    sub_08033A78,
    sub_08033A94,
    sub_08033AB0,
    sub_08033ACC,
    sub_08033B7C,
    sub_08033C00,
    sub_08033C10,
    sub_08033C20,
    sub_08033CD0,
    sub_08033CE0,
    sub_08033CF0,
    sub_08033D00,
    sub_08033D10,
    sub_08033D30,
    sub_08033F04,
    sub_08033F64,
    sub_08033F9C,
    sub_08034008,
    sub_0803402C,
    sub_08034048,
    sub_08034074,
    sub_08034120,
    sub_08034170,
    sub_080341C0,
    sub_08034200,
    sub_08034240,
    sub_0803426C,
    sub_08034288,
    sub_080342C8,
    sub_080342E4,
    sub_08034300,
    sub_0803431C,
    sub_0803435C,
    sub_08034378,
    sub_080343B8,
    sub_080343D4,
    sub_080343F0,
    sub_0803440C,
    sub_08034428,
    sub_08034444,
    sub_08034460,
    sub_0803447C,
    sub_08034498,
    sub_080344B4,
    sub_080344D0,
    sub_080344EC,
    sub_08034508,
    sub_08034524,
    sub_08034540,
    sub_0803455C,
    sub_08034578,
    sub_08034594,
    sub_080345B0,
    sub_080345CC,
    sub_080345E8,
    sub_08034628,
    sub_08034644,
    sub_08034684,
    sub_080346C4,
    sub_08034708,
    sub_08034728,
    sub_0803476C,
    sub_080347AC,
    sub_080347BC,
    sub_080347F8,
    sub_080348D0,
    sub_08034910,
    sub_0803496C,
    sub_080349D8,
    sub_08034A68,
    sub_08034AA0,
    sub_08034AF4,
    sub_08034B68,
    sub_08034BA0,
    sub_08034BBC,
    sub_08034BD8,
    sub_08034BF4,
    sub_08034C10,
    sub_08034C2C,
    sub_08034C48,
    sub_08034C64,
    sub_08034C80,
    sub_08034C9C,
    sub_08034CB8,
    sub_08034CD4,
    sub_08034CF0,
    sub_08034D0C,
    sub_08034D28,
    sub_08034D44,
    sub_08034D60,
    sub_08034D7C,
    sub_08034D98,
    sub_08034DB4,
    sub_08034DD0,
    sub_08034DEC,
    sub_08034E08,
    sub_08034E24,
    sub_08034E40,
    sub_08034E5C,
    sub_08034E78,
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
};

const StateCallback gLateStateCallbacks_083AF6B0[64] = {
    DummyInterruptHandler,
    sub_08037BF4,
    sub_08037C50,
    sub_08037FE4,
    sub_0803809C,
    DummyInterruptHandler,
    sub_08037BF4,
    sub_08037E2C,
    sub_08037FE4,
    sub_0803809C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08038024,
    sub_0803805C,
    sub_0803809C,
    DummyInterruptHandler,
    sub_080380B8,
    sub_080380F0,
    sub_0803805C,
    sub_0803809C,
    sub_080380B8,
    sub_080380F0,
    sub_0803805C,
    sub_0803809C,
    sub_08038178,
    sub_0803805C,
    sub_0803809C,
    DummyInterruptHandler,
    sub_080381E0,
    sub_08038258,
    sub_0803805C,
    sub_0803809C,
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
    sub_080382F4,
    sub_0803805C,
    sub_0803809C,
    DummyInterruptHandler,
    sub_080380B8,
    sub_080380F0,
    sub_0803805C,
    sub_0803809C,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const StateCallback gLateStateCallbacks_083AF810[16] = {
    DummyInterruptHandler,
    sub_08038428,
    sub_0803858C,
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

const StateCallback gLateStateCallbacks_083AF860[16] = {
    DummyInterruptHandler,
    sub_08038650,
    sub_08038700,
    sub_08038804,
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

const StateCallback gLateStateCallbacks_083AF8A0[8] = {
    DummyInterruptHandler,
    sub_080388A4,
    sub_08038AC0,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
};

const StateCallback gLateStateCallbacks_083AF8C0[80] = {
    DummyInterruptHandler,
    sub_08039430,
    sub_08039448,
    sub_080394C4,
    sub_08039540,
    sub_08039568,
    sub_08039598,
    sub_080395C0,
    sub_080395E8,
    sub_080396C4,
    sub_080396D4,
    sub_080397B0,
    sub_0803981C,
    sub_080398AC,
    sub_080399EC,
    sub_08039A2C,
    sub_08039AC8,
    sub_08039BFC,
    sub_08039CB4,
    sub_08039CF8,
    sub_08039E00,
    sub_08039FE4,
    sub_0803A0B8,
    sub_0803A0E0,
    sub_0803A130,
    sub_0803A264,
    sub_0803A2E8,
    sub_0803A310,
    sub_0803A370,
    sub_0803A444,
    sub_0803A474,
    sub_0803A5CC,
    sub_0803A6FC,
    sub_0803A760,
    sub_0803A840,
    sub_0803A920,
    sub_0803A93C,
    sub_0803AA00,
    sub_0803AA90,
    sub_0803AB00,
    sub_0803AB9C,
    sub_0803ACB4,
    sub_0803AC4C,
    sub_0803ADE8,
    sub_0803ADFC,
    sub_0803AF2C,
    sub_0803B0C0,
    sub_0803B19C,
    sub_0803B1EC,
    sub_0803B328,
    sub_0803B374,
    sub_0803B3C8,
    sub_0803B428,
    sub_0803B4F8,
    sub_0803B5DC,
    sub_0803B6D8,
    sub_0803B700,
    sub_0803B754,
    sub_0803B884,
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
};
