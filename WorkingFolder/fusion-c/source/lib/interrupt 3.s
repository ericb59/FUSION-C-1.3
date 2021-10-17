; ___________________________________________________________
;/               __           _                              \
;|              / _|         (_)                             |
;|             | |_ _   _ ___ _  ___  _ __                   |
;|             |  _| | | / __| |/ _ \| '_ \                  |
;|             | | | |_| \__ \ | (_) | | | |                 |
;|             |_|  \__,_|___/_|\___/|_| |_| *               |
;|                                                           |
;|               The MSX C Library for SDCC                  |
;|                     V1.3   -  04-2020                     |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|              Revision by Oduvaldo Pavan Junior            |
;|          Using suggestion by MRC User DarkSchneider       |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;|                                                           |
;\___________________________________________________________/
;
;
;	Interrupt functions Based on H.KEYI HOOK
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;	2020/04/07 Oduvaldo Pavan Junior - code based on MRC User DarkSchneider ;;
;;  example at :															;;
;; https://www.msx.org/forum/msx-talk/development/fusion-c-and-htimi?page=1 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;

 .area _CODE
  
; ---------------------------------------------------------
reset_vect	= 0x0000
bdos		= 0x0005
ramad1		= 0xF342
hookint		= 0xFD9A

; ---------------------------------------------------------
;	void InitInterruptHandler(int InterrupFunction)
; ---------------------------------------------------------
_InitInterruptHandler::
	push	ix
	ld		ix,#0
	add		ix,sp
	ld		l,4(ix)
	ld		h,5(ix)
	pop		ix
	di
	ld		(intr_handler+1), hl	; Replace in intr_handler the address
	
	;	save hookint 
	ld		hl, #hookint
	ld		de, #backup_hookint
	ld		bc, #5
	ldir
		
	ld		a, #0xF7				; RST_30 (interslot call both dos and bios)
	ld		(hookint), a
	ld		a, (ramad1)
	ld		(hookint+1), a
	ld		hl, #intr_handler
	ld		(hookint+2), hl
	ld		a, #0xc9
	ld		(hookint+4), a
	ei
	ret

backup_hookint:
	.ds		5

; ---------------------------------------------------------
;	void EndInterruptHandler(void)
; ---------------------------------------------------------
_EndInterruptHandler::
	di
	ld		hl, #backup_hookint
	ld		de, #hookint
	ld		bc, #5
	ldir
	ei
	ret

; ---------------------------------------------------------
;	intr_handler
; ---------------------------------------------------------
intr_handler:
	call	dummy_handler		; This will be replaced by user routine address
dummy_handler:
	jp		backup_hookint		; And continue processing interrupt hooks
	ret

	