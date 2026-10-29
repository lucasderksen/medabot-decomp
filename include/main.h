#ifndef GUARD_MAIN_H
#define GUARD_MAIN_H

#include "global.h"
#include "main_callbacks.h"
#include "serial.h"

/* Descriptive interfaces recovered from the main-loop assembly. */
extern u32 gMainState;
extern u32 gFrameCounter;

void GameMain(void);

#endif
