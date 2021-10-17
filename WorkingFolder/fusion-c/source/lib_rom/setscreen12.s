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
;	SetScreen12



RG1SAV = 0xF3E0 
DPPAGE = 0xFAF5 
ATRBAS = 0xF928 
RG25SAV = 0xFFFA
RG2SAV = 0xF3E1
RG8SAV = 0xFFE7
RG9SAV = 0xFFE8 


	.area _CODE

;----------------------------
;   MODULE  SetScreen12
;
;   void SetScreen12(char n)
;   
;   MSX2+/Tr enable/disable  the screen12 Color coding bit YJK
;  
;
_SetScreen12::
	  ld a,l
    cp #0
    jp z,unset_12		; YES 0
  set_12:				; if 1 Set YJK bit
    ld a,(RG25SAV) 
    or #0b00001000 
    and #0b11101111
    jp J_continue
  unset_12:				; if 0 if 0 Unset Bits  YAE and YJK
     ld a,(RG25SAV) 
     and #0b11100111 
  J_continue:          
    ld (RG25SAV),a 
    ld b,a
    ld a,#25
    or #0x80
	ld		c, #0x99		;;	VDP port #1 (unsupport "MSX1 adapter")
	di
	out		(c), b			;;	out data
	out		(c), a			;;	out VDP register number
	ei
	ret

