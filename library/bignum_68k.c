// This is a mix of the 68020 assembly code in bn_mul.h,
// fed through NetBSD/mac68k GCC, and adapted to work with
// CodeWarrior and MacOS. There is one further optimization,
// which is to not store/fetch registers in RAM after every
// iteration of the loop (a consequence of the mixed C/ASM in the
// original)
//
// -leitec, 2014

#include "polarssl/config.h"
#include "polarssl/bignum.h"
#include "polarssl/bn_mul.h"

asm void mpi_mul_hlp_68k(int i, t_uint *s, t_uint *d, t_uint b);

asm void mpi_mul_hlp_68k(int i, t_uint *s, t_uint *d, t_uint b)
{
	machine 68020
	
	link	 a6,#-28
	movem.l  d3-d7/a2-a4,-(a7)
	
	// hand-tune: don't keep writing/fetching these from RAM
	// with each iteration of the loop
	clr.l	-28(a6)		// c
	move.l	  8(a6), d5	// i
	movea.l	 12(a6), a2	// s
	movea.l	 16(a6), a3	// d
	move.l	-28(a6), d3	// c
	move.l	 20(a6), d0	// b

	// check if we need to run this loop (size >= 8)
	moveq	 #7, d7
	cmp.l	 d5, d7
	bcc 	 pre_loop1

	// gcc a0 = a4
	movea.l	 d5, a4
loop8:
	// INIT
	moveq	 #0, d7

	// HUIT gcc d2 = d0
	//      gcc d0 = d7
	move.l	 (a2)+, d1
	mulu.l	 d0, d4:d1
	addx.l	 d3, d1
	addx.l	 d7, d4
	add.l	 d1, (a3)+
	move.l	 (a2)+, d1
	mulu.l	 d0, d3:d1
	addx.l	 d4, d1
	addx.l	 d7, d3
	add.l	 d1, (a3)+
	
	move.l	 (a2)+, d1
	mulu.l	 d0, d4:d1
	addx.l	 d3, d1
	addx.l	 d7, d4
	add.l	 d1, (a3)+
	move.l	 (a2)+, d1
	mulu.l	 d0, d3:d1
	addx.l	 d4, d1
	addx.l	 d7, d3
	add.l	 d1, (a3)+

	move.l	 (a2)+, d1
	mulu.l	 d0, d4:d1
	addx.l	 d3, d1
	addx.l	 d7, d4
	add.l	 d1, (a3)+
	move.l	 (a2)+, d1
	mulu.l	 d0, d3:d1
	addx.l	 d4, d1
	addx.l	 d7, d3
	add.l	 d1, (a3)+

	move.l	 (a2)+, d1
	mulu.l	 d0, d4:d1
	addx.l	 d3, d1
	addx.l	 d7, d4
	add.l	 d1, (a3)+
	move.l	 (a2)+, d1
	mulu.l	 d0, d3:d1
	addx.l	 d4, d1
	addx.l	 d7, d3
	add.l	 d1, (a3)+

	addx.l	 d7, d3

	// STOP
	subq.l	 #8, a4
	moveq	 #7, d7
	cmp.l	 a4, d7
	bcs	 	 loop8
	and.l	 d7, d5
pre_loop1:
	// check if we need to run this loop
	tst.l	 d5
	beq	 	 pre_carry
loop1:
	// INIT
	moveq	 #0, d7

	// CORE
	move.l	 (a2)+, d1
	mulu.l	 d0, d4:d1
	add.l	 d3, d1
	addx.l	 d7, d4
	moveq	 #0, d3
	add.l	 d1, (a3)+
	addx.l	 d4, d3

	// STOP
	subq.l	 #1, d5
	bne	 	 loop1
pre_carry:
	movea.l	 a3, a4
	move.l	 d3, d7
	move.l	 d3, d5
carry:
	add.l	 (a4), d7
	move.l	 d7, (a4)+
	cmp.l	 d5, d7
	scs	 	 d7
	extb.l	 d7
	neg.l	 d7
	move.l	 d7, d5
	bne	 	 carry
	movem.l	 (a7)+, d3-d7/a2-a4
	unlk	 a6
	rts
}