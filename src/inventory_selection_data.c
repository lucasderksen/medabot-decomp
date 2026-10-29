#include "inventory_selection_data.h"

typedef char SelectionRecordSize[(sizeof(struct InventorySelectionRecord) == 6) ? 1 : -1];
typedef char CursorPointSize[(sizeof(struct InventoryCursorPoint) == 2) ? 1 : -1];
typedef char CursorHeaderSize[(sizeof(struct InventoryCursorHeader) == 2) ? 1 : -1];

const struct InventorySelectionRecord gInventorySelectionRecords[52] = {
    { 0, 1, 80, 0, 20, 1 },
    { 1, 0, 60, 0, 30, 0 },
    { 2, 3, 80, 0, 10, 1 },
    { 3, 2, 60, 0, 10, 1 },
    { 4, 2, 40, 0, 0, 3 },
    { 5, 3, 70, 0, 0, 3 },
    { 6, 2, 40, 0, 0, 3 },
    { 7, 3, 70, 0, 0, 3 },
    { 8, 2, 40, 0, 0, 3 },
    { 9, 3, 70, 0, 0, 3 },
    { 10, 4, 60, 30, 30, 0 },
    { 11, 4, 30, 0, 0, 3 },
    { 12, 0, 50, 16, 40, 0 },
    { 13, 1, 60, 0, 0, 2 },
    { 14, 0, 50, 8, 8, 0 },
    { 15, 1, 60, 0, 0, 2 },
    { 16, 0, 50, 16, 10, 0 },
    { 17, 1, 60, 0, 0, 2 },
    { 18, 0, 50, 16, 8, 0 },
    { 19, 1, 60, 0, 0, 2 },
    { 20, 5, 70, 0, 60, 1 },
    { 21, 5, 40, 0, 0, 2 },
    { 22, 7, 40, 0, 2, 2 },
    { 23, 7, 50, 0, 0, 0 },
    { 24, 4, 40, 0, 10, 3 },
    { 25, 4, 40, 0, 10, 3 },
    { 26, 5, 60, 0, 60, 2 },
    { 27, 5, 80, 0, 0, 1 },
    { 28, 5, 70, 0, 40, 2 },
    { 29, 5, 50, 0, 20, 1 },
    { 30, 2, 50, 16, 10, 0 },
    { 31, 3, 40, 0, 30, 2 },
    { 32, 2, 50, 16, 10, 0 },
    { 33, 3, 40, 0, 30, 2 },
    { 34, 6, 30, 0, 30, 2 },
    { 35, 6, 40, 0, 30, 2 },
    { 36, 6, 30, 0, 30, 2 },
    { 37, 6, 40, 0, 30, 2 },
    { 38, 6, 40, 16, 10, 2 },
    { 39, 6, 60, 0, 2, 0 },
    { 40, 7, 50, 16, 10, 0 },
    { 41, 7, 50, 16, 10, 0 },
    { 42, 1, 70, 0, 1, 0 },
    { 43, 3, 70, 0, 0, 1 },
    { 44, 7, 60, 0, 0, 0 },
    { 45, 7, 50, 0, 0, 2 },
    { 46, 4, 40, 0, 20, 3 },
    { 47, 4, 70, 0, 0, 0 },
    { 48, 4, 50, 0, 0, 3 },
    { 49, 4, 70, 0, 0, 3 },
    { 50, 7, 60, 0, 10, 1 },
    { 51, 7, 70, 0, 80, 1 },
};

const u8 gInventorySelectionLists[30][3] = {
    { 0, 1, 35 },
    { 2, 3, 11 },
    { 4, 5, 21 },
    { 6, 7, 37 },
    { 8, 9, 47 },
    { 10, 11, 1 },
    { 12, 13, 29 },
    { 14, 15, 31 },
    { 16, 17, 39 },
    { 18, 19, 49 },
    { 20, 21, 41 },
    { 22, 23, 27 },
    { 24, 25, 15 },
    { 26, 27, 9 },
    { 28, 29, 7 },
    { 30, 31, 51 },
    { 32, 33, 45 },
    { 34, 35, 43 },
    { 36, 37, 3 },
    { 38, 39, 17 },
    { 40, 41, 19 },
    { 42, 43, 23 },
    { 44, 45, 25 },
    { 46, 47, 5 },
    { 48, 49, 33 },
    { 50, 51, 13 },
    { 26, 10, 50 },
    { 28, 42, 48 },
    { 0, 44, 14 },
    { 2, 40, 20 },
};

const u8 gInventorySelectionPadding[2] __attribute__((aligned(1))) = { 0, 0 };

const struct { struct InventoryCursorHeader header; struct InventoryCursorPoint points[5]; } gInventoryCursor_083B7FE8 __attribute__((aligned(1))) = {
    { 5, 0 }, {
        { 2, 7 },
        { 2, 10 },
        { 10, 7 },
        { 10, 10 },
        { 20, 7 },
    }
};

const struct { struct InventoryCursorHeader header; struct InventoryCursorPoint points[6]; } gInventoryCursor_083B7FF4 __attribute__((aligned(1))) = {
    { 6, 0 }, {
        { 12, 6 },
        { 12, 8 },
        { 12, 10 },
        { 15, 7 },
        { 15, 10 },
        { 19, 7 },
    }
};

const struct { struct InventoryCursorHeader header; struct InventoryCursorPoint points[2]; } gInventoryCursor_083B8002 __attribute__((aligned(1))) = {
    { 2, 0 }, {
        { 5, 6 },
        { 5, 9 },
    }
};

const struct { struct InventoryCursorHeader header; struct InventoryCursorPoint points[7]; } gInventoryCursor_083B8008 __attribute__((aligned(1))) = {
    { 7, 0 }, {
        { 2, 9 },
        { 2, 11 },
        { 11, 9 },
        { 14, 6 },
        { 14, 7 },
        { 14, 8 },
        { 14, 9 },
    }
};

const struct { struct InventoryCursorHeader header; struct InventoryCursorPoint points[8]; } gInventoryCursor_083B8018 __attribute__((aligned(1))) = {
    { 8, 0 }, {
        { 2, 9 },
        { 2, 11 },
        { 11, 9 },
        { 14, 6 },
        { 14, 7 },
        { 14, 8 },
        { 14, 9 },
        { 14, 10 },
    }
};

const struct { struct InventoryCursorHeader header; struct InventoryCursorPoint points[8]; } gInventoryCursor_083B802A __attribute__((aligned(1))) = {
    { 8, 0 }, {
        { 2, 11 },
        { 11, 9 },
        { 14, 6 },
        { 14, 7 },
        { 14, 8 },
        { 14, 9 },
        { 14, 10 },
        { 14, 11 },
    }
};

const u8 *const gUnknownPointers_083B803C[6] = {
    (const u8 *)&gInventoryCursor_083B7FE8,
    (const u8 *)&gInventoryCursor_083B7FF4,
    (const u8 *)&gInventoryCursor_083B8002,
    (const u8 *)&gInventoryCursor_083B8008,
    (const u8 *)&gInventoryCursor_083B8018,
    (const u8 *)&gInventoryCursor_083B802A,
};
