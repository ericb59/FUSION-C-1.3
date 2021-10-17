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
;	SetTransparent


;----------------------------
;   MODULE  SetTransparent
;
;   void SetTransparent(void)
;   
;   Set the state of Color 0: Transparent or redefinable
;   MSX2 and upper
;

RG1SAV = 0xF3E0 
DPPAGE = 0xFAF5 
ATRBAS = 0xF928 
RG25SAV = 0xFFFA
RG2SAV = 0xF3E1
RG8SAV = 0xFFE7
RG9SAV = 0xFFE8 

 .area _CODE

 
_SetTransparent::
	ld a,l
    cp #0
    jp z,unset_tr		; YES 0
  set_tr:				; if 1 Set TP bit. No transparent mode. Color 0 is redefinable 
    ld a,(RG8SAV) 
    or #0b00100000
    jp tr_continue
  unset_tr:				; if 0 if 0 Unset TP Bits. Transparent mode on
     ld a,(RG8SAV) 
     and #0b11011111 
  tr_continue:          
    ld (RG8SAV),a 
    ld b,a
    ld a,#8				; R# number
    or #0x80
    ld		c, #0x99		;;	VDP port #1 (unsupport "MSX1 adapter")
	di
	out		(c), b			;;	out data
	out		(c), a			;;	out VDP register number
	ei
	ret


