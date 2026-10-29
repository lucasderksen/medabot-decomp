#include "frame.h"
#include "graphics.h"

void sub_08001FF8(s32 *x, s32 *y, const struct FrameObject *object)
{
    s32 cosine = gSineTable[(object->angle & 0x3FF) + 0x100];
    s32 sine = gSineTable[object->angle & 0x3FF];
    s32 oldX = *x;
    s32 oldY = *y;

    *x = (oldX * cosine - oldY * sine) / 0x4000;
    *y = (oldX * sine + oldY * cosine) / 0x4000;
}

void sub_08002060(union FrameOrderEntry *entries, u16 count)
{
    u16 gap = count;
    if (count > 1)
    {
        s32 swapped;
    nextGap:
        {
            u16 i;
            gap = gap * 5 / 8;
            if (gap == 0)
                gap = 1;
            swapped = 0;
            i = 0;
        nextComparison:
            {
                u16 j = i + gap;
                union FrameOrderEntry *left = (union FrameOrderEntry *)(i * 4 + (u32)entries);
                union FrameOrderEntry *right = (union FrameOrderEntry *)(j * 4 + (u32)entries);
                if (left->bytes.priority < right->bytes.priority)
                {
                    u16 temporary = left->value;
                    left->value = right->value;
                    right->value = temporary;
                    swapped = 1;
                }
                if (j + 1 < count)
                {
                    i++;
                    goto nextComparison;
                }
            }
            if (swapped == 1 || gap > 1)
                goto nextGap;
        }
    }
}


void sub_08001EA8(u32 affineIndex, s32 scaleX, s32 scaleY, u32 flags)
{
    u32 i = affineIndex * 4;
    if (gFrameAffineOverride == -1)
    {
        if (flags & 0x1000)
        {
            gOamShadow[affineIndex * 4].affine = -0x4000 / scaleX;
            gOamShadow[i + 1].affine = 0;
        }
        else
        {
            gOamShadow[affineIndex * 4].affine = 0x4000 / scaleX;
            gOamShadow[i + 1].affine = flags & 0x1000;
        }
        if (flags & 0x2000)
        {
            gOamShadow[i + 2].affine = 0;
            gOamShadow[i + 3].affine = -0x4000 / scaleY;
        }
        else
        {
            gOamShadow[i + 3].affine = 0x4000 / scaleY;
            gOamShadow[i + 2].affine = flags & 0x2000;
        }
    }
    else
    {
        if (flags & 0x1000)
        {
            gOamShadow[affineIndex * 4].affine = -0x400000 / gFrameAffineOverride;
            gOamShadow[i + 1].affine = 0;
        }
        else
        {
            gOamShadow[affineIndex * 4].affine = 0x400000 / gFrameAffineOverride;
            gOamShadow[i + 1].affine = flags & 0x1000;
        }
        if (flags & 0x2000)
        {
            gOamShadow[i + 2].affine = 0;
            gOamShadow[i + 3].affine = -0x400000 / gFrameAffineOverride;
        }
        else
        {
            gOamShadow[i + 3].affine = 0x400000 / gFrameAffineOverride;
            gOamShadow[i + 2].affine = flags & 0x2000;
        }
    }
}

extern s32 DivArm(s32 denominator, s32 numerator);

void sub_08001CAC(u32 affineIndex, u32 angle, s32 scaleX, s32 scaleY, u32 flags)
{
    u32 i = affineIndex * 4;
    s32 cosine;
    s32 sine;

    if (gFrameAffineOverride == -1)
    {
        cosine = gSineTable[(angle & 0x3FF) + 0x100];
        sine = gSineTable[angle & 0x3FF];
        if (scaleX == 0)
            scaleX = 1;
        if (scaleY == 0)
            scaleY = 1;

        if (flags & 0x1000)
        {
            gOamShadow[affineIndex * 4].affine = DivArm(scaleX, -cosine);
            gOamShadow[i + 1].affine = DivArm(scaleY, -sine);
        }
        else
        {
            gOamShadow[affineIndex * 4].affine = DivArm(scaleX, cosine);
            gOamShadow[i + 1].affine = DivArm(scaleY, sine);
        }
        if (flags & 0x2000)
        {
            gOamShadow[i + 2].affine = DivArm(scaleX, sine);
            gOamShadow[i + 3].affine = DivArm(scaleY, -cosine);
        }
        else
        {
            gOamShadow[i + 3].affine = DivArm(scaleY, cosine);
            gOamShadow[i + 2].affine = DivArm(scaleX, -sine);
        }
    }
    else
    {
        cosine = gSineTable[(angle & 0x3FF) + 0x100] * 256;
        sine = gSineTable[angle & 0x3FF] * 256;
        if (flags & 0x1000)
        {
            gOamShadow[affineIndex * 4].affine = DivArm(gFrameAffineOverride, -cosine);
            gOamShadow[i + 1].affine = DivArm(gFrameAffineOverride, -sine);
        }
        else
        {
            gOamShadow[affineIndex * 4].affine = DivArm(gFrameAffineOverride, cosine);
            gOamShadow[i + 1].affine = DivArm(gFrameAffineOverride, sine);
        }
        if (flags & 0x2000)
        {
            gOamShadow[i + 2].affine = DivArm(gFrameAffineOverride, sine);
            gOamShadow[i + 3].affine = DivArm(gFrameAffineOverride, -cosine);
        }
        else
        {
            gOamShadow[i + 3].affine = DivArm(gFrameAffineOverride, cosine);
            gOamShadow[i + 2].affine = DivArm(gFrameAffineOverride, -sine);
        }
    }
}

