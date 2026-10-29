extern u8 D_03000438;
extern struct { s16 x; s16 y; } D_03001794;
extern struct BgScroll D_03002C24;
extern s32 D_03005040;
extern s32 D_03005044;
extern s32 D_0300504C;
extern s32 sub_0807CD2C(s32, s32);
extern const struct SpriteFrameHeader *const *const gSpriteFrameGroups_Default[];
extern const struct SpriteFrameHeader *const *const gSpriteFrameGroups_083AC208[];
extern const struct SpriteFrameHeader *const *const gSpriteFrameGroups_083AC248[];
extern const struct SpriteFrameHeader *const *const gSpriteFrameGroups_083AC288[];

void sub_08001520(void)
{
    union FrameOrderEntry order[128];
    u32 zero;
    s32 x;
    s32 y;
    s32 i;
    s32 count;
    s32 j;
    s32 oamIndex;
    s32 affine;
    s32 doubleBits;
    s32 affineBits;
    const struct SpriteFrameHeader *const *frames;
    union FrameOrderEntry *entry;
    struct FrameObject *object;
    const struct SpriteFrameHeader *const *const *groups;
    const struct SpriteFramePart *part;
    s32 screenX;
    s32 screenY;
    s32 width;
    s32 height;
    s32 shape;
    u16 f2;
    u32 flags;
    u32 tile;
    s32 depth;
    s32 scale;
    s32 scroll;
    struct OamEntry *oam;

    if (1 & D_03000438)
    {
        D_03000438 = 0;
        return;
    }
    zero = 0;
    CpuFastSet(&zero, order, 0x01000040);
    object = gFrameObjects;
    count = 0;
    for (i = 0; i < 128; i++, object++)
    {
        if (0x8000 & object->flags)
        {
            order[count].bytes.index = i;
            order[count].bytes.priority = object->priority;
            count++;
        }
    }
    if (!(2 & D_03000438))
        sub_08002060(order, count);
    else
        D_03000438 = 0;

    affine = gRenderMode == 2 ? 0x16 : 0;
    oamIndex = 0;
    for (i = 0; i < count; i++)
    {
        object = &gFrameObjects[order[i].bytes.index];
        gFrameAffineOverride = -1;
        switch (0xC0 & object->flags)
        {
        case 0x80:
            screenX = (object->positionX.value >> 8) * 4;
            screenY = ((object->positionY >> 8) + D_03005044) * 4;
            depth = object->positionZ >> 8;
            depth = (depth + 0x3000) / 64;
            screenX = sub_0807CD2C(screenX, depth);
            screenY = sub_0807CD2C(screenY, depth);
            object->screenX = D_03005040 + screenX;
            object->screenY = D_0300504C + screenY;
            scale = sub_0807CD2C(0x8000, depth);
            object->scaleY = scale;
            object->scaleX = scale;
            gFrameAffineOverride = sub_0807CD2C(0x700000, depth);
            break;
        case 0x40:
            object->screenX = (object->positionX.value >> 16) - D_03002C24.x;
            object->screenY = (((object->positionY >> 8) + (object->positionZ >> 8)) >> 8) - D_03002C24.y;
            break;
        case 0xC0:
            break;
        }
        switch (0xF & object->tableSelector)
        {
        case 1:
            groups = gSpriteFrameGroups_083AC208;
            break;
        case 2:
            groups = gSpriteFrameGroups_083AC248;
            break;
        case 3:
            groups = gSpriteFrameGroups_083AC288;
            break;
        case 0:
        default:
            groups = gSpriteFrameGroups_Default;
            break;
        }
        frames = groups[object->frameAndGroup >> 8];
        do {
        part = (const struct SpriteFramePart *)(frames[object->frameAndGroup & 0xFF] + 1);
        scroll = (s16)gBgScrollBase.x;
        screenX = D_03001794.x - scroll + object->screenX;
        scroll = (s16)gBgScrollBase.y;
        screenY = D_03001794.y - scroll + object->screenY;
        } while (0);
        flags = object->flags;
        if ((0xC0 & flags) == 0x40)
        {
            if ((u32)(screenY + 0x20) > 0x100)
            {
                object->flags = 2 | flags;
                continue;
            }
            if ((u32)(screenX + 0x20) > 0x150)
            {
                object->flags = 2 | flags;
                continue;
            }
            object->flags = 0xFFFD & flags;
        }
        if (!(0x4000 & object->flags))
            continue;
        if (0x200 & object->flags)
        {
            if ((0xC0 & object->flags) != 0xC0)
            {
                if (affine < 0x20)
                {
                    if (object->angle != 0)
                        sub_08001CAC(affine, object->angle, object->scaleX, object->scaleY, object->flags);
                    else
                        sub_08001EA8(affine, object->scaleX, object->scaleY, object->flags);
                    doubleBits = (0x20 & object->flags) ? 0x300 : 0x100;
                    affineBits = affine << 9;
                    affine++;
                }
            }
            else
            {
                doubleBits = (0x20 & object->flags) ? 0x300 : 0x100;
                affineBits = object->affineIndex << 9;
            }
        }
        else
        {
            doubleBits = 0;
            affineBits = 0;
        }
        for (j = 0; j < frames[object->frameAndGroup & 0xFF]->count; j++)
        {
            struct OamEntry *shadow = gOamShadow;
            height = 0xC0C0 & part->attributes;
            switch (height)
            {
            case 0x0000:
            case 0x0080:
            case 0x4080:
                width = 4;
                break;
            case 0x0040:
            case 0x4000:
            case 0x8080:
                width = 8;
                break;
            case 0x4040:
            case 0x8000:
            case 0x8040:
            case 0xC080:
                width = 16;
                break;
            case 0xC000:
            case 0xC040:
                width = 32;
                break;
            }
            switch (height)
            {
            case 0x0000:
            case 0x0040:
            case 0x4040:
                height = 4;
                break;
            case 0x0080:
            case 0x4000:
            case 0x8040:
                height = 8;
                break;
            case 0x4080:
            case 0x8000:
            case 0x8080:
            case 0xC040:
                height = 16;
                break;
            case 0xC000:
            case 0xC080:
                height = 32;
                break;
            }
            f2 = object->flags;
            if (0x200 & object->flags)
            {
                if ((0xC0 & f2) != 0xC0)
                {
                    x = part->x + width;
                    y = part->y + height;
                    if (0x20 & object->flags)
                    {
                        width = -width * 2;
                        height = -height * 2;
                    }
                    else
                    {
                        width = -width;
                        height = -height;
                    }
                    if (object->flags & 0x1000)
                        x = -x - x * (object->scaleX - 0x40) / 64;
                    else
                        x = x + x * (object->scaleX - 0x40) / 64;
                    if (object->flags & 0x2000)
                        y = -y - y * (object->scaleY - 0x40) / 64;
                    else
                        y = y + y * (object->scaleY - 0x40) / 64;
                    if (object->flags & 0x100)
                        sub_08001FF8(&x, &y, object);
                    width = width + screenX + x;
                    height = height + screenY + y;
                    shadow[oamIndex].attr0 = (height & 0xFF) | (((const u8 *)part)[0] << 8) | doubleBits
                        | ((0x18 & object->flags) << 7) | ((1 & object->flags) << 12);
                    shadow[oamIndex].attr1 = (width & 0x1FF) | ((0xC0 & ((const u8 *)part)[1]) << 8) | affineBits;
                }
                else
                {
                    if (0x20 & f2)
                    {
                        width = part->x;
                        height = part->y;
                    }
                    else
                    {
                        width = 0;
                        height = 0;
                    }
                    if (0x1000 & f2)
                        width = -part->x - width + screenX - width;
                    else
                        width = width + (part->x + screenX);
                    if (0x2000 & f2)
                        height = -part->y - height + screenY - height;
                    else
                        height = height + (part->y + screenY);
                    shadow[oamIndex].attr0 = (height & 0xFF) | (((const u8 *)part)[0] << 8) | doubleBits
                        | ((0x18 & object->flags) << 7) | ((1 & object->flags) << 12);
                    shadow[oamIndex].attr1 = ((width & 0x1FF) | (((const u8 *)part)[1] << 8) | affineBits)
                        ^ (object->flags & 0x3000);
                }
            }
            else
            {
                if (0x1000 & f2)
                    width = -part->x - width + screenX - width;
                else
                    width = screenX + part->x;
                if (0x2000 & f2)
                    height = -part->y - height + screenY - height;
                else
                    height = screenY + part->y;
                shadow[oamIndex].attr0 = (height & 0xFF) | (((const u8 *)part)[0] << 8) | doubleBits
                    | ((0x18 & object->flags) << 7) | ((1 & object->flags) << 12);
                shadow[oamIndex].attr1 = ((width & 0x1FF) | (((const u8 *)part)[1] << 8))
                    ^ (object->flags & 0x3000);
            }
            f2 = object->flags;
            if (4 & f2)
            {
                tile = part->tileAndPalette;
                if (0xF000 & tile)
                    (&gOamShadow->attr2)[oamIndex * 4] = (0xC00 & f2) | tile;
                else
                    (&gOamShadow->attr2)[oamIndex * 4] = (tile & 0xFFF) | (object->palette << 12) | (0xC00 & f2);
            }
            else
            {
                (&gOamShadow->attr2)[oamIndex * 4] = ((object->palette << 12) + part->tileAndPalette) | (0xC00 & f2);
            }
            oamIndex++;
            part++;
            if (oamIndex > 0x7F)
                goto done;
        }
    }
done:
    for (i = oamIndex; i < 128; i++)
        gOamShadow[i].attr0 = 0x200;
    gState0TypedWork.bytes[0x12E] = 1;
}
