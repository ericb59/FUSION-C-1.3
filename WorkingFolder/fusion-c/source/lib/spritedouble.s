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
;	SpriteDouble
;	


;----------------------------
;   MODULE  SpriteDouble
;
;   void SpriteDouble(void)
;   
;   Activates the double pixels sprite mode
;   
;
RG1SAV = 0xF3E0 
DPPAGE = 0xFAF5 
ATRBAS = 0xF928 
RG25SAV = 0xFFFA
RG2SAV = 0xF3E1
RG8SAV = 0xFFE7
RG9SAV = 0xFFE8 

	.area _CODE
	
_SpriteDouble::
	ld a,(RG1SAV)
	or #0b00000001
	ld (RG1SAV),a
	ld b,a
	ld a,#0x80+#1
	ld c, #0x99		;;	VDP port #1 (unsupport "MSX1 adapter")
	di
	out	(c), b			;;	out data
	out	(c), a			;;	out VDP register number
	ei
	ret