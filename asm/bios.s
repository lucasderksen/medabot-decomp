    .syntax unified
    .cpu arm7tdmi
    .thumb
    .section .bios, "ax", %progbits

    .macro bios_function name, number
    .global \name
    .type \name, %function
    .thumb_func
\name:
    svc #\number
    bx lr
    .size \name, . - \name
    .endm

    bios_function CpuFastSet, 0x0c       /* 0x0807CCC0 */
    bios_function CpuSet, 0x0b           /* 0x0807CCC4 */
    bios_function Div, 0x06              /* 0x0807CCC8 */
    bios_function DivArm, 0x07           /* 0x0807CCCC */

    .global Mod
    .type Mod, %function
    .thumb_func
Mod:                                    /* 0x0807CCD0 */
    svc #6
    adds r0, r1, #0
    bx lr
    .short 0
    .size Mod, . - Mod

    bios_function LZ77UnCompVram, 0x12    /* 0x0807CCD8 */
    bios_function LZ77UnCompWram, 0x11    /* 0x0807CCDC */
    bios_function ObjAffineSet, 0x0f     /* 0x0807CCE0 */
    bios_function Sqrt, 0x08             /* 0x0807CCE4 */

    .global VBlankIntrWait
    .type VBlankIntrWait, %function
    .thumb_func
VBlankIntrWait:                          /* 0x0807CCE8 */
    movs r2, #0
    svc #5
    bx lr
    .short 0
    .size VBlankIntrWait, . - VBlankIntrWait
