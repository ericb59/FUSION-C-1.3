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
;	vram to Ram Memory block transfert & Ram to Vram Memory Block Transfert
;
;	Port of the MSX-C ' Ascii routine
;
;	Eric Boez 2019
;
;	GetVramSize
;
;

 .area _CODE

 MODE	=	0xFAFC

;---------------------------
;	 MODULE	GetVramSize          Eric Boez 2019
;	Return the VRAM Size of the MSX Computer 16/64 or 128 KB
;	Definition : char    GetVramSize(void)
_GetVramSize::
	push ix
	ld	a,(MODE)
	and	#0b00000110		; extract VRAM size
	ld	hl,#16			; assume 16K (MSX1)
	ret	z				; good assumption
	cp	#0b00000010		; 64K?
	ld	l,#64			; assume so
	ret	z				; good assumption
	add	hl,hl			; 128K
	pop ix
	ret