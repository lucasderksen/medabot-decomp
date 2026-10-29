"""Bounded host decoder for the GBA BIOS 0x10 LZ77 serialization.

Format cross-check: mGBA src/gba/bios.c, _unLz77 (primary implementation),
https://github.com/mgba-emu/mgba/blob/master/src/gba/bios.c
This host parser rejects malformed streams; it does not replace game code.
"""

def decode(data, offset=0, max_output=128*1024):
    if offset < 0 or offset+4 > len(data) or data[offset] != 0x10:
        raise ValueError('Invalid or truncated LZ77 header.')
    size=int.from_bytes(data[offset+1:offset+4], 'little')
    if size > max_output:
        raise ValueError('LZ77 decoded size exceeds limit.')
    cursor=offset+4
    output=bytearray()
    def take(count):
        nonlocal cursor
        if cursor+count>len(data):
            raise ValueError('Truncated LZ77 payload.')
        result=data[cursor:cursor+count]
        cursor+=count
        return result
    while len(output)<size:
        flags=take(1)[0]
        for bit in range(7,-1,-1):
            if flags & (1<<bit):
                packed=int.from_bytes(take(2),'big')
                count=(packed>>12)+3
                distance=(packed&4095)+1
                if distance>len(output):
                    raise ValueError('LZ77 reference precedes output.')
                if len(output)+count>size:
                    raise ValueError('LZ77 command overruns declared size.')
                for _ in range(count):
                    output.append(output[-distance])
            else:
                output.extend(take(1))
            if len(output)==size:
                break
    return bytes(output),cursor-offset
