#include "equipment_menu_data.h"

/* Contiguous text banks preserve fixed-width copies across label boundaries. */
#define LABEL_END 0xFE

const u8 gEquipmentMenuAlignment[1] __attribute__((aligned(1))) = {
    0x00,
};

const u8 gEquipmentMenuText_083C47C4[40] __attribute__((aligned(1))) = {
    /* 0: Medaparts */
    0x0D, 0x1F, 0x1E, 0x1B, 0x2A, 0x1B, 0x2C, 0x2E, 0x2D, LABEL_END,
    /* 1: MF */
    0x0D, 0x06, LABEL_END,
    /* 2: Status */
    0x13, 0x2E, 0x1B, 0x2E, 0x2F, 0x2D, LABEL_END,
    /* 3: Aim */
    0x01, 0x23, 0x27, LABEL_END,
    /* 4: Rotation */
    0x12, 0x29, 0x2E, 0x1B, 0x2E, 0x23, 0x29, 0x28, LABEL_END,
    /* 5: Auto */
    0x01, 0x2F, 0x2E, 0x29, LABEL_END, 0x00, 0x00,
};

const u8 *const gUnknown_083C47EC[6] = {
    &gEquipmentMenuText_083C47C4[0],
    &gEquipmentMenuText_083C47C4[10],
    &gEquipmentMenuText_083C47C4[13],
    &gEquipmentMenuText_083C47C4[20],
    &gEquipmentMenuText_083C47C4[24],
    &gEquipmentMenuText_083C47C4[33],
};

const u8 gEquipmentMenuText_083C4804[908] __attribute__((aligned(1))) = {
    /* 0: Damaged */
    0x04, 0x1B, 0x27, 0x1B, 0x21, 0x1F, 0x1E, LABEL_END,
    /* 1: Unusable */
    0x15, 0x28, 0x2F, 0x2D, 0x1B, 0x1C, 0x26, 0x1F, LABEL_END,
    /* 2: Used Up */
    0x15, 0x2D, 0x1F, 0x1E, 0x00, 0x15, 0x2A, LABEL_END,
    /* 3: Charge MF */
    0x03, 0x22, 0x1B, 0x2C, 0x21, 0x1F, 0x00, 0x0D, 0x06, LABEL_END,
    /* 4: MF low */
    0x0D, 0x06, 0x00, 0x26, 0x29, 0x31, LABEL_END,
    /* 5: Unmastered */
    0x15, 0x28, 0x27, 0x1B, 0x2D, 0x2E, 0x1F, 0x2C, 0x1F, 0x1E, LABEL_END,
    /* 6: Data[35][3B] */
    0x04, 0x1B, 0x2E, 0x1B, 0x35, 0x3B, LABEL_END,
    /* 7: Data[35][3C] */
    0x04, 0x1B, 0x2E, 0x1B, 0x35, 0x3C, LABEL_END,
    /* 8: Data[35][3D] */
    0x04, 0x1B, 0x2E, 0x1B, 0x35, 0x3D, LABEL_END,
    /* 9: Data[35][3E] */
    0x04, 0x1B, 0x2E, 0x1B, 0x35, 0x3E, LABEL_END,
    /* 10: Data[35]A */
    0x04, 0x1B, 0x2E, 0x1B, 0x35, 0x01, LABEL_END,
    /* 11: Data[35]B */
    0x04, 0x1B, 0x2E, 0x1B, 0x35, 0x02, LABEL_END,
    /* 12: Data[35]C */
    0x04, 0x1B, 0x2E, 0x1B, 0x35, 0x03, LABEL_END,
    /* 13: Data[35]D */
    0x04, 0x1B, 0x2E, 0x1B, 0x35, 0x04, LABEL_END,
    /* 14: Data[35]E */
    0x04, 0x1B, 0x2E, 0x1B, 0x35, 0x05, LABEL_END,
    /* 15: Data[35]F */
    0x04, 0x1B, 0x2E, 0x1B, 0x35, 0x06, LABEL_END,
    /* 16: Data[36][35] */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x35, LABEL_END,
    /* 17: Data[36][36] */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x36, LABEL_END,
    /* 18: Data[36][37] */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x37, LABEL_END,
    /* 19: Data[36][38] */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x38, LABEL_END,
    /* 20: Data[36][39] */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x39, LABEL_END,
    /* 21: Data[36][3A] */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x3A, LABEL_END,
    /* 22: Data[36][3B] */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x3B, LABEL_END,
    /* 23: Data[36][3C] */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x3C, LABEL_END,
    /* 24: Data[36][3D] */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x3D, LABEL_END,
    /* 25: Data[36][3E] */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x3E, LABEL_END,
    /* 26: Data[36]A */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x01, LABEL_END,
    /* 27: Data[36]B */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x02, LABEL_END,
    /* 28: Data[36]C */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x03, LABEL_END,
    /* 29: Data[36]D */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x04, LABEL_END,
    /* 30: Data[36]E */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x05, LABEL_END,
    /* 31: Data[36]F */
    0x04, 0x1B, 0x2E, 0x1B, 0x36, 0x06, LABEL_END,
    /* 32: Data[37][35] */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x35, LABEL_END,
    /* 33: Data[37][36] */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x36, LABEL_END,
    /* 34: Data[37][37] */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x37, LABEL_END,
    /* 35: Data[37][38] */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x38, LABEL_END,
    /* 36: Data[37][39] */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x39, LABEL_END,
    /* 37: Data[37][3A] */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x3A, LABEL_END,
    /* 38: Data[37][3B] */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x3B, LABEL_END,
    /* 39: Data[37][3C] */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x3C, LABEL_END,
    /* 40: Data[37][3D] */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x3D, LABEL_END,
    /* 41: Data[37][3E] */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x3E, LABEL_END,
    /* 42: Data[37]A */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x01, LABEL_END,
    /* 43: Data[37]B */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x02, LABEL_END,
    /* 44: Data[37]C */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x03, LABEL_END,
    /* 45: Data[37]D */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x04, LABEL_END,
    /* 46: Data[37]E */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x05, LABEL_END,
    /* 47: Data[37]F */
    0x04, 0x1B, 0x2E, 0x1B, 0x37, 0x06, LABEL_END,
    /* 48: Data[38][35] */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x35, LABEL_END,
    /* 49: Data[38][36] */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x36, LABEL_END,
    /* 50: Data[38][37] */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x37, LABEL_END,
    /* 51: Data[38][38] */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x38, LABEL_END,
    /* 52: Data[38][39] */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x39, LABEL_END,
    /* 53: Data[38][3A] */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x3A, LABEL_END,
    /* 54: Data[38][3B] */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x3B, LABEL_END,
    /* 55: Data[38][3C] */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x3C, LABEL_END,
    /* 56: Data[38][3D] */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x3D, LABEL_END,
    /* 57: Data[38][3E] */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x3E, LABEL_END,
    /* 58: Data[38]A */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x01, LABEL_END,
    /* 59: Data[38]B */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x02, LABEL_END,
    /* 60: Data[38]C */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x03, LABEL_END,
    /* 61: Data[38]D */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x04, LABEL_END,
    /* 62: Data[38]E */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x05, LABEL_END,
    /* 63: Data[38]F */
    0x04, 0x1B, 0x2E, 0x1B, 0x38, 0x06, LABEL_END,
    /* 64: Data[39][35] */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x35, LABEL_END,
    /* 65: Data[39][36] */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x36, LABEL_END,
    /* 66: Data[39][37] */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x37, LABEL_END,
    /* 67: Data[39][38] */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x38, LABEL_END,
    /* 68: Data[39][39] */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x39, LABEL_END,
    /* 69: Data[39][3A] */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x3A, LABEL_END,
    /* 70: Data[39][3B] */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x3B, LABEL_END,
    /* 71: Data[39][3C] */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x3C, LABEL_END,
    /* 72: Data[39][3D] */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x3D, LABEL_END,
    /* 73: Data[39][3E] */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x3E, LABEL_END,
    /* 74: Data[39]A */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x01, LABEL_END,
    /* 75: Data[39]B */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x02, LABEL_END,
    /* 76: Data[39]C */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x03, LABEL_END,
    /* 77: Data[39]D */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x04, LABEL_END,
    /* 78: Data[39]E */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x05, LABEL_END,
    /* 79: Data[39]F */
    0x04, 0x1B, 0x2E, 0x1B, 0x39, 0x06, LABEL_END,
    /* 80: Data[3A][35] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x35, LABEL_END,
    /* 81: Data[3A][36] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x36, LABEL_END,
    /* 82: Data[3A][37] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x37, LABEL_END,
    /* 83: Data[3A][38] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x38, LABEL_END,
    /* 84: Data[3A][39] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x39, LABEL_END,
    /* 85: Data[3A][3A] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x3A, LABEL_END,
    /* 86: Data[3A][3B] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x3B, LABEL_END,
    /* 87: Data[3A][3C] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x3C, LABEL_END,
    /* 88: Data[3A][3D] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x3D, LABEL_END,
    /* 89: Data[3A][3E] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x3E, LABEL_END,
    /* 90: Data[3A]A */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x01, LABEL_END,
    /* 91: Data[3A]B */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x02, LABEL_END,
    /* 92: Data[3A]C */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x03, LABEL_END,
    /* 93: Data[3A]D */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x04, LABEL_END,
    /* 94: Data[3A]E */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x05, LABEL_END,
    /* 95: Data[3A]F */
    0x04, 0x1B, 0x2E, 0x1B, 0x3A, 0x06, LABEL_END,
    /* 96: Data[3B][35] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x35, LABEL_END,
    /* 97: Data[3B][36] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x36, LABEL_END,
    /* 98: Data[3B][37] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x37, LABEL_END,
    /* 99: Data[3B][38] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x38, LABEL_END,
    /* 100: Data[3B][39] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x39, LABEL_END,
    /* 101: Data[3B][3A] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x3A, LABEL_END,
    /* 102: Data[3B][3B] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x3B, LABEL_END,
    /* 103: Data[3B][3C] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x3C, LABEL_END,
    /* 104: Data[3B][3D] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x3D, LABEL_END,
    /* 105: Data[3B][3E] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x3E, LABEL_END,
    /* 106: Data[3B]A */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x01, LABEL_END,
    /* 107: Data[3B]B */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x02, LABEL_END,
    /* 108: Data[3B]C */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x03, LABEL_END,
    /* 109: Data[3B]D */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x04, LABEL_END,
    /* 110: Data[3B]E */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x05, LABEL_END,
    /* 111: Data[3B]F */
    0x04, 0x1B, 0x2E, 0x1B, 0x3B, 0x06, LABEL_END,
    /* 112: Data[3C][35] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x35, LABEL_END,
    /* 113: Data[3C][36] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x36, LABEL_END,
    /* 114: Data[3C][37] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x37, LABEL_END,
    /* 115: Data[3C][38] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x38, LABEL_END,
    /* 116: Data[3C][39] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x39, LABEL_END,
    /* 117: Data[3C][3A] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x3A, LABEL_END,
    /* 118: Data[3C][3B] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x3B, LABEL_END,
    /* 119: Data[3C][3C] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x3C, LABEL_END,
    /* 120: Data[3C][3D] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x3D, LABEL_END,
    /* 121: Data[3C][3E] */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x3E, LABEL_END,
    /* 122: Data[3C]A */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x01, LABEL_END,
    /* 123: Data[3C]B */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x02, LABEL_END,
    /* 124: Data[3C]C */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x03, LABEL_END,
    /* 125: Data[3C]D */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x04, LABEL_END,
    /* 126: Data[3C]E */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x05, LABEL_END,
    /* 127: Data[3C]F */
    0x04, 0x1B, 0x2E, 0x1B, 0x3C, 0x06, LABEL_END, 0x00,
};

const u8 *const gUnknown_083C4B90[128] = {
    &gEquipmentMenuText_083C4804[0],
    &gEquipmentMenuText_083C4804[8],
    &gEquipmentMenuText_083C4804[17],
    &gEquipmentMenuText_083C4804[25],
    &gEquipmentMenuText_083C4804[35],
    &gEquipmentMenuText_083C4804[42],
    &gEquipmentMenuText_083C4804[53],
    &gEquipmentMenuText_083C4804[60],
    &gEquipmentMenuText_083C4804[67],
    &gEquipmentMenuText_083C4804[74],
    &gEquipmentMenuText_083C4804[81],
    &gEquipmentMenuText_083C4804[88],
    &gEquipmentMenuText_083C4804[95],
    &gEquipmentMenuText_083C4804[102],
    &gEquipmentMenuText_083C4804[109],
    &gEquipmentMenuText_083C4804[116],
    &gEquipmentMenuText_083C4804[123],
    &gEquipmentMenuText_083C4804[130],
    &gEquipmentMenuText_083C4804[137],
    &gEquipmentMenuText_083C4804[144],
    &gEquipmentMenuText_083C4804[151],
    &gEquipmentMenuText_083C4804[158],
    &gEquipmentMenuText_083C4804[165],
    &gEquipmentMenuText_083C4804[172],
    &gEquipmentMenuText_083C4804[179],
    &gEquipmentMenuText_083C4804[186],
    &gEquipmentMenuText_083C4804[193],
    &gEquipmentMenuText_083C4804[200],
    &gEquipmentMenuText_083C4804[207],
    &gEquipmentMenuText_083C4804[214],
    &gEquipmentMenuText_083C4804[221],
    &gEquipmentMenuText_083C4804[228],
    &gEquipmentMenuText_083C4804[235],
    &gEquipmentMenuText_083C4804[242],
    &gEquipmentMenuText_083C4804[249],
    &gEquipmentMenuText_083C4804[256],
    &gEquipmentMenuText_083C4804[263],
    &gEquipmentMenuText_083C4804[270],
    &gEquipmentMenuText_083C4804[277],
    &gEquipmentMenuText_083C4804[284],
    &gEquipmentMenuText_083C4804[291],
    &gEquipmentMenuText_083C4804[298],
    &gEquipmentMenuText_083C4804[305],
    &gEquipmentMenuText_083C4804[312],
    &gEquipmentMenuText_083C4804[319],
    &gEquipmentMenuText_083C4804[326],
    &gEquipmentMenuText_083C4804[333],
    &gEquipmentMenuText_083C4804[340],
    &gEquipmentMenuText_083C4804[347],
    &gEquipmentMenuText_083C4804[354],
    &gEquipmentMenuText_083C4804[361],
    &gEquipmentMenuText_083C4804[368],
    &gEquipmentMenuText_083C4804[375],
    &gEquipmentMenuText_083C4804[382],
    &gEquipmentMenuText_083C4804[389],
    &gEquipmentMenuText_083C4804[396],
    &gEquipmentMenuText_083C4804[403],
    &gEquipmentMenuText_083C4804[410],
    &gEquipmentMenuText_083C4804[417],
    &gEquipmentMenuText_083C4804[424],
    &gEquipmentMenuText_083C4804[431],
    &gEquipmentMenuText_083C4804[438],
    &gEquipmentMenuText_083C4804[445],
    &gEquipmentMenuText_083C4804[452],
    &gEquipmentMenuText_083C4804[459],
    &gEquipmentMenuText_083C4804[466],
    &gEquipmentMenuText_083C4804[473],
    &gEquipmentMenuText_083C4804[480],
    &gEquipmentMenuText_083C4804[487],
    &gEquipmentMenuText_083C4804[494],
    &gEquipmentMenuText_083C4804[501],
    &gEquipmentMenuText_083C4804[508],
    &gEquipmentMenuText_083C4804[515],
    &gEquipmentMenuText_083C4804[522],
    &gEquipmentMenuText_083C4804[529],
    &gEquipmentMenuText_083C4804[536],
    &gEquipmentMenuText_083C4804[543],
    &gEquipmentMenuText_083C4804[550],
    &gEquipmentMenuText_083C4804[557],
    &gEquipmentMenuText_083C4804[564],
    &gEquipmentMenuText_083C4804[571],
    &gEquipmentMenuText_083C4804[578],
    &gEquipmentMenuText_083C4804[585],
    &gEquipmentMenuText_083C4804[592],
    &gEquipmentMenuText_083C4804[599],
    &gEquipmentMenuText_083C4804[606],
    &gEquipmentMenuText_083C4804[613],
    &gEquipmentMenuText_083C4804[620],
    &gEquipmentMenuText_083C4804[627],
    &gEquipmentMenuText_083C4804[634],
    &gEquipmentMenuText_083C4804[641],
    &gEquipmentMenuText_083C4804[648],
    &gEquipmentMenuText_083C4804[655],
    &gEquipmentMenuText_083C4804[662],
    &gEquipmentMenuText_083C4804[669],
    &gEquipmentMenuText_083C4804[676],
    &gEquipmentMenuText_083C4804[683],
    &gEquipmentMenuText_083C4804[690],
    &gEquipmentMenuText_083C4804[697],
    &gEquipmentMenuText_083C4804[704],
    &gEquipmentMenuText_083C4804[711],
    &gEquipmentMenuText_083C4804[718],
    &gEquipmentMenuText_083C4804[725],
    &gEquipmentMenuText_083C4804[732],
    &gEquipmentMenuText_083C4804[739],
    &gEquipmentMenuText_083C4804[746],
    &gEquipmentMenuText_083C4804[753],
    &gEquipmentMenuText_083C4804[760],
    &gEquipmentMenuText_083C4804[767],
    &gEquipmentMenuText_083C4804[774],
    &gEquipmentMenuText_083C4804[781],
    &gEquipmentMenuText_083C4804[788],
    &gEquipmentMenuText_083C4804[795],
    &gEquipmentMenuText_083C4804[802],
    &gEquipmentMenuText_083C4804[809],
    &gEquipmentMenuText_083C4804[816],
    &gEquipmentMenuText_083C4804[823],
    &gEquipmentMenuText_083C4804[830],
    &gEquipmentMenuText_083C4804[837],
    &gEquipmentMenuText_083C4804[844],
    &gEquipmentMenuText_083C4804[851],
    &gEquipmentMenuText_083C4804[858],
    &gEquipmentMenuText_083C4804[865],
    &gEquipmentMenuText_083C4804[872],
    &gEquipmentMenuText_083C4804[879],
    &gEquipmentMenuText_083C4804[886],
    &gEquipmentMenuText_083C4804[893],
    &gEquipmentMenuText_083C4804[900],
};

const u8 gEquipmentColumnLookup[7][11] = {
    { 6, 0, 12, 12, 12, 12, 12, 12, 14, 18, 0 },
    { 10, 6, 10, 6, 10, 6, 10, 6, 10, 6, 0 },
    { 12, 12, 6, 0, 12, 12, 14, 18, 12, 12, 0 },
    { 14, 18, 10, 6, 6, 0, 10, 6, 14, 18, 0 },
    { 10, 6, 14, 18, 14, 18, 6, 0, 14, 18, 0 },
    { 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0 },
    { 14, 18, 12, 12, 12, 12, 12, 12, 6, 0, 0 },
};

const u8 gEquipmentColumnPadding[3] __attribute__((aligned(1))) = {
    0x00, 0x00, 0x00,
};

const struct EquipmentPlacement gEquipmentPlacements[17] = {
    { -8, 244, 1, 0 }, /* 083C4DE0 */
    { 0, 0, 0, 1 }, /* 083C4DE4 */
    { 0, 0, 1, 1 }, /* 083C4DE8 */
    { -8, 244, 1, 0 }, /* 083C4DEC */
    { -8, 4, 1, 1 }, /* 083C4DF0 */
    { -8, 4, 1, 1 }, /* 083C4DF4 */
    { 8, 4, 0, 0 }, /* 083C4DF8 */
    { 8, 4, 1, 0 }, /* 083C4DFC */
    { 8, 4, 0, 0 }, /* 083C4E00 */
    { 8, 4, 1, 0 }, /* 083C4E04 */
    { 8, 244, 1, 1 }, /* 083C4E08 */
    { 8, 244, 0, 0 }, /* 083C4E0C */
    { -8, 244, 0, 0 }, /* 083C4E10 */
    { -8, 244, 1, 0 }, /* 083C4E14 */
    { -8, 244, 1, 0 }, /* 083C4E18 */
    { -8, 244, 1, 0 }, /* 083C4E1C */
    { 8, 4, 1, 1 }, /* 083C4E20 */
};
