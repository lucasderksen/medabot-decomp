#ifndef GUARD_ACTION_SCENE_COMMANDS_H
#define GUARD_ACTION_SCENE_COMMANDS_H

#define ACTION_END 1
#define ACTION_LABEL(label) (label)
#define ACTION_MOTION(y, x) (u16)(y), (u16)(x)
#define ACTION_PIECE(units, asset) (units), (asset)
#define ACTION_PIECE_END 0
#define ACTION_TILE_HEADER(base, width) (base), (width)
#define ACTION_TILE_FRAME(time, frame) (time), (frame)
#define ACTION_TILE_SOUND(sound) 0xFD, (sound)
#define ACTION_TILE_LOOP(target) 0xFE, (target)
#define ACTION_TILE_END 0xFF
#define ACTION_COMMAND_0(op) (op)
#define ACTION_COMMAND_1(op, p0) (op), (p0)
#define ACTION_COMMAND_2(op, p0, p1) (op), (p0), (p1)
#define ACTION_COMMAND_3(op, p0, p1, p2) (op), (p0), (p1), (p2)
#define ACTION_COMMAND_4(op, p0, p1, p2, p3) (op), (p0), (p1), (p2), (p3)
#define ACTION_COMMAND_5(op, p0, p1, p2, p3, p4) (op), (p0), (p1), (p2), (p3), (p4)
#define ACTION_COMMAND_6(op, p0, p1, p2, p3, p4, p5) (op), (p0), (p1), (p2), (p3), (p4), (p5)
#define ACTION_COMMAND_7(op, p0, p1, p2, p3, p4, p5, p6) (op), (p0), (p1), (p2), (p3), (p4), (p5), (p6)
#define ACTION_COMMAND_8(op, p0, p1, p2, p3, p4, p5, p6, p7) (op), (p0), (p1), (p2), (p3), (p4), (p5), (p6), (p7)

#endif
