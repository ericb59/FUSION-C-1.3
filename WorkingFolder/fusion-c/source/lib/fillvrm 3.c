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
|	FillVRM
|
*/

#define FUSION 2019
#include "../../header/msx_fusion.h"


void 	FillVRM(unsigned int adr, char data, unsigned int len) __naked
{
	adr,data,len;

__asm

; Other FillVram Function. Not using the Bios
; Fillvrm(adr, data, len)

	push ix
    ld   ix,#0
    add  ix,sp
	ld   L,4(ix) ; DEST VRAM address  
  	ld   H,5(ix)
  	ld   C,6(ix) ; Data
  	;ld   B,7(ix)
  	ld   E,7(ix) ; Length
  	ld   D,8(ix)

				;push	bc		; save data
	di
	call	_SetVDPwrite
	ld   l,6(ix) ; Data
				;pop	hl		;  L = data
				; DE = length
				;  C = VDPIO
	ld  c,#0x98
	ld	b,e		; set lower byte of length
	ld	a,d		; set higher byte of length
	inc	e		; is lower byte of length 0?
	dec	e
	jr	z,filvrm_1	; yes
	inc	a
filvrm_1:
	out	(c),l
	djnz	filvrm_1
	dec	a
	jp	nz,filvrm_1
	ei
	pop  ix
	ret

__endasm;
}