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
;    SetColors



 FORCLR   =   0xF3E9       ; foreground color 
 BAKCLR   =   0xF3EA       ; background color
 BDRCLR   =   0xF3EB       ; border color

 .area _CODE
;----------------------------
;   MODULE  SetColors
;
;   void SetColors (unsigned char foreground, unsigned char background, unsigned char border)  
;   
;   
;   
;

_SetColors::    
  push ix
  ld   ix,#0
  add  ix,sp
  ld   a,4(ix)
  ld   (FORCLR),a
  ld   a,5(ix)
  ld   (BAKCLR),a
  ld   a,6(ix)
  ld   (BDRCLR),a
  call 0x0062		
  ;ei
  pop ix
  ret