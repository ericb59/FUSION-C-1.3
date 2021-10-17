; ___________________________________________________________
;/               __           _                              \
;|              / _|         (_)                             |
;|             | |_ _   _ ___ _  ___  _ __                   |
;|             |  _| | | / __| |/ _ \| '_ \                  |
;|             | | | |_| \__ \ | (_) | | | |                 |
;|             |_|  \__,_|___/_|\___/|_| |_| *               |
;|                                                           |
;|               The MSX C Library for SDCC                  |
;|                   V1.3 -  03-04 2020                      |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;|                                                           |
;\___________________________________________________________/
; VDPwrite Functions
;
;	VDP60Hz



RG1SAV = 0xF3E0 
DPPAGE = 0xFAF5 
ATRBAS = 0xF928 
RG25SAV = 0xFFFA
RG2SAV = 0xF3E1
RG8SAV = 0xFFE7
RG9SAV = 0xFFE8 


	.area _CODE

;----------------------------
;   MODULE  VDP60Hz
;
;   void VDP60Hz(void)
;   
;   MSX2 and upper
;   
;
_VDP60Hz::
	ld a,(RG9SAV)
	and #0b11111101
	ld (RG9SAV),a
	ld b,a
	ld a,#9
	or #0x80
	ld		c, #0x99		;;	VDP port #1 (unsupport "MSX1 adapter")
	out		(c), b			;;	out data
	out		(c), a			;;	out VDP register number
	ret





