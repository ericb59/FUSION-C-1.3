; ___________________________________________________________
;/               __           _                              \
;|              / _|         (_)                             |
;|             | |_ _   _ ___ _  ___  _ __                   |
;|             |  _| | | / __| |/ _ \| '_ \                  |
;|             | | | |_| \__ \ | (_) | | | |                 |
;|             |_|  \__,_|___/_|\___/|_| |_| *               |
;|                                                           |
;|               The MSX C Library for SDCC                  |
;|                   V1.0 - 09-10-11 2018                    |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;|                                                           |
;\___________________________________________________________/
;
;
;

_Sprite32Bytes::
	push ix
	ld ix,#0
	add ix,sp
	ld l,4(ix)
	ld h,5(ix)
	pop ix

	inc	hl
	ld	de,#_spr_32b
	ld	c,#1
lb_spr0qrt:
	ld	b,#16
lb_spr1qrt:
	ld	a,(hl)
	ld	(de),a
	inc	hl
	inc	hl
	inc	de
	djnz	lb_spr1qrt
	dec	c
	jp	m,lb_sprQ4
	push	bc
	ld	bc,#33
	scf
	ccf
	sbc	hl,bc
	pop	bc
	jr	lb_spr0qrt
lb_sprQ4:
	ld	hl,#_spr_32b
	ret
	
		 .area	_XDATA

_spr_32b:	.ds #32