;------------------------------------------------------------------------------
;  █▀▀ █▀▄▀█ █▀ ▀▄▀
;  █▄▄ █ ▀ █ ▄█ █ █ v0.2
;------------------------------------------------------------------------------
; crt0 header for 32KB ROM
; 
; Code address: 0x4010
; Data address: 0xC000
;------------------------------------------------------------------------------
.module	crt0

.globl	_main
.globl  l__INITIALIZER
.globl  s__INITIALIZED
.globl  s__INITIALIZER
.globl  s__HEAP

HIMEM = #0xFC4A
PPI_A = #0xA8

;------------------------------------------------------------------------------
.area	_HEADER (ABS)
	.org	0x4000

	; ROM header
	.db		0x41
	.db		0x42
	.dw		init
	.dw		0x0000
	.dw		0x0000
	.dw		0x0000
	.dw		0x0000
	.dw		0x0000
	.dw		0x0000

;------------------------------------------------------------------------------
.area	_CODE

init:
	di
	; Set stack address at the top of free memory
	ld		sp, (HIMEM)
	
	; Set Page 2 slot equal to Page 1 slot
	in		a, (PPI_A)
	and		a, #0xCF
	ld		c, a
	in		a, (PPI_A)
	and		a, #0x0C
	add		a, a
	add		a, a
	or		a, c
	out		(PPI_A), a
	
	; Initialize globals
    ld		bc, #l__INITIALIZER
	ld		a, b
	or		a, c
	jp		z, start	
	ld		de, #s__INITIALIZED
	ld		hl, #s__INITIALIZER
	ldir

	; Initialize heap address
	;ld		hl, #s__HEAP
	;ld		(#_g_HeapStartAddress), hl

start:
	; start main() function
	ei
	call	_main
	rst		0


;------------------------------------------------------------------------------
; Ordering of segments for the linker

;-- ROM --
.area	_HOME
.area	_CODE
.area	_INITIALIZER 
.area   _GSINIT
.area   _GSFINAL
;-- RAM --
.area	_DATA
;_g_HeapStartAddress::
;	.ds 2
	
.area	_INITIALIZED
.area	_BSEG
.area   _BSS
.area   _HEAP