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
;    Cls


 .area _CODE

;----------------------------
;   MODULE  Cls
;
;   void Cls(void)
;   
;   
;   
;
_Cls::
  push ix
  ld   ix,#0x00c3   ; Bios CLS
  ld iy, (0xFCC0)	; mainrom slotaddress 
  call 0x001c		; interslotcall
  ei
  pop ix
  ret
