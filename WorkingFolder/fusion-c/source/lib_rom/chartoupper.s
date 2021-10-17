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
;	general types definition for ASCII or SOLID C
;
;	(c) 1995, SOLID MSX C
;
;	SDCC port 2015
;
;	CharToLower     




	.area _CODE

;--- proc 	TOUPPER
;
;	char	CharToUpper(char ch)
;
_CharToUpper::
	ld	hl, #2
	add	hl, sp
	ld	a,(hl)
	
	cp	#'a'
	jr	c, lb_z1
	cp	#'{'
	jr	nc, lb_z1
	sub	#' '
	ld	l,a
	ld	h,#0
	jr	lb_z2
lb_z1:
	ld	a,(hl)
lb_z2:
	ld	l,a
	ld	h,#0
	ret