    .syntax unified
    .cpu arm7tdmi
    .thumb
    .section .trampolines, "ax", %progbits
    .balign 4

    /* GNU Thumb indirect-call helpers, 0x0807CCF0..0x0807CD2C. */
    .macro call_via name, reg
    .global \name
    .type \name, %function
    .thumb_func
\name:
    bx \reg
    nop
    .size \name, . - \name
    .endm

    call_via _call_via_r0, r0
    call_via _call_via_r1, r1
    call_via _call_via_r2, r2
    call_via _call_via_r3, r3
    call_via _call_via_r4, r4
    call_via _call_via_r5, r5
    call_via _call_via_r6, r6
    call_via _call_via_r7, r7
    call_via _call_via_r8, r8
    call_via _call_via_r9, r9
    call_via _call_via_r10, r10
    call_via _call_via_r11, r11
    call_via _call_via_r12, r12
    call_via _call_via_sp, sp
    call_via _call_via_lr, lr

    .global CallViaR0
    .thumb_set CallViaR0, _call_via_r0
    .global _call_via_sb
    .thumb_set _call_via_sb, _call_via_r9
    .global _call_via_sl
    .thumb_set _call_via_sl, _call_via_r10
    .global _call_via_fp
    .thumb_set _call_via_fp, _call_via_r11
    .global _call_via_ip
    .thumb_set _call_via_ip, _call_via_r12
