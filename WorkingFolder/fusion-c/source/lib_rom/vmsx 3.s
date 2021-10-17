; ___________________________________________________________
;/               __           _                              \
;|              / _|         (_)                             |
;|             | |_ _   _ ___ _  ___  _ __                   |
;|             |  _| | | / __| |/ _ \| '_ \                  |
;|             | | | |_| \__ \ | (_) | | | |                 |
;|             |_|  \__,_|___/_|\___/|_| |_| *               |
;|                                                           |
;|               The MSX C Library for SDCC                  |
;|                     V1.3 - 02 - 2020                      |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;|                                                           |
;\___________________________________________________________/
;
;
;----------------------------------------------------------------------------;
; Simply check MSX1 or MSX2 without touching VDP                   			 ;
;----------------------------------------------------------------------------
;
EXBRSA = 0xFAF8	

_vMSX::
	ld	a, (EXBRSA)	; do not touch TMS9918A of MSX1, just obtain technical slot presence
	or	a
	jp	nz, lb_vrYm
				; MSX1
	ld	de, #_MSX1_err_
	ld	c, #9
	call	#5	; display "MSX1 not supported"
	ld	a,#1
	jp	lb_vrEx

lb_vrYm:
	ld	a,#2		; MSX2 and above
lb_vrEx:
	ld	l,a
	ld	h,#0
	ret


_MSX1_err_:	.ascii "MSX1 not supported\n"
_curHL:		.dw #0