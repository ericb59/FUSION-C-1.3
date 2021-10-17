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
; Call DOS functions
; 1995, SOLID MSX C & SDCC port 2015
; 2019-2020 Eric Boez
;
;
;	GetDisk


;----------------------------
;   MODULE  GetDisk
;   
;	int	GetDisk(void)
;	Return Current Drive number
;
;
;
 .area _CODE
 
 
_GetDisk::
	push	ix
	ld	c,#0x19
	call	#5
	pop	ix
	ld	h,#0
	ld	l,a
	
	ret