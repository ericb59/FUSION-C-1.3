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


void 	CopyVramToRam(unsigned int SrcVramAddress, void *DestRamAddress, unsigned int Length) __naked
{
	SrcVramAddress,DestRamAddress,Length;

__asm

;------------------------------
; MODULE	LDIRMV
;
;	LDIRMV	moves block from VRAM to memory.
;
; Definition : CopyVramToRam(unsigned int SrcVramAddress, void *DestRamAddress, unsigned int Length);
;

	push ix
 	di
    ld   ix,#0
    add  ix,sp
	ld   E,4(ix) ; SRC VRAM address
  	ld   D,5(ix)
  	ld   L,6(ix) ; DEST RAM address 
  	ld   H,7(ix)

  	ld   C,8(ix) ; Block length
  	ld   B,9(ix)
  	pop ix
	push	bc		; save length
	ex	de,hl		; HL = pointer to source
	call	_SetVDPread
	ex	de,hl		; HL = pointer to destination
	pop	de			; DE = length
					; C  = VDPIO
	ld	b,e			; set lower byte of length
	ld	a,d			; set higher byte of length
	inc	e			; is lower byte of length 0?
	dec	e
	jr	z,ldirmv_1	; yes
	inc	a
ldirmv_1:
	ini				; INIR cannot be used (VDP may fail)
	jp	nz,ldirmv_1
	dec	a
	jp	nz,ldirmv_1
	ei
	
	ret

__endasm;
}