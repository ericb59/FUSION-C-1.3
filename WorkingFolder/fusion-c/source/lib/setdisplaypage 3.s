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
;	SetDisplayPage




RG1SAV = 0xF3E0 
DPPAGE = 0xFAF5 
ATRBAS = 0xF928 
RG25SAV = 0xFFFA
RG2SAV = 0xF3E1
RG8SAV = 0xFFE7
RG9SAV = 0xFFE8 


	.area _CODE

;----------------------------
;   MODULE  SetDisplayPage
;
;   void SetDisplayPage(char n)
;   
;   MSX2 Show the specified VRAM Page at Screen
;   
;
_SetDisplayPage::
	
    ld  a,l
	rla
	rla
	rla
	rla
	rla
	and #0x7F
	or #0x1F
	ld b,a 
	ld a,#2
	or #0x80
	ld		c, #0x99		;;	VDP port #1 (unsupport "MSX1 adapter")
	di
	out		(c), b			;;	out data
	out		(c), a			;;	out VDP register number
	ei
	ld (DPPAGE),a
	ret


