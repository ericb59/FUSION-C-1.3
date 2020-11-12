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
;|                   V1.2 - 14/04/2020                       |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|                V1.2 - Oduvaldo Pavan Junior               |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;|                                                           |
;\___________________________________________________________/
;
; 
;	IO.H
;	Disk operations
;	
;	(c) 1995, SOLID MSX C
;
;	SDCC port 2015
;
;	MSXDOS1, MSXDOS2 disk operations
;
;	DiskLoad 
;
;

	.area _CODE

;
;	Diskload - load binary file from disk to RAM.
;
;	Compile on SDCC for MSX 
;

		.area _CODE
		
_DiskLoad::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	l,4(ix)
	ld	h,5(ix)
	ld	e,6(ix)
	ld	d,7(ix)
	ld	c,8(ix)
	ld	b,9(ix)
	
	push	bc
	push	de
	
	ld	a,#1
	ld	(#loadflag),a

		; prepare FCB
	push	hl
	ld	hl,#f_fcb
	ld	de,#f_fn
	push	de
	ld	bc,#36
	xor	a
	ld	(hl),a
	ldir
	pop	de
	pop	hl

		; copy filename into FCB
	ld	bc,#11
	ldir

		; open file for reading
	ld	de,#f_fcb
	ld	c, #0xF
	call	#5

	ld	hl,#1
	ld	(#f_groot),hl
	dec	hl
	ld	(#f_blok),hl
	ld	(#f_blok+#2),hl
	
	ld	hl,(#f_bleng)	; obtain file size
	pop	de
	push	hl
		; set writing to RAM address
	ld	c,#0x1A
	call	#5
	pop	hl
	
		; read from file
	ld	de,#f_fcb
	ld	c,#0x27
	call	#5
	ld      (#loadflag),a  ;sets 0 if ok, 1 if can not load 
	
	ld	de,#f_fcb
	ld	c,#0x10
	call	#5

	pop	bc
	ld	(#lb_calladdr),bc
	
	pop	ix
	
	xor	a
	or	b
	or	c
	jr	z, lb_exit_
			
	.db	#0xCD	; call to address
lb_calladdr:
	.db	#0
	.db	#0
	
lb_exit_:
	ld	a,(#loadflag)
	ld	l,a
	ld	h,#0
	ret
	
;	.area _DATA

loadflag:	.db #0

f_fcb:		.db	#0
f_fn:		.ascii	"???????????"   ;11 chars          
		.dw	#0
f_groot:	.dw	#0
f_bleng:	.ds	#17
		
f_blok:		.dw	#0
		.dw	#0
	.db	#0