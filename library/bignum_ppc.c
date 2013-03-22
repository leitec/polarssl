#include "polarssl/config.h"

#include "polarssl/bignum.h"
#include "polarssl/bn_mul.h"

#if defined(macintosh) && defined(__powerc)
/*
 * CW Pro 1 doesn't have inline assembly support.
 * This is mpi_mul_hlp as compiled by gcc on Tiger,
 * with inline ASM code enabled. Using the whole
 * routine like this saves us from having to make
 * several different functions to support ASM
 * bignum and may be more efficient.
 *
 * I don't know what CW's default alignment is, so this may
 * be sub-optimal depending on what GCC sets. I'll have to look
 * into that sometime.
 *
 * I only had to change any use of r2, since CW/MacOS
 * doesn't like that. It's now r12. I also removed the
 * part at the beginning that loads the parameters, since
 * CW sets that up for us.
 */

asm void mpi_mul_hlp_powerpc_gcc(size_t i, t_uint *s, t_uint *d, t_uint b);
 
asm void mpi_mul_hlp_powerpc_gcc(size_t i, t_uint *s, t_uint *d, t_uint b)
{
	t_uint c;

	cmplwi cr7,r3,15
	li r0,0
	mr r11,r3
	stw r0,c
	ble cr7,L372
	addi r12,r3,-16
	rlwinm r12, r12, 28, 4, 31
	addi r12,r12,1
	mtctr r12
L385:
	lwz    r3, s        
	lwz    r4, d         
	lwz    r5, c         
	lwz    r6, b         
	addi   r3, r3, -4     
	addi   r4, r4, -4     
	addic  r5, r5,  0     
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
	addze  r5, r5         
	addi   r4, r4, 4      
	addi   r3, r3, 4      
	stw    r3, s         
	stw    r5, c         
	stw    r4, d         
	addi r11,r11,-16
	bdnz L385
L372:
	cmplwi cr7,r11,7
	ble cr7,L375
	addi r12,r11,-8
	rlwinm r12, r12, 29, 3, 31
	addi r12,r12,1
	mtctr r12
L386:
	lwz    r3, s         
	lwz    r4, d         
	lwz    r5, c         
	lwz    r6, b         
	addi   r3, r3, -4     
	addi   r4, r4, -4     
	addic  r5, r5,  0     
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
	addze  r5, r5         
	addi   r4, r4, 4      
	addi   r3, r3, 4      
	stw    r3, s         
	stw    r5, c         
	stw    r4, d         
	addi r11,r11,-8
	bdnz L386
L375:
	cmpwi cr7,r11,0
	beq cr7,L387
	mtctr r11
L380:
	lwz    r3, s         
	lwz    r4, d         
	lwz    r5, c         
	lwz    r6, b         
	addi   r3, r3, -4     
	addi   r4, r4, -4     
	addic  r5, r5,  0     
	lwzu   r7, 4(r3)      
	mullw  r8, r7, r6     
	mulhwu r9, r7, r6     
	adde   r8, r8, r5     
	lwz    r7, 4(r4)      
	addze  r5, r9         
	addc   r8, r8, r7     
	stwu   r8, 4(r4)      
	addze  r5, r5         
	addi   r4, r4, 4      
	addi   r3, r3, 4      
	stw    r3, s         
	stw    r5, c         
	stw    r4, d         
	bdnz L380
L387:
	lwz r9,d
	lwz r12,c
	lwz r0,0(r9)
	add r0,r0,r12
	stw r0,0(r9)
	lwz r12,d
	lwz r9,c
	lwz r0,0(r12)
	addi r12,r12,4
	stw r12,d
	subfc r0,r9,r0
	subfe r0,r0,r0
	neg r0,r0
	cmpwi cr7,r0,0
	stw r0,c
	bne cr7,L387
	blr
}
#endif