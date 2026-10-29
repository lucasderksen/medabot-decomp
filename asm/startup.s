    .syntax unified
    .cpu arm7tdmi
    .arm
    .section .startup, "ax", %progbits

    .global AgbMain
    .type AgbMain, %function
AgbMain:                    /* 0x080000C0 */
    mov r0, #0x12          /* IRQ mode. */
    msr cpsr_fc, r0
    ldr sp, .Lirq_stack
    mov r0, #0x1f          /* System mode. */
    msr cpsr_fc, r0
    ldr sp, .Lsystem_stack
    ldr r1, .Lirq_vector
    adr r0, IntrMain
    str r0, [r1]
    ldr r1, .Lmain
    mov lr, pc
    bx r1
    b AgbMain
.Lsystem_stack: .word 0x03007F00
.Lirq_stack:    .word 0x03007FA0
.Lirq_vector:   .word 0x03007FFC
.Lmain:         .word 0x0800025D
    .size AgbMain, . - AgbMain

    .global IntrMain
    .type IntrMain, %function
IntrMain:                   /* 0x08000104; copied to IWRAM at 0x03001C10. */
    mov r3, #0x04000000
    add r3, r3, #0x200
    ldr r2, [r3]           /* IE and IF in one word. */
    ldrh r1, [r3, #8]     /* IME. */
    mrs r0, spsr
    stmdb sp!, {r0-r3, lr}
    mov r0, #1
    strh r0, [r3, #8]
    and r1, r2, r2, lsr #16
    mov r12, #0
    ands r0, r1, #0xc0    /* Timer3/Serial precede display interrupts. */
    bne .Ldispatch
    add r12, r12, #4
    ands r0, r1, #1       /* VBlank. */
    bne .Ldispatch
    add r12, r12, #4
    ands r0, r1, #4       /* VCount. */
    bne .Ldispatch
    add r12, r12, #4
    ands r0, r1, #2       /* HBlank. */
    bne .Ldispatch
    add r12, r12, #4
    ands r0, r1, #0x100   /* DMA0. */
    bne .Ldispatch
    add r12, r12, #4
    ands r0, r1, #0x200   /* DMA1. */
    bne .Ldispatch
    add r12, r12, #4
    ands r0, r1, #0x400   /* DMA2. */
    bne .Ldispatch
    add r12, r12, #4
    ands r0, r1, #0x800   /* DMA3. */
    bne .Ldispatch
    add r12, r12, #4
    ands r0, r1, #0x1000  /* Keypad. */
    bne .Ldispatch
    add r12, r12, #4
    ands r0, r1, #0x20    /* Timer2. */
    bne .Ldispatch
    add r12, r12, #4
    ands r0, r1, #0x2000  /* Game Pak interrupt: mute sound and stop. */
    strbne r0, [r3, #-0x17c]
.Lgamepak_stop:
    bne .Lgamepak_stop
.Ldispatch:
    strh r0, [r3, #2]     /* Acknowledge the selected interrupt. */
    mov r1, #0x26c0
    bic r2, r2, r0
    and r1, r1, r2
    strh r1, [r3]
    mrs r3, cpsr
    bic r3, r3, #0xdf
    orr r3, r3, #0x1f
    msr cpsr_fc, r3
    ldr r1, .Lirq_table
    add r1, r1, r12
    ldr r0, [r1]
    stmdb sp!, {lr}
    adr lr, .Lhandler_return
    bx r0
.Lhandler_return:
    ldmia sp!, {lr}
    mrs r3, cpsr
    bic r3, r3, #0xdf
    orr r3, r3, #0x92
    msr cpsr_fc, r3
    ldmia sp!, {r0-r3, lr}
    strh r2, [r3]
    strh r1, [r3, #8]
    msr spsr_fc, r0
    bx lr
.Lirq_table: .word 0x03000BA0
    .size IntrMain, . - IntrMain

    .global SwapSerialBuffers
    .type SwapSerialBuffers, %function
SwapSerialBuffers:          /* 0x08000218; descriptive name is provisional. */
    stmdb sp!, {r8-r11}
    mov r12, #0x04000000
    ldr r11, .Lserial_state
    add r10, r11, #0x28
    mov r9, #1
    mov r8, #0
    strb r8, [r12, #0x208]
    ldmia r10, {r0, r1}
    stmia r10!, {r1}
    stmia r10!, {r0}
    ldrb r0, [r11, #5]
    strb r8, [r11, #5]
    strb r9, [r12, #0x208]
    ldmia sp!, {r8-r11}
    bx lr
.Lserial_state: .word 0x03005170
    .size SwapSerialBuffers, . - SwapSerialBuffers

    .thumb
    .global Nullsub_08000258
    .thumb_func
Nullsub_08000258:
    bx lr
    .short 0
