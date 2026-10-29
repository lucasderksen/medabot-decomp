@ Derived from pret/agbcc libgcc/lib1thumb.asm, pinned commit
@ da598c1d918402c42c0c0d7128ba14567f3175e9, preprocessed with L_dvmd_tls.
@ Changes: explicit per-function ELF section and final zero-fill alignment.
@ The upstream copyright and linking exceptions below are retained.
@ GNU GPL version 2 text is in asm/libgcc/COPYING.

.section .libgcc_dvmd_tls,"ax",%progbits
@ libgcc1 routines for ARM cpu.
@ Division routines, written by Richard Earnshaw, (rearnsha@armltd.co.uk)
/* Copyright (C) 1995, 1996, 1998 Free Software Foundation, Inc.

This file is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

In addition to the permissions in the GNU General Public License, the
Free Software Foundation gives you unlimited permission to link the
compiled version of this file with other programs, and to distribute
those programs without any restriction coming from the use of this
file.  (The General Public License restrictions do apply in other
respects; for example, they cover modification of the file, and
distribution when not linked into another program.)

This file is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */
/* As a special exception, if you link this library with other files,
   some of which are compiled with GCC, to produce an executable,
   this library does not by itself cause the resulting executable
   to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */
 .code 16
work .req r4 @ XXXX is this safe ?
 .globl __div0
 .type __div0,function
 .align 2, 0
 .thumb_func
__div0:
 mov pc, lr
 .size __div0, . - __div0

.section .libgcc_dvmd_tls,"ax",%progbits
.align 2, 0
