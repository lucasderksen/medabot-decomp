#ifndef GUARD_ROM_LIBC_H
#define GUARD_ROM_LIBC_H

/* Pinned imported Newlib size_t is unsigned long. */
void *memcpy(void *destination, const void *source, unsigned long length);

#endif
