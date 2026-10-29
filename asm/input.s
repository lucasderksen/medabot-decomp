    .syntax unified
    .cpu arm7tdmi
    .thumb
    .section .input, "ax", %progbits
    .balign 4

    .global ReadKeys
    .type ReadKeys, %function
    .thumb_func
ReadKeys:                       /* 0x08000844 */
    push {r4-r6, lr}
    ldr r0, .Lprevious
    ldr r5, .Lheld
    ldrh r2, [r5]
    strh r2, [r0]
    ldr r0, .Lkeyinput
    ldrh r1, [r0]
    ldr r3, .Lkeymask
    adds r0, r3, #0
    eors r1, r0                 /* Hardware keys are active low. */
    strh r1, [r5]
    ldr r6, .Lnew
    adds r3, r1, #0
    bics r3, r2
    strh r3, [r6]               /* Newly pressed: held & ~previous. */
    ldr r0, .Lreleased
    bics r2, r1
    strh r2, [r0]               /* Released: previous & ~held. */
    ldr r4, .Lrepeated
    movs r0, #0
    strh r0, [r4]
    cmp r3, #0
    beq .Lcheck_held
    strh r3, [r4]
    ldr r1, .Lrepeat_counter
    movs r0, #16                /* Initial repeat delay. */
    strb r0, [r1]
.Lcheck_held:
    ldrh r2, [r5]
    cmp r2, #0
    beq .Lreturn
    ldr r1, .Lrepeat_counter
    ldrb r0, [r1]
    cmp r0, #0
    bne .Ldecrement
    ldrh r0, [r6]
    orrs r0, r2
    strh r0, [r4]
    movs r0, #3                 /* Subsequent repeat interval. */
    b .Lstore_counter
    .short 0
.Lprevious:       .word gPreviousKeys
.Lheld:           .word gHeldKeys
.Lkeyinput:       .word 0x04000130
.Lkeymask:        .word 0x000003FF
.Lnew:            .word gNewKeys
.Lreleased:       .word gReleasedKeys
.Lrepeated:       .word gRepeatedKeys
.Lrepeat_counter: .word gKeyRepeatCounter
.Ldecrement:
    subs r0, #1
.Lstore_counter:
    strb r0, [r1]
.Lreturn:
    pop {r4-r6}
    pop {r0}
    bx r0
    .short 0
    .size ReadKeys, . - ReadKeys
