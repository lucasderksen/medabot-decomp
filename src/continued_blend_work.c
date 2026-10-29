#include "main_callbacks.h"
#include "main_callbacks.h"

/* Observed six-byte prefix, not proof of the complete original work type. */
struct ObservedBlendWork
{
    u16 control;
    u8 value;
    u8 interval;
    u8 timer;
    s8 mode;
};

void sub_080656DC(void *workPointer, u32 first, u32 second, u32 third, u32 fourth)
{
    struct ObservedBlendWork *work = workPointer;
    u16 control = fourth;
    u32 zero = 0;
    volatile u16 *destination;
    work->control = control;
    work->value = first;
    work->interval = second;
    work->mode = third;
    *(volatile u16 *)0x04000050 = control | 63;
    destination = (void *)0x04000052;
    *destination = zero;
    destination++;
    *destination = work->value;
}

u32 sub_08065710(void *workPointer)
{
    struct ObservedBlendWork *work = workPointer;
    u32 finished = 0;
    u32 zero;
    if (work->mode == 0)
    {
        finished = 1;
        goto complete;
    }
    *(volatile u16 *)0x04000050 = work->control | 63;
    zero = 0;
    *(volatile u16 *)0x04000052 = finished;
    *(volatile u16 *)0x04000054 = work->value;
    work->timer++;
    if (work->timer >= work->interval)
    {
        work->timer = zero;
        if (work->mode > 0 && work->value > 15)
        {
            work->mode = zero;
            finished = 1;
        }
        if (work->mode < 0 && work->value == 0)
        {
            work->mode = 0;
            finished = 1;
        }
        if (finished == 0)
            work->value += work->mode;
    }
complete:
    return finished;
}
