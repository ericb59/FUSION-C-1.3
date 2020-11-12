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
;     HideDisplay
;	  ShowDisplay




 .area _CODE
;----------------------------
;   MODULE  HideDisplay
;
;   void HideDisplay(void)
;   
;
;  
;

_CallBiosX1:

  ld iy, (0xFCC0)	; mainrom slotaddress 
  call 0x001c		; interslotcall
  ei
  pop ix
  ret

_HideDisplay::
  push ix
  ld   ix,#0x0041       ; Bios hide display routine
  jp _CallBiosX1


;----------------------------
;   MODULE  ShowDisplay
;
;   void ShowDisplay(void)
;   
;
;  
;

_ShowDisplay::
   push ix
   ld   ix,#0x0044       ; Bios show display routine
   jp _CallBiosX1