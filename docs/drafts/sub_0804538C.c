struct OamBits538C {
    u16 y:8;
    u16 attr0Middle:6;
    u16 shape:2;
    u16 x:9;
    u16 attr1Middle:5;
    u16 size:2;
    u16 attr2;
    u16 affine;
};
void sub_0804538C(struct RecordObjectWork *work, u16 y, u16 x, u16 key) {
    struct OamBits538C *object;
    u32 dims;
    u32 height;
    u32 width;
    u16 row;
    u16 column;

    object = (struct OamBits538C *)work->objects;
    height = object->shape;
    width = object->size;
    dims = sub_08044E64(height << 14, width << 30);
    height = dims >> 16;
    width = dims & 0xFFFF;
    work->key = key;
    for (row = 0; row < work->rows; row++) {
        for (column = 0; column < work->columns; column++) {
            s32 sx;
            object->y = y;
            sx = (s16)x;
            object->x = sx;
            x += width;
            object++;
        }
        x -= width * work->columns;
        y += height;
    }
}
