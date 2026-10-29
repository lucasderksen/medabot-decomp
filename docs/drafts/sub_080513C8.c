struct SelectionWork13C8
{
    u8 unknown000[0x5DC];
    struct SelectionRecord records[0x44];   /* 5DC */
    u8 unknown7FC[2];
    u8 byte7FE;                             /* 7FE */
    u8 byte7FF;                             /* 7FF */
    u16 width;                              /* 800 */
    u8 unknown802[0xE];
    u8 map[0x438];                          /* 810 */
    u16 halfC48;                            /* C48 */
    u16 halfC4A;                            /* C4A */
    u8 unknownC4C[0x42];
    u16 halfC8E;                            /* C8E */
    u8 unknownC90[0x24];
    s8 byteCB4;                             /* CB4 */
    u8 unknownCB5[5];
    u8 byteCBA;                             /* CBA */
};
struct ObjectAttributes13C8
{
    u16 attributes;
    u16 unknown02;
};
extern struct SelectionWork13C8 gSelectionWork13C8 asm("gContinuedWork_030057E0");
extern struct ObjectAttributes13C8 gObjectAttributes13C8[] asm("gLaterBuffer_030055A0");
extern const struct SelectionRecord *const D_08483234[] asm("gMapObjectLists_08483234");

void sub_080513C8(u32 value)
{
    s32 slot;
    struct SelectionRecord saved[64];
    s32 k;
    s32 row;
    s32 count;
    s32 found;
    struct SelectionRecord *records;
    s32 skip;
    const struct SelectionRecord *entry;
    s32 hi;
    s32 objIndex;
    s32 shadowIndex;
    s32 i;

    records = gSelectionRecords_03005DBC;
    sub_08049714(saved, 0x200);
    sub_080497C0(records, saved, 0x200);
    sub_08049714(records, 0x200);
    count = 0;
    slot = 0;
    k = 0;
    for (row = 0; row < 32; row++)
    {
        entry = D_08483234[gSelectionWork13C8.byte7FE];
        while (entry->x != 0xFF)
        {
            if (((entry->unknown06 >> gSelectionWork13C8.byte7FF) & 1) && entry->frame == row
                && sub_080531E0(0xFFF & entry->attributes) == 0)
            {
                skip = 0;
                found = 0;
                if (value == 0)
                {
                    hi = entry->flags.value >> 4;
                }
                else
                {
                if ((s32)value >= 0 && (s32)value <= 2)
                {
                        for (k = 0; k <= 0x3F; k++)
                        {
                            if ((0xFFF & entry->attributes) == (0xFFF & saved[k].attributes))
                                found = 1;
                            if (found != 0)
                                break;
                        }
                    if (k != 0x40)
                    {
                        if (value == 1)
                            goto store;
                        if (value == 2 && saved[k].flags.bits.active != 1)
                            goto next;
                    }
                    else if (value == 2)
                    {
                        skip = 1;
                    }
                }
                if (skip != 0)
                    goto next;
            store:
                hi = entry->flags.value >> 4;
                }
                gSelectionWork13C8.records[slot].x = entry->x;
                gSelectionWork13C8.records[slot].y = entry->y;
                gSelectionWork13C8.records[slot].attributes = entry->attributes;
                switch (entry->attributes >> 12)
                {
                case 0:
                case 4:
                case 6:
                    gSelectionWork13C8.map[entry->y * (gSelectionWork13C8.width >> 1) + entry->x] = 7;
                    break;
                }
                gSelectionWork13C8.records[slot].flags.bits.active = 1;
                if (entry->flags.value != 0xFF)
                {
                    if (count <= 0x1D)
                    {
                        switch (entry->attributes >> 12)
                        {
                        default:
                            objIndex = count + 0x31;
                            shadowIndex = count + 0x5B;
                            break;
                        case 0:
                        case 2:
                        case 4:
                        case 6:
                            objIndex = count + 0x31;
                            sub_08048864((u8)objIndex, 0xC804, hi * 12, hi, 1);
                            gSelectionWork13C8.records[slot].flags.bits.auxiliary = 1;
                            gFrameObjects[objIndex].value30 = sub_08048684(hi);
                            sub_080487C8((u8)objIndex);
                            shadowIndex = count + 0x5B;
                            if (gObjectAuxiliaryLookup_083D2D0D[(u16)gFrameObjects[objIndex].value30] != 0)
                                sub_08048864((u8)shadowIndex, 0xCC0C, 0x90, 0xE, 1);
                            do {
                            break;
                            } while (0);
                        }
                        gSelectionWork13C8.records[slot].flags.bits.index = count;
                        hi = entry->flags.value >> 4;
                        gObjectAttributes13C8[objIndex].attributes = entry->attributes & 0xFFF;
                        gFrameObjects[objIndex].byte2B = hi;
                        gFrameObjects[objIndex].positionX.value = (gFrameObjects[objIndex].positionX.value & 0xFF) | ((entry->x * 16 + gSelectionWork13C8.halfC48) << 8);
                        gFrameObjects[objIndex].positionY = (gFrameObjects[objIndex].positionY & 0xFF) | ((entry->y * 16 + gSelectionWork13C8.halfC4A) << 8);
                        sub_0805218C((u8)objIndex, 0xF & entry->flags.value, &gSelectionRecords_03005DBC[slot]);
                        sub_08049420((u8)objIndex, (u8)(hi * 4 + (0xF & entry->flags.value)));
                        if (value != 0 && found != 0)
                        {
                            do {
                            sub_0805218C((u8)objIndex, saved[k].frame, &gSelectionRecords_03005DBC[slot]);
                            } while (0);
                            sub_08049420((u8)objIndex, (u8)(saved[k].frame + hi * 4));
                        }
                        gFrameObjects[objIndex].unknown2C[0] = 0;
                        gFrameObjects[shadowIndex].positionX.value = (gFrameObjects[shadowIndex].positionX.value & 0xFF) | ((gFrameObjects[objIndex].positionX.value >> 8) << 8);
                        gFrameObjects[shadowIndex].positionY = (gFrameObjects[shadowIndex].positionY & 0xFF) | (((gFrameObjects[objIndex].positionY >> 8) - 5) << 8);
                        gFrameObjects[shadowIndex].screenX = gFrameObjects[objIndex].screenX;
                        gFrameObjects[shadowIndex].screenY = gFrameObjects[objIndex].screenY - 5;
                    }
                    count++;
                }
            next:
                slot++;
            }
            entry++;
        }
    }
    if (gSelectionWork13C8.halfC8E != 0)
    {
        for (i = 0; i <= 0x3F; i++)
        {
            if ((0xFFF & records->attributes) == gSelectionWork13C8.halfC8E)
            {
                gSelectionWork13C8.byteCB4 = i;
                break;
            }
            records++;
        }
    }
    gSelectionWork13C8.byteCBA = 2;
}
