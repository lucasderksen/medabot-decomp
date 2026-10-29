.syntax unified
.cpu arm7tdmi
.thumb
.section .main, "ax", %progbits
.balign 4
/* Local Thumb aliases preserve interworking metadata for routines that still
 * live in copied ROM intervals. Linker-script absolute symbols lack that type. */
.thumb_set sub_080020C8, 0x080020C9
.thumb_set sub_080021F4, 0x080021F5
.thumb_set sub_08000964, 0x08000965
.thumb_set CallViaR0, 0x0807CCF1
.thumb_set sub_08001520, 0x08001521
.thumb_set sub_080022DC, 0x080022DD
.thumb_set InitAudio, 0x0800058D
.global GameMain
.type GameMain, %function
.thumb_func
GameMain:
    /* Entry is called in Thumb state by AgbMain; original name is unknown. */
    push {r4, r5, r6, r7, lr}
    mov r7, sl
    mov r6, sb
    mov r5, r8
    push {r5, r6, r7}
    /* Configure GBA wait states: WAITCNT = 0x4014. */
    ldr r1, .Lliteral_08000330
    ldr r2, .Lliteral_08000334
    adds r0, r2, #0
    strh r0, [r1]
    bl ResetMemory
    bl InitInterrupts
    movs r1, #0x80
    lsls r1, r1, #0x13
    movs r0, #0x60
    strh r0, [r1]
    /* Initial callback index is 3; other fields start at zero. */
    ldr r1, .Lliteral_08000338
    movs r0, #3
    str r0, [r1]
    ldr r0, .Lliteral_0800033C
    movs r4, #0
    str r4, [r0]
    ldr r0, .Lliteral_08000340
    str r4, [r0]
    bl sub_080020C8
    ldr r0, .Lliteral_08000344
    bl InitAudio
    ldr r0, .Lliteral_08000348
    movs r1, #0
    strh r4, [r0]
    ldr r0, .Lliteral_0800034C
    strb r1, [r0]
    ldr r0, .Lliteral_08000350
    strb r1, [r0]
    ldr r0, .Lliteral_08000354
    strb r1, [r0, #0x1e]
    strb r1, [r0, #0x1d]
    /* One main-loop iteration starts with the BIOS VBlank wait. */
.L080002AC:
    bl VBlankIntrWait
    ldr r1, .Lliteral_08000350
    movs r0, #0
    strb r0, [r1]
    bl ReadKeys
    ldr r1, .Lliteral_08000358
    ldr r0, [r1]
    adds r0, #1
    str r0, [r1]
    ldr r0, .Lliteral_0800035C
    ldrb r0, [r0]
    cmp r0, #0
    beq .L080002D8
    ldr r2, .Lliteral_08000360
    ldr r1, [r2, #0x18]
    ldr r0, .Lliteral_08000364
    cmp r1, r0
    bhi .L080002D8
    adds r0, r1, #1
    str r0, [r2, #0x18]
    /* Poll the four serial connection bits; names remain provisional. */
.L080002D8:
    ldr r5, .Lliteral_08000368
    ldrb r7, [r5, #2]
    mov sb, r7
    ldr r4, .Lliteral_08000354
    movs r0, #0
    strb r0, [r4, #0x1d]
    strb r0, [r4, #0x1e]
    adds r0, r4, #0
    adds r0, #8
    bl sub_080021F4
    str r0, [r4]
    movs r6, #0
    movs r0, #1
    mov sl, r0
    movs r1, #0xff
    mov r8, r1
    movs r2, #0x19
    adds r2, r2, r4
    mov ip, r2
    /* For each bit, set edge flags or count consecutive missing polls. */
.L08000300:
    mov r1, sl
    lsls r1, r6
    ldr r3, [r4]
    ands r3, r1
    cmp r3, #0
    beq .L0800036C
    movs r0, #0
    mov r7, ip
    strb r0, [r7]
    mov r0, sb
    asrs r0, r6
    mov r2, sl
    ands r0, r2
    cmp r0, #0
    bne .L080003A6
    ldrb r0, [r5, #2]
    orrs r1, r0
    strb r1, [r5, #2]
    ldrb r0, [r4, #0x1d]
    mov r7, r8
    orrs r0, r7
    strb r0, [r4, #0x1d]
    b .L080003A6
    .short 0 /* Original alignment padding. */
.Lliteral_08000330:
    .word 0x04000204
.Lliteral_08000334:
    .word 0x00004014
.Lliteral_08000338:
    .word gMainState
.Lliteral_0800033C:
    .word 0x03002B8C
.Lliteral_08000340:
    .word 0x0300137C
.Lliteral_08000344:
    .word 0x03002430
.Lliteral_08000348:
    .word 0x03001784
.Lliteral_0800034C:
    .word 0x03005030
.Lliteral_08000350:
    .word 0x03002410
.Lliteral_08000354:
    .word 0x03005010
.Lliteral_08000358:
    .word gFrameCounter
.Lliteral_0800035C:
    .word 0x03000588
.Lliteral_08000360:
    .word 0x03002B70
.Lliteral_08000364:
    .word 0x014996FE
.Lliteral_08000368:
    .word gSerialState
    /* After more than ten missing polls, clear the remembered connection bit. */
.L0800036C:
    mov r0, ip
    ldrb r2, [r0]
    ldrb r0, [r0]
    lsls r0, r0, #0x18
    asrs r0, r0, #0x18
    cmp r0, #0xa
    ble .L080003A0
    ldr r2, .Lliteral_0800039C
    ldrb r0, [r2, #2]
    asrs r0, r6
    mov r7, sl
    ands r0, r7
    cmp r0, #0
    beq .L08000390
    ldrb r0, [r4, #0x1e]
    mov r7, r8
    orrs r0, r7
    strb r0, [r4, #0x1e]
.L08000390:
    ldrb r0, [r2, #2]
    bics r0, r1
    strb r0, [r2, #2]
    mov r0, ip
    strb r3, [r0]
    b .L080003A6
.Lliteral_0800039C:
    .word gSerialState
.L080003A0:
    adds r0, r2, #1
    mov r1, ip
    strb r0, [r1]
.L080003A6:
    movs r2, #1
    add ip, r2
    adds r6, #1
    cmp r6, #3
    ble .L08000300
    /* A nonzero result from sub_08000964 reinitializes the audio context. */
    bl sub_08000964
    adds r4, r0, #0
    cmp r4, #0
    beq .L080003D0
    bl VBlankIntrWait
    ldr r0, .Lliteral_080003CC
    bl InitAudio
    bl VBlankIntrWait
    b .L08000416
    .short 0 /* Original alignment padding. */
.Lliteral_080003CC:
    .word 0x03002430
    /* Check paired 0xFFFF serial words before selecting callback state zero. */
.L080003D0:
    ldr r0, .Lliteral_08000434
    ldrb r0, [r0]
    lsls r0, r0, #0x18
    asrs r0, r0, #0x18
    cmp r0, #0
    beq .L08000416
    movs r1, #0
    ldr r0, .Lliteral_08000438
    ldrb r0, [r0]
    cmp r0, #0
    bne .L080003E8
    movs r1, #1
.L080003E8:
    ldr r3, .Lliteral_0800043C
    lsls r2, r1, #2
    adds r0, r3, #0
    adds r0, #8
    adds r0, r2, r0
    ldrh r1, [r0]
    ldr r0, .Lliteral_08000440
    cmp r1, r0
    bne .L08000416
    adds r0, r3, #0
    adds r0, #0xa
    adds r0, r2, r0
    ldrh r0, [r0]
    cmp r0, r1
    bne .L08000416
    ldr r0, .Lliteral_08000444
    str r4, [r0]
    ldr r1, .Lliteral_08000448
    movs r0, #0xa
    str r0, [r1]
    ldr r1, .Lliteral_0800044C
    movs r0, #0x10
    str r0, [r1]
    /* Invoke gMainCallbacks[gMainState] through the register trampoline. */
.L08000416:
    ldr r1, .Lliteral_08000450
    ldr r0, .Lliteral_08000444
    ldr r0, [r0]
    lsls r0, r0, #2
    adds r0, r0, r1
    ldr r0, [r0]
    bl CallViaR0
    /* Run remaining per-frame work, then repeat without returning. */
    bl sub_08001520
    ldr r0, .Lliteral_08000454
    bl sub_080022DC
    b .L080002AC
    .short 0 /* Original alignment padding. */
.Lliteral_08000434:
    .word 0x03005030
.Lliteral_08000438:
    .word 0x03000B90
.Lliteral_0800043C:
    .word 0x03005010
.Lliteral_08000440:
    .word 0x0000FFFF
.Lliteral_08000444:
    .word gMainState
.Lliteral_08000448:
    .word 0x03002B8C
.Lliteral_0800044C:
    .word 0x0300137C
.Lliteral_08000450:
    .word gMainCallbacks
.Lliteral_08000454:
    .word 0x03005014
.size GameMain, . - GameMain
