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
;	SetScrollH
;	SetScrollV



RG1SAV = 0xF3E0 
DPPAGE = 0xFAF5 
ATRBAS = 0xF928 
RG25SAV = 0xFFFA
RG2SAV = 0xF3E1
RG8SAV = 0xFFE7
RG9SAV = 0xFFE8 


	.area _CODE

;----------------------------
;   MODULE  SetScrollH
;
;   void SetScrollH(char n)
;   
;   MSX2+/Tr Hardware horizontal scroll
;   
;
_SetScrollH::

    ld a,#7
    sub a,l 
    ;ld a,l
    and #0b00000111
    ld b,a 
    ld a,#27
    or #0x80
    ld		c, #0x99		;;	VDP port #1 (unsupport "MSX1 adapter")
	di
	out		(c), b			;;	out data
	out		(c), a			;;	out VDP register number
	ei

    rr h
    ld a,l 
    rra 
    srl a
    srl a     
    
    ld b,a 
    ld a,#26
    or #0x80
    ld		c, #0x99		;;	VDP port #1 (unsupport "MSX1 adapter")
	di
	out		(c), b			;;	out data
	out		(c), a			;;	out VDP register number
	ei
    ret


;----------------------------
;   MODULE  SetScrollV
;
;   void SetScrollV(char n)
;   
;   MSX2 Hardware vertical scroll
;   
;
_SetScrollV::
	ld b,l
	ld a,#23
	or #0x80
	ld		c, #0x99		;;	VDP port #1 (unsupport "MSX1 adapter")
	di
	out		(c), b			;;	out data
	out		(c), a			;;	out VDP register number
	ei
	ret


