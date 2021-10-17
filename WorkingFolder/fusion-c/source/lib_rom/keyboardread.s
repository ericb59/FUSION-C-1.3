; ___________________________________________________________
;/               __           _                              \
;|              / _|         (_)                             |
;|             | |_ _   _ ___ _  ___  _ __                   |
;|             |  _| | | / __| |/ _ \| '_ \                  |
;|             | | | |_| \__ \ | (_) | | | |                 |
;|             |_|  \__,_|___/_|\___/|_| |_| *               |
;|                                                           |
;|               The MSX C Library for SDCC                  |
;|                   V1.3 - 03 - 2020                        |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;|                                                           |
;\___________________________________________________________/
;------------------------------------------------
;	RKeys
;	Fkeys §
;-----------------------------------------------
_Rkeys::
			
			ld	a,(#0xFBED)				; Read in System Vars, status of line 8 of the Keymatrix
			xor #0xFF	
			ld	l,a 					; Return a byte with status of keys : Right Key - Down Key - Up Key - Left Key - DEL - INS - HOME - SPACE
			ld	h,#0					; Status = 1 key pressed   0 : Key Not pressed
			ret 


_Fkeys::
			ld a,(#0xFBEB)				; Read in System Vars, status of line 6 and 7 of the Keymatrix
			xor #0xFF					; Return a byte with status of keys : STOP - GRAPH - ESC - F5 - F4 - F3 - F2 - F1
			rra							; Status = 1 key pressed   0 : Key Not pressed
			rra
			rra
			rra
			rra
			and #0b01000111
			ld b,a
			ld a,(#0xFBEC)
			xor #0xFF
			rla
			rla
			rla
			and #00011000
			or b 
			ld l,a 
			ld h,#0
			ret
