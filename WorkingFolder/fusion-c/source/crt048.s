; ___________________________________________________________
;/               __           _                              \
;|              / _|         (_)                             |
;|             | |_ _   _ ___ _  ___  _ __                   |
;|             |  _| | | / __| |/ _ \| '_ \                  |
;|             | | | |_| \__ \ | (_) | | | |                 |
;|             |_|  \__,_|___/_|\___/|_| |_| *               |
;|                                                           |
;|               The MSX C Library for SDCC                  |
;|                 V1.3 -   December 2020                    |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;|                                                           |
;\___________________________________________________________/
;
; CRT0 for MSX 32KB ROM
; What this crt0 do : Init Global variables, Init Rom Page 2
;
; Compilation option : --code-loc 0x4023 --data-loc 0xC000
;
 
.module	crt0

.globl	_main
.globl  l__INITIALIZER
.globl  s__INITIALIZED
.globl  s__INITIALIZER
.globl  s__HEAP

RSLREG		.equ 0x0138
EXPTBL		.equ 0xfcc1
SLOT_SEL	.equ 0xa8
SUBSLOT_SEL	.equ 0xffff

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

init:
	; Set stack address at the top of free memory
	ld   SP,(#0xFC4A)	; 0xF380 or 0xF379

	ld	bc, #l__INITIALIZER
	ld	a, b
	or	a, c
	jr	Z, start
	ld	de, #s__INITIALIZED
	ld	hl, #s__INITIALIZER
	ldir
	
;; Ordering of segments for the linker.
	.area	_HOME
	.area	_CODE
	.area	_INITIALIZER
	.area   _GSINIT
	.area   _GSFINAL

	.area	_DATA
	.area	_INITIALIZED
	.area	_BSEG
	.area   _BSS
	.area   _HEAP

	.area   _CODE	

start:
	call bootstrap
	call	_main
	rst		0

_sys_set_rom::
		push ix
		di
		ld	a,(romslot)
		ld	h,#0x00
		call	enaslt
		pop ix
		ret
_sys_set_bios:
		push ix
		ld	a,(biosslot)
		ld	h, #0x00
		call	enaslt
		ei
		pop ix
		ret

		; set slot and subslot at target address
		; (from msx bios listing)
		; hl - target address
		; a  - slot : FxxxSSPP
		;             F  : expanded slot flag (if F=0, SS is ignored)
		;             SS : expanded subslot
		;             PP : primary slot
enaslt:
		call selprm         ; calculate bit pattern and mask code
		jp m, eneslt        ; if expanded set secondary first
		in a,(SLOT_SEL)
		and c
		or b
		out (SLOT_SEL),a        ; set primary slot
		ret
eneslt:
		push hl
		call selexp         ; set secondary slot
		pop hl
		jr enaslt

		; calculate bit pattern and mask
selprm:
		di
		push af
		ld a,h
		rlca
		rlca
		and #3
		ld e,a              ; bank number
		ld a,#0xC0
selprm1:
		rlca
		rlca
		dec e
		jp p, selprm1
		ld e,a              ; mask pattern
		cpl
		ld c,a              ; inverted mask pattern
		pop af
		push af
		and #3              ; extract xxxxxxPP
		inc a
		ld b,a
		ld a,#0xAB
selprm2:
		add a,#0x55
		djnz selprm2
		ld d,a              ; primary slot bit pattern
		and e
		ld b,a
		pop af
		and a               ; if expanded slot set sign flag
		ret

		; set secondary slot
selexp:
		push af
		ld a,d
		and #0xC0          ; get slot number for bank 3
		ld c,a
		pop af
		push af
		ld d,a
		in a,(SLOT_SEL)
		ld b,a
		and #0x3F
		or c
		out (SLOT_SEL),a        ; set bank 3 to target slot
		ld a,d
		rrca
		rrca
		and #3
		ld d,a
		ld a,#0xAB          ; secondary slot to bit pattern
selexp1:
		add a,#0x55
		dec d
		jp p,selexp1
		and e
		ld d,a
		ld a,e
		cpl
		ld h,a
		ld a,(SUBSLOT_SEL)       ; read and update secondary slot register
		cpl
		ld l,a
		and h               ; strip off old bits
		or d                ; add new bits
		ld (SUBSLOT_SEL),a
		ld a,b
		out (SLOT_SEL),a        ; restore status
		pop af
		and #3
		ret

		; The following code sets bank 2 to the same slot as bank 1 and continues
		; execution.
bootstrap:

		
nopret:		
		call 	#RSLREG
		call 	getslot
		ld	(biosslot),a
		call 	#RSLREG
		rrca
		rrca
		call 	getslot
		ld	(romslot),a
		ld	h,#0x80
		call 	enaslt
		jp 	done
getslot:
		and	#0x03
		ld	c,a
		ld	b,#0
		ld	hl,#EXPTBL
		add	hl,bc
		ld	a,(hl)
		and	#0x80
		jr	z,exit
		or	c
		ld	c,a
		inc	hl
		inc	hl
		inc	hl
		inc	hl
		ld	a,(hl)
		and	#0x0C
exit:
		or	c
		ret
done:
	ret
		.area _DATA
romslot:	.ds 1
biosslot:	.ds 1