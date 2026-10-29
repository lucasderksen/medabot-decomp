#ifndef GUARD_GLOBAL_H
#define GUARD_GLOBAL_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

#ifndef NULL
#define NULL ((void *)0)
#endif

#define NAKED __attribute__((naked))

/*
 * A function that does not match yet. The matching build assembles the
 * original code from `path` (asm/non_matching/) in its place; the C body is
 * the closest attempt so far and is compiled as dead code, so it stays
 * type-checked. Building with -DNON_MATCHING compiles the C instead, which is
 * not byte-identical. Usage:
 *
 *     NONMATCH("asm/non_matching/sub_08048BE0.inc", void sub_08048BE0(void))
 *     {
 *         ...
 *     }
 *     END_NONMATCH
 */
#ifdef NON_MATCHING
#define NONMATCH(path, decl) decl
#define END_NONMATCH
#else
#define NONMATCH(path, decl) NAKED decl { asm(".include " #path); if (0)
#define END_NONMATCH }
#endif

/* Fake match (AGENTS.md): keeps `var` in hard register `reg`. */
#define FORCE_REGISTER(var, reg) register var asm(#reg)

#endif
