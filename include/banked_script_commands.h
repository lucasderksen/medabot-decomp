#ifndef GUARD_BANKED_SCRIPT_COMMANDS_H
#define GUARD_BANKED_SCRIPT_COMMANDS_H
#include "global.h"

/* Native event command bytes. Unknown semantics retain the opcode name. */
#define BANKED_HEADER_U16(value) ((value) & 0xFF), (((value) >> 8) & 0xFF)
#define BANKED_NOP 0x00 /* sub_0804B73C */
#define BANKED_DIALOGUE(a0, a1, a2) 0x01, (a0), (a1), (a2) /* sub_0804B740 */
#define BANKED_DIALOGUE_02(a0, a1, a2) 0x02, (a0), (a1), (a2) /* sub_0804B74C */
#define BANKED_OP_03 0x03 /* sub_0804B778 */
#define BANKED_WAIT_TICKS(a0) 0x04, (a0) /* sub_0804B78C */
#define BANKED_WAIT_KEY 0x05 /* sub_0804B7B4 */
#define BANKED_END 0x06 /* sub_0804B7C8 */
#define BANKED_OP_07(a0) 0x07, (a0) /* sub_0804B858 */
#define BANKED_OP_08(a0) 0x08, (a0) /* sub_0804B8AC */
#define BANKED_OP_09(a0) 0x09, (a0) /* sub_0804B900 */
#define BANKED_OP_0A(a0) 0x0A, (a0) /* sub_0804B958 */
#define BANKED_OP_0B(a0, a1, a2, a3, a4) 0x0B, (a0), (a1), (a2), (a3), (a4) /* sub_0804B9B0 */
#define BANKED_OP_0C(a0, a1, a2, a3, a4) 0x0C, (a0), (a1), (a2), (a3), (a4) /* sub_0804B9CC */
#define BANKED_OP_0D(a0) 0x0D, (a0) /* sub_0804BA5C */
#define BANKED_OP_0E 0x0E /* sub_0804BA9C */
#define BANKED_OP_0F(a0) 0x0F, (a0) /* sub_0804BAEC */
#define BANKED_OP_10(a0, a1, a2, a3) 0x10, (a0), (a1), (a2), (a3) /* sub_0804BB14 */
#define BANKED_OP_11(a0) 0x11, (a0) /* sub_0804BBA0 */
#define BANKED_OP_12(a0, a1) 0x12, (a0), (a1) /* sub_0804BBC8 */
#define BANKED_OP_13(a0, a1) 0x13, (a0), (a1) /* sub_0804BBF4 */
#define BANKED_OP_14 0x14 /* sub_0804BC20 */
#define BANKED_OP_15 0x15 /* sub_0804BC6C */
#define BANKED_OP_16(a0, a1) 0x16, (a0), (a1) /* sub_0804BCD4 */
#define BANKED_OP_17(a0, a1, a2) 0x17, (a0), (a1), (a2) /* sub_0804BD08 */
#define BANKED_OP_18(a0, a1) 0x18, (a0), (a1) /* sub_0804BD44 */
#define BANKED_OP_19(a0, a1) 0x19, (a0), (a1) /* sub_0804BD70 */
#define BANKED_OP_1A(a0, a1) 0x1A, (a0), (a1) /* sub_0804BDD8 */
#define BANKED_OP_1B 0x1B /* sub_0804BE50 */
#define BANKED_OP_1C(a0) 0x1C, (a0) /* sub_0804BEC4 */
#define BANKED_OP_1D 0x1D /* sub_0804BF34 */
#define BANKED_OP_1E(a0) 0x1E, (a0) /* sub_0804BFB4 */
#define BANKED_OP_1F(a0, a1, a2, a3, a4) 0x1F, (a0), (a1), (a2), (a3), (a4) /* sub_0804C02C */
#define BANKED_OP_20(a0, a1, a2, a3, a4) 0x20, (a0), (a1), (a2), (a3), (a4) /* sub_0804C078 */
#define BANKED_OP_21(a0, a1, a2, a3) 0x21, (a0), (a1), (a2), (a3) /* sub_0804C0C4 */
#define BANKED_OP_22(a0, a1) 0x22, (a0), (a1) /* sub_0804C100 */
#define BANKED_OP_23(a0, a1) 0x23, (a0), (a1) /* sub_0804C130 */
#define BANKED_OP_24(a0, a1) 0x24, (a0), (a1) /* sub_0804C168 */
#define BANKED_OP_25(a0) 0x25, (a0) /* sub_0804C1A0 */
#define BANKED_OP_26(a0, a1) 0x26, (a0), (a1) /* sub_0804C1C0 */
#define BANKED_OP_27(a0, a1, a2) 0x27, (a0), (a1), (a2) /* sub_0804C210 */
#define BANKED_OP_28(a0) 0x28, (a0) /* sub_0804C26C */
#define BANKED_OP_29(a0) 0x29, (a0) /* sub_0804C2C8 */
#define BANKED_OP_2A(a0) 0x2A, (a0) /* sub_0804C2F0 */
#define BANKED_OP_2B(a0, a1, a2, a3, a4) 0x2B, (a0), (a1), (a2), (a3), (a4) /* sub_0804C318 */
#define BANKED_OP_2C(a0) 0x2C, (a0) /* sub_0804C364 */
#define BANKED_OP_2D(a0, a1) 0x2D, (a0), (a1) /* sub_0804C3AC */
#define BANKED_OP_2E(a0, a1, a2) 0x2E, (a0), (a1), (a2) /* sub_0804C3E4 */
#define BANKED_JUMP16(a0, a1) 0x30, (a0), (a1) /* sub_0804C478 */
#define BANKED_OP_31(a0) 0x31, (a0) /* sub_0804C4B4 */
#define BANKED_OP_32(a0) 0x32, (a0) /* sub_0804C4F8 */
#define BANKED_OP_33(a0, a1, a2) 0x33, (a0), (a1), (a2) /* sub_0804C53C */
#define BANKED_OP_34(a0, a1, a2) 0x34, (a0), (a1), (a2) /* sub_0804C588 */
#define BANKED_OP_35(a0) 0x35, (a0) /* sub_0804C5E4 */
#define BANKED_OP_36(a0, a1) 0x36, (a0), (a1) /* sub_0804C648 */
#define BANKED_OP_37(a0, a1) 0x37, (a0), (a1) /* sub_0804C678 */
#define BANKED_OP_38(a0, a1, a2) 0x38, (a0), (a1), (a2) /* sub_0804C6A8 */
#define BANKED_OP_39(a0, a1, a2) 0x39, (a0), (a1), (a2) /* sub_0804C6C8 */
#define BANKED_OP_3A(a0, a1) 0x3A, (a0), (a1) /* sub_0804C6E8 */
#define BANKED_OP_3B(a0, a1) 0x3B, (a0), (a1) /* sub_0804C708 */
#define BANKED_OP_3C(a0) 0x3C, (a0) /* sub_0804C728 */
#define BANKED_OP_3D(a0) 0x3D, (a0) /* sub_0804C750 */
#define BANKED_OP_3E(a0, a1) 0x3E, (a0), (a1) /* sub_0804C778 */
#define BANKED_OP_3F(a0, a1) 0x3F, (a0), (a1) /* sub_0804C7DC */
#define BANKED_OP_40(a0) 0x40, (a0) /* sub_0804C840 */
#define BANKED_OP_41(a0) 0x41, (a0) /* sub_0804C868 */
#define BANKED_OP_42 0x42 /* sub_0804C928 */
#define BANKED_OP_43(a0, a1) 0x43, (a0), (a1) /* sub_0804C92C */
#define BANKED_OP_44(a0) 0x44, (a0) /* sub_0804C94C */
#define BANKED_OP_45(a0) 0x45, (a0) /* sub_0804C960 */
#define BANKED_OP_46 0x46 /* sub_0804C984 */
#define BANKED_OP_47 0x47 /* sub_0804C994 */
#define BANKED_OP_48(a0) 0x48, (a0) /* sub_0804C9A0 */
#define BANKED_OP_49 0x49 /* sub_0804C9C4 */
#define BANKED_OP_4A(a0, a1) 0x4A, (a0), (a1) /* sub_0804C9D4 */
#define BANKED_OP_4B(a0, a1, a2) 0x4B, (a0), (a1), (a2) /* sub_0804CA28 */
#define BANKED_OP_4C(a0, a1, a2) 0x4C, (a0), (a1), (a2) /* sub_0804CA84 */
#define BANKED_OP_4D(a0, a1) 0x4D, (a0), (a1) /* sub_0804CAE8 */
#define BANKED_OP_4E(a0, a1, a2) 0x4E, (a0), (a1), (a2) /* sub_0804CB34 */
#define BANKED_OP_4F(a0) 0x4F, (a0) /* sub_0804CB94 */
#define BANKED_OP_50(a0, a1, a2) 0x50, (a0), (a1), (a2) /* sub_0804CBDC */
#define BANKED_OP_51(a0, a1) 0x51, (a0), (a1) /* sub_0804CC5C */
#define BANKED_OP_52(a0, a1) 0x52, (a0), (a1) /* sub_0804CCAC */
#define BANKED_OP_53(a0, a1) 0x53, (a0), (a1) /* sub_0804CCF4 */
#define BANKED_OP_54 0x54 /* sub_0804CD60 */
#define BANKED_OP_55 0x55 /* sub_0804CD64 */
#define BANKED_OP_56 0x56 /* sub_0804CD68 */
#define BANKED_OP_57 0x57 /* sub_0804CD7C */
#define BANKED_OP_58 0x58 /* sub_0804CD80 */
#define BANKED_OP_59(a0) 0x59, (a0) /* sub_0804CD84 */
#define BANKED_OP_5A(a0) 0x5A, (a0) /* sub_0804CDA4 */
#define BANKED_OP_5B(a0) 0x5B, (a0) /* sub_0804CE04 */
#define BANKED_OP_5C(a0, a1) 0x5C, (a0), (a1) /* sub_0804CE44 */
#define BANKED_OP_5D(a0) 0x5D, (a0) /* sub_0804CE90 */
#define BANKED_OP_5E(a0) 0x5E, (a0) /* sub_0804CEF8 */
#define BANKED_OP_5F(a0) 0x5F, (a0) /* sub_0804CF40 */
#define BANKED_OP_60(a0, a1, a2) 0x60, (a0), (a1), (a2) /* sub_0804CF5C */
#define BANKED_OP_61 0x61 /* sub_0804D00C */
#define BANKED_OP_62 0x62 /* sub_0804D018 */
#define BANKED_OP_63(a0, a1, a2) 0x63, (a0), (a1), (a2) /* sub_0804D024 */
#define BANKED_OP_64 0x64 /* sub_0804D084 */
#define BANKED_OP_65 0x65 /* sub_0804D090 */
#define BANKED_OP_66(a0, a1) 0x66, (a0), (a1) /* sub_0804D094 */
#define BANKED_OP_67(a0, a1) 0x67, (a0), (a1) /* sub_0804D0E0 */
#define BANKED_OP_68(a0, a1) 0x68, (a0), (a1) /* sub_0804D100 */
#define BANKED_OP_69(a0, a1) 0x69, (a0), (a1) /* sub_0804D158 */
#define BANKED_OP_6A 0x6A /* sub_0804D204 */
#define BANKED_OP_6B(a0) 0x6B, (a0) /* sub_0804D208 */
#define BANKED_OP_6C(a0, a1, a2, a3, a4) 0x6C, (a0), (a1), (a2), (a3), (a4) /* sub_0804D224 */
#define BANKED_OP_6D(a0, a1) 0x6D, (a0), (a1) /* sub_0804D270 */
#define BANKED_OP_6E(a0, a1, a2, a3, a4) 0x6E, (a0), (a1), (a2), (a3), (a4) /* sub_0804D2A8 */
#define BANKED_OP_6F(a0, a1) 0x6F, (a0), (a1) /* sub_0804D2F4 */
#define BANKED_OP_70 0x70 /* sub_0804D32C */
#define BANKED_OP_71 0x71 /* sub_0804D340 */
#define BANKED_OP_72 0x72 /* sub_0804D354 */
#define BANKED_OP_73 0x73 /* sub_0804D368 */
#define BANKED_OP_74 0x74 /* sub_0804D37C */
#define BANKED_OP_75 0x75 /* sub_0804D380 */
#define BANKED_OP_76 0x76 /* sub_0804D384 */
#define BANKED_OP_77 0x77 /* sub_0804D398 */
#define BANKED_OP_78(a0, a1) 0x78, (a0), (a1) /* sub_0804D39C */
#define BANKED_OP_79(a0) 0x79, (a0) /* sub_0804D400 */
#define BANKED_OP_7A 0x7A /* sub_0804D424 */
#define BANKED_OP_7B(a0, a1, a2) 0x7B, (a0), (a1), (a2) /* sub_0804D438 */
#define BANKED_OP_7C 0x7C /* sub_0804D48C */
#define BANKED_OP_7D(a0) 0x7D, (a0) /* sub_0804D490 */
#define BANKED_OP_7E(a0) 0x7E, (a0) /* sub_0804D4AC */
#define BANKED_OP_7F(a0) 0x7F, (a0) /* sub_0804D4D4 */
#define BANKED_RESET_AND_DISPATCH 0x80 /* sub_0804D4FC */
#define BANKED_ADD_ROW_AND_DISPATCH(a0, a1, a2, a3, a4, a5, a6, a7) 0x81, (a0), (a1), (a2), (a3), (a4), (a5), (a6), (a7) /* sub_0804D580 */
#define BANKED_OP_82 0x82 /* sub_0804D5DC */
#define BANKED_OP_83(a0, a1) 0x83, (a0), (a1) /* sub_0804D5F0 */
#define BANKED_OP_84(a0) 0x84, (a0) /* sub_0804D758 */
#define BANKED_OP_85 0x85 /* sub_0804D778 */
#define BANKED_ADD_ROW(a0, a1, a2, a3, a4, a5, a6, a7) 0x86, (a0), (a1), (a2), (a3), (a4), (a5), (a6), (a7) /* sub_0804D7AC */
#define BANKED_OP_87 0x87 /* sub_0804D7E4 */
#define BANKED_OP_88(a0, a1) 0x88, (a0), (a1) /* sub_0804D7F8 */
#define BANKED_SWITCH_1(a0) 0x2F, (a0)
#define BANKED_SWITCH_2(a0, a1) 0x2F, (a0), (a1)
#define BANKED_SWITCH_3(a0, a1, a2) 0x2F, (a0), (a1), (a2)
#define BANKED_SWITCH_4(a0, a1, a2, a3) 0x2F, (a0), (a1), (a2), (a3)
#define BANKED_SWITCH_5(a0, a1, a2, a3, a4) 0x2F, (a0), (a1), (a2), (a3), (a4)
#define BANKED_SWITCH_6(a0, a1, a2, a3, a4, a5) 0x2F, (a0), (a1), (a2), (a3), (a4), (a5)
#define BANKED_SWITCH_7(a0, a1, a2, a3, a4, a5, a6) 0x2F, (a0), (a1), (a2), (a3), (a4), (a5), (a6)
#define BANKED_SWITCH_8(a0, a1, a2, a3, a4, a5, a6, a7) 0x2F, (a0), (a1), (a2), (a3), (a4), (a5), (a6), (a7)

#endif
