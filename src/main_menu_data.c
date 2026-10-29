#include "main_menu_data.h"

extern void DummyInterruptHandler(void);
extern void sub_0805E478(void);
extern void sub_0805EA44(void);
extern void sub_0805F9C8(void);
extern void sub_0805FA00(void);
extern void sub_0805FA18(void);
extern void sub_0805FA58(void);
extern void sub_0805FADC(void);
extern void sub_0805FB14(void);
extern void sub_0805FC58(void);
extern void sub_0805FC94(void);
extern void sub_0805FD10(void);
extern void sub_0805FE84(void);
extern void sub_0805FEC8(void);
extern void sub_0805FF1C(void);
extern void sub_0805FFF8(void);
extern void sub_08060180(void);
extern void sub_080601D4(void);
extern void sub_08060280(void);
extern void sub_080602BC(void);
extern void sub_0806030C(void);
extern void sub_08060400(void);
extern void sub_0806045C(void);
extern void sub_0806048C(void);
extern void sub_080604C4(void);
extern void sub_0806050C(void);
extern void sub_08060688(void);
extern void sub_080606A8(void);
extern void sub_08060708(void);
extern void sub_0806096C(void);
extern void sub_080609D4(void);
extern void sub_08060A1C(void);
extern void sub_08060A54(void);
extern void sub_08060AF4(void);
extern void sub_08060B28(void);
extern void sub_08060D6C(void);
extern void sub_08060DAC(void);
extern void sub_08060DC8(void);
extern void sub_08060DD4(void);
extern void sub_08060F78(void);
extern void sub_0806113C(void);
extern void sub_080611E8(void);
extern void sub_080612E8(void);
extern void sub_08061338(void);
extern void sub_08061440(void);
extern void sub_08061468(void);
extern void sub_080614DC(void);
extern void sub_08061594(void);
extern void sub_080615D4(void);
extern void sub_080617E0(void);
extern void sub_08061860(void);
extern void sub_080618B4(void);
extern void sub_08061958(void);
extern void sub_08061998(void);
extern void sub_080619B0(void);
extern void sub_08061CE0(void);
extern void sub_08061E98(void);
extern void sub_08061F00(void);
extern void sub_08062484(void);
extern void sub_080625F0(void);
extern void sub_08062614(void);
extern void sub_08062754(void);
extern void sub_080627A0(void);
extern void sub_080629DC(void);
extern void sub_08063948(void);
extern void sub_0806463C(void);
extern void sub_080649BC(void);
extern void sub_08064B90(void);
extern void sub_08064BBC(void);
extern void sub_08064DA8(void);
extern void sub_08064DB4(void);
extern void sub_08064DF4(void);
extern void sub_08064E18(void);
extern void sub_08064EB4(void);
extern void sub_08065074(void);
extern void sub_08065198(void);
extern void sub_08065208(void);
extern void sub_080654C0(void);
extern void sub_0806552C(void);
extern void sub_08065590(void);
extern void sub_080655FC(void);
extern void sub_08065D10(void);
extern void sub_08066824(void);
extern void sub_08067B9C(void);
extern void sub_08068400(void);

/* 16-color palette copied by CpuFastSet with eight words. */
const u16 gMain2NameTransfer_08483534[16] = {
    0x0000, 0x02FF, 0x01DF, 0x009F, 0x0000, 0x03EF, 0x02C8, 0x0162,
    0x7F80, 0x75E0, 0x5400, 0x0000, 0x7F7B, 0x6673, 0x456B, 0x2884,
};

/* Boolean choice lookup read by 0805B5FC; all 64 physical bytes retained. */
const u8 gUnknown_08483554[64] __attribute__((aligned(1))) = {
    0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const MainCallback gMain2Callbacks_08483594[30] = {
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_0805C0D4,
    sub_0805CB50,
    sub_0805D704,
    sub_0805E404,
    sub_0805F104,
    sub_0805FC58,
    sub_08060280,
    sub_08060688,
    sub_08060D6C,
    sub_08061958,
    DummyInterruptHandler,
    DummyInterruptHandler,
    DummyInterruptHandler,
    sub_08063948,
    sub_0806463C,
    sub_08064DB4,
    sub_080649BC,
    sub_08066824,
    sub_08065D10,
    sub_08067B9C,
    sub_08060688,
    sub_08068400,
    sub_080629DC,
    sub_08064BBC,
    sub_08064B90,
    sub_0805CB20,
    DummyInterruptHandler,
};

const MainCallback gMain2Subcallbacks_0848360C[40] = {
    sub_0805C128,
    sub_0805C17C,
    sub_0805C2DC,
    sub_0805C410,
    sub_0805C454,
    sub_0805C574,
    sub_0805C7F8,
    sub_0805C8EC,
    sub_0805C950,
    sub_0805C988,
    sub_0805CBFC,
    sub_0805CC3C,
    sub_0805CDAC,
    sub_0805CED0,
    sub_0805CF58,
    sub_0805CFB4,
    sub_0805D4A0,
    sub_0805D4E0,
    sub_0805D4FC,
    sub_0805D580,
    sub_0805D5A4,
    sub_0805D5D0,
    sub_0805D5F0,
    sub_0805D658,
    sub_0805D674,
    sub_0805D750,
    sub_0805D790,
    sub_0805D860,
    sub_0805DA14,
    sub_0805DAB0,
    sub_0805DAD4,
    sub_0805DB84,
    sub_0805DBC4,
    sub_0805DC4C,
    sub_0805DC88,
    sub_0805DCB0,
    sub_0805DCCC,
    sub_0805DD50,
    sub_0805DB20,
    sub_0805DB4C,
};

/* FE-terminated YES and NO labels followed by an additional FE byte. */
const u8 gMain2YesNoLabels_084836AC[8] __attribute__((aligned(1))) = {
    0x19, 0x05, 0x13, 0xFE, 0x0E, 0x0F, 0xFE, 0xFE,
};

const u8 gMain2SerializerSignature_084836B4[17] __attribute__((aligned(1))) = "MEDAROT2 Ver.KBT";

const u8 gMain2SaveSignature_084836C5[17] __attribute__((aligned(1))) = "MEDAROT2 NATSUME";

const u8 gMain2SaveAlignment_084836D6[2] __attribute__((aligned(1))) = {
    0x00, 0x00,
};

const MainCallback gMain2SaveCallbacks_084836D8[7] = {
    sub_0805E450,
    sub_0805E478,
    sub_0805E718,
    sub_0805E9E0,
    sub_0805EA44,
    sub_0805EFD4,
    sub_0805EFFC,
};

/* Encoded default name, including its FE terminal. */
const u8 gMain2DefaultName_084836F4[5] __attribute__((aligned(1))) = {
    0x09, 0x25, 0x25, 0x23, 0xFE,
};

const u8 gMain2DefaultNameAlignment_084836F9[3] __attribute__((aligned(1))) = {
    0x00, 0x00, 0x00,
};

const u8 *const gMain2SaveNamePointers_084836FC[1] = {
    gMain2DefaultName_084836F4,
};

const MainCallback gMain2NameCallbacks_08483700[14] = {
    sub_0805F144,
    sub_0805F19C,
    sub_0805F358,
    sub_0805F414,
    sub_0805F488,
    sub_0805F8E0,
    sub_0805F960,
    sub_0805F984,
    sub_0805F9C8,
    sub_0805FA18,
    sub_0805FA58,
    sub_0805FADC,
    sub_0805FB14,
    sub_0805FA00,
};

const MainCallback gUnknown_08483738[8] = {
    sub_0805FC94,
    sub_0805FD10,
    sub_0805FE84,
    sub_0805FEC8,
    sub_0805FF1C,
    sub_0805FFF8,
    sub_08060180,
    sub_080601D4,
};

const MainCallback gUnknown_08483758[7] = {
    sub_080602BC,
    sub_0806030C,
    sub_08060400,
    sub_0806045C,
    sub_0806048C,
    sub_080604C4,
    sub_0806050C,
};

/* 192 scene IDs select a cursor coordinate pair in 08060708. Choice 10 reads into the following X-offset data in the reference. */
const u8 gMain2SceneCursorChoices_08483774[192] __attribute__((aligned(1))) = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x0A, 0x0A, 0x0A, 0x0A, 0x09, 0x09, 0x09, 0x09,
    0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09,
    0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09,
    0x09, 0x09, 0x09, 0x09, 0x09, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x0A, 0x0A,
    0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
    0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x07, 0x07, 0x07, 0x07, 0x00, 0x09, 0x00, 0x00,
};

const MainCallback gUnknown_08483834[8] = {
    sub_080606A8,
    sub_08060708,
    sub_0806096C,
    sub_080609D4,
    sub_08060A1C,
    sub_08060A54,
    sub_08060AF4,
    sub_08060B28,
};

/* Ten physical tile-coordinate pairs; 080605A0 multiplies each component by eight. */
const u8 gTable08483854[20] __attribute__((aligned(1))) = {
    0x0F, 0x08, 0x12, 0x05, 0x0E, 0x05, 0x16, 0x07, 0x16, 0x0A, 0x1B, 0x07, 0x1B, 0x0A, 0x0F, 0x0B,
    0x0A, 0x06, 0x04, 0x09,
};

/* Two choices of four animation X offsets. */
const u16 gTable08483868[8] = {
    0x0002, 0x0003, 0x0004, 0x0003, 0x0006, 0x0006, 0x0006, 0x0006,
};

/* Two choices of four animation Y offsets. */
const u16 gTable08483878[8] = {
    0x0002, 0x0003, 0x0004, 0x0003, 0x0002, 0x0003, 0x0004, 0x0003,
};

/* Two choices of four animation frame/group halfwords. */
const u16 gTable08483888[8] = {
    0x010D, 0x010D, 0x010D, 0x010D, 0x010F, 0x0110, 0x0111, 0x0110,
};

/* Eleven phase/10 block selectors; copied block is (selector + 1) * 0x1E0. */
const u8 gAnimationBlocks60620[11] __attribute__((aligned(1))) = {
    0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x02, 0x03, 0x03,
};

const u8 gMain2AnimationAlignment_084838A3[1] __attribute__((aligned(1))) = {
    0x00,
};

const MainCallback gUnknown_084838A4[16] = {
    sub_08060DAC,
    sub_08060F78,
    sub_0806113C,
    sub_080611E8,
    sub_080612E8,
    sub_08061338,
    sub_08061440,
    sub_08061468,
    sub_080614DC,
    sub_08061594,
    sub_080615D4,
    sub_080617E0,
    sub_08061860,
    sub_080618B4,
    sub_08060DD4,
    sub_08060DC8,
};

/* 080619B0 selects a row with work[05], reads up to four item IDs and stops at FF. */
const u8 gMain2PresetItems_084838E4[15][4] = {
    { 0x13, 0x00, 0xFF, 0xFF },
    { 0x13, 0x00, 0x42, 0xFF },
    { 0x13, 0x00, 0x42, 0x1C },
    { 0x1D, 0x1E, 0xFF, 0xFF },
    { 0x1F, 0x58, 0xFF, 0xFF },
    { 0x0D, 0x63, 0xFF, 0xFF },
    { 0x0D, 0x63, 0x0A, 0xFF },
    { 0x0D, 0x63, 0x0A, 0x4D },
    { 0x0E, 0x0F, 0xFF, 0xFF },
    { 0x0E, 0x0F, 0x12, 0xFF },
    { 0x0E, 0x0F, 0x12, 0x20 },
    { 0x23, 0x61, 0xFF, 0xFF },
    { 0x62, 0x6C, 0xFF, 0xFF },
    { 0x62, 0x6C, 0x6D, 0xFF },
    { 0x3B, 0x6F, 0x04, 0xFF },
};

const MainCallback gUnknown_08483920[10] = {
    sub_08061998,
    sub_080619B0,
    sub_08061CE0,
    sub_08061E98,
    sub_08061F00,
    sub_08062484,
    sub_080625F0,
    sub_08062614,
    sub_08062754,
    sub_080627A0,
};

const MainCallback gUnknown_08483948[11] = {
    sub_08064DF4,
    sub_08064E18,
    sub_08064EB4,
    sub_08065074,
    sub_08065198,
    sub_08065208,
    sub_080654C0,
    sub_0806552C,
    sub_08065590,
    sub_080655FC,
    sub_08064DA8,
};

const char gCreditsText_080AFCF4[20] = "SACHIKO YAMAUCHI";

const char gCreditsText_080AFD08[16] = "_LOCALIZATION";

const char gCreditsText_080AFD18[16] = "GRAHAM MARKAY";

const char gCreditsText_080AFD28[8] = "MANAGER";

const char gCreditsText_080AFD30[12] = "_PRODUCT";

const char gCreditsText_080AFD3C[16] = "HIRO MAEKAWA";

const char gCreditsText_080AFD4C[12] = "PRODUCER";

const char gCreditsText_080AFD58[12] = "_EXECUTIVE";

const char gCreditsText_080AFD64[4] = " ";

const char gCreditsText_080AFD68[20] = "EDITORIAL DIVISION";

const char gCreditsText_080AFD7C[16] = "\\BOM BOM]MAG[";

const char gCreditsText_080AFD8C[12] = "KODANSHA^S";

const char gCreditsText_080AFD98[8] = "WITH";

const char gCreditsText_080AFDA0[16] = "_IN COOPERATION";

const char gCreditsText_080AFDB0[16] = "MAMI FUNAYAMA";

const char gCreditsText_080AFDC0[16] = "JULIE NINOMIYA";

const char gCreditsText_080AFDD0[16] = "TOMIO YOSHIDA";

const char gCreditsText_080AFDE0[16] = "COORDINATORS";

const char gCreditsText_080AFDF0[16] = "_INTERNATIONAL";

const char gCreditsText_080AFE00[20] = "ALL MEDAFIGHTERS";

const char gCreditsText_080AFE14[4] = "AND";

const char gCreditsText_080AFE18[12] = "SHIRATAMA";

const char gCreditsText_080AFE24[16] = "HIROSHI KOYAMA";

const char gCreditsText_080AFE34[20] = "SHINJI MORIMITSU";

const char gCreditsText_080AFE48[16] = "REINA MARUYAMA";

const char gCreditsText_080AFE58[12] = "TETSUYA OKU";

const char gCreditsText_080AFE64[16] = "TOSHIAKI KANAME";

const char gCreditsText_080AFE74[20] = "_SPECIAL THANKS TO";

const char gCreditsText_080AFE88[20] = "TETSUARI WATANABE";

const char gCreditsText_080AFE9C[20] = "_SFX AND SOUND DATA";

const char gCreditsText_080AFEB0[12] = "KINUYO UEDA";

const char gCreditsText_080AFEBC[16] = "_MUSIC COMPOSER";

const char gCreditsText_080AFECC[16] = "IKKY MIZUTANI";

const char gCreditsText_080AFEDC[16] = "_SOUND PRODUCER";

const char gCreditsText_080AFEEC[16] = "DAISUKE SAKANE";

const char gCreditsText_080AFEFC[16] = "YASUYO YAMAMOTO";

const char gCreditsText_080AFF0C[16] = "SATOSHI UEDA";

const char gCreditsText_080AFF1C[16] = "SYUYA TAKAOKA";

const char gCreditsText_080AFF2C[20] = "TERUYUKI HIRAOKA";

const char gCreditsText_080AFF40[12] = "_ART WORKER";

const char gCreditsText_080AFF4C[16] = "_VISUAL DESIGN";

const char gCreditsText_080AFF5C[16] = "RYUSUKE NISHIDA";

const char gCreditsText_080AFF6C[16] = "NAOKI TOMOSADA";

const char gCreditsText_080AFF7C[20] = "MITSUGU TAKAMIYA";

const char gCreditsText_080AFF90[16] = "WATARU KITAMURA";

const char gCreditsText_080AFFA0[12] = "_PROGRAMMER";

const char gCreditsText_080AFFAC[16] = "HIROSHI SAITO";

const char gCreditsText_080AFFBC[12] = "_DIRECTOR";

const char gCreditsText_080AFFC8[12] = "TAKESHI UTO";

const char gCreditsText_080AFFD4[12] = "_PRODUCER";

const char gCreditsText_080AFFE0[16] = "KIMIO HIROTA";

const char gCreditsText_080AFFF0[12] = "_SUPERVISOR";

const char gCreditsText_080AFFFC[18] = "TAKASHI MATSUMOTO";

const char *const gCreditsLinesFirst_08483974[31] = {
    gCreditsText_080AFD64,
    gCreditsText_080AFD58,
    gCreditsText_080AFD4C,
    gCreditsText_080AFD64,
    gCreditsText_080AFD3C,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD30,
    gCreditsText_080AFD28,
    gCreditsText_080AFD64,
    gCreditsText_080AFD18,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD08,
    gCreditsText_080AFD28,
    gCreditsText_080AFD64,
    gCreditsText_080AFCF4,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
};

const char *const gCreditsLinesSecond_084839F0[29] = {
    gCreditsText_080AFD64,
    gCreditsText_080AFDF0,
    gCreditsText_080AFDE0,
    gCreditsText_080AFD64,
    gCreditsText_080AFDD0,
    gCreditsText_080AFD64,
    gCreditsText_080AFDC0,
    gCreditsText_080AFD64,
    gCreditsText_080AFDB0,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFDA0,
    gCreditsText_080AFD98,
    gCreditsText_080AFD8C,
    gCreditsText_080AFD7C,
    gCreditsText_080AFD68,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
};

const char *const gCreditsLinesThird_08483A64[107] = {
    gCreditsText_080AFD64,
    gCreditsText_080AFD58,
    gCreditsText_080AFD4C,
    gCreditsText_080AFD64,
    gCreditsText_080AFFFC,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFFF0,
    gCreditsText_080AFD64,
    gCreditsText_080AFFE0,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFFD4,
    gCreditsText_080AFD64,
    gCreditsText_080AFFC8,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFFBC,
    gCreditsText_080AFD64,
    gCreditsText_080AFFAC,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFFA0,
    gCreditsText_080AFD64,
    gCreditsText_080AFF90,
    gCreditsText_080AFD64,
    gCreditsText_080AFF7C,
    gCreditsText_080AFD64,
    gCreditsText_080AFF6C,
    gCreditsText_080AFD64,
    gCreditsText_080AFF5C,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFF4C,
    gCreditsText_080AFD64,
    gCreditsText_080AFFAC,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFF40,
    gCreditsText_080AFD64,
    gCreditsText_080AFF2C,
    gCreditsText_080AFD64,
    gCreditsText_080AFF1C,
    gCreditsText_080AFD64,
    gCreditsText_080AFF0C,
    gCreditsText_080AFD64,
    gCreditsText_080AFEFC,
    gCreditsText_080AFD64,
    gCreditsText_080AFEEC,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFEDC,
    gCreditsText_080AFD64,
    gCreditsText_080AFECC,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFEBC,
    gCreditsText_080AFD64,
    gCreditsText_080AFEB0,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFE9C,
    gCreditsText_080AFD64,
    gCreditsText_080AFE88,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFE74,
    gCreditsText_080AFD64,
    gCreditsText_080AFE64,
    gCreditsText_080AFD64,
    gCreditsText_080AFE58,
    gCreditsText_080AFD64,
    gCreditsText_080AFE48,
    gCreditsText_080AFD64,
    gCreditsText_080AFE34,
    gCreditsText_080AFD64,
    gCreditsText_080AFE24,
    gCreditsText_080AFD64,
    gCreditsText_080AFE18,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFE14,
    gCreditsText_080AFD64,
    gCreditsText_080AFE00,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
    gCreditsText_080AFD64,
};

const char *const *const gCreditsLineLists_080B0014[3] = {
    gCreditsLinesFirst_08483974,
    gCreditsLinesSecond_084839F0,
    gCreditsLinesThird_08483A64,
};

/* Three credits line counts: 31, 29 and 107. */
const u8 gUnknown_08483C10[3] __attribute__((aligned(1))) = {
    0x1F, 0x1D, 0x6B,
};

const u8 gCreditsCountAlignment_08483C13[1] __attribute__((aligned(1))) = {
    0x00,
};

const u8 gMain2Label_08483C14[9] __attribute__((aligned(1))) = {
    0x14, 0x29, 0x31, 0x28, 0x00, 0x0D, 0x1B, 0x2A, 0xFE,
};

const u8 gMain2Label_08483C1D[6] __attribute__((aligned(1))) = {
    0x13, 0x25, 0x23, 0x2C, 0x2E, 0xFE,
};

const u8 gMain2Label_08483C23[9] __attribute__((aligned(1))) = {
    0x0C, 0x2F, 0x28, 0x1D, 0x22, 0x1C, 0x29, 0x32, 0xFE,
};

const u8 gMain2Label_08483C2C[7] __attribute__((aligned(1))) = {
    0x0C, 0x1F, 0x2E, 0x2E, 0x1F, 0x2C, 0xFE,
};

const u8 gMain2Label_08483C33[13] __attribute__((aligned(1))) = {
    0x02, 0x2C, 0x29, 0x25, 0x1F, 0x28, 0x00, 0x10, 0x1B, 0x2C, 0x2E, 0x2D, 0xFE,
};

const u8 gMain2Label_08483C40[7] __attribute__((aligned(1))) = {
    0x0B, 0x23, 0x27, 0x29, 0x28, 0x29, 0xFE,
};

const u8 gMain2Label_08483C47[15] __attribute__((aligned(1))) = {
    0x13, 0x40, 0x01, 0x28, 0x23, 0x27, 0x1B, 0x26, 0x00, 0x12, 0x1B, 0x2A, 0x2A, 0x33, 0xFE,
};

const u8 gMain2Label_08483C56[12] __attribute__((aligned(1))) = {
    0x13, 0x22, 0x23, 0x2A, 0x00, 0x14, 0x23, 0x1D, 0x25, 0x1F, 0x2E, 0xFE,
};

const u8 gMain2Label_08483C62[13] __attribute__((aligned(1))) = {
    0x07, 0x23, 0x2C, 0x26, 0x42, 0x2D, 0x00, 0x0D, 0x1F, 0x1E, 0x1B, 0x26, 0xFE,
};

const u8 gMain2Label_08483C6F[13] __attribute__((aligned(1))) = {
    0x0F, 0x2C, 0x1B, 0x28, 0x21, 0x1F, 0x00, 0x0A, 0x2F, 0x23, 0x1D, 0x1F, 0xFE,
};

const u8 gMain2Label_08483C7C[11] __attribute__((aligned(1))) = {
    0x0C, 0x1F, 0x27, 0x29, 0x28, 0x00, 0x10, 0x1B, 0x1D, 0x25, 0xFE,
};

const u8 gMain2Label_08483C87[11] __attribute__((aligned(1))) = {
    0x04, 0x1F, 0x26, 0x2F, 0x32, 0x1F, 0x00, 0x0F, 0x23, 0x26, 0xFE,
};

const u8 gMain2Label_08483C92[13] __attribute__((aligned(1))) = {
    0x08, 0x1F, 0x2C, 0x29, 0x00, 0x03, 0x29, 0x2D, 0x2E, 0x2F, 0x27, 0x1F, 0xFE,
};

const u8 gMain2Label_08483C9F[6] __attribute__((aligned(1))) = {
    0x04, 0x2C, 0x1F, 0x2D, 0x2D, 0xFE,
};

const u8 gMain2Label_08483CA5[15] __attribute__((aligned(1))) = {
    0x14, 0x1F, 0x26, 0x1F, 0x2A, 0x22, 0x29, 0x2E, 0x29, 0x00, 0x0C, 0x1F, 0x28, 0x2D, 0xFE,
};

const u8 gMain2Label_08483CB4[8] __attribute__((aligned(1))) = {
    0x08, 0x1B, 0x27, 0x2D, 0x2E, 0x1F, 0x2C, 0xFE,
};

const u8 gMain2Label_08483CBC[15] __attribute__((aligned(1))) = {
    0x10, 0x22, 0x29, 0x2E, 0x29, 0x00, 0x29, 0x20, 0x00, 0x0B, 0x1B, 0x2C, 0x23, 0x28, 0xFE,
};

const u8 gMain2Label_08483CCB[8] __attribute__((aligned(1))) = {
    0x0E, 0x1B, 0x27, 0x1F, 0x2E, 0x1B, 0x21, 0xFE,
};

const u8 gMain2Label_08483CD3[13] __attribute__((aligned(1))) = {
    0x0D, 0x23, 0x28, 0x23, 0x00, 0x13, 0x40, 0x17, 0x22, 0x1F, 0x1F, 0x26, 0xFE,
};

const u8 gMain2Label_08483CE0[15] __attribute__((aligned(1))) = {
    0x12, 0x2F, 0x1C, 0x1C, 0x1F, 0x2C, 0x29, 0x1C, 0x29, 0x00, 0x13, 0x2F, 0x23, 0x2E, 0xFE,
};

const u8 gMain2Label_08483CEF[13] __attribute__((aligned(1))) = {
    0x0B, 0x1F, 0x33, 0x45, 0x00, 0x01, 0x00, 0x03, 0x26, 0x1B, 0x2D, 0x2D, 0xFE,
};

const u8 gMain2Label_08483CFC[13] __attribute__((aligned(1))) = {
    0x0B, 0x1F, 0x33, 0x45, 0x00, 0x02, 0x00, 0x03, 0x26, 0x1B, 0x2D, 0x2D, 0xFE,
};

const u8 gMain2Label_08483D09[8] __attribute__((aligned(1))) = {
    0x02, 0x23, 0x21, 0x00, 0x0B, 0x1F, 0x33, 0xFE,
};

const u8 gMain2Label_08483D11[12] __attribute__((aligned(1))) = {
    0x0D, 0x1B, 0x28, 0x22, 0x29, 0x26, 0x1F, 0x00, 0x0B, 0x1F, 0x33, 0xFE,
};

const u8 gMain2Label_08483D1D[14] __attribute__((aligned(1))) = {
    0x13, 0x23, 0x26, 0x30, 0x1F, 0x2C, 0x00, 0x0C, 0x29, 0x1D, 0x25, 0x1F, 0x2E, 0xFE,
};

const u8 gMain2Label_08483D2B[14] __attribute__((aligned(1))) = {
    0x17, 0x23, 0x28, 0x21, 0x2D, 0x00, 0x29, 0x20, 0x00, 0x17, 0x23, 0x28, 0x1E, 0xFE,
};

const u8 gMain2Label_08483D39[6] __attribute__((aligned(1))) = {
    0x0C, 0x1F, 0x27, 0x29, 0x28, 0xFE,
};

const u8 gMain2Label_08483D3F[15] __attribute__((aligned(1))) = {
    0x0C, 0x1F, 0x27, 0x29, 0x28, 0x00, 0x02, 0x1B, 0x2E, 0x2E, 0x1F, 0x2C, 0x33, 0x00, 0xFE,
};

const u8 gMain2Label_08483D4E[9] __attribute__((aligned(1))) = {
    0x10, 0x29, 0x26, 0x1B, 0x2C, 0x29, 0x23, 0x1E, 0xFE,
};

const u8 gMain2Label_08483D57[12] __attribute__((aligned(1))) = {
    0x06, 0x23, 0x33, 0x2F, 0x28, 0x00, 0x13, 0x2E, 0x29, 0x28, 0x1F, 0xFE,
};

const u8 gMain2Label_08483D63[11] __attribute__((aligned(1))) = {
    0x09, 0x28, 0x30, 0x23, 0x2E, 0x1B, 0x2E, 0x23, 0x29, 0x28, 0xFE,
};

const u8 gMain2Label_08483D6E[14] __attribute__((aligned(1))) = {
    0x17, 0x1B, 0x26, 0x25, 0x23, 0x1F, 0x00, 0x14, 0x1B, 0x26, 0x25, 0x23, 0x1F, 0xFE,
};

const u8 gMain2Label_08483D7C[10] __attribute__((aligned(1))) = {
    0x0B, 0x1F, 0x33, 0x31, 0x29, 0x2C, 0x1E, 0x00, 0x36, 0xFE,
};

const u8 gMain2Label_08483D86[10] __attribute__((aligned(1))) = {
    0x0B, 0x1F, 0x33, 0x31, 0x29, 0x2C, 0x1E, 0x00, 0x37, 0xFE,
};

const u8 gMain2Label_08483D90[10] __attribute__((aligned(1))) = {
    0x0B, 0x1F, 0x33, 0x31, 0x29, 0x2C, 0x1E, 0x00, 0x38, 0xFE,
};

const u8 gMain2Label_08483D9A[10] __attribute__((aligned(1))) = {
    0x0B, 0x1F, 0x33, 0x31, 0x29, 0x2C, 0x1E, 0x00, 0x39, 0xFE,
};

const u8 gMain2Label_08483DA4[13] __attribute__((aligned(1))) = {
    0x12, 0x2F, 0x2D, 0x2E, 0x1F, 0x1E, 0x00, 0x10, 0x1B, 0x2C, 0x2E, 0x2D, 0xFE,
};

const u8 gMain2Label_08483DB1[7] __attribute__((aligned(1))) = {
    0x13, 0x31, 0x23, 0x2E, 0x1D, 0x22, 0xFE,
};

const u8 gMain2Label_08483DB8[10] __attribute__((aligned(1))) = {
    0x10, 0x1F, 0x2C, 0x23, 0x2D, 0x1D, 0x29, 0x2A, 0x1F, 0xFE,
};

const u8 gMain2Label_08483DC2[17] __attribute__((aligned(1))) = {
    0x17, 0x1B, 0x23, 0x2E, 0x2C, 0x1F, 0x2D, 0x2D, 0x00, 0x15, 0x28, 0x23, 0x20, 0x29, 0x2C, 0x27,
    0xFE,
};

const u8 gMain2Label_08483DD3[11] __attribute__((aligned(1))) = {
    0x04, 0x29, 0x21, 0x00, 0x0F, 0x2F, 0x2E, 0x20, 0x23, 0x2E, 0xFE,
};

const u8 gMain2Label_08483DDE[9] __attribute__((aligned(1))) = {
    0x13, 0x2A, 0x1F, 0x1E, 0x1B, 0x1C, 0x29, 0x2E, 0xFE,
};

const u8 gMain2Label_08483DE7[14] __attribute__((aligned(1))) = {
    0x0B, 0x42, 0x2D, 0x00, 0x01, 0x2F, 0x2E, 0x29, 0x21, 0x2C, 0x1B, 0x2A, 0x22, 0xFE,
};

const u8 gMain2Label_08483DF5[14] __attribute__((aligned(1))) = {
    0x0B, 0x1B, 0x2C, 0x23, 0x28, 0x42, 0x2D, 0x00, 0x0D, 0x1F, 0x1E, 0x1B, 0x26, 0xFE,
};

const u8 gMain2Label_08483E03[14] __attribute__((aligned(1))) = {
    0x10, 0x1B, 0x2C, 0x2E, 0x2D, 0x2F, 0x28, 0x00, 0x02, 0x1B, 0x1E, 0x21, 0x1F, 0xFE,
};

const u8 gMain2Label_08483E11[16] __attribute__((aligned(1))) = {
    0x07, 0x29, 0x26, 0x1E, 0x00, 0x02, 0x26, 0x1B, 0x1D, 0x25, 0x00, 0x0C, 0x2F, 0x2C, 0x1F, 0xFE,
};

const u8 gMain2Label_08483E21[13] __attribute__((aligned(1))) = {
    0x02, 0x26, 0x2F, 0x1F, 0x00, 0x03, 0x1B, 0x2A, 0x2D, 0x2F, 0x26, 0x1F, 0xFE,
};

const u8 gMain2Label_08483E2E[12] __attribute__((aligned(1))) = {
    0x10, 0x23, 0x28, 0x25, 0x00, 0x06, 0x26, 0x29, 0x31, 0x1F, 0x2C, 0xFE,
};

const u8 gMain2Label_08483E3A[13] __attribute__((aligned(1))) = {
    0x07, 0x1B, 0x27, 0x1F, 0x00, 0x02, 0x29, 0x33, 0x00, 0x12, 0x1F, 0x1E, 0xFE,
};

const u8 gMain2Label_08483E47[15] __attribute__((aligned(1))) = {
    0x12, 0x1B, 0x2C, 0x1F, 0x00, 0x0D, 0x1F, 0x1E, 0x1B, 0x31, 0x1B, 0x2E, 0x1D, 0x22, 0xFE,
};

const u8 gMain2Label_08483E56[16] __attribute__((aligned(1))) = {
    0x12, 0x2F, 0x1C, 0x1C, 0x1F, 0x2C, 0x29, 0x1C, 0x29, 0x00, 0x0D, 0x1F, 0x1E, 0x1B, 0x26, 0xFE,
};

const u8 gMain2Label_08483E66[9] __attribute__((aligned(1))) = {
    0x10, 0x1F, 0x28, 0x26, 0x23, 0x21, 0x22, 0x2E, 0xFE,
};

const u8 gMain2Label_08483E6F[8] __attribute__((aligned(1))) = {
    0x0E, 0x29, 0x2E, 0x22, 0x23, 0x28, 0x21, 0xFE,
};

const u8 gMain2Label_08483E77[8] __attribute__((aligned(1))) = {
    0x0E, 0x29, 0x2E, 0x22, 0x23, 0x28, 0x21, 0xFE,
};

const u8 gMain2Label_08483E7F[14] __attribute__((aligned(1))) = {
    0x05, 0x2C, 0x23, 0x25, 0x1B, 0x42, 0x2D, 0x00, 0x0D, 0x1F, 0x1E, 0x1B, 0x26, 0xFE,
};

const u8 gMain2Label_08483E8D[8] __attribute__((aligned(1))) = {
    0x0E, 0x29, 0x2E, 0x22, 0x23, 0x28, 0x21, 0xFE,
};

const u8 gMain2Label_08483E95[8] __attribute__((aligned(1))) = {
    0x0E, 0x29, 0x2E, 0x22, 0x23, 0x28, 0x21, 0xFE,
};

const u8 gMain2Label_08483E9D[8] __attribute__((aligned(1))) = {
    0x0E, 0x29, 0x2E, 0x22, 0x23, 0x28, 0x21, 0xFE,
};

const u8 gMain2Label_08483EA5[8] __attribute__((aligned(1))) = {
    0x0E, 0x29, 0x2E, 0x22, 0x23, 0x28, 0x21, 0xFE,
};

const u8 gMain2Label_08483EAD[8] __attribute__((aligned(1))) = {
    0x0E, 0x29, 0x2E, 0x22, 0x23, 0x28, 0x21, 0xFE,
};

const u8 gMain2Label_08483EB5[8] __attribute__((aligned(1))) = {
    0x0E, 0x29, 0x2E, 0x22, 0x23, 0x28, 0x21, 0xFE,
};

const u8 gMain2Label_08483EBD[8] __attribute__((aligned(1))) = {
    0x0E, 0x29, 0x2E, 0x22, 0x23, 0x28, 0x21, 0xFE,
};

const u8 gMain2Label_08483EC5[8] __attribute__((aligned(1))) = {
    0x0E, 0x29, 0x2E, 0x22, 0x23, 0x28, 0x21, 0xFE,
};

const u8 gMain2Label_08483ECD[8] __attribute__((aligned(1))) = {
    0x0E, 0x29, 0x00, 0x09, 0x2E, 0x1F, 0x27, 0xFE,
};

const u8 gMain2LabelAlignment_08483ED5[3] __attribute__((aligned(1))) = {
    0x00, 0x00, 0x00,
};

const void *const gFreshPointers_08483ED8[64] = {
    gMain2Label_08483C14,
    gMain2Label_08483C1D,
    gMain2Label_08483C23,
    gMain2Label_08483C2C,
    gMain2Label_08483C33,
    gMain2Label_08483C40,
    gMain2Label_08483C47,
    gMain2Label_08483C56,
    gMain2Label_08483C62,
    gMain2Label_08483C6F,
    gMain2Label_08483C7C,
    gMain2Label_08483C87,
    gMain2Label_08483C92,
    gMain2Label_08483C9F,
    gMain2Label_08483CA5,
    gMain2Label_08483CB4,
    gMain2Label_08483CBC,
    gMain2Label_08483CCB,
    gMain2Label_08483CD3,
    gMain2Label_08483CE0,
    gMain2Label_08483CEF,
    gMain2Label_08483CFC,
    gMain2Label_08483D09,
    gMain2Label_08483D11,
    gMain2Label_08483D1D,
    gMain2Label_08483D2B,
    gMain2Label_08483D39,
    gMain2Label_08483D3F,
    gMain2Label_08483D4E,
    gMain2Label_08483D57,
    gMain2Label_08483D63,
    gMain2Label_08483D6E,
    gMain2Label_08483D7C,
    gMain2Label_08483D86,
    gMain2Label_08483D90,
    gMain2Label_08483D9A,
    gMain2Label_08483DA4,
    gMain2Label_08483DB1,
    gMain2Label_08483DB8,
    gMain2Label_08483DC2,
    gMain2Label_08483DD3,
    gMain2Label_08483DDE,
    gMain2Label_08483DE7,
    gMain2Label_08483DF5,
    gMain2Label_08483E03,
    gMain2Label_08483E11,
    gMain2Label_08483E21,
    gMain2Label_08483E2E,
    gMain2Label_08483E3A,
    gMain2Label_08483E47,
    gMain2Label_08483E56,
    gMain2Label_08483E66,
    gMain2Label_08483E6F,
    gMain2Label_08483E77,
    gMain2Label_08483E7F,
    gMain2Label_08483E8D,
    gMain2Label_08483E95,
    gMain2Label_08483E9D,
    gMain2Label_08483EA5,
    gMain2Label_08483EAD,
    gMain2Label_08483EB5,
    gMain2Label_08483EBD,
    gMain2Label_08483EC5,
    gMain2Label_08483ECD,
};
