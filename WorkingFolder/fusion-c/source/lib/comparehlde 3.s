; ___________________________________________________________
;/               __           _                              \
;|              / _|         (_)                             |
;|             | |_ _   _ ___ _  ___  _ __                   |
;|             |  _| | | / __| |/ _ \| '_ \                  |
;|             | | | |_| \__ \ | (_) | | | |                 |
;|             |_|  \__,_|___/_|\___/|_| |_| *               |
;|                                                           |
;|               The MSX C Library for SDCC                  |
;|                     V1.3 - 02 - 2020                      |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;|                                                           |
;\___________________________________________________________/
;
;


;----------------------------------------------------------------------------;
; Compare function                                                           ;
;----------------------------------------------------------------------------;

; test if HL>=DE
; Input      HL, DE
; Output     A=0 -> true (HL>=DE)
;            A=4 -> false (HL<DE)
; modify     A, HL, DE
cmpgte:
	and a    ; RESET CARRY FLAG
	ld a,h
	xor d
	jp m,cmpgte2
	sbc hl,de
	jp nc,cmpgte3
cmpgte1:

	xor a
	sub l
	ld l,a
    sbc a,a
    sub h
    ld h,a

	ld a,#4 ; move to the left
	ret
cmpgte2: ; if here, one is negative, the other one is positive
	bit #7,d
	jp z,cmpgte1
cmpgte3:
	xor a  ; move to the right
	ret