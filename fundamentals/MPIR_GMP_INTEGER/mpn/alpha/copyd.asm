dnl  Alpha mpn_copyd -- copy, decrementing.

dnl  Copyright 2002, 2003 Free Software Foundation, Inc.

dnl  This file is part of the GNU MP Library.

dnl  The GNU MP Library is free software; you can redistribute it and/or modify
dnl  it under the terms of the GNU Lesser General Public License as published
dnl  by the Free Software Foundation; either version 2.1 of the License, or (at
dnl  your option) any later version.

dnl  The GNU MP Library is distributed in the hope that it will be useful, but
dnl  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
dnl  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
dnl  License for more details.

dnl  You should have received a copy of the GNU Lesser General Public License
dnl  along with the GNU MP Library; see the file COPYING.LIB.  If not, write
dnl  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
dnl  Boston, MA 02110-1301, USA.

include(`../config.m4')

C      cycles/limb
C EV4:     4
C EV5:     1.75
C EV6:     1

C INPUT PARAMETERS
C rp	r16
C up	r17
C n	r18


ASM_START()
PROLOGUE(mpn_copyd)
	s8addq	r18,r16,r16		C E0
	s8addq	r18,r17,r17		C E1
	lda	r18,-8(r18)		C E0
	blt	r18,$Lend		C E1
$Loop:	ldq	r0,-8(r17)		C E0
	ldq	r1,-16(r17)		C E1
	ldq	r2,-24(r17)		C E0
	ldq	r3,-32(r17)		C E1
	ldq	r4,-40(r17)		C E0
	ldq	r5,-48(r17)		C E1
	ldq	r6,-56(r17)		C E0
	ldq	r7,-64(r17)		C E1
	stq	r0,-8(r16)		C E0
	lda	r17,-64(r17)		C E1
	stq	r1,-16(r16)		C E0
	bis	r31, r31, r31		C E1
	stq	r2,-24(r16)		C E0
	lda	r18,-8(r18)		C E1
	stq	r3,-32(r16)		C E0
	bis	r31, r31, r31		C E1
	stq	r4,-40(r16)		C E0
	bis	r31, r31, r31		C E1
	stq	r5,-48(r16)		C E0
	bis	r31, r31, r31		C E1
	stq	r6,-56(r16)		C E0
	bis	r31, r31, r31		C E1
	stq	r7,-64(r16)		C E0
	lda	r16,-64(r16)		C E1
	bge	r18,$Loop		C E1
$Lend:	lda	r18,7(r18)		C E0
	blt	r18,$Lret		C E1
	ldq	r0,-8(r17)		C E0
	beq	r18,$Lend0		C E1
$Loop0:	stq	r0,-8(r16)		C E0
	lda	r16,-8(r16)		C E1
	ldq	r0,-16(r17)		C E0
	lda	r18,-1(r18)		C E1
	lda	r17,-8(r17)		C E0
	bgt	r18,$Loop0		C E1
$Lend0:	stq	r0,-8(r16)		C E0
$Lret:	ret	r31,(r26),1		C E1
EPILOGUE(mpn_copyd)
ASM_END()
