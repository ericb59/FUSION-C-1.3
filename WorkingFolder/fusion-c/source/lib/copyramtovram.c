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
|	CopyVramToRam
|
*/

#define FUSION 2019
#include "../../header/msx_fusion.h"


void 	CopyRamToVram(void *SrcRamAddress, unsigned int DestVramAddress, unsigned int Length) __naked
{
	SrcRamAddress,DestVramAddress,Length;

__asm

;---------------------------
;	MODULE	LDIRVM
;
;	LDIRVM	moves block from memory to the VRAM.
;

	push ix
 	di
    ld   ix,#0
    add  ix,sp
	ld   E,4(ix) ; SRC RAM address  
  	ld   D,5(ix)
  	ld   L,6(ix) ; DEST VRAM address
  	ld   H,7(ix)

  	ld   C,8(ix) ; Block length
  	ld   B,9(ix)


	push	bc		; save length
	call	_SetVDPwrite
	ex	de,hl		; HL = pointer to source
	pop	de			; DE = length
					; C  = VDPIO
	ld	b,e			; set lower byte of length
	ld	a,d			; set higher byte of length
	inc	e			; is lower byte of length 0?
	dec	e
	jr	z,ldirvm_1	; yes
	inc	a
ldirvm_1:
	outi			; OTIR cannot be used (VDP may fail)
	jp	nz,ldirvm_1
	dec	a
	jp	nz,ldirvm_1
	ei
	pop  ix
	ret

__endasm;
}