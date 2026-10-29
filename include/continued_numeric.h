#ifndef GUARD_CONTINUED_NUMERIC_H
#define GUARD_CONTINUED_NUMERIC_H
#include "global.h"

/* Normalize inputs to bytes and move current toward target when they differ. */
u8 sub_080669AC(u32 target, u32 current, u32 divisor);

/* Observed float-array slots and outputs; complete RAM layout remains unknown. */
float sub_08053360(float value);
float sub_08053380(float value);
float sub_080533A4(float value);
double sub_080533CC(double value);
void sub_08053464(void);
void sub_080534C4(const float *first, const float *second, const float *third);
void sub_080535C8(const float *first, const float *second, const float *third,
                 float *firstResult, float *secondResult, float *thirdResult,
                 float *fourthResult);
void sub_080537BC(float *first, float *second, float *third);
void sub_080537D8(void);
void sub_08053B04(const float *first, const float *second, const float *third);
void sub_080537E4(void);
void sub_08053858(float first, float second, float third, float fourth);
void sub_0805390C(float first, float second, float third, float fourth);
void sub_080539C0(float first, float second, float scale, float fourth);
void sub_08053BE0(float first, float second, float third);
void sub_08053C00(float first, float second);
void sub_08053C14(float first, float second, float third);
void sub_08053C7C(float first, float second, float third, float *firstResult,
                 float *secondResult, float *thirdResult);
void sub_08053D78(float first, float second, s32 *firstResult, s32 *secondResult);
void sub_08053DE0(float first, float second);
void sub_08053FBC(s32 first, s32 second);
extern const float gSecondaryFloatTable_083D6F2C[];
extern const float gSecondaryFloatTable_083D732C[];
#endif
