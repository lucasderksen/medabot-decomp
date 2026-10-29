/* Minimal expansion of the historical Newlib ANSI declarations.
 * size_t and these macro definitions preserve the original headers' types.
 * Source and license provenance: docs/RUNTIME.md and COPYING.NEWLIB. */
#ifndef MEDABOTS_LIBC_COMPAT_H
#define MEDABOTS_LIBC_COMPAT_H
typedef unsigned long size_t;
#define _PTR void *
#define _CONST const
#define _AND ,
#define _DEFUN(name, arglist, args) name(args)
#endif
