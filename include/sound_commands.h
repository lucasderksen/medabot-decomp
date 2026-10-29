#ifndef GUARD_SOUND_COMMANDS_H
#define GUARD_SOUND_COMMANDS_H

/* Bytecode interpreted by sub_08072D68 and its 08072910..08072D5C handlers.
 * Parameters preserve encoded bytes: event/rest delays gain one tick in the
 * interpreter; SOUND_DURATION is stored directly. MODE 1 events carry a
 * word payload (channel kind 3 ignores it without an operand), while MODE 0/2
 * events carry a length byte. Numeric suffixes
 * denote channel-field offsets whose musical meaning remains provisional. */
#define SOUND_EVENT(code, length) (code), (length)
#define SOUND_WORD(high, low) (high), (low)
#define SOUND_MODE1_IGNORED(code) (code)
#define SOUND_VOLUME(value) (0xD0 | (value))
#define SOUND_REST(length) 0x80, (length)
#define SOUND_REST_E0(a) 0xE0, (a)
#define SOUND_DURATION(a) 0xE1, (a)
#define SOUND_SET_69(a) 0xE2, (a)
#define SOUND_SET_67(a) 0xE3, (a)
#define SOUND_DUTY_0 0xE4
#define SOUND_DUTY_1 0xE5
#define SOUND_DUTY_2 0xE6
#define SOUND_DUTY_3 0xE7
#define SOUND_TRANSPOSE(a) 0xE8, (a)
#define SOUND_GATE(a) 0xE9, (a)
#define SOUND_SET_6F(a) 0xEA, (a)
#define SOUND_INCREMENT_4C 0xEB
#define SOUND_REPEAT_A(a) 0xF0, (a)
#define SOUND_REPEAT_A_END 0xF1
#define SOUND_REPEAT_B(a) 0xF2, (a)
#define SOUND_REPEAT_B_END 0xF3
#define SOUND_SET_54(a) 0xF7, (a)
#define SOUND_SET_55(a) 0xF8, (a)
#define SOUND_SET_56_57(a, b) 0xF9, (a), (b)
#define SOUND_DELAY_HIGH(a) 0xFA, (a)
#define SOUND_SET_58_61(a, b, c, d) 0xFB, (a), (b), (c), (d)
#define SOUND_ENABLE_62 0xFC
#define SOUND_DISABLE_62 0xFD
#define SOUND_MODE(a) 0xFE, (a)
#define SOUND_END 0xFF

#endif
