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
;	VDPwriteNi
;	VDPwrite



RG1SAV = 0xF3E0 
DPPAGE = 0xFAF5 
ATRBAS = 0xF928 
RG25SAV = 0xFFFA
RG2SAV = 0xF3E1
RG8SAV = 0xFFE7
RG9SAV = 0xFFE8 


	.area _CODE
;----------------------------
;   MODULE  VDPwriteNi
;
;   void VDPwriteNi( unsigned char vdpreg, unsigned char data );
;   
;   Write to the VDP with no Disabled interrupt
;   
;

_VDPwriteNi::
	ld		hl, #2
	add		hl, sp

	ld		a, (hl)			;;	port
	or		#0x80
	inc		hl
	ld		b, (hl)			;;	parameter
_DoWriteNI:
	ld		c, #0x99		;;	VDP port #1 (unsupport "MSX1 adapter")
	out		(c), b			;;	out data
	out		(c), a			;;	out VDP register number
	ret



;----------------------------
;   MODULE  VDPwrite
;
;   void VDPwrite( unsigned char vdpreg, unsigned char data );
;   
;   Write to the VDP with   interrupt disabled
;   
;

_VDPwrite::
	ld		hl, #2
	add		hl, sp

	ld		a, (hl)			;;	port
	or		#0x80
	inc		hl
	ld		b, (hl)			;;	parameter
_DoWrite:
	ld		c, #0x99		;;	VDP port #1 (unsupport "MSX1 adapter")
	di
	out		(c), b			;;	out data
	ei
	out		(c), a			;;	out VDP register number

	ret



































