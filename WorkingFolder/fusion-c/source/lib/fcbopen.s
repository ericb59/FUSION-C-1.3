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
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;	fcb_access.s for MSX													;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;	2006/12/02	t.hara														;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;	FcbOpen
;	FcbCreate
;
	.area _CODE

;;	unsigned char FcbOpen( FCB *p_fcb );
_FcbOpen::
	ld		hl, #2
	add		hl, sp

	push	ix
	ld		e, (hl)			;;	de <= p_fcb
	inc		hl
	ld		d, (hl)
	push	de

	ld		c, #0x0F		;;	open file (DOS function)
	call	0x0005			;;	call system
	jr		_fcb_open_exit

;;	unsigned char FcbCreate( FCB *p_fcb );
_FcbCreate::
	ld		hl, #2
	add		hl, sp

	push	ix
	ld		e, (hl)			;;	de <= p_fcb
	inc		hl
	ld		d, (hl)
	push	de

	ld		c, #0x16		;;	create file (DOS function)
	call	0x0005			;;	call system
_fcb_open_exit:
	pop		iy				;;	iy <= p_fcb
	ld		12(iy), #0
	ld		14(iy), #1
	ld		15(iy), #0

	ld		l, a			;;	success(0) or fail(255)
	pop		ix
	ret