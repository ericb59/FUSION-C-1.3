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
; void Beep(void)
;


.area _CODE


_Beep::
  push ix
  push iy

  ld iy, (0xFCC0)	; mainrom slotaddress (reference)
  ld ix, # 0x00C0	; Beep

  call 0x001c		; interslotcall
  ei
  pop iy 			; restore register
  pop ix
  ret

