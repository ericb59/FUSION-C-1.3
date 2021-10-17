; ___________________________________________________________
;/               __           _                              \
;|              / _|         (_)                             |
;|             | |_ _   _ ___ _  ___  _ __                   |
;|             |  _| | | / __| |/ _ \| '_ \                  |
;|             | | | |_| \__ \ | (_) | | | |                 |
;|             |_|  \__,_|___/_|\___/|_| |_| *               |
;|                                                           |
;|               The MSX C Library for SDCC                  |
;|                     V1.2a   -  11-2019                    |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;|                                                           |
;\___________________________________________________________/
;
;
;	SetVDPread
;	SetVDPwrite
;
;	Port of the MSX-C ' Ascii routine
;
;	Eric Boez 2019

 .area _CODE

VDPIO   = 	0x98 			;VRAM Data (Read/Write)
VDPSTATUS = 0x99 		;VDP Status Registers 
EXBRSA	=	0xFAF8
SCRMOD	=	0xFCAF
ACPAGE	=	0xFAF6
MODE	=	0xFAFC
ATRBAS  =   0xF928
;---------------------------
;	MODULE	SetVDPread          Eric Boez 2019
;	Definition : SetVDPread(unsigned int address);
;
;	sets up the VDP for read.
;	Entry:	HL.
;	Exit:	None.
;
;
_SetVDPread::
	call	SETADRESS
	ei
	out	(c),a
	dec	c
	ret




;---------------------------
;	MODULE	SetVDPWrite          Eric Boez 2019
;	Definition : SetVDPwrite(unsigned int address);
;	sets up the VDP for write.
;	Entry:	HL.
;	Exit:	None.
;
_SetVDPwrite::
	call	SETADRESS
	or	#0b01000000		;set the low address with write bit
	ei
	out	(c),a
	dec	c
	ret



;----------------------------
;   MODULE	SETADR
;
;	low level routine for SETRD and SETWRT
;
;	entry:		HL = read/write address
;
;	Used internally
;

SETADRESS:
	push	de
	ld	a,#VDPIO
	ld	c,a
	inc	c
	ld	a,(EXBRSA)			; MSX1?
	and	a
	jr	z,setaddress_1a		; yes
	ld	a,h					; extract the high address
	rlca
	rlca
	and	#0b00000011
	ld	d,a					; save a15,a14
	ld	a,(SCRMOD)
	cp	#7
	ld	a,(ACPAGE)
	jr	c,set_high1a			; page size is 32k
	add	a,a
set_high1a:
	add	a,a
	add	a,d
	di
	out	(c),a				; set data to be written
	ld	a,#0x80+#14			; set it to register #14
	out	(c),a
setaddress_1a:
	di
	out	(c),l				; set the low address
	ld	a,h					; prepare to set the middle address
	and	#0b00111111
	pop	de
	ret