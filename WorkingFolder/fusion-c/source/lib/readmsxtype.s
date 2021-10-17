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
;    Read MSX Type


 .area _CODE

;----------------------------
;   MODULE  ReadMSXType
;
;   void ReadMSXType(void)
;   
;   
;   
;
_ReadMSXtype::
  push ix
  
  ld ix,#0x000c   	; Bios Read From Slot
  
  ld iy,(0xFCC0)	; mainrom slotaddress 
  ld a,(#0xFCC1)
  ld hl,#0x2d       ; Adresse to read
  di
  call 0x001c		; interslotcall

  ei
  ld l,a      ; Return value to L 
  pop ix
  ret
