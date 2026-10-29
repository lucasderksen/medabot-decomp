    .syntax unified
    .cpu arm7tdmi
    .arm
    .section .rom_header, "ax", %progbits
    .global RomHeader
RomHeader:
    b AgbMain
    /* Nintendo logo bytes are extracted from the locally supplied dump. */
    .incbin "baserom.gba", 0x04, 0x9c
    .ascii "MEDABOTSMTBV"
    .ascii "A8BP"
    .ascii "E9"
    .byte 0x96              /* Fixed byte. */
    .byte 0x00              /* Main unit code. */
    .byte 0x00              /* Device type. */
    .space 7, 0
    .byte 0x00              /* Software revision. */
    .byte 0x40              /* Header complement checksum. */
    .space 2, 0
