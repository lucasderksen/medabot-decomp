#include "continued_numeric.h"
#include "global.h"
#include "gba.h"
#include "continued_commands.h"


void sub_080534C4(const float *first, const float *second, const float *third)
{
    float normalFirst, normalSecond, normalThird, normalFourth;
    float positionFirst, positionSecond, positionThird;
    float firstValue, secondValue, thirdValue;
    float differenceFirst, differenceSecond, differenceThird;
    float length;
    s32 divisor, firstInteger;
    sub_080535C8(first, second, third, &normalFirst, &normalSecond, &normalThird, &normalFourth);
    firstValue = first[0];
    secondValue = second[0];
    thirdValue = third[0];
    sub_080537BC(&positionFirst, &positionSecond, &positionThird);
    differenceFirst = firstValue - positionFirst;
    differenceSecond = secondValue - positionSecond;
    differenceThird = thirdValue - positionThird;
    length = differenceFirst * differenceFirst + differenceSecond * differenceSecond + differenceThird * differenceThird;
    length = sub_080533CC(length);
    if (length == 0.0f)
        length = 1.0f;
    firstInteger = (s32)differenceFirst;
    divisor = (s32)length;
    Div(firstInteger, divisor);
    Div((s32)differenceSecond, divisor);
    Div((s32)differenceThird, divisor);
    if (length < 10000.0f)
        sub_08053B04(first, second, third);
}


void sub_080535C8(const float *first, const float *second, const float *third,
                  float *firstResult, float *secondResult, float *thirdResult,
                  float *fourthResult)
{
    float firstValue, secondValue, thirdValue, length;
    s32 divisor, firstInteger;
    firstValue = second[0] * (third[1] - third[2])
               + second[1] * (third[2] - third[0])
               + second[2] * (third[0] - third[1]);
    secondValue = third[0] * (first[1] - first[2])
                + third[1] * (first[2] - first[0])
                + third[2] * (first[0] - first[1]);
    thirdValue = first[0] * (second[1] - second[2])
               + first[1] * (second[2] - second[0])
               + first[2] * (second[0] - second[1]);
    length = firstValue * firstValue + secondValue * secondValue + thirdValue * thirdValue;
    length = sub_080533CC(length);
    if (length == 0.0f)
        length = 1.0f;
    firstInteger = (s32)firstValue;
    divisor = (s32)length;
    firstValue = Div(firstInteger, divisor);
    secondValue = Div((s32)secondValue, divisor);
    thirdValue = Div((s32)thirdValue, divisor);
    *firstResult = firstValue;
    *secondResult = secondValue;
    *thirdResult = thirdValue;
    *fourthResult = -(firstValue * first[0] + secondValue * second[0] + thirdValue * third[0]);
}


void sub_080537BC(float *first, float *second, float *third)
{
    float *work = (float *)gLaterBuffer_03005350;
    *first = work[16];
    *second = work[17];
    *third = work[18];
}
