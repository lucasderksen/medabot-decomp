#ifndef GUARD_BIOS_LZ77_H
#define GUARD_BIOS_LZ77_H
/* Native BIOS LZ77: eight flags, high bit first; one means a copy. */
#define LZ77_HEADER(size) 0x10, ((size)&255), (((size)>>8)&255), (((size)>>16)&255)
#define LZ77_FLAGS(a,b,c,d,e,f,g,h) (((a)<<7)|((b)<<6)|((c)<<5)|((d)<<4)|((e)<<3)|((f)<<2)|((g)<<1)|(h))
#define LZ77_WORD(distance,count) ((((count)-3)<<12)|((distance)-1))
#define LZ77_COPY(distance,count) ((LZ77_WORD(distance,count)>>8)&255), (LZ77_WORD(distance,count)&255)
#define LZ77_LITERAL(value) (value)
#endif
