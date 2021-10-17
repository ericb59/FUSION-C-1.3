; ___________________________________________________________
;/               __           _                              \
;|              / _|         (_)                             |
;|             | |_ _   _ ___ _  ___  _ __                   |
;|             |  _| | | / __| |/ _ \| '_ \                  |
;|             | | | |_| \__ \ | (_) | | | |                 |
;|             |_|  \__,_|___/_|\___/|_| |_| *               |
;|                                                           |
;|               The MSX C Library for SDCC                  |
;|                   V1.3 - 12/12/2020                       |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;|                                                           |
;\___________________________________________________________/
;
; GetOSversion For MSX-DOS. 


	.area _CODE

_GetOSversion::

	call checkOS
	ld	h, #0
	ret
	
checkOS:	
	ld	c,#0xC
	call	#5
	cp	#5
	jr	z,LBVC

	ld	bc,#0x6F
	call	#5
	ld	a,b				;MSX-DOS kernel version
	cp	#2
	jr	c,LBVC
	ld	l,#2
	ret

LBVC:
	ld	l,#1
	ret