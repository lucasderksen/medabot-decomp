    .syntax unified
    .cpu arm7tdmi
    .thumb
    .section .initialization, "ax", %progbits
    .balign 4

    /* These two code intervals have not yet been reconstructed. */
    .thumb_set Unknown_0807C8B0, 0x0807C8B0
    .thumb_set Unknown_0805DEB0, 0x0805DEB0

    .global InitInterrupts
    .type InitInterrupts, %function
    .thumb_func
InitInterrupts:                     /* 0x08000458 */
    push {r4, r5, lr}
    ldr r0, .Ldefault_intr_table
    ldr r1, .Lintr_table
    ldr r2, .Lcopy_intr_table        /* CpuSet: copy fourteen 32-bit words. */
    bl CpuSet
    ldr r0, .Lintr_main_rom
    ldr r4, .Lintr_main_buffer
    ldr r5, .Lcopy_intr_main        /* Also the address of REG_IE. */
    adds r1, r4, #0
    adds r2, r5, #0
    bl CpuSet                      /* Copy 0x800 bytes, not just IntrMain. */
    ldr r0, .Lbios_intr_vector
    str r4, [r0]                   /* The copied dispatcher uses ARM state. */
    ldr r0, .Lcallback_03000b98
    ldr r1, .Ldummy_intr_handler
    str r1, [r0]
    ldr r0, .Lcallback_030017f0
    str r1, [r0]
    ldr r0, .Lcallback_03002c20
    str r1, [r0]
    ldr r1, .Linitial_ie
    adds r0, r1, #0
    strh r0, [r5]                  /* VBlank, DMA1, DMA2, and Game Pak. */
    ldr r1, .Ldispstat
    movs r0, #8                    /* Enable the VBlank interrupt request. */
    strh r0, [r1]
    ldr r1, .Lime_init
    movs r0, #1
    strh r0, [r1]
    movs r0, #0x40
    bl Unknown_0807C8B0
    bl Unknown_0805DEB0
    pop {r4, r5}
    pop {r0}
    bx r0
    .short 0                       /* Original alignment halfword. */
.Ldefault_intr_table: .word 0x0807E860
.Lintr_table:         .word gIntrTable
.Lcopy_intr_table:    .word 0x0400000E
.Lintr_main_rom:      .word IntrMain
.Lintr_main_buffer:   .word gIntrMainBuffer
.Lcopy_intr_main:     .word 0x04000200
.Lbios_intr_vector:   .word 0x03007FFC
.Lcallback_03000b98:  .word 0x03000B98
.Ldummy_intr_handler: .word DummyInterruptHandler
.Lcallback_030017f0:  .word 0x030017F0
.Lcallback_03002c20:  .word 0x03002C20
.Linitial_ie:         .word 0x00002601
.Ldispstat:           .word 0x04000004
.Lime_init:           .word 0x04000208
    .size InitInterrupts, . - InitInterrupts

    .global ResetMemory
    .type ResetMemory, %function
    .thumb_func
ResetMemory:                        /* 0x080004E0 */
    push {r4, lr}
    sub sp, #12
    ldr r1, .Lime_reset
    movs r0, #0
    strh r0, [r1]
    movs r4, #0
    str r4, [sp]
    movs r1, #0x80
    lsls r1, r1, #18               /* EWRAM 0x02000000. */
    ldr r2, .Lfill_ewram           /* CpuFastSet fill: 0x10000 words. */
    mov r0, sp
    bl CpuFastSet
    str r4, [sp, #4]
    add r0, sp, #4
    movs r1, #0xc0
    lsls r1, r1, #18               /* IWRAM 0x03000000. */
    ldr r2, .Lfill_iwram           /* 0x1F40 words: leave top 0x300 bytes. */
    bl CpuFastSet
    bl ResetSpritesAndVram
    str r4, [sp, #8]
    add r0, sp, #8
    movs r4, #0xa0
    lsls r4, r4, #19               /* Palette RAM 0x05000000. */
    ldr r2, .Lfill_palette
    adds r1, r4, #0
    bl CpuFastSet
    ldr r1, .Lwhite
    adds r0, r1, #0
    strh r0, [r4]                  /* Palette entry zero = RGB5(31,31,31). */
    add sp, #12
    pop {r4}
    pop {r0}
    bx r0
    .short 0
.Lime_reset:    .word 0x04000208
.Lfill_ewram:   .word 0x01010000
.Lfill_iwram:   .word 0x01001F40
.Lfill_palette: .word 0x01000100
.Lwhite:        .word 0x00007FFF
    .size ResetMemory, . - ResetMemory

    .global ResetSpritesAndVram
    .type ResetSpritesAndVram, %function
    .thumb_func
ResetSpritesAndVram:                /* 0x08000540 */
    push {r4, lr}
    sub sp, #8
    movs r0, #0xa0
    str r0, [sp]
    movs r1, #0xe0
    lsls r1, r1, #19               /* OAM 0x07000000. */
    ldr r2, .Lfill_oam
    mov r0, sp
    bl CpuFastSet                  /* Fill each word with 0x000000A0. */
    add r3, sp, #4
    ldr r1, .Loam_shadow
    movs r2, #0xa0
    movs r4, #0xfe
    lsls r4, r4, #2               /* Last attr0: shadow + 0x3F8. */
    adds r0, r1, r4
.Lreset_shadow:
    strh r2, [r0]                 /* Only attr0 in each shadow entry. */
    subs r0, #8
    cmp r0, r1
    bge .Lreset_shadow
    movs r0, #0
    str r0, [sp, #4]
    movs r1, #0xc0
    lsls r1, r1, #19               /* VRAM 0x06000000. */
    ldr r2, .Lfill_vram
    adds r0, r3, #0
    bl CpuFastSet
    add sp, #8
    pop {r4}
    pop {r0}
    bx r0
.Lfill_oam:   .word 0x01000100
.Loam_shadow: .word gOamShadow
.Lfill_vram:  .word 0x01006000
    .size ResetSpritesAndVram, . - ResetSpritesAndVram
