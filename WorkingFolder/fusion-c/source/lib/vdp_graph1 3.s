; ___________________________________________________________
;/               __           _                              \
;|              / _|         (_)                             |
;|             | |_ _   _ ___ _  ___  _ __                   |
;|             |  _| | | / __| |/ _ \| '_ \                  |
;|             | | | |_| \__ \ | (_) | | | |                 |
;|             |_|  \__,_|___/_|\___/|_| |_| *               |
;|                                                           |
;|               The MSX C Library for SDCC                  |
;|                   V1.0 - 09-10-11 2018                    |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;|                                                           |
;\___________________________________________________________/
;
;
;
;	VDPgraph1.h	- MSX1 graphics VDP functions (also MSX2 compatible)
;
;	Compile on SDCC for MSX
;
;	This works on MSXDOS, not BASIC ROM
;	Copy pixel data from memory RAM to video memory VRAM by using chip built in functions.
;	No slow BASIC graphics, real game must load data, manage rectangles of pixels in memory.
;
;
;	Clear1px
;	Clear8px 
;	Get1px 
;	Get8px
;	GetCol8px 
;	SC2Paint 
;	Set1px
;	Set8px 
;	SetCol8px 
;

	.area _CODE

	
GRPACX		.equ	#0xFCB7
GRPACY		.equ	#0xFCB9 
FORCLR		.equ  	#0xF3E9         ; foreground color 


.area	_CODE
;---------------------------------------- 2 pixel writing/reading mode	
;
; VDP write/read at address
;
_pos_XY:		; Procedure calculates hl offset and sets VDP for writing
	di
	ld	a,e	; e=y[0..191]
	and	#248	; /8
	rra
	rra
	rra
	ld	h,a	; each 8 lines = 256 bytes
	ld	a,d	; d=x[0..255]
	and	#248
	ld	l,a	; + 8*int(x/8)
	ld	a,e
	and	#7
	or	l	; + y mod 8
	ld	l,a
	ei
	ret


_VDPread1:
	xor	a
	push	ix
	.db	#0xF7	; RST 30h
	.db	#0x80
	.dw	#0x0050		; SETRD Sets up the VDP for reading with HL address
	pop	ix
	ret

_VDPwrite1:
	xor	a
	push	ix
	.db	#0xF7	; RST 30h
	.db	#0x80
	.dw	#0x0053		; SETWRT Sets up the VDP for writing with HL address
	pop	ix
	ret   



;****************************************************************
; Get pattern at x,y.

;
; int Get8px(int X, int Y);
;
_Get8px::
	push ix
	ld ix,#0
	add ix,sp
	ld d,4(ix)
	ld e,6(ix)
	call	_igB8px
	ld	l,a
	ld	h,#0
	pop ix
	ret
;
; int Get1px(int X, int Y);
;
_Get1px::
	push ix
	ld ix,#0
	add ix,sp
	ld d,4(ix)
	ld e,6(ix)
	call	_iget1px
	pop ix
	ld	l,a
	ld	h,#0
	ret
_iget1px:
	ld	hl,#_px8bits
	ld	b,#0
	ld	a,d
	and	#7
	ld	c,a
	add	hl,bc
	ld	b,(hl)
	call	_igB8px
	and	b
	ret
	
;****************************************************************
; Set pattern at x,y.

;
; void set8px(int X, int Y);
;
_Set8px::
	push ix
	ld ix,#0
	add ix,sp
	ld d,4(ix)
	ld e,6(ix)
	ld b,#0xFF
	call	_iset8px
	pop ix
	ret
;
; void set1px(int X, int Y);
;
_Set1px::
	push ix
	ld ix,#0
	add ix,sp
	ld d,4(ix)
	ld e,6(ix)
	call	_iset1px
	pop ix
	ret
_iset1px:
	ld	hl,#_px8bits
	ld	b,#0
	ld	a,d
	and	#7
	ld	c,a
	add	hl,bc
	ld	b,(hl)
	call	_iset8px
	ret
	
_igB8px:		; get byte from VRAM
	push	bc
	call	_pos_XY
	call	_VDPread1
	call	_VDPget8pixels
	pop	bc
	ret
	
_iset8px:
	call	_igB8px
	or	b
	ld	c,a
	call	_VDPwrite1
	ld	a,c		; write new pattern of 8 pixels
	call	_VDPput8pixels
	ret

_VDPput8pixels:		; Put 8 pixels by sending one byte
	out (#0x98),a		; send this sequentially
	ret

_VDPget8pixels:           	; Get 8 pixels
	in	a,(#0x98)	; read this sequentially
	ret
;****************************************************************
; Clear pattern at x,y.

;
; void Clear8px(int X, int Y);
;
_Clear8px::
	push ix
	ld ix,#0
	add ix,sp
	ld d,4(ix)
	ld e,6(ix)
	ld b,#0x00
	call	_iset8px
	pop ix
	ret
	
;
; void Clear1px(int X, int Y);
;
_Clear1px::
	push ix
	ld ix,#0
	add ix,sp
	ld d,4(ix)
	ld e,6(ix)
	call	_iclear1px
	pop ix
	ret
_iclear1px:
	ld	hl,#_px8bits
	ld	b,#0
	ld	a,d
	and	#7
	ld	c,a
	add	hl,bc
	
	ld	a,(hl)
	xor	#0xFF		; invert
	ld	b,a
	call	_igB8px
	and	b		; remove pixel
	ld	c,a
	call	_VDPwrite1
	ld	a,c		; write new pattern of 8 pixels
	call	_VDPput8pixels	
	ret
	
	; .area	_XDATA

_px8bits:	.db #0x80,#0x40,#0x20,#0x10,#0x08,#0x04,#0x02,#0x01

.area	_CODE

;****************************************************************
; Get colour at x,y.
;	void	GetCol8px( int x, int y, pxColor *C )
;
_GetCol8px::
	push ix
	ld ix,#0
	add ix,sp
	ld d,4(ix)
	ld e,6(ix)
	ld l,8(ix)
	ld h,9(ix)
	push	hl
	pop	ix
	call	_igetCol8px
	ld	b,a
	xor	a
	ld	1(ix),#0
	ld	3(ix),#0
	ld	a,b
	and	#0x0F
	ld	2(ix),a
	ld	a,b
	and	#0xF0
	rra
	rra
	rra
	rra
	ld	0(ix),a
	pop ix
	ret
	
_igetCol8px:
	call	_pos_XY
	ld	bc,#0x2000	; colours are mapped +0x2000
	add	hl,bc
	call	_VDPread1
	call	_VDPget8pixels
	ret

;****************************************************************
; Set colour at x,y.
;	void	setCol8px( int x, int y, pxColor *C )
;
_SetCol8px::
	push ix
	ld ix,#0
	add ix,sp
	ld d,4(ix)
	ld e,6(ix)
	ld l,8(ix)
	ld h,9(ix)
	push	hl
	pop	ix
	ld	a,0(ix)
	rla
	rla
	rla
	rla
	or	2(ix)
	call	_isetCol8px
	pop ix
	ret
	
_isetCol8px:
	push	af
	call	_pos_XY
	ld	bc,#0x2000	; colours are mapped +0x2000
	add	hl,bc
	call	_VDPwrite1
	pop	af
	call	_VDPput8pixels
	ret	


	 
; This prepares for "pixeling",  HL contains initial address
_VDPwrite:
	xor	a
	push	ix
	.db	#0xF7	; RST 30h
	.db	#0x80
	.dw	#0x0053		; SETWRT Sets up the VDP for writing with HL address
	pop	ix
	ret         




_VDPread:
	xor	a
	push	ix
	.db	#0xF7	; RST 30h
	.db	#0x80
	.dw	#0x0050		; SETRD Sets up the VDP for reading with HL address
	pop	ix
	ret
	

	


;****************************************************************
;	Set coloured pixel at x,y
;	Ignore 8pt same colour scheme. 
;
;	void	PSET( int x, int y, int color )
;

_OLDSC2Pset::
	push ix
	ld ix,#0
	add ix,sp
	ld d,4(ix)
	ld e,6(ix)
	ld b,8(ix)
	call	_ipset
	pop ix
	ret
_ipset:	
	push	bc
	ld	a,(#_ln_y8px)
	or	a
	jr	z,lb_lnpset
	xor	a
	ld	(#_ln_y8px),a
	ld b,#0xFF
	call	_iset8px
	jr	lb_lnpcol
lb_lnpset:	
	call	_iset1px
lb_lnpcol:
	call	_igetCol8px
	and	#0x0F
	ld	c,a
	pop	af
	and	#0x0F
	rla
	rla
	rla
	rla
	or	c
	ld	c,a
	call	_VDPwrite
	ld	a,c
	call	_VDPput8pixels
	ret

_ipsetsv:			; saves registers
	push	de
	push	hl
	push	bc
	call	_ipset
	pop	bc
	pop	hl
	pop	de
	ret
	
;****************************************************************
;	Get coloured pixel at x,y
;	Ignore 8pt same colour scheme. 
;
;	int	POINT( int x, int y )
;
		
_OLDSC2Point::
	push ix
	ld ix,#0
	add ix,sp
	ld d,4(ix)
	ld e,6(ix)
	call	_ipoint
	pop ix
	ld	l,a
	ld	h,#0
	ret
_ipoint:	
	call	_iget1px
	or	a
	jr	z,lb_Pt0
	call	_igetCol8px
	rra
	rra
	rra
	rra
	jr	lb_PtExt
lb_Pt0:
	call	_igetCol8px
lb_PtExt:
	and	#0x0F
	ret
	

	
;---------------------------
; Paints from the point (x:H, y:L), color:E
; Not 100% correct. Basic has better PAINT code.
; There is SRCH (colour code search) VDP algorithm that
; should be implemented here instead of this crap.
;
_SC2Paint::
	
	push ix
	ld ix,#0
	add ix,sp
	
	ld h,4(ix)
	ld l,6(ix)
	ld e,8(ix)
	pop ix
	
		; this is way to limit stack depth, it is better then dumb crash
_ptAgain:	
	ld	bc, #0x2000	; calculate depth, limit
	call	_paintRR
	
	ld	hl,(#_lpaintHL)
	ld	a,b
	or	c
	jr	z,_ptAgain	; if bc==0 then try paint at last position
	ret
	
_paintRR:
	push	hl
	push	de
	push	bc
	ld	b,e
	ex	de,hl		; de = X,Y
	call	_ipset
	pop	bc
	pop	de
	pop	hl
	ld	(#_lpaintHL),hl	; will continue after all returns (Call SP>SP>SP...>..0x8000 crash at)
lb_ptY0:	
	ld	a,l
	or	a
	jr	z,lb_ptX0
	dec	l
	call	recIfPaint
	inc	l
lb_ptX0:	
	ld	a,h
	or	a
	jr	z,lb_ptY2
	dec	h
	call	recIfPaint
	inc	h
lb_ptY2:
	ld	a,l
	cp	#191
	jr	z,lb_ptX2
	inc	l
	call	recIfPaint
	dec	l
lb_ptX2:
	ld	a,h
	cp	#255
	jr	z,lb_ptOk
	inc	h
	call	recIfPaint
	dec	h	
lb_ptOk:
	ld	a,b
	or	c
	ret	z	; if bc==0 then just return
	jr	lb_rbc

recIfPaint:
	ld	a,b
	or	c
	ret	z	; if bc==0 then just return
	
	dec	bc	
	push	hl
	push	de
	push	bc
	ex	de,hl		; de = X,Y
	call	_iget1px
	pop	bc
	pop	de
	pop	hl
	or	a
	jr	nz,lb_rbc
	jp	_paintRR 
lb_rbc:
	inc	bc
	ret

;.area	_XDATA
_lpaintHL:	.dw #0
_ln_yy0:	.db #0
_ln_y8px:	.db #0