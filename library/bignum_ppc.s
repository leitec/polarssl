# This is an ASM rewrite of the mpi_mul_hlp function.
# This is a little bit faster than the GCC-compiled
# version in bignum_ppc.c.
#
# The core of the multiplication is still done with the
# instructions provided with PolarSSL (MULADDC_CORE) but
# since we are not doing inline ASM we can be a little
# more efficient. Namely, we don't waste any time
# repeatedly reading and writing to memory with each
# iteration of each loop.
#
# This works under OS X, too, and provides a speedup
# there as well.
#
# -leitec, 2013

	export .mpi_mul_hlp_powerpc_ours
.mpi_mul_hlp_powerpc_ours:
	mr r10, r3
	mr r3, r4
	mr r4, r5
	li r5, 0

	cmplwi cr0, r10, 16
	blt bpreloop8

	addi r12,r10,-16
	rlwinm r12,r12,28,4,31
	addi r12,r12,1
	mtctr r12
bloop16:
	addi r3, r3, -4
	addi r4, r4, -4
	addic r5, r5, 0
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	addze	r5, r5
	addi	r4, r4, 4
	addi	r3, r3, 4			
	addi r10, r10, -16
	bdnz bloop16
bpreloop8:
	cmplwi	cr0, r10, 8
	blt bpreloop1
	addi r12,r10,-8
	rlwinm r12,r12,29,3,31
	addi r12,r12,1
	mtctr r12
bloop8:
	addi	r3, r3, -4
	addi	r4, r4, -4
	addic	r5, r5, 0
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	addze	r5, r5
	addi	r4, r4, 4
	addi	r3, r3, 4	
	addi r10, r10, -8
	bdnz bloop8
bpreloop1:
	cmpwi cr0, r10, 0
	beq bdone
	mtctr r10
bloop1:
	addi	r3, r3, -4
	addi	r4, r4, -4
	addic	r5, r5, 0
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)    	
	addze	r5, r5
	addi	r4, r4, 4
	addi	r3, r3, 4
	bdnz bloop1
bdone:
bloopD:
	lwz	r11, 0(r4)
	add	r11,r11,r5
	stw	r11, 0(r4)
	cmplw	r11, r5
	blt	d1
	li	r5, 0
	b	d2
d1:
	li	r5, 1		
d2:
	addi	r4, r4, 4
	cmpwi	cr0, r5, 0
	bne bloopD
	blr
