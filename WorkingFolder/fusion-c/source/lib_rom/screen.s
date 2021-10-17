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
; Call Bios functions
;
;     Screen




 .area _CODE

 ;----------------------------
;   MODULE  Screen
;
;   void Screen(char scr) 
;   
;
;  
;

_Screen::
	xor		a
	ld		hl, #0xFAF5		;;	DPPAGE
	ld		(hl), a
	inc		hl				    ;;	ACPAGE
	ld		(hl), a

	ld		hl, #2
	add		hl, sp

	ld		a, (hl)			  ;;	mode
	ld 		hl,#0xFCAF		;; Save current mode to FCAF 
	ld 		(hl),a
  	call 	0x005f			; interslotcall
  	ei
  	ret