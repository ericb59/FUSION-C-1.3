/*
 ___________________________________________________________
/               __           _                              \
|              / _|         (_)                             |
|             | |_ _   _ ___ _  ___  _ __                   |
|             |  _| | | / __| |/ _ \| '_ \                  |
|             | | | |_| \__ \ | (_) | | | |                 |
|             |_|  \__,_|___/_|\___/|_| |_| *               |
|                                                           |
|               The MSX C Library for SDCC                  |
|                   V1.2a   -  11-2019                      |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|          C   &   A S M    S O U R C E   C O D E           |
|					    	P S G 							|
|                                                           |
\___________________________________________________________/
|
|     2019-2020 Eric Boez
|
|	CopyVramToRam2  (Only for MSX2 and upper) No Interrupt
|
*/

#define FUSION 2020
#include "../../header/msx_fusion.h"


void 	CopyRamToVram2NI(void *SrcRamAddress, unsigned int DestVramAddress, unsigned int Length) __naked
{
	SrcRamAddress,DestVramAddress,Length;

__asm

;---------------------------
;	MODULE	COPY RAM TO VRAM MSX2 VErsion No Interrupt 
;
;		moves block from memory to the VRAM.
;

			push ix
		 	
		    ld   ix,#0
		    add  ix,sp

		  	ld   l,6(ix) ; DEST VRAM address
  			ld   h,7(ix)
	
		setvdp_write: 
			ld	c,#0x99
			ld	a,h					; extract the high address
			rlca
			rlca
			and	#0b00000011
			ld	d,a					; save a15,a14
			ld	a,(0xFCAF)
			cp	#7
			ld	a,(0xFAF6)
			jr	c,set_high11a		; page size is 32k
			add	a,a
		set_high11a:
			add	a,a
			add	a,d
			;di
			out	(c),a				; set data to be written
			ld	a,#0x80+#14			; set it to register #14
			out	(c),a
			out	(c),l				; set the low address
			ld	a,h					; prepare to set the middle address
			and	#0b00111111
			or	#0b01000000			;set the low address with write bit
			;ei
			out	(c),a
			
			;--------------------------------------
			ld  l,4(ix) 			; SRC RAM address  
		  	ld  h,5(ix)
			ld  e,8(ix) 			; Block length
		  	ld  d,9(ix)
		  	;ei 
		  	dec c
			ld	b,e					; set lower byte of length
			ld	a,d					; set higher byte of length

			otir					; send first bytes
		
		copy_loop_start:
			cp		a,#0
			jp		z,copy_loop_end

			ld		b,#0			; send 256 bytes 

			otir

			dec		a
			jp		copy_loop_start
		copy_loop_end:
		
			pop	ix
			ret

__endasm;
}