extern const u8 D_083D2B36[][4];
extern u8 gFreshWork_03006D38[];
extern u8 gContinuedWork_030057E0[];

u32 sub_0804842C(u32 first, u32 second)
{
    /* Falls off the end like the reference (r0 keeps first or the last call result); no caller uses it: sub_0804A6A0, sub_0804A6F8, sub_0804A764, sub_0804A944, sub_0804AA74, sub_0804AB60, sub_0804ABCC, sub_0804ACD4, sub_0804AE80, sub_0804C960, sub_0804C984, sub_0804C9A0, sub_0804C9C4, sub_08050CCC, sub_0805424C */
    u32 value;

    switch (first) {
    case 0:
    case 10:
    case 12:
        if (gContinuedWork_030057E0[0xC30] == 0xFF)
            break;
        value = sub_080483F8();
        if (gContinuedWork_030057E0[0xC30] == value)
            break;
        gContinuedWork_030057E0[0xC30] = value;
        sub_08047BB4(value);
        break;
    case 1:
        gContinuedWork_030057E0[0xC30] = second;
        sub_08047BB4(second);
        break;
    case 2:
        gContinuedWork_030057E0[0xC30] = 0;
        sub_08047BB4(0);
        break;
    case 3: {
        u8 old = gContinuedWork_030057E0[0xC30];
        if (old != 0xFF) {
            if (!(0x80 & second)) {
                gContinuedWork_030057E0[0xC31] = second & 0x7F;
                sub_08047BB4(second);
                gContinuedWork_030057E0[0xC30] = 0xFF;
                break;
            }
        } else if (!(0x80 & second))
            break;
        gContinuedWork_030057E0[0xC31] = second & 0x7F;
        gContinuedWork_030057E0[0xC30] = 0xFF | old;
        break;
    }
    case 4: {
        u8 old = gContinuedWork_030057E0[0xC30];
        gContinuedWork_030057E0[0xC30] = 0;
        value = sub_080483F8();
        if (old != value) {
            gContinuedWork_030057E0[0xC30] = value;
            sub_08047BB4(value);
        } else
            gContinuedWork_030057E0[0xC30] = value;
        break;
    }
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 19:
    case 28:
        value = sub_080483F8();
        gContinuedWork_030057E0[0xC30] = value;
        sub_08047BB4(value);
        break;
    case 11:
    case 13:
    case 14:
    case 15:
    case 21:
    case 22:
    case 26:
        if (gContinuedWork_030057E0[0xC30] != 0xFF) {
            value = sub_080483F8();
            gContinuedWork_030057E0[0xC30] = value;
            sub_08047BB4(value);
        } else
            sub_08047BB4(gContinuedWork_030057E0[0xC31]);
        break;
    case 23:
        if (D_083D2B36[gFreshWork_03006D38[1]][0] != 0)
            sub_08047BC0(0x1E);
        break;
    case 24:
        if (D_083D2B36[gFreshWork_03006D38[1]][0] != 0) {
            gContinuedWork_030057E0[0xC30] = D_083D2B36[gFreshWork_03006D38[1]][1];
            sub_08047BB4(D_083D2B36[gFreshWork_03006D38[1]][1]);
        }
        break;
    case 25:
        switch (D_083D2B36[gFreshWork_03006D38[1]][2]) {
        case 1:
            gContinuedWork_030057E0[0xC30] = D_083D2B36[gFreshWork_03006D38[1]][3];
            sub_08047BB4(D_083D2B36[gFreshWork_03006D38[1]][3]);
            break;
        case 2:
            value = sub_080483F8();
            gContinuedWork_030057E0[0xC30] = value;
            sub_08047BB4(value);
            break;
        }
        break;
    }
}
